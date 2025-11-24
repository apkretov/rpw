#ifdef MINE // QuickFix: Uses std::recursive_mutex to allow the same thread to lock multiple times, fixing the crash but usually discouraged.

#include <iostream>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

class QuickFix { // --- Quick-and-dirty workaround: switch to recursive_mutex ---
	recursive_mutex rmtx;
public:
	void f1() {
		lock_guard lock(rmtx);
		cout << "f1 start\n";
		f2();  // This works because recursive_mutex allows re-locking
		cout << "f1 end\n";
	}

	void f2() {
		lock_guard lock(rmtx);
		cout << "f2 running\n";
	}
};

int main() {
	print_file_line();

	QuickFix fix;
	fix.f1();

	return 0;
}
#endif //MINE
