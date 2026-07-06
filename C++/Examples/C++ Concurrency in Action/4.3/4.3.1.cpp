#ifndef MINE

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
int data = 0;

void worker() {
	std::unique_lock<std::mutex> lock(mtx);

	auto result1 = cv.wait_for(lock, std::chrono::milliseconds{200}); // Wait up to 200ms for signal or SPURIOUS wakeup (no predicate)
	std::cout << "wait_for(200ms) result: " << (result1 == std::cv_status::timeout ? "timeout" : "signaled") << std::endl;

	auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds{100}; // Wait until specific time (absolute, e.g., 100ms from now)
	auto result2 = cv.wait_until(lock, deadline);
	std::cout << "wait_until(deadline) result: " << (result2 == std::cv_status::timeout ? "timeout" : "signaled") << std::endl;

	auto result3 = cv.wait_for(lock, std::chrono::milliseconds{150}, [] { return ready; }); // RECOMENDED: With predicate: waits until signaled AND predicate true, or timeout.
	std::cout << "wait_for(150ms, predicate): " << (result3 ? "true (ready)" : "false (timeout)") << std::endl;
	// The first two options require you to manually check the condition after waking, which is error - prone. The predicate version does this for you safely.
}

int main() {
	std::jthread t(worker);

	std::this_thread::sleep_for(std::chrono::milliseconds{50}); // Simulate delay before signaling
	{
		std::scoped_lock lock(mtx);
		data = 42;  // Set data
		// cv.notify_one();  // Uncomment to signal early
	}

	std::this_thread::sleep_for(std::chrono::milliseconds{300});  // Let worker timeout
	{
		std::scoped_lock lock(mtx);
		ready = true;
		cv.notify_one();
	}

	return 0;
}
#endif //MINE
