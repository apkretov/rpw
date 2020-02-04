#include "stdafx.h" //Chapter 25. Boost.PropertyTree - Example 25.4. Various member functions of boost::property_tree::ptree @ https://theboostcpplibraries.com/boost.propertytree
#include <boost/property_tree/ptree.hpp>
#include <utility>
#include <iostream>
using namespace std;

using boost::property_tree::ptree;

int main() {
	ptree pt;
	pt.put("C:.Windows.System", "20 files");

	boost::optional<string> c = pt.get_optional<string>("C:");
	cout << boolalpha << c.is_initialized() << '\n';

	pt.put_child("D:.Program Files", ptree{ "50 files" });
	pt.add_child("D:.Program Files", ptree{ "60 files" });

	/*ORIG ptree d = pt.get_child("D:");
	for (const pair<string, ptree>& p : d) cout << p.second.get_value<string>() << '\n';*/
	for (const auto& p : pt.get_child("D:")) cout << p.second.get_value<string>() << '\n'; //TEST

	boost::optional<ptree&> e = pt.get_child_optional("E:");
	cout << e.is_initialized() << '\n';
}