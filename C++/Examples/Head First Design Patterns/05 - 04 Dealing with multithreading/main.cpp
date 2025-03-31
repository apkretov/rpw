#include <future>
#include "../../stdafx.h"
#include "SingletonLazy.h"
using namespace std;

int main() {
	print_file_line();

	constexpr size_t numThreads = 10;
	
	auto getSingletonInstance = [] { return Lazy::Singleton::getInstance(); };
	vector<future<Lazy::Singleton *>> boilerInstances(numThreads);
	for	(size_t i = 0; i < numThreads; ++i)
		boilerInstances[i] = async(getSingletonInstance);

    return 0;
}