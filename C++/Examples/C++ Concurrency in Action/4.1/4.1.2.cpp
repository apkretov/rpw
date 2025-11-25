#ifndef MINE

#include <iostream>
#include <thread>
#include "listing_4.5.h"
#include "../../stdafx.h"
using namespace std;

struct data_chunk { int id; };

static int prepared_chunks_count = 0;
constexpr int total_chunks_to_produce = 5;

bool more_data_to_prepare() { return prepared_chunks_count < total_chunks_to_produce; }

data_chunk prepare_data() { return data_chunk{prepared_chunks_count++}; }

void process(data_chunk& data) { cout << "Processing chunk " << data.id << endl; }

bool is_last_chunk(data_chunk& data) { return data.id == 4; } // last chunk has id 4

threadsafe_queue<data_chunk> q;

void data_preparation_thread() {
	while (more_data_to_prepare()) {
		const data_chunk data = prepare_data();
		q.push(data);
	}
}

void data_processing_thread() {
	for (int i = 0; i < total_chunks_to_produce; ++i) {
		data_chunk data;
		q.wait_and_pop(data);
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
