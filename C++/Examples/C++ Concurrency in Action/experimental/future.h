#pragma region MINE
// Teaching stand-in for Concurrency TS <experimental/future>.
// MSVC never shipped this header; the TS was withdrawn from standardization.
#pragma once

#include <chrono>
#include <future>
#include <thread>
#include <type_traits>
#include <utility>

namespace std::experimental {
template <typename T>
class future;

template <typename T>
class shared_future;

namespace detail {
template <typename T>
struct is_experimental_future : std::false_type {};

template <typename T>
struct is_experimental_future<future<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_experimental_future_v = is_experimental_future<T>::value;

template <typename T>
struct future_value;

template <typename T>
struct future_value<future<T>> {
	using type = T;
};
} // namespace detail

template <typename T>
class future {
public:
	future() noexcept = default;
	explicit future(std::future<T> f) noexcept : inner(std::move(f)) {}
	future(future&&) noexcept = default;
	future& operator=(future&&) noexcept = default;
	future(const future&) = delete;
	future& operator=(const future&) = delete;

	T get() { return inner.get(); }
	bool valid() const noexcept { return inner.valid(); }
	void wait() const { inner.wait(); }
	bool is_ready() const { return valid() && inner.wait_for(std::chrono::seconds(0)) == std::future_status::ready; }
	shared_future<T> share();

	template <typename F>
	auto then(F&& func) { // Continuations TS: schedule func(*this) when ready; invalidates *this.
		using U = std::invoke_result_t<std::decay_t<F>, future>; // See the note about std::invoke_result_t<std::decay_t... below.

		if constexpr (detail::is_experimental_future_v<U>) { // Continuations TS unwraps a returned future<R> to future<R>.
			using R = typename detail::future_value<U>::type;
			std::promise<R> p;
			auto result = future<R>(p.get_future()); // See the note about future<R>(p.get_future()) below.
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)), moved = std::move(inner)]() mutable {
				try {
					future self(std::move(moved));
					U nested = f(std::move(self));
					if constexpr (std::is_void_v<R>) {
						nested.get();
						p.set_value();
					} else
						p.set_value(nested.get());
				} catch (...) {
					p.set_exception(std::current_exception());
				}
			}).detach();
			return result;
		} else {
			std::promise<U> p;
			auto result = future<U>(p.get_future());
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)), moved = std::move(inner)]() mutable {
				try {
					future self(std::move(moved));
					if constexpr (std::is_void_v<U>) {
						f(std::move(self));
						p.set_value();
					} else
						p.set_value(f(std::move(self)));
				} catch (...) {
					p.set_exception(std::current_exception());
				}
			}).detach();
			return result;
		}
	}
private:
	std::future<T> inner;
};

template <>
class future<void> {
public:
	future() noexcept = default;
	explicit future(std::future<void> f) noexcept : inner(std::move(f)) {}
	future(future&&) noexcept = default;
	future& operator=(future&&) noexcept = default;
	future(const future&) = delete;
	future& operator=(const future&) = delete;

	void get() { inner.get(); }
	bool valid() const noexcept { return inner.valid(); }
	void wait() const { inner.wait(); }
	bool is_ready() const {
		return inner.valid() && inner.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
	}
	shared_future<void> share();

	template <typename F>
	auto then(F&& func) {
		using U = std::invoke_result_t<std::decay_t<F>, future>;

		if constexpr (detail::is_experimental_future_v<U>) {
			using R = typename detail::future_value<U>::type;
			std::promise<R> p;
			auto result = future<R>(p.get_future());
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)), moved = std::move(inner)]() mutable {
				try {
					future self(std::move(moved));
					U nested = f(std::move(self));
					if constexpr (std::is_void_v<R>) {
						nested.get();
						p.set_value();
					} else
						p.set_value(nested.get());
				} catch (...) {
					p.set_exception(std::current_exception());
				}
			}).detach();
			return result;
		} else {
			std::promise<U> p;
			auto result = future<U>(p.get_future());
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)), moved = std::move(inner)]() mutable {
				try {
					future self(std::move(moved));
					if constexpr (std::is_void_v<U>) {
						f(std::move(self));
						p.set_value();
					} else
						p.set_value(f(std::move(self)));
				} catch (...) {
					p.set_exception(std::current_exception());
				}
			}).detach();
			return result;
		}
	}

private:
	std::future<void> inner;
};

template <typename T>
class shared_future {
public:
	shared_future() noexcept = default;
	explicit shared_future(std::shared_future<T> f) noexcept : inner(std::move(f)) {}

	T const& get() const { return inner.get(); }
	bool valid() const noexcept { return inner.valid(); }
	void wait() const { inner.wait(); }

	template <typename F>
	auto then(F&& func) const {
		using U = std::invoke_result_t<std::decay_t<F>, shared_future>;
		std::promise<U> p;
		auto result = future<U>(p.get_future());
		auto shared = inner;

		std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)),
					 shared = std::move(shared)]() mutable {
			try {
				shared_future self(std::move(shared));
				if constexpr (std::is_void_v<U>) {
					f(std::move(self));
					p.set_value();
				} else
					p.set_value(f(std::move(self)));
			} catch (...) {
				p.set_exception(std::current_exception());
			}
		}).detach();
		return result;
	}

private:
	std::shared_future<T> inner;
};

template <>
class shared_future<void> {
public:
	shared_future() noexcept = default;
	explicit shared_future(std::shared_future<void> f) noexcept : inner(std::move(f)) {}

	void get() const { inner.get(); }
	bool valid() const noexcept { return inner.valid(); }
	void wait() const { inner.wait(); }

	template <typename F>
	auto then(F&& func) const {
		using U = std::invoke_result_t<std::decay_t<F>, shared_future>;
		std::promise<U> p;
		auto result = future<U>(p.get_future());
		auto shared = inner;

		std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)),
					 shared = std::move(shared)]() mutable {
			try {
				shared_future self(std::move(shared));
				if constexpr (std::is_void_v<U>) {
					f(std::move(self));
					p.set_value();
				} else
					p.set_value(f(std::move(self)));
			} catch (...) {
				p.set_exception(std::current_exception());
			}
		}).detach();
		return result;
	}

private:
	std::shared_future<void> inner;
};

template <typename T>
shared_future<T> future<T>::share() { return shared_future<T>(inner.share()); }

inline shared_future<void> future<void>::share() { return shared_future<void>(inner.share()); }

template <typename T>
class promise {
public:
	promise() = default;
	promise(promise&&) noexcept = default;
	promise& operator=(promise&&) noexcept = default;
	promise(const promise&) = delete;
	promise& operator=(const promise&) = delete;

	future<T> get_future() { return future<T>(inner.get_future()); }

	void set_value(const T& value) { inner.set_value(value); }
	void set_value(T&& value) { inner.set_value(std::move(value)); }
	void set_exception(std::exception_ptr e) { inner.set_exception(std::move(e)); }

	void set_value_at_thread_exit(const T& value) { inner.set_value_at_thread_exit(value); }
	void set_value_at_thread_exit(T&& value) { inner.set_value_at_thread_exit(std::move(value)); }
	void set_exception_at_thread_exit(std::exception_ptr e) {
		inner.set_exception_at_thread_exit(std::move(e));
	}

private:
	std::promise<T> inner;
};

template <>
class promise<void> {
public:
	promise() = default;
	promise(promise&&) noexcept = default;
	promise& operator=(promise&&) noexcept = default;
	promise(const promise&) = delete;
	promise& operator=(const promise&) = delete;

	future<void> get_future() { return future<void>(inner.get_future()); }

	void set_value() { inner.set_value(); }
	void set_exception(std::exception_ptr e) { inner.set_exception(std::move(e)); }

	void set_value_at_thread_exit() { inner.set_value_at_thread_exit(); }
	void set_exception_at_thread_exit(std::exception_ptr e) {
		inner.set_exception_at_thread_exit(std::move(e));
	}

private:
	std::promise<void> inner;
};

template <typename T>
future<T> make_ready_future(T value) {
	std::promise<T> p;
	p.set_value(std::move(value));
	return future<T>(p.get_future());
}

inline future<void> make_ready_future() {
	std::promise<void> p;
	p.set_value();
	return future<void>(p.get_future());
}
} // namespace std::experimental
#pragma endregion // MINE

/*
The note about std::invoke_result_t<std::decay_t...

# What does this line do?

using U = std::invoke_result_t<std::decay_t<F>, future>;

This defines `U` as the **return type obtained by calling the continuation `F` with a `future` argument**.

In other words, it asks the compiler to determine the type of:

```cpp
F{}(future<T>{})
```

more precisely, the type of invoking a stored/decayed `F` with `future<T>`.

## Breaking it down

### `std::decay_t<F>`

`F` is the type of the continuation parameter:

```cpp
template <typename F>
auto then(F&& func)
```

Because `F&&` is a forwarding reference, `F` may be:

```cpp
SomeCallable&
SomeCallable&&
const SomeCallable&
```

`std::decay_t<F>` normalizes that type by removing:

- references,
- `const`/`volatile` qualifiers,
- array/function special properties.

For example:

```cpp
F = MyLambda&
std::decay_t<F> = MyLambda
```

This matches what the code later stores:

```cpp
f = std::decay_t<F>(std::forward<F>(func))
```

So the callable is treated as an owned, value-like object.

### `std::invoke_result_t<Callable, Args...>`

`std::invoke_result_t<F, future>` determines the result type of invoking `F` with a `future` argument at compile time. `std::invoke_result_t` is the helper alias for `std::invoke_result`, which deduces the return type of a callable invocation.[^1_1][^1_2]

For example:

```cpp
future<int> input;

auto f = [](future<int>) {
	return 42.0;
};
```

Then:

```cpp
using U = std::invoke_result_t<decltype(f), future<int>>;
// U is double
```

In your code, `future` means the current specialization `future<T>`, because this line is inside:

```cpp
template <typename T>
class future
```

Therefore, if:

```cpp
auto next = [](future<int>) {
	return std::string{"done"};
};
```

then:

```cpp
U = std::string
```

## Why the code needs `U`

The following branch checks whether the continuation itself returns another experimental future:

```cpp
if constexpr (detail::is_experimental_future_v<U>) {
```

There are two cases.

### Ordinary return value

```cpp
future<int>.then([](future<int>) {
	return std::string{"result"};
});
```

Here:

```cpp
U = std::string
```

The implementation creates:

```cpp
std::promise<std::string>
future<std::string>
```

and eventually stores the returned string in the promise.

### Nested future

```cpp
future<int>.then([](future<int>) {
	return future<double>{ ... };
});
```

Here:

```cpp
U = future<double>
```

The code detects this and unwraps the nested future :

```cpp
future<future<double>>  // avoided
```

Instead, it returns :

```cpp
future<double>
```

This is what the comment means by :

```cpp
// Continuations TS unwraps a returned future<R> to future<R>.
```

The relevant type extraction is :

```cpp
using R = typename detail::future_value<U>::type;
```

For `U = future<double>`, `R` is `double`.
*/

/*
See the note about future<R>(p.get_future())

---

# I don't understand why

auto result = future<R>(p.get_future());
is needed instead of for example just
auto result = p.get_future();

`p.get_future()` and `future<R>(p.get_future())` have different types.

## What `p.get_future()` returns

For:

```cpp
std::promise<R> p;
```

the standard library function returns:

```cpp
std::future<R>
```

That is the standard future associated with the promise's shared state. The promise later writes into that shared state with `set_value()` or `set_exception()`, while the future reads from it with `get()` or `wait()`.[^3_1][^3_2]

So this:

```cpp
auto result = p.get_future();
```

gives:

```cpp
std::future<R>
```


## What `then` must return

Your custom `then` function is a member of:

```cpp
std::experimental::future<T>
```

and is intended to return another custom future:

```cpp
std::experimental::future<R>
```

Your wrapper has this constructor:

```cpp
explicit future(std::future<T> f) noexcept
	: inner(std::move(f)) {}
```

Therefore, this expression:

```cpp
future<R>(p.get_future())
```

takes the standard future and wraps it inside your custom future:

```text
std::future<R>
		│
		▼
std::experimental::future<R>
```

The wrapper stores the standard future here:

```cpp
private:
	std::future<T> inner;
```

The result then exposes your wrapper's interface:

```cpp
result.get();
result.wait();
result.then(...);
result.is_ready();
```
*/