#ifdef ON

#include <iostream>
#include <map>
#include "../../stdafx.h"
using namespace std;

void Subscripting_a_map() {
	map <string, size_t, less<>> word_count; //ORIG map <string, size_t> word_count; // empty map
	word_count["Anna"] = 1; //TEST! //																																								insert a value-initialized element with key Anna; then assign 1 to its value
}

void Using_the_Value_Returned_from_a_Subscript_Operation() {
	map<string, size_t, less<>> word_count = {{"Anna", 1}}; //ORIG map<string, size_t> word_count = {{"Anna", 1}};

	cout << word_count["Anna"]; // fetch the element indexed by Anna; prints 1
	++word_count["Anna"]; //TEST! //																																								fetch the element and add 1 to it
	cout << word_count["Anna"]; // fetch the element and print it; prints 2
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	Using_the_Value_Returned_from_a_Subscript_Operation();
	cout << '\n';

	return 0;
}

#endif
