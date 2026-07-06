#ifndef MINE

#undef SEQUENTIAL_QUICK_SORT
#define PARALLEL_QUICK_SORT

#include <iostream>
#ifdef SEQUENTIAL_QUICK_SORT
#include "Listing 4.12.h"
#else if defined(PARALLEL_QUICK_SORT)
#include "Listing 4.13.h"
#endif

void print_list(const std::list<int>& l) { // Helper function to print the list to the console
	for (int num : l) 
		std::cout << num << " ";
	std::cout << "\n";
}

int main() {
	std::list<int> my_list = {5, 7, 3, 4, 1, 9, 2, 8, 10, 6};

	std::cout << "Original list: ";
	print_list(my_list);

#ifdef SEQUENTIAL_QUICK_SORT
	std::list<int> sorted_list = sequential_quick_sort(my_list);
#else if defined(PARALLEL_QUICK_SORT)
	std::list<int> sorted_list = parallel_quick_sort(my_list);
#endif

	std::cout << "Sorted list:   ";
	print_list(sorted_list);

	return 0;
}
#endif //MINE
