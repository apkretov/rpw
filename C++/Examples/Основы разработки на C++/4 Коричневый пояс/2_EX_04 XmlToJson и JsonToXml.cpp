#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week2/04%20Practice%20Assignment

#include <istream>
#include <map>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#pragma region xml.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/04%20Practice%20Assignment/xml.h
namespace Xml {
	class Node {
	public:
		Node(string name, unordered_map<string, string> attrs);

		const vector<Node> &Children() const;
		void AddChild(Node node);
		string_view Name() const;

		template <typename T>
		T AttributeValue(const string &name) const;

	private:
		string name;
		vector<Node> children;
		unordered_map<string, string> attrs;
	};

	class Document {
	public:
		explicit Document(Node root);

		const Node &GetRoot() const;

	private:
		Node root;
	};

	Document Load(istream &input);




	template <typename T>
	inline T Node::AttributeValue(const string &name) const {
		istringstream attr_input(attrs.at(name));
		T result;
		attr_input >> result;
		return result;
	}

}
#pragma endregion //xml.h

#pragma region xml.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/04%20Practice%20Assignment/xml.cpp
namespace Xml {
	pair<string_view, string_view> Split(string_view line, char by) {
		size_t pos = line.find(by);
		string_view left = line.substr(0, pos);

		if (pos < line.size() && pos + 1 < line.size()) {
			return {left, line.substr(pos + 1)};
		} else {
			return {left, string_view()};
		}
	}

	string_view Lstrip(string_view line) {
		while (!line.empty() && isspace(line[0])) {
			line.remove_prefix(1);
		}
		return line;
	}

	string_view Unquote(string_view value) {
		if (!value.empty() && value.front() == '"') {
			value.remove_prefix(1);
		}
		if (!value.empty() && value.back() == '"') {
			value.remove_suffix(1);
		}
		return value;
	}

	Node LoadNode(istream &input) {
		string root_name;
		getline(input, root_name);

		Node root(root_name.substr(1, root_name.size() - 2), {});
		for (string line; getline(input, line) && line[1] != '/'; ) {
			auto [node_name, attrs] = Split(Lstrip(line), ' ');
			attrs = Split(attrs, '>').first;
			unordered_map<string, string> node_attrs;
			while (!attrs.empty()) {
				auto [head, tail] = Split(attrs, ' ');
				auto [name, value] = Split(head, '=');
				if (!name.empty() && !value.empty()) {
					node_attrs[string(Unquote(name))] = string(Unquote(value));
				}
				attrs = tail;
			}

			root.AddChild(Node(string(node_name.substr(1)), move(node_attrs)));
		}
		return root;
	}

	Document Load(istream &input) {
		return Document{LoadNode(input)};
	}

	Node::Node(
		string name, unordered_map<string, string> attrs
	) : name(move(name)), attrs(move(attrs)) {
	}

	const vector<Node> &Node::Children() const {
		return children;
	}

	Document::Document(Node root) : root(move(root)) {
	}

	const Node &Document::GetRoot() const {
		return root;
	}

	void Node::AddChild(Node node) {
		children.push_back(move(node));
	}

	string_view Node::Name() const {
		return name;
	}
}
#pragma endregion //xml.cpp

#pragma region json.h //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/04%20Practice%20Assignment/json.h
namespace Json {
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

}
#pragma endregion //json.h

#pragma region json.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/04%20Practice%20Assignment/json.cpp
namespace Json {
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

}
#pragma endregion //json.cpp

#pragma region solution.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/04%20Practice%20Assignment/solution.cpp
Json::Document XmlToJson(const Xml::Document &doc) {
	using namespace std;

	vector<Json::Node> result;

	for (const Xml::Node &n : doc.GetRoot().Children()) {
		result.emplace_back(map<string, Json::Node>{
			{"category", Json::Node{n.AttributeValue<string>("category")}},
			{"amount", Json::Node(n.AttributeValue<int>("amount"))}
		});
	}

	return Json::Document(Json::Node(move(result)));
}

Xml::Document JsonToXml(const Json::Document &doc, string root_name) {
	Xml::Node root(move(root_name), {});
	for (const Json::Node &n : doc.GetRoot().AsArray()) {
		root.AddChild(Xml::Node("spend", {
		  {"category", n.AsMap().at("category").AsString()},
		  {"amount", to_string(n.AsMap().at("amount").AsInt())},
			}));
	}
	return Xml::Document(move(root));
}

void TestXmlToJson() {
	using std::string;
	using std::vector;

	Xml::Node root("july", {});
	root.AddChild({"spend", {{"category", "travel"}, {"amount", "23400"}}});
	root.AddChild({"spend", {{"category", "food"}, {"amount", "5000"}}});
	root.AddChild({"spend", {{"category", "transport"}, {"amount", "1150"}}});
	root.AddChild({"spend", {{"category", "sport"}, {"amount", "12000"}}});
	const Xml::Document xml_doc(move(root));

	const auto json_doc = XmlToJson(xml_doc);

	const auto &items = json_doc.GetRoot().AsArray();
	ASSERT_EQUAL(items.size(), 4u);

	const vector<string> expected_category = {"travel", "food", "transport", "sport"};
	const vector<int> expected_amount = {23400, 5000, 1150, 12000};

	for (size_t i = 0; i < items.size(); ++i) {
		const map<string, Json::Node> &item = items[i].AsMap();
		const string feedback_msg = "i = " + to_string(i);
		AssertEqual(item.at("category").AsString(), expected_category[i], feedback_msg);
		AssertEqual(item.at("amount").AsInt(), expected_amount[i], feedback_msg);
	}
}

void TestJsonToXml() {
	using namespace std;

	vector<Json::Node> spendings;
	{
		using Json::Node; // Здесь мы очень много раз обращаемся к Json::Node, поэтому using Json::Node заметно сокращает наш код

		spendings = {
		  Node(map<string, Node>{
			{"category", Node("food")}, {"amount", Node(2500)}
		  }),
		  Node(map<string, Node>{
			{"category", Node("transport")}, {"amount", Node(1150)}
		  }),
		  Node(map<string, Node>{
			{"category", Node("restaurants")}, {"amount", Node(5780)}
		  }),
		  Node(map<string, Node>{
			{"category", Node("clothes")}, {"amount", Node(7500)}
		  }),
		  Node(map<string, Node>{
			{"category", Node("travel")}, {"amount", Node(23740)}
		  }),
		  Node(map<string, Node>{
			{"category", Node("sport")}, {"amount", Node(12000)}
		  }),
		};
	}
	const Json::Document json_doc{Json::Node(move(spendings))};

	const string root_name = "month";
	const auto xml_doc = JsonToXml(json_doc, root_name);
	const Xml::Node &root = xml_doc.GetRoot();

	ASSERT_EQUAL(root.Name(), root_name);
	const vector<Xml::Node> &children = root.Children();
	ASSERT_EQUAL(children.size(), 6u);

	const vector<string> expected_category = {
	  "food", "transport", "restaurants", "clothes", "travel", "sport"
	};
	const vector<int> expected_amount = {2500, 1150, 5780, 7500, 23740, 12000};

	for (size_t i = 0; i < children.size(); ++i) {
		const string feedback_msg = "i = " + to_string(i);
		const auto &c = children[i];
		AssertEqual(c.Name(), "spend", feedback_msg);
		AssertEqual(c.AttributeValue<string>("category"), expected_category[i], feedback_msg);
		AssertEqual(c.AttributeValue<int>("amount"), expected_amount[i], feedback_msg);
	}
}

int main() {
	PRINT_FILE_LINE();

	TestRunner tr;
	RUN_TEST(tr, TestXmlToJson);
	RUN_TEST(tr, TestJsonToXml);
	return 0;
}
#pragma endregion //solution.cpp
#endif //1

/*
Продолжим работать с примером, в котором мы создавали программу учёта личных финансов и работали с форматами JSON и XML. На этот раз мы решили добавить в неё возможность конвертировать список расходов из XML в JSON и наоборот. Для этого мы написали две функции:

	Json::Document XmlToJson(const Xml::Document& doc)

	Xml::Document JsonToXml(const Json::Document& doc, string root_name)

Кроме того, мы покрыли их юнит-тестами в функциях TestXmlToJson и TestJsonToXml. Но есть одна проблема — весь этот код писал начинающий специалист, который посмотрел все лекции нашего курса, но, не решив ни одной задачи, сразу стал применять полученные знания в работе. Он обратился к вам за помощью, передал свой код и, сказав: «Что-то у меня не компилируется», ушёл в отпуск. Ваша задача — привести в порядок код его функций и тестов, то есть сделать так, чтобы они компилировались и работали.

Более подробно, функция XmlToJson ожидает на вход документ, имеющий структуру ..., то есть в корневом узле лежит ноль или больше узлов с именем "spend" и атрибутами "amount" и "category". Она должна возвращать объект класса Json::Document, имеющий структуру [{"amount": 2500, "category": "food"}, ...], то есть это массив, содержащий столько словарей, сколько было узлов в XML-документе. При этом в словарях узёл по ключу "amount" должен быть целочисленным, а по ключу "category" — строковым. Гарантируется, что в тестирующей системе на вход вашей функции будут подаваться только XML-документы, соответствующие описанному формату (то есть обрабатывать некорректный ввод в данной задаче не надо).

Функция JsonToXml должна выполнять обратное преобразование. Точно так же в нашей тестирующей системе ей на вход будут подаваться только JSON-документы, соответствующие описанному формату.

Тесты TestXmlToJson и TestJsonToXml не должны принимать пустые реализации функций XmlToJson и JsonToXml, а также реализации, нарушающие формат выходных данных. Вам не надо добавлять в тесты другие тестовые случаи, надо заставить компилироваться и работать те, которые есть.

На проверку пришлите cpp-файл, который

	подключает файлы xml.h и json.h

	содержит реализацию функций XmlToJson, JsonToXml, TestJsonToXml, TestXmlToJson

Вам даны файлы xml.h/cpp и json.h/cpp, приведённые в соответствие с рекомендациями последней лекции. Именно они будут использоваться в процессе тестирования вашей посылки.
*/