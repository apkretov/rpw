#include "stdafx.h" //static_cast conversion @ http://en.cppreference.com/w/cpp/language/static_cast
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

struct B {
	int m = 0;
	void hello() const {
		cout << "Hello world, this is B!\n";
}	};

struct D : B {
	void hello() const {
		cout << "Hello world, this is D!\n";
}	};

enum class E { ONE = 1, TWO, THREE };
enum EU { ONE = 1, TWO, THREE };

int main() {
	int n = static_cast<int>(3.14); // 1: initializing conversion
	cout << "n = " << n << '\n';
	vector<int> v = static_cast<vector<int>>(10);
	cout << "v.size() = " << v.size() << "\n\n";

	D d; // 2: static downcast
	B& br = d; // upcast via implicit conversion
	br.hello();
	D& another_d = static_cast<D&>(br); // downcast
	another_d.hello();
	cout << endl;

	vector<int> v2 = static_cast<vector<int>&&>(v); // 3: lvalue to xvalue
	cout << "after move, v.size() = " << v.size() << "\n\n";

	string strTestSrc = "Test"; //TEST
	cout << strTestSrc << endl; 
	cout << strTestSrc.size() << endl;
	string strTestDst = static_cast<string&&>(strTestSrc); 
	cout << strTestSrc.size() << endl;
	cout << strTestDst.size() << "\n\n";

	static_cast<void>(v2.size()); // 4: discarded-value expression

	void* nv = &n; // 5. inverse of implicit conversion
	int* ni = static_cast<int*>(nv);
	cout << "*ni = " << *ni << "\n\n";

	D a[10]; // 6. array-to-pointer followed by upcast
	B* dp = static_cast<B*>(a);

	E e = E::ONE; // 7. scoped enum to int or float
	int one = static_cast<int>(e);
	cout << one << "\n\n";

	E e2 = static_cast<E>(one); // 8. int to enum, enum to another enum
	EU eu = static_cast<EU>(e2);

	int D::*pm = &D::m; // 9. pointer to member upcast
	cout << br.*static_cast<int B::*>(pm) << "\n\n";

	void* voidp = &e; // 10. void* to any type
	vector<int>* p = static_cast<vector<int>*>(voidp);
}