#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>
using namespace std;

stringstream ss;

class animal {
  int legs_;
  int weight_ = 100; //TEST
  friend class boost::serialization::access;
  template <typename Archive> void serialize(Archive &ar, const unsigned int version) { ar & legs_; }
public:
  animal() = default;
  animal(int legs) : legs_{legs} {}
  int legs() const { return legs_; }
  int weight() const { return weight_; } //TEST
};

void save() {
  boost::archive::text_oarchive oa{ss};
  animal* a = new animal{4};
  oa << a;
  cout << hex << a << '\n';
  delete a;
}

void load() {
  boost::archive::text_iarchive ia{ss};
  animal* a;
  ia >> a;
  cout << hex << a << '\n';
  cout << dec << a->legs() << '\n';
  cout << dec << a->weight() << '\n'; //TEST
  delete a;
}

int main() {
  save();
  load();
}