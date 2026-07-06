#pragma region MINE
#pragma once

#include <exception>
#include <memory>
#include <utility>
#include "shared_state.h"
using namespace std;

template <typename T> class simple_future; // Forward declaration to break circular dependency

template <typename T>
class simple_promise {
public:
	simple_promise() : state(make_shared<shared_state<T>>()) {}
	simple_promise(const simple_promise&) = delete; // Disable copy for simplicity; real promise is movable.
	simple_promise& operator=(const simple_promise&) = delete;
	simple_promise(simple_promise&& other) noexcept : state(move(other.state)) {}

	simple_promise& operator=(simple_promise&& other) noexcept {
		if (this != &other) 
			state = move(other.state);
		return *this;
	}
	
	simple_future<T> get_future(); // Get the associated future.
	void set_value(const T& v) { state->set_value(v); } // Set the result value.
	void set_value(T&& v) { state->set_value(move(v)); }
	void set_exception(exception_ptr e) { state->set_exception(e); } // Set an exception.
private:
	shared_ptr<shared_state<T>> state;
	template <typename U> friend class simple_future;
};

template <> 
class simple_promise<void> { // The full template specialization for void (no value to store).
public:
	simple_promise() : state(make_shared<shared_state<void>>()) {}
	simple_promise(const simple_promise&) = delete;
	simple_promise& operator=(const simple_promise&) = delete;
	simple_promise(simple_promise&& other) noexcept : state(move(other.state)) {}

	simple_promise& operator=(simple_promise&& other) noexcept {
		if (this != &other) {
			state = move(other.state);
		}
		return *this;
	}

	simple_future<void> get_future();
	void set_value() { state->set_value(); }
	void set_exception(exception_ptr e) { state->set_exception(e); }
private:
	shared_ptr<shared_state<void>> state;
	template <typename U> friend class simple_future;
};

#include "simple_future.h"

template <typename T>
simple_future<T> simple_promise<T>::get_future() { return simple_future<T>(state); } // Now that future is defined, implement get_future() for promise.

inline simple_future<void> simple_promise<void>::get_future() { return simple_future<void>(state); }
#pragma endregion //MINE