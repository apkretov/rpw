#ifndef	EX_16_28

#include <iostream>
#include <type_traits>
#include "../../stdafx.h"
#include "vld.h"
#include "16_01_4_2.h"
#include "16_01_6_1.h"
#include "16_01_6_2.h"
using namespace std;

//OFF #define DEBUG_EX_16_28

template <typename T>
void deleter_func(T *ptr) {
#ifdef DEBUG_EX_16_28
	cout << "\nvoid deleter_func(T *ptr): deleting...";
#endif
	delete ptr;
}

void test_shared() {
	my_shared_ptr<int> p1(new int(111));
	cout << "p1: " << *p1 << '\t';
	cout << "p1.use_count(): " << p1.use_count() << '\n';

	my_shared_ptr<int> p2(new int(222), deleter_func<int>);
	cout << "\np2: " << *p2 << '\t';
	cout << "p2.use_count(): " << p2.use_count() << '\n';

	my_shared_ptr<int> p3(new int(333), DebugDelete());
	cout << "\np3: " << *p3 << '\t';
	cout << "p3.use_count(): " << p3.use_count() << '\n';

	my_shared_ptr<int> p4(p1);
	cout << "\np4: " << *p4 << '\t';
	cout << "p4.use_count(): " << p4.use_count() << '\n';
	cout << "p1: " << *p1 << '\t';
	cout << "p1.use_count(): " << p1.use_count() << '\n';

	p2 = p1;
	cout << "\np2: " << *p2 << '\t';
	cout << "p1.use_count(): " << p1.use_count() << '\n';
	cout << "p2: " << *p2 << '\t';
	cout << "p2.use_count(): " << p2.use_count() << '\n';
	cout << "p4: " << *p4 << '\t';
	cout << "p4.use_count(): " << p4.use_count() << '\n';

	my_shared_ptr<int> p5 = std::move(p3);
	cout << "\np5: " << *p5 << '\t';
	cout << "p5.use_count(): " << p5.use_count() << '\n';

	my_shared_ptr<int> p6 = std::move(p1);
	cout << "\np6: " << *p6 << '\t';
	cout << "p6.use_count(): " << p6.use_count() << '\n';
	cout << "p2: " << *p2 << '\t';
	cout << "p2.use_count(): " << p2.use_count() << '\n';
	cout << "p4: " << *p4 << '\t';
	cout << "p4.use_count(): " << p4.use_count() << '\n';

	p3 = std::move(p6);
	cout << "\np3: " << *p3 << '\t';
	cout << "p3.use_count(): " << p3.use_count() << '\n';
	cout << "p2: " << *p2 << '\t';
	cout << "p2.use_count(): " << p2.use_count() << '\n';
	cout << "p4: " << *p4 << '\t';
	cout << "p4.use_count(): " << p4.use_count() << '\n';

	cout << '\n';
}

void test_unique() {
	my_unique_ptr<int> p1;

	my_unique_ptr<int> p2(new int(111));
	cout << "p2: " << *p2 << '\n';

	my_unique_ptr<int> p3(new int(222), DebugDelete());
	cout << "p3: " << *p3 << '\n';

	my_unique_ptr<int> p4 = std::move(p2);
	cout << "\np4: " << *p4 << '\n';

	p3 = std::move(p4);
	cout << "\np3: " << *p3 << '\n';
}

struct constructible {
	int i;
	constructible() : i(111) { cout << "constructible()\n"; }
	explicit constructible(int i) : i(i) { cout << "constructible(int i)\n"; }
};

void move_constructible_() {
	cout << boolalpha;
	cout << "is_move_constructible<my_shared_ptr<int>>() = " << is_move_constructible<my_shared_ptr<int>>() << '\n';
	cout << "is_trivially_move_constructible<my_shared_ptr<int>>() = " << is_trivially_move_constructible<my_shared_ptr<int>>() << '\n';
	cout << "is_move_constructible<my_shared_ptr<int>>() = " << is_move_constructible<my_shared_ptr<int>>() << '\n';
	cout << "is_move_assignable<my_shared_ptr<int>>() = " << is_move_assignable<my_shared_ptr<int>>() << '\n';
	
	cout << "\nis_move_constructible<constructible>() = " << is_move_constructible<constructible>() << '\n';
	cout << "is_trivially_move_constructible<constructible>() = " << is_trivially_move_constructible<constructible>() << '\n';
	cout << "is_move_assignable<constructible>() = " << is_move_assignable<constructible>() << '\n';
}

int main() {
	print_file_line();

	test_shared();
	//test_unique();
	//move_constructible_();

	return 0;
}
#endif

#ifdef EX_16_29

#include <iostream>
#include "../../stdafx.h"
#include "vld.h"
#include "16_01_6_3.h"
using namespace std;

int main() {
	print_file_line();

	auto pi = my_make_shared<int>(111);
	cout << "*pi: " << *pi << '\n';

	auto pv = my_shared_ptr<vector<int>>(new vector<int>({0,1,2,3,4,5,6,7,8,9}));
	cout << "(*pv).back() = " << (*pv).back() << '\n';
	cout << "(*pv).size() = " << (*pv).size() << '\n';
	(*pv).push_back(111);
	cout << "(*pv).back() = " << (*pv).back() << '\n';
	cout << "(*pv).size() = " << (*pv).size() << '\n';

	return 0;
}
#endif
