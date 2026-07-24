#pragma region MINE
#pragma once

#include "shared_state.h"
#include <stdexcept>
#include <memory>
#include <utility>

template <typename T>
class simple_future {
public:
	simple_future() = default;
	explicit simple_future(std::shared_ptr<shared_state<T>> s) : state(std::move(s)) {}
	simple_future(const simple_future&) = delete;
	simple_future& operator=(const simple_future&) = delete;
	simple_future(simple_future&& other) noexcept : state(std::move(other.state)) {}

	simple_future& operator=(simple_future&& other) noexcept {
		if (this != &other)
			state = std::move(other.state);
		return *this;
	}

	T get() { // Block until value is ready and return it.
		if (!state)
			throw std::runtime_error("no state");
		auto tmp = state; // get() consumes the state in real future; we mimic that.
		state.reset();
		return tmp->get();
	}
	
	void wait() const {
		if (!state) 
			throw std::runtime_error("no state");
		state->wait();
	}

	bool valid() const noexcept { return static_cast<bool>(state); }
private:
	std::shared_ptr<shared_state<T>> state;
};

template <>
class simple_future<void> { // The full template specialization for void (no value to store).
public:
	simple_future() = default;
	explicit simple_future(std::shared_ptr<shared_state<void>> s) : state(std::move(s)) {}
	simple_future(const simple_future&) = delete;
	simple_future& operator=(const simple_future&) = delete;
	simple_future(simple_future&& other) noexcept : state(std::move(other.state)) {}

	simple_future& operator=(simple_future&& other) noexcept {
		if (this != &other) 
			state = std::move(other.state);
		return *this;
	}

	void get() {
		if (!state) 
			throw std::runtime_error("no state");
		auto tmp = state;
		state.reset();
		tmp->get();
	}

	void wait() const {
		if (!state) 
			throw std::runtime_error("no state");
		state->wait();
	}

	bool valid() const noexcept { return static_cast<bool>(state); }
private:
	std::shared_ptr<shared_state<void>> state;
};
#pragma endregion //MINE
