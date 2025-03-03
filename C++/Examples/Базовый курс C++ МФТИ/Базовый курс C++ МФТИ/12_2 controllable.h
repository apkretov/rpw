#pragma once // 08-exceptions/myvec-demo/controllable.hh @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/myvec-demo/controllable.hh

#include <iostream>
#include <stdexcept>
#include <utility>
using std::cout;

//MINE #define DEBUG 

struct Controllable {
	static int control;
	int *resource_;
	
	Controllable() : resource_(new int(42)) {
#ifdef DEBUG
		cout << "Constructing: this = " << this << '\n'; //MINE
#endif
	}

	Controllable(Controllable &&rhs) noexcept : resource_(rhs.resource_) {
		rhs.resource_ = nullptr;
	}

	Controllable &operator=(Controllable &&rhs) noexcept {
		std::swap(resource_, rhs.resource_);
		return *this;
	}
	
	Controllable(const Controllable &rhs) : resource_(new int(*rhs.resource_)) {
#ifdef DEBUG
		cout << "Copying: this = " << this << '\n'; //MINE
#endif
		if (control == 0) {
			control = 5;
			cout << "Control reached\n";
			throw std::bad_alloc{};
		}
		control -= 1;
	}
	
	Controllable &operator=(const Controllable &rhs) {
		Controllable tmp(rhs);
		std::swap(*this, tmp);
		return *this;
	}

	~Controllable() { 
#ifdef DEBUG
		printf("Deleting: this = %p\n", this); //MINE
#endif
		delete resource_; 
	}
};