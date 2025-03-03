#if 0

#include <deque>
#include <set>
#include <vector>
#include "../../stdafx.h"
#include "1_10 Автоматический вывод типа возвращаемого функцией.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	for (vector v{1, 2, 3, 4, 5}; int x : Head(v, 3))
		cout << x << ' ';
	cout << '\n';

	for (set s{1, 2, 3, 4, 5}; int x : Head(s, 3))
		cout << x << ' ';
	cout << '\n';

	for (const deque d{1, 2, 3, 4, 5}; int x : Head(d, 3)) //TEST!
		cout << x << ' ';
	cout << '\n';
}
#endif //1
