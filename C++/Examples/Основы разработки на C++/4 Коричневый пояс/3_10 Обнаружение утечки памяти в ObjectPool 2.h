#pragma once

#include <iostream>
#include "3_10 ����������� ������ ������ � ObjectPool 1.h"
using std::cout;
using std::endl;

int counter = 0;

struct Counted {
	Counted() { ++counter; }
	~Counted() { --counter; }
};

void run() {
	ObjectPool<Counted> pool;
	cout << "Counter before loop = " << counter << endl;
	for (int i = 0; i < 1000; ++i) {
		cout << "Allocating object #" << i << endl;
		pool.Allocate();
	}
	cout << "Counter after loop = " << counter << endl;
}
