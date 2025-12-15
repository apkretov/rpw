#ifdef MINE

#include <future>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() { // Broken packaged_task
	print_file_line();

	future<void>* f_ptr;
	{
		packaged_task<void()> task([] {});
		future<void> f = task.get_future();
		f_ptr = &f;
	} // Destroy without invoking task

	try {
		f_ptr->get();
	}
	catch (const future_error& e) {
		cerr << "Uninvoked task: " << e.what() << '\n';
	}
}
#endif //MINE
