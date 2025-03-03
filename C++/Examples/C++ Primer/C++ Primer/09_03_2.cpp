#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

vector<int> c(10);

void Accessing_Elements() {
	if (!c.empty()) { // check that there are elements before dereferencing an iterator or calling front or back
		//TEST! auto val = *c.begin(), val2 = c.front(); //																																				val and val2 are copies of the value of the first element in cs
		auto last = c.end(); // val3 and val4 are copies of the of the last element in c
		auto val3 = *(--last); // can’t decrement forward_list iterators
		auto val4 = c.back(); // not supported by forward_list
	}
}

void The_Access_Members_Return_References() {
	if (!c.empty()) {
		c.front() = 42; // assigns 42 to the first element in c
		auto &v = c.back(); //																																											get a reference to the last element
		//TEST! v = 1024; //																																											changes the element in c
		auto v2 = c.back(); //																																											v2 is not a reference; it’s a copy of c.back()
		//TEST! v2 = 0; //																																												no change to the element in c
	}
}

void Subscripting_and_Safe_Random_Access() {
	vector<string> svec; // empty vector
	cout << svec[0]; // run-time error: there are no elements in svec!
	cout << svec.at(0); // throws an out_of_range exception
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif
