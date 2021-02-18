#include "stdafx.h" //�������� � C++11: ����� ��������� @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::shared_ptr;

int main() { //� ������� �� ������������� ���� ����������, shared_ptr ��������� ������� ������ �� ������. ������ ����������� �����, ����� ������� ������ �� ���� ����� ����� 0.
	shared_ptr<int> x_ptr(new int(42));
	shared_ptr<int> y_ptr(new int(13));
	cout << "*y_ptr = " << *y_ptr << endl; //TEST
	y_ptr = x_ptr; // ����� ���������� ������ �������, ������ �� ������� �������� ����� y_ptr (int(13)) �����������, � �� int(42) ����� ��������� ��� ���������
	cout << "*x_ptr = " << *x_ptr << "\t*y_ptr = " << *y_ptr << endl;
	// int(42) ����������� ���� ��� ����������� ���������� ������������ �� ���� ���������
	return 0;
}