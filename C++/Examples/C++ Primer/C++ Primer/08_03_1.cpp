#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#include "08_03_1.h"

void Using_an_istringstream(vpi &people) {
	string line, word; // will hold a line and word from input, respectively
	//ORIG vector<PersonInfo> people; // will hold all the records from the input

	while (getline(cin, line)) { // read the input a line at a time until cin hits end-of-file (or another error)
		PersonInfo info; // create an object to hold this record’s data
		istringstream record(line); // bind record to the line we just read

		record >> info.name; //TEST!! //																																									read the name
		while (record >> word) // read the phone numbers
			info.phones.push_back(word); // and store them
		
		people.push_back(info); // append this record to people
	}
}

#ifdef ON

void printPeople(const vpi &people) { //MINE
	for (const auto &i : people) {
		cout << i.name;
		for (const auto &j : i.phones)
			cout << ' ' << j;
		cout << '\n';
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vpi people;
	Using_an_istringstream(people);
	printPeople(people);

	return 0;
}
#endif

#ifdef EX_08_09

#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	istream &read_stream(istream &);
	string s;

	while (cin >> s) {
		istringstream iss(s);
		read_stream(iss);
		cout << '\n';
	}

	return 0;
}
#endif

#ifdef EX_08_10

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	ifstream in(argv[1]);
	string s;
	vector<string> lines;
	while (in >> s)
		lines.push_back(s);

	string word;
	for (const auto &line : lines) {
		istringstream iss(line);
		while (iss >> word)
			cout << word << '\n';
	}

	return 0;
}
#endif

#ifdef EX_08_11

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	ifstream in;
	in.open(argv[1]);
		
	string s;
	vector<string> lines;
	while (getline(in, s))
		lines.push_back(s);

	string word;
	istringstream iss;
	for (const auto &line : lines) {
		iss.str(line);
		while (iss >> word)
			cout << word << '\t';
		//TEST! iss.clear(); //																																											you.com: reset the state of the istringstream iss object before using it to parse the next line.
		cout << '\n';
	}

	return 0;
}
#endif
