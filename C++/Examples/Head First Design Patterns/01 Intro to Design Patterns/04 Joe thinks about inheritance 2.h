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

struct Quack final : QuackBehavior {
	void quack() const override { cout << "Quack\n"; }
};

struct Squeak final : QuackBehavior {
	void quack() const override { cout << "Squeak\n"; }
};

struct MuteQuack final : QuackBehavior {
	void quack() const override { cout << "<< Silence >>\n"; }
};

struct FlyBehavior {
	~FlyBehavior() = default;
	virtual void fly() const = 0;
};

struct FlyWithWings final : FlyBehavior {
	void fly() const override { cout << "I’m flying!!!\n"; }
};

struct FlyNoWay final : FlyBehavior {
	void fly() const override { cout << "I can’t fly.\n"; }
};

//class Duck {
//	unique_ptr<QuackBehavior> quacking;
//	unique_ptr<FlyBehavior> flying;
//public:
//	Duck(unique_ptr<QuackBehavior> quack_behavior, unique_ptr<FlyBehavior> fly_behavior) : quacking(std::move(quack_behavior)), flying(std::move(fly_behavior)) {}
//	~Duck() = default;
//	void quack() const { quacking->quack(); };
//	void swim() const { cout << "The duck swims.\n"; }
//	virtual void display() const = 0;
//	void fly() const { flying->fly(); }
//};
//
//struct MallardDuck final : Duck {
//	MallardDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
//	void display() const override { cout << "The duck looks like a mallard.\n"; }
//};
//
//struct RedheadDuck final : Duck {
//	RedheadDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
//	void display() const override { cout << "The duck looks like a redhead.\n"; }
//};
//
//struct RubberDuck final : Duck {
//	RubberDuck() : Duck(make_unique<Squeak>(), make_unique<FlyNoWay>()) {}
//	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
//};
//
//struct DecoyDuck final : Duck {
//	DecoyDuck() : Duck(make_unique<MuteQuack>(), make_unique<FlyNoWay>()) {}
//	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
//};