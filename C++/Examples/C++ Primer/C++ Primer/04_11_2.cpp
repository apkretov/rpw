#ifdef ON

#include <iostream>
using namespace std;

void Other_Implicit_Conversions() {
	int i;
	const int &j = i; //TEST // convert a nonconst to a reference to const int
	const int *p = &i; //TEST // convert address of a nonconst to the address of a const
	//TEST! int &r = j, *q = p; //																																								error: conversion from const to nonconst not allowed
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Other_Implicit_Conversions();

	return 0;
}
#endif
