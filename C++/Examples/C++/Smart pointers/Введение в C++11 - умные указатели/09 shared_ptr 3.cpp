#include "stdafx.h" //Введение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
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

int main() { //Циклическая зависимость - объект foo ссылается на bar и наоборот. Образован цикл, из-за которого не вызовутся деструкторы объектов. Почему образован цикл? При выходе из блока уничтожаются локальный объект foo. При уничтожении foo счетчик ссылок на его ресурс уменьшится на единицу. Однако, ресурс освобожден не будет, так как на него есть ссылка со стороны ресурса bar. А на bar есть ссылка со стороны того же ресурса foo.
	for (int i = 0; i < 1000; i++) { //Memory leak demonstration.
		auto foo = std::make_shared<Foo>();
		foo->bar = std::make_shared<Bar>();
		foo->bar->foo = foo;
	}
	return 0;
}
