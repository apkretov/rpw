#include <iostream>
#include <memory>
#include <fstream>

class FileWrapper {
	std::ofstream file_;
public:
	FileWrapper(const std::string& filename) : file_(filename) {
		if (!file_) {
			throw std::runtime_error("Failed to open file");
		}
	}

	// No-throw destructor
	~FileWrapper() noexcept {
		try {
			if (file_.is_open()) {
				file_.close();  // std::ofstream::close() may throw
			}
		}
		catch (const std::exception& e) {
			// Handle/Log but do not throw
			std::cerr << "Exception caught in destructor: " << e.what() << std::endl;
			// Optionally, terminate or swallow silently
		}
	}

	void write(const std::string& data) {
		file_ << data;
	}
};

int main() {
	try {
		FileWrapper fw("test.txt");
		fw.write("Hello, C++23!");
	}
	catch (const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	return 0;
}
