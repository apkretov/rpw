#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_5/04%20Programming%20Assignment

#include <iostream> 
#include <vector>
#include "../../stdafx.h"
#include "../test_runner.h"
#include "../test_runner_utility.h"
using namespace std;

template <typename Token> // ��������� Sentence<Token> ��� ������������� ���� Token // ��������� vector<Token>. // ��������� ����� � �������� ������������� �������� // ������� ����� ������� �� ������������ ������ ��������, // � ������ ����������� � vector<Sentence<Token>>.
using Sentence = vector<Token>;

template <typename Token> //GITHUB @ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/blob/main/Week_5/04%20Programming%20Assignment/Solution/split_into_sentences.cpp
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) { // ����� Token ����� ����� bool IsEndSentencePunctuation() const
	std::vector<Sentence<Token>> sentences;
	Sentence<Token> sentence;

	for (auto it = tokens.begin(); it != tokens.end(); ) {
		if (it->IsEndSentencePunctuation()) {
			do {
				sentence.push_back(std::move(*it));
				++it;
			} while (it != tokens.end() && it->IsEndSentencePunctuation());
			sentences.push_back(std::move(sentence));
		} else {
			sentence.push_back(std::move(*it));
			++it;
		}
	}

	if (!sentence.empty()) sentences.push_back(std::move(sentence));
	return sentences;
}

struct TestToken {
	string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const {
		return is_end_sentence_punctuation;
	}

	bool operator==(const TestToken &other) const {
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
};

ostream &operator<<(ostream &stream, const TestToken &token) {
	return stream << token.data;
}

void TestSplitting() { // ���� �������� ����������� �������� ������ TestToken. // ��� �������� ���������� ����������� � ������� SplitIntoSentences // ���������� �������� ��������� ����.
	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!"}}
			})
	);

	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}}
			})
	);

	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
			{{"Without"}, {"copies"}, {".", true}},
			})
			);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestSplitting);

	return 0;
}
#endif //1

/*
��������� �� �����������
�������

��� ������ �������. �������� �������, ����������� ������ �� �����������:

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens);

Token � ��������� ���, ��� ������� �������� ���� ��, ��� �� ����� ����������� ����� IsEndSentencePunctuation, ������������ true, ���� ����� �������� ������ ����������, ������������� �����������, � false � ��������� ������. ������� ����� ���� ��������� ����������. ��� ������� ����������� ���� �������� �� �������� ������ ����������.

Sentence � ������� ��� ���� vector, ����������� ��������� �������:

// ��������� Sentence<Token> ��� ������������� ���� Token
// ��������� vector<Token>.
// ��������� ����� � �������� ������������� ��������
// ������� ����� ������� �� ������������ ������ ��������,
// � ������ ����������� � vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

������������ ��������� ������������������ �������, ��������������� ������ ������� ��������, ����������� ������� ���������� ����� �����������. ����� �������, ����� ����������� ������ �������� �� ���� ������:

	������, ��� ������� IsEndSentencePunctuation ���������� false (����� ������ ������� �������������� � ����������� �� �����������, ��������, ������� �����������);
	������, ��� ������� IsEndSentencePunctuation ���������� true (����� ������ ������� �������������� � ����������� �� �����������, ��������, ���������� �����������).

�����������

������������ ���������� ������� � 10^6. ����� ���������� ������ ������ ������� ���������� 1 ��������.
���� � ���������� �������

split_into_sentences.cpp
*/