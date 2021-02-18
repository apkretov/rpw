#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace boost::archive;

void save() {
  ofstream file{"archive.txt"};
  text_oarchive oa{file};
  int i = 1;
  oa << i;
}

void load() {
  ifstream file{"archive.txt"};
  text_iarchive ia{file};
  int i = 0;
  ia >> i;
  cout << i << '\n';
}

int main() {
  save();
  load();
}