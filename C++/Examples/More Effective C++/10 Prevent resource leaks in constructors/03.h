#pragma once

#pragma region Perplexity: Keep actual failure-prone operations (I/O, allocation, etc.) in separate initialization methods.

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>
using namespace std;

class Config {
public:
	Config() = default;  // Default constructor never throws

	void initialize(const string& filename) { // Separate initialization method that may throw
		ifstream file(filename);
		if (!file)
			throw runtime_error("Failed to open config file");

		getline(file, setting_); // Simulate reading configuration from file
		if (setting_.empty())
			throw runtime_error("Config setting missing");
	}

	void printSetting() const { cout << "Config setting: " << setting_ << "\n"; }
private:
	string setting_;
};

int main_03() {
	try {
		Config config;          // Construction is guaranteed not to throw
		config.initialize("config.txt");  // Actual I/O happens here and may throw
		config.printSetting();
		return 0;
	}
	catch (const exception& e) {
		cerr << "Initialization failed: " << e.what() << "\n";
	}
}
#pragma endregion //Perplexity: Keep actual failure-prone operations (I/O, allocation, etc.) in separate initialization methods.
