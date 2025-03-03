#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

inline bool get_status() { //MINE
	return true;
};

void Controlling_the_Format_of_Boolean_Values() {
	cout << "default bool values: " << true << " " << false	<< "\nalpha bool values: " << boolalpha	<< true << " " << false << endl;

	bool bool_val = get_status();
	cout << boolalpha // sets the internal state of cout
		<< bool_val
		<< noboolalpha; //TEST! //																																		// resets the internal state to default formatting
}

void Specifying_the_Base_for_Integral_Values() {
	cout << "default: " << 20 << " " << 1024 << endl;
	cout << "octal: " << oct << 20 << " " << 1024 << endl;
	cout << "hex: " << hex << 20 << " " << 1024 << endl;
	cout << "decimal: " << dec << 20 << " " << 1024 << endl;
}

void Indicating_Base_on_the_Output() {
	cout << showbase; // show the base when printing integral values
	cout << "default: " << 20 << " " << 1024 << endl;
	cout << "in octal: " << oct << 20 << " " << 1024 << endl;
	cout << "in hex: " << hex << 20 << " " << 1024 << endl;
	cout << "in decimal: " << dec << 20 << " " << 1024 << endl;
	cout << noshowbase; // reset the state of the stream

	cout << uppercase << showbase << hex //TEST
		<< "printed in hexadecimal: " << 20 << " " << 1024
		<< nouppercase << noshowbase << dec << endl;
}

void Specifying_How_Much_Precision_to_Print() {
	cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl; //TEST! //																	cout.precision reports the current precision value
	cout.precision(12); //TEST! //																																cout.precision(12) asks that 12 digits of precision be printed
	cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
	cout << setprecision(3); // alternative way to set precision using the setprecision manipulator
	cout << "Precision: " << cout.precision() << ", Value: " << sqrt(2.0) << endl;
}

void Specifying_the_Notation_of_Floating_Point_Numbers() {
	cout << "default format: " << 100 * sqrt(2.0) << '\n'
		<< "scientific: " << scientific << 100 * sqrt(2.0) << '\n'
		<< "fixed decimal: " << fixed << 100 * sqrt(2.0) << '\n' //TEST
		<< "hexadecimal: " << hexfloat << 100 * sqrt(2.0) << '\n' //TEST!
		<< "use defaults: " << defaultfloat << 100 * sqrt(2.0) //TEST
		<< "\n\n";
}

void Printing_the_Decimal_Point() {
	cout << 10.0 << endl; // prints 10
	cout << showpoint << 10.0 // prints 10.0000
		<< noshowpoint << endl; // revert to default format for the decimal point
}

void Padding_the_Output() {
	int i = -16;
	double d = 3.14159;
	
	cout << "i: " << setw(12) << i << "next col" << '\n' //TEST //																						pad the first column to use a minimum of 12 positions in the output
		<< "d: " << setw(12) << d << "next col" << '\n';
	
	cout << left //TEST //																																pad the first column and left-justify all columns
		<< "i: " << setw(12) << i << "next col" << '\n'
		<< "d: " << setw(12) << d << "next col" << '\n'
		<< right; //TEST //																																restore normal justification // restore normal justification
	
	cout << right // pad the first column and right-justify all columns
		<< "i: " << setw(12) << i << "next col" << '\n'
		<< "d: " << setw(12) << d << "next col" << '\n';
	
	cout << internal //TEST! //																															pad the first column but put the padding internal to the field
		<< "i: " << setw(12) << i << "next col" << '\n'
		<< "d: " << setw(12) << d << "next col" << '\n';
	
	cout << setfill('#') //TEST! //																														pad the first column, using # as the pad character
		<< "i: " << setw(12) << i << "next col" << '\n'
		<< "d: " << setw(12) << d << "next col" << '\n'
		<< setfill(' '); // restore the normal pad character
}

void Controlling_Input_Formatting() {
	char ch;
#ifdef SKIPWS
	while (cin >> ch)
		cout << ch;
#elif !NOSKIPWS
	cin >> noskipws; //TEST! //																															set cin so that it reads whitespace
	while (cin >> ch)
		cout << ch;
	cin >> skipws; // reset cin to the default state so that it discards whitespace
#endif 
}

int main() {
	print_file_line();

	//Controlling_the_Format_of_Boolean_Values();
	//Specifying_the_Base_for_Integral_Values();
	//Indicating_Base_on_the_Output();
	//Specifying_How_Much_Precision_to_Print();
	//Specifying_the_Notation_of_Floating_Point_Numbers();
	//Printing_the_Decimal_Point();
	Padding_the_Output();
	//Controlling_Input_Formatting();
}
#endif
