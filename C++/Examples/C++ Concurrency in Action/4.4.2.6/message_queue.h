#pragma once

#include "wrapped_message.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

class message_queue {
public:
	template<typename T>
	void push(T const& msg) {
		std::scoped_lock lk(m);
		q.push(std::make_shared<wrapped_message<T>>(msg));
		cv.notify_all();
	}

	std::shared_ptr<message_base> wait_and_pop() {
		std::unique_lock lk(m);
		cv.wait(lk, [&] { return !q.empty(); });
		auto res = q.front();
		q.pop();
		return res;
	}
private:
	std::mutex m;
	std::condition_variable cv;
	std::queue<std::shared_ptr<message_base>> q;
};
