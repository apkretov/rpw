#pragma once

#include <type_traits>
#include "stdafx.h"

struct DefaultCtor {}; // 08-exceptions/noexc.cc @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/noexc.cc

struct ThrowingCtor {
#ifndef ORIG
	ThrowingCtor() {}; //TEST! //																														=default will create noexcept one
#else //MINE
	ThrowingCtor() = default;
#endif
	ThrowingCtor(const ThrowingCtor&) = default;
	ThrowingCtor(ThrowingCtor&&) = default;
};

struct Inherited {
	ThrowingCtor c;
};

void foo(int) noexcept;
void foo(DefaultCtor) noexcept;
void foo(ThrowingCtor) noexcept;

int main() {
	PRINT_FILE_LINE();

	cout << boolalpha;
	cout << "noexcept(null pointer deref): " << noexcept(*static_cast<int*>(nullptr)) << '\n'; //TEST!

	cout << "foo(int): " << noexcept(foo(1)) << '\n';
	cout << "foo(Default): " << noexcept(foo(DefaultCtor{})) << '\n';
	cout << "foo(Throwing): " << noexcept(foo(ThrowingCtor{})) << '\n';

	cout << "Default constr: " << is_nothrow_constructible_v<DefaultCtor> << '\n'; //TEST!
	cout << "Default copy constr: " << is_nothrow_copy_constructible_v<DefaultCtor> << '\n';
	cout << "Default move constr: " << is_nothrow_move_constructible_v<DefaultCtor> << '\n';

	cout << "Inherited constr: " << is_nothrow_constructible_v<Inherited> << '\n'; //TEST!
	cout << "Inherited copy constr: " << is_nothrow_copy_constructible_v<Inherited> << '\n';
	cout << "Inherited move constr: " << is_nothrow_move_constructible_v<Inherited> << '\n';

#ifndef MINE
	cout << '\n';
	cout << "is_nothrow_constructible_v<ThrowingCtor>: " << is_nothrow_constructible_v<ThrowingCtor> << '\n'; //TEST!
	cout << "noexcept(ThrowingCtor::ThrowingCtor()): " << noexcept(ThrowingCtor::ThrowingCtor()) << '\n';
	cout << "noexcept(Inherited::Inherited()): " << noexcept(Inherited::Inherited()) << '\n';
#endif
}
