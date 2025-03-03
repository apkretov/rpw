#undef ON
#ifdef ON

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	typedef char *pstring;
	const pstring cstr = 0; // cstr is a constant pointer to char
	const pstring *ps; // ps is a pointer to a constant pointer to char	

	//MINE
	char t[] = "test";	
	//ERR const pstring ps = t;
	//ERR const pstring ps = "test";
	pstring v;
	v = t;
	cout << v << '\n';

	return 0;
}
#endif
