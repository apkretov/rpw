#pragma once

#include <iostream>
using std::cout;

struct Duck {
	~Duck() = default;
	void swim() const { cout << "The duck swims.\n"; }
	virtual void display() const = 0;
};
