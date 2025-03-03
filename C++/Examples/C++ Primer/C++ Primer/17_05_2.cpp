#ifdef ON

#include <cstdio>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

void Single_Byte_Operations() {
	char ch;
	while (cin.get(ch))
		cout.put(ch);
}

void int_Return_Values_from_Input_Operations() {
	int ch; // use an int, not a char to hold the return from get()
	while ((ch = cin.get()) != EOF) // loop to read and write all the data in the input
		cout.put(ch);
}

int main() {
	print_file_line();

	Single_Byte_Operations();
	//int_Return_Values_from_Input_Operations();
}
#endif

#ifdef EX_17_37

#include "../../stdafx.h"
#include "17_05_2.h"
using namespace std;

int main(int, char *argv[]) {
	print_file_line();

	try {
		read_file(argv[1], '\n');
	}
	catch (const exception &e) {
		cerr << "Exception: " << e.what() << '\n';
	}

	return 0;
}
#endif

#ifdef EX_17_38

#include "../../stdafx.h"
#include "17_05_2.h"
using namespace std;

int main(int, char *argv[]) {
	print_file_line();
	read_file(argv[1], ' ');
	return 0;
}
#endif
