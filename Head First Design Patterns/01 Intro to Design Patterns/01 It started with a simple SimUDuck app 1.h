#pragma once

#include <iostream>
using std::cout;

struct Duck {
	~Duck() = default;
	virtual void quack() const { cout << "The duck quacks.\n"; }
	void swim() const { cout << "The duck swims.\n"; }
	virtual void display() const = 0;
};
