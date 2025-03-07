#if 0

#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
#include "09 Integrating the Duck Behavior.h"
using namespace std;

/* Java
public abstract class Duck { // 1. Type and compile the Duck class below (Duck.java), and the MallardDuck class from two pages back (MallardDuck.java).
	FlyBehavior flyBehavior; // Declare two reference variables for the behavior interface types. All duck subclasses(in the same package) inherit these.
	QuackBehavior quackBehavior;
	public Duck() {}
	public abstract void display();
	public void performFly() { flyBehavior.fly(); } // Delegate to the behavior class.
	public void performQuack() { quackBehavior.quack(); } // Delegate to the behavior class.
	public void swim() { System.out.println(“All ducks float, even decoys!”); }
}

public interface FlyBehavior{ // 2. Type and compile the FlyBehavior interface (FlyBehavior.java) and the two behavior implementation classes (FlyWithWings.java and FlyNoWay.java).
	public void fly();
}

public class FlyWithWings implements FlyBehavior {
	public void fly() {	System.out.println(“I’m flying!!”); }
}

public class FlyNoWay implements FlyBehavior {
	public void fly() { System.out.println(“I can’t fly”); }
}

public interface QuackBehavior{ // 3. Type and compile the QuackBehavior interface (QuackBehavior.java) and the three behavior implementation classes(Quack.java, MuteQuack.java, and Sqeak.java).
	public void quack();
}

public class Quack implements QuackBehavior {
	public void quack() { System.out.println(“Quack”); }
}

public class MuteQuack implements QuackBehavior {
	public void quack() { System.out.println(“ << Silence >> ”); }
}

public class Squeak implements QuackBehavior {
	public void quack() { System.out.println(“Squeak”);	}
}

public class MiniDuckSimulator { // Type and compile the test class (MiniDuckSimulator.java).
	public static void main(String[] args) {
		Duck mallard = new MallardDuck();
		mallard.performQuack(); // This calls the MallardDuck’s inherited performQuack() method, which then delegates to the object’s QuackBehavior (i.e. calls quack() on the duck’s inherited quackBehavior reference).
		mallard.performFly(); // Then we do the same thing with MallardDuck’s inherited performFly() method.
	}
}
*/

int main() {
	print_file_line();

	MallardDuck mallard;
	mallard.performQuack(); // This calls the MallardDuck’s inherited performQuack() method, which then delegates to the object’s QuackBehavior (i.e. calls quack() on the duck’s inherited quackBehavior reference).
	mallard.performFly(); // Then we do the same thing with MallardDuck’s inherited performFly() method.

	return 0;
}
#endif //1
