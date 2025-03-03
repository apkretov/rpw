#ifdef ON

#include <iostream>
using namespace std;

namespace Array_Reference_Parameters {
	void print(int(&arr)[10]) { //TEST //																																						ok: parameter is a reference to an array; the dimension is part of the type
		for (auto elem : arr)
			cout << elem << endl;
	}

	void Array_Reference_Parameters() {
		int arr[10]{0, 1, 2};
		print(arr);
	}


#ifdef ON
	//TEST! void f(int &arr[10]) { //																																										error: declares arr as an array of references
		//...
	 }

#elif ON
	//TEST void f(int(&arr)[10]) { //																																									ok: arr is a reference to an array of ten ints
		//...
	 }
#endif
}

namespace Passing_a_Multidimensional_Array {
	void print1(int(*matrix)[10], int rowSize) { // matrix points to the first element in an array whose elements are arrays of ten ints
		/* . . . */
	}

	void print2(int matrix[][10], int rowSize) { // equivalent definition
		/* . . . */
	}

	//TEST int *matrix[10]; //																																									array of ten pointers
	//TEST int(*matrix)[10]; //																																								pointer to an array of ten int
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int arr[10]{0, 1, 2};
	Array_Reference_Parameters::print(arr);

	const int rowSize{20};
	int matrix[rowSize][10]{};
	Passing_a_Multidimensional_Array::print1(matrix, rowSize);

	return 0;
}
#endif