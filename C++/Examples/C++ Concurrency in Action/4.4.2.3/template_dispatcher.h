#pragma once

#pragma region MINE

#include "message_queue.h"
#include <utility>
#include <memory>
#include "debug.h"

template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
	template<typename D, typename M, typename F> 
	friend class TemplateDispatcher;
public:
	TemplateDispatcher(message_queue* q_, PreviousDispatcher* prev_, Func&& f_) : q(q_), prev(prev_), f(std::forward<Func>(f_)) { 
		#ifdef DEBUG
		std::println("TemplateDispatcher ctor, Msg = {}", typeid(Msg).name()); // See the note below.
		#endif
	}
	
	~TemplateDispatcher() noexcept(false) {
		if (!chained) // The last temporary in the chain (where chained is still false) runs the dispatch loop
			for (;;)
				if (dispatch(q->wait_and_pop()))
					break; // Stop waiting once a message is successfully handled
	
		#ifdef DEBUG
		std::println("TemplateDispatcher dtor, Msg = {}", typeid(Msg).name());
		#endif
	}

	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) {
		#ifdef DEBUG
		std::println("TemplateDispatcher handle, Msg = {}", typeid(Msg).name());
		#endif

		chained = true; // This link is now chained; responsibility moves to the new child
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}
private:
	message_queue* q;
	bool chained = false;
	PreviousDispatcher* prev;
	Func f;

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) { // If the message type matches this link, handle it and break the loop
			f(wrapper->contents);
			return true;
		}
		return prev->dispatch(msg); // Otherwise, forward it down to the previous link in the chain
	}
};

/*
The note

Question:

When the class TemplateDispatcher is constructed, does it already know the message type from its template parameters (template<typename PreviousDispatcher, typename Msg, typename Func> class TemplateDispatcher)?

I want to print the type in the constructor body to verify whether the class already knows it at that point. My goal is to visualize when instances of this class are constructed. If I am mistaken, please explain how the class determines the message type from its template parameters, if it does at all. If it does not, does dynamic casting handle the type switching instead? If that is still incorrect, please explain what actually happens inside the constructors when templates are instantiated into concrete classes.


Answer:

Yes. By the time any constructor of `TemplateDispatcher` runs, `Msg` is already a fixed concrete type for that specialization. Instantiation is finished at compile time; the ctor only runs for that already-typed class.

## What “knows the type” means

```8:9:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.2.6\template_dispatcher.h
template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
```

Each use of `.handle<SomeMsg>(…)` creates a **different class**, not one class that later learns `Msg`:

| Call site | Concrete class (conceptually) |
|---|---|
| `dispatcher(q).handle<MsgA>(λA)` | `TemplateDispatcher<dispatcher, MsgA, typeof(λA)>` |
| `.handle<MsgB>(λB)` on that result | `TemplateDispatcher<TemplateDispatcher<…MsgA…>, MsgB, typeof(λB)>` |

So when the second ctor body runs, for that object `Msg` **is** `MsgB`. The first temporary’s type has `Msg = MsgA`. There is no “switching” of `Msg` inside one object.

You can print it in the ctor:

```cpp
TemplateDispatcher(message_queue* q_, PreviousDispatcher* prev_, Func&& f_)
	: q(q_), prev(prev_), f(std::forward<Func>(f_)) {
#ifdef DEBUG
	std::println("TemplateDispatcher ctor, Msg = {}", typeid(Msg).name());
#endif
}
```

On MSVC you’ll often see mangled names (`struct MsgA`); that’s still enough to see which link was built. For prettier names you can use a small `type_name<Msg>()` helper, but `typeid(Msg)` already answers “does the class know `Msg` here?” — **yes**.

## When that knowledge is fixed

1. **Compile time:** the compiler sees `.handle<MsgA>(…)` / `.handle<MsgB>(…)` and generates two specializations (two class types, two ctor functions, two `dispatch` functions).
2. **Runtime:** constructing those objects only executes the already-generated ctor for that specialization. The ctor does **not** deduce `Msg`; `Msg` is part of the type of `*this`.

Your `DEBUG` prints of `"TemplateDispatcher ctor"` should fire **twice** per worker-loop iteration (once for the `MsgA` link, once for the `MsgB` link), before the outermost dtor blocks in the wait loop.

## Role of `dynamic_cast` (not type discovery for the class)

```37:42:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.2.6\template_dispatcher.h
	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) {
			f(wrapper->contents);
			return true;
		}
		return prev->dispatch(msg);
	}
```

Here `Msg` is again the **compile-time** parameter of **this** link. The cast answers a different question:

- Queue stores `shared_ptr<message_base>` (type-erased).
- This link asks: “Is *this* runtime message a `wrapped_message<Msg>` for **my** `Msg`?”
- If yes → call `f`; if no → forward to `prev`.

So:

- **Templates / `Msg`:** which handler link this object is (fixed at construction / instantiation).
- **`dynamic_cast`:** whether the **incoming** erased message matches that link’s `Msg`.

`dynamic_cast` does not tell the class what `Msg` is; it uses the already-known `Msg` to test the payload.

## What actually happens “inside” construction when templates are instantiated

There is no runtime “template engine” in the ctor. Roughly:

1. Instantiation produces a normal C++ class, as if you had handwritten e.g. `class TD_MsgB { using Msg = MsgB; … }`.
2. Constructing it runs that class’s ctor: store `q`, `prev`, move/forward `f`, maybe print.
3. `chained` starts `false` until a further `.handle` marks this link as non-outermost.

Type nesting is only in the **type of `PreviousDispatcher`** and the **`prev` pointer**; message routing at runtime walks that pointer chain and uses each link’s fixed `Msg` in `dynamic_cast`.

**Bottom line:** printing `typeid(Msg)` (or a demangled name) in the ctor is the right way to visualize which concrete links are being built; you’re not mistaken about the class already knowing `Msg` at that point.
*/
#pragma endregion //MINE