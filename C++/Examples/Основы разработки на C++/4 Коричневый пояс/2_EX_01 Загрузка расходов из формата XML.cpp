#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week2/01%20Practice%20Assignment

#include <sstream>
#include <string_view>
#include <unordered_map>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#pragma region xml.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/01%20Practice%20Assignment/xml.h
class Node {
	string name;
	vector<Node> children;
	unordered_map<string, string> attrs;
public:
	Node(string name, unordered_map<string, string> attrs) : name(move(name)), attrs(move(attrs)) {} //ORIG Node(string name, unordered_map<string, string> attrs);
	const vector<Node> &Children() const { return children; }; //ORIG const vector<Node> &Children() const;
	void AddChild(Node node) { children.push_back(move(node)); } //ORIG void AddChild(Node node);
	string_view Name() const { return name; } //ORIG string_view Name() const;
	template <typename T> T AttributeValue(const string &name) const;
};

template <typename T>
inline T Node::AttributeValue(const string &name) const {
	istringstream attr_input(attrs.at(name));
	T result;
	attr_input >> result;
	return result;
}

class Document {
	Node root;
public:
	explicit Document(Node root) : root(move(root)) {} //ORIG explicit Document(Node root);
	const Node &GetRoot() const { return root; } //ORIG const Node &GetRoot() const;
};
#pragma endregion //xml.h

#pragma region xml.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/01%20Practice%20Assignment/xml.cpp
pair<string_view, string_view> Split(string_view line, char by) {
	size_t pos = line.find(by);
	string_view left = line.substr(0, pos);

	if (pos < line.size() && pos + 1 < line.size()) 
		return {left, line.substr(pos + 1)};
	else 
		return {left, string_view()};
}

string_view Lstrip(string_view line) {
	while (!line.empty() && isspace(line[0]))
		line.remove_prefix(1);
	return line;
}

string_view Unquote(string_view value) {
	if (!value.empty() && value.front() == '"')
		value.remove_prefix(1);
	if (!value.empty() && value.back() == '"')
		value.remove_suffix(1);
	return value;
}

Node LoadNode(istream &input) {
	string root_name;
	getline(input, root_name);

	Node root(root_name.substr(1, root_name.size() - 2), {});
	for (string line; getline(input, line) && Lstrip(line)[1] != '/'; ) {
		auto [node_name, attrs] = Split(Lstrip(line), ' ');
		attrs = Split(attrs, '>').first;
		unordered_map<string, string> node_attrs;
		while (!attrs.empty()) {
			auto [head, tail] = Split(attrs, ' ');
			auto [name, value] = Split(head, '=');
			if (!name.empty() && !value.empty())
				node_attrs[string(Unquote(name))] = string(Unquote(value));
			attrs = tail;
		}

		root.AddChild(Node(string(node_name.substr(1)), move(node_attrs)));
	}
	return root;
}

Document Load(istream &input) {	
	return Document{LoadNode(input)}; 
}
//ORIG Node::Node(string name, unordered_map<string, string> attrs) : name(move(name)), attrs(move(attrs)) {}
//ORIG const vector<Node> &Node::Children() const { return children; }
//ORIG Document::Document(Node root) : root(move(root)) {}
//ORIG const Node &Document::GetRoot() const { return root; }
//ORIG void Node::AddChild(Node node) { children.push_back(move(node)); }
//ORIG string_view Node::Name() const { return name; }
#pragma endregion //xml.cpp

#pragma region spendings_xml.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/01%20Practice%20Assignment/spendings_xml.cpp
struct Spending {
	string category;
	int amount;
};

bool operator == (const Spending &lhs, const Spending &rhs) { return lhs.category == rhs.category && lhs.amount == rhs.amount; }
ostream &operator << (ostream &os, const Spending &s) {	return os << '(' << s.category << ": " << s.amount << ')'; }

int CalculateTotalSpendings(const vector<Spending> &spendings) {
	int result = 0;
	for (const Spending &s : spendings) 
		result += s.amount;
	return result;
}

string MostExpensiveCategory(const vector<Spending> &spendings) {
	auto compare_by_amount =
		[](const Spending &lhs, const Spending &rhs) {
		return lhs.amount < rhs.amount;
	};
	return max_element(begin(spendings), end(spendings), compare_by_amount)->category;
}

vector<Spending> LoadFromXml(istream &input) { //MINE
	Document doc = Load(input);
	const vector<Node> &children = doc.GetRoot().Children();
	vector<Spending> result;
	result.reserve(children.size());
	for (const Node &child : children)
		result.emplace_back(child.AttributeValue<string>("category"), child.AttributeValue<int>("amount"));
	return result;
}

void TestLoadFromXml() {
	istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="1150" category="transport"></spend>
    <spend amount="5780" category="restaurants"></spend>
    <spend amount="7500" category="clothes"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
	</july>)");
	const vector<Spending> spendings = LoadFromXml(xml_input);

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

void TestXmlLibrary() {
	istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
  </july>)");

	Document doc = Load(xml_input);
	const Node &root = doc.GetRoot();
	ASSERT_EQUAL(root.Name(), "july");
	ASSERT_EQUAL(root.Children().size(), 3u);

	const Node &food = root.Children().front();
	ASSERT_EQUAL(food.AttributeValue<string>("category"), "food");
	ASSERT_EQUAL(food.AttributeValue<int>("amount"), 2500);

	const Node &sport = root.Children().back();
	ASSERT_EQUAL(sport.AttributeValue<string>("category"), "sport");
	ASSERT_EQUAL(sport.AttributeValue<int>("amount"), 12000);

	Node july("july", {});
	Node transport("spend", {{"category", "transport"}, {"amount", "1150"}});
	july.AddChild(transport);
	ASSERT_EQUAL(july.Children().size(), 1u);
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestXmlLibrary);
	RUN_TEST(tr, TestLoadFromXml);
}
#pragma endregion //spendings_xml.cpp
#endif //1

/*
В этой тренировочной задаче вам надо поддержать загрузку расходов из формата XML в нашей программе управления личными финансами. При этом вам надо воспользоваться готовой библиотекой работы с XML. Более конкретно, вам надо написать функцию vector LoadFromXml(istream& input). Spending — это структура из вводной лекции:

struct Spending {
string category;
int amount;
};

Поток input содержит описание расходов в формате XML, например:

<july>
<spend amount="2500" category="food"></spend>
<spend amount="1150" category="transport"></spend>
<spend amount="5780" category="restaurants"></spend>
<spend amount="7500" category="clothes"></spend>
<spend amount="23740" category="travel"></spend>
<spend amount="12000" category="sport"></spend>
</july>

Важно отметить:

	формат текста в потоке input всегда строго такой, как в примере: есть один корневой узел, который содержит несколько узлов с атрибутами "amount" и "category"

	функция Load из выданной вам библиотеки работы с XML умеет загружать описанный выше формат

	мы выдаём вам не реальную библиотеку разбора XML, а лишь минимальный код, достаточный для работы описанным форматом данных

	цель этой задачи — не показать, как правильно парсить XML, а познакомить вас с кодом, на котором мы в дальнейшем будем разбирать пространства имён, поэтому очень важно, чтобы вы реализовали функцию LoadFromXml через содержимое нашей библиотеки работы с XML.

На проверку пришлите cpp-файл, который подключает файл xml.h (дан ниже) и содержит реализацию функции LoadFromXml. Тестирующая система соберёт его вместе с файлом xml.cpp и прогонит набор юнит-тестов.
*/