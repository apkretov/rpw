#ifdef EX_16_14

#include "../../stdafx.h"
using namespace std;

using pos = string::size_type;

template <pos HT, pos WD> class Screen { //VER1 // Based on class Screen { //VER7 //TEST!
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

int main(int argc, char *argv[]) {
	print_file_line();

	constexpr pos ht = 5;
	constexpr pos wd = 5;
	Screen<ht, wd> myScreen('X'); //TEST!
	myScreen.display(cout);
	try {
		cout << "\n\nmyScreen.get(ht, wd) = " << myScreen.get(ht, wd); // Generate an error.
	}
	catch (const out_of_range &e) {
		log_by_clog(string("Error: ") + e.what());
	}

	return 0;
}
#endif