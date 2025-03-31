#include "../../stdafx.h"
#include "ChocolateBoiler.h"
#include <thread>
#include <vector>

void operateBoiler() {
    auto boiler = ChocolateBoiler::getInstance();
    boiler->fill();
    boiler->boil();
    boiler->drain();
}

int main() {
    print_file_line();

    vector<thread> threads;
    for (int i = 0; i < 2; ++i)
        threads.emplace_back(operateBoiler);

    for (auto& thread : threads)
        thread.join();

    return 0;
}