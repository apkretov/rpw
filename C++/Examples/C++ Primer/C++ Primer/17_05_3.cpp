#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

void Accessing_the_Marker() {
	ostringstream writeStr; // remember the current write position in mark // output stringstream
	ostringstream::pos_type mark = writeStr.tellp();
	// ...
	bool cancelEntry = true; //MINE
	if (cancelEntry)
		writeStr.seekp(mark); // return to the remembered position
}

int Reading_and_Writing_to_the_Same_File(const string &path) {
	//TEST! fstream inOut("copyOut", fstream::ate | fstream::in | fstream::out); //																							open for input and output and preposition file pointers to end-of-file // file mode argument see § 8.4 (p. 319)
	fstream inOut(path, fstream::ate | fstream::in | fstream::out); //MINE 
	if (!inOut) {
		cerr << "Unable to open file!" << endl;
		return EXIT_FAILURE; // EXIT_FAILURE see § 6.3.2 (p. 227)
	}

	auto end_mark = inOut.tellg(); // inOut is opened in ate mode, so it starts out positioned at the end // remember original end-of-file position
	inOut.seekg(0, fstream::beg); //TEST //																																	reposition to the start of the file
	size_t cnt = 0; // accumulator for the byte count
	string line; // hold each line of input
	while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) { //TEST! //																							while we haven’t hit an error and are still reading the original data // and can get another line of input

		while (inOut // while we haven’t hit an error
			&& inOut.tellg() != end_mark //TEST! //																															and are still reading the original data
			&& getline(inOut, line)) { // and can get another line of input

			cnt += line.size() + 1; // add 1 to account for the newline
			auto mark = inOut.tellg(); // remember the read position

			inOut.seekp(0, fstream::end); //TEST //																																set the write marker to the end
			inOut << cnt; // write the accumulated length
			if (mark != end_mark)
				inOut << " "; // print a separator if this is not the last line

			inOut.seekg(mark); //TEST //																																		restore the read position

		}
		inOut.seekp(0, fstream::end); // seek to the end
		inOut << "\n"; // write a newline at end-of-file

		view_file(path);

		return 0;
	}
}

int main(int, char *argv[]) {
	print_file_line();

	Accessing_the_Marker();
	//return Reading_and_Writing_to_the_Same_File(argv[1]);
}
#endif
