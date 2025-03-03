#ifdef ON

#include <cassert>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

#define NDEBUG

void The_assert_Preprocessor_Macro(const string &word, size_t threshold) {
	assert(word.size() > threshold);
}

namespace The_NDEBUG_Preprocessor_Variable {
	void print(const int ia[], size_t size) {
#ifndef NDEBUG //TEST!!
		cerr << __func__ << ": array size is " << size << endl; // __func__ is a local static defined by the compiler that holds the function’s name
#endif
		// ...
	}

	void print(const string &word, size_t threshold) {
		if (word.size() < threshold)
			cerr << "Error: " << __FILE__
			<< " : in function " << __func__
			<< " at line " << __LINE__ << endl
			<< " Compiled on " << __DATE__
			<< " at " << __TIME__ << endl
			<< " Word read was \"" << word
			<< "\": Length too short" << endl;
	}
}

int main(int argc, char *argv[]) {
	print_file_line();

	constexpr size_t size{10};
	int ia[size]{};

	string word{"string"};
	//The_assert_Preprocessor_Macro(word, size);
	The_assert_Preprocessor_Macro(word, 100);
	//The_NDEBUG_Preprocessor_Variable::print(ia, size);
	//The_NDEBUG_Preprocessor_Variable::print(word, size);

	return 0;
}
#endif

#undef EX_06_48
#ifdef EX_06_48

#include <iostream>
#include <cassert>
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	const string sought{"test"};
	string in;

	while (cin >> in && in != sought)
		;
 	//TEST assert(cin);

	return 0;
}
#endif
