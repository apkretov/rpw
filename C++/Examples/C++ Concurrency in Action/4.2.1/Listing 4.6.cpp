#if	0

#include <chrono>
#include <future>
#include <print>
#include "../../stdafx.h"

int find_the_answer_to_ltuae() { 
	std::print("Thread {}: Finding the answer...\n", std::this_thread::get_id()); //MINE
	std::this_thread::sleep_for(std::chrono::seconds(2)); //MINE
	return 42; 
}

void do_other_stuff() {
	std::print("Thread {}: Doing other stuff...\n", std::this_thread::get_id()); //MINE
}

int main() {
	print_file_line();

	std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
	do_other_stuff();
	std::print("Thread {}: The answer is {}\n", std::this_thread::get_id(), the_answer.get()); //ORIG std::cout << "The answer is " << the_answer.get() << std::endl;
}
#endif // 1
