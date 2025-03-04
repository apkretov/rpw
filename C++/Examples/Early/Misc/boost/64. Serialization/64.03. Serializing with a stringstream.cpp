#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
using namespace std;
using namespace boost::archive;

stringstream ss;

void save() {
  text_oarchive oa{ss};
  int i = 1;
  oa << i;
}

void load() {
  text_iarchive ia{ss};
  int i = 0;
  ia >> i;
  cout << i << '\n';
}

int main() {
  save();
  load();
}