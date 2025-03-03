#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "06_05_2.h"
using namespace std;

void inline_Functions_Avoid_Function_Call_Overhead() {
	//MINE
	const string s1("string1"); 
	const string s2("string 2");

	cout << shorterString(s1, s2) << endl;
}

#pragma region constexpr_Functions
constexpr int new_sz() { //TEST! 
	return 42;
} 

constexpr int foo = new_sz(); //TEST! //																																				ok: foo is a constant expression

constexpr size_t scale(size_t cnt) { // scale(arg) is a constant expression if arg is a constant expression
	return new_sz() * cnt;
} 

int arr[scale(2)]; //TEST! //																																							ok: scale(2) is a constant expression
int i = 2; // i is not a constant expression
//TEST!! int a2[scale(i)]; //																																							error: scale(i) is not a constant expression
#pragma endregion

//TEST!
// Page 239: the function body must contain exactly one return statement.
// you.com: A constexpr function can have multiple return statements.The restriction of having exactly one return statement in a constexpr function body was removed in C++14.
constexpr int mine2() {
	if (true)
		return 1;
	else
		return 0;
	return -1;
}

constexpr string mine3() { //TEST! // C++20 only feature! string is a literal type since C++20.
	if (true)
		return "one";
	else
		return "two";
	return "three";
}

int main() {
	print_file_line();

	//inline_Functions_Avoid_Function_Call_Overhead();

	//constexpr auto j = mine1();
	//cout << "j = " << j << '\n';

	cout << "mine2() = " << mine2() << '\n';
	cout << "mine3() = " << mine3() << '\n';
	
	return 0;
}
#endif

#ifdef EX_06_46

#include <iostream>
using namespace std;

//TEST constexpr bool isShorter(const string &s1, const string &s2) { return s1.size() < s2.size(); }

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif

