#pragma once

#include <chrono>
#include <deque>
#include <mutex>
#include <future>
#include <print>
#include <thread>
#include <utility>

std::mutex m;
std::deque<std::packaged_task<void()>> tasks;
bool shutdown_gui = false; //MINE

bool gui_shutdown_message_received() {
#pragma region MINE
	std::lock_guard lk(m);
	if (shutdown_gui)
		print("Thread {}: GUI thread received a Shutdown message.\n", std::this_thread::get_id());
	return shutdown_gui;
#pragma endregion
}

void get_and_process_gui_message() {
#pragma region MINE
	print("Thread {}: GUI thread processing its own messages...\n", std::this_thread::get_id());
	std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate GUI message processing
#pragma endregion
}

#pragma region MINE
// What is the difference between steps 3 and 6? To me, executing a task seems like processing messages. It feels like I’m mixing up different concepts.
// In step 3, the GUI thread is processing its own messages, things like user input, clicks or window movements. Step 6 is actually executing tasks that were posted by another thread, like updating a button's text or redrawing the window. So, three is processing internal messages, and six is performing external tasks requested by other threads.
#pragma endregion //MINE
void gui_thread() {  // ❶
	while (!gui_shutdown_message_received()) {  // ❷
		get_and_process_gui_message();  // ❸
		std::packaged_task<void()> task;
		{
			std::lock_guard<std::mutex> lk(m);
			if (tasks.empty())  // ❹
				continue;
			task = std::move(tasks.front());  // ❺
			tasks.pop_front();
		}
		task();  // ❻
	}
}

//OFF std::thread gui_bg_thread(gui_thread); //MINE: Moved to the main cpp-file.

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f) {
	std::packaged_task<void()> task(f);  // ❼
	std::future<void> res = task.get_future();  // ❽
	std::lock_guard<std::mutex> lk(m);
#ifndef ORIG
	tasks.push_back(std::move(task));  // ❾  
#else // MINE
	task(); // Execute the task immediately for demonstration purposes in the main thread.
#endif // MINE
	return res;
}
