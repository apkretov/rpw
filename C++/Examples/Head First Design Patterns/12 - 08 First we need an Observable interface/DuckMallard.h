#pragma once

#include <memory>
#include "Observable.h"
#include "ObservableQuack.h"
#include "Quackable.h"

#pragma region Integrate the helper Observable with the Quackable classes
/* Java
public class MallardDuck implements Quackable { // Each Quackable has an Observable instance variable
	Observable observable;

	public MallardDuck() { // In the constructor, we create an Observable and pass it a reference to the MallardDuck object
		observable = new Observable(this);
	}

	public void quack() {
		System.out.println("Quack");
		notifyObservers(); // When we quack, we need to let the observers know about it
	}

	public void registerObserver(Observer observer) {
		observable.registerObserver(observer);
	}

	public void notifyObservers() { // Here's our two QuackObservable methods. Notice that we just delegate to the helper
		observable.notifyObservers();
	}
}
*/
class MallardDuck : public Quackable { // Each Quackable has an Observable instance variable
	Observable observable;
public:
	MallardDuck() : observable(*this) {} // In the constructor, we create an Observable and pass it a reference to the MallardDuck object

	void quack() override {
		cout << "Quack\n";
		notifyObservers(); // When we quack, we need to let the observers know about it
	}

	void registerObserver(PtrObserver observer) override { observable.registerObserver(observer); }
	void notifyObservers() override { observable.notifyObservers(); } // Here's our two QuackObservable methods. Notice that we just delegate to the helper
};
#pragma endregion //Integrate the helper Observable with the Quackable classes