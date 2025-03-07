#if 1

#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
using namespace std;

/* Java
public class Duck {
	QuackBehavior quackBehavior;
	public void performQuack() { quackBehavior.quack();	}
}

public class MallardDuck extends Duck {
	public MallardDuck() {
		quackBehavior = new Quack();
		flyBehavior = new FlyWithWings();
	}

	public void display() {	System.out.println("I’m a real Mallard duck"); }
}
*/

class Duck {
	unique_ptr<QuackBehavior> quacking;
	unique_ptr<FlyBehavior> flying;
public:
	Duck(unique_ptr<QuackBehavior> quack_behavior, unique_ptr<FlyBehavior> fly_behavior) : quacking(std::move(quack_behavior)), flying(std::move(fly_behavior)) {}
	~Duck() = default;
	void performQuack() const { quacking->quack(); };
	void swim() const { cout << "The duck swims.\n"; }
	virtual void display() const = 0;
	void performFly() const { flying->fly(); }
};

struct MallardDuck final : Duck {
	MallardDuck() : Duck(make_unique<Quack>(), make_unique<FlyWithWings>()) {}
	void display() const override { cout << "I’m a real Mallard duck\n"; }
};

int main() {
	print_file_line();

	MallardDuck duck;
	duck.performQuack();
	duck.performFly();
	duck.display();

	return 0;
}
#endif //1