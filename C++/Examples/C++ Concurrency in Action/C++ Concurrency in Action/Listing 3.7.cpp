#if 1

#include <mutex>
#include "../../stdafx.h"
#include "Listing 3.8.h"
using namespace std;

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);
hierarchical_mutex other_mutex(6000);

int do_low_level_stuff();

int low_level_func() {
	std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
	return do_low_level_stuff();
}

void high_level_stuff(int some_param);

void high_level_func() {
	std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
	high_level_stuff(low_level_func());
}

void thread_a() {
	try {
		high_level_func();
	}
	catch (const std::logic_error& e) { //MINE
		std::cerr << "Thread A exception: " << e.what() << '\n';
	}
}

void do_other_stuff();

void other_stuff() {
	high_level_func();
	do_other_stuff();
}

void thread_b() {
	try {
		std::lock_guard<hierarchical_mutex> lk(other_mutex);
		other_stuff();
	}
	catch (const std::logic_error& e) { //MINE
		std::cerr << "Thread B exception: " << e.what() << '\n';
	}
}

#pragma region MINE
int do_low_level_stuff() {
	cout << "Low level work done.\n";
	return 42;
}

void high_level_stuff(int some_param) { cout << "High level work with param: " << some_param << "\n"; }

void do_other_stuff() { cout << "Doing other stuff.\n"; }

int main() {
	print_file_line();

	thread t1(thread_a);
	thread t2(thread_b);
	t1.join();
	t2.join();

	return 0;
}
#pragma endregion //MINE
#endif