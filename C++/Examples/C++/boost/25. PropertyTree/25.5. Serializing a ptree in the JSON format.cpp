#include "stdafx.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost\property_tree\xml_parser.hpp>
using namespace boost::property_tree;
#include <iostream>
using namespace std;

void json() { //Chapter 25. Boost.PropertyTree - Example 25.5. Serializing a boost::property_tree::ptree in the JSON format @ https://theboostcpplibraries.com/boost.propertytree
	ptree pt;
	pt.put("C:.Windows.System", "20 files");
	pt.put("C:.Windows.Cursors", "50 files");

	json_parser::write_json("file.json", pt);

	ptree pt2;
	json_parser::read_json("file.json", pt2);

	cout << boolalpha << (pt == pt2) << '\n';
}

void jsonMine() {
	ptree pt;
	const string strConstants = "Constants";
	const string strAccount = "Account";
	pt.put_child(strConstants + "." + strAccount, ptree{strAccount});	

	ptree pt2;
	pt2.put("Test1.Test2.Test21", "Item21");
	pt2.put("Test1.Test2.Test22", "Item22");
	pt2.put_child("Test1.Test2.Test23", pt);
	json_parser::write_json("fileMine.json", pt2);

	ptree pt3;
	json_parser::read_json("fileMine.json", pt3);
	cout << boolalpha << (pt2 == pt3) << '\n';
}

void xml() {
	ptree pt;
	pt.put("C:.Windows.System", "20 files");
	pt.put("C:.Windows.Cursors", "50 files");

	xml_parser::write_xml("file.xml", pt);

	ptree pt2;
	xml_parser::read_xml("file.xml", pt2);

	cout << boolalpha << (pt == pt2) << '\n';
}

int main() {
	json();
	jsonMine();
	xml();
}