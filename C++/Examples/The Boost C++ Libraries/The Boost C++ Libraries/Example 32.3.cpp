#if 0

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include "../../stdafx.h"
using namespace boost::asio;

void example_32_3() {
#pragma region Aliases
	using boost::system::error_code;
	using std::chrono::seconds;
	using std::cout;
	using std::thread;
#pragma endregion //Aliases
	cout << "Starting the timers...\n"; //MINE

	io_service ioservice;
	steady_timer timer1{ioservice, seconds{3}};
	timer1.async_wait([](const error_code &ec) { cout << "1: 3 sec\n"; });
	steady_timer timer2{ioservice, seconds{3}};
	timer2.async_wait([](const error_code &ec) { cout << "2: 3 sec\n"; });
	thread thread1{[&ioservice]() { ioservice.run(); }};
	thread thread2{[&ioservice]() { ioservice.run(); }};
	thread1.join();
	thread2.join();
}

void example_32_3_mine() {
#pragma region Aliases
	using boost::system::error_code;
	using std::chrono::seconds;
	using std::cout;
	using std::thread;
#pragma endregion //Aliases
	cout << "Starting the timers...\n"; //MINE

	io_service ioservice;
	steady_timer timer1{ioservice, seconds{3}};
	timer1.async_wait([](const error_code &ec) { cout << "3 sec\n"; });
#ifdef ORIG
	steady_timer timer2{ioservice, seconds{3}};
	timer2.async_wait([](const error_code &ec) { cout << "3 sec\n"; });
#else //MINE
	steady_timer timer2{ioservice, seconds{4}};
	timer2.async_wait([](const error_code &ec) { cout << "4 sec\n"; });
#endif //MINE
	cout << "111\n"; //MINE
	thread thread1{[&ioservice]() { ioservice.run(); }};
	cout << "222\n"; //MINE
	thread thread2{[&ioservice]() { ioservice.run(); }};
	cout << "333\n"; //MINE
	thread1.join();
	cout << "444\n"; //MINE
	thread2.join();
	cout << "555\n"; //MINE
}

void mine() {
#pragma region Aliases
	using boost::system::error_code;
	using std::chrono::seconds;
	using std::cout;
	using std::thread;
#pragma endregion //Aliases

	cout << "Starting the timers...\n";

	io_service ioservice;
	steady_timer timer1{ioservice, seconds{3}};
	timer1.async_wait([](const error_code &ec) { cout << "3 sec\n"; });
	steady_timer timer2{ioservice, seconds{4}};
	timer2.async_wait([](const error_code &ec) { cout << "4 sec\n"; });
	cout << "111\n";
	ioservice.run();
	cout << "222\n";
	ioservice.run();
	cout << "333\n";
}

int main() {
#pragma region Aliases
	using boost::system::error_code;
	using std::chrono::seconds;
	using std::cout;
	using std::thread;
#pragma endregion //Aliases
	print_file_line();

	cout << "Example 32.3:\n";
#ifndef ORIG
	example_32_3();
#else //MINE
	example_32_3_mine();
#endif //MINE
#if 0
	cout << "\nMINE:\n";
	mine();
#endif //0

	return 0;
}
#endif //0
