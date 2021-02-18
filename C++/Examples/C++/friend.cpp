//Based on 8.13 — Friend functions and classes @ http://www.learncpp.com/cpp-tutorial/813-friend-functions-and-classes/
#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

class a {
	int x = 10;
public:
	double y = 20;
	friend void friendFunction(a& objA);
	friend class b;
	friend void multipleFriendFunction(a& objA, b& objB);
};

void friendFunction(a& objA) { cout << "friendFunction: objA.x = " << objA.x << endl; }

class b {
	int x = 100;
public:
	double y = 200;
	void display(a& objA) { cout << "friend class b.display: objA.x = " << objA.x << endl; }
	friend void multipleFriendFunction(a& objA, b& objB);
};

void multipleFriendFunction(a& objA, b& objB) {cout << "multipleFriendFunction: objA.x = " << objA.x << " objB.x = " << objB.x << endl;}

int main() {
   a objA;
	friendFunction(objA);
	b objB;
	objB.display(objA);
	multipleFriendFunction(objA, objB);
	return 0;
}

