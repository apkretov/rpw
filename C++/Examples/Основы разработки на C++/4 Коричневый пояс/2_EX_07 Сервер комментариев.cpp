#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week2/07%20Programming%20Assignment
#pragma region comment_server.cpp //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week2/07%20Programming%20Assignment/source/comment_server.cpp
#include <sstream>
#include <utility>
#include <map>
#include <optional>
#include <unordered_set>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct HttpRequest {
	string method;
	string path;
	string body;
	map<string, string, less<>> get_params;
};

pair<string, string> SplitBy(const string &what, const string &by) {
	size_t pos = what.find(by);
	if (by.size() < what.size() && pos < what.size() - by.size()) {
		return {what.substr(0, pos), what.substr(pos + by.size())};
	} else {
		return {what, {}};
	}
}

template<typename T>
T FromString(const string &s) {
	T x;
	istringstream is(s);
	is >> x;
	return x;
}

pair<size_t, string> ParseIdAndContent(const string &body) {
	auto [id_string, content] = SplitBy(body, " ");
	return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo {
	size_t user_id;
	size_t consecutive_count;
};

#pragma region MINE
enum class HttpCode { Ok = 200, Found = 302, NotFound = 404 };

class HttpResponse {
	friend ostream &operator<<(ostream &output, const HttpResponse &resp);
	static unordered_map<HttpCode, string> code_names;
	HttpCode http_code;
	unordered_multimap<string, string, str_hash, str_equal> headers;
	string content;
public:
	explicit HttpResponse(HttpCode code) : http_code(code) {}
	HttpResponse &AddHeader(string name, string value);
	HttpResponse &SetContent(string a_content);
	HttpResponse &SetCode(HttpCode a_code);
};

unordered_map<HttpCode, string> HttpResponse::code_names = {
	{HttpCode::Ok, "Ok"},
	{HttpCode::Found, "Found"},
	{HttpCode::NotFound, "NotFound"},
};

HttpResponse &HttpResponse::AddHeader(string name, string value) {
	headers.emplace(std::move(name), std::move(value));
	return *this;
}

HttpResponse &HttpResponse::SetContent(string a_content) { 
	content = std::move(a_content); 
	return *this;
}

HttpResponse &HttpResponse::SetCode(HttpCode a_code) {
	http_code = a_code;
	return *this;
}

ostream &operator<<(ostream &output, const HttpResponse &resp) {
	output << "HTTP/1.1 " << static_cast<int>(resp.http_code) 
		<< " " << HttpResponse::code_names.at(resp.http_code);
	for (const auto &[name, value] : resp.headers) //<< "Content-Length: " << response.size() 
		output << "\n" << name << ": " << value;
	if (!resp.content.empty()) //<< response;
		output << "\n" << "\n" << resp.content;
	return output;
}

class CommentServer {
	vector<vector<string>> comments_;
	optional<LastCommentInfo> last_comment;
	unordered_set<size_t> banned_users;
	HttpResponse AddUser();
	HttpResponse AddComment(const HttpRequest &req);
	HttpResponse CheckCaptcha(const HttpRequest &req);
	HttpResponse GetUserComments(const HttpRequest &req) const;
	HttpResponse GetCaptcha() const;
public:
	HttpResponse ServeRequest(const HttpRequest &req);
};

HttpResponse CommentServer::ServeRequest(const HttpRequest &req) { //ORIG void ServeRequest(const HttpRequest &req, ostream &os) {
	if (req.method == "POST") {
		if (req.path == "/add_user")
			return AddUser();
		else if (req.path == "/add_comment")
			return AddComment(req);
		else if (req.path == "/checkcaptcha")
			return CheckCaptcha(req);
		else
			return HttpResponse{HttpCode::NotFound}; //ORIG os << "HTTP/1.1 404 Not found\n\n";
	} else if (req.method == "GET") {
		if (req.path == "/user_comments")
			return GetUserComments(req);
		else if (req.path == "/captcha")
			return GetCaptcha();
		else
			return HttpResponse{HttpCode::NotFound}; //ORIG os << "HTTP/1.1 404 Not found\n\n";
	} else //MINE
		return HttpResponse{HttpCode::NotFound};
}

HttpResponse CommentServer::AddUser() {
	comments_.emplace_back();
	auto response = to_string(comments_.size() - 1);
	return HttpResponse{HttpCode::Ok}.AddHeader("Content-Length", to_string(response.size())).SetContent(std::move(response)); //ORIG os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << "\n" << "\n" << response;
}

HttpResponse CommentServer::AddComment(const HttpRequest &req) {
	auto [user_id, comment] = ParseIdAndContent(req.body);
	if (!last_comment || last_comment->user_id != user_id)
		last_comment = LastCommentInfo{user_id, 1};
	else if (++last_comment->consecutive_count > 3)
		banned_users.insert(user_id);
	if (!banned_users.contains(user_id)) {
		comments_[user_id].emplace_back(comment);
		return HttpResponse{HttpCode::Ok}; //ORIG os << "HTTP/1.1 200 OK\n\n";
	} else
		return HttpResponse{HttpCode::Found}.AddHeader("Location", "/captcha"); //ORIG os << "HTTP/1.1 302 Found\n\n" "Location: /captcha\n" "\n"; //TEST!!
}

HttpResponse CommentServer::CheckCaptcha(const HttpRequest &req) {
	if (auto [id, response] = ParseIdAndContent(req.body); response == "42") {
		banned_users.erase(id);
		if (last_comment && last_comment->user_id == id)
			last_comment.reset();
		return HttpResponse{HttpCode::Ok}; //ORIG os << "HTTP/1.1 200 OK\n\n";
	} else //MINE
		return HttpResponse{HttpCode::Found}.AddHeader("Location", "/captcha");
}

HttpResponse CommentServer::GetUserComments(const HttpRequest &req) const {
	auto user_id = FromString<size_t>(req.get_params.at("user_id"));
	string response;
	for (const string &c : comments_[user_id])
		response += c + '\n';
	return HttpResponse{HttpCode::Ok}.AddHeader("Content-Length", to_string(response.size())).SetContent(std::move(response)); //TEST! //ORIG os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << response;
}

HttpResponse CommentServer::GetCaptcha() const {
	const string response = "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
	return HttpResponse{HttpCode::Ok}.AddHeader("Content-Length", to_string(response.size())).SetContent(std::move(response)); //ORIG os << "HTTP/1.1 200 OK\n" << "Content-Length: 80\n" << "\n" << "What's the answer for The Ultimate Question of Life, the Universe, and Everything?";
}
#pragma endregion //MINE

struct HttpHeader {
	string name, value;
};

ostream &operator<<(ostream &output, const HttpHeader &h) {
	return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader &lhs, const HttpHeader &rhs) {
	return lhs.name == rhs.name && lhs.value == rhs.value;
}

struct ParsedResponse {
	int code;
	vector<HttpHeader> headers;
	string content;
};

istream &operator>>(istream &input, ParsedResponse &r) {
	string line;
	getline(input, line);

	{
		istringstream code_input(line);
		string dummy;
		code_input >> dummy >> r.code;
	}

	size_t content_length = 0;

	r.headers.clear();
	while (getline(input, line) && !line.empty()) {
		if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
			istringstream length_input(value);
			length_input >> content_length;
		} else
			r.headers.push_back({std::move(name), std::move(value)});
	}

	r.content.resize(content_length);
	input.read(r.content.data(), r.content.size());
	return input;
}

void Test(CommentServer &srv, const HttpRequest &request, const ParsedResponse &expected) {
	stringstream ss;
	HttpResponse http_response = srv.ServeRequest(request); //ORIG srv.ServeRequest(request, ss);
	ss << http_response;

	ParsedResponse resp;
	ss >> resp;
	ASSERT_EQUAL(resp.code, expected.code);
	ASSERT_EQUAL(resp.headers, expected.headers);
	ASSERT_EQUAL(resp.content, expected.content);
}

template <typename CommentServer>
void TestServer() {
	CommentServer cs;

	const ParsedResponse ok{200};
	const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
	const ParsedResponse not_found{404};

	Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
	Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
	Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
	Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
	Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
	Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);
	Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
	Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
	Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
	Test(
		cs,
		{"GET", "/user_comments", "", {{"user_id", "0"}}},
		{200, {}, "Hello\nWhat are you selling?\n"}
	);
	Test(
		cs,
		{"GET", "/user_comments", "", {{"user_id", "1"}}},
		{200, {}, "Hi\nBuy my goods\nEnlarge\n"}
	);
	Test(
		cs,
		{"GET", "/captcha"},
		{200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}}
	);
	Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
	Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
	Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
	Test(
		cs,
		{"GET", "/user_comments", "", {{"user_id", "1"}}},
		{200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"}
	);

	Test(cs, {"GET", "/user_commntes"}, not_found);
	Test(cs, {"POST", "/add_uesr"}, not_found);
}

int main() {
	PRINT_FILE_LINE();
	TestRunner tr;
	RUN_TEST(tr, TestServer<CommentServer>);
}
#pragma endregion //comment_server.cpp
#endif //1

/*
������ ������������
�����������

� ���� ������ �� ������� ����, ��������� ��� chaining, ������� ������ ����������� �� ������ ������ ����������������, �������� � JavaScript. � C++ chaining ���� ����� ���� ���� ����������. ��������� this ��������� ��� ���������� chaining'�. ����� ����, ����� ������ �� ��������� �������������, �� ������� ���������� ����� ����� � �������� ������������ ��������, � ������� ����������� ���� �� �������������� �����.
�������

�� ������������ � �������, ������� ������������� web-������ ������������. ���� ������ ��������� ��������� ����� �������������, ����������� ����� ����������, � ����� ������ ��� ���������� ���������� ������������. ����� ���� ������� ������� ����������� ������� �� ���������. ���� �����-�� ������������ ��������� ��������, �� �����������, ����� ���� ��� ������� �������� �����, �� ������� �� ������ �����������, ��� �� �������. � ������ ��������� ����� ����� ������������ �������������� � �������� ����������� ����� ��������� �����������.

��� ��������� �������� ������������ �������� ������� �������� � �������� ��������� ������������, ����������� ��� ����������� ������ (��. ���������� ������� � ��������� �������).

������ �������� �� ��������� HTTP � ������������ ��������� �������:

	POST /add_user � ��������� ������ ������������ � ���������� ����� 200 OK, � ���� �������� ���������� ������������� ����� ������������ ������������ (��. ���������� � ��������� �������)

	POST /add_comment � ��������� �� ���� ������� ������������� ������������ � ����� �����������; ���� ������������ ��������� ��������, ���������� 302 Found c ���������� Location: /captcha, �������� ������������ �� �������� �����, � ��������� ������ ��������� ����������� � ���������� 200 OK

	GET /user_comments?user_id=[id] � ���������� ����� 200 OK, � ���� �������� ���������� ��� ����������� ������������ id, ���������� ��������� ������

	GET /captcha � ���������� ����� 200 OK, � ���� �������� ���������� �������� ����� (��� �������� � ���� ������ �� ������ ���������� ������, �� ������� ���� �������� ������������, �� �������� ��� ����� ���� ����������� HTML-��������)

	POST /checkcaptcha � ��������� �� ���� ������� ����� �� ������ �����; ���� �� �����, ������������ ������������ � ���������� 200 OK, ���� ��� � ���������� 302 Found c ���������� Location: /captcha

	���� ����� ������� �� POST � �� GET ��� ���� ������� �� ��������� �� � ����� �� �����������������, ������ �������� 404 Not found.

Web-������ � ���� ���������� � ������� ������ CommentServer:

struct HttpRequest {
  string method, path, body;
  map<string, string> get_params;
};

class CommentServer {
public:
  void ServeRequest(const HttpRequest& req, ostream& response_output);

private:
  ...
};

��� ����� ServeRequest ��������� HTTP-������, ������������ ��� � ���������� HTTP-����� � �������� ����� response_output (���� ����� ����� ���� �������� � �������� ����������). ��� ������ HTTP-������ � �������� ����� ������������ ��������� ������:

HTTP/1.1 [��� ������] [�����������]
[��������� 1]: [�������� ��������� 1]
[��������� 2]: [�������� ��������� 2]
...
[��������� N]: [�������� ��������� N]
<������ ������>
[���� ������]

	��� ������ � ��� 200, 302, 404 � �.�.

	����������� � "Found", "OK", "Not found" � �.�.

	��������� X � ��� ���������, ��������, "Location"

	���� ������ � ��������, ��� ���������� �������� ����� ��� ������������� ����� ������������ ������������; ��� ����, ���� ���� ������ ��������, � ������ ����������� ������ �������������� ��������� Content-Length, �������� �������� ����� ����� ������ � ������.

������ ������ �� ������ /add_user, � ������� ������������ ������������� ������ ������������, ������ 12. Content-Length ����� 2, ������ ��� "12" � ��� ��� �������:

HTTP/1.1 200 OK
Content-Length: 2

12

� ����� �������� ���� �������� � ������ �� ������ �� �������� �� �������, � ������ ���������� ����������� �������������� ������. �������� ���� ������� � ���, ��� ������ ����������� ������� ������ ��� (��. ��������� �������). ��-�� ����� �� �� ������� ������ ������, �� �������� ������, �� � ���� ������ �����������:

void ServeRequest(const HttpRequest& req, ostream& os) {
  if (req.method == "POST") {
	if (req.path == "/add_user") {
	  comments_.emplace_back();
	  auto response = to_string(comments_.size() - 1);
	  os << "HTTP/1.1 200 OK\n" << "Content-Length: " << response.size() << "\n" << "\n"
		<< response;
	} else if (req.path == "/checkcaptcha") {
	   ...
		os << "HTTP/1.1  20 OK\n\n";
	  }
	} else {
	  os << "HTTP/1.1 404 Not found\n\n";
	}
  ...
}

�� ������ ���������� �� ���� ������� ����� � �������� ��������� �����������:

	����������� ����� HttpResponse, ������� ����� ������������ ����� HTTP-�����; � operator << �� ������ ��������������� ������ ������ HTTP-������ � �����

	������� ����� ��������� ������ ServeRequest � HttpResponse ServeRequest(const HttpRequest& req), � ������� �� ����� ���������� ����� �������������, ��� ��� ������ ������ ���������� ���� �����-�� ����� (���� �� ������� ��� �������, ���������� ������ �������������� "control reaches end of non-void function")

	���������� ����� ������� � �������� ����� � ����� ������������ �����, � ������� ���������� ����� ServeRequest

��������� ������ HttpResponse �� ������ ������� �����:

enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};

class HttpResponse {
public:
  explicit HttpResponse(HttpCode code);

  HttpResponse& AddHeader(string name, string value);
  HttpResponse& SetContent(string a_content);
  HttpResponse& SetCode(HttpCode a_code);

  friend ostream& operator << (ostream& output, const HttpResponse& resp);
};

������ AddHeader, SetContent � SetCode ������ ���������� ������ �� ����, ����� ����� ����������� ������������ ����� � ����� ������ � ������� chaining'�: return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");. ������������ HttpCode, ������������ � ����������� ������ HttpResponse, �����������, ��� �� �� ������� � ���� ������.

���� ����������� ��� � ��������� ��������� � ���� ������. �������� �� �������� cpp-����, �������

	�������� ���������� ������ HttpResponse,

	�������� ���������� ������ CommentServer � ��������� ������� HttpResponse ServeRequest(const HttpRequest& req).

������ ������ ������������� ��������� ���� ��������.

��������� � ���������� ������ HttpResponse:

	������ AddHeader, SetContent, SetCode ������ ���������� ������ �� ������, ��� �������� ��� �������

	����� AddHeader ������ ��������� � ������ ����� ���������, ���� ���� ��������� � ����� ������ ��� ����

	operator<< ��� ������ HttpResponse ������ �������� HTTP-����� � �������, ��������� ���� � �������� ������ ServerRequest; ��� ���� ��������� ����� �������� � ������������ �������. ���� � HTTP-������ ���� �������� ����������, �� ���������� ������� ����� ���� ��������� "Content-Length"(������ ����������, ������������ � HTTP-������), �������� �������� ����� ������� ����������� � ������.
*/