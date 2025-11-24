#ifdef MINE // Intermediate: Delegates work to a private helper that assumes the mutex is already locked, preventing double locking.

#include <iostream>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

class Intermediate { // --- Intermediate solution: private helper that assumes mutex is locked ---
	mutex mtx;
	void helper() const { cout << "helper running\n"; } // Helper does work but assumes mutex is locked externally
public:
	void f1() {
		lock_guard lock(mtx);
		cout << "f1 start\n";
		helper();  // No locking here, already locked by f1
		cout << "f1 end\n";
	}

	void f2() {
		lock_guard lock(mtx);
		helper();  // No lock inside helper, safe to call here too
	}
};

int main() {
	print_file_line();

	Intermediate inter;
	inter.f1();
	inter.f2();

	return 0;
}
#endif //MINE
