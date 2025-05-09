#pragma once

#include <iostream>
#include "Observable.h"
#include "Quackable.h"

#pragma region Integrate the helper Observable with the Quackable classes
class DuckCall : public Quackable {
	Observable observable;
public:
	DuckCall() : observable(*this) {}

	void quack() override {
		std::cout << "Kwak\n";
		notifyObservers();
	}

	void registerObserver(PtrObserver observer) override { observable.registerObserver(observer); }
	void notifyObservers() const override { observable.notifyObservers(); }
};
#pragma endregion //Integrate the helper Observable with the Quackable classes
