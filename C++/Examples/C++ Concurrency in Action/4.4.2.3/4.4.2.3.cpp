#pragma region MINE

#include "message_queue.h"
#include "dispatcher.h"
#include "messages.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../../stdafx.h"
#include "debug.h"

static void worker_thread(message_queue* q) {
	try {
		for (;;) {
			dispatcher{q} // At the end of this statement, the temporary TemplateDispatcher dtor runs, blocking and processing exactly one valid incoming message.
				.handle<MsgA>([](MsgA const& msg) { std::cout << "[Worker] Handled MsgA: " << msg.text << std::endl; }) // See the note below.
				.handle<MsgB>([](MsgB const& msg) { std::cout << "[Worker] Handled MsgB: " << msg.value << std::endl; });
			#ifdef DEBUG
			std::println(".handle executed inside the for loop.\n");
			#endif
		}
	}
	catch (close_queue const&) {
		std::cout << "[Worker] Received close_queue. Shutting down cleanly." << std::endl;

		#ifdef DEBUG
		std::println("TemplateDispatcher dtor (via catch close_queue)");
		#endif
	}
}
			/* dispatcher(q) builds one nested type (names shortened):
			TemplateDispatcher<
				TemplateDispatcher<
					dispatcher,			// PreviousDispatcher
					MsgA, λA			// this link handles MsgA
				>,
				MsgB, λB				// outer link handles MsgB
			>
			TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, λA>, MsgB, λB>
			*/

int main() {
	print_file_line();

	message_queue q;
	std::jthread t(worker_thread, &q);

	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Send diverse messages to demonstrate runtime routing down the template chain
	q.push(MsgA{"Hello Chain!"});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push(MsgB{42});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push(close_queue{});

	return 0;
}

/*
The note

Question:
I’m trying to understand template chaining but find it difficult. I understand how basic templates generate type-specific instances, but chaining remains unclear even after simplifying textbook examples. Manually expanding templates didn’t help because the combinations grow exponentially. Ideally, I want to debug and step through the instantiations, but that’s been impractical. Please first explain how template chaining works, then help me set up a way to debug and visualize the generated code.

Answer:

The key insight: this is **not** exponential. You build one **linear nested type**, then at runtime walk that list with `dynamic_cast`. Manual expansion feels explosive because people try every message × every handler combo; the real structure is a short chain of pointers.

---

## How template chaining works here

### Two layers: type nesting (compile time) vs message walk (runtime)

Your call:

```133:139:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.2.6\4.4.2.6.cpp
			dispatcher(q)
				.handle<MsgA>([](MsgA const& msg) {
				std::cout << "[Worker] Handled MsgA: " << msg.text << std::endl;
				})
				.handle<MsgB>([](MsgB const& msg) {
				std::cout << "[Worker] Handled MsgB: " << msg.value << std::endl;
				});
```

builds **one** nested type (names shortened):

```text
TemplateDispatcher<
  TemplateDispatcher<
	dispatcher,           // PreviousDispatcher
	MsgA, λA              // this link handles MsgA
  >,
  MsgB, λB                // outer link handles MsgB
>
```

Each `.handle<>()` does **not** spawn a tree of specializations. It returns a **new** `TemplateDispatcher` whose first template argument is *the previous dispatcher type*:

```88:92:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.2.6\4.4.2.6.cpp
	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) {
		chained = true; // This link is now chained; responsibility moves to the new child
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}
```

So the growth is **linear in the number of `.handle` calls**, not combinatorial.

### Object graph at the semicolon

Temporaries form a linked list (outer → … → base):

```text
  [TD<MsgB>]  prev ──►  [TD<MsgA>]  prev ──►  [dispatcher]
   chained=false          chained=true           chained=true
   (will run the loop)    (dtor is a no-op)      (dtor is a no-op)
```

`chained = true` on every link that was used as `PreviousDispatcher` so only the **outermost** temporary’s destructor does work:

```94:97:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.2.6\4.4.2.6.cpp
	~TemplateDispatcher() noexcept(false) {
		// The last temporary in the chain (where chained is still false) runs the dispatch loop
		if (!chained) wait_and_dispatch();
	}
```

### Runtime: one message walks the chain

When a message arrives, `dispatch` tries **this** link, then forwards to `prev`:

```62:69:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.2.6\4.4.2.6.cpp
	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) {
			f(wrapper->contents);
			return true;
		}
		return prev->dispatch(msg);
	}
```

For `MsgB{42}`:

```text
TD<MsgB>::dispatch  →  match → run λB → true → exit wait loop
```

For `MsgA{"Hello"}`:

```text
TD<MsgB>::dispatch  →  no match → prev->dispatch
TD<MsgA>::dispatch  →  match → run λA → true
```

For `close_queue{}`:

```text
TD<MsgB> → miss → TD<MsgA> → miss → dispatcher::dispatch → throw close_queue
```

So: **compile time** = nested types + `prev` pointers; **runtime** = linear search of handlers via `dynamic_cast`.

### Why “manual expansion” feels exponential

People often expand as if every handler must be specialized against every message. Wrong model. Instantiations you actually get for this program are essentially:

| Instantiation | Role |
|---|---|
| `wrapped_message<MsgA>`, `<MsgB>`, `<close_queue>` | type-erased queue payloads |
| `TemplateDispatcher<dispatcher, MsgA, λA>` | first handler link |
| `TemplateDispatcher<TD<…MsgA…>, MsgB, λB>` | second handler link |
| `dispatcher::handle<MsgA,…>`, `TD::handle<MsgB,…>` | the two `.handle` calls |

That’s a handful of types, not 2ⁿ.

---

## Debugging and visualizing instantiations

### 1. Trace with `typeid` / prints (best mental model)

Add temporary logging inside `dispatch` / ctors / dtors (conceptually):

```cpp
std::cout << "dispatch trying " << typeid(Msg).name()
		  << " chained=" << chained << "\n";
```

Or a static counter per specialization:

```cpp
template<typename Prev, typename Msg, typename Func>
struct TemplateDispatcher {
  inline static int id = []{
	std::cout << "instantiated TD for " << typeid(Msg).name() << "\n";
	return 0;
  }();
  // ...
};
```

Breakpoints in `TemplateDispatcher::dispatch` then step: you’ll see the **same function body** for different `Msg`, once per link.

### 2. MSVC: list instantiations (see the chain names)

In the project’s C/C++ → Command Line, or `/d1reportSingleClassLayoutTemplateDispatcher` / more usefully:

- `/d1reportAllClassLayout` is heavy
- Better: **`/FAs`** (assembly with source) or look at **Browse information**
- Clang/GCC style (if you have clang-cl): **`-Xclang -ftemplate-backtrace-limit=0`** on a deliberate error

Deliberate “force print types” trick (works on MSVC/Clang/GCC):

```cpp
template<typename T> struct show_type;  // incomplete

// temporarily in worker_thread, after building the chain conceptually:
show_type<decltype(
  dispatcher(q)
	.handle<MsgA>([](MsgA const&){})
	.handle<MsgB>([](MsgB const&){})
)>();
```

The compiler error **names the full nested type** — that’s the visualization of the chain.

### 3. Debugger: step the *runtime* chain, not every template

In Visual Studio:

1. Break on `TemplateDispatcher::dispatch` (or `wait_and_dispatch`).
2. Watch `typeid(Msg).name()`, `chained`, `prev`.
3. Step into `prev->dispatch(msg)` — that’s walking the chain.
4. Don’t try to “step through template instantiation”; that’s a compile-time process. Instantiation already happened when the `.exe` was built.

Temporaries: break on `~TemplateDispatcher` and check `chained`. Only the outer one enters `wait_and_dispatch`.

### 4. Draw the chain once (non-exponential checklist)

For `N` handlers, write:

```text
handle #1: Previous = dispatcher,           Msg = MsgA
handle #2: Previous = TD<..., MsgA>,        Msg = MsgB
handle #3: Previous = TD<..., MsgB>,        Msg = MsgC
...
Runtime walk: MsgN → MsgN-1 → … → MsgA → dispatcher
```

One row per `.handle`. Stop when that table is filled; don’t expand message×handler matrices.

### 5. Compiler Explorer / Godbolt

Paste a minimal version (same types, no threads). Use “MSVC” or “clang”, enable “Demangle”, and inspect symbols like:

```text
TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, ...>, MsgB, ...>::dispatch
```

You should see **two** `dispatch` specializations, not an explosion.

### 6. Clang’s `-Xclang -fdump-record-layouts` / `-ftime-trace`

Useful for big TMP; overkill here. For this example, the `show_type` error or a couple of `typeid` prints is enough.

---

## Mental model in one sentence

**`.handle` nests types and links `prev` pointers; the outermost destructor waits; each message walks those links with `dynamic_cast` until one matches or the base throws.**

If you want, in Agent mode I can add a small optional `TRACE_CHAIN` macro to this file that prints ctor/dtor/`dispatch` steps without changing behavior. In Ask mode I can only outline it as above.
*/
#pragma endregion //MINE