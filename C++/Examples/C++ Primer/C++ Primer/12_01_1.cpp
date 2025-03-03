#ifdef ON

#include <iostream>
#include <list>
#include "../../stdafx.h"
#include "12_01_1_1.h"
using namespace std;

void The_shared_ptr_Class() {
	shared_ptr<string> p1; // shared_ptr that can point at a string
	shared_ptr<list<int>> p2; // shared_ptr that can point at a list of ints

	if (p1 && p1->empty()) //TEST!! //																																								if p1 is not null, check whether it’s the empty string
		*p1 = "hi"; // if so, dereference p1 to assign a new value to that string
}

void The_make_shared_Function() {
	shared_ptr<int> p3 = make_shared<int>(42); //																																					shared_ptr that points to an int with value 42
	shared_ptr<string> p4 = make_shared<string>(10, '9'); //TEST!! //																																p4 points to a string with value 9999999999
	shared_ptr<int> p5 = make_shared<int>(); //																																						p5 points to an int that is value initialized (§ 3.3.1 (p. 98)) to 0

	auto p6 = make_shared<vector<string>>(); //																																						p6 points to a dynamically allocated, empty vector<string>
}

void Copying_and_Assigning_shared_ptrs() {
	auto p = make_shared<int>(42); //																																								object to which p points has one user
	auto q(p); //TEST!! //																																											p and q point to the same object
	//																																																object to which p and q point has two users
	
	//MINE
	auto s{q}; //TEST!!
	*q = 111; 
	*s = 222; 
	cout << "*p = " << *p << '\n';
	cout << "s.use_count() = " << s.use_count() << '\n';

	auto r = make_shared<int>(42); //																																								int to which r points has one user
	r = q; //TEST! //																																												assign to r, making it point to a different address
	//																																																increase the use count for the object to which q points
	//																																																reduce the use count of the object to which r had pointed
	//																																																the object r had pointed to has no users; that object is automatically freed
}

#ifndef and_Automatically_Free_the_Associated_Memory
struct Foo {}; //MINE

template <typename T> //MINE
shared_ptr<Foo> factory(T arg) { //TEST! // factory returns a shared_ptr pointing to a dynamically allocated object
	// process arg as appropriate
	return make_shared<Foo>(arg); // shared_ptr will take care of deleting this memory
}

template <typename T> //MINE
void use_factory(T arg) {
	shared_ptr<Foo> p = factory(arg);
	// use p
} // p goes out of scope; the memory to which p points is automatically freed

template <typename T> //MINE
shared_ptr<Foo> use_factory(T arg) {
	shared_ptr<Foo> p = factory(arg);
	// use p
	return p; // reference count is incremented when we return p
} // p goes out of scope; the memory to which p points is not freed
#endif

void Classes_with_Resources_That_Have_Dynamic_Lifetime() {
	vector<string> v1; // empty vector
	{ // new scope
		vector<string> v2 = {"a", "an", "the"};
		v1 = v2; // copies the elements from v2 into v1
	} // v2 is destroyed, which destroys the elements in v2
	// v1 has three elements, which are copies of the ones originally in v2
}

void mine() {
	StrBlob b{"aaa", "bbb"};
	b.push_back("ccc");
	auto print_StrBlob = [](StrBlob &b_) {
		cout << "size() = " << b_.size() << '\n';
		cout << "back() = " << b_.back() << '\n';
	};
	cout << "print_StrBlob(b):\n";
	print_StrBlob(b);

	StrBlob b2(b);
	cout << "\nprint_StrBlob(b2):\n";
	print_StrBlob(b2);
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	//The_shared_ptr_Class();
	//The_make_shared_Function();
	//Copying_and_Assigning_shared_ptrs();
	mine();

	return 0;
}
#endif

#ifdef EX_12_01

#include <iostream>
#include "12_01_1_1.h"
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	StrBlob b1;
	{
		StrBlob b2 = {"a", "an", "the"};
		b1 = b2;
		b2.push_back("about");
	}

	return 0;
}
#endif

#ifdef EX_12_02

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
using namespace std;

#ifndef Defining_the_StrBlob_Class
class StrBlob { //VER2 Pointer-like with const added.
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> il);

	size_type size() const {
		return data->size();
	}

	bool empty() const {
		return data->empty();
	}

	void push_back(const string &t) { // add and remove elements
		data->push_back(t);
	}

	void pop_back();
#ifndef EX_12_02
	string &front() const; // element access
	string &back() const;
#endif

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
#endif

#include "12_01_1_2.h" //MINE This header must be here.

#ifndef Element_Access_Members
string &StrBlob::front() const {
	check(0, "front on empty StrBlob"); // if the vector is empty, check will throw
	return data->front();
}

string &StrBlob::back() const {
	check(0, "back on empty StrBlob");
	return data->back();
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const StrBlob cb = {"aaa", "bbb", "ccc"};
	auto b{cb};

	cout << b.front() << '\n';
	cout << b.back() << "\n\n";

	cout << cb.front() << '\n';
	cout << cb.back() << "\n\n";

	b.push_back("b_DDD");
	cout << b.back() << "\n\n";

	auto pcb{&cb};
	const_cast<StrBlob *>(pcb)->push_back("cb_EEE");
	cout << cb.back() << '\n';

	return 0;
}
#endif

#ifdef EX_12_03

#include <iostream>
#include "12_01_1_3.h"
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const StrBlob b = {"aaa", "bbb", "ccc"};

	cout << b.front() << '\n';
	cout << b.back() << '\n';

	b.push_back("DDD");
	cout << b.back() << '\n';

	return 0;
}
#endif