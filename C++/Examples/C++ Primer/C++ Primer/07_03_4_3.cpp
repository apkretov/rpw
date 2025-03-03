#ifdef Overloaded_Functions_and_Friendship

#include <iostream>
#include "../../stdafx.h"
#include "07_03_4.h"
using namespace std;

void Window_mgr::clear(ScreenIndex i) {
	try { //MINE
		//ORIG Screen &s = screens[i]; // s is a reference to the Screen we want to clear
		Screen &s = screens.at(i); //MINE  // s is a reference to the Screen we want to clear
		s.contents = string(s.height * s.width, ' '); // reset the contents of that Screen to all blanks
	} //MINE
	catch (const out_of_range &e) {
		cerr << "Error: " << e.what() << "\tFile: " << __FILE__ << "\tLine: " << __LINE__ << endl;
	}
}

int main(int argc, char *argv[]) {
	print_file_line();

	Window_mgr w;
	w.addScreen(Screen(2, 2, 'a'));
	w.clear(1);

	return 0;
}
#endif

#ifdef Friend_Declarations_and_Scope

#include <iostream>
using namespace std;

struct X {
	friend void f1() {} //TEST! //																																							friend function can be defined in the class body
	X() {
		//TEST! f1(); //																																										error: no declaration for f
	}
	void g();
	void h();
};

void X::g() {
	//TEST! return f(); //																																									error: f hasn’t been declared
}

void f1(); // declares the function defined inside X

void X::h() {
	//TEST return f(); //																																										ok: declaration for f is now in scope
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	X x; //MINE

	return 0;
}
#endif