#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

void The_allocator_Class() {
	constexpr size_t n{10}; //MINE
#ifdef OFF
	{
		string *const p = new string[n]; // construct n empty strings
		string s;
		string *q = p; // q points to the first string

		while (cin >> s && q != p + n)
			*q++ = s; // assign a new value to *q

		const size_t size = q - p; // remember how many strings we read
		// use the array

		delete[] p; // p points to an array; must remember to use delete[]
	}
#endif
	{
		allocator<string> alloc; // object that can allocate strings
		auto const p = alloc.allocate(n); //TEST! //																																					allocate n unconstructed strings

#ifndef allocators_Allocate_Unconstructed_Memory
		auto q = p; // q will point to one past the last constructed element
#ifdef ORIG
		alloc.construct(q++); //																																										*q is the empty string
		alloc.construct(q++, 10, 'c'); //																																								*q is cccccccccc
		alloc.construct(q++, "hi"); // 																																									*q is hi!
#else MINE // std::construct_at - cppreference.com @ https://en.cppreference.com/w/cpp/memory/construct_at
		construct_at(q++); 
		construct_at(q++, 10, 'c'); //TEST! 
		construct_at(q++, "hi"); 

		auto r = p;
		while (r != q)
			cout << *r++ << '\n';
#endif

		cout << *p << endl; //																																											ok: uses the string output operator
		cout << *q << endl; //TEST! //																																									disaster: q points to unconstructed memory!

		while (q != p)
			//ORIG alloc.destroy(--q); //																																								free the strings we actually allocated
			destroy_at(--q); //TEST! //MINE // std::destroy_at - cppreference.com @ https://en.cppreference.com/w/cpp/memory/destroy_at

		alloc.deallocate(p, n); //TEST! 
#endif
	}
}

void Algorithms_to_Copy_and_Fill_Uninitialized_Memory() {
	vector<int> vi = {0, 1, 2, 3, 4}; //MINE
	allocator<int> alloc;

	auto p = alloc.allocate(vi.size() * 2); // allocate twice as many elements as vi holds
	auto q = uninitialized_copy(vi.begin(), vi.end(), p); //TEST!! //																																	construct elements starting at p as copies of elements in vi
	uninitialized_fill_n(q, vi.size(), 42); //TEST!! //																																					initialize the remaining elements to 42
}

int main(int argc, char *agrv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	The_allocator_Class();
	//Algorithms_to_Copy_and_Fill_Uninitialized_Memory();

	return 0;
}
#endif

#ifdef EX_12_26_1

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *agrv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr size_t n{10};
	string s;
	allocator<string> alloc;
	
	const auto p = alloc.allocate(n);
	auto q = p, r = p;
	while (cin >> s && q != p + n)
		//TEST! construct_at(q++, s);
	
	while (r != q)
		cout << *r++ << ' ';

	while (q != p)
		//TEST! destroy_at(--q);
	alloc.deallocate(p, n);

	return 0;
}
#endif

#ifdef EX_12_26_2

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	constexpr size_t n{3};
	allocator<string> a;
	auto const p = a.allocate(n);
	auto q{p};
	string s;
	ifstream in(argv[1]);
	
	while (q != p + n && in >> s)
		construct_at(q++, s);

	const size_t size = q - p;
	cout << size << '\n';

	for (size_t i = 0; i < size; ++i)
		cout << p[i] << ' ';
	cout << '\n';

	while (q != p)
		destroy_at(--q);
	a.deallocate(p, n);

	return 0;
}
#endif