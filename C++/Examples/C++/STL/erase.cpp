#include "stdafx.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
using namespace std;

void eraseExample() { //std::vector::erase
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) std::cout << i << " ";
    std::cout << '\n';
 
    c.erase(c.begin());
    for (auto &i : c) std::cout << i << " ";
    std::cout << '\n';
 
    c.erase(c.begin()+2, c.begin()+5);
    for (auto &i : c) std::cout << i << " ";
    std::cout << '\n';
}

void eraseIteratorsERROR() {
	vector<int> vecInt(10);
	iota(vecInt.begin(), vecInt.end(), 0);
	auto display = [vecInt](){ copy(vecInt.begin(), vecInt.end(), ostream_iterator<int>(cout, " ")); cout << endl; };
	display();
	for (auto ptrVecInt = vecInt.begin(); ptrVecInt != vecInt.end();)	{
		if (*ptrVecInt == 5) 
			;//ERROR vecInt.erase(ptrVecInt); //Invalidates iterators and references at or after the point of the erase, including the end() iterator.
		else 
			++ptrVecInt;
	}
	display();
}

int main() {
	eraseExample();
	//eraseIteratorsERROR();
	return 0;
}

