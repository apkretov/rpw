#if 0

#include <thread>
#include "../../stdafx.h"

class joining_thread {
	std::thread t;
public:
	joining_thread() noexcept = default;

	template<typename Callable, typename ... Args>
	explicit joining_thread(Callable&& func, Args&& ... args) : t(std::forward<Callable>(func), std::forward<Args>(args)...) {}

	explicit joining_thread(std::thread t_) noexcept : t(std::move(t_)) {}
	joining_thread(joining_thread&& other) noexcept : t(std::move(other.t)) {}

	joining_thread& operator=(joining_thread&& other) noexcept {
		if (joinable()) 
			join();
		t = std::move(other.t);
		return *this;
	}

	joining_thread& operator=(std::thread other) noexcept {
		if (joinable()) 
			join();
		t = std::move(other);
		return *this;
	}

	~joining_thread() noexcept { 
		if (joinable()) 
			join(); 
	}

	bool joinable() const noexcept { return t.joinable(); }
	void join() { t.join(); }
	void detach() { t.detach(); }

	std::thread& as_thread() noexcept { return t; }
};

int main() {
	print_file_line();

	//MINE
	joining_thread jt1;
	if (jt1.joinable())
		jt1.join();
	if (jt1.joinable())
		jt1.detach();


	auto jt2(std::move(jt1));
	jt1 = std::move(jt2);

	std::thread t1([] { for (int i = 0; i < 1000; ++i); });
	t1.join();

	std::thread t2;
	if (t2.joinable())
		t2.join();
}
#endif //1