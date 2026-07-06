#ifndef MINE

#include "Listing 2.4.h"
#include "../../stdafx.h"
#include <thread>
#include <chrono>

int main() {
	print_file_line();

	edit_document("foo.txt");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	return 0;
}
#endif //MINE