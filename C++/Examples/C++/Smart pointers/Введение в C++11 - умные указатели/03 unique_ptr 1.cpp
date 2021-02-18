#include "stdafx.h" //¬ведение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::unique_ptr;

int main() { //¬ отличие от auto_ptr, unique_ptr запрещает копирование.
	unique_ptr<int> x_ptr(new int(42));
	unique_ptr<int> y_ptr;
	cout << "*x_ptr = " << *x_ptr << endl;
	//ORIG y_ptr = x_ptr; // ошибка при компил€ции
	//ORIG unique_ptr<int> z_ptr(x_ptr); // ошибка при компил€ции
   return 0;
}

