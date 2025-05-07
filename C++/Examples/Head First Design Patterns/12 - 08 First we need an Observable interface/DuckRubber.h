
#pragma once

#include <iostream>
#include "Quackable.h"

#pragma region Integrate the helper Observable with the Quackable classes
class RubberDuck : public Quackable {
	Observable observable;
public:
	RubberDuck() : observable(*this) {}

	void quack() override {
		std::cout << "Squeak\n";
		notifyObservers();
	}

	void registerObserver(PtrObserver observer) override { observable.registerObserver(observer); }
	void notifyObservers() override { observable.notifyObservers(); }
};
#pragma endregion //Integrate the helper Observable with the Quackable classes
