#pragma once
#include <string>
using std::string;

class bar {
public:
	bar();
	~bar();
	string time; // The bar's date & time.
	double O;
	double H;
	double L;
	double C;
	void readOHLC(string /*strLine*/); // Read the date & time & the open, high, low & close quotes of the bar.
private:
	string readTime(string); // Return the date & time string.
};

