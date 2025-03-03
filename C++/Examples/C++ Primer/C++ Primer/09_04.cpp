#ifdef ON

#include <iostream>
#include <vector>
using namespace std;

void capacity_and_size() {
	vector<int> ivec;
	
	cout << "size = " << ivec.size() << " capacity = " << ivec.capacity() << '\n' << endl; // size should be zero; capacity is implementation defined
	for (vector<int>::size_type ix = 0; ix != 24; ++ix) { // give ivec 24 elements
		ivec.push_back(ix);
		cout << "size = " << ivec.size() << " capacity = " << ivec.capacity() << endl; //MINE
	}
	cout << "\nAfter for ix != 24: size = " << ivec.size() << " capacity = " << ivec.capacity() << endl; // size should be 24; capacity will be >= 24 and is implementation defined

	ivec.reserve(50); //TEST!! //																																									sets capacity to at least 50; might be more
	cout << "\nAfter reserve(50): size = " << ivec.size() << " capacity = " << ivec.capacity() << '\n' << endl; // size should be 24; capacity will be >= 50 and is implementation defined

	while (ivec.size() != ivec.capacity()) { // add elements to use up the excess capacity
		ivec.push_back(0);
		cout << "size = " << ivec.size() << " capacity = " << ivec.capacity() << endl; // capacity should be unchanged and size and capacity are now equal
	}
	cout << "\nAfter while ivec.size() != ivec.capacity(): size = " << ivec.size() << " capacity = " << ivec.capacity() << endl; // capacity should be unchanged and size and capacity are now equal

	ivec.push_back(42); // add one more element
	cout << "\nsize = " << ivec.size() << " capacity = " << ivec.capacity() << endl; // size should be 51; capacity will be >= 51 and is implementation defined

	ivec.shrink_to_fit(); // ask for the memory to be returned
	cout << "\nAfter shrink_to_fit(): size = " << ivec.size() << " capacity = " << ivec.capacity() << endl; // size should be unchanged; capacity is implementation defined
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	capacity_and_size();

	return 0;
}

#endif

#ifdef EX_09_39

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<string> svec;
	string word;

	svec.reserve(1024);
	cout << "size = " << svec.size() << "\tcapacity = " << svec.capacity() << "\n\n";

	while (cin >> word) {
		svec.push_back(word);
		cout << "size = " << svec.size() << "\tcapacity = " << svec.capacity() << '\n';
	}

	svec.resize(svec.size() + svec.size() / 2);
	cout << "size = " << svec.size() << "\tcapacity = " << svec.capacity() << '\n';

	return 0;
}

#endif