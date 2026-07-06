#pragma once

//## Safe Thread - Safe Stack(Listing 3.5)
//Combines top / pop atomically; uses shared_ptr or ref overload; throws on empty.

#include <algorithm>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <utility>

struct EmptyStack : std::exception {
	const char* what() const noexcept { return "empty_stack"; }
};

template<typename T>
class ThreadSafeStack {
	mutable std::mutex m;
	std::stack<T> data;
public:
	ThreadSafeStack() = default;

	ThreadSafeStack(const ThreadSafeStack& other) {
		std::scoped_lock lock(m, other.m);
		data = other.data;
	}

	ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;

	void push(T newValue) {
		std::scoped_lock lock(m);
		data.push(std::move(newValue));
	}

	std::shared_ptr<T> pop() {
		std::scoped_lock lock(m);
		if (data.empty())
			throw EmptyStack{};
		std::shared_ptr<T> res = std::make_shared<T>(data.top());
		data.pop();
		return res;
	}

	void pop(T& value) {
		std::scoped_lock lock(m);
		if (data.empty())
			throw EmptyStack{};
		value = data.top();
		data.pop();
	}

	bool empty() const {
		std::scoped_lock lock(m);
		return data.empty();
	}
};
