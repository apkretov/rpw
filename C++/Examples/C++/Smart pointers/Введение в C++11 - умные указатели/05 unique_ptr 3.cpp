#include "stdafx.h" //Введение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
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

int main() { //Как auto_ptr, так и unique_ptr обладают методами reset(), который сбрасывает права владения, и get(), который возвращает сырой (классический) указатель.
	unique_ptr<Foo> ptr = unique_ptr<Foo> (new Foo);
	ptr->bar(); //TEST
	Foo* foo = ptr.get(); // получаем классический указатель
	foo->bar(); //TEST
	ptr.reset(); // сбрасываем права владения
	ptr->bar(); //TEST: It strangely works...
	return 0;
}