#ifdef ON

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;

void constexpr_and_Constant_Expressions() {
	string text; // empty string
	cin >> text; // read a whitespace-separated string into s
	cout << text << endl; // write	s to the output
}

void f2() {
	string s1, s2;
	cin >> s1 >> s2; // read first input into s1, second into s2
	cout << s1 << s2 << endl; // write both	strings
}

void Reading_an_Unknown_Number_of_strings() {
	string word;

	while (cin >> word) // read until end-of-file
		cout << word << endl; // write each word followed by a new line
}

void Using_getline_to_Read_an_Entire_Line() {
	string line;

	while (getline(cin, line)) // read input a line at a time until end-of-file
		cout << line << endl;
}

void The_string_empty_and_size_Operations_1() {
	string line;

	while (getline(cin, line)) // read input a line at a time and discard blank lines
		if (!line.empty())
			cout << line << endl;
}

void The_string_empty_and_size_Operations_2() {
	string line;
	
	while (getline(cin, line)) // read input a line at a time and print lines that are longer than 80 characters
		if (line.size() > 80)
			cout << line << endl;
}

void Adding_Literals_and_strings() {
	string s1, s2;

	//TEST string s4 = s1 + ", "; //																																									ok: adding a string anda literal
	//TEST! string s5 = "hello" + ", "; //																																								error: no string operand
	//TEST! string s6 = s1 + ", " + "world"; // 																																						ok: each + has a string operand
	//TEST! string s7 = "hello" + ", " + s2; // 																																						error: can’t add string literals
	//TEST!! string s8 = "hello" + s4; //MINE
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//f1();
	//f2();
	//Reading_an_Unknown_Number_of_strings();
	Using_getline_to_Read_an_Entire_Line();
	//The_string_empty_and_size_Operations_1();
	//The_string_empty_and_size_Operations_2();

	return 0;
}

#endif