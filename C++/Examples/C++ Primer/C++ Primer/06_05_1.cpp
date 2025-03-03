#ifdef ON

#include <iostream>
using namespace std;

namespace Default_Arguments {
	typedef string::size_type sz; // typedef see § 2.5.1 (p. 67)
	//OFF string screen(sz ht = 24, sz wid = 80, char backgrnd = ' ');
}

namespace Default_Argument_Declarations {
	using namespace Default_Arguments;

	string screen(sz, sz, char = ' '); //																																						no default for the height or width parameters
	//TEST!!! string screen(sz, sz, char = '*'); //																																				error: redeclaration
	//TEST!! string screen(sz = 24, sz = 80, char); //																																			ok: adds default arguments
}

namespace Default_Argument_Initializers {
	using namespace Default_Arguments;

	sz wd = 80; // the declarations of wd, def, and ht must appear outside a function
	char def = ' ';
	sz ht();
	//TEST! string screen(sz = ht(), sz = wd, char = def); 
	//TEST! string window = screen(); //																																						calls screen(ht(), 80, ' ')

	void f2() {
		def = '*'; //																																											changes the value of a default argument
		sz wd = 100; //																																											hides the outer definition of wd but does not change the default
		//TEST!!! window = screen(); //																																							calls screen(ht(), 80, '*')
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif

#ifdef  EX_06_40

#include <iostream>
using namespace std;

int ff(int v, int b = 0, int c = 0); // (a)
//TEST char *init(int ht = 24, int wd, char bckgrnd); // (b)

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif

#ifdef  EX_06_41

#include <iostream>
using namespace std;

char *init(int ht, int wd = 80, char bckgrnd = ' ');

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//ERR init(); // (a)
	init(24, 10);  // (b)
	//TEST init(14, '*'); // (c)

	return 0;
}
#endif