#if 0

#undef SYNCED_BY_OSTREAM
#undef UNSYNCED_BY_OSTREAM
#define SYNCED_BY_CONST

#include <future>
#include <thread>
#include "../../stdafx.h"
using namespace std;

class Data {
	string data_;
public:
	Data(string data) : data_(data) { cout << "Data constructed\n"; }
	~Data() { cout << "Data destructed\n"; }
	const string &Get() const { return data_; } //TEST!
	string &Get() { return data_; }
};

#ifdef SYNCED_BY_OSTREAM
void ShareResource(shared_ptr<Data> data) {
	stringstream ss;
	ss << "Shared resource " << data->Get() 
		<< " in " << this_thread::get_id() 
		<< ", counter = " << data.use_count() << endl; //TEST
	cout << ss.str();
	data->Get().push_back('x');
}

vector<future<void>> spawn() {
	vector<future<void>> tasks;
	auto data = make_shared<Data>("meow");
	for (int i = 0; i < 10; ++i)
		tasks.push_back(async([=]() { ShareResource(data); }));
	return tasks;
}
#endif //SYNCED_BY_OSTREAM

#ifdef UNSYNCED_BY_OSTREAM
void ShareResource(shared_ptr<Data> data) {
	stringstream ss;
	ss << "Shared resource " << data->Get() << " in " << this_thread::get_id() << ", counter = " << data.use_count() << endl;
	data->Get().push_back('x');
}

vector<future<void>> spawn() {
	vector<future<void>> tasks;
	auto data = make_shared<Data>("meow");
	for (int i = 0; i < 1'000; ++i)
		tasks.push_back(async([=]() { ShareResource(data); }));
	return tasks;
}
#endif //UNSYNCED_BY_OSTREAM

#ifdef SYNCED_BY_CONST
void ShareResource(shared_ptr<const Data> data) { //TEST
	stringstream ss;
	ss << "Shared resource " << data->Get() << " in " << this_thread::get_id() << ", counter = " << data.use_count() << endl;
	cout << ss.str();
}

vector<future<void>> spawn() {
	vector<future<void>> tasks;
	auto data = make_shared<const Data>("meow"); //TEST
	for (int i = 0; i < 10; ++i)
		tasks.push_back(async([=]() { ShareResource(data); }));
	return tasks;
}
#endif //SYNCED_BY_CONST

int main() {
	PRINT_FILE_LINE();

	cout << "Spawning tasks...\n";
	auto tasks = spawn();
#ifdef MINE
	for (auto &task : tasks)
		task.get();
#endif //MINE
	cout << "Done spawning.\n";

	return 0;
}
#endif //1
