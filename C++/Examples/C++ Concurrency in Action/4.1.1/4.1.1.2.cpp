#if 0

#include <mutex>
#include <print>
#include <thread>
#include "Listing 4.1.h"
#include "../../stdafx.h"
using namespace std;

template<typename Predicate>
void minimal_wait(unique_lock<mutex>& lk, Predicate pred) {
	while (!pred()) {
		lk.unlock();
		lk.lock();
	}
}

#pragma region MINE
void data_processing_thread_with_minimal_wait() {
	print("Thread {}: Waiting for data...\n", this_thread::get_id());
	while (true) {
		std::unique_lock lk(mut);
		minimal_wait(lk, [] { return !data_queue.empty(); });
		data_chunk data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		process(data);
		if (is_last_chunk(data))
			break;
	}
}

int main() {
	print_file_line();

	jthread t1(data_preparation_thread);
	this_thread::sleep_for(chrono::milliseconds(300));
	jthread t2(data_processing_thread_with_minimal_wait);

	return 0;
}
#pragma endregion //MINE
#endif //1
