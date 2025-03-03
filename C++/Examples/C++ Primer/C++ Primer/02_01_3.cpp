#undef ON
#ifdef ON

#include <iostream>

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	std::cout << "Hi \x4dO\115!\n"; // prints Hi MOM! followed by a newline
	std::cout << '\115' << /*ORIG '\n' */ '\12'; // prints M followed by a newline
}
#endif

#undef EX_02_07
#ifdef EX_02_07

#include <iostream>
using std::cout;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	cout << "Who goes with F\145rgus?\012";
	//cout << '\145' << '\n';
}
#endif
