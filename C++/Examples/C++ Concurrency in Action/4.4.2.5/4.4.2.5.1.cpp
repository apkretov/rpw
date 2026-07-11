#if 0
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <thread>
#include <string>

// ==========================================
// 1. Messages Types
// ==========================================
struct MsgA { std::string text; };
struct MsgB { int value; };
struct close_queue {};

// ==========================================
// 2. Core Infrastructure (Queue & Wrappers)
// ==========================================
struct message_base {
	virtual ~message_base() = default;
};

template<typename Msg>
struct wrapped_message : message_base {
	Msg contents;
	explicit wrapped_message(Msg const& c) : contents(c) {}
};

class message_queue {
	std::mutex m;
	std::condition_variable cv;
	std::queue<std::shared_ptr<message_base>> q;
public:
	template<typename T>
	void push(T const& msg) {
		std::lock_guard<std::mutex> lk(m);
		q.push(std::make_shared<wrapped_message<T>>(msg));
		cv.notify_all();
	}

	std::shared_ptr<message_base> wait_and_pop() {
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [&] { return !q.empty(); });
		auto res = q.front(); q.pop();
		return res;
	}
};

// ==========================================
// 3. The Template Chaining Engines
// ==========================================
template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
	message_queue* q;
	PreviousDispatcher* prev;
	Func f;
	bool chained = false;

	template<typename D, typename M, typename F> friend class TemplateDispatcher;

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		// If the message type matches this link, handle it and break the loop
		if (auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) {
			f(wrapper->contents);
			return true;
		}
		// Otherwise, forward it down to the previous link in the chain
		return prev->dispatch(msg);
	}

	void wait_and_dispatch() {
		for (;;) {
			auto msg = q->wait_and_pop();
			if (dispatch(msg)) break; // Stop waiting once a message is successfully handled
		}
	}

public:
	TemplateDispatcher(TemplateDispatcher&& other)
		: q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained) {
		other.chained = true; // Prevents the moved-from temporary from processing messages
	}

	TemplateDispatcher(message_queue* q_, PreviousDispatcher* prev_, Func&& f_)
		: q(q_), prev(prev_), f(std::forward<Func>(f_)) {}

	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) {
		chained = true; // This link is now chained; responsibility moves to the new child
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}

	~TemplateDispatcher() noexcept(false) {
		// The last temporary in the chain (where chained is still false) runs the dispatch loop
		if (!chained) wait_and_dispatch();
	}
};

class dispatcher {
	message_queue* q;
	bool chained = false;
public:
	dispatcher(dispatcher&& other) : q(other.q), chained(other.chained) { other.chained = true; }
	explicit dispatcher(message_queue* q_) : q(q_) {}

	template<typename Msg, typename Func>
	TemplateDispatcher<dispatcher, Msg, Func> handle(Func&& f) {
		chained = true;
		return TemplateDispatcher<dispatcher, Msg, Func>(q, this, std::forward<Func>(f));
	}

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) throw close_queue();
		return false;
	}

	~dispatcher() noexcept(false) {
		if (!chained) {
			for (;;) { if (dispatch(q->wait_and_pop())) break; }
		}
	}
};

// ==========================================
// 4. Execution & Verification
// ==========================================
void worker_thread(message_queue* q) {
	try {
		for (;;) {
			// At the end of this statement, the temporary TemplateDispatcher dtor runs, 
			// blocking and processing exactly one valid incoming message.
			dispatcher(q)
				.handle<MsgA>([](MsgA const& msg) {
				std::cout << "[Worker] Handled MsgA: " << msg.text << std::endl;
				})
				.handle<MsgB>([](MsgB const& msg) {
				std::cout << "[Worker] Handled MsgB: " << msg.value << std::endl;
				});
		}
	}
	catch (close_queue const&) {
		std::cout << "[Worker] Received close_queue. Shutting down cleanly." << std::endl;
	}
}

int main() {
	message_queue q;
	std::thread t(worker_thread, &q);

	// Send diverse messages to demonstrate runtime routing down the template chain
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push(MsgA{"Hello Chain!"});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push(MsgB{42});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push(close_queue{});

	t.join();
	return 0;
}
#endif // 0
