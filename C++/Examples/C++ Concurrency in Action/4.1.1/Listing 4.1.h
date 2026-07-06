#include <mutex>
#include <print>
#include <queue>
using namespace std;

#pragma region MINE
struct data_chunk {
	int id;
};

static int prepared_chunks_count = 0;
constexpr int total_chunks_to_produce = 5;

bool more_data_to_prepare() { return prepared_chunks_count < total_chunks_to_produce; }

data_chunk prepare_data() { return data_chunk{prepared_chunks_count++}; }

void process(data_chunk& data) { print("Thread {}: Processing chunk {}\n", this_thread::get_id(), data.id); }

bool is_last_chunk(data_chunk& data) { return data.id == 4; } // last chunk has id 4

mutex mut;
queue<data_chunk> data_queue;
condition_variable data_cond;
bool producer_done = false;
#pragma endregion //MINE

void data_preparation_thread() {
	while (more_data_to_prepare()) {
		data_chunk const data = prepare_data();
		{
			std::scoped_lock lk(mut); //ORIG std::lock_guard<std::mutex> lk(mut);
			print("Thread {}: Preparing chunk {}\n", this_thread::get_id(), data.id); //MINE
			data_queue.push(data);
		}
		data_cond.notify_one();
		this_thread::sleep_for(chrono::milliseconds(100)); //MINE
	}
	print("Thread {}: No more data to prepare\n", this_thread::get_id()); //MINE
}
void data_processing_thread() {
	print("Thread {}: Waiting for data...\n", this_thread::get_id()); //MINE
	while (true) {
		std::unique_lock lk(mut); //ORIG std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [] { return !data_queue.empty(); });
		data_chunk data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		process(data);
		if (is_last_chunk(data))
			break;
	}
}
