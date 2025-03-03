#ifdef ON

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <algorithm>
using namespace std;

void Assignment_and_swap() {
	vector<int> c1, c2 = {0, 1, 2, 3, 4}; int a{10}, b{20}, c{30}; //MINE

	c1 = c2; // replace the contents of c1 with a copy of the elements in c2
	copy(c1.cbegin(), c1.cend(), ostream_iterator<int>(cout, " ")); cout << "\tSize: " << c1.size() << "\tCapacity: " << c1.capacity() << '\n'; //MINE
	//TEST! c1 = {a, b, c}; //																																										after the assignment c1 has size 3
	copy(c1.cbegin(), c1.cend(), ostream_iterator<int>(cout, " ")); cout << "\tSize: " << c1.size() << "\tCapacity: " << c1.capacity() << '\n'; //MINE

	array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
	array<int, 10> a2 = {0}; // elements all have value 0
	
#ifdef OFF
	//MINE
	//TEST! array<int, 5> a3;
	cout << '\n'; copy(a3.cbegin(), a3.cend(), ostream_iterator<int>(cout, " ")); cout << "\tSize: " << a3.size() << '\n';
	vector<int> c3(5);
	copy(c3.cbegin(), c3.cend(), ostream_iterator<int>(cout, " ")); cout << "\tSize: " << c3.size() << "\tCapacity: " << c3.capacity() << '\n';
#endif
		
	a1 = a2; // replaces elements in a1
	cout << '\n'; copy(a2.cbegin(), a2.cend(), ostream_iterator<int>(cout, " ")); cout << "\tSize: " << a2.size() << '\n'; //MINE
	//ORIG a2 = {0}; // error: cannot assign to an array from a braced list
	//TEST! a2 = {5}; //MINE
	copy(a2.cbegin(), a2.cend(), ostream_iterator<int>(cout, " ")); cout << "\tSize: " << a2.size() << '\n'; //MINE
}

void Using_assign_Sequential_Containers_Only() {
	list<string> names;
	vector<const char *> oldstyle;
	//TEST! names = oldstyle; //																																									error: container types don’t match
	//TEST! names.assign(oldstyle.cbegin(), oldstyle.cend()); //																																	ok: can convert from const char* to string

	// equivalent to slist1.clear(); followed by slist1.insert(slist1.begin(), 10, "Hiya!");
	list<string> slist1(1); // one element, which is the empty string
	//TEST! slist1.assign(10, "Hiya!"); //																																							ten elements; each one is Hiya!
}

void Using_swap() {
	vector<string> svec1(10); // vector with ten elements
	vector<string> svec2(24); // vector with 24 elements
	auto out = ostream_iterator<string>(cout, " "); //MINE
	
	cout << '|'; copy(svec1.cbegin(), svec1.cend(), out); cout << "|\n"; //MINE
	cout << '|'; copy(svec2.cbegin(), svec2.cend(), out); cout << "|\n"; //MINE

	swap(svec1, svec2); //TEST!

	cout << '|'; copy(svec1.cbegin(), svec1.cend(), out); cout << "|\n"; //MINE
	cout << '|'; copy(svec2.cbegin(), svec2.cend(), out); cout << "|\n"; //MINE

	//MINE
	int a{1}, b{2};
	swap(a, b); //TEST!
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Assignment_and_swap();
	//Using_assign_Sequential_Containers_Only();
	Using_swap();

	return 0;
}
#endif