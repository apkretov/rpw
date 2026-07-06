#ifndef MINE

#include "Listing 4.1.h"
#include <thread>
#include "../../stdafx.h"
using namespace std;

int main() {
	print_file_line();

	jthread t1(data_preparation_thread);
	this_thread::sleep_for(chrono::milliseconds(300));
	jthread t2(data_processing_thread);

	return 0;
}
#endif //MINE