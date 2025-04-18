#if 0

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include "../../stdafx.h"
using namespace boost::asio;

int main() {
#pragma region Aliases
	using boost::system::error_code;
	using std::chrono::seconds;
	using std::cout;
#pragma endregion //Aliases
	print_file_line();

	cout << "Starting the timers...\n"; //MINE

	io_service ioservice;
	steady_timer timer1{ioservice, seconds{3}};
	timer1.async_wait([](const error_code &ec) { std::cout << "3 sec\n"; });
	steady_timer timer2{ioservice, seconds{4}};
	timer2.async_wait([](const error_code &ec) { std::cout << "4 sec\n"; });
	cout << "111\n"; //MINE
	ioservice.run();
	cout << "222\n"; //MINE

	return 0;
}
#endif //0
