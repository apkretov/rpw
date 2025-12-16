#ifdef MINE

#include <future>
#include <iostream>
#include <thread>
#include <vector>
#include "../../stdafx.h"
using namespace std;

int main() { // std::shared_future for multiple threads
	print_file_line();

	promise<int> p;
	shared_future<int> sf = p.get_future().share();

	vector<jthread> threads;
	for (int i = 0; i < 3; ++i) {
		threads.emplace_back([sf, i] {
			try {
				int result = sf.get();  // All threads can call get()
				cout << "Thread " << i << " got: " << result << '\n';
			}
			catch (const exception& e) {
				cerr << "Thread " << i << " exception: " << e.what() << '\n';
			}
		});
	}

	p.set_value(42);  // All waiting threads unblocked
}
#endif //MINE
