#include "pch.h"
#include "../2 Жёлтый пояс/2_10 Обеспечиваем регулярный запуск юнит тестов.h"
TEST(TestSynonyms, TestAddSynonyms) {
	{
		Synonyms empty;
		AddSynonyms(empty, "a", "b");
		const Synonyms expected = {{"a", {"b"}},
								   {"b", {"a"}}};
		EXPECT_EQ(empty, expected);
	}
	{
		Synonyms synonyms = {{"a", {"b"}},
					 {"b", {"a", "c"}},
					 {"c", {"b"}}};

		AddSynonyms(synonyms, "a", "c");
		const Synonyms expected = {{"a", {"b", "c"}},
								   {"b", {"a", "c"}},
								   {"c", {"b", "a"}}};
		EXPECT_EQ(synonyms, expected);
	}
}

TEST(TestSynonyms, TestCount) {
	{
		Synonyms empty;
		EXPECT_EQ(GetSynonymCount(empty, "a"), 0u);
	}
	{
		Synonyms synonyms = {{"a", {"b", "c"}},
						   {"b", {"a"}},
						   {"c", {"a"}}};
		EXPECT_EQ(GetSynonymCount(synonyms, "a"), 2u);
		EXPECT_EQ(GetSynonymCount(synonyms, "b"), 1u);
		EXPECT_EQ(GetSynonymCount(synonyms, "z"), 0u);
	}
}
