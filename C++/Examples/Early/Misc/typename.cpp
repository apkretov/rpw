#include "stdafx.h"

template<class T> void f() { T::x * p; ... } 

//Выражение T::x * p может означать две вещи. //Ключевое слово typename @ http://alenacpp.blogspot.ru/2006/08/typename.html
//Первая: x - это имя некого типа, а все выражение есть объявление указателя p. 
//Вторая: x - это статическая переменная, а * - это знак умножения. Тогда p - это тоже какая-то переменная.
//Ключевое слово typename разрешит это недоразумение, явно сказав компилятору, что речь идет о типе.
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

