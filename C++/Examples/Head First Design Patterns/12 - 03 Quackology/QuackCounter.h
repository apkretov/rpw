#pragma once

#include "Quackable.h"

#pragma region Were going to make those Quackologists happy and give them some quack counts //We're going to make those Quackologists happy and give them some quack counts.
/* Java
public class QuackCounter implements Quackable {
	Quackable duck;
	static int numberOfQuacks;
	public QuackCounter(Quackable duck) { this.duck = duck; }

	public void quack() {
		duck.quack();
		numberOfQuacks++;
	}

	public static int getQuacks() { return numberOfQuacks; }
}
*/
class QuackCounter : public Quackable {
	Quackable &duck;
	static int numberOfQuacks;
public:
	explicit QuackCounter(Quackable &duck) : duck(duck) {}

	void quack() override {
		duck.quack();
		++numberOfQuacks;
	}

	static int getQuacks() { return numberOfQuacks; }
};

int QuackCounter::numberOfQuacks = 0;
#pragma endregion //Were going to make those Quackologists happy and give them some quack counts