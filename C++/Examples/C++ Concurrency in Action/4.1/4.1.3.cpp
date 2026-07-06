#ifndef MINE // Recommended Approach (With Predicate) Always re-checks condition after any wakeup, handles spurious wakeups safely.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker() {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [] { return ready; });  // Waits until signaled AND ready==true
	std::cout << "Worker: Data ready!" << std::endl;
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
