#ifdef ON

#include <iostream>
#include <cstdarg> // For ellipsis
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifndef initializer_list_Parameters
void error_msg_1(initializer_list<string> il) { //TEST!!
	for (auto it = il.begin(); it != il.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
}

void error_msg_2(initializer_list<string> il) {
	for (const auto &item : il)
		cout << item << ' ';
	cout << '\n';
}
#endif

/* you.com: 
1) Why get bothered with std::initializer_list while there's std::vector? What's the benefit of the former over the latter?
`std::initializer_list` and `std::vector` are both used to store collections of elements. However, there are some key differences between them which make them useful in different situations.
`std::initializer_list` is a lightweight container that represents a sequence of values, similar to a C-style array. It is particularly useful in situations where you need to pass a variable-length list of arguments to a function or constructor. Because it is a container type, it allows you to use range-based for-loops, like in the example code provided.
`std::vector`, on the other hand, is a more heavyweight container that provides dynamic resizing and other features. It is useful when you need to store a large number of elements and want to take advantage of the container's built-in functionality (such as sorting, searching, or resizing).
When choosing between `std::initializer_list` and `std::vector`, it's important to consider the specific needs of your program. If you only need to store a small number of elements that are known at compile-time (for example, a list of command-line arguments), `std::initializer_list` may be a better choice. If you need more advanced container functionality (such as sorting or dynamic resizing), or if you need to store a large number of elements, `std::vector` is likely the better choice.

2) Are there uses of std::initializer_list other than passing a variable-length list of arguments to a function or constructor?
Yes, there are other uses of std::initializer_list beyond passing a variable-length list of arguments to a function or constructor. Here are some examples:
// Initializing a class member variable:
class MyClass {
public:
	MyClass(std::initializer_list<int> il) : data{il} {}
private:
	std::vector<int> data;
};
MyClass obj {1, 2, 3};
// Returning a collection from a function:
std::initializer_list<int> func() {
	return {1, 2, 3};
}
In general, std::initializer_list can be used anywhere that a fixed set of elements is needed, but where the exact number of elements is not known at compile time.

3) But why in your code snippet did you not use "const std::initializer_list &il" but passed a copy of it? Copying is longer than passing a reference...
You are correct that copying an std::initializer_list may be less efficient than passing a reference, since it involves creating a new copy of the elements stored in the list.
In the provided code snippet, the std::initializer_list is passed by value instead of by reference, which means that a new copy of the list is made within the function. However, in this case, the std::initializer_list is relatively small, and copying it is unlikely to have a noticeable impact on performance.
*/
void mine1(const vector<string> &v) {
	for (const auto &i : v)
		cout << i << ' ';
	cout << '\n';
}

void mine2(const initializer_list<string> &il) {
	for (auto it = il.begin(); it != il.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
}

#ifndef Ellipsis_Parameters
double average(int count, ...) { //TEST!! // C++ program to demonstrate the use of Ellipsis // Function accepting variable number of arguments using Ellipsis // Ellipsis in C++ with Examples - GeeksforGeeks @ https://www.geeksforgeeks.org/ellipsis-in-c-with-examples/
	va_list list; // va_list found in <cstdarg> and list is its type, used to iterate on ellipsis
	va_start(list, count); // Initialize position of va_list
	double avg = 0.0;

	for (int i = 0; i < count; i++) // Iterate through every argument
		avg += static_cast<double>(va_arg(list, int)) / count;
	va_end(list); // Ends the use of va_list

	return avg; // Return the average
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();

	//MINE
	initializer_list<string> err({"aaa", "bbb"});
	error_msg_1(err);
	error_msg_2({"abc", "def"});
	//mine1({"AAA", "BBB"});
	//mine2({"111", "222"});

	//double avg = average(6, 1, 2, 3, 4, 5, 6);
	//cout << "\nAverage is " << avg << '\n';

	return 0;
}
#endif