#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::make_unique;

struct MallardDuck : Duck {
	MallardDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck : Duck {
	RedheadDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};

struct RubberDuck : Duck {
	RubberDuck() : Duck(make_unique<Squeak>(), make_unique<FlyNoWay>()) {}
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
};

struct DecoyDuck : Duck {
	DecoyDuck() : Duck(make_unique<MuteQuack>(), make_unique<FlyNoWay>()) {}
	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
};
