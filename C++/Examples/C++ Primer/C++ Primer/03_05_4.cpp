#undef ON
#ifdef ON

#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	char ca[] = {'C', '+', '+'}; // not null terminated
	cout << strlen(ca) << endl; // disaster: ca isn’t null terminated
	cout << ca << '\n'; //MINE

	return 0;
}
#endif

#undef EX_03_37
#ifdef EX_03_37

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	const char ca[] = {'h', 'e', 'l', 'l', 'o'};
	const char *cp = ca;
	
	while (*cp) {
		cout << *cp << endl;
		++cp;
	}

	return 0;
}
#endif