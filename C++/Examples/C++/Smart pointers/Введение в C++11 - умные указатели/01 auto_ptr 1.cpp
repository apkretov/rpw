#include "stdafx.h" //�������� � C++11: ����� ��������� @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::auto_ptr;

int main() {
	auto_ptr<int> x_ptr(new int(42));
	auto_ptr<int> y_ptr;
	//ORIG y_ptr = x_ptr; // ��� ��� ��������� � ������� ������ ����� �������� �������� ������ � y_ptr � x_ptr �������� ��������� �� null pointer
	cout << "*x_ptr = " << *x_ptr << endl; // segmentation fault
	return 0;
}

