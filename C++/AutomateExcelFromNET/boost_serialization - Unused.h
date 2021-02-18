#pragma once
#include <string>

//typedef struct serializables { 
//
//};

namespace boost_serialization {
	template <typename T> void save(T var);
	void save2(std::wstring str);
	template <typename T> void load(T& var);
}
