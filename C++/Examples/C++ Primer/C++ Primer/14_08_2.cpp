#ifdef ON
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <algorithm>
#include "../../stdafx.h"
using namespace std;

void Library_Defined_Function_Objects() {
	plus<int> intAdd; //TEST! //																																									function object that can add two int values
	negate<int> intNegate; //TEST! //																																								function object that can negate an int value

	// uses intAdd::operator(int, int) to add 10 and 20
	int sum = intAdd(10, 20); // equivalent to sum = 30
	cout << sum << '\n'; //MINE
	sum = intNegate(intAdd(10, 20)); // equivalent to sum = -30
	cout << sum << '\n'; //MINE

	// uses intNegate::operator(int) to generate -10 as the second parameter // to intAdd::operator(int, int)
	sum = intAdd(10, intNegate(10)); // sum = 0
	cout << sum << '\n'; //MINE
}

void Using_a_Library_Function_Object_with_the_Algorithms(const char *arg) {
	//MINE
	cout << "vector<string>\n";
	fstream file(arg);
	istream_iterator<string> in(file), eof;
	vector<string> svec(in, eof), svecCopy(svec);
	ostream_iterator<string> out(cout, " ");
	copy(svec.cbegin(), svec.cend(), out); cout << '\n';

	sort(svec.begin(), svec.end(), greater<string>()); //TEST! //																																	passes a temporary function object that applies the < operator to two strings
	copy(svec.cbegin(), svec.cend(), out); cout << '\n'; //MINE

	vector<string *> nameTable; // vector of pointers

	//MINE
	cout << "\nvector<string *>\n";
	for_each(svecCopy.begin(), svecCopy.end(), [&nameTable](string &s) { nameTable.push_back(&s); });
	auto print = [](const string *ps) { cout << *ps << ' '; };
	for_each(nameTable.cbegin(), nameTable.cend(), print); cout << '\n';

	sort(nameTable.begin(), nameTable.end(), [](string *a, string *b) { return a < b; }); // error: the pointers in nameTable are unrelated, so < is undefined
	for_each(nameTable.cbegin(), nameTable.cend(), print); cout << '\n'; //MINE
	sort(nameTable.begin(), nameTable.end(), less<string *>()); // ok: library guarantees that less on pointer types is well defined
	for_each(nameTable.cbegin(), nameTable.cend(), print); cout << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	print_file_line();

	//Library_Defined_Function_Objects();
	Using_a_Library_Function_Object_with_the_Algorithms(argv[1]);

	return 0;
}
#endif

#ifdef EX_14_42

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <functional>
#include "../../stdafx.h"
#include "14_08_2_util.h"
using namespace std;

void mine1() { // you.com
	random_device rd;  // Obtain a random seed from the hardware
	mt19937 gen(rd()); // Seed the random number generator

	int min = 1; // Define the range of random numbers
	int max = 100;
	uniform_int_distribution<> dis(min, max); // Define the distribution

	int randomNum = dis(gen); // Generate and print a random number
	cout << "Random number: " << randomNum << endl;

	//MINE
	cout << "\nThe all of random numbers:\n";
	for (size_t i = min; i <= max; ++i) {
		cout << dis(gen);
		cout << (i % 10 ? '\t' : '\n');
	}
}

void mine2() {
	constexpr int min = 1, max = 100;
	Rnd rnd(min, max);
	for (size_t i = min; i <= max; ++i)
		cout << rnd() << ' ';
	cout << '\n';
}

void mine3() {
	constexpr int min = 1, max = 3;
	constexpr size_t n = 10;
	Rnd rnd(min, max);

	for (size_t j = 0; j < n; ++j) {
		for (size_t i = min; i <= max; ++i)
			cout << rnd() << ' ';
		cout << "\n\n";
	}
}

void a() {
	vector<int> v(5);
	Rnd rnd(0, 2048);
	generate(v.begin(), v.end(), rnd);

	ostream_iterator<int> out(cout, " ");
	copy(v.cbegin(), v.cend(), out); cout << '\n';

	constexpr int t = 1024;
#ifdef LAMBDA
	auto n = count_if(v.cbegin(), v.cend(), [](int item) { return item > t; });
#elif! GREATER
	auto n = count_if(v.cbegin(), v.cend(), bind(greater<int>(), placeholders::_1, t));
#endif
	cout << n << '\n';
}

void b(const char *arg) {
	fstream file(arg);
	istream_iterator<string> in(file), eof;
	vector<string> v(in, eof);
	ostream_iterator<string> out(cout, " ");
	copy(v.cbegin(), v.cend(), out); 
	cout << '\n';

	const string t = "pooh";
#ifndef _1
	auto first = find_if(v.cbegin(), v.cend(), bind(not_equal_to<string>(), placeholders::_1, t));
#elif! _2
	auto first = find_if_not(v.cbegin(), v.cend(), bind(equal_to<string>(), placeholders::_1, t));
#endif
	cout << *first << '\n';
}

void c() {
	Rnd rnd;
	vector<int> v(5);
	generate(v.begin(), v.end(), rnd);

	cout << "The initial vector:\n";
	ostream_iterator<int> out(cout, "\t");
	copy(v.cbegin(), v.cend(), out);
	cout << '\n';

	constexpr int mult = 2;
	cout << "\nThe vector multiplied by " << mult << ":\n";
	transform(v.begin(), v.end(), v.begin(), bind(multiplies<int>(), placeholders::_1, mult));
	copy(v.cbegin(), v.cend(), out);
	cout << '\n';
}

int main(int argc, char *argv[]) {
	print_file_line();

	//mine1();
	//mine2();
	//mine3();
	//a();
	//b(argv[1]);
	c();

	return 0;
}
#endif

#ifdef EX_14_43

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "../../stdafx.h"
#include "14_08_2_util.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();
	
#ifdef RND
	vector<int> v(10);
	Rnd rnd(2);
	const int t = rnd();
	generate(v.begin(), v.end(), rnd);
#else
	const vector<int> v = {2, 3, 4};
	constexpr int t = 5;
#endif

	ostream_iterator<int> out(cout, " ");
	copy(v.cbegin(), v.cend(), out);
	cout << "\nDivedend: " << t << '\n';

	modulus<int> mod;
	//OFF cout << mod(5, 2) << '\n';
	
#ifdef MINE
	auto it = find_if_not(v.cbegin(), v.cend(), bind(modulus<int>(), t, placeholders::_1));
	if (it != v.cend())
	if (x)
		cout << "Divisible by item " << it - v.cbegin() << ": " << *it << '\n';
	else
		cout << "Not dividisible by any item.\n";
#elif! ANY_OF // By ch14/ex14_43.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch14/ex14_43.cpp
	auto divisible = any_of(v.cbegin(), v.cend(), [&mod, t](int i) { return !mod(t, i); });
	if (divisible)
		cout << "Divisible by some item.\n";
	else
		cout << "Not dividisible by any item.\n";
#endif
	return 0;
}
#endif