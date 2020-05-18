#include "stdafx.h"

template<class T> void f() { T::x * p; ... } 

//��������� T::x * p ����� �������� ��� ����. //�������� ����� typename @ http://alenacpp.blogspot.ru/2006/08/typename.html
//������: x - ��� ��� ������ ����, � ��� ��������� ���� ���������� ��������� p. 
//������: x - ��� ����������� ����������, � * - ��� ���� ���������. ����� p - ��� ���� �����-�� ����������.
//�������� ����� typename �������� ��� �������������, ���� ������ �����������, ��� ���� ���� � ����.
//template<class T> void f() { typename T::x * p; } 

//The keyword typename was introduced to specify that the identifier that follows is a type. Consider the following example: //Officially, what is typename for? @ http://stackoverflow.com/questions/1600936/officially-what-is-typename-for
template <class T>
class MyClass {
	typename T::SubType * ptr;
};
//Here, typename is used to clarify that SubType is a type of class T. Thus, ptr is a pointer to the type T::SubType. Without typename, SubType would be considered a static member. Thus
//T::SubType * ptr
//would be a multiplication of value SubType of type T with ptr.

void myTest() {
	typename int* ptr;
}

int main() {
	myTest();
	return 0;
}

