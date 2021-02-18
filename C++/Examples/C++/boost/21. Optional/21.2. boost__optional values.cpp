#include "stdafx.h" //Chapter 21. Boost.Optional @ https://theboostcpplibraries.com/boost.optional
#include <boost/optional.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using boost::optional;
using namespace std;

optional<int> get_even_random_number() {
  int i = rand();
  return (i % 2 == 0) ? i : optional<int>{};
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  optional<int> i = get_even_random_number();
  if (i) cout << sqrt(static_cast<float>(*i)) << '\n';
}