#undef ON
#ifdef ON

#include <iostream>
using namespace std;

int get_size() {
	return 1;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	// ...
	//TEST goto end;
	int scr_ix = 10; // error: goto bypasses an initialized variable definition
end:
	// error: code here could use ix but the goto bypassed its declaration
	scr_ix = 42;

	// backward jump over an initialized variable definition is okay
begin:
	int sz = get_size();
	if (sz <= 0) {
		//TEST goto begin;
	}

	return 0;
}
#endif