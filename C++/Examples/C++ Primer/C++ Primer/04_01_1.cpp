#ifdef ON

#include <iostream>
using namespace std;

void Lvalues_and_Rvalues() {
	//MINE
	int i{}, *p{&i};
	//TEST! decltype(*p) r{i}; //																																											When we apply decltype to an expression (other than a variable), the result is a reference type if the expression yields an lvalue. Because dereference yields an lvalue, decltype(*p) is int&.
	//TEST! decltype(&p) pp;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif