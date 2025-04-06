#pragma once

#include "Duck.h"
#include "Turkey.h"

/* Java
public class TurkeyAdapter implements Duck { // First, you need to implement the interface of the type you're adapting to.This is the interface your client expects to see.
	Turkey turkey;
	public TurkeyAdapter(Turkey turkey) { this.turkey = turkey; } // Next, we need to get a reference to the object that we are adapting; here we do that through the constructor.
	public void quack() { turkey.gobble(); } // Now we need to implement all the methods in the interface; the quack() translation between classes is easy : just call the gobble() method.

	public void fly() { // Even though both interfaces have a fly() method, Turkeys fly in short spurts - they can't do long - distance flying like ducks.To map between a Duck's fly() method and a Turkey's, we need to call the Turkey's fly() method five times to make up for it.
		for (int i = 0; i < 5; i++)
			turkey.fly();
	}
}
*/
class TurkeyAdapter : public Duck { // First, you need to implement the interface of the type you're adapting to.This is the interface your client expects to see.
	Turkey &turkey_;
public:
	explicit TurkeyAdapter(Turkey &turkey) : turkey_(turkey) {} // Next, we need to get a reference to the object that we are adapting; here we do that through the constructor.
	void quack() override { turkey_.gobble(); } // Now we need to implement all the methods in the interface; the quack() translation between classes is easy : just call the gobble() method.

	void fly() override { // Even though both interfaces have a fly() method, Turkeys fly in short spurts - they can't do long - distance flying like ducks.To map between a Duck's fly() method and a Turkey's, we need to call the Turkey's fly() method five times to make up for it.
		for (int i = 0; i < 5; ++i)
			turkey_.fly();
	}
};