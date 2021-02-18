#include "stdafx.h" 
#include <iostream>
#include <memory> 
using namespace std;

int unique_ptrMove() { //��������� ���� �������� �������� �������������� � ������� ��������������� ������� move @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
	unique_ptr<int> x_ptr(new int(42));
	unique_ptr<int> y_ptr;
	cout << "*x_ptr = " << *x_ptr << endl;
	y_ptr = move(x_ptr); // �����, ��� � � ������ � ``auto_ptr``, ����� �������� ��������� � y_ptr, � x_ptr �������� ��������� �� null pointer
	cout << "*y_ptr = " << *y_ptr << endl;
	return 0;
}

void unique_ptrAssignment () { //std::unique_ptr::operator= @ http://www.cplusplus.com/reference/memory/unique_ptr/operator=/
  unique_ptr<int> foo;
  unique_ptr<int> bar;
  
  foo = unique_ptr<int>(new int (101));  // rvalue
  bar = move(foo);                       // using move
  
  cout << "foo: "; if (foo) cout << *foo << '\n'; else cout << "empty\n";
  cout << "bar: "; if (bar) cout << *bar << '\n'; else cout << "empty\n";
}

int main() { 
	//unique_ptrMove();
	unique_ptrAssignment();
	return 0;
}
