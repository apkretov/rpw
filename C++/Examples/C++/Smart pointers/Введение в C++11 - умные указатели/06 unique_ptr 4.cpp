#include "stdafx.h" //�������� � C++11: ����� ��������� @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::unique_ptr;

class Foo { 
public: 
	Foo() { cout << "Foo" << endl; }
	~Foo() { cout << "~Foo" << endl; }
	void doSomething() { cout << "doSomething" << endl; } 
};

int main() { // ��������� (����� unique_ptr) �� ������������� ��� �������� ���������, �.�. ���������� �������� ������ delete, � �� delete[]. ��� unique_ptr �� ����� ���� � ���������������� �������������� ��� ��������. ��� �� ������������� ���������� ������� [] ����� ��������� �������.
	unique_ptr<Foo[]> arr(new Foo[2]);
	arr[0].doSomething();
	
	cout << endl << "Before arr = nullptr" << endl; //TEST
	arr = nullptr;												//TEST
	cout << "After arr = nullptr" << "\n\n";			//TEST
	
	return 0;
}