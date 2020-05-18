#include "stdafx.h" //Chapter 25. Boost.PropertyTree - Example 25.3. Accessing data with a translator @ https://theboostcpplibraries.com/boost.propertytree
#include <boost/property_tree/ptree.hpp>
#include <boost/optional.hpp>
#include <iostream>
using namespace std;
#include <cstdlib>

struct string_to_int_translator {
	typedef string internal_type;
	typedef int external_type;
	boost::optional<int> get_value(const string& s) {
		char* c;
		long l = strtol(s.c_str(), &c, 10);
		return boost::make_optional(c != s.c_str(), static_cast<int>(l));
}	};

int main() {
	typedef boost::property_tree::iptree ptree;
	ptree pt;
	pt.put(ptree::path_type{ "C:\\Windows\\System", '\\' }, "20 files");
	pt.put(ptree::path_type{ "C:\\Windows\\Cursors", '\\' }, "50 files");

	string_to_int_translator tr;
	int files =
		pt.get<int>(ptree::path_type{ "c:\\windows\\system", '\\' }, tr) +
		pt.get<int>(ptree::path_type{ "c:\\windows\\cursors", '\\' }, tr);
	cout << files << '\n';
}