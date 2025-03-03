#ifdef EX_02_27

#include <iostream>
using std::cout;

void mine() {
	int v{}, b{};
	int &r = v;
	
	r = 1;
	cout << v << "\n";
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//TEST! int i = -1, &r = 0; // (a)
	int i2{}; //MINE
	int *const p2 = &i2; // (b)
	const int i = -1, &r = 0; // (c)
	const int *const p3 = &i2; // (d)
	const int *p1 = &i2; // (e)
	//TEST! const int &const r2; // (f)
	//OFF const int i2 = i, &r = i; // (g)

	mine();
	
	return 0;
}
#endif

#undef EX_02_28
#ifdef EX_02_28

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//ERR int i, *const cp; // (a)
	//ERR int *p1, *const p2; // (b)
	//TEST const int ic, &r = ic; // (c)
	//ERR const int *const p3; // (d)
	const int *p; // (e)
	
	return 0;
}
#endif

#undef EX_02_29
#ifdef EX_02_29

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i{}, *const cp{&i};
	int *p1{}, *const p2{p1};
	const int ic{0}, &r = ic;
	const int *const p3{0};
	const int *p;

	i = ic; // (a)
	//ERR p1 = p3; // (b)
	//ERR p1 = &ic; // (c)
	//ERR p3 = &ic; // (d)
	//ERR p2 = p1; // (e)
	//ERR ic = *p3; // (f)
}
#endif