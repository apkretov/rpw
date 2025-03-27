#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::make_unique;
using std::unique_ptr;

struct QuackBehavior {
	~QuackBehavior() = default;
	virtual void quack() const = 0;
};

struct Quack : QuackBehavior {
	void quack() const override { cout << "Quack\n"; }
};

struct Squeak : QuackBehavior {
	void quack() const override { cout << "Squeak\n"; }
};

struct MuteQuack : QuackBehavior {
	void quack() const override { cout << "<< Silence >>\n"; }
};

struct FlyBehavior {
	~FlyBehavior() = default;
	virtual void fly() const = 0;
};

struct FlyWithWings : FlyBehavior {
	void fly() const override { cout << "I'm flying!!!\n"; }
};

struct FlyNoWay : FlyBehavior {
	void fly() const override { cout << "I can't fly.\n"; }
};
