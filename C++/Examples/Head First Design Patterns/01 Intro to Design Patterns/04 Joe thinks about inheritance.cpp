#if 0

#undef ORIG
#undef MINE
#define AMAZON_Q

#include <array>
#include <memory>
#include "../../stdafx.h"
using namespace std;

#ifdef ORIG
#include "02 But now we need the ducks to FLY.h"
#include "01 It started with a simple SimUDuck app 2.h"

struct RubberDuck : Duck {
	void quack() const override { cout << "The duck squeaks.\n"; }
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
	virtual void fly() const { /* Do nothing. */ } //TEST!!
};

struct DecoyDuck : Duck {
	void quack() const override { /* Do nothing. */ }
	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
	virtual void fly() const { /* Do nothing. */ }
};
#endif //ORIG

#ifdef MINE
#include "04 Joe thinks about inheritance 1.h"
#endif //MINE

#ifdef AMAZON_Q
#include "04 Joe thinks about inheritance 2.h"
#include "04 Joe thinks about inheritance 3.h"
#include "04 Joe thinks about inheritance 4.h"
#endif //AMAZON_Q

int main() {
	print_file_line();

	array<unique_ptr<Duck>, 4> ducks = {
		make_unique<MallardDuck>(),
		make_unique<RedheadDuck>(),
		make_unique<RubberDuck>(),
		make_unique<DecoyDuck>()
	};

	for (const auto &duck : ducks) {
#ifndef MINE
		duck->quack();
		duck->swim();
		duck->display();
		duck->fly();
#endif //MINE
#ifdef MINE
		if (auto quacking = dynamic_cast<Quackable *>(duck.get()); quacking != nullptr)
			quacking->quack();
		duck->swim();
		duck->display();
		if (auto flying = dynamic_cast<Flyable *>(duck.get()); flying != nullptr)
			flying->fly();
#endif //MINE
		cout << '\n';
	}
	return 0;
}
#endif 

/*
Amazon Q

Multiple inheritance (MI) can often be replaced with single inheritance and composition, which is generally preferred in many cases. Here's why: [1]

1. Diamond Problem: When using MI, if two parent classes inherit from the same base class, it can create ambiguity about which version of the base class methods to use. For example:

class Duck {};
class FlyingBird : public Duck {};
class QuackingBird : public Duck {};
class MallardDuck : public FlyingBird, public QuackingBird {}; // Diamond problem!

2. A better approach using composition:

class FlyBehavior {
public:
	virtual void fly() = 0;
};

class QuackBehavior {
public:
	virtual void quack() = 0;
};

class Duck {
private:
	unique_ptr<FlyBehavior> flyBehavior;
	unique_ptr<QuackBehavior> quackBehavior;
public:
	void performFly() { flyBehavior->fly(); }
	void performQuack() { quackBehavior->quack(); }
	void setFlyBehavior(unique_ptr<FlyBehavior> fb) { flyBehavior = move(fb); }
	void setQuackBehavior(unique_ptr<QuackBehavior> qb) { quackBehavior = move(qb); }
};

class MallardDuck : public Duck {
public:
	MallardDuck() {
		setFlyBehavior(make_unique<StandardFly>());
		setQuackBehavior(make_unique<StandardQuack>());
	}
};

Benefits of composition over MI:
Clearer class hierarchy
More flexible - behaviors can be changed at runtime
Easier to maintain and extend
Avoids potential naming conflicts
Better encapsulation
Follows "favor composition over inheritance" principle

The composition approach also better follows the Strategy Pattern, which is more flexible for handling varying behaviors.

However, MI isn't always bad. It can be appropriate when:
Implementing multiple pure interfaces
Working with unrelated class hierarchies
The relationships truly represent "is-a" rather than "has-a"
But in most cases, composition provides a cleaner, more maintainable solution.

Sources
[1] Why should I avoid multiple inheritance?
stackoverflow.comquestions406081
*/