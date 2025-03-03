#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef string_Search_Operations
		string name("AnnaBelle");
		auto pos1 = name.find("Anna"); // pos1 == 0

		string lowercase("annabelle");
		pos1 = lowercase.find("Anna"); // pos1 == npos

		{
			string numbers("0123456789"), name("r2d2");
			auto pos = name.find_first_of(numbers); // returns 1, i.e., the index of the first digit in name

			string dept("03714p3");
			/*ORIG auto*/ pos = dept.find_first_not_of(numbers); // returns 5, which is the index to the character ’p’

#ifndef Specifying_Where_to_Start_the_Search
			/*ORIG string::size_type*/ pos = 0;

			while ((pos = name.find_first_of(numbers, pos)) != string::npos) { // each iteration finds the next number in name
				cout << "found number at index: " << pos << " element is " << name[pos] << endl;
				++pos; // move to the next character
			}
#endif
		}
#endif

#ifndef Searching_Backward
		string river("Mississippi");

		auto first_pos = river.find("is"); // returns 1
		auto last_pos = river.rfind("is"); // returns 4
#endif

	return 0;
}
#endif
