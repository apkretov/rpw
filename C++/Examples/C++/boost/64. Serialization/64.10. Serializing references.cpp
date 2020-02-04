#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
using namespace boost::archive;
using namespace std;

stringstream ss;

class animal {
  int legs_;
  friend class boost::serialization::access;
  template <typename Archive> void serialize(Archive &ar, const unsigned int version) { ar & legs_; }
public:
  animal() = default;
  animal(int legs) : legs_{legs} {}
  int legs() const { return legs_; }
};

void save() {
  text_oarchive oa{ss};
  animal a{4};
  animal& r = a;
  oa << r;
}

void load() {
  text_iarchive ia{ss};
  animal a;
  animal& r = a;
  ia >> r;
  cout << r.legs() << '\n';
}

int main() {
  save();
  load();
}