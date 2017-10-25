#include "stdafx.h" //Range-based for loop (since C++11) @ http://en.cppreference.com/w/cpp/language/range-for
#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> v = { 0, 1, 2, 3, 4, 5 };

	for (const int& i : v) cout << i << ' '; cout << '\n'; // access by const reference
	for (auto i : v) cout << i << ' '; cout << '\n'; // access by value, the type of i is int
	for (auto&& i : v) cout << i << ' '; cout << '\n'; // access by reference, the type of i is int
	for (int n : {0, 1, 2, 3, 4, 5}) cout << n << ' '; cout << '\n'; // the initializer may be a braced-init-list
	
	int a[] = { 0, 1, 2, 3, 4, 5 };
	for (int n : a) cout << n << ' '; cout << '\n'; // the initializer may be an array

	for (int n : a) cout << 1 << ' '; cout << '\n'; // the loop variable need not be used
}