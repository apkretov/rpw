#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::to_string;
#include <stdio.h>
#include <string>
using std::string;

void sizeofOperator1() { //C++ sizeof Operator @ https://www.tutorialspoint.com/cplusplus/cpp_sizeof_operator.htm
	cout << "Size of char : " << sizeof(char) << endl;
	cout << "Size of int : " << sizeof(int) << endl;
	cout << "Size of short int : " << sizeof(short int) << endl;
	cout << "Size of long int : " << sizeof(long int) << endl;
	cout << "Size of long long : " << sizeof(long long) << endl;
	cout << "Size of float : " << sizeof(float) << endl;
	cout << "Size of double : " << sizeof(double) << endl;
	cout << "Size of wchar_t : " << sizeof(wchar_t) << endl;
	cout << endl;
}

void displaySizeOf(const char* chrType, size_t intSizeOf) { cout << "Size of " + string(chrType) + " = " << intSizeOf << ",\tmax value = " << "2^" + to_string(intSizeOf * 8) + " \t= " << pow(2, intSizeOf * 8) << endl; }

void sizeofOperator2() { //C++ sizeof Operator @ https://www.tutorialspoint.com/cplusplus/cpp_sizeof_operator.htm
	printf("Size of char: %u, max value: %i\n", sizeof(char), (long long)pow(2, 8));
	printf("Size of wchar_t: %u\n", sizeof(wchar_t));
	printf("Size of short: %u\n", sizeof(short));
	printf("Size of int: %u\n", sizeof(int));
	printf("Size of long: %u\n", sizeof(long));
	printf("Size of long long: %u\n", sizeof(long long));
	printf("Size of float: %u\n", sizeof(float));
	printf("Size of double: %u\n", sizeof(double));
	cout << endl;
}

void sizeofOperator3() { //C++ sizeof Operator @ https://www.tutorialspoint.com/cplusplus/cpp_sizeof_operator.htm
	displaySizeOf("bool", sizeof(bool));
	displaySizeOf("char", sizeof(char));
	displaySizeOf("wchar_t", sizeof(wchar_t));
	displaySizeOf("short", sizeof(short));
	displaySizeOf("int", sizeof(int));
	displaySizeOf("long", sizeof(long));
	displaySizeOf("void*", sizeof(void*));
	displaySizeOf("float", sizeof(float));
	displaySizeOf("long long", sizeof(long long));
	displaySizeOf("double", sizeof(double));
	displaySizeOf("long double", sizeof(long double)); //https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(wchar_t_CPP);k(wchar_t);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
	displaySizeOf("__wchar_t", sizeof(__wchar_t));
	displaySizeOf("__int8", sizeof(__int8));
	displaySizeOf("__int16", sizeof(__int16));
	displaySizeOf("__int32", sizeof(__int32));
	displaySizeOf("__int64", sizeof(__int64));
	displaySizeOf("char16_t", sizeof(char16_t)); //https://en.wikipedia.org/wiki/Wide_character
	displaySizeOf("char32_t", sizeof(char32_t));
	cout << endl;
}

void ASCIIchart() { //ASCII Chart @ http://en.cppreference.com/w/cpp/language/ascii
	char a = 'x'; // x = 120 in the ASCII chart.
	cout << "x = 120 in the ASCII chart." << endl;
	cout << "a = " << a << endl;
	cout << "a + a = " << a + a << endl;
	cout << endl;
}

void padding1() { //Memory alignment and padding @ http://www.cplusplus.com/forum/articles/31027/
	struct foo {
		char c;
		short s;
		void* p;
		int i;
	};
	cout << "sizeof(foo) = " << sizeof(foo) << endl;
	foo f;
	cout << "address of c: " << reinterpret_cast<void*>(&f.c) << endl;
	cout << "address of s: " << reinterpret_cast<void*>(&f.s) << endl;
	cout << "address of p: " << reinterpret_cast<void*>(&f.p) << endl;
	cout << "address of i: " << reinterpret_cast<void*>(&f.i) << endl;
	cout << "distance between s and c: " << reinterpret_cast<char*>(&f.s) - reinterpret_cast<char*>(&f.c) << endl;
	cout << "distance between p and s: " << reinterpret_cast<char*>(&f.p) - reinterpret_cast<char*>(&f.s) << endl;
	cout << "distance between p and c: " << reinterpret_cast<char*>(&f.p) - reinterpret_cast<char*>(&f.c) << endl;
	cout << "distance between i and p: " << reinterpret_cast<char*>(&f.i) - reinterpret_cast<char*>(&f.p) << endl;
	cout << endl;
}

void padding2() { //Optimizing C++/Code optimization/Faster operations @ https://en.wikibooks.org/wiki/Optimizing_C%2B%2B/Code_optimization/Faster_operations#Structure_fields_order
	struct foo1 {
		bool b;
		double d;
		short s;
		int i;
	};
	cout << "sizeof(foo1) = " << sizeof(foo1) << endl;
	struct foo2 {
		double d;
		int i;
		short s;
		bool b;
	};
	cout << "sizeof(foo2) = " << sizeof(foo2) << endl;
	cout << endl;
}

int main() {
	sizeofOperator1();
	sizeofOperator2();
	sizeofOperator3();
	ASCIIchart();
	padding1();
	padding2();
	system("pause");
	return 0;
}