#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/scoped_ptr.hpp> //Example 64.9 uses the smart pointer boost::scoped_ptr to manage a dynamically allocated object of type animal. Include the header file boost/serialization/scoped_ptr.hpp to serialize such a pointer. To serialize a smart pointer of type boost::shared_ptr, use the header file boost/serialization/shared_ptr.hpp. @ https://theboostcpplibraries.com/boost.serialization-pointers-and-references
#include <boost/scoped_ptr.hpp> //Please note that Boost.Serialization hasn’t been updated for C++11, yet. Smart pointers from the C++11 standard library like std::shared_ptr and std::unique_ptr are not currently supported by Boost.Serialization. @ https://theboostcpplibraries.com/boost.serialization-pointers-and-references
#include <iostream>
#include <sstream>
using namespace boost::archive;
using boost::scoped_ptr;
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
  scoped_ptr<animal> a{new animal{4}};
  oa << a;
}

void load() {
  text_iarchive ia{ss};
  scoped_ptr<animal> a;
  ia >> a;
  cout << a->legs() << '\n';
}

int main() {
  save();
  load();
}