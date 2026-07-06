#pragma once

#pragma region MINE
#include "message_base.h"
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace messaging {
class queue {
    std::mutex m;
    std::condition_variable cv;
    std::queue<std::shared_ptr<message_base>> q;
public:
    void push(std::shared_ptr<message_base> msg) {
        std::scoped_lock lk(m);
        q.push(msg);
        cv.notify_all();
    }
        
	std::shared_ptr<message_base> wait_and_pop() {
        std::unique_lock lk(m);
        cv.wait(lk, [this] { return !q.empty(); });
        auto res = q.front();
        q.pop();
        return res;
    }
};
}
#pragma endregion //MINE