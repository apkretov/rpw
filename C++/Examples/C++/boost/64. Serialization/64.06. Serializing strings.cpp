#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
using namespace boost::archive;
using namespace std;

stringstream ss;

class animal {
  int legs_;
  string name_;
  friend class boost::serialization::access;
  template <typename Archive> friend void serialize(Archive &ar, animal &a, const unsigned int version);
public:
  animal() = default;
  animal(int legs, string name) : legs_{ legs }, name_{ move(name) } {}
  int legs() const { return legs_; }
  const string &name() const { return name_; }
};

template <typename Archive> void serialize(Archive &ar, animal &a, const unsigned int version) {
  ar & a.legs_;
  ar & a.name_;
}

void save() {
  text_oarchive oa{ss};
  animal a{4, "cat"};
  oa << a;
}

void load() {
  text_iarchive ia{ss};
  animal a;
  ia >> a;
  cout << a.legs() << '\n';
  cout << a.name() << '\n';
}

int main() {
  save();
  load();
}