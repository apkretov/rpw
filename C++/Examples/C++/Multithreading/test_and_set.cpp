#include "stdafx.h" //Test-and-set @ https://en.wikipedia.org/wiki/Test-and-set
#include <iostream>
using namespace std;

#define LOCKED 1 //Software implementation of test-and-set (pseudo-C implementation -  atomicity requires explicit hardware support and hence can't be implemented as a simple function.)
/*ORIG 
int TestAndSet(int* lockPtr) {
	int oldValue;
	oldValue = *lockPtr; // Start of atomic segment // The following statements should be interpreted as pseudocode for illustrative purposes only. Traditional compilation of this code will not guarantee atomicity, the use of shared memory (i.e. not-cached values), protection from compiler optimization, or other required properties.
	*lockPtr = LOCKED; // End of atomic segment
	return oldValue;
}*/
int TestAndSet(volatile int& lock_) { //TEST
	int oldValue;
	oldValue = lock_; // Start of atomic segment // The following statements should be interpreted as pseudocode for illustrative purposes only. Traditional compilation of this code will not guarantee atomicity, the use of shared memory (i.e. not-cached values), protection from compiler optimization, or other required properties.
	lock_ = LOCKED; // End of atomic segment
	return oldValue;
}

volatile int lock = 0; //Mutual exclusion using test-and-set (pseudo-C implementation)
//TEST volatile int lock = 1; //This is a simulation of a concurrent thread. A concurrent thread will begin given lock = 1 set by the first thread.
void Critical() {
	while (TestAndSet(lock) == 1); //ORIG while (TestAndSet(&lock) == 1);
	wcout << "Critical section. Only one process can be in this section at a time." << endl; //critical section // only one process can be in this section at a time
	lock = 0; // release lock when finished with the critical section
}

int main() {
	Critical();
	return 0;
}

