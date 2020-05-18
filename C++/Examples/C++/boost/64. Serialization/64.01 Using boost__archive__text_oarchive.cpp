#include "stdafx.h" //Chapter 64. Boost.Serialization @ https://theboostcpplibraries.com/boost.serialization-archive
#include <boost\archive\text_oarchive.hpp>
#include <iostream>
using namespace boost::archive;

int main() {
	text_oarchive oa{std::cout};
	//TEST text_oarchive oa = std::cout;
	int i = 1;
	oa << i;
}