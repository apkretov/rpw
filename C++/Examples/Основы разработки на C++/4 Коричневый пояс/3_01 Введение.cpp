#if 0

#include "3_01 ¬ведение.h"
#include "1_EX_06 ¬торичный индекс в базе данных 2.h"
#include "../../stdafx.h"

int FindMinimalKarma(Database &db) {
	db.RangeByKarma(int{}, int{}, [](const Record &) { return true; });
	// Some code...
	return int{};
}

int main() {
	PRINT_FILE_LINE();
	TestRunner tr;
	{
		LOG_DURATION("All tests");
		RUN_TEST(tr, TestRangeBoundaries);
		RUN_TEST(tr, TestSameUser);
		RUN_TEST(tr, TestReplacement);
	}

	return 0;
}
#endif //1