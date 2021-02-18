#include "stdafx.h" //�������� � C++11: ����� ��������� @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::auto_ptr;
#include <vector>
using std::vector;

int main() {
	auto_ptr<int> x_ptr(new int(42));
	vector<auto_ptr<int>> vec;
	cout << "*x_ptr = " << *x_ptr << endl;
	//ORIG auto_ptr<int> tmp = vec[0]; //������� ������� ������� ����������
	//ORIG cout << *vec[0] << endl;
	return 0;
}

