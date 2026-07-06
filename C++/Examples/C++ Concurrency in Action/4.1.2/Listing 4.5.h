#include <condition_variable>
#include <memory>
#include <mutex>
#include <print>
#include <queue>

template<typename T>
class threadsafe_queue {
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue() = default; //ORIG threadsafe_queue() {}

	threadsafe_queue(threadsafe_queue const& other) {
		std::scoped_lock lk(other.mut); //ORIG std::lock_guard<std::mutex> lk(other.mut);
		data_queue = other.data_queue;
	}

	void push(T new_value, int id = 0) { //ORIG void push(T new_value) {
		std::scoped_lock lk(mut); //ORIG std::lock_guard<std::mutex> lk(mut);
		std::print("Thread {}: Preparing chunk {}\n", std::this_thread::get_id(), id); //MINE
		data_queue.push(new_value);
		data_cond.notify_one();
	}

	void wait_and_pop(T& value) {
		std::unique_lock lk(mut); //ORIG std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] { return !data_queue.empty(); });
		value = data_queue.front();
		data_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop() {
		std::unique_lock lk(mut); //ORIG std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] { return !data_queue.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;
	}

	bool try_pop(T& value) {
		std::scoped_lock lk(mut); //ORIG std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty)
			return false;
		value = data_queue.front();
		data_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop() {
		std::scoped_lock lk(mut); //ORIG std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;
	}

	bool empty() const {
		std::scoped_lock lk(mut); //ORIG std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}
};
