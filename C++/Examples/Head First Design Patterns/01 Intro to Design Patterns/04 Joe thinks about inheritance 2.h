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

struct StandardQuack final : QuackBehavior {
	void quack() const override { cout << "The duck quacks.\n"; }
};

struct SqueakQuack final : QuackBehavior {
	void quack() const override { cout << "The duck squeaks.\n"; }
};

struct NoQuack final : QuackBehavior {
	void quack() const override { /* Do nothing. */ }
};

struct FlyBehavior {
	~FlyBehavior() = default;
	virtual void fly() const = 0;
};

struct FlyWithWings final : FlyBehavior {
	void fly() const override { cout << "The duck flies.\n"; }
};

struct FlyNoWay final : FlyBehavior {
	void fly() const override { /* Do nothing. */ }
};

class Duck {
	unique_ptr<QuackBehavior> quacking;
	unique_ptr<FlyBehavior> flying;
public:
	Duck(unique_ptr<QuackBehavior> quack_behavior, unique_ptr<FlyBehavior> fly_behavior) : quacking(std::move(quack_behavior)), flying(std::move(fly_behavior)) {}
	~Duck() = default;
	void quack() const { quacking->quack(); };
	void swim() const { cout << "The duck swims.\n"; }
	virtual void display() const = 0;
	void fly() const { flying->fly(); }
};

struct MallardDuck final : Duck {
	MallardDuck() : Duck(make_unique<StandardQuack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck final : Duck {
	RedheadDuck() : Duck(make_unique<StandardQuack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};

struct RubberDuck final : Duck {
	RubberDuck() : Duck(make_unique<SqueakQuack>(), make_unique<FlyNoWay>()) {}
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
};

struct DecoyDuck final : Duck {
	DecoyDuck() : Duck(make_unique<NoQuack>(), make_unique<FlyNoWay>()) {}
	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
};