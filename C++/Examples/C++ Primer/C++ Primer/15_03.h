#pragma once

#ifndef EX_15_13

#include <iostream>

class base {
public:
	std::string name() {
		return basename;
	}

	virtual void print(std::ostream &os) {
		os << basename;
	}
private:
	//ORIG std::string basename;
	std::string basename = "Default name";
};

class derived : public base {
public:
	void print(std::ostream &os) {
		//ERR print(os); 
		base::print(os);
		os << " " << i;
	}
private:
	int i{};
};
#endif