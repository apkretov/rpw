#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
using namespace boost::archive;
using namespace std;

stringstream ss;

class animal {
  friend class boost::serialization::access;
  int legs_;
  template <typename Archive> void serialize(Archive& ar, const unsigned int version) { ar & legs_; }
public:
  animal() = default;
  animal(int legs) : legs_{legs} {}
  int legs() const { return legs_; }
};

void save() {
  text_oarchive oa{ss};
  animal a{4};
  oa << a;
}

void load() {
  text_iarchive ia{ss};
  animal a;
  ia >> a;
  cout << a.legs() << '\n';
}

int main() {
  save();
  load();
}