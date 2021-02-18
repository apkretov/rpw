#include "stdafx.h"
#include <iostream>
using std::cout;

int main() {
	if (true) //1
		if (true) //2
			if (false) //3
				cout << "3: true!\n";
			else 
				cout << "3: false!\n";
		else
			cout << "2: false!\n";
			//ERROR cout << "Unkown...\n";
	else 
		cout << "1: false!\n";
	return 0;
}