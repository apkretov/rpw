#include "stdafx.h" //Details on Serialization @ http://www.functionx.com/cppcli/serialization/details.htm
using namespace System;
using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;

[Serializable] public ref class CCar {
public:
	String ^Make;
	String ^Model;
	[NonSerialized] double Value; // Because the value of a car can change, there is no reason to save it
	int Year;
	int Color;
};

int main() {
	FileStream^ stmCar = gcnew FileStream(L"LexusLS.car", FileMode::Open);
	BinaryFormatter^ bfmCar = gcnew BinaryFormatter;
	//ERROR CCar^ vehicle = dynamic_cast<CCar^>(bfmCar->Deserialize(stmCar));

	//Console::WriteLine(L"Car Information");
	//Console::WriteLine(L"Make:  {0}", vehicle->Make);
	//Console::WriteLine(L"Model: {0}", vehicle->Model);
	//Console::WriteLine(L"Year:  {0}", vehicle->Year);
	//Console::Write(L"Color: ");
	//switch (vehicle->Color) {
	//case 1:
	//	Console::WriteLine(L"Black");
	//	break;
	//case 2:
	//	Console::WriteLine(L"Gray");
	//	break;
	//case 3:
	//	Console::WriteLine(L"White");
	//	break;
	//case 4:
	//	Console::WriteLine(L"Red");
	//	break;
	//case 5:
	//	Console::WriteLine(L"Blue");
	//	break;
	//}
	//Console::WriteLine(L"Value:  {0}\n", vehicle->Value);

	return 0;
}