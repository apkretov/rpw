#if 0

#undef MINE
#define HFDP // Head First Design Patterns

#include <array>
#include "../../stdafx.h"
#include "04 Joe thinks about inheritance 2.h"
#include "04 Joe thinks about inheritance 3.h"
#include "04 Joe thinks about inheritance 4.h"
using namespace std;

#ifdef MINE
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
	MallardDuckActor() : SoundDevice(make_unique<Quack>()) {}
	void display() const override { cout << "The duck actor looks like a mallard.\n"; }
};

struct RubberDuckActor final : DuckActor {
	RubberDuckActor() : SoundDevice(make_unique<Squeak>()) {}
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
#endif //MINE

#ifdef HFDP
class SoundDevice {
	unique_ptr<QuackBehavior> sounding;
public:
	SoundDevice(unique_ptr<QuackBehavior> quack_behavior) : sounding(std::move(quack_behavior)) {}
	~SoundDevice() = default;
	void sound() const { sounding->quack(); };
};

struct DuckCall final : SoundDevice {
	DuckCall() : SoundDevice(make_unique<Quack>()) {}
};

int main() {
	print_file_line();

	DuckCall duck_call;
	duck_call.sound();

	return 0;
}
#endif //HFDP
#endif 
