#ifdef ON

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

struct Sales_data { //VER01
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
#endif