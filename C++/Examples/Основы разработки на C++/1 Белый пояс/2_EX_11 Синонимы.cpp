#if 0

#include <iostream>
#include <map>
#include <set>
#include <string>
#include "../../stdafx.h"
//OFF #include "vld.h"
using namespace std;

#ifdef MINE

namespace ex_01_syn_dic {
	class syn_dic {
	public:
		using size = map<string, set<string, less<>>, less<>>::size_type;
		void add(const string &, const string &);
		size count(const string &) const;
		bool check(const string &, const string &) const;
	private:
		map<string, set<string, less<>>, less<>> syns;
	};

	inline void syn_dic::add(const string &word1, const string &word2) {
		try {
			syns[word1].insert(word2);
		}
		catch (const bad_alloc &e) {
			cerr << "Memory allocation error while adding synonym: " << e.what() << '\n';
			throw;
		}
		catch (const length_error &e) {
			cerr << "Length error while adding synonym: " << e.what() << '\n';
			throw;
		}
	}

	inline syn_dic::size syn_dic::count(const string &word) const {
		try {
			return syns.at(word).size();
		}
		catch (const out_of_range &e) {
			cerr << "Error: '" << word << "' does not exist in the map: " << e.what() << '\n';
			throw;
		}
	}

	inline bool syn_dic::check(const string &word1, const string &word2) const {
		if (auto it = syns.find(word1); it != syns.end())
			return it->second.contains(word2);

		if (auto it = syns.find(word2); it != syns.end())
			return it->second.contains(word1);

		return false; // Explicitly return false if neither word is found.
	}

} //namespace ex_01_syn_dic

using namespace ex_01_syn_dic;

int main() {
	try {
		PRINT_FILE_LINE();

		const string word1 = "word1";
		syn_dic dic;

		dic.add(word1, "synonym11");
		dic.add(word1, "synonym12");
		dic.add("word2", "synonym2");
		dic.add("synonym2", "word2");

		cout << format(R"(dic.check("aaa", "bbb") = {})", dic.check("aaa", "bbb"));
		cout << format("\ndic.count(\"{}\") = {}\n", word1, dic.count(word1));
		cout << R"(dic.count("aaa") = )" << dic.count("aaa") << '\n';

		return 0;
	}
	catch (const bad_alloc &e) {
		cerr << "Caught error in main: Memory allocation error: " << e.what() << '\n';
	}
	catch (const length_error &e) {
		cerr << "Caught error in main: Length error: " << e.what() << '\n';
	}
	catch (const out_of_range &e) {
		cerr << "Caught error in main: Key does not exist in the map: " << e.what() << '\n';
	}
	catch (const exception &e) {
		cerr << "Caught error in main: " << e.what() << '\n';
	}
	catch (...) {
		cerr << "Caught an unknown error in main.\n";
	}
}

#else //GITHUB @ https://github.com/avtomato/Basics-of-C-plus-plus-development-white-belt/blob/master/week-02/17-Programming-Assignment/Solution/synonyms.cpp

int main() {
	PRINT_FILE_LINE();

	int q;
	cin >> q;

	map<string, set<string>> synonyms;
	for (int i = 0; i < q; ++i) {
		string operation_code;
		cin >> operation_code;
		if (operation_code == "ADD") {
			string first_word, second_word;
			cin >> first_word >> second_word;
			synonyms[first_word].insert(second_word); // ������ ����� ��������� � ������ ��������� �������...
			synonyms[second_word].insert(first_word); // � ��������
		} else if (operation_code == "COUNT") {
			string word;
			cin >> word;
			cout << synonyms[word].size() << endl;
		} else if (operation_code == "CHECK") {
			string first_word, second_word;
			cin >> first_word >> second_word;
			if (synonyms[first_word].count(second_word) == 1) // ���� ������ ����� �� ��������� ��������� ������� (����� ���� ������� � ��������)
				cout << "YES" << endl;
			 else 
				cout << "NO" << endl;
		}
	}
	return 0;
}
#endif //GITHUB

#endif //1

/*
������� �� ����������������: ��������

��� ����� ���������� ���������� ���� �����, ���� ��� ����� ������� ��������. ���������� ��������� �������� ��� ������� ���������:

	ADD word1 word2 � �������� � ������� ���� ��������� (word1, word2).
	COUNT word � ������ ���������� ��������� ����� word.
	CHECK word1 word2 � ���������, �������� �� ����� word1 � word2 ����������. ����� word1 � word2 ��������� ����������, ���� ����� �������� ADD ��� ���� �� ���� ������ ADD word1 word2 ��� ADD word2 word1.

������ �����

������� �������� ���������� �������� Q, ����� Q ����� � ���������� ��������. �������������, ��� � ������ ������� CHECK � ADD ����� word1 � word2 ��������. ��� ����� ������� ���� �� ��������� ����, ���� � �������� �������������.
������ ������

��� ������� ������� � ��������������� ������ �������� ����� �� ����:

	� ����� �� ������ COUNT word �������� ������������ ����� ����� � ���������� ��������� ����� word.
	� ����� �� ������ CHECK word1 word2 �������� ������ YES, ���� word1 � word2 �������� ����������, � NO � ��������� ������.

������
����

8
ADD program code
COUNT cipher
ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java

�����

0
2
1
YES
NO
NO
*/