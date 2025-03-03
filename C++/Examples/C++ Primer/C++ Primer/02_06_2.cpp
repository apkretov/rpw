#ifdef ON

#include <iostream>
#include "02_06_3.h"

int main() {
	setlocale(LC_ALL, "RU");
	std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Sales_data data1, data2;
	double price = 0; // price per book, used to calculate total revenue
	
	std::cin >> data1.bookNo >> data1.units_sold >> price; // read the first transactions: ISBN, number of books sold, price per book
	data1.revenue = data1.units_sold * price; // calculate total revenue from	price and units_sold

	std::cin >> data2.bookNo >> data2.units_sold >> price; // read the second transaction
	data2.revenue = data2.units_sold * price;

	if (data1.bookNo == data2.bookNo) {
		unsigned totalCnt = data1.units_sold + data2.units_sold;
		double totalRevenue = data1.revenue + data2.revenue;
		std::cout << data1.bookNo << " " << totalCnt << " " << totalRevenue << " "; // print: ISBN, total sold, total revenue, average price per book
		if (totalCnt != 0)
			std::cout << totalRevenue / totalCnt << std::endl;
		else
			std::cout << "(no sales)" << std::endl;
		return 0; // indicate success
	} else { // transactions weren’t for the same ISBN
		std::cerr << "Data must refer to the same ISBN"
			<< std::endl;
		return -1; // indicate failure
	}
}
#endif

