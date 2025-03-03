#ifdef ON

#include <iostream>
using namespace std;

void Other_Ways_to_Construct_strings() {
	const char *cp = "Hello World!!!"; // null-terminated array
	char noNull[] = {'H', 'i'}; // not null terminated

	string s1(cp); // copy up to the null in cp; s1 == "Hello World!!!"
	//TEST! string s2(noNull, 2); //																																								copy two characters from no_null; s2 == "Hi"
	//TEST! string s3(noNull); //																																									undefined: noNull not null terminated
	//TEST! string s4(cp + 6, 5); //																																								copy 5 characters starting at cp[6]; s4 == "World"
	//TEST! string s5(s1, 6, 5); //																																									copy 5 characters starting at s1[6]; s5 == "World"
	//TEST! string s6(s1, 6); //																																									copy from s1[6] to end of s1; s6 == "World!!!"
	//TEST! string s7(s1, 6, 20); //																																								ok, copies only to end of s1; s7 == "World!!!"
	//TEST! string s8(s1, 16); //																																									throws an out_of_range exception
}

void The_substr_Operation() {
	string s("hello world");

	string s2 = s.substr(0, 5); // s2 = hello
	string s3 = s.substr(6); // s3 = world
	string s4 = s.substr(6, 11); // s3 = world
	//TEST! string s5 = s.substr(12); //																																							throws an out_of_range exception
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif
