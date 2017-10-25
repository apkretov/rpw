#include "stdafx.h"

#include <fstream>  // basic_ostream Class @ https://msdn.microsoft.com/library/5baadc65-b662-4fab-8c9f-94457c58cda1.aspx#basic_ostream__tellp
#include <iostream>  
void basic_ostream_seekp() {
	using namespace std;
	ofstream x("basic_ostream_seekp.txt");
	streamoff i = x.tellp();
	cout << i << endl;
	x << "testing";
	i = x.tellp();
	cout << i << endl;
	x.seekp(2);   // Put char in third char position in file  
	x << " ";
	x.seekp(2, ios::end);   // Put char two after end of file  
	x << "z";
	cout << endl << endl;
}

//#include <fstream> //How to read line by line or a whole text file at once? @ http://stackoverflow.com/questions/13035674/how-to-read-line-by-line-or-a-whole-text-file-at-once
#include <string>
void getline_() {
	using namespace std;
	string str;
	cout << "Reading Read.txt...\n";
	ifstream file("Read.txt");
	while (getline(file, str)) cout << str << endl;
	cout << "\nReading an unexisting file Read_none.txt...";
	ifstream file_none("Read_none.txt");
	while (getline(file_none, str)) cout << str << endl;
	cout << endl << endl;
}

int main() {
	basic_ostream_seekp();
	getline_();
	return 0;
}