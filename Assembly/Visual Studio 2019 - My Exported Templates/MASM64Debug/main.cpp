#include <iostream> // Modern x64 Assembly 1: Beginning Assembly Programming - YouTube @ https://www.youtube.com/watch?v=rxsBghsrvpI
using namespace std;

extern "C" int SomeFunction();

int main() {
	cout << "The result is: " << SomeFunction() << endl;
	return 0;
}