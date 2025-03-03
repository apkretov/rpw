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
	// ������ GetMethodStats � GetUriStats ������ ���������� �������
	// � ������ ������� ������, ���� ���� �����-�� �� ��� �� ����������

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
���������� web-�������
�������

����������, ��� � ��� ���� web-������, ������� ����������� ������� � ��������-��������. �� ������������ ��������� ����� �������� �� ��������� HTTP:

	GET / HTTP/1.1 � �������� ������� �������� ��������
	POST /order HTTP/1.1 � ���������� ����� �����
	POST /product HTTP/1.1 � �������� ����� ����� � ������� (������� �������)
	GET /order HTTP/1.1 � �������� ������ ������
	PUT /product HTTP/1.1 � �� �� �����, ��� � POST /order HTTP/1.1
	GET /basket HTTP/1.1 � �������� ������ ������� ������� �������
	DELETE /product HTTP/1.1 � ������� ����� �� ��������-�������� (������� �������)
	GET /help HTTP/1.1 � �������� �������� � ���, ��� ������������ ��������-���������

� ����� ������ ��������� HTTP, ������ ����� ���������� ���� �������� (�GET�, �POST�, �PUT�, �DELETE�) ���������� ��������. ������ ����� ���������� URI (Uniform Resource Identifier). ������ ����� � ��� ������ ���������. ����� �������, ��� web-������ ������������ 4 ������: GET, POST, PUT, DELETE � 5 URI: �/�, �/order�, �/product�, �/basket�, �/help�.

������� ��������� ������������� ������ ������� ���������� ��� ���������������� � ��� ������ �� ����� ������� ���������� �������������. �� ����� ��� ������� ������ � ������� URI ���������, ������� ��� �� ���������� � �������� � ������� �� ��������� �����. �� �������� ��� ������ � ����.

� ��� ��� ���� �����-�� ������� ���� ��� �������� �������� � �������, � �� ������ ��������������� ��, ����� ���������� �����. � ��� ���� ������������ ���� http_request.h, ���������� ��������� HttpRequest:

#pragma once

#include <string_view>

using namespace std;

struct HttpRequest {
  string_view method, uri, protocol;
};

����� ����, ���� ������������ ���� stats.h, ���������� ���������� ������ Stats � ������� ParseRequest:

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

�������, � ��� ���� ������� ������� ServeRequests:

Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
	const HttpRequest req = ParseRequest(line);
	result.AddUri(req.uri);
	result.AddMethod(req.method);
  }
  return result;
}

��� �����, ����������� �� ���������� ������� ServeRequests, ����������� ����� Stats � ������� ParseRequest.

	����� GetMethodStats ���������� �������, � ������� ��� ������� ������ ��������, ������� ��� �� ���������� � �������� ��������� ������ AddMethod;
	����� GetUriStats �������� ���������� ��� URI;
	���� �����, ���������� � ����� AddMethod, �� �������������� ����� �������� (������ �������������� ������� ������� ����), �� ����� �� ������� ��������� ������� ��� ������ "UNKNOWN" (��������� ��. ����-����� � ��������� �������);
	���� URI, ���������� � ����� AddUri, �� �������������� ����� ��������, �� ����� �� ������� ��������� ������� ��� URI "unknown".

�������������� �������� � ������� ParseRequest:

	������� ParseRequest ��������� �������� ������ �� ��� ��������������� ����� (�����, URI, ������ ���������), ��������� ��������� � ����� ��������������� ��������� HttpRequest;
	��� ������� ��������� �������, ������ ����� ������� ���������� �������� � ��������� � �������������� ��������� ��� �����-���� �������������� ���������. ��������, ��� ������� "UNDEFINED /something HTTP/1.1++", � ���� ������, URI � ��������� ��������� HttpRequest ���������� �������� "UNDEFINED", "/something" � "HTTP/1.1++", ��������������.

�� �������� �������� �����, ��������� �� ������ stats.h � stats.cpp (� ����� ����� ������ ������, ������� �� ���������� ������ �������� � ���� ������). ��� ���� ���� ����� �� ������ ��������� ���������� ������� ServeRequests (���� ���� ������� ����� ��������� ������� ServeRequests, �� �������� ������ ����������).
��������� �������

http_request.h

stats.h

server_stats.cpp
��� ����� ������������� ���� �������

� ������� �� ������ ������ ����� �������� cpp-����, �������:

	���������� ������������ ���� stats.h;
	�������� ����� ����� �� ���������� ������� ServeRequests, ����� ��������� � �������;
	�������� ������� main � ������� ����-������ ��� ������� ServeRequests

��� ������ ����� ������ � �������.
*/