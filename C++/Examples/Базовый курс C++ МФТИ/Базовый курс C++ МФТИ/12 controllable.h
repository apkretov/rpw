#pragma once // 08-exceptions/myvec-demo/controllable.hh @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/myvec-demo/controllable.hh

#include <iostream>
#include <stdexcept>
#include <utility>
#include "../../stdafx.h"
#include <cstdint>
#include <cstdio>
using std::cout;

//MINE #define DEBUG_CONTROLLABLE 

struct Controllable {
	static int control;
	int *resource_;
	
	Controllable() : resource_(new int(42)) {
#ifdef DEBUG_CONTROLLABLE
		cout << "Constructing: this = " << format_this(this) << '\n'; //MINE
#endif
	}

	Controllable(Controllable &&rhs) noexcept : resource_(rhs.resource_) { rhs.resource_ = nullptr; }

	Controllable &operator=(Controllable &&rhs) noexcept {
		std::swap(resource_, rhs.resource_);
		return *this;
	}
	
	Controllable(const Controllable &rhs) : resource_(new int(*rhs.resource_)) {
#ifdef DEBUG_CONTROLLABLE
		cout << "Copying: this = " << format_this(this) << '\n'; //MINE
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
#ifdef DEBUG_CONTROLLABLE
		printf("Deleting: this = "); //MINE
		printf_this(this);
		printf("\n");
#endif
		delete resource_; 
	}
};