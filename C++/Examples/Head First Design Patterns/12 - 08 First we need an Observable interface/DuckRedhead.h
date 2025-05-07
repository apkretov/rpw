
#pragma once

#include <iostream>
#include "Observable.h"
#include "Quackable.h"

#pragma region Integrate the helper Observable with the Quackable classes
class RedheadDuck : public Quackable {
	Observable observable;
public:
	RedheadDuck() : observable(*this) {}

	void quack() override {
		std::cout << "Quack\n";
		notifyObservers();
	}

	void registerObserver(PtrObserver observer) override { observable.registerObserver(observer); }
	void notifyObservers() override { observable.notifyObservers(); }
};
#pragma endregion //Integrate the helper Observable with the Quackable classes
