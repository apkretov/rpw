#ifndef MINE // GoodDesign: Final recommended approach with clear ownership of locking and a private function doing the guarded work, avoiding recursive locks.

#include <iostream>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

class GoodDesign { // --- Final recommended design: clear ownership and no recursive locks ---
	mutex mtx;
	void do_work() const { cout << "Doing work with locked mutex\n"; } // Private helper function that works on protected data
public:
	void public_f1() {
		lock_guard lock(mtx);
		cout << "public_f1 start\n";
		do_work();
		cout << "public_f1 end\n";
	}

	void public_f2() {
		lock_guard lock(mtx);
		cout << "public_f2 start\n";
		do_work();
		cout << "public_f2 end\n";
	}
};

int main() {
	print_file_line();

	GoodDesign good;
	good.public_f1();
	good.public_f2();

	return 0;
}
#endif //MINE
