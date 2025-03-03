#ifdef ON

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include "../../stdafx.h"
using namespace std;

#define Copy_and_Swap_Assignment_Operators_and_Move
#ifdef Copy_and_Swap_Assignment_Operators_and_Move

#ifndef StrVec_Class_Definition // simplified implementation of the memory allocation strategy for a vector-like class
class StrVec { //VER2 
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { // the allocator member is default initialized
		cout << "StrVec constructor\n"; //MINE
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
	chk_n_alloc(); // ensure that there is room for another element
#ifdef ORIG
	alloc.construct(first_free++, s); // construct a copy of s in the element to which first_free points
#elif! CPP20
	construct_at(first_free++, s); // construct a copy of s in the element to which first_free points
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
	if (elements) { // may not pass deallocate a 0 pointer; if elements is 0, there’s no work to do
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
	cout << "StrVec copy-constructor\n"; //MINE
	auto newdata = alloc_n_copy(s.begin(), s.end()); // call alloc_n_copy to allocate exactly as many elements as in s
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() {
	free();
}

StrVec &StrVec::operator=(const StrVec &rhs) {
	cout << "StrVec copy-assignment operator\n"; //MINE
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
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first); //TEST!! //										move the elements
	free(); // free the old space
	elements = first; // update the pointers
	first_free = last;
	cap = elements + newcapacity;
}
#endif

#ifndef Move_Constructor_and_Move_Assignment
/*
you.com
Nevetheless given noexcept, what if an error does occur in the move-constructor?
If an error occurs in the move constructor despite being marked as noexcept, the behavior is not well-defined. The noexcept specifier is a contract between the programmer and the compiler, indicating that the function will not throw any exceptions. However, if an exception is thrown from a noexcept function, it will result in the std::terminate function being called, which typically leads to program termination.
The purpose of marking the move constructor (and move-assignment operator) as noexcept is to inform the library and the compiler that these operations are guaranteed to be exception-safe. This allows the library to optimize certain operations, such as vector reallocation, by using move operations instead of copy operations.
By marking the move constructor as noexcept, we are essentially making a promise that the move constructor will not throw exceptions. If an exception is thrown despite the noexcept specifier, it indicates a violation of this promise and can result in program termination.
It's important to note that marking a function as noexcept does not prevent exceptions from being thrown within the function. It is the responsibility of the programmer to ensure that the move constructor is implemented in a way that does not throw exceptions. If exceptions are possible, it is generally recommended not to mark the move constructor as noexcept.
*/
StrVec::StrVec(StrVec &&s) noexcept // move won’t throw any exceptions
	: elements(s.elements), first_free(s.first_free), cap(s.cap) { // member initializers take over the resources in s
	cout << "StrVec move constructor\n"; //MINE
	s.elements = s.first_free = s.cap = nullptr; // leave s in a state in which it is safe to run the destructor
}
#endif

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
	cout << "StrVec move-assignment operator\n"; //MINE
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

void mine1() {
	StrVec v1;
	v1.push_back("aaa");

	auto v2(v1);
	v2.push_back("bbb");

	StrVec v3;
	v3 = v2;
	v3.push_back("ccc");

	for (const auto &it : v3)
		cout << it << '\t';
	cout << '\n';
}

void mine3() {
	StrVec v1;
	v1.push_back("aaa");
	v1.push_back("bbb");
	v1.push_back("ccc");
	cout << "v1.capacity() = " << v1.capacity() << '\n';

	StrVec v2(v1);
	cout << "v2.capacity() = " << v2.capacity() << '\n';
}

void The_Synthesized_Move_Operations() { // the compiler will synthesize the move operations for X and hasX
	struct X {
		//ORIG int i; // built-in types can be moved
		int i{}; //MINE
		std::string s; // string defines its own move operations
	};

	struct hasX {
		X mem; // X has synthesized move operations
	};

	X x, x2 = std::move(x); //TEST! //																																										uses the synthesized move constructor
	hasX hx, hx2 = std::move(hx); //TEST! //																																								uses the synthesized move constructor

	//MINE
	X x3{3, "x3"}, x4 = std::move(x3);
	cout << x4.i << '\t' << x4.s << '\n';

	//MINE
	struct Y {
		Y() = default;

		Y(const Y &y) {
			i = y.i;
		}

		int i{};
	};

	struct hasY { // assume Y is a class that defines its own copy constructor but not a move constructor
		hasY() = default;
		hasY(hasY &&) = default;
		Y mem; //TEST! //																																													hasY will have a deleted move constructor
	};

	hasY hy, hy2 = std::move(hy); //TEST! //																																								error: move constructor is deleted
}

StrVec getVec(istream &in) { //MINE
	StrVec v;
	string s;

	while (in >> s)
		v.push_back(s);

	return v;
}

void print(const StrVec &v) { //MINE
	cout << "v.size() = " << v.size() << "\tv.capacity() = " << v.capacity() << '\n';
	copy(cbegin(v), cend(v), ostream_iterator<string>(cout, "\t"));
}

void Rvalues_Are_Moved_Lvalues_Are_Copied() {
	StrVec v1, v2;
	cout << "v1 = v2;\n"; //MINE
	v1 = v2; //TEST! //																																														v2 is an lvalue; copy assignment

	//MINE
	cout << "\nauto v3(v2);\n";
	auto v3(v2); //TEST!
	cout << "\nStrVec v4 = std::move(v3);\n";
	StrVec v4 = std::move(v3); //TEST!

	StrVec getVec(istream &); // getVec returns an rvalue
	cout << "\nv2 = getVec(cin);\n"; //MINE
	v2 = getVec(cin); //TEST! //																																											getVec(cin) is an rvalue; move assignment
	print(v2); //MINE

	cout << '\n';
}

void mine2() {
	cout << "auto v = getVec(cin);\n";
	StrVec v = getVec(cin);
	print(v);
}

void But_Rvalues_Are_Copied_If_There_Is_No_Move_Constructor() {
	class Foo {
	public:
		Foo() = default;
		//ORIG Foo(const Foo &); // copy constructor
		Foo(const Foo &) = default; //MINE
		// other members, but Foo does not define a move constructor
	};

	Foo x;
	Foo y(x); // copy constructor; x is an lvalue
	//TEST! Foo z(std::move(x)); //																																											copy constructor, because there is no move constructor
}
#endif

#ifdef Copy_and_Swap_Assignment_Operators_and_Move
#ifndef Writing_Our_Own_swap_Function
class HasPtr {
	friend void swap(HasPtr &, HasPtr &); // other members as in § 13.2.1 (p. 511)
#ifndef Classes_That_Act_Like_Values
	friend ostream &operator<<(ostream &out, const HasPtr &ph); //MINE
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0) {
		cout << "Constructor: *ps = " << *ps << '\n'; //MINE
	}
	
	HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) { //																																each HasPtr has its own copy of the string to which ps points
		cout << "Copy constructor: *p.ps = " << *p.ps << '\n'; //MINE
	} 

#ifdef Copy_and_Swap_Assignment_Operators_and_Move
	HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) {  // added move constructor
		cout << "Move constructor: *p.ps = " << *p.ps << '\n'; //MINE
		p.ps = 0;
	}

	HasPtr &operator=(HasPtr rhs) { //TEST!! //																																					assignment operator is both the move- and copy-assignment operator
		cout << "Copy-move-assigment operator: *this->ps = " << *this->ps << "   *rhs.ps = " << *rhs.ps << '\n'; //MINE
		swap(*this, rhs);
		return *this;
	}
	// other members as in § 13.2.1 (p. 511)
#endif 
	~HasPtr() {
		cout << "Destructor: *ps = " << *ps << '\n'; //MINE
		delete ps;
	}

	//ORIG private:
	string *ps;
	int i;
};

ostream &operator<<(ostream &out, const HasPtr &hp) { //MINE
	out << *hp.ps;
	out << '\t' << hp.i;
	return out;
#endif
};
#endif

#ifndef Using_swap_in_Assignment_Operators
inline void swap(HasPtr &lhs, HasPtr &rhs) {
	using std::swap;
	swap(lhs.ps, rhs.ps); //TEST! //																																								swap the pointers, not the string data
	swap(lhs.i, rhs.i); // 																																											swap the int members
}
#endif

void Copy_and_Swap_Assignment_Operators_and_Move_() {
	//MINE
	HasPtr	hp("aaa");
	HasPtr hp2("bbb"); 

	cout << hp << '\n' << hp2 << '\n'; //MINE
	hp = hp2;
	cout << hp << '\n' << hp2 << '\n'; //MINE
	
	*hp2.ps = "ccc"; //MINE
	cout << '\n' << hp << '\n' << hp2 << '\n'; //MINE

	hp = std::move(hp2);
	cout << hp << '\n'; //MINE
}
#endif

#ifndef Move_Operations_for_the_Message_Class
#ifndef The_Message_Class
class Message {
	friend class Folder;
public: // folders is implicitly initialized to the empty set
	explicit Message(const string &str = "") : contents(str) {}
	Message(const Message &); // copy control to manage pointers to this Message // copy constructor
	Message &operator=(const Message &); // copy assignment
#ifndef Move_Operations_for_the_Message_Class
	Message(Message &&m);
	Message &operator=(Message &&rhs);
	void move_Folders(Message *m); // move the Folder pointers from m to this Message
#endif
	~Message(); // destructor
	void save(Folder &); // add/remove this Message from the specified Folder’s set of messages
	void remove(Folder &);
	//ORIG private:
	string contents; // actual message text
	set<Folder *> folders; // Folders that have this Message
private: //MINE 
	void add_to_Folders(const Message &); // utility functions used by copy constructor, assignment, and destructor // add this Message to the Folders that point to the parameter
	void remove_from_Folders(); // remove this Message from every Folder in folders
};
#endif

class Folder {
	friend class Message;
public:
	void addMsg(Message *);
	void remMsg(Message *);
	//ORIG private:
	set<Message *> messages;
};

#ifndef The_save_and_remove_Members
void Message::save(Folder &f) {
	folders.insert(&f); // add the given Folder to our list of Folders
	f.addMsg(this); //																																										add this Message to f’s set of Messages
}

void Message::remove(Folder &f) {
	folders.erase(&f); // take the given Folder out of our list of Folders
	f.remMsg(this); // remove this Message to f’s set of Messages
}
#endif

#ifndef Copy_Control_for_the_Message_Class
void Message::add_to_Folders(const Message &m) { // add this Message to Folders that point to m
	for (auto f : m.folders) //																																								for each Folder that holds m
		f->addMsg(this); // add a pointer to this Message to that Folder
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
	add_to_Folders(m); // add this Message to the Folders that point to m
}
#endif

#ifndef The_Message_Destructor
void Message::remove_from_Folders() {
	for (auto f : folders) // for each pointer in folders
		f->remMsg(this); // remove this Message from that Folder
	folders.clear(); // no Folder points to this Message
}

Message::~Message() {
	remove_from_Folders();
}
#endif

#ifndef Message_Copy_Assignment_Operator
Message &Message::operator=(const Message &rhs) { // handle self-assignment by removing pointers before inserting them
	remove_from_Folders(); // update existing Folders
	contents = rhs.contents; // copy message contents from rhs
	folders = rhs.folders; // copy Folder pointers from rhs
	add_to_Folders(rhs); // add this Message to those Folders
	return *this;
}
#endif

#ifndef A_swap_Function_for_Message
void swap(Message &lhs, Message &rhs) {
	using std::swap; // not strictly needed in this case, but good habit

	for (auto f : lhs.folders) // remove pointers to each Message from their (original) respective Folders
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	// swap the contents and Folder pointer sets
	swap(lhs.folders, rhs.folders); // uses swap(set&, set&)
	swap(lhs.contents, rhs.contents); // swap(string&, string&)

	for (auto f : lhs.folders) // add pointers to each Message to their (new) respective Folders
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}
#endif

#ifndef Move_Operations_for_the_Message_Class
Message::Message(Message &&m) : contents(std::move(m.contents)) {
	move_Folders(&m); // moves folders and updates the Folder pointers
}

Message &Message::operator=(Message &&rhs) {
	if (this != &rhs) { // direct check for self-assignment
		remove_from_Folders();
		contents = std::move(rhs.contents); // move assignment
		move_Folders(&rhs); // reset the Folders to point to this Message
	}
	return *this;
}

void Message::move_Folders(Message *m) { // move the Folder pointers from m to this Message
	folders = std::move(m->folders); //TEST! // uses set move assignment
	for (auto f : folders) { // for each Folder
		f->remMsg(m); // remove the old Message from the Folder
		f->addMsg(this); // add this Message to that Folder
	}
	m->folders.clear(); //TEST! // ensure that destroying m is harmless
}
#endif

void Folder::addMsg(Message *m) {
	messages.insert(m);
}

void Folder::remMsg(Message *m) {
	messages.erase(m);
}
#endif

void print(const Message &m) {
	cout << "Message contents: " << m.contents << '\n';

	cout << "Folders' messages:\n";
	for (auto f : m.folders)
		for_each(f->messages.cbegin(), f->messages.cend(), [](const Message *p) { cout << p->contents << ' '; });
	cout << "\n\n";
}

Folder inbox, outbox;

Message createMessage() {
	Message m1("Message 1");
	m1.save(inbox);
	print(m1);

	Message m2(std::move(m1));
	print(m2);

	return m2;
}

void mine4() {
	auto m = createMessage();
	print(m);
}

int main(int argc, char *argv[]) {
	print_file_line();

	//mine1();
#ifndef Copy_and_Swap_Assignment_Operators_and_Move
	//The_Synthesized_Move_Operations();
	Rvalues_Are_Moved_Lvalues_Are_Copied();
	//mine2();
#endif
#ifdef Copy_and_Swap_Assignment_Operators_and_Move
	//Copy_and_Swap_Assignment_Operators_and_Move_();
#endif
	mine3();
	//mine4();

	return 0;
}
#endif

#ifdef EX_13_49_StrVec

#include <iostream>
using namespace std;

#ifndef Copy_and_Swap_Assignment_Operators_and_Move
#ifndef StrVec_Class_Definition // simplified implementation of the memory allocation strategy for a vector-like class
class StrVec { //VER2 
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { // the allocator member is default initialized
		cout << "StrVec constructor\n"; //MINE
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
	chk_n_alloc(); // ensure that there is room for another element
#ifdef ORIG
	alloc.construct(first_free++, s); // construct a copy of s in the element to which first_free points
#elif! CPP20
	construct_at(first_free++, s); // construct a copy of s in the element to which first_free points
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
	if (elements) { // may not pass deallocate a 0 pointer; if elements is 0, there’s no work to do
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
#ifndef ORIG
StrVec::StrVec(const StrVec &s) {
	cout << "StrVec copy-constructor\n"; //MINE
	auto newdata = alloc_n_copy(s.begin(), s.end()); // call alloc_n_copy to allocate exactly as many elements as in s
	elements = newdata.first;
	first_free = cap = newdata.second;
}
#else //MINE
StrVec::StrVec(const StrVec &v) {
	cout << "StrVec copy-constructor\n";
	elements = alloc.allocate(v.capacity());
	first_free = uninitialized_copy(v.begin(), v.end(), elements);
	cap = elements + v.capacity();
}
#endif

StrVec::~StrVec() {
	free();
}

#ifdef ORIG
StrVec &StrVec::operator=(const StrVec &rhs) {
	cout << "StrVec copy-assignment operator\n"; //MINE
	auto data = alloc_n_copy(rhs.begin(), rhs.end()); // call alloc_n_copy to allocate exactly as many elements as in rhs
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
#else //MINE
StrVec &StrVec::operator=(const StrVec &rhs) {
	cout << "StrVec copy-assignment operator\n";

	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;

	return *this;
}
#endif
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
#ifdef ORIG
StrVec::StrVec(StrVec &&s) noexcept //TEST!! // move won’t throw any exceptions
	: elements(s.elements), first_free(s.first_free), cap(s.cap) { // member initializers take over the resources in s
	cout << "StrVec move constructor\n"; //MINE
	s.elements = s.first_free = s.cap = nullptr; // leave s in a state in which it is safe to run the destructor
}
#else //MINE
StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap) {
	cout << "StrVec move constructor\n";
	s.elements = s.first_free = s.cap = nullptr;
}
#endif

#ifdef ORIG
StrVec &StrVec::operator=(StrVec &&rhs) noexcept { //TEST!!
	cout << "StrVec move-assignment operator\n"; //MINE
	if (this != &rhs) { // direct test for self-assignment
		free(); // free existing elements
		elements = rhs.elements; // take over resources from rhs
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr; // leave rhs in a destructible state
	}
	return *this;
}
#else //MINE
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
	cout << "StrVec move-assignment operator\n"; //MINE
	if (&rhs != this) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}

	return *this;
}
#endif
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	StrVec v1;
	v1.push_back("aaa");
	v1.push_back("bbb");
	v1.push_back("ccc");
	cout << "v1.capacity() = " << v1.capacity() << '\n';

	StrVec v2(v1);
	cout << "v2.capacity() = " << v2.capacity() << '\n';

	v1 = v2;
	v2 = v2;

	auto v3(std::move(v2));
	v1 = std::move(v3);

	return 0;
}
#endif
#endif

#ifdef EX_13_49_String

#include "13_06_2.h"
using namespace std;

template <typename T>
void print(const string &var, const T &s) {
	cout << var << ":\t" << s << '\t' << s.size() << '\t' << s.capacity() << '\n';
}

#define STRINGIZE(x) #x

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	String s1("test test");
	print(STRINGIZE(s1), s1);

	s1 = s1;
	print(STRINGIZE(s1), s1);

	String s2;
	print(STRINGIZE(s2), s2);

	String s3(s1);
	print(STRINGIZE(s3), s3);

	String s4(s2);
	print(STRINGIZE(s4), s4);
	s4 = s1;
	print(STRINGIZE(s4), s4);
	s4.push_back(" push");
	print(STRINGIZE(s4), s4);

	String s5;
	print(STRINGIZE(s5), s5);
	s5.push_back("push");
	print(STRINGIZE(s5), s5);
	s5.push_back(" push");
	print(STRINGIZE(s5), s5);
	s5.push_back(" push");

	String s6(std::move(s1));
	print(STRINGIZE(s6), s6);

	s6 = std::move(s6);
	print(STRINGIZE(s6), s6); // No problem. s6 = std::move(s6); is a prevented self-assigment. // Warning	C26800	Use of a moved from object : ''s6''.


	s6 = std::move(s3);
	print(STRINGIZE(s6), s6);

	s2 = std::move(s4);
	print(STRINGIZE(s2), s2);

	return 0;
}
#endif

#ifdef EX_13_49_Message

#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

#ifndef The_Message_Class
class Message {
	friend class Folder;
public: // folders is implicitly initialized to the empty set
	explicit Message(const string &str = "") : contents(str) {}
	Message(const Message &); // copy control to manage pointers to this Message // copy constructor
	Message &operator=(const Message &); // copy assignment
	Message(Message &&m);
	Message &operator=(Message &&);
	~Message(); // destructor
	void save(Folder &); // add/remove this Message from the specified Folder’s set of messages
	void remove(Folder &);
	//ORIG private:
	string contents; // actual message text
	set<Folder *> folders; // Folders that have this Message
private: //MINE 
	void add_to_Folders(const Message &); // utility functions used by copy constructor, assignment, and destructor // add this Message to the Folders that point to the parameter
	void remove_from_Folders(); // remove this Message from every Folder in folders
};
#endif

class Folder {
	friend class Message;
public:
	void addMsg(Message *);
	void remMsg(Message *);
	//OFF private:
	set<Message *> messages;
};

#ifndef The_save_and_remove_Members
void Message::save(Folder &f) {
	folders.insert(&f); // add the given Folder to our list of Folders
	f.addMsg(this); //TEST! //																																										add this Message to f’s set of Messages
}

void Message::remove(Folder &f) {
	folders.erase(&f); // take the given Folder out of our list of Folders
	f.remMsg(this); // remove this Message to f’s set of Messages
}
#endif

#ifndef Copy_Control_for_the_Message_Class
void Message::add_to_Folders(const Message &m) { // add this Message to Folders that point to m
	for (auto f : m.folders) //TEST! //																																								for each Folder that holds m
		f->addMsg(this); // add a pointer to this Message to that Folder
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
	add_to_Folders(m); // add this Message to the Folders that point to m
}
#endif

Message::Message(Message &&m) : contents(std::move(m.contents)) {
	cout << "Move-constructor\n";

	for (auto f : m.folders) // remove pointers to each Message from their (original) respective Folders
		f->remMsg(&m);

	folders = std::move(m.folders);
	add_to_Folders(*this);
	m.folders.clear();
}

Message &Message::operator=(Message &&rhs) {
	cout << "Move-assignment operator\n";

	if (&rhs != this) {
		remove_from_Folders();
		contents = std::move(rhs.contents);
		folders = std::move(rhs.folders);

		for (auto f : folders) {
			f->remMsg(&rhs);
			f->addMsg(this);
		}

		rhs.folders.clear();
	}

	return *this;
}

#ifndef The_Message_Destructor
void Message::remove_from_Folders() {
	for (auto f : folders) // for each pointer in folders
		f->remMsg(this); // remove this Message from that Folder
	folders.clear(); // no Folder points to this Message
}

Message::~Message() {
	remove_from_Folders();
}
#endif

#ifndef Message_Copy_Assignment_Operator
Message &Message::operator=(const Message &rhs) { // handle self-assignment by removing pointers before inserting them
	remove_from_Folders(); // update existing Folders
	contents = rhs.contents; // copy message contents from rhs
	folders = rhs.folders; // copy Folder pointers from rhs
	add_to_Folders(rhs); // add this Message to those Folders
	return *this;
}
#endif

#ifndef A_swap_Function_for_Message
void swap(Message &lhs, Message &rhs) { //TEST!
	using std::swap; // not strictly needed in this case, but good habit

	for (auto f : lhs.folders) // remove pointers to each Message from their (original) respective Folders
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	// swap the contents and Folder pointer sets
	swap(lhs.folders, rhs.folders); // uses swap(set&, set&)
	swap(lhs.contents, rhs.contents); // swap(string&, string&)

	for (auto f : lhs.folders) // add pointers to each Message to their (new) respective Folders
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}
#endif

void Folder::addMsg(Message *m) {
	messages.insert(m);
}

void Folder::remMsg(Message *m) {
	messages.erase(m);
}

void print(const Message &m) {
	cout << "Message contents: " << m.contents << '\n';

	cout << "Folders' messages:\n";
	for (auto f : m.folders)
		for_each(f->messages.cbegin(), f->messages.cend(), [](const Message *p) { cout << p->contents << ' '; });
	cout << "\n\n";
}

Folder inbox, outbox;

static Message createMessage() {
	Message m1("Message 1");
	m1.save(inbox);
	print(m1);

	Message m2(std::move(m1));
	print(m2);

	return m2;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	auto m1 = std::move(createMessage());
	print(m1);

	Message m2("Message 2");
	m2.save(inbox);
	m1 = std::move(m2);
	print(m1);

	return 0;
}
#endif

#ifdef EX_13_50

#include <vector>
#include "13_06_2.h"
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<String> v;
	String s("aaa");

	for (int i = 1; i <= 14; ++i) {
		cout << "\npush_back " << i << '\n';
		v.push_back(s);
		cout << "v.size(): " << v.size() << '\t' << "v.capacity(): " << v.capacity() << '\n';
	}

	return 0;
}
#endif

#ifdef EX_13_51
/*
Thanks to moving.
Page 471:
We can copy or assign a unique_ptr that is about to be destroyed.
The most common example is when we return a unique_ptr from a function.
In such cases, the compiler does a special kind of “copy” which we’ll discuss in § 13.6.2 (p. 534).
*/
#endif

#ifndef EX_13_52
// Ref. Copy_and_Swap_Assignment_Operators_and_Move_().
#endif

#ifdef EX_13_53

#include <iostream>
using namespace std;

#ifndef Writing_Our_Own_swap_Function
class HasPtr {
	friend void swap(HasPtr &, HasPtr &); // other members as in § 13.2.1 (p. 511)
#ifndef Classes_That_Act_Like_Values
	friend ostream &operator<<(ostream &out, const HasPtr &ph); //MINE
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0) {
		cout << "Constructor: s = " << s << '\n'; //MINE
	}

	HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) { //																																each HasPtr has its own copy of the string to which ps points
		cout << "Copy constructor: \*p.ps = " << *p.ps << '\n'; //MINE
	}

#ifndef Copy_and_Swap_Assignment_Operators_and_Move
	HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) {  // added move constructor
		cout << "Move constructor: \*p.ps = " << *p.ps << '\n'; //MINE
		p.ps = 0;
	}

	HasPtr &operator=(const HasPtr &rhs) {
		cout << "Copy-assigment operator: *this->ps = " << *this->ps << "   *rhs.ps = " << *rhs.ps << '\n';
		auto temp = new string(*rhs.ps); // Self-assignment protection;
		delete ps;
		ps = temp;
		i = rhs.i;
		return *this;
	}

	HasPtr &operator=(HasPtr &&rhs) noexcept {
		cout << "Move-assigment operator: *this->ps = " << *this->ps << "   *rhs.ps = " << *rhs.ps << '\n';
		if (&rhs != this) { // Self-asignment protection;
			delete ps;
			ps = exchange(rhs.ps, nullptr);
			i = rhs.i;
		}
		return *this;
	}
	// other members as in § 13.2.1 (p. 511)
#endif 
	~HasPtr() {
		delete ps;
	}

	//ORIG private:
	string *ps;
	int i;
};

ostream &operator<<(ostream &out, const HasPtr &hp) { //MINE
	out << *hp.ps;
	out << '\t' << hp.i;
	return out;
#endif
};
#endif

#ifndef Using_swap_in_Assignment_Operators
inline void swap(HasPtr &lhs, HasPtr &rhs) {
	using std::swap;
	swap(lhs.ps, rhs.ps); //																																										swap the pointers, not the string data
	swap(lhs.i, rhs.i); // 																																											swap the int members
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	HasPtr	hp("aaa"), hp2("bbb"); //MINE

	cout << hp << '\n' << hp2 << '\n'; //MINE
	hp = hp2;
	cout << hp << '\n' << hp2 << '\n'; //MINE

	*hp2.ps = "ccc"; //MINE
	cout << '\n' << hp << '\n' << hp2 << '\n'; //MINE

	hp = std::move(hp2);
	cout << hp << '\n'; //MINE


	return 0;
}
#endif
