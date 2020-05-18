#include "stdafx.h" //�������� � C++11: ����� ��������� @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::unique_ptr;

int main() { //� ������� �� auto_ptr, unique_ptr ��������� �����������.
	unique_ptr<int> x_ptr(new int(42));
	unique_ptr<int> y_ptr;
	cout << "*x_ptr = " << *x_ptr << endl;
	//ORIG y_ptr = x_ptr; // ������ ��� ����������
	//ORIG unique_ptr<int> z_ptr(x_ptr); // ������ ��� ����������
   return 0;
}

