#pragma once

namespace mtqcWinAPI {
	class messages {
		static void messageException(const std::exception& objException, const char* chrFunction, long double lngLine);
};	}