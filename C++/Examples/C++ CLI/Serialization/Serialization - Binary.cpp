#include "stdafx.h" //Details on Serialization @ http://www.functionx.com/cppcli/serialization/details.htm
using namespace System;
using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;

[Serializable] public ref class CCar {
public:
	String^ Make;
	String^ Model;
	[NonSerialized] double Value; // Because the value of a car can change, there is no reason to save it
	int Year;
	int Color;

	void serializeSelf() {
		FileStream^ stmCar = gcnew FileStream(L"LexusLSSelf.car", FileMode::Create);
		BinaryFormatter^ bfmCar = gcnew BinaryFormatter;
		bfmCar->Serialize(stmCar, this);
}	};

int main() {
	CCar^ vehicle = gcnew CCar;
	vehicle->Make = L"Lexus";
	vehicle->Model = L"LS";
	vehicle->Year = 2007;
	vehicle->Color = 4;
	vehicle->Value = 28640;

	FileStream^ stmCar = gcnew FileStream(L"LexusLS.car", FileMode::Create);
	BinaryFormatter^ bfmCar = gcnew BinaryFormatter;
	bfmCar->Serialize(stmCar, vehicle);

	vehicle->serializeSelf();

	return 0;
}
