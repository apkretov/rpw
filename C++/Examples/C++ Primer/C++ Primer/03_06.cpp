#ifdef ON

#include <iostream>
using namespace std;

void Multidimensional_Arrays() {
	int ia[3][4]; // array of size 3; each element is an array of ints of size 4
	// array of size 10; each element is a 20-element array whose elements are arrays of 30 ints
	int arr[10][20][30] = {0}; // initialize all elements to 0
}

void Subscripting_a_Multidimensional_Array() {
	int arr[5][5][5]{}, ia[3][4]{};
	ia[2][3] = arr[0][0][0]; // assigns the first element of arr to the last element in the last row of ia
	//TEST! int (&row)[4] = ia[1]; //																																									binds row to the second four-element array in ia

	{ //MINE
		int v[3][4]{};
		int(&b)[4] = v[2];

		v[2][3] = 111;
		cout << b[3] << '\n';
	}

}

void Using_a_Range_for_with_Multidimensional_Arrays() {
	int ia[3][3]{1, 2, 3, 4, 5, 6, 7, 8, 9}, n{}; //MINE

	/*
	for (auto &row : ia) //MINE
		for (auto &col : row)
			col = ++n;
	*/
	
	/*
	//TEST! for (const auto &row : ia) { 
	//TEST! for (const auto row : ia) {  
		for (auto col : row)
			cout << col << ' ';
		cout << '\n';
	}
	*/
}

void Pointers_and_Multidimensional_Arrays() {
	int ia[3][4]; // array of size 3; each element is an array of ints of size 4
	//TEST int(*p)[4] = ia; //																																										p points to an array of four ints
	//TEST! p = &ia[2]; //																																											p now points to the last element in ia

	// The parentheses in this declaration are essential:
	//TEST! int *ip[4]; //																																											array of pointers to int
	//TEST int (*ip)[4]; //																																											pointer to an array of four ints
}

void Type_Aliases_Simplify_Pointers_to_Multidimensional_Arrays() {
	int ia[3][4]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; //MINE

	//TEST! using int_array = int[4]; //																																								new style type alias declaration; see § 2.5.1 (p. 68)
	//TEST! typedef int int_array[4]; //																																								equivalent typedef declaration; § 2.5.1 (p. 67)
	
	// print the value of each element in ia, with each inner array on its own line
	/*
	for (int_array *p = ia; p != ia + 3; ++p) {
		for (int *q = *p; q != *p + 4; ++q)
			cout << *q << ' ';
		cout << endl;
	}
	*/
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Multidimensional_Arrays();
	//Subscripting_a_Multidimensional_Array();
	Using_a_Range_for_with_Multidimensional_Arrays();
	//Type_Aliases_Simplify_Pointers_to_Multidimensional_Arrays();

	return 0;
}
#endif

#ifdef EX_03_43

#include <iostream>
using namespace std;

int main(int argc, char *agrv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const size_t rs{3}, cs{4};
	const int ia[rs][cs] {0, 1, 2, 3,
						  4, 5, 6, 7, 
						  8, 9, 10,11};

#ifdef ON
	//TEST! for (const int (&r)[cs] : ia) {
		for (int c : r)
			cout << c << '\t';
		cout << '\n';
	}
	cout << '\n';

#elif !ON
	for (size_t i = 0; i < rs; ++i) {
		for (size_t j = 0; j < cs; ++j)
			cout << ia[i][j] << '\t';
		cout << '\n';
	}
	cout << '\n';

#elif ON
	//TEST! for (const int(*pr)[cs] = ia; pr < ia + rs; ++pr) {
		//TEST! for (const int *pi = *pr; pi < *pr + cs; ++pi)
			cout << *pi << '\t';
		cout << '\n';
	}
	cout << '\n';
#endif	

	return 0;
}
#endif

#ifdef EX_03_44

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const size_t rs{3}, cs{4};
	const int ia[rs][cs] {0, 1, 2, 3,
						  4, 5, 6, 7,
						  8, 9, 10,11};

#ifdef ON
	{
		//TEST! using row = const int(&)[cs]; 
		using col = int;
		for (row r : ia) {
			for (col c: r)
				cout << c << '\t';
			cout << '\n';
		}
		cout << '\n';
	}

#elif !ON

	for (size_t i = 0; i < rs; ++i) {
		for (size_t j = 0; j < cs; ++j)
			cout << ia[i][j] << '\t';
		cout << '\n';
	}

#elif ON
	{
		//TEST! using row = const int(*)[cs];
		using col = const int*;
		for (row pr = ia; pr < ia + rs; ++pr) {
			for (col pc = *pr; pc < *pr + cs; ++pc)
				cout << *pc << '\t';
			cout << '\n';
		}
	}
#endif

	return 0;
}

#endif

#ifdef EX_03_45

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	const size_t rs{3}, cs{4};
	const int ia[rs][cs]{0, 1, 2, 3,
						 4, 5, 6, 7,
						 8, 9, 10, 11};

	/*
	for (auto &r : ia) {
		for (auto c : r)
			cout << c << '\t';
		cout << '\n';
	}
	*/

	/*
	for (auto i = 0; i < rs; ++i) {
		for (auto j = 0; j < cs; ++j)
			cout << ia[i][j] << '\t';
		cout << '\n';
	}
	*/

	for (auto pr = ia; pr < ia + rs; ++pr) {
		for (auto pc = *pr; pc < *pr + cs; ++pc)
			cout << *pc << '\t';
		cout << '\n';
	}

	return 0;
}

#endif