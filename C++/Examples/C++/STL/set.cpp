#include "stdafx.h" // Based on Fig. 20.20: fig20_20.cpp // Standard Library class set test program.
#include <iostream>
#include <iterator> // ostream_iterator
#include <set>
#include <functional>
using namespace std;

int main() {
   ostream_iterator<double> output(cout, " ");

	set<double> setYearsAsc{1, 2, 3};
	cout << "setYearsAsc contains: ";
	copy(setYearsAsc.begin(), setYearsAsc.end(), output);
	cout << endl;

	set<double, std::greater<>> setYearsDesc(setYearsAsc.crbegin(), setYearsAsc.crend());
	cout << "setYearsDesc contains: ";
	copy(setYearsDesc.begin(), setYearsDesc.end(), output);
	cout << endl;

	set<double> setYearsLatest(setYearsDesc.begin(), ++setYearsDesc.begin());
	cout << "setYearsLatest contains: ";
	copy(setYearsLatest.begin(), setYearsLatest.end(), output);
	cout << endl;

	return 0;
} 
