#ifdef MINE // BadDesign: Shows how locking a std::mutex twice on one thread causes undefined behavior.

#include <iostream>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

class BadDesign { // --- Problematic case with mutex causing undefined behavior ---
	mutex mtx;
public:
	void f1() {
		lock_guard lock(mtx);
		cout << "f1 start\n";
		f2();  // Calls f2, which tries to lock mtx again - undefined behavior
		cout << "f1 end\n";
	}

	void f2() {
		lock_guard lock(mtx);  // Locks same mutex again -> error
		cout << "f2 running\n";
	}
};

int main() {
	print_file_line();

	 BadDesign bad; // The problematic case may crash or deadlock.
	 bad.f1();

	return 0;
}
#endif //MINE
