#pragma once

#pragma once

#include <iostream>
using std::cout;

struct Duck {
	~Duck() = default;
	void swim() const { cout << "The duck swims.\n"; }
	virtual void display() const = 0;
};

struct Quackable {
	virtual void quack() const { cout << "The duck quacks.\n"; }
};

struct Flyable {
	void fly() const { cout << "The duck flies.\n"; }
};

struct MallardDuck : Duck, Quackable, Flyable {
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck : Duck, Quackable, Flyable {
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};

struct RubberDuck : Duck, Quackable {
	void quack() const override { cout << "The duck squeaks.\n"; }
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
};

struct DecoyDuck : Duck {
	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
};