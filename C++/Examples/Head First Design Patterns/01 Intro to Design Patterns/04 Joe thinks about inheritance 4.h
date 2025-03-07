#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::make_unique;

struct MallardDuck final : Duck {
	MallardDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck final : Duck {
	RedheadDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};

struct RubberDuck final : Duck {
	RubberDuck() : Duck(make_unique<Squeak>(), make_unique<FlyNoWay>()) {}
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
};

struct DecoyDuck final : Duck {
	DecoyDuck() : Duck(make_unique<MuteQuack>(), make_unique<FlyNoWay>()) {}
	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
};
