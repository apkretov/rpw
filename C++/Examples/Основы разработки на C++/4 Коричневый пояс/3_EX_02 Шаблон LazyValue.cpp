#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/02%20Programming%20Assingment

#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

template <typename T>
class LazyValue {
	mutable optional<T> value;
	function<T()> func;
public:
	explicit LazyValue(function<T()> init) : func(std::move(init)) {} //TEST!
	bool HasValue() const { return value.has_value(); }

	const T &Get() const {
		if (!value.has_value())
			value = func();
		return *value;
	}
};

void UseExample() {
	const string big_string = "Giant amounts of memory";

	LazyValue<string> lazy_string([&big_string] { return big_string; });

	ASSERT(!lazy_string.HasValue());
	ASSERT_EQUAL(lazy_string.Get(), big_string);
	ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
	bool called = false;

	{
		LazyValue<int> lazy_int([&called] {
			called = true;
			return 0;
			});
	}
	ASSERT(!called);
}

int main() {
	PRINT_FILE_LINE(); //MINE

	TestRunner tr;
	RUN_TEST(tr, UseExample);
	RUN_TEST(tr, TestInitializerIsntCalled);
	return 0;
}
#endif //1

/*
������ LazyValue

������ �� �������� ����������� �������, �������� ������� �������� ������������ �����, ������ ��� ������ ����� �� ��� ������ ������� ���������. ��������, ������ ������� �������� ������ ����� ���������� � ��������� ������, � ����� � � ��������� �����������. ����� ������������� ���������� � �������� ������������ �����, ������ ���� ������������ ����� � ���� ����������.

��� ������������� ����� �������� ����� ���� ������� ������ LazyValue. � ���� ���� ����������� ����� const T& Get(), ������� ���������� ������ �� ��������� ������. � ���� ������������ LazyValue ��������� ���������������� �������, ������� ������������ ��� ������ ������ ������ Get ��� �������� ��������� �������. ����������� ������ Get ������ ���������� ������ �� �������� ������.

����� �������, ������ ������ LazyValue �� ������ ����� �� �������� ��������� ������� �� ������� ������ ������ Get.

��� ��� ��������� ������� LazyValue. ���������� ���. ����� ��������� ������ ����������:

	������ ������ LazyValue �� ������ �������������� ������ ���� T ��� ���� ��������

	��� ������ ������ ������ LazyValue::Get ������ ����������� ������ ���� T � ������� �������, ���������� � ����������� LazyValue

	����������� ������ ������ Get �� ������ �������� �������, ���������� � �����������

	���� �� ����� ����� ������� LazyValue ����� Get �� ��� ������ �� ����, �� ���������������� ������� �� ������ ���� �������.

	������ LazyValue ������ ������������ ������ � ������ ��� ������������ �� ���������

��������� ������� ������� � ��������� �������.

#include "test_runner.h"

#include <functional>
#include <string>
using namespace std;

template <typename T>
class LazyValue {
public:
explicit LazyValue(std::function<T()> init);

bool HasValue() const;
const T& Get() const;

private:

};

void UseExample() {
const string big_string = "Giant amounts of memory";

LazyValue<string> lazy_string([&big_string] { return big_string; });

ASSERT(!lazy_string.HasValue());
ASSERT_EQUAL(lazy_string.Get(), big_string);
ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
bool called = false;

{
  LazyValue<int> lazy_int([&called] {
	called = true;
	return 0;
  });
}
ASSERT(!called);
}

int main() {
TestRunner tr;
RUN_TEST(tr, UseExample);
RUN_TEST(tr, TestInitializerIsntCalled);
return 0;
}
*/