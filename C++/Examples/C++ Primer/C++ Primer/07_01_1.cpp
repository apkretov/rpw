#ifdef ON

#include <iostream>
using namespace std;
//ORIG #include "02_06_3.h"
#include "07_05_4.h" //MINE

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef Using_the_Revised_Sales_data_Class
	Sales_data total; // variable to hold the running sum
	if (read(cin, total)) { // read the first transaction
		Sales_data trans; // variable to hold data for the next transaction
		while (read(cin, trans)) { // read the remaining transactions
			if (total.isbn() == trans.isbn()) // check the isbns
				total.combine(trans); // update the running total
			else {
				print(cout, total) << endl; // print the results
				total = trans; // process the next book
			}
		}
		print(cout, total) << endl; // print the last transaction
	} else { // there was no input
		cerr << "No data?!" << endl; // notify the user
	}
#endif
}
#endif
