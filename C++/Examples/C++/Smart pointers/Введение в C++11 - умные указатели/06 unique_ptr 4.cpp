#include "stdafx.h" //¬ведение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::unique_ptr;

class Foo { 
public: 
	Foo() { cout << "Foo" << endl; }
	~Foo() { cout << "~Foo" << endl; }
	void doSomething() { cout << "doSomething" << endl; } 
};

int main() { // ”казатели (кроме unique_ptr) не предназначены дл€ владени€ массивами, т.к. деструктор вызывает именно delete, а не delete[]. ƒл€ unique_ptr мы имеем дело с предопределенной специализацией дл€ массивов. ƒл€ ее использовани€ необходимо указать [] возле параметра шаблона.
	unique_ptr<Foo[]> arr(new Foo[2]);
	arr[0].doSomething();
	
	cout << endl << "Before arr = nullptr" << endl; //TEST
	arr = nullptr;												//TEST
	cout << "After arr = nullptr" << "\n\n";			//TEST
	
	return 0;
}