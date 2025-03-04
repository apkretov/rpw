#include "stdafx.h" //Smart pointers ��� ���������� @ https://habrahabr.ru/post/140222/
#include <iostream>
using std::cout;
using std::endl;

class MyClass {
public:
	MyClass() { cout << "MyClass" << endl; }
	~MyClass() { cout << "~MyClass" << endl; }
	void doSomething() { cout << "doSomething" << endl; };
};

template <typename T> // ����� ������ ������ ���������
class smart_pointer {
	T *m_obj;
public:
	smart_pointer(T* obj) : m_obj(obj) { } // ������ ��� �� �������� ����� ������
	~smart_pointer() { delete m_obj; } // �� ������ �� ������� ��������� ���� ������ �� ���������
	T* operator->() const { return m_obj; } // ������������� ���������< // ��������. ��������� ���������� � ������ ���� T ����������� "���������"
	T& operator*() const { return *m_obj; } // � ������� ������ ��������� �� ����� ������������ ��������� � �������� ������ �� ������, ������� �� ������
};

int main() {
	smart_pointer<MyClass> pMyClass(new MyClass()); // ������ myClass �� �������� ������
	pMyClass->doSomething(); // ���������� � ������ ������ MyClass ����������� ���������
	//ORIG cout << *pMyClass << std::endl; // ��������, ��� ��� ������ ������ ���� ������� ������ ��� � ostream. ��� ������� ����� �� ���������� ������ �������� ������ �� ������, ������� ������ ���� ������� �� �����.
	// �� ������ �� ������ ������ MyClass ����� ������
	return 0;
}

