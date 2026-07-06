#if 0

#include <thread>
#include "../../stdafx.h"

void some_function() {}
void some_other_function() {}

int main() {
	print_file_line();

	std::thread t1(some_function);        // start thread t1
	std::thread t2 = std::move(t1);       // move ownership from t1 to t2 (t1 no longer owns a thread)
	t1 = std::thread(some_other_function); // start new thread for t1
	std::thread t3;
	t3 = std::move(t2);                   // move ownership from t2 to t3

	//TEST! t1 = std::move(t3); //																															unsafe! t1 already owns a thread, program terminates

	t1.join(); //MINE 
	t3.join();
}
#endif //1