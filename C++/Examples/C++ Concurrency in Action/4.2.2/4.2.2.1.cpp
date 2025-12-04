#ifdef MINE // std::packaged_task associates a future with a function or callable. When the packaged_task is called, it executes the function and sets the future with the function's return value. This mechanism is useful for thread pools or task schedulers that manage tasks by handling packaged_task instances instead of individual functions.

#include <future> 
#include <iostream>
#include <thread>   
#include "../../stdafx.h"
using namespace std;

int add(int a, int b) { return a + b; }

int main() {
	print_file_line();

	packaged_task<int(int, int)> task(add); // Step 1: Associate a packaged_task with a function (add)
	future<int> resultFuture = task.get_future(); // Retrieve the future associated with this packaged_task

	thread t(move(task), 3, 4); // Step 2 and 3: Run the packaged_task, which calls the function and sets the future value
	t.join(); // Wait for thread to finish

	int result = resultFuture.get(); // Step 3 continued: Get the value from the future (set by packaged_task)
	cout << "Addition result: " << result << '\n';

	// Step 4: This mechanism can be used in thread pools or task schedulers, here we just use a single thread for demonstration.
}
#endif // MINE
