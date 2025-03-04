#include "stdafx.h" //�������� � C++11: ����� ��������� @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::shared_ptr;

class Bar;

class Foo {
	int intArray[1000000];
public:
    Foo() { std::cout << "Foo()" << std::endl; }
    ~Foo() { std::cout << "~Foo()" << std::endl; }
    shared_ptr<Bar> bar;
};

class Bar {
public:
    Bar() { std::cout << "Bar()" << std::endl; }
    ~Bar() { std::cout << "~Bar()" << std::endl; }
    shared_ptr<Foo> foo;
};

int main() { //����������� ����������� - ������ foo ��������� �� bar � ��������. ��������� ����, ��-�� �������� �� ��������� ����������� ��������. ������ ��������� ����? ��� ������ �� ����� ������������ ��������� ������ foo. ��� ����������� foo ������� ������ �� ��� ������ ���������� �� �������. ������, ������ ���������� �� �����, ��� ��� �� ���� ���� ������ �� ������� ������� bar. � �� bar ���� ������ �� ������� ���� �� ������� foo.
	for (int i = 0; i < 1000; i++) { //Memory leak demonstration.
		auto foo = std::make_shared<Foo>();
		foo->bar = std::make_shared<Bar>();
		foo->bar->foo = foo;
	}
	return 0;
}
