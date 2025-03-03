#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week2/03%20Programming%20Assingment

#include <istream>
#include <sstream>
#include <unordered_map>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#pragma region ini.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/03%20Programming%20Assingment/ini.h
namespace Ini {
	using Section = unordered_map<string, string>;

	class Document {
	public:
		Section &AddSection(string name);
		const Section &GetSection(const string &name) const;
		size_t SectionCount() const;
	private:
		unordered_map<string, Section> sections;
	};

	Document Load(istream &input);
}
#pragma endregion //ini.h

#pragma region solution.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/03%20Programming%20Assingment/solution.cpp
namespace Ini {
	Document Load(istream &input) {
		Document result;

		Section *current_section = nullptr;
		for (string line; getline(input, line);) {
			if (!line.empty()) {
				if (line[0] == '[')
					current_section = &result.AddSection(line.substr(1, line.size() - 2));
				else {
					size_t eq_pos = line.find('=');
					current_section->insert({line.substr(0, eq_pos), line.substr(eq_pos + 1)});
				}
			}
		}

		return result;
	}

	Section &Document::AddSection(string name) {
		return sections[name];
	}

	const Section &Document::GetSection(const string &name) const {
		return sections.at(name);
	}

	size_t Document::SectionCount() const {
		return sections.size();
	}

} //Ini
#pragma endregion //solution.cpp

#pragma region ini.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/03%20Programming%20Assingment/ini.cpp
pair<string, string> Split(string line, char by) {
	size_t pos = line.find(by);
	string left = line.substr(0, pos);
	return {left, line.substr(pos + 1)};
}
#pragma endregion //ini.cpp

#pragma region test_ini.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/03%20Programming%20Assingment/test_ini.cpp
void TestLoadIni() {
	istringstream input(
		R"([july]
			food=2500
			sport=12000
			travel=23400
			clothes=5200

			[august]
			food=3250
			sport=10000
			travel=0
			clothes=8300
			jewelery=25000
		)"
	);

	const Ini::Document doc = Ini::Load(input);

	ASSERT_EQUAL(doc.SectionCount(), 2u);

	const Ini::Section expected_july = {
	  {"food", "2500"},
	  {"sport", "12000"},
	  {"travel", "23400"},
	  {"clothes", "5200"},
	};

	const Ini::Section expected_august = {
	  {"food", "3250"},
	  {"sport", "10000"},
	  {"travel", "0"},
	  {"clothes", "8300"},
	  {"jewelery", "25000"},
	};

	ASSERT_EQUAL(doc.GetSection("july"), expected_july);
	ASSERT_EQUAL(doc.GetSection("august"), expected_august);
}

void TestDocument() {
	Ini::Document doc;
	ASSERT_EQUAL(doc.SectionCount(), 0u);

	Ini::Section *section = &doc.AddSection("one");
	ASSERT_EQUAL(doc.SectionCount(), 1u);

	section->insert({"name_1", "value_1"});
	section->insert({"name_2", "value_2"});

	section = &doc.AddSection("two");
	section->insert({"name_1", "value_1"});
	section->insert({"name_2", "value_2"});
	section->insert({"name_3", "value_3"});

	section = &doc.AddSection("three");
	section->insert({"name_1", "value_1"});

	ASSERT_EQUAL(doc.SectionCount(), 3u);
	const Ini::Section expected_one = {{"name_1", "value_1"}, {"name_2", "value_2"}};
	const Ini::Section expected_two = {
	  {"name_1", "value_1"}, {"name_2", "value_2"}, {"name_3", "value_3"}
	};
	const Ini::Section expected_three = {{"name_1", "value_1"}};

	ASSERT_EQUAL(doc.GetSection("one"), expected_one);
	ASSERT_EQUAL(doc.GetSection("two"), expected_two);
	ASSERT_EQUAL(doc.GetSection("three"), expected_three);
}

void TestUnknownSection() {
	Ini::Document doc;
	doc.AddSection("primary");

	try {
		doc.GetSection("secondary");
		Assert(
			false,
			"Ini::Document::GetSection() should throw std::out_of_range for unknown section"
		);
	}
	catch (out_of_range &) {
	}
	catch (...) {
		Assert(
			false,
			"Ini::Document::GetSection() throws unexpected exception for unknown section"
		);
	}
}

void TestDuplicateSections() {
	Ini::Document doc;
	doc.AddSection("one").insert({"key_1", "value_1"});
	doc.AddSection("one").insert({"key_2", "value_2"});

	const Ini::Section expected = {{"key_1", "value_1"}, {"key_2", "value_2"}};
	ASSERT_EQUAL(doc.GetSection("one"), expected);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestLoadIni);
	RUN_TEST(tr, TestDocument);
	RUN_TEST(tr, TestUnknownSection);
	RUN_TEST(tr, TestDuplicateSections);
	return 0;
}
#pragma endregion //test_ini.cpp
#endif //1

/*
Библиотека работы с INI-файлами

В лекциях мы разработали библиотеки для загрузки данных из форматов XML и JSON, поместив каждую из них в своё пространство имён. В этой задаче вам нужно сделать то же самое для формата INI. Вам надо разработать библиотеку со следующим интерфейсом

using Section = unordered_map<string, string>;

class Document {
public:
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;

private:
  unordered_map<string, Section> sections;
};

Document Load(istream& input);

Требования:

	Содержимое библиотеки должно находиться в пространстве имён Ini

	Интерфейс, приведённый выше, должен быть объявлен в файле ini.h

	На проверку пришлите архив с полной реализацией библиотеки, в архиве должен быть файл ini.h

	В процессе тестирования функции Load ей на вход будет подаваться текст в формате

[секция 1]
ключ1=значение1
ключ2=значение2

[секция 2]
ключ3=значение3
ключ4=значение4

	Гарантируется, что в наших тестах используются только корректные ini-файлы, то есть строки вида ключ=значение всегда находятся внутри какой-то секции и содержат ровно один символ '='

	Строка ini-файла либо пустая, либо не содержит ведущих пробелов Примеры применения библиотеки смотрите в юнит-тестах в файле test_ini.cpp

Замечание
Возможно, вам придётся добавить поддержку unordered_map в своей версии файла test_runner.h
*/