#pragma once

struct MallardDuck : Duck {
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck : Duck {
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};
