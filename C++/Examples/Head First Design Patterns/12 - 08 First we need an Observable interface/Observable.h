#pragma once

#include <memory>
#include <vector>
#include "ObservableQuack.h"

using PtrQuackObservable = std::shared_ptr<QuackObservable>;

#pragma region Now, we need to make sure all the concrete classes that implement Quackable can handle being a QuackObservable
/* Java
public class Observable implements QuackObservable { // Observable must implement QuackObservable because these are the same method calls that are going to be delegated to it
    ArrayList observers = new ArrayList(); // Observable implements all the functionality a Quackable needs to be an observable. We just need to plug it into a class and have that class delegate to Observable
    QuackObservable duck;

    public Observable(QuackObservable duck) { // In the constructor we get passed the QuackObservable that is using this object to manage its observable behavior
        this.duck = duck;
    }

    public void registerObserver(Observer observer) { // Here's the code for registering an observer
        observers.add(observer);
    }

    public void notifyObservers() { // And the code for doing the notifications
        Iterator iterator = observers.iterator();
        while (iterator.hasNext()) {
            Observer observer = (Observer)iterator.next();
            observer.update(duck);
        }
    }
}
*/
class Observable : public QuackObservable { // Observable must implement QuackObservable because these are the same method calls that are going to be delegated to it
    std::vector<PtrObserver> observers; // Observable implements all the functionality a Quackable needs to be an observable. We just need to plug it into a class and have that class delegate to Observable
    PtrQuackObservable duck;

public:
    explicit Observable(PtrQuackObservable duck) : duck(duck) {} // In the constructor we get passed the QuackObservable that is using this object to manage its observable behavior

    void registerObserver(PtrObserver observer) override { // Here's the code for registering an observer
        observers.push_back(observer);
    }

    void notifyObservers() override { // And the code for doing the notifications
        for (const auto& observer : observers)
            observer->update(duck);
    }
};
#pragma endregion //Now, we need to make sure all the concrete classes that implement Quackable can handle being a QuackObservable