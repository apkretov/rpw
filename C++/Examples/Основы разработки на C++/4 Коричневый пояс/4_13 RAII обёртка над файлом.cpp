#if 0

#include <cstdio>
#include "../../stdafx.h"
#include "vld.h"
using namespace std;

void ManipulateCFile() {
#ifdef ORIG
	FILE *f = fopen("4_13 - output.txt", "w");
	if (f != nullptr) {
#else //MINE
	FILE *f;
	errno_t res = fopen_s(&f, "4_13 - output.txt", "w"); 
	if (res == 0) {
#endif //MINE
		fputs("Hello World!\n", f);
		fputs("This file is written with fputs\n", f);
		//...
		fclose(f);
	} else {
		printf("Cannot open the file\n"); //ORIG cout << "Cannot open the file\n";
	}
}

class File { //TEST
	FILE *f;
public:
	File(const string &filename) {
#ifdef ORIG
		f = fopen(name.c_str(), "w");
		if (f == nullptr)
#else //MINE
		errno_t res = fopen_s(&f, filename.c_str(), "w");
		if (res != 0)
#endif //MINE
			throw runtime_error("Cannot open " + filename);
	}

	~File() { fclose(f); }
	void Write(const string &line) { fputs(line.c_str(), f); }
};

void ManipulateRAIIFile() {
	try {
		File f("4_13 - output.txt");
		f.Write("Hello World!\n");
		f.Write("This is a RAII file\n");
	}
	catch (...) { cout << "Cannot open the file\n"; }
}

int main() {
	PRINT_FILE_LINE();

	ManipulateCFile();
	ManipulateRAIIFile();

	return 0;
}
#endif //1