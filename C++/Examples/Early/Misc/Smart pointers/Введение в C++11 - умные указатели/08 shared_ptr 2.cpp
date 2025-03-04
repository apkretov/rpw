#include "stdafx.h" //Введение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::shared_ptr;

class Foo { 
public: 
	Foo() { cout << "Foo" << endl; }
	~Foo() { cout << "~Foo" << endl; }
	void bar() { cout << "Foo::bar()" << endl; } 
};

int main() { //Также как и unique_ptr, и auto_ptr, данный класс предоставляет методы get() и reset().
	auto ptr = std::make_shared<Foo>();
	Foo *foo = ptr.get();
	foo->bar();
	ptr.reset();
	ptr->bar(); //TEST: It strangely works...
	return 0;
}