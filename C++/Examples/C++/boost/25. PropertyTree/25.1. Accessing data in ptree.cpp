#include "stdafx.h" //Chapter 25. Boost.PropertyTree - Example 25.1. Accessing data in boost::property_tree::ptree @ https://theboostcpplibraries.com/boost.propertytree
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <iostream>
using namespace std;

int main() {
	ptree pt;
	pt.put("C:.Windows.System", "20 files");

	ptree& c = pt.get_child("C:");
	ptree& windows = c.get_child("Windows"); /*TEST cout << "windows.get_value: " << windows.get_value<string>() << '\n';*/
	ptree& system = windows.get_child("System");
	cout << system.get_value<string>() << '\n';
	ptree& ptreeCWindowsSystem  = pt.get_child("C:.Windows.System"); //TEST
	cout << "ptreeCWindowsSystem.get_value: " << ptreeCWindowsSystem.get_value<string>() << endl; //TEST
}