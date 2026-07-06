#ifndef MINE

#include <print>
#include <thread>
#include "Listing 4.5.h"
#include "../../stdafx.h"
using namespace std;

struct data_chunk { int id; };

static int prepared_chunks_count = 0;
constexpr int total_chunks_to_produce = 5;

bool more_data_to_prepare() { return prepared_chunks_count < total_chunks_to_produce; }

data_chunk prepare_data() { return data_chunk{prepared_chunks_count++}; }

void process(data_chunk& data) { print("Thread {}: Processing chunk {}\n", this_thread::get_id(), data.id); }

bool is_last_chunk(data_chunk& data) { return data.id == 4; } // last chunk has id 4

threadsafe_queue<data_chunk> q;

void data_preparation_thread() {
	while (more_data_to_prepare()) {
		const data_chunk data = prepare_data();
		q.push(data, data.id);
		this_thread::sleep_for(chrono::milliseconds(100)); //MINE
	}
	print("Thread {}: No more data to prepare\n", this_thread::get_id()); //MINE
}

void data_processing_thread() {
	print("Thread {}: Waiting for data...\n", this_thread::get_id()); //MINE
	for (int i = 0; i < total_chunks_to_produce; ++i) {
		data_chunk data;
		q.wait_and_pop(data);
		process(data);
	}
}

int main() {
	print_file_line();

	jthread t1(data_preparation_thread);
	this_thread::sleep_for(chrono::milliseconds(300));
	jthread t2(data_processing_thread);

	return 0;
}
#endif //MINE
