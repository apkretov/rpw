#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Bit-fields
typedef unsigned int Bit;

class File { //TEST
	Bit mode : 2; // mode has 2 bits
	Bit modified : 1; // modified has 1 bit
	Bit prot_owner : 3; // prot_owner has 3 bits
	Bit prot_group : 3; // prot_group has 3 bits
	Bit prot_world : 3; // prot_world has 3 bits
	// operations and data members of File
public:
	enum modes { READ = 01, WRITE = 02, EXECUTE = 03 }; // file modes specified as octal literals; see § 2.1.3 (p. 38)
	File &open(modes);
	void close();
	void write();
	bool isRead() const;
	void setWrite();
};
#pragma endregion

#pragma region Using Bit-fields
void File::write() {
	modified = 1;
	// ...
}

void File::close() {
	if (modified)
		/**/; //MINE
		// . . . save contents
}

File &File::open(File::modes m) {
	mode |= READ; // set the READ bit by default
	// other processing
	if (m & WRITE) // if opening READ and WRITE
		// processing to open the file in read/write mode
	return *this;
}

inline bool File::isRead() const { 
	return mode & READ; 
}

inline void File::setWrite() { 
	mode |= WRITE; 
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif