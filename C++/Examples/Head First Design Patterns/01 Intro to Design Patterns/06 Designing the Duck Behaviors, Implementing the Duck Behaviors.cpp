#if 0

#include <array>
#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
#include "04 Joe thinks about inheritance 3.h"
#include "04 Joe thinks about inheritance 4.h"
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
		duck->quack();
		duck->swim();
		duck->display();
		duck->fly();
		cout << '\n';
	}
	return 0;
}
#endif 
