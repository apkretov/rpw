#ifdef ON

#include "../../stdafx.h"
#include "16_04_3_1.h"
using namespace std;

void Forwarding_Parameter_Packs() {
	StrVec svec;
	svec.emplace_back(10, 'c'); // adds cccccccccc as a new last element

	//MINE
	auto print = [](const StrVec &sv) {
		for (const auto &i : sv)
			cout << i << " ";
		cout << '\n';
	};
	print(svec);

	//MINE
	const string s1 = "Hello, "; 
	const string s2 = "World!";
	
	svec.emplace_back(s1 + s2);

	print(svec); //MINE
}

void mine() {
	StrVec s;
	
	s.emplace_back("Hello");
	s.emplace_back("World");
	s.emplace_back("!");

	for (const auto &i : s)
		cout << i << " ";
	cout << endl;
}

int main() {
	print_file_line();

	Forwarding_Parameter_Packs();
	//mine();
}
#endif

#ifdef EX_16_58

#include <string>
#include "../../stdafx.h"
#include "16_04_3_2.h"
using namespace std;

int main() {
	print_file_line();

	Vec<string> svec;
	
	svec.emplace_back("Hello,");
	svec.emplace_back("World!");
	svec.emplace_back(10, 'c'); // adds cccccccccc as a new last element
	
	svec.push_back("Bye!");
	string s{"Good buy!"};
	svec.push_back(s);
	
	cout << "svec: ";
	ranges::copy(svec, ostream_iterator<string>(cout, " "));
	cout << '\n';
}
#endif

#ifdef EX_16_61

#include <iostream>
#include "vld.h"
#include "../../stdafx.h"
#include "16_04_3_3.h"
using namespace std;

int main() {
	print_file_line();

	auto p = my_make_shared<int>(42);
	cout << *p << '\n';
}
#endif