#if 0

#include <memory>
#include "../../stdafx.h"
#include "vld.h"
using namespace std;

struct Widget {};

shared_ptr<Widget> GetOwningPtr() { return make_shared<Widget>(); }
Widget *GetNonOwningPtr() { return new Widget; }

shared_ptr<Widget> GetPtr(bool owning) {
	if (owning)
		return GetOwningPtr();
	else {
		auto ptr = GetNonOwningPtr(); //TEST!!
		auto DummyDeleter = [](Widget *) {}; //TEST!
		shared_ptr<Widget> ret = shared_ptr<Widget>(ptr, DummyDeleter);
	}
}

int main() {
	PRINT_FILE_LINE();

	auto ptr1 = GetPtr(true);
	auto ptr2 = GetPtr(false);
	delete ptr2.get(); //TEST!! //MINE //																													Amazon Q: Using a dummy deleter means the memory will never be freed automatically, and trying to delete it manually while the shared_ptr still exists can lead to undefined behavior.  

	return 0;
}
#endif //1