#pragma once

#include <iostream>
#include <memory>
using std::cout;
using std::unique_ptr;

#pragma region MINE
class Duck {
	unique_ptr<QuackBehavior> quacking;
	unique_ptr<FlyBehavior> flying;
public:
	Duck(unique_ptr<QuackBehavior> quack_behavior, unique_ptr<FlyBehavior> fly_behavior) : quacking(std::move(quack_behavior)), flying(std::move(fly_behavior)) {}
	~Duck() = default;
	void performQuack() const { quacking->quack(); };
	void swim() const { cout << "All ducks float, even decoys!\n"; }
	virtual void display() const = 0;
	void performFly() const { flying->fly(); }
	void setQuackBehavior(unique_ptr<QuackBehavior> qb) { quacking = std::move(qb); }
	void setFlyBehavior(unique_ptr<FlyBehavior> fb) { flying = std::move(fb); }
};
#pragma endregion MINE