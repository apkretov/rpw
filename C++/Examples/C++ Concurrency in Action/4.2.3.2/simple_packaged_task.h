#pragma region MINE
#pragma once // simple_packaged_task wraps a callable and owns a promise internally.

#include <functional>
#include <type_traits>
#include "simple_promise.h"
#include "simple_future.h"
using namespace std;

template <typename F> class simple_packaged_task; // primary template not defined

template <typename R, typename... Args> 
class simple_packaged_task<R(Args...)> { // Specialization for general callable type.
public:
	template <typename F> 
	explicit simple_packaged_task(F&& f) : func(forward<F>(f)) {} // Construct from any callable that can be stored in function.

	simple_packaged_task(const simple_packaged_task&) = delete;
	simple_packaged_task& operator=(const simple_packaged_task&) = delete;
	simple_packaged_task(simple_packaged_task&& other) noexcept : func(move(other.func)), prom(move(other.prom)) {}

	simple_packaged_task& operator=(simple_packaged_task&& other) noexcept {
		if (this != &other) {
			func = move(other.func);
			prom = move(other.prom);
		}
		return *this;
	}

	simple_future<R> get_future() { return prom.get_future(); } // Get future from internal promise.

	void operator()(Args... args) { // Invoke the stored callable, set value or exception.
		try {
			if constexpr (is_void_v<R>) {
				func(forward<Args>(args)...); // If it appears, ignore the compiler warning: "std::forward" should only be called on a forwarding reference.
				prom.set_value();
			} else {
				R result = func(forward<Args>(args)...); // Same as above.
				prom.set_value(move(result));
			}
		}
		catch (...) {
			prom.set_exception(current_exception());
		}
	}
private:
	function<R(Args...)> func;
	simple_promise<R> prom;
};
#pragma endregion //MINE