#if 0 //@ https://github.com/Reavolt/basics-of-c-plus-plus-development-red-belt/tree/main/Week_4/06%20Programming%20Assignment/Solution

#include <iostream>
#include <map>
#include <string_view>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

#undef ERR

struct HttpRequest {
	string_view method, uri, protocol;
};

class Stats {
public:
	Stats();
	void AddMethod(std::string_view method);
	void AddUri(std::string_view uri);
	const std::map<std::string_view, int> &GetMethodStats() const;
	const std::map<std::string_view, int> &GetUriStats() const;
private:
	std::map<std::string_view, int> method_stats;
	std::map<std::string_view, int> uri_stats;
};

HttpRequest ParseRequest(string_view line);

Stats::Stats() {
	method_stats = {{"GET", 0}, {"POST", 0}, {"PUT", 0}, {"DELETE", 0}, {"UNKNOWN", 0}};
	uri_stats = {{"/", 0}, {"/order", 0}, {"/product", 0}, {"/basket", 0}, {"/help", 0}, {"unknown", 0}};
}

void Stats::AddMethod(std::string_view method) {
	if (method_stats.find(method) != method_stats.end()) {
		method_stats[method]++;
	} else {
		method_stats["UNKNOWN"]++;
	}
}

void Stats::AddUri(std::string_view uri) {
	if (uri_stats.find(uri) != uri_stats.end()) {
		uri_stats[uri]++;
	} else {
		uri_stats["unknown"]++;
	}
}

const std::map<std::string_view, int> &Stats::GetMethodStats() const {
	return method_stats;
}

const std::map<std::string_view, int> &Stats::GetUriStats() const {
	return uri_stats;
}

HttpRequest ParseRequest(std::string_view line) {
	HttpRequest parse;
	line.remove_prefix(line.find_first_not_of(" ")); //TEST!

	parse.method = line.substr(0, line.find(" "));
	line.remove_prefix(std::min(line.find(" ") + 1, line.size()));

	parse.uri = line.substr(0, line.find(" "));
	line.remove_prefix(std::min(line.find(" ") + 1, line.size()));

	parse.protocol = line.substr(0, line.find(" "));

	return parse;
}

Stats ServeRequests(istream &input) {
	Stats result;
	for (string line; getline(input, line); ) {
		const HttpRequest req = ParseRequest(line);
		result.AddMethod(req.method);
		result.AddUri(req.uri);
	}
	return result;
}

#ifdef ERR
void TestBasic() {
	const string input =
		R"(GET / HTTP/1.1
		POST /order HTTP/1.1
		POST /product HTTP/1.1
		POST /product HTTP/1.1
		POST /product HTTP/1.1
		GET /order HTTP/1.1
		PUT /product HTTP/1.1
		GET /basket HTTP/1.1
		DELETE /product HTTP/1.1
		GET / HTTP/1.1
		GET / HTTP/1.1
		GET /help HTTP/1.1
		GET /upyachka HTTP/1.1
		GET /unexpected HTTP/1.1
		HEAD / HTTP/1.1)";

	const map<string_view, int> expected_method_count = {
	  {"GET", 8},
	  {"PUT", 1},
	  {"POST", 4},
	  {"DELETE", 1},
	  {"UNKNOWN", 1},
	};
	const map<string_view, int> expected_url_count = {
	  {"/", 4},
	  {"/order", 2},
	  {"/product", 5},
	  {"/basket", 1},
	  {"/help", 1},
	  {"unknown", 2},
	};

	istringstream is(input);
	const Stats stats = ServeRequests(is);

	ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
	ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts() {
	// Методы GetMethodStats и GetUriStats должны возвращать словари
	// с полным набором ключей, даже если какой-то из них не встречался

	const map<string_view, int> expected_method_count = {
	  {"GET", 0},
	  {"PUT", 0},
	  {"POST", 0},
	  {"DELETE", 0},
	  {"UNKNOWN", 0},
	};
	const map<string_view, int> expected_url_count = {
	  {"/", 0},
	  {"/order", 0},
	  {"/product", 0},
	  {"/basket", 0},
	  {"/help", 0},
	  {"unknown", 0},
	};
	const Stats default_constructed;

	ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
	ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}
#endif //ERR

int main() {
	PRINT_FILE_LINE();

#ifdef ERR
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
	RUN_TEST(tr, TestAbsentParts);
#endif //ERR
}
#endif

/*
Статистика web-сервера
Условие

Представим, что у нас есть web-сервер, который обслуживает запросы к интернет-магазину. Он поддерживает следующий набор запросов по протоколу HTTP:

	GET / HTTP/1.1 — получить главную страницу магазина
	POST /order HTTP/1.1 — разместить новый заказ
	POST /product HTTP/1.1 — добавить новый товар в магазин (команда админки)
	GET /order HTTP/1.1 — получить детали заказа
	PUT /product HTTP/1.1 — то же самое, что и POST /order HTTP/1.1
	GET /basket HTTP/1.1 — получить состав текущей корзины клиента
	DELETE /product HTTP/1.1 — удалить товар из интернет-магазина (команда админки)
	GET /help HTTP/1.1 — получить страницу о том, как пользоваться интернет-магазином

С точки зрения протокола HTTP, первые части приведённых выше запросов («GET», «POST», «PUT», «DELETE») называются методами. Вторые части называются URI (Uniform Resource Identifier). Третья часть — это версия протокола. Таким образом, наш web-сервер поддерживает 4 метода: GET, POST, PUT, DELETE и 5 URI: «/», «/order», «/product», «/basket», «/help».

Главный системный администратор нашего сервера озаботился его масштабированием и для начала он решил изучить статистику использования. Он хочет для каждого метода и каждого URI посчитать, сколько раз он встречался в запросах к серверу за последний месяц. Он попросил вас помочь с этим.

У вас уже есть какая-то кодовая база для изучения запросов к серверу, и вы хотите воспользоваться ею, чтобы сэкономить время. У вас есть заголовочный файл http_request.h, содержащий структуру HttpRequest:

#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};

Кроме того, есть заголовочный файл stats.h, содержащий объявления класса Stats и функции ParseRequest:

#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

using namespace std;

class Stats {
public:
  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);

Наконец, у вас есть готовая функция ServeRequests:

Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
	const HttpRequest req = ParseRequest(line);
	result.AddUri(req.uri);
	result.AddMethod(req.method);
  }
  return result;
}

Вам нужно, основываясь на реализации функции ServeRequests, реализовать класс Stats и функцию ParseRequest.

	метод GetMethodStats возвращает словарь, в котором для каждого метода хранится, сколько раз он встретился в качестве аргумента метода AddMethod;
	метод GetUriStats работает аналогично для URI;
	если метод, переданный в метод AddMethod, не поддерживается нашим сервером (список поддерживаемых методов приведён выше), то нужно на единицу увеличить счётчик для метода "UNKNOWN" (подробнее см. юнит-тесты в заготовке решения);
	если URI, переданный в метод AddUri, не поддерживается нашим сервером, то нужно на единицу увеличить счётчик для URI "unknown".

Дополнительные сведения о функции ParseRequest:

	функция ParseRequest разбивает исходный запрос на три соответствующих части (метод, URI, версия протокола), возвращая результат в полях соответствующей структуры HttpRequest;
	при разборе исходного запроса, каждую часть запроса необходимо выделять и сохранять в результирующую структуру без каких-либо дополнительных изменений. Например, для запроса "UNDEFINED /something HTTP/1.1++", в поля метода, URI и протокола структуры HttpRequest необходимо записать "UNDEFINED", "/something" и "HTTP/1.1++", соответственно.

На проверку пришлите архив, состоящий из файлов stats.h и stats.cpp (а также любых других файлов, которые вы посчитаете нужным добавить в свой проект). При этом ваши файлы не должны содержать реализацию функции ServeRequests (если ваша посылка будет содержать функцию ServeRequests, вы получите ошибку компиляции).
Заготовка решения

http_request.h

stats.h

server_stats.cpp
Как будет тестироваться ваша посылка

К проекту из вашего архива будет добавлен cpp-файл, который:

	подключает заголовочный файл stats.h;
	содержит точно такую же реализацию функции ServeRequests, какая приведена в условии;
	содержит функцию main с набором юнит-тестов для функции ServeRequests

Ваш проект будет собран и запущен.
*/