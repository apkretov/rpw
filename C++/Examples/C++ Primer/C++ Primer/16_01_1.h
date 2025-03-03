#pragma once

#include <functional>
using std::less;

#pragma region Writing_Type_Independent_Code
template <typename T>
int compare(const T &var1, const T &var2) {
	if (less<T>()(var1, var2))
		return -1;
	if (less<T>()(var2, var1))
 		return 1;
	return 0;
}
#pragma endregion
