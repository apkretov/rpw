#if 0

#include <iostream>
#include <map>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#define WITH_JOIN_TEMPLATE

template <typename First, typename Second>
ostream &operator<<(ostream &out, const pair<First, Second> &p) {
	//ORIG return out << '(' << p.first << ',' << p.second << ')';
	return out << format("({},{})", p.first, p.second); //MINE
}

template <typename Collection> //TEST!
string Join(const Collection &c, const char d) {
	stringstream ss;
	bool first = true;
	for (const auto &i : c) {
		if (!first)
			ss << d;
		first = false;
		ss << i;
	}
	return ss.str();
}

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
#ifndef WITH_JOIN_TEMPLATE
	for (const auto &i : v)
		out << i << ", ";
	return out;
#else
	return out << '[' << Join(v, ',') << ']';
#endif 
}

template <typename Key, typename Value>
ostream &operator<<(ostream &out, const map<Key, Value> &m) {
#ifndef WITH_JOIN_TEMPLATE
	for (const auto &i : m)
		out << i << ", ";
	return out;
#else
	return out << '{' << Join(m, ',') << '}';
#endif
}

int main() {
	vector<int> vi{1, 2, 3};
	vector<double> vd{1.1, 2.2, 3.3};
	vector<vector<int>> vvi{{1,2, 3}, {4,5,6}};
	map<int, double> m{{1, 1.1}, {2, 2.2}, {3, 3.3}};

	cout << vi << '\n';
	cout << vd << '\n';
	cout << vvi << '\n';
	cout << m << '\n';
}
#endif