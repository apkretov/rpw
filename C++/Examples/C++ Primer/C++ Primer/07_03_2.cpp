#ifdef Overloaded_Functions_and_Friendship
#include "07_03_2.h"
#else
#include "07_03_4.h"
#endif
using namespace std;

#ifndef Functions_That_Return_this
inline Screen__Functions_That_Return_this &Screen__Functions_That_Return_this::set(char c) {
	contents[cursor] = c; // set the new value at the current cursor location
	return *this; // return this object as an lvalue
}

inline Screen__Functions_That_Return_this &Screen__Functions_That_Return_this::set(pos r, pos col, char ch) {
	contents[r * width + col] = ch; // set specified location to given value
	return *this; // return this object as an lvalue
}

inline Screen__Functions_That_Return_this &Screen__Functions_That_Return_this::move(pos r, pos c) { //MINE
	Screen__mutable_Data_Members::move(r, c);
	return *this;
}
#endif

#ifdef ON

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifdef Functions_That_Return_this	
	Screen__Overloading_Based_on_const myScreen;
	myScreen.move(4, 0).set('#'); // move the cursor to a given position, and set that character

	//MINE
	Screen__Overloading_Based_on_const sm, *ptr;
	
	ptr = &sm;
	ptr->move(40, 10);
	
	ptr = &myScreen;
	ptr->move(400, 100);

#elif !Overloading_Based_on_const
/* ORIG
	Screen myScreen(5, 3);
	const Screen blank(5, 3);
*/
	//MINE
	Screen__Overloading_Based_on_const myScreen(5, 3, 'a');
	const Screen__Overloading_Based_on_const blank(5, 3, ' ');

	myScreen.set('#').display(cout); // calls nonconst version
	blank.display(cout); // calls const version
#endif

	return 0;
}
#endif
