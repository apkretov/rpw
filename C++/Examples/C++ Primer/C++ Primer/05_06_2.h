#pragma once

#include <string>

class Sales_item { //MINE
	std::string isbn_;
public:
	int count;
	Sales_item(std::string isbn__ = "", int count__ = 0) : isbn_(isbn__), count(count__) {};
	std::string isbn() const;
	void setIsbn(std::string isbn__);
	bool operator!=(const Sales_item &item) const;
	int operator+(const Sales_item &item) const;
	friend std::istream &operator>>(std::istream &in, Sales_item &item);
	friend std::ostream &operator<<(std::ostream &out, const Sales_item &item); //MINE
};
