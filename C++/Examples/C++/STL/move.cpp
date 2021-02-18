#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
using namespace std;

typedef vector<int> vecInt_t;

void display(const vecInt_t& objNumbers) {
	for (auto intNumber : objNumbers) cout << intNumber << " ";
	cout << "\n\n";
}

int main() {
	vecInt_t objNumbers(6);
	iota(objNumbers.begin(), objNumbers.end(), 0);
	cout << endl;
	display(objNumbers);
	auto ptrObjectsBeg = objNumbers.begin();
	vecInt_t intNumbersDest;
	auto ptrNumberPastMoved = move(ptrObjectsBeg, ptrObjectsBeg + 4, back_inserter(intNumbersDest));
	objNumbers.erase(ptrObjectsBeg, ptrObjectsBeg + 4);
	cout << "intNumbers.size() = " << objNumbers.size() << endl;
	display(objNumbers);
	display(intNumbersDest);
	return 0;
}