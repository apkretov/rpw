#ifdef ON

#include "../../stdafx.h"
#include "16_03_2.h"
using namespace std;

#pragma region Pack Expansion
template <typename T>
ostream &print(ostream &os, const T &t) { //MINE
	return os << t;
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest) { // expand Args
	os << t << ", ";
	return print(os, rest...); // expand rest
}

void Pack_Expansion() {
	int i = 0; //MINE
	string s = "hello"; //MINE

	print(cout, i, s, 42); // two parameters in the pack
}
#pragma endregion

#pragma region Understanding Pack Expansions
template <typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest) { // call debug_rep on each argument in the call to print
	return print(os, debug_rep(rest)...); //TEST! //																													print(os, debug_rep(a1), debug_rep(a2), ..., debug_rep(an)
}

void Understanding_Pack_Expansions() {
	//ORIG errorMsg(cerr, fcnName, code.num(), otherData, "other", item);
	errorMsg(cerr, "fcnName", 42, "otherData", "other", "item"); //MINE

	//TEST! print(os, debug_rep(rest...)); //																															error: no matching function to call // passes the pack to debug_rep; print(os, debug_rep(a1, a2, ..., an))
}
#pragma endregion

int main() {
	print_file_line();

	//Pack_Expansion();
	Understanding_Pack_Expansions();
	cout << '\n';
}
#endif
