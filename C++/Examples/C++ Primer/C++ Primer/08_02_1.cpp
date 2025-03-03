#ifdef ON

#include <iostream>
#include <fstream>
#include <exception>
using namespace std;
#include "07_05_4.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLIne: " << __LINE__ << "\n\n";

#ifndef Using_an_fstream_in_Place_of_an_iostream
	ifstream input(argv[1]); // open the file of sales transactions
	ofstream output(argv[2], ofstream::app); // open the output file
	Sales_data total; // variable to hold the running sum

	if (read(input, total)) { // read the first transaction
		Sales_data trans; // variable to hold data for the next transaction
		while (read(input, trans)) { // read the remaining transactions
			if (total.isbn() == trans.isbn()) // check isbns
				total.combine(trans); // update the running total
			else {
				print(output, total) << endl; // print the results
				total = trans; // process the next book
			}
		}
		print(output, total) << endl; // print the last transaction
	} else // there was no input
		cerr << "No data?!" << endl; 
#endif

#ifdef _1 //MINE
	try {
		cout << unitbuf;

		ifstream in(argv[1]);
		cout << "in.goodbit() = " << in.goodbit << '\n';

		ofstream out;
		out.open(argv[2]);
		cout << "out.goodbit() = " << out.goodbit << '\n';

		in.close();
		out.close();
		cout << nounitbuf;
	}
	catch (const exception &err) {
		cerr << err.what();
	}
#endif

#ifdef The_open_and_close_Members
	string ifile = argv[1]; //MINE
	ifstream in(ifile); // construct an ifstream and open the given file
	ofstream out; // output file stream that is not associated with any file
	//ORIG out.open(ifile + ".copy"); // open the specified file
	out.open(argv[2]); //MINE
	//TEST! if (out) //																																													check that the open succeeded
		cout << "the open succeeded" << endl; //																																						the open succeeded, so we can use the file

	in.close(); // close the file
	//ORIG in.open(ifile + "2"); // open another file
	in.open(argv[3]); //MINE
#endif

#ifdef Automatic_Construction_and_Destruction
	for (auto p = argv + 1; p != argv + argc; ++p) { // for each file passed to the program
		ifstream input(*p); // create input and open the file
		if (input) { // if the file is ok, ‘‘process’’ this file
			//ORIG process(input);
			cout << "could open: " + string(*p) << endl; //MINE
		} else
			cerr << "couldn’t open: " + string(*p) << endl;
	} // input goes out of scope and is destroyed on each iteration
#endif

	return 0;
}
#endif

#ifdef EX_08_04

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <filesystem>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLIne: " << __LINE__ << "\n\n";

	ifstream in;

	try {
		if (!filesystem::exists(argv[1]) || !filesystem::is_regular_file(argv[1])) { //you.com
			cerr << "The file does not exist: " << argv[1] << "\nThe current path: " << filesystem::current_path() << '\n';
			return EXIT_FAILURE;
		}
		
		in.open(argv[1]);
#ifdef OFF
		//TEST! if (in.goodbit != 0) {
		//TEST! if (!in) { 
			cerr << "Could not open v file!\n";
			return EXIT_FAILURE;
		}
#endif
	}
	catch (const exception &e) {
		cerr << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\tError: " << e.what() << '\n';
	}

	vector<string> ls;
	string l;

#ifdef OFF
	//TEST! while (getline(in, l))
		ls.push_back(l);
#endif

	for (const auto &i : ls)
		cout << i << '\n';

	return 0;
}
#endif

#ifdef EX_08_05

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLIne: " << __LINE__ << "\n\n";

	ifstream in(argv[1]);
	vector<string> ss;
	string s;
	
#ifdef OFF
	//TEST! while (in >> s)
		ss.push_back(s);
#endif

	for (const string &i : ss)
		cout << i << '\n';
	cout << '\n';

	return 0;
}
#endif