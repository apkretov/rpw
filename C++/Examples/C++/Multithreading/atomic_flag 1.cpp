#include "stdafx.h" // atomic_flag as a spinning lock //atomic_flag::test_and_set @ http://www.cplusplus.com/reference/atomic/atomic_flag/test_and_set/
#include <iostream>       // cout
#include <atomic>         // atomic_flag
#include <thread>         // thread
#include <vector>         // vector
#include <sstream>        // stringstream
using namespace std;

atomic_flag lock_stream = ATOMIC_FLAG_INIT;
stringstream stream;

void append_number(int x) {
  while (lock_stream.test_and_set()) {}
  stream << "thread #" << x << '\n';
  lock_stream.clear();
}

int main () {
  vector<thread> threads;
  for (int i = 1; i <= 10; ++i) threads.push_back(thread(append_number, i));
  for (auto& th : threads) th.join();

  cout << stream.str();
  return 0;
}