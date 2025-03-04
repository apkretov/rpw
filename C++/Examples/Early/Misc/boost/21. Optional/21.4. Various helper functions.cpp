#include "stdafx.h" //Chapter 21. Boost.Optional @ https://theboostcpplibraries.com/boost.optional
#include <boost/optional.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace boost;
using namespace std;

optional<int> get_even_random_number() {
  int i = rand();
  return make_optional(i % 2 == 0, i);
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  //ORIG optional<int> i = get_even_random_number();
  auto i = get_even_random_number(); //TEST
  double d = get_optional_value_or(i, 0);
  cout << sqrt(d) << '\n';
}