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
Сервер комментариев
Предисловие

В этой задаче мы разберём приём, известный как chaining, который широко применяется во многих языках программирования, особенно в JavaScript. В C++ chaining тоже имеет свою нишу применения. Указатель this необходим для реализации chaining'а. Кроме того, чтобы задача не выглядела искусственной, мы разберём применение этого приёма в реальной практической ситуации, с которой сталкивался один из преподавателей курса.
Условие

Вы подключились к команде, которая разрабатывает web-сервер комментариев. Этот сервер позволяет создавать новых пользователей, публиковать новые объявления, а также читать все объявления выбранного пользователя. Кроме того команда недавно озаботилась борьбой со спамерами. Если какой-то пользователь признаётся спамером, он блокируется, после чего ему выдаётся страница капчи, на которой он должен подтвердить, что он человек. В случае успешного ввода капчи пользователь разблокируется и получает возможность снова оставлять комментарии.

Для выявления спамеров используется довольно простой алгоритм — спамером признаётся пользователь, отправивший три комментария подряд (см. реализацию сервера в заготовке решения).

Сервер работает по протоколу HTTP и обрабатывает следующие запросы:

	POST /add_user — добавляет нового пользователя и возвращает ответ 200 OK, в теле которого содержится идентификатор вновь добавленного пользователя (см. реализацию в заготовке решения)

	POST /add_comment — извлекает из тела запроса идентификатор пользователя и новый комментарий; если пользователь признаётся спамером, возвращает 302 Found c заголовком Location: /captcha, переводя пользователя на страницу капчи, в противном случае сохраняет комментарий и возвращает 200 OK

	GET /user_comments?user_id=[id] — возвращает ответ 200 OK, в теле которого содержатся все комментарии пользователя id, разделённые переводом строки

	GET /captcha — возвращает ответ 200 OK, в теле которого содержится страница капчи (для простоты в этой задаче мы просто возвращаем вопрос, на который надо ответить пользователю, на практике это может быть полноценная HTML-страница)

	POST /checkcaptcha — извлекает из тела запроса ответ на вопрос капчи; если он верен, разблокирует пользователя и возвращает 200 OK, если нет — возвращает 302 Found c заголовком Location: /captcha

	если метод запроса не POST и не GET или путь запроса не совпадает ни с одним из вышеперечисленных, сервер отвечает 404 Not found.

Web-сервер в коде реализован с помощью класса CommentServer:

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

Его метод ServeRequest принимает HTTP-запрос, обрабатывает его и записывает HTTP-ответ в выходной поток response_output (этот поток может быть привязан к сетевому соединению). При записи HTTP-ответа в выходной поток используется следующий формат:

HTTP/1.1 [код ответа] [комментарий]
[Заголовок 1]: [Значение заголовка 1]
[Заголовок 2]: [Значение заголовка 2]
...
[Заголовок N]: [Значение заголовка N]
<пустая строка>
[Тело ответа]

	код ответа — это 200, 302, 404 и т.д.

	комментарий — "Found", "OK", "Not found" и т.д.

	Заголовок X — имя заголовка, например, "Location"

	тело ответа — например, это содержимое страницы капчи или идентификатор вновь добавленного пользователя; при этом, если тело ответа непустое, в ответе обязательно должен присутствовать заголовок Content-Length, значение которого равно длине ответа в байтах.

Пример ответа на запрос /add_user, в котором возвращается идентификатор нового пользователя, равный 12. Content-Length равен 2, потому что "12" — это два символа:

HTTP/1.1 200 OK
Content-Length: 2

12

С нашим сервером есть проблема — иногда он ничего не отвечает на запросы, а иногда возвращает некорректно сформированные ответы. Источник этих проблем в том, что ответы формируются вручную каждый раз (см. заготовку решения). Из-за этого мы то перевод строки забыли, то добавили лишний, то в коде ответа опечатались:

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

Вы решили избавиться от всех проблем разом и провести следующий рефакторинг:

	разработать класс HttpResponse, который будет представлять собой HTTP-ответ; в operator << вы решили инкапсулировать формат вывода HTTP-ответа в поток

	сделать новую сигнатуру метода ServeRequest — HttpResponse ServeRequest(const HttpRequest& req), — которая на этапе компиляции будет гарантировать, что наш сервер всегда возвращает хоть какой-то ответ (если мы забудем это сделать, компилятор выдаст предупреждение "control reaches end of non-void function")

	записывать ответ сервера в выходной поток в одном единственном месте, в котором вызывается метод ServeRequest

Интерфейс класса HttpResponse вы решили сделать таким:

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

Методы AddHeader, SetContent и SetCode должны возвращать ссылку на себя, чтобы иметь возможность сформировать ответ в одной строке с помощью chaining'а: return HttpResponse(HttpCode::Found).AddHeader("Location", "/captcha");. Перечисление HttpCode, передаваемое в конструктор класса HttpResponse, гарантирует, что мы не ошибёмся в коде ответа.

Этот рефакторинг вам и предстоит выполнить в этой задаче. Пришлите на проверку cpp-файл, который

	содержит реализацию класса HttpResponse,

	содержит реализацию класса CommentServer с публичным методом HttpResponse ServeRequest(const HttpRequest& req).

Сервер должен реализовывать описанный выше протокол.

Уточнения к реализации класса HttpResponse:

	Методы AddHeader, SetContent, SetCode должны возвращать ссылку на объект, для которого они вызваны

	Метод AddHeader всегда добавляет к ответу новый заголовок, даже если заголовок с таким именем уже есть

	operator<< для класса HttpResponse должен выводить HTTP-ответ в формате, описанном выше в описании метода ServerRequest; при этом заголовки можно выводить в произвольном порядке. Если у HTTP-ответа есть непустое содержимое, то необходимо вывести ровно один заголовок "Content-Length"(помимо заголовков, содержащихся в HTTP-ответе), значение которого равно размеру содержимого в байтах.
*/