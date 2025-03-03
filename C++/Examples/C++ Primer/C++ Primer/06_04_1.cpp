#ifdef  ON

#include <iostream>
using namespace std;

namespace _1 {
	string read();
	void print(const string &);
	void print(double); // overloads the print function

	void fooBar(int ival) {
		//TEST bool read = false; //																																							new scope: hides the outer declaration of read
		//TEST!!! string s = read(); //																																							error: read is a bool variable, not a function

		//																																														bad practice: usually it’s a bad idea to declare functions at local scope
		//TEST! void print(int); //																																								new scope: hides previous instances of print
		//TEST!! print("Value: "); //																																							error: print(const string &) is hidden
		//TEST!! print(ival); //																																								ok: print(int) is visible
		//TEST!!! print(3.14); //																																								ok: calls print(int); print(double) is hidden
	}
}

namespace _2 {
	void print(const string &);
	void print(double); // overloads the print function
	void print(int); // another overloaded instance
	
	void fooBar2(int ival) {
		print("Value: "); // calls print(const string &)
		print(ival); // calls print(int)
		print(3.14); // calls print(double)
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif
