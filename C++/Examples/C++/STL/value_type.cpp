#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
using namespace std;

void useOfVectorValue_type1() { vector<int>::value_type c = 10; } //use of vector<int>::value_type? @ http://forums.codeguru.com/showthread.php?479035-use-of-vector-lt-int-gt-value_type

template<typename Container> // Re: use of vector<int>::value_type? // value_type and similar typedefs are useful for writing generic code that can work with any STL container. Eg: @ http://forums.codeguru.com/showthread.php?479035-use-of-vector-lt-int-gt-value_type
class Foo {
	Container m_con;
public:
	Foo(const Container& c) : m_con(c) { }
	typename Container::value_type GetFirst() { return *(m_con.begin()); }
};

void useOfVectorValue_type2() {
	vector<int> a;
	a.push_back(20);

	list<float> b;
	b.push_back(1.234f);

	Foo<vector<int>> c(a);
	Foo<list<float>> d(b);

	cout << c.GetFirst() << endl;
	cout << d.GetFirst() << endl;
}

void vectorValue_type() { //vector::value_type @ https://msdn.microsoft.com/en-us/library/0yf66c82.aspx
	vector<int>::value_type AnInt;
	AnInt = 44;
	cout << AnInt << endl;
}

int main() {
	//useOfVectorValue_type1();
	useOfVectorValue_type2();
	//vectorValue_type();
	return 0;
}

