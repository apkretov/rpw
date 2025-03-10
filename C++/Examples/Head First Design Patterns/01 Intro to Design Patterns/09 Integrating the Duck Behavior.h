#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::unique_ptr;

class Duck {
	unique_ptr<QuackBehavior> quackBehavior; // Each Duck has a reference to something that implements the QuackBehavior interface.
	unique_ptr<FlyBehavior> flyBehavior; // Rather than handling the quack behavior itself, the Duck object delegates that behavior to the object referenced by quackBehavior.
public:
	Duck(unique_ptr<QuackBehavior> quack_behavior, unique_ptr<FlyBehavior> fly_behavior) : quackBehavior(std::move(quack_behavior)), flyBehavior(std::move(fly_behavior)) {}
	~Duck() = default;
	void performQuack() const { quackBehavior->quack(); };
	void swim() const { cout << "All ducks float, even decoys!\n"; }
	virtual void display() const = 0;
	void performFly() const { flyBehavior->fly(); }
};

struct MallardDuck : Duck {
	MallardDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "I’m a real Mallard duck\n"; }
};