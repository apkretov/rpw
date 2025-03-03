#pragma once

void test_StrBlob() { //MINE
	StrBlob b1 = {"aaa", "bbb", "ccc"}, b2(b1);

	print(b1);
	print(b2);

	b1.front() = "AAA";

	std::cout << '\n';
	print(b1);
	print(b2);
}