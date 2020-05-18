#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/array.hpp>
#include <array>
#include <iostream>
#include <sstream>
using namespace boost::archive;
using namespace std;

stringstream ss;

void save() {
  text_oarchive oa{ss};
  array<int, 3> a{{0, 1, 2}};
  oa << boost::serialization::make_array(a.data(), a.size());
}

void load() {
  text_iarchive ia{ss};
  array<int, 3> a;
  ia >> boost::serialization::make_array(a.data(), a.size());
  cout << a[0] << ", " << a[1] << ", " << a[2] << '\n';
}

int main() {
  save();
  load();
}