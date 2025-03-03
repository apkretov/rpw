#if 0 

#include <iostream>
#include "../../stdafx.h"
#include "1_06 »нтеграци€ пользовательского класса в цикл for.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	for (vector<int> v{1, 2, 3, 4, 5}; int x : Head(v, 3)) //TEST!
		cout << x << ' ';
	cout << '\n';

	for (const vector<int> v{1, 2, 3, 4, 5}; int x : HeadMine(v, 3)) //TEST!
		cout << x << ' ';
	cout << '\n';
}
#endif //1