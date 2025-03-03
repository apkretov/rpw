#ifdef ON

#include <iostream>
using namespace std;

void Pointers_and_Arrays() {
	string nums[] = {"one", "two", "three"}; // array of strings
	string *p = &nums[0]; //TEST //																																									p points to the first element in nums
	//TEST string *p2 = nums; //																																									equivalent to p2 = &nums[0]

	int ia[] = {0,1,2,3,4,5,6,7,8,9}; // ia is an array of ten ints
	//TEST!! auto ia2(ia); //																																										ia2 is an int* that points to the first element in ia

	//TEST ia2 = 42; //																																												error: ia2 is a pointer, and we can’t assign an int to a pointer
	//TEST! auto ia2(&ia[0]); //																																									now it’s clear that ia2 has type int *

	//TEST decltype(ia) ia3 = {0,1,2,3,4,5,6,7,8,9}; //																																				ia3 is an array of ten ints
	//TEST ia3 = p; // 																																												error: can’t assign an int* to an array
	//TEST ia3[4] = i; // 																																											ok: assigns the value of i to an element in ia3
}

void Pointers_Are_Iterators() {
#ifdef ON
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	//TEST!! int *e = &arr[10]; //																																									pointer just past the last element in arr
	for (int *b = arr; b != e; ++b)
		cout << *b << endl; // print the elements in arr
#endif
}

#include <algorithm>
using namespace std;
void The_Library_begin_and_end_Functions() {
	int arr[]{1, 3, -5, 10, 8}; //MINE
	
	//TEST! int *pbeg = begin(arr), *pend = end(arr); //																																			pbeg points to the first and pend points just past the last element in arr
	auto pbeg = cbegin(arr), pend = cend(arr); //TEST! //MINE
	while (pbeg != pend && *pbeg >= 0) // find the first negative element, stopping if we’ve seen all the elements
		++pbeg;
	
	cout << *pbeg << '\n'; //MINE
}

void Pointer_Arithmetic() {
	constexpr size_t sz = 5;
	int arr[sz] = {1,2,3,4,5};
	int *ip = arr; // equivalent to int *ip = &arr[0]
	//TEST int *ip2 = ip + 4; // ip2 points to arr[4], the last element in arr
	
	//TEST int *p = arr + sz; //																																									use caution -- do not dereference!
	//TEST int *p2 = arr + 10; // 																																									error: arr has only 5 elements; p2 has undefined value

	//TEST auto n = end(arr) - begin(arr); //																																						n is 5, the number of elements in arr

	int *b = arr, *e = arr + sz;
	while (b < e) {
		cout << *b << '\n';
		++b;
	}

	{
		int i = 0, sz = 42;
		int *p = &i, *e = &sz;
		//TEST!! while (p < e) ; //																																									undefined: p and e are unrelated; comparison is meaningless!
	}
}

void Subscripts_and_Pointers() {
	int ia[] = {0,2,4,6,8}; // array with 5 elements of type int

	int i = ia[2];	// ia is converted to a pointer to the first element in ia
					// ia[2] fetches the element to which (ia + 2) points
	int *p = ia;	// p points to the first element in ia
	i = *(p + 2);	// equivalent to i = ia[2]
	
	{
		int *p = &ia[2]; //TEST //																																										p points to the element indexed by 2
		//TEST! int j = p[1]; cout << j << '\n'; // 																																					p[1] is equivalent to *(p + 1),
							 // 																																										p[1] is the same element as ia[3]
		//TEST! int k = p[-2]; cout << k << '\n'; // 																																					p[-2] is the same element as ia[0]
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Pointers_and_Arrays();
	//Pointers_Are_Iterators();
	The_Library_begin_and_end_Functions();
	//Pointer_Arithmetic();
	//Subscripts_and_Pointers();

	return 0;
}
#endif

#ifdef EX_03_35

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const size_t sz{10};
	int v[sz];

	for (auto p = v; p < v + sz; ++p)
		*p = 0;

	for (auto p = begin(v); p < end(v); ++p)
		cout << *p << " ";
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_03_36

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int a1[] = {0, 1, 2}, a2[] = {0, 1, 2};
	auto sz1 = end(a1) - begin(a1);
	auto sz2 = end(a2) - begin(a2);

	if (sz1 != sz2)
		cout << "a1 != a2\n";
	else {
		auto p1 = a1, p2 = a2;
		for (; p1 < a1 + sz1; ++p1, p2++)
			if (*p1 != *p2) {
				cout << "a1 != a2\n";
				break;
			}
		if (p1 == a1 + sz1)
			cout << "a1 == a2\n";
	}

	vector<int> v1(a1, a1 + sz1), v2(a2, a2 + sz2);

	if (v1 == v2)
		cout << "v1 == v2\n";
	else if (v1 > v2)
		cout << "v1 > v2\n";
	else
		cout << "v1 < v2\n";

	return 0;
}
#endif