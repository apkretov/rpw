#ifdef ON

#include <iostream>
#include <bitset>
#include <climits>
using std::cout;
using std::bitset;

#define C 128
#define SC 128
#define UC 257
#define UC2 (-1)

void mine() {
	char c = C;
	signed char sc = SC;
	unsigned char uc = UC, uc2 = UC2;

	cout << C << "\t\t" <<					SC << "\t\t" <<					UC << "\t\t" <<					UC2 << '\n';
	cout << c << "\t\t"	<<					sc << "\t\t" <<					uc << "\t\t" <<					uc2 << '\n';
	cout << bitset<CHAR_BIT>(c) << '\t' <<	bitset<CHAR_BIT>(sc) << '\t' << bitset<CHAR_BIT>(uc) << '\t' <<	bitset<CHAR_BIT>(uc2) << '\n';
	cout << int(c) << "\t\t" <<				int(sc) << "\t\t" <<			int(uc) << "\t\t" <<			int(uc2) << '\n';
}

int main(int argc, char** agrv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	mine();

	return 0;
}
#endif