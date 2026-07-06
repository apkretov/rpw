#ifdef MINE // Non-Recommended Approach (No Predicate) Wakes up on spurious wakeups, may process data prematurely.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock);  // Wakes on signal OR spurious wakeup, no check!
	std::cout << "Worker: Data ready? " << (ready ? "Yes" : "No!") << std::endl;
}

int main() {
	std::thread t(worker);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	{
		std::lock_guard<std::mutex> lock(mtx);
		ready = true;
		cv.notify_one();
	}
	t.join();
	return 0;
}
#endif //MINE
