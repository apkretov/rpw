#include "stdafx.h" //Predicates vs. Function Objects @ https://adtmag.com/articles/2000/05/30/predicates-vs-function-objects.aspx
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class Nth {        // function object that returns true for the nth call
    int nth;       // call for which to return true
    int count;     // call counter
  public:
    Nth(int n) : nth(n), count(0) { }
    bool operator()(int) { return ++count == nth; }
};

#define PRINT_ELEMENTS(coll, print)	for_each(coll.cbegin(), coll.cend(), print), cout << endl;

int main() {
    list<int> coll;
    auto print = [](const auto& n) {cout << " " << n; };

	 for (int i=1; i<=9; ++i) coll.push_back(i); // insert elements from 1 to 9
	 PRINT_ELEMENTS(coll, print);

    list<int>::iterator pos;							// remove third element
    pos = remove_if( coll.begin(), coll.end(),	// range
			 Nth(3) ),										// remove criterion
			 coll.erase(pos, coll.end());
	 PRINT_ELEMENTS(coll, print);
}
