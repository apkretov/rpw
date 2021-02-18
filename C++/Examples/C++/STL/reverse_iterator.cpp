#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
using namespace std;

int main() {
	constexpr int intSearchedNum = 9;
	vector<int> vecInt(10);
	iota(vecInt.begin(), vecInt.end(), 0);
	auto coutInt = ostream_iterator<int>(cout, " ");
	copy(vecInt.cbegin(), vecInt.cend(), coutInt); cout << endl;
	auto ptrRBeg = vecInt.crbegin();
	auto ptrREnd = vecInt.crend();
	copy(ptrRBeg, ptrREnd, coutInt); cout << endl;
	auto ptrFind = find(ptrRBeg, ptrREnd, intSearchedNum);
	if (ptrFind != ptrREnd) cout << "Serched number is " << *ptrFind << endl; //See std::reverse_iterator @ http://en.cppreference.com/w/cpp/iterator/reverse_iterator
	else cout << "Serched number is not found. ptrFind == ptrREnd" << endl;
	return 0;
}

