#if 0

#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
#include "10 Behavior changes at runtime.h"
#include "04 Joe thinks about inheritance 4.h"
using namespace std;

#pragma region MINE
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