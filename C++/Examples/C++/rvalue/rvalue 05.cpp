#include "stdafx.h" //Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c
#include <map>
#include <iostream>
using namespace std;

int main() {
	map<int, float> mymap;
	cout << mymap.size() << endl;
	mymap[10] = 5.6;
	cout << mymap.size() << endl;
	cout << mymap[1] << endl;
	cout << mymap.size() << endl;
	cout << mymap[10] << endl;
	mymap[5] = 2.5;
	cout << mymap.size() << endl;
	cout << mymap[5] << endl;
	return 0;
}

