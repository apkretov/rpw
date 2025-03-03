#if 0

#include <chrono>
#include <iostream>
#include <locale>
using namespace std;

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__) {message}

class LogDuration {
public:
	explicit LogDuration(const string &msg = "") : message(msg + ": "), start(chrono::steady_clock::now()) {}

	~LogDuration() {
		auto finish = chrono::steady_clock::now();
		auto dur = finish - start;
		cout << message << chrono::duration_cast<chrono::milliseconds>(dur).count() << " ms" << endl;
	}
private:
	string message;
	chrono::steady_clock::time_point start;
};

int main() {
	setlocale(LC_ALL, "RU"); // Don't include "../../stdafx.h" for PRINT_FILE_LINE() because of the LogDuration class.
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	LOG_DURATION("main");
}
#endif //1
