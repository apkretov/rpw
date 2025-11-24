#ifdef MINE

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include "../../stdafx.h"
using namespace std;

struct data_chunk { int id; };

static int prepared_chunks_count = 0;
constexpr int total_chunks_to_produce = 5;

bool more_data_to_prepare() { return prepared_chunks_count < total_chunks_to_produce; }

data_chunk prepare_data() { return data_chunk{prepared_chunks_count++}; }

void process(data_chunk& data) { cout << "Processing chunk " << data.id << endl; }

bool is_last_chunk(data_chunk& data) { return data.id == 4; } // last chunk has id 4

mutex mut;
queue<data_chunk> data_queue;
condition_variable data_cond;
bool producer_done = false;

void data_preparation_thread() {
	while (more_data_to_prepare()) {
		const data_chunk data = prepare_data();
		{
			lock_guard<mutex> lk(mut);
			data_queue.push(data);
		}
		data_cond.notify_one();
	}
	{
		lock_guard<mutex> lk(mut);
		producer_done = true;
	}
	data_cond.notify_all();
}

void data_processing_thread() {
	while (true) {
		unique_lock<mutex> lk(mut);
		data_cond.wait(lk, [] { return producer_done || !data_queue.empty(); });
		if (producer_done && data_queue.empty()) 
			break;
		data_chunk data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		process(data);
	}
}

int main() {
	print_file_line();

	thread t1(data_preparation_thread);
	thread t2(data_processing_thread);

	t1.join();
	t2.join();
}
#endif //MINE
