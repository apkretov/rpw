#include <iostream>
using namespace std;
#include "12_01_4.h"
using namespace Smart_Pointers_and_Dumb_Classes;
using namespace Using_Our_Own_Deletion_Code;

#ifdef Smart_Pointers_and_Exceptions
#ifndef _1
void f() {
	shared_ptr<int> sp(new int(42)); // allocate a new object
	// code that throws an exception that is not caught inside f
} // shared_ptr freed automatically when the function ends

#elif! _2
void f() {
	int *ip = new int(42); // dynamically allocate a new object
	// code that throws an exception that is not caught inside f
	delete ip; // free the memory before exiting
}
#endif
#endif

#ifndef Smart_Pointers_and_Dumb_Classes
void Smart_Pointers_and_Dumb_Classes::disconnect(connection c) { //MINE
	cout << "Disconnected!\n";
}

connection Smart_Pointers_and_Dumb_Classes::connect(destination *d) { //MINE
	cout << "Connected!\n";
	return connection();
}

void Smart_Pointers_and_Dumb_Classes::f1(destination &d /* other parameters */) {
	connection c = connect(&d); // get a connection; must remember to close it when done
	// use the connection
	// if we forget to call disconnect before exiting f, there will be no way to close c
	cout << "But not disconnected!\n"; //MINE
}
#endif

#ifndef Using_Our_Own_Deletion_Code
void Using_Our_Own_Deletion_Code::end_connection(connection *p) {
	disconnect(*p); 
}

void Using_Our_Own_Deletion_Code::f1(Smart_Pointers_and_Dumb_Classes::destination &d /* other parameters */) {
	connection c = connect(&d);
	shared_ptr<connection> p(&c, end_connection); //TEST!!
	throw(exception("Error at connecting...")); //MINE
	cout << "This should not appear." << endl; //MINE
	// use the connection
	//																																																when f exits, even if by an exception, the connection will be properly closed
#ifndef EX_12_15
	//TEST! shared_ptr<connection> p2(&c, [](connection *p) { disconnect(*p); });
#endif
}
#endif

#ifdef ON
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE
	destination d;
	//Smart_Pointers_and_Dumb_Classes::f(d);
	try {
		Using_Our_Own_Deletion_Code::f(d);
	}
	catch (const exception &e) {
		cerr << e.what() << '\n';
	}

	return 0;
}
#endif
