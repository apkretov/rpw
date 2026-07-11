#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
#include <thread>
#include <string>

struct MsgA {
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > text;
};

struct MsgB {
	int value;
};

struct close_queue {};

struct message_base {
	inline virtual constexpr ~message_base() noexcept = default;
};

template<typename Msg>
struct wrapped_message : public message_base {
	Msg contents;
	inline explicit wrapped_message(const Msg& c) : contents(c) {}
};

#ifdef INSIGHTS_USE_TEMPLATE
template<>
struct wrapped_message<MsgA> : public message_base {
	MsgA contents;
	inline explicit wrapped_message(const MsgA& c) : message_base(), contents{MsgA(c)} {}
};

template<>
struct wrapped_message<MsgB> : public message_base {
	MsgB contents;
	inline explicit wrapped_message(const MsgB& c) : message_base(), contents{MsgB(c)} {}
};

template<>
struct wrapped_message<close_queue> : public message_base {
	close_queue contents;
	inline explicit wrapped_message(const close_queue& c) : message_base(), contents{close_queue(c)} {}
};
#endif

class message_queue {
	std::mutex m;
	std::condition_variable cv;
	std::queue<std::shared_ptr<message_base>, std::deque<std::shared_ptr<message_base>, std::allocator<std::shared_ptr<message_base> > > > q;

public:
	template<typename T>
	inline void push(const T& msg) {
		std::lock_guard<std::mutex> lk = std::lock_guard<std::mutex>(this->m);
		push(std::make_shared<wrapped_message<T> >(msg));
		this->cv.notify_all();
	}

	#ifdef INSIGHTS_USE_TEMPLATE
	template<>
	inline void push<MsgA>(const MsgA& msg) {
		std::lock_guard<std::mutex> lk = std::lock_guard<std::mutex>(this->m);
		this->q.push(std::shared_ptr<message_base>(std::make_shared<wrapped_message<MsgA> >(msg)));
		this->cv.notify_all();
	}

	template<>
	inline void push<MsgB>(const MsgB& msg) {
		std::lock_guard<std::mutex> lk = std::lock_guard<std::mutex>(this->m);
		this->q.push(std::shared_ptr<message_base>(std::make_shared<wrapped_message<MsgB> >(msg)));
		this->cv.notify_all();
	}

	template<>
	inline void push<close_queue>(const close_queue& msg) {
		std::lock_guard<std::mutex> lk = std::lock_guard<std::mutex>(this->m);
		this->q.push(std::shared_ptr<message_base>(std::make_shared<wrapped_message<close_queue> >(msg)));
		this->cv.notify_all();
	}
	#endif

	inline std::shared_ptr<message_base> wait_and_pop() {
		std::unique_lock<std::mutex> lk = std::unique_lock<std::mutex>(this->m);

		class __lambda_43_21 {
		public:
			inline bool operator()() const {
				return !__this->q.empty();
			}
			message_queue* __this;
		};

		this->cv.wait<__lambda_43_21>(lk, __lambda_43_21{this});
		std::shared_ptr<message_base> res = std::shared_ptr<message_base>(this->q.front());
		this->q.pop();
		return res;
	}
};

class dispatcher;

template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
	message_queue* q;
	PreviousDispatcher* prev;
	Func f;
	bool chained;
public:
	template<typename D, typename M, typename F>
	friend class TemplateDispatcher;
private:
	inline bool dispatch(const std::shared_ptr<message_base>& msg) {
		auto wrapper = dynamic_cast<wrapped_message<Msg> *>(msg.get());
		if (wrapper) {
			this->f(wrapper->contents);
			return true;
		}
		return this->prev->dispatch(msg);
	}

	inline void wait_and_dispatch() {
		for (; ; ) {
			std::shared_ptr<message_base> msg = this->q->wait_and_pop();
			if (this->dispatch(msg)) {
				break;
			}
		}
	}

public:
	inline TemplateDispatcher(TemplateDispatcher<PreviousDispatcher, Msg, Func>&& other)
		: q{other.q}
		, prev(other.prev)
		, f(std::move(other.f))
		, chained{other.chained} {
		other.chained = true;
	}

	inline TemplateDispatcher(message_queue* q_, PreviousDispatcher* prev_, Func&& f_)
		: q{q_}
		, prev(prev_)
		, f(std::forward<Func>(f_)) {}

	template<typename OtherMsg, typename OtherFunc>
	inline TemplateDispatcher<TemplateDispatcher<PreviousDispatcher, Msg, Func>, OtherMsg, OtherFunc> handle(OtherFunc&& of) {
		this->chained = true;
		return TemplateDispatcher<TemplateDispatcher<PreviousDispatcher, Msg, Func>, OtherMsg, OtherFunc>(this->q, this, std::forward<OtherFunc>(of));
	}
	inline ~TemplateDispatcher() noexcept(false) {
		if (!this->chained) {
			this->wait_and_dispatch();
		}
	}
};

class __lambda_133_31 {
public:
	inline void operator()(const MsgA& msg) const {
		std::cout << "[Worker] Handled MsgA: " << msg.text << std::endl;
	}
	using retType_133_31 = void (*)(const MsgA&);
	inline constexpr operator retType_133_31 () const noexcept { return __invoke; };
private:
	static inline void __invoke(const MsgA& msg) { __lambda_133_31{}.operator()(msg); }
};

class __lambda_136_31 {
public:
	inline void operator()(const MsgB& msg) const {
		std::cout << "[Worker] Handled MsgB: " << msg.value << std::endl;
	}
	using retType_136_31 = void (*)(const MsgB&);
	inline constexpr operator retType_136_31 () const noexcept { return __invoke; };
private:
	static inline void __invoke(const MsgB& msg) { __lambda_136_31{}.operator()(msg); }
};

#ifdef INSIGHTS_USE_TEMPLATE
template<>
class TemplateDispatcher<dispatcher, MsgA, __lambda_133_31> {
	message_queue* q;
	dispatcher* prev;
	__lambda_133_31 f;
	bool chained;
public:
	template<typename D, typename M, typename F>
	friend class TemplateDispatcher;
private:
	inline bool dispatch(const std::shared_ptr<message_base>& msg) {
		wrapped_message<MsgA>* wrapper = dynamic_cast<wrapped_message<MsgA> *>(msg.get());
		if (wrapper) {
			this->f.operator()(wrapper->contents);
			return true;
		}
		return this->prev->dispatch(msg);
	}

	inline void wait_and_dispatch() {
		for (; ; ) {
			std::shared_ptr<message_base> msg = this->q->wait_and_pop();
			if (this->dispatch(msg)) {
				break;
			}
		}
	}

public:
	inline TemplateDispatcher(message_queue* q_, dispatcher* prev_, __lambda_133_31&& f_)
		: q{q_}, prev{prev_}, f{std::move(f_)}, chained{false} {}

	template<typename OtherMsg, typename OtherFunc>
	inline TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>, OtherMsg, OtherFunc> handle(OtherFunc&& of);

	template<>
	inline TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>, MsgB, __lambda_136_31> handle<MsgB, __lambda_136_31>(__lambda_136_31&& of) {
		this->chained = true;
		return TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>, MsgB, __lambda_136_31>(this->q, this, std::forward<__lambda_136_31>(of));
	}

	inline ~TemplateDispatcher() noexcept(false) {
		if (!this->chained) {
			this->wait_and_dispatch();
		}
	}
};

template<>
class TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>, MsgB, __lambda_136_31> {
	message_queue* q;
	TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>* prev;
	__lambda_136_31 f;
	bool chained;
public:
	template<typename D, typename M, typename F>
	friend class TemplateDispatcher;
private:
	inline bool dispatch(const std::shared_ptr<message_base>& msg) {
		wrapped_message<MsgB>* wrapper = dynamic_cast<wrapped_message<MsgB> *>(msg.get());
		if (wrapper) {
			this->f.operator()(wrapper->contents);
			return true;
		}
		return this->prev->dispatch(msg);
	}

	inline void wait_and_dispatch() {
		for (; ; ) {
			std::shared_ptr<message_base> msg = this->q->wait_and_pop();
			if (this->dispatch(msg)) {
				break;
			}
		}
	}

public:
	inline TemplateDispatcher(message_queue* q_, TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>* prev_, __lambda_136_31&& f_)
		: q{q_}, prev{prev_}, f{std::move(f_)}, chained{false} {}

	template<typename OtherMsg, typename OtherFunc>
	inline TemplateDispatcher<TemplateDispatcher<TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>, MsgB, __lambda_136_31>, OtherMsg, OtherFunc> handle(OtherFunc&& of);

	inline ~TemplateDispatcher() noexcept(false) {
		if (!this->chained) {
			this->wait_and_dispatch();
		}
	}
};
#endif

class dispatcher {
	message_queue* q;
	bool chained;

public:
	inline dispatcher(dispatcher&& other)
		: q{other.q}, chained{other.chained} {
		other.chained = true;
	}

	inline explicit dispatcher(message_queue* q_)
		: q{q_}, chained{false} {}

	template<typename Msg, typename Func>
	inline TemplateDispatcher<dispatcher, Msg, Func> handle(Func&& f) {
		this->chained = true;
		return TemplateDispatcher<dispatcher, Msg, Func>(this->q, this, std::forward<Func>(f));
	}

	#ifdef INSIGHTS_USE_TEMPLATE
	template<>
	inline TemplateDispatcher<dispatcher, MsgA, __lambda_133_31> handle<MsgA, __lambda_133_31>(__lambda_133_31&& f) {
		this->chained = true;
		return TemplateDispatcher<dispatcher, MsgA, __lambda_133_31>(this->q, this, std::forward<__lambda_133_31>(f));
	}
	#endif

	inline bool dispatch(const std::shared_ptr<message_base>& msg) {
		if (dynamic_cast<wrapped_message<close_queue> *>(msg.get())) {
			throw close_queue();
		}
		return false;
	}

	inline ~dispatcher() noexcept(false) {
		if (!this->chained) {
			for (; ; ) {
				if (this->dispatch(this->q->wait_and_pop())) {
					break;
				}
			}
		}
	}
};

void worker_thread(message_queue* q) {
	try {
		for (; ; ) {
			dispatcher(q).handle<MsgA, __lambda_133_31>(__lambda_133_31{}).handle<MsgB, __lambda_136_31>(__lambda_136_31{});
		}
	}
	catch (const close_queue&) {
		std::cout << "[Worker] Received close_queue. Shutting down cleanly." << std::endl;
	}
}

int main() {
	message_queue q;
	std::thread t(worker_thread, &q);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push<MsgA>(MsgA{"Hello Chain!"});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push<MsgB>(MsgB{42});

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	q.push<close_queue>(close_queue{});

	t.join();
	return 0;
}