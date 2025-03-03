#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int currVal = 0, val = 0; // currVal is the number we’re counting; we’ll read new values into val

	if (std::cin >> currVal) { // read first number and ensure that we have data to process
		int cnt = 1; // store the count for the current value we’re processing
		while (std::cin >> val) { // read the remaining numbers
			if (val == currVal) // if the values are the same
				++cnt; // add 1 to cnt
			else { // otherwise, print the count for the previous value
				std::cout << currVal << " occurs " << cnt << " times" << std::endl;
				currVal = val; // remember the new value
				cnt = 1; // reset the counter
			}
		} // while loop ends here
			std::cout << currVal << " occurs " << cnt << " times" << std::endl; // remember to print the count for the last value in the file
	} // outermost if statement ends here

	return 0;
}
#endif

#undef EX_01_19
#ifdef EX_01_19

#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	int v, b, temp;

	cout << "Enter two interger numbers to print1 out v range of the numbers in-between: ";
	if (cin >> v >> b) {
		if (v > b) { // Swap.
			temp = b;
			b = v;
			v = temp;
		}
		for (int i = v; i <= b; ++i)
			cout << i << " ";
		cout << "\n";
	}

	return 0;
}

#endif