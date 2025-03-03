#if 0

#include <iostream>
#include <set>
#include "../../stdafx.h"
using namespace std;

#undef ERR
#undef COPYING
#define MOVING

#ifdef MOVING
struct NCString : public string {
	using string::string;
	NCString(const NCString &) = delete;
	NCString(NCString &&) = default;
};
#endif //MOVING

int main() {
	PRINT_FILE_LINE();

#ifndef MOVING //ERR or COPYING
	set<string> ss;
#else //MOVING
	set<NCString> ss;
#endif //MOVING
	ss.insert("Aaa");
	ss.insert("Bbb");
	ss.insert("Ccc");

	for (auto const &el : ss)
		cout << el << ' ';
	cout << endl;

	auto it = ss.begin();
#ifdef ERR
	string &temp = *it;
	temp[0] = tolower(temp[0]); //TEST!
#endif //ERR
#ifdef COPYING
	string temp = *it;
	temp[0] = tolower(temp[0]);
	ss.erase(it);
	ss.insert(temp);
#endif //COPYING
#ifdef MOVING
	auto node = ss.extract(it); //TEST!
	string &temp = node.value(); //TEST!
	temp[0] = tolower(temp[0]);
	ss.insert(move(node)); //TEST!
#endif //MOVING

	for (auto const &el : ss)
		cout << el << ' ';
	cout << endl;

#ifdef MOVING
	set<NCString> ss2;
	ss2.insert("Xxx");
	ss2.insert("Yyy");
	ss2.insert("yyy");

	ss.merge(ss2);
	for (auto const &el : ss)
		cout << el << ' ';
	cout << endl;

	for (auto const &el : ss2)
		cout << el << ' ';
	cout << endl;
#endif //MOVING
}
#endif //1