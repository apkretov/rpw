#include <future>
#include "../../stdafx.h"
#include "vld.h"
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

	cout << "Lazy::Singleton\n";
	testThreads<Lazy::Singleton>();

	cout << "\nEager::Singleton\n";
	testThreads<Eager::Singleton>();

	cout << "\nDoubleCheckedLocking::Singleton\n";
	testThreads<DoubleCheckedLocking::Singleton>();
	cout << '\n';

    return 0;
}