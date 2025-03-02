#pragma once

struct MallardDuck final : Duck {
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck final : Duck {
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};
