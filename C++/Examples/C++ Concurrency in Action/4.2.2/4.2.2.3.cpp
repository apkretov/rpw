#ifndef MINE

#include <chrono>
#include <mutex>
#include <print>
#include <thread>
#include "../../stdafx.h"
#include "listing_4.9.h"
using namespace std;

const jthread gui_bg_thread(gui_thread);

int main() {
	print_file_line();

	auto fut1 = post_task_for_gui_thread([] { print("Thread {}: GUI Task 1: Updating button text.\n", this_thread::get_id()); }); // Post a few tasks
	print("Thread {}: Posted Task 1 to GUI thread.\n", this_thread::get_id());
	auto fut2 = post_task_for_gui_thread([] { print("Thread {}: GUI Task 2: Repainting window.\n", this_thread::get_id()); });
	print("Thread {}: Posted Task 2 to GUI thread.\n", this_thread::get_id());
	auto fut3 = post_task_for_gui_thread([] { print("Thread {}: GUI Task 3: Updating status bar.\n", this_thread::get_id()); });
	print("Thread {}: Posted Task 3 to GUI thread.\n\n", this_thread::get_id());

	fut1.wait(); // Wait for tasks to complete
	fut2.wait();
	fut3.wait();
	print("Thread {}: All GUI tasks completed.\n\n", this_thread::get_id());

	this_thread::sleep_for(chrono::milliseconds(100)); // Let GUI thread run a bit more
	{
		lock_guard lk(m);
		shutdown_gui = true; // Shut down GUI
	}

	print("Thread {}: Returning from main...\n", this_thread::get_id());

	return 0;
}
#endif // MINE
