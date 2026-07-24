#pragma region MINE
#pragma once

#include <condition_variable>
#include <exception>
#include <mutex>
#include <utility>

template <typename T>
class shared_state { // This is the core object both promise and future point to. It owns the result (or exception) and the synchronization primitives.
public:
	void set_value(const T& v) { // Store a value and mark the state as ready, then wake waiters.
		{
			std::scoped_lock lock(m);
			value = v;
			ready = true;
		}
		cv.notify_all();
	}

	void set_value(T&& v) {
		{
			std::scoped_lock lock(m);
			value = std::move(v);
			ready = true;
		}
		cv.notify_all();
	}

	void set_exception(std::exception_ptr e) { // Store an exception and mark ready, then wake waiters.
		{
			std::scoped_lock lock(m);
			exc = e;
			has_exception = true;
			ready = true;
		}
		cv.notify_all();
	}

	void wait() { // Block until ready is true.
		std::unique_lock lock(m);
		cv.wait(lock, [this] { return ready; });
	}

	T get() { // Get the value or rethrow the stored exception.
		wait();
		if (has_exception)
			std::rethrow_exception(exc);
		return value;
	}
private:
	T value{};
	bool ready = false;
	bool has_exception = false;
	std::exception_ptr exc;

	std::mutex m;
	std::condition_variable cv;
};

template <>
class shared_state<void> { // The full template specialization for void (no value to store).
public:
	void set_value() {
		{
			std::scoped_lock lock(m);
			ready = true;
		}
		cv.notify_all();
	}

	void set_exception(std::exception_ptr e) {
		{
			std::scoped_lock lock(m);
			exc = e;
			has_exception = true;
			ready = true;
		}
		cv.notify_all();
	}

	void wait() {
		std::unique_lock lock(m);
		cv.wait(lock, [this] { return ready; });
	}

	void get() {
		wait();
		if (has_exception) 
			std::rethrow_exception(exc);
		// nothing to return
	}
private:
	bool ready = false;
	bool has_exception = false;
	std::exception_ptr exc;

	std::mutex m;
	std::condition_variable cv;
};
#pragma endregion //MINE