#include "stdafx.h" //Smart pointers для начинающих @ https://habrahabr.ru/post/140222/
#include <iostream>
using std::cout;
using std::endl;

class MyClass {
public:
	MyClass() { cout << "MyClass" << endl; }
	~MyClass() { cout << "~MyClass" << endl; }
	void doSomething() { cout << "doSomething" << endl; };
};

template <typename T> // Класс нашего умного указателя
class smart_pointer {
	T *m_obj;
public:
	smart_pointer(T* obj) : m_obj(obj) { } // Отдаем ему во владение некий объект
	~smart_pointer() { delete m_obj; } // По выходу из области видимости этот объект мы уничтожим
	T* operator->() const { return m_obj; } // Перегруженные операторы< // Селектор. Позволяет обращаться к данным типа T посредством "стрелочки"
	T& operator*() const { return *m_obj; } // С помощью такого оператора мы можем разыменовать указатель и получить ссылку на объект, который он хранит
};

int main() {
	smart_pointer<MyClass> pMyClass(new MyClass()); // Отдаем myClass во владение умному
	pMyClass->doSomething(); // Обращаемся к методу класса MyClass посредством селектора
	//ORIG cout << *pMyClass << std::endl; // Допустим, что для нашего класса есть функция вывода его в ostream. Эта функция одним из параметров обычно получает ссылку на объект, который должен быть выведен на экран.
	// по выходу из скоупа объект MyClass будет удален
	return 0;
}

