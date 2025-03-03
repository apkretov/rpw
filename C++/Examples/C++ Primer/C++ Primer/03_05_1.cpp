#ifdef ON

#include <iostream>
using namespace std;

void Defining_and_Initializing_Built_in_Arrays() {
	unsigned cnt = 42; // not a constant expression
	constexpr unsigned sz = 42; // constant expression
	const unsigned sz_const{42}; //MINE
	
	int arr[10]; // array of ten ints
	//TEST int *parr[sz]; //																																										array of 42 pointers to int
	//TEST string bad[cnt]; //																																										error: cnt is not a constant expression
	//TEST! string strs[get_size()]; //																																								ok if get_size is constexpr, error otherwise
	//TEST string arr2[sz_const]; //MINE
}

void Understanding_Complicated_Array_Declarations() {
	//MINE
	int arr[10];
	int *ptrs[10];

	//TEST int *ptrs[10]; //																																										ptrs is an array of ten pointers to int
	
	//TEST! int &refs[10]; // = /* ? */; // 																																							error: no arrays of references
	
	//MINE
	int i;
	int &ref{i};
	//TEST!! int &refs3[]{ref};
	
	//TEST! int(*Parray)[10] = &arr; // 																																							Parray points to an array of ten ints
	//TEST! int(&arrRef)[10] = arr; // 																																								arrRef refers to an array of ten ints

	//TEST! int *(&arry)[10] = ptrs; //																																								arry is a reference to an array of ten pointers
}

#define EX_03_27
#ifdef EX_03_27
unsigned buf_size = 1024;

int txt_size() { return buf_size; }

//TEST int ia[buf_size]; // (a)
//TEST int ia[4 * 7 - 14]; // (b)
//TEST int ia[txt_size()]; // (c) 
//TEST char st[11] = "fundamental"; //(d) 
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif

#undef EX_03_28
#ifdef EX_03_28

#include <iostream>
using namespace std;

//TEST string sa[10];
//TEST int ia[10];

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//TEST string sa2[10];
	//TEST int ia2[10];
}
#endif
