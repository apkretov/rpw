#include "stdafx.h" //¬ведение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::shared_ptr;
using std::weak_ptr;

class Foo {
public:
    Foo() { std::cout << "Foo()" << std::endl; }
    ~Foo() { std::cout << "~Foo()" << std::endl; }
	 void doSomething() {cout << "doSomething" << endl; }
};

int main() {
	shared_ptr<Foo> ptr = std::make_shared<Foo>();
	weak_ptr<Foo> w(ptr);
	if (shared_ptr<Foo> foo = w.lock()) foo->doSomething();
	return 0;
}
