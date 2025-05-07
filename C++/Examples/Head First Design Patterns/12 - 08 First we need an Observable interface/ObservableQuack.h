#pragma once

#include <memory>

class Observer; //TO DO: Define the Observer class and delete this.
using PtrObserver = std::shared_ptr<Observer>;

#pragma region First we need an Observable interface
/* Java
public interface QuackObservable { // QuackObservable is the interface that Quackables should implement if they want to be observed
    public void registerObserver(Observer observer); // It has a method for registering Observers. Any object implementing the Observer interface can listen to quacks
    public void notifyObservers(); // It also has a method for notifying the observers
}
*/
class QuackObservable { // QuackObservable is the interface that Quackables should implement if they want to be observed
public:
    virtual ~QuackObservable() = default;
    virtual void registerObserver(PtrObserver observer) = 0; // It has a method for registering Observers. Any object implementing the Observer interface can listen to quacks
    virtual void notifyObservers() = 0; // It also has a method for notifying the observers
};

using PtrQuackobservable = std::shared_ptr<QuackObservable>;
#pragma endregion //First we need an Observable interface