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
	void bar() { cout << "Foo::bar()" << endl; } 
};

int main() { //��� auto_ptr, ��� � unique_ptr �������� �������� reset(), ������� ���������� ����� ��������, � get(), ������� ���������� ����� (������������) ���������.
	unique_ptr<Foo> ptr = unique_ptr<Foo> (new Foo);
	ptr->bar(); //TEST
	Foo* foo = ptr.get(); // �������� ������������ ���������
	foo->bar(); //TEST
	ptr.reset(); // ���������� ����� ��������
	ptr->bar(); //TEST: It strangely works...
	return 0;
}