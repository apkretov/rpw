#if 0

#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
#include "09 Integrating the Duck Behavior.h"
using namespace std;

/* Java
public class Duck {
	QuackBehavior quackBehavior; // Each Duck has a reference to something that implements the QuackBehavior interface.
	public void performQuack() { quackBehavior.quack();	} // Rather than handling the quack behavior itself, the Duck object delegates that behavior to the object referenced by quackBehavior.
}

public class MallardDuck extends Duck {
	public MallardDuck() {
		quackBehavior = new Quack();
		flyBehavior = new FlyWithWings();
	}

	public void display() {	System.out.println("I'm a real Mallard duck"); }
}
*/

int main() {
	print_file_line();

	MallardDuck duck;
	duck.performQuack();
	duck.performFly();
	duck.display();

	return 0;
}
#endif //1