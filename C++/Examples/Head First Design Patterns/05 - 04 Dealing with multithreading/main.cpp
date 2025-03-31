#include <future>
#include "../../stdafx.h"
#include "Singleton.h"
using namespace std;

int main() {
	print_file_line();

	constexpr size_t numThreads = 10;
	
	auto getSingletonInstance = [] { return Singleton::getInstance(); };
	vector<future<Singleton *>> boilerInstances(numThreads);
	for	(size_t i = 0; i < numThreads; ++i)
		boilerInstances[i] = async(getSingletonInstance);

    return 0;
}