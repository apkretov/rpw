#include "stdafx.h" //Введение в C++11: умные указатели @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/
#include <iostream>
using std::cout;
using std::endl;
#include <memory> 
using std::shared_ptr;

int main() { //В отличие от рассмотренных выше указателей, shared_ptr реализует подсчет ссылок на ресурс. Ресурс освободится тогда, когда счетчик ссылок на него будет равен 0.
	shared_ptr<int> x_ptr(new int(42));
	shared_ptr<int> y_ptr(new int(13));
	cout << "*y_ptr = " << *y_ptr << endl; //TEST
	y_ptr = x_ptr; // после выполнения данной строчки, ресурс на который указывал ранее y_ptr (int(13)) освободится, а на int(42) будут ссылаться оба указателя
	cout << "*x_ptr = " << *x_ptr << "\t*y_ptr = " << *y_ptr << endl;
	// int(42) освободится лишь при уничтожении последнего ссылающегося на него указателя
	return 0;
}