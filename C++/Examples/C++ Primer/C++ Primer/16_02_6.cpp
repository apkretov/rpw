#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

namespace How_std_move_Is_Defined {
	template <typename T>
	typename remove_reference<T>::type &&move(T &&t) { //TEST! // for the use of typename in the return type and the cast see § 16.1.3 (p. 670) // remove_reference is covered in § 16.2.3 (p. 684)
		return static_cast<typename remove_reference<T>::type &&>(t); // static_cast covered in § 4.11.3 (p. 163)
	}

	void How_std_move_Is_Defined() {
		string s1("hi!"), s2;
		s2 = How_std_move_Is_Defined::move(string("bye!")); // ok: moving from an rvalue
		s2 = How_std_move_Is_Defined::move(s1); // ok: but after the assigment s1 has indeterminate value
	}
}

int main() {
	print_file_line();

	How_std_move_Is_Defined::How_std_move_Is_Defined();
}
#endif