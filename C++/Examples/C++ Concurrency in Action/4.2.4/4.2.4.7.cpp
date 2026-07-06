#ifdef MINE

#include <future>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() { // Broken packaged_task
	print_file_line();

	future<void> f;
	{
		packaged_task<void()> task([] {});
		f = task.get_future();
	} // Destroy without invoking task

	try {
		f.get();
	}
	catch (const future_error& e) {
		cerr << "Uninvoked task: " << e.what() << '\n';
	}
}
#endif //MINE
