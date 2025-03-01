#if 0

#include <array>
#include <memory>
#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 1.h"
#include "04 Joe thinks about inheritance 2.h"
using namespace std;

int main() {
	print_file_line();

	array<unique_ptr<Duck>, 4> ducks = {
		make_unique<MallardDuck>(),
		make_unique<RedheadDuck>(),
		make_unique<RubberDuck>(),
		make_unique<DecoyDuck>()
	};

	for (const auto &duck : ducks) {
		if (auto quacking = dynamic_cast<Quackable *>(duck.get()); quacking != nullptr)
			quacking->quack();
		duck->swim();
		duck->display();
		if (auto flying = dynamic_cast<Flyable *>(duck.get()); flying != nullptr)
			flying->fly();
		cout << '\n';
	}
	return 0;
}
#endif //1