#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::unique_ptr;

class Duck {
	unique_ptr<QuackBehavior> quackBehavior;
	unique_ptr<FlyBehavior> flyBehavior;
public:
	Duck(unique_ptr<QuackBehavior> quack_behavior, unique_ptr<FlyBehavior> fly_behavior) : quackBehavior(std::move(quack_behavior)), flyBehavior(std::move(fly_behavior)) {}
	~Duck() = default;
	void quack() const { quackBehavior->quack(); };
	void swim() const { cout << "The duck swims.\n"; }
	virtual void display() const = 0;
	void fly() const { flyBehavior->fly(); }
};
