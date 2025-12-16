#if 1

#include <cassert>
#include <functional>
#include <future>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "../../stdafx.h"

static void func_1() {
	std::promise<int> p;
	std::future<int> f(p.get_future());
	assert(f.valid());  // ❶
	std::shared_future<int> sf(std::move(f));
	assert(!f.valid());  // ❷
	assert(sf.valid());  // ❸
}

static void func_2() {
	std::promise<std::string> p;
	std::shared_future<std::string> sf(p.get_future());  // ❶ Implicit transfer
}

static void func_3() {
#pragma region MINE
	using SomeIndexType = int;
	using SomeDataType = std::string;
	using SomeComparator = std::less<SomeIndexType>;
	using SomeAllocator = std::allocator<std::pair<const SomeIndexType, SomeDataType>>;
#pragma endregion
	std::promise<std::map<SomeIndexType, SomeDataType, SomeComparator, SomeAllocator>::iterator> p;
	auto sf = p.get_future().share();
}

int main() {
	print_file_line();

	func_1();
	func_2();
	func_3();
}
#endif //1
