#pragma once

#include <future>
#include <thread>
#include <utility>
#include <algorithm>
#include <type_traits>

#pragma region MINE
#if defined(STD_RESULT_OF_SHIM) || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L // See the note below about why this is needed.
namespace std {
	template<typename> struct result_of;
	template<typename F, typename... Args>
	struct result_of<F(Args...)> : invoke_result<F, Args...> {};
}
#endif
#pragma endregion //MINE

template<typename F, typename A> std::future<typename std::result_of<F(A&&)>::type>
spawn_task(F&& f, A&& a) {
	typedef typename std::result_of<F(A&&)>::type result_type;

	std::packaged_task<result_type(A&&)> task(std::move(f));
	std::future<result_type> res(task.get_future());
	
	std::thread t(std::move(task), std::move(a));
	t.detach();
	
	return res;
}
/*
The note

That block is a **compatibility shim** so the textbook listing can keep using `std::result_of` while your project builds as **C++20/C++23**.

**What the book assumes**

*C++ Concurrency in Action* (circa C++11) was written when `std::result_of` lived in `<type_traits>` and was the usual way to get “the return type of calling `F` with these arguments.”

**What your project uses**

`4.4.1.vcxproj` sets `LanguageStandard` to `stdcpp20` / `stdcpp23`. In C++17 `std::result_of` was deprecated; in **C++20 it was removed** and replaced by `std::invoke_result`. So with your language setting, `std::result_of` simply does not exist in the standard library anymore — which is why you originally saw `'result_of': is not a member of 'std'`.

**What the shim does**

It reintroduces the old trait only when compiling as C++20 or later:

```cpp
struct result_of<F(Args...)> : invoke_result<F, Args...> {};
```

That mirrors the old `result_of<F(Args...)>::type` API using the modern replacement underneath, so this signature can stay as written:

```cpp
std::future<typename std::result_of<F(A&&)>::type>
```

**Why the `#if` and `STD_RESULT_OF_SHIM`**

The shim must **not** be defined in C++17 and earlier, because `std::result_of` is already provided there and you’d get a redefinition error. The conditions detect “we’re on C++20+”:

- `STD_RESULT_OF_SHIM` — defined in the `.vcxproj` so MSVC IntelliSense reliably enables the shim
- `_MSVC_LANG >= 202002L` — MSVC’s real language level (since `__cplusplus` is often still `199711L` without `/Zc:__cplusplus`)

**Alternatives (if you don’t want the shim)**

1. Set the project to **C++17** (`stdcpp17`) — `std::result_of` comes back from the standard library.
2. Modernize the listing to `std::invoke_result` / `std::invoke_result_t` — but that changes the textbook code.

So the shim exists purely to bridge **old textbook code** and **new language standard** without rewriting the listing.
*/
