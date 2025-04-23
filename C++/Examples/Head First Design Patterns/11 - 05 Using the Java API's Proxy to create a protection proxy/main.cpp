#include "../../stdafx.h"
#include "vld.h"
#include "MatchMakingTestDrive.h"

int main() {
	print_file_line();

    MatchMakingTestDrive test;
    test.drive();
	std::cout << '\n';

    return 0;
}