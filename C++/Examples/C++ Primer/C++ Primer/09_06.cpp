#ifdef ON

#include <iostream>
#include <fstream>
#include <stack>
#include <deque>
#include <vector>
#include <queue>
using namespace std;

void Defining_an_Adaptor() {
	//MINE
	deque<int> deq = {0, 1, 2};
	vector<string> svec;

	stack<int> stk(deq); // copies elements from deq into stk

	stack<string, vector<string>> str_stk; // empty stack implemented on top of vector
	stack<string, vector<string>> str_stk2(svec); // str_stk2 is implemented on top of vector and initially holds a copy of svec
}

void Stack_Adaptor() {
	stack<int> intStack; // empty stack
	
	for (size_t ix = 0; ix != 10; ++ix) // fill up the stack
		intStack.push(ix); // intStack holds 0 . . . 9 inclusive
	
	while (!intStack.empty()) { // while there are still values in intStack
		int value = intStack.top();
		// code that uses value
		intStack.pop(); // pop the top element, and repeat
	}
}

void mine(const char *file) {
	ifstream in(file);
	istream_iterator<string> it(in), eof;
	priority_queue<string> q(it, eof);
	
	while (!q.empty()) {
		cout << q.top() << '\n';
		q.pop();
	}
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Stack_Adaptor();
	mine(argv[1]);

	return 0;
}
#endif
