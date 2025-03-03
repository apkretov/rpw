#if 1

#include <iostream>
#include <exception>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include "../../stdafx.h"
#include "../test_runner.h"
//OFF #include "vld.h"
#include "2_10 ќбеспечиваем регул€рный запуск юнит тестов.h"
using namespace std;

void TestAddSynonyms() {
	{
		Synonyms empty;
		AddSynonyms(empty, "a", "b");
		const Synonyms expected = {{"a", {"b"}}, 
								   {"b", {"a"}}};
		AssertEqual(empty, expected, "Add to empty");
	}
	{
		Synonyms synonyms = {{"a", {"b"}},
							 {"b", {"a", "c"}},
							 {"c", {"b"}}};

		AddSynonyms(synonyms, "a", "c");
		const Synonyms expected = {{"a", {"b", "c"}},
								   {"b", {"a", "c"}},
								   {"c", {"b", "a"}}};
		AssertEqual(synonyms, expected, "Add to non-empty");
	}
}

void TestCount() {
	{
		Synonyms empty;
		AssertEqual(GetSynonymCount(empty, "a"), 0u, "count for empty");
	}
	{
		Synonyms synonyms = {{"a", {"b", "c"}},
						   {"b", {"a"}},
						   {"c", {"a"}}};
		AssertEqual(GetSynonymCount(synonyms, "a"), 2u, "count for a");
		AssertEqual(GetSynonymCount(synonyms, "b"), 1u, "count for b");
		AssertEqual(GetSynonymCount(synonyms, "z"), 0u, "count for z");
	}
}

void TestAreSynonyms() {
	{
		Synonyms empty;
		Assert(!AreSynonyms(empty, "a", "b"), "empty a b");
		Assert(!AreSynonyms(empty, "b", "a"), "empty b a");
	}
	{
		Synonyms synonyms = {{"a", {"b", "c"}},
						   {"b", {"a"}},
						   {"c", {"a"}}};
		Assert(AreSynonyms(synonyms, "a", "b"), "synonyms a b");
		Assert(AreSynonyms(synonyms, "b", "a"), "synonyms b a");
		Assert(AreSynonyms(synonyms, "a", "c"), "synonyms a c");
		Assert(AreSynonyms(synonyms, "c", "a"), "synonyms c a");
		Assert(!AreSynonyms(synonyms, "b", "c"), "synonyms b c");
		Assert(!AreSynonyms(synonyms, "c", "b"), "synonyms c b");
	}
}

void TestAll() {
	TestRunner tr;
#ifdef ORIG
	tr.RunTest(TestAddSynonyms, "TestAddSynonyms");
	tr.RunTest(TestCount, "TestCount");
	tr.RunTest(TestAreSynonyms, "TestAreSynonyms");
#else //1_03 ќператор #
	RUN_TEST(tr, TestAddSynonyms);
	RUN_TEST(tr, TestCount);
	RUN_TEST(tr, TestAreSynonyms);
#endif //1_03 ќператор #
}

int main() {
	PRINT_FILE_LINE();

	TestAll();

	int q;
	cin >> q;

	Synonyms synonyms;
	for (int i = 0; i < q; ++i) {
		string operation_code;
		cin >> operation_code;
		if (operation_code == "ADD") {
			string first_word, second_word;
			cin >> first_word >> second_word;
			AddSynonyms(synonyms, first_word, second_word);
		} else if (operation_code == "COUNT") {
			string word;
			cin >> word;
			cout << GetSynonymCount(synonyms, word) << endl;
		} else if (operation_code == "CHECK") {
			string first_word, second_word;
			cin >> first_word >> second_word;
			if (AreSynonyms(synonyms, first_word, second_word)) // ищЄм второе слово во множестве синонимов первого (можно было сделать и наоборот)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}
	return 0;
}
#endif //1
