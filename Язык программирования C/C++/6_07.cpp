#define ON
#ifdef ON

#include <iostream>
#include <iomanip>
using namespace std;
#include <bitset>
#include <climits>

#define KEYWORD	01 
#define EXTERNAL	02 
#define STATIC		04

#define MINE_010	010
#define MINE_020	020
#define MINE_040	040
#define MINE_0100 0100
#define MINE_0200 0200

static constexpr int width1 = 10, width2 = 35;
static int flags = 0;

static void mine1() {
	cout << left;
	cout << setw(width1) << "KEYWORD:" << bitset<CHAR_BIT>(KEYWORD) << '\n';
	cout << setw(width1) << "EXTERNAL:" << bitset<CHAR_BIT>(EXTERNAL) << '\n';
	cout << setw(width1) << "STATIC:" << bitset<CHAR_BIT>(STATIC) << '\n';
	cout << setw(width1) << "flags:" << bitset<CHAR_BIT>(flags) << '\n' << '\n';

	cout << setw(width2) << "EXTERNAL | STATIC: " << bitset<CHAR_BIT>(EXTERNAL | STATIC) << '\n' << '\n';
}

static void mine2() {
	cout << bitset<CHAR_BIT>(MINE_010) << '\n';
	cout << bitset<CHAR_BIT>(MINE_020) << '\n';
	cout << bitset<CHAR_BIT>(MINE_040) << '\n';
	cout << bitset<CHAR_BIT>(MINE_0100) << '\n';
	cout << bitset<CHAR_BIT>(MINE_0200) << '\n' << '\n';
}

static void f1() {
	flags |= EXTERNAL | STATIC; // включает биты external и static в flags
	cout << setw(width2) << "flags |= EXTERNAL | STATIC: " << bitset<CHAR_BIT>(flags) << '\n';

	flags &= ~(EXTERNAL | STATIC); // в то время как их выключает
	cout << setw(width2) << "flags &= ~(EXTERNAL | STATIC): " << bitset<CHAR_BIT>(flags) << '\n';

	//OFF flags = 077; cout << "flags: " << bitset<BITS>(flags) << '\n';
	if ((flags & (EXTERNAL | STATIC)) == 0) // истинно, если оба бита выключены.
		cout << setw(width2) << "flags & (EXTERNAL | STATIC): " << bitset<CHAR_BIT>(flags & (EXTERNAL | STATIC)) << '\n' << '\n';
}

static void f2() {
	struct flagsstruct { // содержит три 1-битовых поля.
		unsigned is_keyword : 1; // Следующее за двоеточием число задает ширину поля в битах.
		unsigned is_extern : 1; // Поля описаны как unsigned, чтобы подчеркнуть, что они действительно будут величинами без знака.
		unsigned is_static : 1;
	} flags;
	cout << setw(width1) << "sizeof(flags): " << sizeof(flags) << '\n';

	flags.is_keyword = flags.is_extern = flags.is_static = 1;  // для включения битов
	cout << "flags.is_keyword = flags.is_extern = flags.is_static = 1;" << '\n';
	cout << setw(width2) << "flags.is_keyword: " << bitset<CHAR_BIT>(flags.is_keyword) << '\n';
	cout << setw(width2) << "flags.is_extern: " << bitset<CHAR_BIT>(flags.is_extern) << '\n';
	cout << setw(width2) << "flags.is_static: " << bitset<CHAR_BIT>(flags.is_static) << '\n' << '\n';
}

static void mine3() {
	struct {
		unsigned is_keyword : 1; // Следующее за двоеточием число задает ширину поля в битах.
		unsigned is_extern : 2;
		unsigned is_static : 3;
	} flags;

	struct {
		unsigned bitwidth_01 : 1;
		unsigned bitwidth_31 : 31;
		unsigned bitwidth_32 : 32;
	} wideflags;

	cout << setw(width1) << "sizeof(flags): " << sizeof(flags) << '\n';

	cout << "flags.is_keyword = flags.is_extern = flags.is_static = " << bitset<CHAR_BIT>(007) << '\n';
	flags.is_keyword = flags.is_extern = flags.is_static = 007;  // для включения битов
	cout << setw(width2) << "flags.is_static: " << bitset<CHAR_BIT>(flags.is_static) << '\n';
	cout << setw(width2) << "flags.is_extern: " << bitset<CHAR_BIT>(flags.is_extern) << '\n';
	cout << setw(width2) << "flags.is_keyword: " << bitset<CHAR_BIT>(flags.is_keyword) << '\n';

	cout << "\nsizeof(wideflags): " << sizeof(wideflags) << '\n';
	cout << "wideflags.bitwidth_01 = wideflags.bitwidth_31 = wideflags.bitwidth_32 = " << bitset<CHAR_BIT * 4>(037777777777) << '\n';
	wideflags.bitwidth_01 = wideflags.bitwidth_31 = wideflags.bitwidth_32 = 037777777777;
	cout << setw(width2) << "wideflags.field_32: " << bitset<CHAR_BIT * 4>(wideflags.bitwidth_32) << '\n';
	cout << setw(width2) << "wideflags.field_31: " << bitset<CHAR_BIT * 4>(wideflags.bitwidth_31) << '\n';
	cout << setw(width2) << "wideflags.field_01: " << bitset<CHAR_BIT * 4>(wideflags.bitwidth_01) << '\n';
}

#include <cstdio>
static void mine4() { // Битовые поля @ https://metanit.com/cpp/c/6.7.php
	struct point {
		unsigned int x : 5;   // 0-31
		unsigned int y : 3;   // 0-7
	};

	struct point center = { 0, 5 };
	center.x = 2;
	printf("x=%d    y=%d \n", center.x, center.y);  // x=2  y=5
}

int main() {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//mine1();
	//f1();
	//mine2();
	f2();
	//mine3();
	//mine4();

	return(0);
}
#endif