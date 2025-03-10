#if 0

#include <memory>
#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
#include "08 Sharpen your pencil 1.h"
#include "10 Behavior changes at runtime.h"
#include "04 Joe thinks about inheritance 4.h"
using namespace std;

/* Java
public void setFlyBehavior(FlyBehavior fb) { fl yBehavior = fb; } // 1. Add two new methods to the Duck class.
public void setQuackBehavior(QuackBehavior qb) { quackBehavior = qb; }

public class ModelDuck extends Duck { // 2. Make a new Duck type(ModelDuck.java).
	public ModelDuck() {
		flyBehavior = new FlyNoWay(); // Our model duck begins life grounded... without a way to fly.
		quackBehavior = new Quack();
	}
	public void display() { System.out.println(“I’m a model duck”);	}
}

public class FlyRocketPowered implements FlyBehavior { // 3. Make a new FlyBehavior type (FlyRocketPowered.java). // That’s okay, we’re creating a rocket powered flying behavior.
	public void fl y() { System.out.println(“I’m fl ying with a rocket!”); }
}

public class MiniDuckSimulator { // 4. Change the test class (MiniDuckSimulator.java), add the ModelDuck, and make the ModelDuck rocket - enabled.
	public static void main(String[] args) {
		Duck mallard = new MallardDuck();
		mallard.performQuack();
		mallard.performFly();

		Duck model = new ModelDuck();
		model.performFly(); // The first call to performFly() delegates to the flyBehavior object set in the ModelDuck’s constructor, which is a FlyNoWay instance.
		model.setFlyBehavior(new FlyRocketPowered()); // This invokes the model’s inherited behavior setter method, and...voila! The model suddenly has rocket-powered flying capability!
		model.performFly(); // If it worked, the model duck dynamically changed its flying behavior! You can’t do THAT if the implementation lives inside the duck class.
	}
}
*/

struct ModelDuck : Duck { // 2. Make a new Duck type(ModelDuck.java).
	ModelDuck() : Duck(make_unique<Quack>(), make_unique<FlyNoWay>()) {} // Our model duck begins life grounded... without a way to fly.
	void display() const override { cout << "I’m a model duck.\n"; }
};

int main() {
	print_file_line();

	MallardDuck mallard;
	mallard.performQuack();
	mallard.performFly();
	cout << '\n';

	ModelDuck model;
	model.performFly(); // The first call to performFly() delegates to the flyBehavior object set in the ModelDuck’s constructor, which is a FlyNoWay instance.
	model.setFlyBehavior(make_unique<FlyRocketPowered>()); // This invokes the model’s inherited behavior setter method, and...voila! The model suddenly has rocket-powered flying capability!
	model.performFly(); // If it worked, the model duck dynamically changed its flying behavior! You can’t do THAT if the implementation lives inside the duck class.

	return 0;
}
#endif //1
