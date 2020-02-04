#include "stdafx.h" //C++/CLI Threading: Part I @ http://www.drdobbs.com/cpp/ccli-threading-part-i/184402018
using namespace System;
using namespace System::Threading;

public ref struct ArrayManip {
	static int TotalValues(array<int>^ array) {
		int sum = 0; /*1*/
		Monitor::Enter(array); /*2*/
		{
			for (int i = 0; i < array->Length; ++i) sum += array[i];
		}
		Monitor::Exit(array);
		return sum;
	}

	static void SetAllValues(array<int>^ array, int newValue) {
		Monitor::Enter(array); /*3*/
		{
			for (int i = 0; i < array->Length; ++i) array[i] = newValue;
		}
		Monitor::Exit(array);
	}

	static void CopyArrays(array<int>^ array1, array<int>^ array2)	{
		Monitor::Enter(array1); /*4*/
		{
			Monitor::Enter(array2); /*5*/
			{
				Array::Copy(array1, array2, array1->Length < array2->Length ? array1->Length : array2->Length);
			}
			Monitor::Exit(array2);
		}
		Monitor::Exit(array1);
}	};

int main(array<System::String ^> ^args) {
	return 0;
}