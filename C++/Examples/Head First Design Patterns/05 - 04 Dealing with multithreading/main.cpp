#include <future>
#include "../../stdafx.h"
#include "SingletonDoubleCheckedLocking.h"
#include "SingletonEager.h"
#include "SingletonLazy.h"
using namespace std;

template <typename T>
void testThreads() {
	constexpr size_t numThreads = 3;

	auto getSingletonInstance = [] { return T::getInstance(); };
	vector<future<T *>> boilerInstances(numThreads);
	for (size_t i = 0; i < numThreads; ++i)
		boilerInstances[i] = async(getSingletonInstance);
}

int main() {
	print_file_line();

	testThreads<Lazy::Singleton>();
	cout << '\n';
	testThreads<Eager::Singleton>();
	cout << '\n';
	testThreads<DoubleCheckedLocking::Singleton>();

    return 0;
}