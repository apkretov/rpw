#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "16_05_1.h"
using namespace std;

struct Base {
	virtual ~Base() {};
};

struct Derived : Base {};

void The_type_info_Class() {
	int arr[10];
	Derived d;
	Base *p = &d;
	cout << typeid(42).name() << ", "
		<< typeid(arr).name() << ", "
		<< typeid(Sales_data).name() << ", "
		<< typeid(std::string).name() << ", "
		<< typeid(p).name() << ", "
		<< typeid(*p).name() << endl;
}

int main() {
	print_file_line();

	The_type_info_Class();

	return 0;
}
#endif