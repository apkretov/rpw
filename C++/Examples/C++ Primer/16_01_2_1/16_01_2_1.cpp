#ifndef ON

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "16_01_2_1.h"
using namespace std;

void Instantiating_a_Class_Template() {
	Blob<int> ia; // empty Blob<int>
#ifdef ORIG
	Blob<int> ia2 = {0,1,2,3,4}; // Blob<int> with five elements
#else //MINE
	Blob<int> ia2{0,1,2,3,4}; // Blob<int> with five elements // TEST! // Compiler Error C3445 @ https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c3445?view=msvc-170&f1url=%3FappId%3DDev17IDEF1%26l%3DEN-US%26k%3Dk(C3445)%26rd%3Dtrue
#endif

	Blob<string> names; // Blob that holds strings // these definitions instantiate two distinct Blob types
	Blob<double> prices;// different element type
}

void Blob_Constructors() {
#ifdef ORIG
	Blob<string> a = {"a", "an", "the"};
#else //MINE
	Blob<string> a{"a", "an", "the"}; // Compiler Error C3445 @ https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c3445?view=msvc-170&f1url=%3FappId%3DDev17IDEF1%26l%3DEN-US%26k%3Dk(C3445)%26rd%3Dtrue
#endif

}

void Instantiation_of_Class_Template_Member_Functions() {
#ifdef ORIG
	Blob<int> squares = {0,1,2,3,4,5,6,7,8,9}; // instantiates Blob<int> and the initializer_list<int> constructor
#else //MINE
	Blob<size_t> squares{0,1,2,3,4,5,6,7,8,9}; // instantiates Blob<int> and the initializer_list<int> constructor // Compiler Error C3445 @ https://learn.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c3445?view=msvc-170&f1url=%3FappId%3DDev17IDEF1%26l%3DEN-US%26k%3Dk(C3445)%26rd%3Dtrue
#endif
	for (size_t i = 0; i != squares.size(); ++i) // instantiates Blob<int>::size() const
		squares[i] = i * i; // instantiates Blob<int>::operator[](size_t)
}

void mine() {
	Blob<int> b({0, 1, 2, 3});

	cout << "b values: ";
	for (decltype(b.size()) i = 0; i < b.size(); ++i)
		cout << b[i] << ' ';

	cout << "\nb.back() = " << b.back() << '\n';

	cout << "\npopping back...\n";
	b.pop_back();
	cout << "b.back() = " << b.back() << '\n';
}

int main(int argc, char* argv[]) {
    print_file_line();

	Instantiating_a_Class_Template();
	Instantiation_of_Class_Template_Member_Functions();
	mine();

	return 0;
}
#endif