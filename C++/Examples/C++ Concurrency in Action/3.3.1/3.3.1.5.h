#pragma once

#pragma region MINE

#include <atomic>
#include <mutex>
#include <thread>
using namespace std;

class SimpleOnceFlag {
	atomic<int> state{0}; // 0 = not called, 1 = locked/calling, 2 = done
	mutex mtx;
public:
	template <typename Callable>
	void call_once(Callable&& func) {
		int expected = 0;
		if (state.compare_exchange_strong(expected, 1, memory_order_acquire)) { // Try to transition from 'not called' (0) to 'locked' (1)
			try { // This thread is responsible for calling func
				func();
				state.store(2, memory_order_release); // Done
			}
			catch (...) {
				state.store(0, memory_order_release); // Reset on failure
				throw;
			}
		} else { // Another thread is calling or has called func
			unique_lock<mutex> lock(mtx); // If state was 1 (locked), wait for it to become 2 (done)
			while (state.load(memory_order_acquire) != 2) {
				lock.unlock(); // Spin or wait - std::call_once typically uses blocking wait, here we simulate by locking mutex
				this_thread::yield();
				lock.lock();
			}
		}
	}
};
#pragma endregion //MINE
