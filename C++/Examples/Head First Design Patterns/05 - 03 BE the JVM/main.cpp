#include <future>
#include "../../stdafx.h"
#include "ChocolateBoiler.h"
using namespace std;

void operateBoiler() {
    auto boiler = ChocolateBoiler::getInstance();
    boiler->fill();
    boiler->boil();
    boiler->drain();
	cout << '\n';
}

int main() {
	print_file_line();

	constexpr size_t numThreads = 2;
	
	auto getBoilerInstance = [] { return ChocolateBoiler::getInstance(); };
	vector<future<ChocolateBoiler *>> boilerInstances(numThreads);
	for	(size_t i = 0; i < numThreads; ++i)
		boilerInstances[i] = async(getBoilerInstance);

	vector<future<void>> boilerOperations(numThreads);
	for (size_t i = 0; i < numThreads; ++i)
		boilerOperations.emplace_back(async(operateBoiler));
	cout << '\n';


    return 0;
}