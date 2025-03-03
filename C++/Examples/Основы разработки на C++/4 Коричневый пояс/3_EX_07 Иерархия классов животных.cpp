#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/07%20Practice%20Assignment

#include <memory>
#include <stdexcept>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

class Animal {
public:
	virtual string Voice() const { return "Not implemented yet"; }
	virtual ~Animal() {}
};

class Tiger : public Animal {
	string Voice() const override { return "Rrrr"; }
};

class Wolf : public Animal {
	string Voice() const override { return "Wooo"; }
};

class Fox : public Animal {
	string Voice() const override { return "Tyaf"; }
};

using Zoo = vector<unique_ptr<Animal>>;

Zoo CreateZoo(istream &in) {
	Zoo zoo;
	string word;
	while (in >> word) {
		if (word == "Tiger")
			zoo.emplace_back(make_unique<Tiger>());
		else if (word == "Wolf")
			zoo.emplace_back(make_unique<Wolf>());
		else if (word == "Fox")
			zoo.emplace_back(make_unique<Fox>());
		else
			throw runtime_error("Unknown animal!");
	}
	return zoo;
}

void Process(const Zoo &zoo, ostream &out) {
	for (const auto &animal : zoo)
		out << animal->Voice() << "\n";
}

void TestZoo() {
	istringstream input("Tiger Wolf Fox Tiger");
	ostringstream output;
	Process(CreateZoo(input), output);
	const string expected =
		"Rrrr\n"
		"Wooo\n"
		"Tyaf\n"
		"Rrrr\n";
	ASSERT_EQUAL(output.str(), expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestZoo);
}
#endif //1

/*
Вы работаете с иерархией классов, описывающих животных:

#include <string>

class Animal {
public:
  virtual std::string Voice() const {
	return "Not implemented yet";
  }
  virtual ~Animal() {
  }
};

class Tiger: public Animal {
  std::string Voice() const override {
	return "Rrrr";
  }
};

class Wolf: public Animal {
  std::string Voice() const override {
	return "Wooo";
  }
};

class Fox: public Animal {
  std::string Voice() const override {
	return "Tyaf";
  }
};

Вам нужно определить тип Zoo, представляющий собой набор различных животных, и написать две функции:

	Zoo CreateZoo(std::istream& in)

	void Process(const Zoo& zoo, std::ostream& out)

Функция CreateZoo должна читать слова из потока ввода. Если на вход поступают слова "Tiger", "Wolf" или "Fox", она должна помещать соответствующего зверя в зоопарк. В противном случае она должна прекратить чтение и сгенерировать исключение std::runtime_error.

Функция Process должна перебрать всех зверей в зоопарке в порядке создания и записать в поток вывода для каждого из них результат работы виртуальной функции Voice.

Один ваш друг написал решение этой задачи, но оно почему-то не работает. Исправьте его и сдайте в систему.
Замечания:

	Код классов из файла animals.h переписывать не надо, просто подключите заголовочный файл animals.h.

	Обратите внимание, что в нашей версии файла animals.h голоса зверей могут отличаться от того, что приведено в примере.

	Ваша программа должна создавать ровно столько объектов-зверей, сколько было передано во входном потоке в функцию CreateZoo.

Неверное решение вашего друга и файл animals.h
*/
