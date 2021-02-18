#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main() {
	vector<vector<string>> strCountryDim = { {"008", "FO17.0001"}, {"008", "FO17.0001"} };
	for (auto i = strCountryDim.begin(); i < strCountryDim.end(); i++) {
		for (auto j = i._Ptr->begin(); j < i._Ptr->end(); j++) cout << *j << '\t';
		cout << endl;
	}
	cout << endl;
	
	vector<vector<double>> dblYearValue = { {1990, 788.8}, {2010, 753.3} };
	for (auto i = dblYearValue.begin(); i < dblYearValue.end(); i++) {
		for (auto j = i._Ptr->begin(); j < i._Ptr->end(); j++) cout << *j << '\t';
		cout << endl;
	}
	cout << endl;
}

