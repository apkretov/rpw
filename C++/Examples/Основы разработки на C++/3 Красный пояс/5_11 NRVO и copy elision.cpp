#if 0

#include <iostream>
#include "../../stdafx.h"
using namespace std;

class Logger {
public:
	Logger() {
		cout << "Default ctor\n";
	}

	Logger(const Logger &) {
		cout << "Copy ctor\n";
	}

	Logger(Logger &&) {
		cout << "Move ctor\n";
	}

	~Logger() {
		cout << "Dtor\n\n"; //MINE
	}
};

namespace RVO {
	Logger MakeLogger() {
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
		return Logger(); //TEST! //																															Return a temporary variable.
	}
}

namespace NRVO {
	Logger MakeLogger() {
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
		Logger logger;
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
		// ...
		return logger; //TEST! //																															Return a local variable.
	}
}

int main() {
	PRINT_FILE_LINE();
	{
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
		Logger logger = RVO::MakeLogger(); //TEST! //																											Temporary object elimination
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
	}
	{
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
		Logger logger = NRVO::MakeLogger();
		//MINE cout << __func__ << ' ' << __LINE__ << '\n';
	}
}
#endif //1
