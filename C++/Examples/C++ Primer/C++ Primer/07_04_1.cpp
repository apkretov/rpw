#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
#ifdef Type_Names_Are_Special
	typedef double Money;
	class Account {
	public:
		Money balance() { return bal; } // uses Money from the outer scope
	private:
		typedef double Money; // error: cannot redefine Money
		Money bal;
		// ...
	};

	//MINE
	Account v;
	cout << v.balance() << '\n';
	
#endif
	return 0;
}

#ifndef	Normal_Block_Scope_Name_Lookup_inside_Member_Definitions

// note: this code is for illustration purposes only and reflects bad practice // it is generally a bad idea to use the same name for a parameter and a member
int height; // defines a name subsequently used inside Screen

class Screen {
public:
	typedef std::string::size_type pos;
	//ORIG void dummy_fcn(pos height) {
	void dummy_fcn_(pos height) { //MINE
		cursor = width * height; // which height? the parameter
	}
	void dummy_fcn(pos height); //MINE
private:
	pos cursor = 0;
	pos height = 0, width = 0;
};

#ifndef _

void Screen::dummy_fcn(pos height) { // bad practice: names local to member functions shouldn’t hide member names
	cursor = width * this->height; //TEST // member height
	// alternative way to indicate the member
	cursor = width * Screen::height; //TEST // member height
}

#elif !After_Class_Scope_Look_in_the_Surrounding_Scope

void Screen::dummy_fcn(pos height) { // bad practice: don’t hide names that are needed from surrounding scopes
	cursor = width * ::height; // which	height ? the global one
}

#endif
#endif
#endif


#ifdef EX_07_34

#include <iostream>
using namespace std;

class Screen {
	pos cursor = 0;
	pos height = 0, width = 0;

public:
	void dummy_fcn(pos height) {
		cursor = width * height;
	}
	
	//TEST!! typedef string::size_type pos;
};

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}

#elif EX_07_34

#include <iostream>
using namespace std;

typedef string Type;
//ORIG Type initVal();
Type initVal() { return ""; } //MINE

class Exercise {
public:
	typedef double Type;
	Type setVal(Type);
	//OIRG Type initVal();
	Type initVal() { return static_cast<Type>(0); }
private:
	int val;
};

//TEST Type Exercise::setVal(Type parm) {
Exercise::Type Exercise::setVal(Type parm) { //MINE
	val = parm + initVal();
	return val;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}

#endif
