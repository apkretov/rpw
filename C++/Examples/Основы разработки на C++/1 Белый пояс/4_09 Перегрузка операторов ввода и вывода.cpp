#if 0

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct Duration {
	int hour;
	int min;

	Duration(int h = 0, int m = 0) {
		hour = h;
		min = m;
	}
};

static ostream &operator<<(ostream &stream, const Duration &d) {
	stream << setfill('0'); //TEST
	stream << setw(2) << d.hour << ':' << setw(2) << d.min;
	return stream;
}

static istream &operator>>(istream &stream, Duration &d) {
	stream >> setw(2) >> d.hour;
	stream.ignore(); //ORIG stream.ignore(1);
	stream >> setw(2) >> d.min;
	return stream;
}

int main() {
	PRINT_FILE_LINE();

	stringstream dur_ss("02:50");
	Duration dur1;
	dur_ss >> dur1;
	cout << dur1 << '\n';
}
#endif