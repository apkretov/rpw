#ifdef ON

#include <algorithm>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

#ifndef Copy_and_Swap_Assignment_Operators_and_Move
#ifndef StrVec_Class_Definition // simplified implementation of the memory allocation strategy for a vector-like class
class StrVec { //VER3 
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { // the allocator member is default initialized
		cout << "Constructor\n"; //MINE
	}
	StrVec(const StrVec &); // copy constructor
	StrVec &operator=(const StrVec &); // copy assignment
#ifndef Move_Operations_Library_Containers_and_Exceptions
	StrVec(StrVec &&) noexcept; // move constructor
	// other members as before
#endif
	StrVec &operator=(StrVec &&) noexcept; //MINE
	~StrVec(); // destructor
	void push_back(const string &); // copy the element
#ifndef Rvalue_References_and_Member_Functions
	void push_back(std::string &&); //TEST!! // move the element
#endif
	size_t size() const {
		return first_free - elements;
	}

	size_t capacity() const {
		return cap - elements;
	}

	string *begin() const {
		return elements;
	}

	string *end() const {
		return first_free;
	}
	// ...
private:
	static allocator<string> alloc; // allocates the elements

	void chk_n_alloc() { // used by functions that add elements to a StrVec
		if (size() == capacity())
			reallocate();
	}

	// utilities used by the copy constructor, assignment operator, and destructor
	pair<string *, string *> alloc_n_copy(const string *, const string *);
	void free(); // destroy the elements and free the space
	void reallocate(); // get more space and copy the existing elements
	string *elements; // pointer to the first element in the array
	string *first_free; // pointer to the first free element in the array
	string *cap; // pointer to one past the end of the array
};

allocator<string> StrVec::alloc; // alloc must be defined in the StrVec implmentation file
#endif

#ifndef Using_construct
void StrVec::push_back(const string &s) {
	cout << "push_back(const string &s)\n"; //MINE
	chk_n_alloc(); // ensure that there is room for another element
#ifdef ORIG
	alloc.construct(first_free++, s); // construct a copy of s in the element to which first_free points
#elif! CPP20
	construct_at(first_free++, s); // construct a copy of s in the element to which first_free points
#endif
}
#endif

#ifndef Rvalue_References_and_Member_Functions
void StrVec::push_back(string &&s) { //TEST!
	cout << "push_back(string &&)\n"; //MINE
	chk_n_alloc(); // reallocates the StrVec if necessary
#ifdef ORIG
	alloc.construct(first_free++, std::move(s));
#else
	construct_at(first_free++, std::move(s));
#endif
}
#endif

#ifndef The_alloc_n_copy_Member
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e) { // allocate space to hold as many elements as are in the range
	auto data = alloc.allocate(e - b);
	return {data, uninitialized_copy(b, e, data)}; // initialize and return a pair constructed from data and the value returned by uninitialized_copy
}
#endif

#ifndef The_free_Member
void StrVec::free() {
	if (elements) { // may not pass deallocate a 0 pointer; if elements is 0, there�s no work to do
		for (auto p = first_free; p != elements; /* empty */) // destroy the old elements in reverse order
#ifdef ORIG
			alloc.destroy(--p);
#elif! CPP20
			destroy_at(--p);
#endif
		alloc.deallocate(elements, cap - elements);
	}
}
#endif

#ifndef Copy_Control_Members
StrVec::StrVec(const StrVec &s) {
	cout << "Copy constructor\n"; //MINE
	auto newdata = alloc_n_copy(s.begin(), s.end()); // call alloc_n_copy to allocate exactly as many elements as in s
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() {
	free();
}

StrVec &StrVec::operator=(const StrVec &rhs) {
	cout << "Copy-assignment operator\n"; //MINE
	auto data = alloc_n_copy(rhs.begin(), rhs.end()); // call alloc_n_copy to allocate exactly as many elements as in rhs
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
#endif

#ifndef Move_Iterators
void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1; // allocate space for twice as many elements as the current size
	auto first = alloc.allocate(newcapacity);
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first); // move the elements
	free(); // free the old space
	elements = first; // update the pointers
	first_free = last;
	cap = elements + newcapacity;
}
#endif

#ifndef Move_Constructor_and_Move_Assignment
StrVec::StrVec(StrVec &&s) noexcept // move won�t throw any exceptions
	: elements(s.elements), first_free(s.first_free), cap(s.cap) { // member initializers take over the resources in s
	cout << "Move constructor\n"; //MINE
	s.elements = s.first_free = s.cap = nullptr; // leave s in a state in which it is safe to run the destructor
}
#endif

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
	cout << "Move-assignment operator\n"; //MINE
	if (this != &rhs) { // direct test for self-assignment
		free(); // free existing elements
		elements = rhs.elements; // take over resources from rhs
		first_free = rhs.first_free;
		cap = rhs.cap;
		// leave rhs in a destructible state
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}
#endif

void Rvalue_References_and_Member_Functions() {
	StrVec vec; // empty StrVec
	string s = "some string or another";
	vec.push_back(s); // calls push_back(const string&)
	vec.push_back("done"); // calls push_back(string&&)
	vec.push_back(std::move(s)); //MINE
}

#ifndef Rvalue_and_Lvalue_Reference_Member_Functions
class Foo {
public:
	Foo &operator=(const Foo &) &; //TEST! //																																							may assign only to modifiable lvalues
	// other members of Foo
	//TEST! Foo someMem() &const; //																																									error: const qualifier must come first
	//TEST! Foo anotherMem() const &; //																																								ok: const qualifier comes first
#ifndef Overloading_and_Reference_Functions
	Foo sorted() &&; //TEST!! //																															may run on modifiable rvalues
	Foo sorted() const &; //TEST!! //																														may run on any kind of Foo
private:
	vector<int> data;
#endif
};

Foo &Foo::operator=(const Foo &rhs) & {
	// do whatever is needed to assign rhs to this object
	return *this;
}

#ifndef Overloading_and_Reference_Functions
Foo Foo::sorted() && { // this object is an rvalue, so we can sort in place
	cout << "Foo::sorted() &&\n"; //MINE
	sort(data.begin(), data.end());
	return *this;
}

Foo Foo::sorted() const & { // this object is either const or it is an lvalue; either way we can�t sort in place
	cout << "Foo::sorted() const &\n"; //MINE
	Foo ret(*this); //TEST! //																																											make a copy
	sort(ret.data.begin(), ret.data.end()); // sort the copy
	return ret; // return the copy
}
#endif

static Foo &retFoo() { //MINE
	Foo f;
	return f;
}

static Foo retVal() { //MINE
	Foo f;
	return f;
}

void Rvalue_and_Lvalue_Reference_Member_Functions_() {
	string s1 = "a value", s2 = "another";
	auto n = (s1 + s2).find('a'); //TEST
	cout << "n = " << n << '\n'; //MINE

	s1 + s2 = "wow!"; //TEST!
	cout << (s1 + s2 = "wow") << '\n'; //TEST! //MINE

	Foo &retFoo(); // returns a reference; a call to retFoo is an lvalue
	Foo retVal(); // returns by value; a call to retVal is an rvalue
	Foo i, j; // i and j are lvalues
	i = j; //																																															ok: i is an lvalue
	retFoo() = j; //TEST!! //																																											ok: retFoo() returns an lvalue 
	//TEST! retVal() = j; //																																											error: retVal() returns an rvalue
	i = retVal(); //TEST!! //																																											ok: we can pass an rvalue as the right-hand operand to assignment
}
#endif

void Overloading_and_Reference_Functions_() {
	retVal().sorted(); //TEST! //																																										retVal() is an rvalue, calls Foo::sorted() &&
	retFoo().sorted(); //TEST! //																																										retFoo() is an lvalue, calls Foo::sorted() const &

	{
		class Foo {
		public:
			Foo sorted() &&;
			//TEST! Foo sorted() const; //																																								error: must have reference qualifier
			// Comp is type alias for the function type (see � 6.7 (p. 249))
			// that can be used to compare int values
			using Comp = bool(const int &, const int &);
			Foo sorted(Comp *); //TEST! //																																								ok: different parameter list
			Foo sorted(Comp *) const; //TEST! //																																						ok: neither version is reference qualified
		};
	}
}

void mine1() { //TEST!
	cout << "mine1()\n";

	struct s {
		int i;
		void fnc() {
			cout << "fnc(): i = " << ++i << '\n';
		};
		void fnc() const {
			cout << "fnc() const: i = " << i << '\n';
		};
	};

	s s1{111};
	const s s2{111};
	s1.fnc();
	s2.fnc();
}

void mine2() { //TEST!
	cout << "\nmine2()\n";

	struct s {
		int i;
		void fnc() && {
			cout << "fnc() &&: i = " << ++i << '\n';
		};
		void fnc() const & {
			cout << "fnc() const &: i = " << i << '\n';
		};
	};

	s s1{111};
	const s s2{111};
	s1.fnc();
	s2.fnc();
	std::move(s1).fnc();
}

void mine3() { //TEST!
	cout << "\nmine3()\n";

	struct s {
		int i;
		void fnc() && {
			cout << "fnc() &&: i = " << i << '\n';
		};
		void fnc() & {
			cout << "fnc() const &: i = " << i << '\n';
		};
	};

	s s1{111};
	s1.fnc();
	std::move(s1).fnc();
}

void mine4() { //TEST!
	cout << "\nmine4()\n";

	struct s {
		int i;

		void fnc() & {
			cout << "fnc() &: i = " << i << '\n';
		};
		void fnc() const & {
			cout << "fnc() const &: i = " << i << '\n';
		};

		void fnc() && {
			cout << "fnc() &&: i = " << i << '\n';
		};
		void fnc() const && {
			cout << "fnc() const &&: i = " << i << '\n';
		};
	};

	s s1{111};
	s1.fnc();
	std::move(s1).fnc();

	const s s2{111};
	s2.fnc();
	std::move(s2).fnc();
}

int main(int argc, char *argv[]) {
	print_file_line();

	//Rvalue_References_and_Member_Functions();
	//Rvalue_and_Lvalue_Reference_Member_Functions_();
	Overloading_and_Reference_Functions_();
	//mine1();
	//mine2();
	//mine3();
	//mine4();

	return 0;
}
#endif

#ifdef EX_13_55

#include "../../stdafx.h"
#include "13_06_3.h"
#include "14_07.h"

int main(int argc, char *argv[]) {
	print_file_line();

	StrBlob sb;
	string s = "bbb";

	sb.push_back("aaa");
	sb.push_back(s);
	sb.push_back(std::move(s));
	sb.push_back("ccc");
	print(sb);

	cout << "\nb.begin().deref() = " << sb.begin().deref() << '\n';
	auto b = sb.begin(), e = sb.end();
	cout << *b << ' ' << *--e << '\n';

	return 0;
}
#endif

#ifdef EX_13_56

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../stdafx.h"
using namespace std;

class Foo {
public:
	Foo &operator=(const Foo &) &; //																																									may assign only to modifiable lvalues
#ifndef Overloading_and_Reference_Functions
	Foo sorted() &&; // may run on modifiable rvalues
	Foo sorted() const &; // may run on any kind of Foo
private:
	vector<int> data;
#endif
};

Foo &Foo::operator=(const Foo &rhs) & {
	// do whatever is needed to assign rhs to this object
	return *this;
}

Foo Foo::sorted() && { // this object is an rvalue, so we can sort in place
	cout << "sorted() &&\n"; //MINE
	sort(data.begin(), data.end());
	return *this;
}

Foo Foo::sorted() const & { // this object is either const or it is an lvalue; either way we can�t sort in place
	cout << "sorted() const &\n"; //MINE
	Foo ret(*this); //																																													make a copy
#ifndef ORIG
	return ret.sorted();
#elif! MINE
	return std::move(ret).sorted();
#endif
}

static Foo &retFoo() { //MINE
	Foo f;
	return f;
}

static Foo retVal() { //MINE
	Foo f;
	return f;
}

int main(int argc, char *argv[]) {
	print_file_line();

	retFoo().sorted(); //																																												retFoo() is an lvalue, calls Foo::sorted() const &

	return 0;
}
#endif

#ifdef EX_13_57

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../stdafx.h"
using namespace std;

class Foo {
public:
#ifndef Overloading_and_Reference_Functions
	Foo sorted() &&; // may run on modifiable rvalues
	Foo sorted() const &; // may run on any kind of Foo
	//OFF private:
	vector<int> data;
#endif
};

Foo Foo::sorted() && { // this object is an rvalue, so we can sort in place
	cout << "sorted() &&\n"; //MINE
	sort(data.begin(), data.end());
	return *this;
}

Foo Foo::sorted() const & { // this object is either const or it is an lvalue; either way we can�t sort in place
	cout << "sorted() const &\n"; //MINE
	return Foo(*this).sorted();
}

static Foo &retFoo() { //MINE
	Foo f;
	return f;
}

static Foo retVal() { //MINE
	Foo f;
	return f;
}

int main(int argc, char *argv[]) {
	print_file_line();

	Foo a; // Testing the default copy constructor.
	a.data.push_back(111);
	Foo b(a);
	cout << "a.data.front() = " << a.data.front() << '\n'; //MINE
	cout << "b.data.front() = " << b.data.front() << "\n\n"; //MINE

	cout << "retFoo().sorted():\n"; //MINE
	retFoo().sorted(); //																																												retFoo() is an lvalue, calls Foo::sorted() const &

	return 0;
}
#endif