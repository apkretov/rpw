#ifdef ON

#include <iostream>
using namespace std;

void Other_Ways_to_Change_a_string() {
	string s = "test string"; //MINE

	//TEST! s.insert(s.size(), 5, '!'); //																																							insert five exclamation points at the end of s
	//TEST! s.erase(s.size() - 5, 5); // 																																							erase the last five characters from s

	const char *cp = "Stately, plump Buck";
	//TEST! s.assign(cp, 7); //																																										s == "Stately"
	//TEST! s.insert(s.size(), cp + 7); // 																																							s == "Stately, plump Buck"

	{
		string s = "some string", s2 = "some other string";
		//TEST! s.insert(0, s2); //																																									insert a copy of s2 before position 0 in s
		//TEST! s.insert(0, s2, 0, s2.size()); //																																					insert s2.size() characters from s2 starting at s2[0] before s[0]
	}
}

void The_append_and_replace_Functions() {
	string s("C++ Primer"), s2 = s; // initialize s and s2 to "C++ Primer"
	
	s.insert(s.size(), " 4th Ed."); // s == "C++ Primer 4th Ed."
	s2.append(" 4th Ed."); // equivalent: appends " 4th Ed." to s2; s == s2

	// equivalent way to replace "4th" by "5th"
	s.erase(11, 3); // s == "C++ Primer Ed."
	s.insert(11, "5th"); // s == "C++ Primer 5th Ed."
	// starting at position 11, erase three characters and then insert "5th"
	s2.replace(11, 3, "5th"); // equivalent: s == s2

	s.replace(11, 3, "Fifth"); // s == "C++ Primer Fifth Ed."
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Other_Ways_to_Change_a_string();

	return 0;
}
#endif
