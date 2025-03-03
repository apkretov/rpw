#ifdef ON

#include <iostream>
using namespace std;

void Arithmetic_Operations() {
	int i = 1024;
	int k = -i; // i is -1024
	bool b = true;
	//TEST bool b2 = -b; //																																										b2 is true!
	//MINE cout << b2 << ' ' << boolalpha << b2 << '\n';

	21 % 6; /* result is 3 */ 
	21 / 6; /* result is 3 */
	21 % 7; /* result is 0 */ 
	21 / 7; /* result is 3 */
	//TEST!! cout << -21 % -8 << '\n'; //																																						result is -5
	-21 / -8; /* result is 2 */
	//TEST!! cout << 21 % -5 << '\n'; //																																						result is 1
	21 / -5; /* result is -4 */
	//TEST!! cout << -21 % -5 << '\n'; //MINE //																																				By implication, if m%n is nonzero, it has the same sign as m.
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Arithmetic_Operations();

	return 0;
}
#endif

#undef EX_04_06
#ifdef EX_04_06

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i;

	while (cin >> i)
		cout << boolalpha << !bool(i % 2) << '\n';

	return 0;
}
#endif