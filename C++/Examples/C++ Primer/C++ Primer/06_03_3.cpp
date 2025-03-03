#ifdef ON

#include <iostream>
using namespace std;

void Returning_a_Pointer_to_an_Array() {
	typedef int arrT[10]; //																																								arrT is a synonym for the type array of ten ints
	using arrT = int[10]; // 																																								equivalent declaration of arrT; see § 2.5.1 (p. 68)
	//TEST! arrT *func(int i); //																																							func returns a pointer to an array of ten ints
}

#ifdef ON
//TEST! int (*mine(int (&arr)[10]))[10] { 
	return &arr;
}
#endif

void Declaring_a_Function_That_Returns_a_Pointer_to_an_Array() {
	int arr[10]; // arr is an array of ten ints
	int *p1[10]; // p1 is an array of ten pointers
	//TEST! int(*p2)[10] = &arr; //																																							p2 points to an array of ten ints
	//TEST!! int (*func(int))[10]; //																																						Declaring a Function That Returns a Pointer to an Array
	//TEST!! int (*a[10])(int); //MINE																																						This declares an array that contains 10 pointers to functions that take an int parameter and return an int.
	//TEST!! int (*(*b[10])(int))[10]; //MINE																																				Declare an array that contains 10 pointers to functions that take an int parameter and return a pointer to an array of 10 int.

}

void Using_a_Trailing_Return_Type() {
	//TEST! auto func(int i) -> int(*)[10]; //																																				fcn takes an int argument and returns a pointer to an array of ten	ints
}

namespace Using_decltype {
	int odd[] = {1,3,5,7,9};
	int even[] = {0,2,4,6,8};

#ifdef ON
	//TEST! decltype(odd) *arrPtr(int i) { //																																				returns a pointer to an array of five int elements
	return (i % 2) ? &odd : &even; //																																					returns a pointer to the array
}
#endif
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifdef ON
	{ //MINE
		int arr[10]{10};
		//TEST! int(*arr2)[10] = mine(arr);

		for (auto s : *arr2)
			cout << s << ' ';
		cout << '\n';
	}
#endif

	return 0;
}
#endif

#ifdef EX_06_36

#include <iostream>
using namespace std;

#ifdef ON
//TEST! string(&fnc(string (&arr)[10]))[10] {  
	return arr;
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string arr[10]{"one", "two", "three"};

	for (auto &s : fnc(arr))
		cout << s << ' ';
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_06_37

#include <iostream>
using namespace std;

string arr[10]{"one", "two", "three"};

//TEST using ra = string(&)[10]; ra type_alias(ra arr) { return arr; }
//TEST auto trailing_return(string (&arr)[10]) -> string(&)[10] { return arr; }
//TEST decltype(arr) &decltype_(decltype(arr) &arr) { return arr; } 

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifdef ON
	//auto fptr = type_alias;
	//auto fptr = trailing_return;
	// auto fptr = decltype_;

	for (auto &s : fptr(arr))
		cout << s << "| ";
	cout << '\n';
#endif

	return 0;
}
#endif

#ifdef EX_06_38

#include <iostream>
using namespace std;

int even[]{0, 2, 4, 6};
int odd[]{1, 3, 5, 7};

decltype(even) &fcnRef(int i) {
	return i % 2 == 0 ? even : odd;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int in;

	cout << "Enter an even/odd interger to output the even/odd array:\n";
	while (cin >> in) {
		for (auto i : fcnRef(1))
			cout << i << ' ';
		cout << '\n';
	}

	return 0;
}
#endif