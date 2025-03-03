#ifdef ON

#include <iostream>
#include <algorithm>
using namespace std;

constexpr auto get_size = []() -> size_t { return 10; }; //MINE

void new_and_Arrays() {
	// call get_size to determine how many ints to allocate
	//TEST! int *pia = new int[get_size()]; //																																					pia points to the first of these ints

	typedef int arrT[42]; // arrT names the type array of 42 ints
	//TEST! int *p = new arrT; // allocates an array of 42 ints; p points to the first one
	
	{
		int *p = new int[42];
		//TEST! copy(cbegin(p), cend(p), ostream_iterator<int>(cout, " "));
	}
}

void Initializing_an_Array_of_Dynamically_Allocated_Objects() {
	int *pia = new int[10]; // block of ten uninitialized ints
	//TEST! int *pia2 = new int[10](); //																																						block of ten ints value initialized to 0
	string *psa = new string[10]; // block of ten empty strings
	string *psa2 = new string[10](); // block of ten empty strings

	int *pia3 = new int[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //																																	block of ten ints each initialized from the corresponding initializer
	//TEST! string *psa3 = new string[10]{"a", "an", "the", string(3,'x')}; //																													block of ten strings; the first four are initialized from the given initializers // remaining elements are value initialized
}

void It_Is_Legal_to_Dynamically_Allocate_an_Empty_Array() {
	size_t n = get_size(); // get_size returns the number of elements needed
	int *p = new int[n]; // allocate an array to hold the elements
	for (int *q = p; q != p + n; ++q)
		/* process the array */;

	//TEST! char arr[0]; //																																										error: cannot define a zero-length array
	//TEST! char *cp = new char[0]; // 																																							ok: but cp can’t be dereferenced
}

void Freeing_Dynamic_Arrays() {
	auto p = new int; //MINE
	auto pa = new int[0]; //MINE

	delete p; // p must point to a dynamically allocated object or be null
	//TEST delete[] pa; //																																										pa must point to a dynamically allocated array or be null

	{
		typedef int arrT[42]; // arrT names the type array of 42 ints
		int *p = new arrT; // allocates an array of 42 ints; p points to the first one
		delete[] p; // brackets are necessary because we allocated an array
	}
}

void Smart_Pointers_and_Dynamic_Arrays() {
	unique_ptr<int[]> up(new int[10]); //TEST //																																				up points to an array of ten uninitialized ints
	up.release(); //TEST! // automatically uses delete[] to destroy its pointer

#ifdef OFF
	for (size_t i = 0; i != 10; ++i)
		up[i] = i; //TEST! // assign a new value to each of the elements
#endif

	shared_ptr<int> sp(new int[10], [](int *p) { delete[] p; }); //TEST! //																														to use a shared_ptr we must supply a deleter
	//TEST! shared_ptr<int[]> p(new int[10], [](int *p) {delete[] p; }); //MINE //																												GPT: both shared_ptr<int[]> and shared_ptr<int> are correct ways to create a shared_ptr to an array of int
#ifdef OFF
	sp.reset(); // uses the lambda we supplied that uses delete[] to free the array
#endif

#ifndef OFF
	for (size_t i = 0; i != 10; ++i) // shared_ptrs don’t have subscript operator and don’t support pointer arithmetic
		*(sp.get() + i) = i; //TEST! // use get to get a built-in pointer
#endif
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//new_and_Arrays();
	//Initializing_an_Array_of_Dynamically_Allocated_Objects();
	Smart_Pointers_and_Dynamic_Arrays();

	return 0;
}
#endif

#ifdef EX_12_23

#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr char c1[] = {"One"}, c2[] = {"Two"};
	const auto sz1 = strlen(c1), sz2 = strlen(c2);
	
	char *const c3 = new char[sz1 + sz2 + 1];
	auto pa{c3};

	auto cat = [&pa](const char c[], const size_t sz) {
		for (size_t i = 0; i < sz; ++i)
			*pa++ = c[i];
		};
	cat(c1, sz1);
	cat(c2, sz2);
	*pa = '\0';

	cout << c3 << '\n';
	delete[] c3;

	string s1{c1}, s2(c2), s3;
	s3 = s1 + s2;
	cout << s3 << '\n';

	return 0;
}
#endif