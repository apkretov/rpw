#if 1

#include <array>
#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
using namespace std;

class DuckActor {
	unique_ptr<QuackBehavior> quacking;
public:
	DuckActor(unique_ptr<QuackBehavior> quack_behavior) : quacking(std::move(quack_behavior)) {}
	~DuckActor() = default;
	virtual void display() const = 0;
	void talk() const { cout << "The actor talks.\n"; }
	void quack() const { quacking->quack(); };
};

struct MallardDuckActor final : DuckActor {
	MallardDuckActor() : DuckActor(make_unique<Quack>()) {}
	void display() const override { cout << "The duck actor looks like a mallard.\n"; }
};

struct RubberDuckActor final : DuckActor {
	RubberDuckActor() : DuckActor(make_unique<Squeak>()) {}
	void display() const override { cout << "The duck actor looks like a rubber duck.\n"; }
};

int main() {
	print_file_line();

	array<unique_ptr<DuckActor>, 2> duck_actors = {
		make_unique<MallardDuckActor>(),
		make_unique<RubberDuckActor>()
	};

	for (const auto &duck_actor : duck_actors) {
		duck_actor->display();
		duck_actor->talk();
		duck_actor->quack();
		cout << '\n';
	}

	return 0;
}
#endif 
