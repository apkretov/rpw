#pragma once
		
#ifndef Delegating_Constructors

#include <string>
//MINE #include <iostream>

class Sales_data { //VER07
	friend Sales_data add(const Sales_data &, const Sales_data &); // friend declarations for nonmember Sales_data operations added
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);
public: 
	Sales_data(std::string s, unsigned cnt, double price) : bookNo(s), units_sold(cnt), revenue(cnt *price) { // nondelegating constructor initializes members from corresponding arguments	
		//MINE std::cout << __LINE__ << " Sales_data(std::string s, unsigned cnt, double price) constructor\n";
	} 

	Sales_data() : Sales_data("", 0, 0) { //TEST!! //																																		remaining constructors all delegate to another constructor
		//MINE std::cout << __LINE__ << " Sales_data() constructor\n"; 
	} 

	Sales_data(std::string s) : Sales_data(s, 0, 0) { //TEST!!
		//MINE std::cout << __LINE__ << " Sales_data(std::string s) constructor\n";
	} 

	Sales_data(std::istream &is) : Sales_data() { //TEST!!
		//MINE std::cout << __LINE__ << " Sales_data(std::istream &is) constructor\n";
		read(is, *this);
	}
	
	std::string isbn() const { return bookNo; } // other members as before
	Sales_data &combine(const Sales_data &);

	double avg_price() const { //MINE
		return units_sold ? revenue / units_sold : 0;
	}
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif

