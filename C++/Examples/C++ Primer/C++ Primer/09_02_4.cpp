#ifdef ON

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <array>
#include <algorithm>
#include <iterator>
using namespace std;

void Initializing_a_Container_as_a_Copy_of_Another_Container() {
	list<string> authors = {"Milton", "Shakespeare", "Austen"}; // each container has three elements, initialized from the given initializers
	vector<const char *> articles = {"a", "an", "the"};

	list<string> list2(authors); //																																									ok: types match
	//TEST! deque<string> authList(authors); //																																						error: container types don’t match
	//TEST! vector<string> words(articles); //																																						error: element types must match
	//TEST! forward_list<string> words(articles.begin(), articles.end()); //																														ok: converts const char* elements to string

#ifdef OFF
	auto it = authors.end(); //MINE
	--it; //MINE
	copy(authors.cbegin(), authors.cend(), ostream_iterator<string>(cout, " ")); cout << '\n'; //MINE
	//TEST! deque<string> authList(authors.begin(), it); //																																			copies up to but not including the element denoted by it
	copy(authList.cbegin(), authList.cend(), ostream_iterator<string>(cout, " ")); cout << '\n'; //MINE
#endif
}

void Library_arrays_Have_Fixed_Size() {
#ifdef OFF
	//TEST array<int, 42> //																																										type is: array that holds 42 ints
	//TEST array<string, 10> //																																										type is: array that holds 10 strings
#endif
		
	array<int, 10>::size_type i; //																																									array type includes element type and size
	//TEST! array<int>::size_type j; //																																								error: array<int> is not a type

	array<int, 10> ia1; // ten default-initialized ints
	array<int, 10> ia2 = {0,1,2,3,4,5,6,7,8,9}; // list initialization
	//TEST array<int, 10> ia3 = {42}; //																																							ia3[0] is 42, remaining elements are 0

	int digs[10] = {0,1,2,3,4,5,6,7,8,9};
	//TEST int cpy[10] = digs; //																																									error: no copy or assignment for built-in arrays
	array<int, 10> digits = {0,1,2,3,4,5,6,7,8,9};
	//TEST array<int, 10> copy = digits; //																																							ok: so long as array types match
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Initializing_a_Container_as_a_Copy_of_Another_Container();

	return 0;
}
#endif