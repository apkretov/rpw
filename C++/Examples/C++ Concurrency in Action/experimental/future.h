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
	bool is_ready() const {
		return inner.valid() && inner.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
	}

	template <typename F>
	auto then(F&& func) { // Continuations TS: schedule func(*this) when ready; invalidates *this.
		using U = std::invoke_result_t<std::decay_t<F>, future>;
		std::future<T> moved = std::move(inner);

		if constexpr (detail::is_experimental_future_v<U>) {
			// Continuations TS unwraps a returned future<R> to future<R>.
			using R = typename detail::future_value<U>::type;
			std::promise<R> p;
			auto result = future<R>(p.get_future());
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)),
							moved = std::move(moved)]() mutable {
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
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)),
							moved = std::move(moved)]() mutable {
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

	template <typename F>
	auto then(F&& func) {
		using U = std::invoke_result_t<std::decay_t<F>, future>;
		std::future<void> moved = std::move(inner);

		if constexpr (detail::is_experimental_future_v<U>) {
			using R = typename detail::future_value<U>::type;
			std::promise<R> p;
			auto result = future<R>(p.get_future());
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)),
							moved = std::move(moved)]() mutable {
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
			std::thread([p = std::move(p), f = std::decay_t<F>(std::forward<F>(func)),
							moved = std::move(moved)]() mutable {
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
