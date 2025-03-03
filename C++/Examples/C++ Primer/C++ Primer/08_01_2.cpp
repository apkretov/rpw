#include <iostream>
using namespace std;

#ifdef ON

void process_input(istream &is) { //MINE
	int i;
	is >> i;
	cout << i;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef Managing_the_Condition_State 
	auto old_state = cin.rdstate(); // remember the current state of cin 
	cin.clear(); // make cin valid 
	process_input(cin); // use cin 
	cout << "\ncin.rdstate() = " << cin.rdstate() << '\n';

	//TEST! cin.clear(cin.rdstate() & ~istream::failbit & ~istream::badbit); //MINE
	cout << "cin.rdstate() = " << cin.rdstate() << '\n';

	cin.setstate(old_state); // now reset cin to its old state 
	cout << "cin.rdstate() = " << cin.rdstate() << '\n';

	//TEST! cin.clear(cin.rdstate() & cin.failbit & cin.badbit); //																															turns off failbit and badbit but all other bits unchanged 
#endif
	cout << '\n';

	return 0;
}

#endif

istream &read_stream(istream &is) {
	string s;

#ifndef OFF
	do {
		is.clear();
		while (is >> s)
			cout << s;
	} while (!is.eof()); //TEST!
#endif

	is.clear();
	return is;
}

#ifdef EX_08_01
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	read_stream(cin);

	return 0;
}

#endif