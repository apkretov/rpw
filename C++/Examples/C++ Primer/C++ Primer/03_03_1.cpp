#ifdef ON

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Processing_Every_Character_Use_Range_Based_for_1() {
	string str("some string");

	// print the characters in str one character to a line
	for (auto c : str) // for every	char in	str
		cout << c << endl; // print the current character followed by a newline
}

void Processing_Every_Character_Use_Range_Based_for_2() {
	string text("Hello World!!!");
	decltype(text.size()) punct_cnt = 0; // punct_cnt has the same type that s.size returns; see § 2.5.3 (p. 70)
	
	// count the number of punctuation characters in s
	for (auto c : text) // for every char in s
		if (ispunct(c)) // if the character is punctuation
			++punct_cnt; // increment the punctuation counter
	cout << punct_cnt << " punctuation characters in " << text << endl;
}

void Using_a_Range_for_to_Change_the_Characters_in_a_string() {
	string text("Hello World!!!");
	
	// convert s to uppercase
	for (auto &c : text) // for every char in s (note: c is a reference)
		c = toupper(c); // c is a reference, so the assignment changes the char in s
	cout << text << endl;
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Processing_Every_Character_Use_Range_Based_for_1();
	//Processing_Every_Character_Use_Range_Based_for_2();
	//Using_a_Range_for_to_Change_the_Characters_in_a_string();

#ifdef EX_03_09
	string s;
	//TEST! cout << s[0] << endl;

#elif EX_03_12
	//TEST vector<vector<int>> ivec; // (a)
	//TEST vector<string> svec = ivec; // (b)
	//TEST vector<string> svec(10, "null"); // (c)

#elif !EX_03_13
	//TEST vector<int> v1; // (a)
	//TEST vector<int> v2(10); // (b)
	//TEST vector<int> v3(10, 42); // (c)
	//TEST vector<int> v4{10}; // (d)
	//TEST vector<int> v5{10, 42}; // (e)
	//TEST! vector<string> v6{10}; // (f)
	//TEST! vector<string> v7{10, "hi"}; // (g)
#endif
}

#endif