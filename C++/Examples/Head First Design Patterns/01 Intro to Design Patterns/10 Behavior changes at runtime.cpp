#if 0

#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
using namespace std;

#pragma region MINE
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
	void setQuackBehavior(unique_ptr<QuackBehavior> quack_behavior) { quacking = std::move(quack_behavior); }
	void setFlyBehavior(unique_ptr<FlyBehavior> fly_behavior) { flying = std::move(fly_behavior); }
};

#include "04 Joe thinks about inheritance 4.h"

int main() {
	print_file_line();

	auto enact_duck = [](const MallardDuck &duck) {
		duck.performQuack();
		duck.performFly();
		duck.display();
	};

	MallardDuck duck;
	enact_duck(duck);

	duck.setQuackBehavior(make_unique<Squeak>());
	duck.setFlyBehavior(make_unique<FlyNoWay>());
	cout << '\n';
	enact_duck(duck);

	return 0;
}
#pragma endregion MINE
#endif //1