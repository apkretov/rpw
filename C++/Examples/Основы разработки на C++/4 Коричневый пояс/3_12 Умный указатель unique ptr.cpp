#if 0

#include "../../stdafx.h"
#include <memory>
using namespace std;

struct Actor {
	Actor() { cout << "I was born! :)" << endl; }
	~Actor() { cout << "I died! :(" << endl; }
	void DoWork() { cout << "I did some job!" << endl; }
};

void run(Actor *ptr) {
	if (ptr)
		ptr->DoWork();
	else
		cout << "An actor was expected :-/" << endl;
}

int main() {
	PRINT_FILE_LINE();

	auto ptr = make_unique<Actor>();
	run(ptr.get());
	auto ptr2 = std::move(ptr);
	run(ptr2.get());
	run(ptr.get());
	
	return 0;

}
#endif //1