#include "stdafx.h" //Chapter 25. Boost.PropertyTree - Example 25.2. Accessing data in basic_ptree<std::string, int> @ https://theboostcpplibraries.com/boost.propertytree
#include <boost/property_tree/ptree.hpp>
#include <utility>
#include <iostream>
using namespace std;

int main() {
	typedef boost::property_tree::basic_ptree<string, int> ptree;
	ptree pt;
	pt.put(ptree::path_type{ "C:\\Windows\\System", '\\' }, 20);
	pt.put(ptree::path_type{ "C:\\Windows\\Cursors", '\\' }, 50);

	ptree& windows = pt.get_child(ptree::path_type{ "C:\\Windows", '\\' });
	int files = 0;
	//ORIG for (const pair<string, ptree> &p : windows) files += p.second.get_value<int>();
	for (const auto &p : windows) files += p.second.get_value<int>(); //TEST
	cout << files << '\n';
}