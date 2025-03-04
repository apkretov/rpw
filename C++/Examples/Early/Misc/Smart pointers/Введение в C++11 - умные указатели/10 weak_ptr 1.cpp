#include "stdafx.h" //¬ведение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::shared_ptr;
using std::weak_ptr;

class Bar;

class Foo {
public:
    Foo() { std::cout << "Foo()" << std::endl; }
    ~Foo() { std::cout << "~Foo()" << std::endl; }
    shared_ptr<Bar> bar;
};

class Bar {
public:
    Bar() { std::cout << "Bar()" << std::endl; }
    ~Bar() { std::cout << "~Bar()" << std::endl; }
    weak_ptr<Foo> foo;
};

int main() { //ƒл€ того чтобы разорвать цикл, достаточно в классе Bar заменить shared_ptr на weak_ptr.
	auto foo = std::make_shared<Foo>();
	foo->bar = std::make_shared<Bar>();
	foo->bar->foo = foo;
	return 0;
}
