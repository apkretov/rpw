#pragma once

#include <utility>
#include "Quackable.h"

#pragma region Sharpen your pencil
class QuackCounter : public Quackable {
	PtrQuackable duck;
	static int numberOfQuacks;
public:
	explicit QuackCounter(PtrQuackable duck) : duck(std::move(duck)) {}

	void quack() override {
		duck->quack();
		++numberOfQuacks;
	}

	static int getQuacks() { return numberOfQuacks; }
	void registerObserver(PtrObserver observer) override { duck->registerObserver(observer); }
	void notifyObservers() const override { duck->notifyObservers(); }
};

int QuackCounter::numberOfQuacks = 0;
#pragma endregion //Sharpen your pencil