#if 0

#include <iostream>
#include "../../stdafx.h"
using namespace std;

void Значение_по_умолчанию_для_полей() {
	struct Lecture {
		string title = "C++"; //TEST
		int duration = 0;
	};

	Lecture lecture;
	cout << lecture.title << " " << lecture.duration << '\n';

	Lecture lecture2 = {"OOP", 5400};
	cout << lecture2.title << " " << lecture2.duration << '\n';
	
	Lecture lecture3 = {"OOP"}; //TEST!
	cout << lecture3.title << " " << lecture3.duration << '\n';
}

int main() {
	PRINT_FILE_LINE();
	Значение_по_умолчанию_для_полей();
}
#endif