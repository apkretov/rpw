#ifdef ON

#include <iostream>
using namespace std;

void mine() {
	int i{-2};
	unsigned u{1};

	//TEST! auto r = i + u;	cout << r << '\n';
}

void Understanding_the_Arithmetic_Conversions() {
	bool flag; char cval;
	short sval; unsigned short usval;
	int ival; unsigned int uival;
	long lval; unsigned long ulval;
	//ORIG float fval; double dval;
	float fval; double dval{}; //MINE

	3.14159L + 'a'; // ’a’ promoted to int, then that int converted to long double
	dval + ival; // ival converted to double
	dval + fval; // fval converted to double
	ival = dval; // dval converted (by truncation) to int
	flag = dval; // if dval is 0, then flag is false, otherwise true
	cval + fval; // cval promoted to int, then that int converted to float
	sval + cval; // sval and cval promoted to int
	cval + lval; // cval converted to long
	ival + ulval; // ival converted to unsigned long
	usval + ival; // promotion depends on the size of unsigned short and int
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	mine();

	return 0;
}
#endif
