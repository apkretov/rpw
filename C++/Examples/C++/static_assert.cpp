#include "stdafx.h"
#include <iostream>
#include <type_traits>
using namespace std;

/*OFF
template <typename T, size_t Size> class Vector { //#9 Ч static_assert и классы свойств @ https://habrahabr.ru/post/182920/
   static_assert(Size > 3, "Size is too small");
   T _points[Size];
};

void No9_static_assert_Example1() { 
   Vector<int, 16> a1;
   Vector<double, 2> a2;
}*/

template <typename T1, typename T2> auto add1(T1 t1, T2 t2) -> decltype(t1 + t2) { return t1 + t2; }

template <typename T1, typename T2> auto add2(T1 t1, T2 t2) -> decltype(t1 + t2) { 
	static_assert(is_integral<T1>::value, "Type T1 must be integral (int)");
	static_assert(is_integral<T2>::value, "Type T2 must be integral (int)");
	return t1 + t2;
}

void No9_static_assert_Example2() { 
	cout << add1(1, 3.14) << endl;
	cout << add1("one", 2) << endl;

	cout << add2(1, 3.14) << endl;
	cout << add2("one", 2) << endl;
}

void static_assert_Example() { //What is the difference between assert and static_assert? @ http://stackoverflow.com/questions/18210270/what-is-the-difference-between-assert-and-static-assert
	static_assert(sizeof(int) == 4, "int should be 4 bytes");
}

int main() {
	//OFF No9_static_assert_Example1();
	No9_static_assert_Example2();
	static_assert_Example();
	return 0;
}
