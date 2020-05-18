#include "stdafx.h" //Введение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::auto_ptr;

int main() {
	auto_ptr<int> x_ptr(new int(42));
	auto_ptr<int> y_ptr;
	//ORIG y_ptr = x_ptr; // вот это нехороший и неявный момент права владения ресурсов уходят в y_ptr и x_ptr начинает указывать на null pointer
	cout << "*x_ptr = " << *x_ptr << endl; // segmentation fault
	return 0;
}

