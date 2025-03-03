#if 0

#include <array>
#include <fstream>
#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

int GetIndex(int n) {
	if (n == 10) return 0;
	if (n == 50) return 1;
	if (n == 100) return 2;
	if (n == 200) return 3;
	if (n == 500) return 3;
	if (n == 1000) return 4;
	if (n == 2000) return 5;
	if (n == 5000) return 7;
}

int main(int argc, char *argv[]) {
	PRINT_FILE_LINE();

	vector<int> cash(8);
	ifstream input("1_03 Введение в хеш функции - Input.txt"); //MINE
	int nominal; 
	while (input >> nominal) //ORIG while (cin >> nominal)
		++cash[GetIndex(nominal)];

	static array<int, 8> names = {10, 50, 100, 200, 500, 1000, 2000, 5000};
	for (int i = 0; i < cash.size(); ++i) {
		if (cash[i] > 0)
			cout << names[i] << " - " << cash[i] << endl;
	}

	return 0;
}
#endif //1
