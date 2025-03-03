#undef ON
#ifdef ON

#include <iostream>
using std::cout;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	cout << ":";
	cout << "12";
	cout << '\10'; // Backspace
	cout << '\7'; // Bell
	cout << '\a'; // Bell
	//OK cout << '\011'; // Tab
	cout << ":";

	return 0;
}

#endif