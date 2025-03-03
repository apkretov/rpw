#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week2/02%20Practice%20Assignment

#include <istream>
#include <map>
#include <sstream>
#include <unordered_map>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#pragma region json.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/02%20Practice%20Assignment/json.h
class Node {
public:
	explicit Node(vector<Node> array);
	explicit Node(map<string, Node> map);
	explicit Node(int value);
	explicit Node(string value);

	const vector<Node> &AsArray() const;
	const map<string, Node> &AsMap() const;
	int AsInt() const;
	const string &AsString() const;

private:
	vector<Node> as_array;
	map<string, Node> as_map;
	int as_int;
	string as_string;
};

class Document {
public:
	explicit Document(Node root);

	const Node &GetRoot() const;

private:
	Node root;
};

Document Load(istream &input);
#pragma endregion //json.h

#pragma region json.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/02%20Practice%20Assignment/json.cpp
Node::Node(vector<Node> array) : as_array(move(array)) {
}

Node::Node(map<string, Node> map) : as_map(move(map)) {
}

Node::Node(int value) : as_int(value) {
}

Node::Node(string value) : as_string(move(value)) {
}

const vector<Node> &Node::AsArray() const {
	return as_array;
}

const map<string, Node> &Node::AsMap() const {
	return as_map;
}

int Node::AsInt() const {
	return as_int;
}

const string &Node::AsString() const {
	return as_string;
}

Document::Document(Node root) : root(move(root)) {
}

const Node &Document::GetRoot() const {
	return root;
}

Node LoadNode(istream &input);

Node LoadArray(istream &input) {
	vector<Node> result;

	for (char c; input >> c && c != ']'; ) {
		if (c != ',') {
			input.putback(c);
		}
		result.push_back(LoadNode(input));
	}

	return Node(move(result));
}

Node LoadInt(istream &input) {
	int result = 0;
	while (isdigit(input.peek())) {
		result *= 10;
		result += input.get() - '0';
	}
	return Node(result);
}

Node LoadString(istream &input) {
	string line;
	getline(input, line, '"');
	return Node(move(line));
}

Node LoadDict(istream &input) {
	map<string, Node> result;

	for (char c; input >> c && c != '}'; ) {
		if (c == ',') {
			input >> c;
		}

		string key = LoadString(input).AsString();
		input >> c;
		result.insert({move(key), LoadNode(input)});
	}

	return Node(move(result));
}

Node LoadNode(istream &input) {
	char c;
	input >> c;

	if (c == '[') {
		return LoadArray(input);
	} else if (c == '{') {
		return LoadDict(input);
	} else if (c == '"') {
		return LoadString(input);
	} else {
		input.putback(c);
		return LoadInt(input);
	}
}

Document Load(istream &input) {
	return Document{LoadNode(input)};
}
#pragma endregion //

#pragma region solution.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/02%20Practice%20Assignment/solution.cpp
struct Spending {
	string category;
	int amount;
};

vector<Spending> LoadFromJson(istream &input) {
	Document doc = Load(input);
	vector<Spending> result;
	for (const Node &node : doc.GetRoot().AsArray())
		result.push_back({node.AsMap().at("category").AsString(), node.AsMap().at("amount").AsInt()});
	return result;
}
#pragma endregion //solution.cpp 

#pragma region spendings_json.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/02%20Practice%20Assignment/spendings_json.cpp
bool operator == (const Spending &lhs, const Spending &rhs) {
	return lhs.category == rhs.category && lhs.amount == rhs.amount;
}

ostream &operator << (ostream &os, const Spending &s) {
	return os << '(' << s.category << ": " << s.amount << ')';
}

int CalculateTotalSpendings(
	const vector<Spending> &spendings
) {
	int result = 0;
	for (const Spending &s : spendings) {
		result += s.amount;
	}
	return result;
}

string MostExpensiveCategory(
	const vector<Spending> &spendings
) {
	auto compare_by_amount =
		[](const Spending &lhs, const Spending &rhs) {
		return lhs.amount < rhs.amount;
		};
	return max_element(begin(spendings), end(spendings),
		compare_by_amount)->category;
}

void TestLoadFromJson() {
	istringstream json_input(R"([
    {"amount": 2500, "category": "food"},
    {"amount": 1150, "category": "transport"},
    {"amount": 5780, "category": "restaurants"},
    {"amount": 7500, "category": "clothes"},
    {"amount": 23740, "category": "travel"},
    {"amount": 12000, "category": "sport"}
  ])");

	const vector<Spending> spendings = LoadFromJson(json_input);

	const vector<Spending> expected = {
	  {"food", 2500},
	  {"transport", 1150},
	  {"restaurants", 5780},
	  {"clothes", 7500},
	  {"travel", 23740},
	  {"sport", 12000}
	};
	ASSERT_EQUAL(spendings, expected);
}

void TestJsonLibrary() {

	istringstream json_input(R"([
    {"amount": 2500, "category": "food"},
    {"amount": 1150, "category": "transport"},
    {"amount": 12000, "category": "sport"}
  ])");

	Document doc = Load(json_input);
	const vector<Node> &root = doc.GetRoot().AsArray();
	ASSERT_EQUAL(root.size(), 3u);

	const map<string, Node> &food = root.front().AsMap();
	ASSERT_EQUAL(food.at("category").AsString(), "food");
	ASSERT_EQUAL(food.at("amount").AsInt(), 2500);

	const map<string, Node> &sport = root.back().AsMap();
	ASSERT_EQUAL(sport.at("category").AsString(), "sport");
	ASSERT_EQUAL(sport.at("amount").AsInt(), 12000);

	Node transport(map<string, Node>{{"category", Node("transport")}, {"amount", Node(1150)}});
	Node array_node(vector<Node>{transport});
	ASSERT_EQUAL(array_node.AsArray().size(), 1u);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestJsonLibrary);
	RUN_TEST(tr, TestLoadFromJson);
}
#pragma endregion //spendings_json.cpp
#endif //1

/*
В этой тренировочной задаче вам надо поддержать загрузку расходов из формата JSON в нашей программе управления личными финансами. При этом вам надо воспользоваться готовой библиотекой работы с JSON. Более конкретно, вам надо написать функцию vector LoadFromJson(istream& input). Spending — это структура из вводной лекции:

struct Spending {
string category;
int amount;
};

Поток input содержит описание расходов в формате JSON, например:

[
{"amount": 2500, "category": "food"},
{"amount": 1150, "category": "transport"},
{"amount": 5780, "category": "restaurants"},
{"amount": 7500, "category": "clothes"},
{"amount": 23740, "category": "travel"},
{"amount": 12000, "category": "sport"}
]

Важно отметить:

	формат текста в потоке input всегда строго такой, как в примере: есть массив, который содержит несколько словарей с ключами "amount" и "category"

	функция Load из выданной вам библиотеки работы с JSON умеет загружать описанный выше формат

	мы выдаём вам не реальную библиотеку разбора JSON, а лишь минимальный код, достаточный для работы описанным форматом данных

	цель этой задачи — не показать, как правильно парсить JSON, а познакомить вас с кодом, на котором мы в дальнейшем будем разбирать пространства имён, поэтому очень важно, чтобы вы реализовали функцию LoadFromJson через содержимое нашей библиотеки работы с JSON.

На проверку пришлите cpp-файл, который подключает файл json.h (дан ниже) и содержит реализацию функции LoadFromJson. Тестирующая система соберёт его вместе с файлом json.cpp и прогонит набор юнит-тестов.
*/