#ifdef ON

#include <iostream>
#include "05_06_2.h"
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Sales_item total; // variable to hold data for the next transaction
	if (cin >> total) { // read the first transaction and ensure that there are data to process
		Sales_item trans; // variable to hold the running sum
		while (cin >> trans) { // read and process the remaining transactions
			if (total.isbn() == trans.isbn()) // if we’re still processing the same book
				//ORIG total += trans; // update the running total
				total.count = total + trans; //MINE
			else {
				cout << total << endl; // print results for the previous book
				total = trans; // total now refers to the next book
			}
		}
		cout << total << endl; // print the last transaction
	} else { // no input! warn the user
			cerr << "No data?!" << endl;
		return -1; // indicate failure
	}
	return 0;
}
#endif