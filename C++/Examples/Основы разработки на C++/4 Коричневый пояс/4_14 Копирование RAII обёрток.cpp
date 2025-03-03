#if 0

#include <cstdio>
#include "../../stdafx.h"
using namespace std;

class File {
	FILE *f;
public:
	File(const string &filename) {
		errno_t res = fopen_s(&f, filename.c_str(), "w");
		if (res != 0)
			throw runtime_error("Cannot open " + filename);
	}

	File(const File &) = delete; //TEST
	void operator=(const File &) = delete; //TEST!!
	~File() { fclose(f); }
	void Write(const string &line) { fputs(line.c_str(), f); }
};


int main() {
	PRINT_FILE_LINE();

	try {
		File f("4_13 - output.txt");
		//TEST File f2 = f;
		File f2("4_14 - output2.txt");
		//TEST f2 = f;
		f.Write("Hello World!\n");
		f.Write("This is a RAII file\n");
	}
	catch (...) { cout << "Cannot open the file\n"; }

	return 0;
}
#endif //1