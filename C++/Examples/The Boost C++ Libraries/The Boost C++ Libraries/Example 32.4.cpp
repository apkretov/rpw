#if 1

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include "../../stdafx.h"

int main() {
#pragma region Aliases
    using io_service =    boost::asio::io_service;
    using steady_timer =  boost::asio::steady_timer;
    using error_code =    boost::system::error_code;
    using seconds =       std::chrono::seconds;
    using                 std::cout;
    using thread =        std::thread;
#pragma endregion //Aliases
    print_file_line();

	cout << "Starting the timers...\n"; //MINE

	io_service ioservice1;
    io_service ioservice2;
    steady_timer timer1{ioservice1, seconds{3}};
    timer1.async_wait([](const error_code& ec) { cout << "1: 3 sec\n"; });
    steady_timer timer2{ioservice2, seconds{3}};
    timer2.async_wait([](const error_code& ec) { cout << "2: 3 sec\n"; });
    thread thread1{[&ioservice1]() { ioservice1.run(); }};
    thread thread2{[&ioservice2]() { ioservice2.run(); }};
    thread1.join();
    thread2.join();

    return 0;
}
#endif //1