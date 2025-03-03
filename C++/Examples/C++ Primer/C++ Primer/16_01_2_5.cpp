#ifdef EX_16_15

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef EX_16_14
using pos = string::size_type;

#ifndef EX_16_15 // The forward declarations that can be omitted in the given context.
template <pos HT, pos WD> class Screen;
template <pos HT, pos WD> ostream &operator<<(ostream &, const Screen<HT, WD> &); //TEST!
#endif

template <pos HT, pos WD> class Screen { //VER2
#ifndef EX_16_15
	friend ostream &operator<< <HT, WD>(ostream &, const Screen<HT, WD> &); //TEST!
#endif
public:
	Screen() = default; // needed because Screen has another constructor
	explicit Screen(char c) : contents(HT *WD, c) {} // cursor initialized to 0 by its in-class initializer

	char get() const { // get the character at the cursor // implicitly inline
		return contents[cursor];
	}
#ifdef ORIG
	inline char get(pos ht, pos wd) const; // explicitly inline
#else //MINE
	char get(pos ht, pos wd) const;
#endif
	Screen &move(pos r, pos c); // can be made inline later
	void some_member() const;
	Screen &set(char);
	Screen &set(pos, pos, char);

	Screen &display(ostream &os) { // display overloaded on whether the object is const or not
		do_display(os);
		return *this;
	}

	const Screen &display(ostream &os) const {
		do_display(os);
		return *this;
	}

private:
	pos cursor = 0;
	pos height = HT; // using type alias to declare a type member
	pos width = WD;
	string contents;
	mutable size_t access_ctr{}; //	may change even in a const object

	void do_display(ostream &os) const { // function to do the work of displaying a Screen
		os << contents;
	}
};

template <pos HT, pos WD>
#ifdef ORIG
char Screen<HT, WD>::get(pos r, pos c) const { // declared as inline in the class
#else //MINE
inline char Screen<HT, WD>::get(pos r, pos c) const {
#endif
	pos row = r * width; // compute row location
	//ORIG return contents[row + c]; // return character at the given column
	return contents.at(row + c); //MINE // return character at the given column
}

template <pos HT, pos WD>
void Screen<HT, WD>::some_member() const {
	++access_ctr; // keep a count of the calls to any member function
	// whatever other work this member needs to do
}

template <pos HT, pos WD>
inline // we can specify inline on the definition
Screen<HT, WD> &Screen<HT, WD>::move(pos r, pos c) {
	pos row = r * width; // compute the row location
	cursor = row + c; // move cursor to the column within that row
	return *this; // return this object as an lvalue
}

template <pos HT, pos WD>
inline Screen<HT, WD> &Screen<HT, WD>::set(char c) {
	contents[cursor] = c; // set the new value at the current cursor location
	return *this; // return this object as an lvalue
}

template <pos HT, pos WD>
inline Screen<HT, WD> &Screen<HT, WD>::set(pos r, pos col, char ch) {
	contents[r * width + col] = ch; // set specified location to given value
	return *this; // return this object as an lvalue
}
#endif

template <pos HT, pos WD>
ostream &operator<<(ostream &os, const Screen<HT, WD> &s) { //TEST!
	s.do_display(os);
	return os;
}

int main(int argc, char const *argv[]) {
	print_file_line();

	Screen<5, 5> s('A');
	cout << s << '\n';

	return 0;
}
#endif
