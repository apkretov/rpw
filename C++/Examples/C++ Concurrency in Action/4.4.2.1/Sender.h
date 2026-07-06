#pragma once

#pragma region MINE
#include "queue.h"
#include "wrapped_message.h"
#include <memory>

namespace messaging {
class sender {
	queue* q;
public:
	sender() : q(nullptr) {}
	explicit sender(queue* q_) : q(q_) {}

	template<typename Message>
	void send(Message const& msg) {
		if (q)
			q->push(std::make_shared<wrapped_message<Message>>(msg));
	}
};
}
#pragma endregion //MINE