#ifdef ON

#include <iostream>
using namespace std;

void The_Relational_Operators() {
	const int i{10}, j{20}, k{2};
	
	//TEST!! if (i < j < k)  //																																								oops! this condition compares k to the bool result of i < j // true if k is greater than 1!
		cout << "true\n";
	else
		cout << "false\n";
	
	if (i < j && j < k) //TEST //																																							ok: condition is	true if	i is smaller than j and j is smaller than k
		cout << "true\n";
	else
		cout << "false\n";

	const int val{10};
	
	if (val == true) //TEST! //																																							true only if val is equal to 1!
		cout << "\ntrue\n";
	else
		cout << "\nfalse\n";
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	The_Relational_Operators();

	return 0;
}
#endif

#undef EX_04_09
#ifdef EX_04_09

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const char *cp = "Hello, World!";

	if (cp && *cp) //TEST
		cout << "true\n";
	else
		cout << "false\n";

	return 0;
}
#endif

#undef EX_04_10
#ifdef EX_04_10

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const int ci{42};
	int i;

	while ((cin >> i) && i != ci)
		cout << i << '\n';

	return 0;
}
#endif

#undef EX_04_12
#ifdef EX_04_12

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i{}, j{}, k{};

	while (cin >> i >> j >> k)
		cout << "i != j < k is " << (i != j < k ? "true\n" : "false\n");

	return 0;
}
#endif
