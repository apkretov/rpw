#pragma region Perplexity: How to design classes and resource management to minimize throwing exceptions from destructors.

#include <iostream>
#include <memory>
#include <fstream>
using namespace std;

class FileWrapper {
	ofstream file_;
public:
	FileWrapper(const string& filename) : file_(filename) {
		if (!file_) 
			throw runtime_error("Failed to open file");
	}

	~FileWrapper() noexcept { // No-throw destructor
		try {
			if (file_.is_open())
				file_.close();  // ofstream::close() may throw
		}
		catch (const exception& e) { 
			cerr << "Exception caught in destructor: " << e.what() << endl; // Handle/Log but do not throw
			// Optionally, terminate or swallow silently
		}
	}

	void write(const string& data) { file_ << data; }
};

int main() {
	try {
		FileWrapper fw("test.txt");
		fw.write("Hello, C++23!");
	}
	catch (const exception& e) {
		cerr << "Exception caught: " << e.what() << endl;
	}
	return 0;
}
#pragma endregion //Perplexity: How to design classes and resource management to minimize throwing exceptions from destructors.
