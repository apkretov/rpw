#undef ON
#ifdef ON

#include <iostream>
using std::cout;
#include <bitset>
#include <climits>

static int bitcount(unsigned n) { /* count 1 bits in n */
	typedef std::bitset<sizeof(n) * CHAR_BIT> bs; //TEMPLATE
	int b;

	cout << bs(n) << "\n\n";

	for (b = 0; n != 0; n >>= 1) {
		cout << bs(n) << '\n' << bs(n & 0b111) << "\n\n";
		if (n & 01)
			b++;
	}
	return b;
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	cout << bitcount(0707) << '\n';
	return 0;
}
#endif

#undef EX_2_09 // Solution by Gregory Pietsch @ https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_2:Exercise_9#Solution_by_Gregory_Pietsch
#ifdef EX_2_09

#include <iostream>
using std::cout;
#include <climits>
#include <bitset>

static int bitcount(unsigned x) { /* bitcount:  count 1 bits in x */
	typedef std::bitset<sizeof(x)* CHAR_BIT> bs;
	int b;

	cout << bs(x) << "\n\n";
	for (b = 0; x != 0; x &= (x - 1)) {
		cout << bs(x) << '\n';
		b++;
	}
	return b;
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	cout << '\n' << bitcount(0b00001110) << '\n';
	return 0;
}
#endif