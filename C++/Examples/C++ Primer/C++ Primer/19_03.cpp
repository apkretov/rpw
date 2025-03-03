#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Enumerations
enum class open_modes { input, output, append };

enum color { red, yellow, green }; // unscoped enumeration
enum { floatPrec = 6, doublePrec = 10, double_doublePrec = 10 }; //TEST! //																				unnamed, unscoped enum
#pragma endregion

#pragma region MINE
auto m = open_modes::input;
//TEST auto m2 = input;
auto c = color::red; //TEST!
auto c2 = red; //TEST
auto n = floatPrec;
#pragma endregion

void Enumerators() {
	enum color { red, yellow, green }; // unscoped enumeration
	enum stoplight { red, yellow, green }; //TEST //																									error: redefines enumerators
	enum class peppers { red, yellow, green }; //TEST //																								ok: enumerators are hidden

	color eyes = green; //TEST! //																														ok: enumerators are in scope for an unscoped enumeration
	//TEST peppers p = green; //																														error: enumerators from peppers are not in scope
	// color::green is in scope but has the wrong type
	color hair = color::red; //TEST //																													ok: we can explicitly access the enumerators
	peppers p2 = peppers::red; // ok: using red from peppers

	enum class intTypes {
		charTyp = 8, shortTyp = 16, 
		intTyp = 16, //TEST!
		longTyp = 32, long_longTyp = 64
	};
}

void Like_Classes_Enumerations_Define_New_Types() {
	//TEST! open_modes om = 2; //																														error: 2 is not of type open_modes // error: 2 is not of type open_modes
	//ORIG om = open_modes::input; // ok: input is an enumerator of open_modes
	open_modes om = open_modes::input; //MINE

	int i = color::red; // ok: unscoped enumerator implicitly converted to int
	//TEST! int j = peppers::red; //																													error: scoped enumerations are not implicitly converted
}

void Specifying_the_Size_of_an_enum() {
	enum intValues : unsigned long long { //TEST!
		charTyp = 255, shortTyp = 65535, intTyp = 65535,
		longTyp = 4294967295UL,
		long_longTyp = 18446744073709551615ULL
	};
}

void Forward_Declarations_for_Enumerations() {
	// forward declaration of unscoped enum named intValues
	enum intValues : unsigned long long; //TEST! //																										unscoped, must specify a type
	enum class open_modes; // scoped enums can use int by default

	{
		enum class intValues; // error: declarations and definition must agree whether the enum is scoped or unscoped
		//TEST enum intValues; //																														error: intValues previously declared as scoped enum
		//TEST enum intValues : long; //																												error: intValues previously declared as int
	}
}

#pragma region Parameter Matching and Enumerations
enum Tokens { INLINE = 128, VIRTUAL = 129 }; // unscoped enumeration; the underlying type is machine dependent
void ff(Tokens); //TEST
void ff(int);

void Parameter_Matching_and_Enumerations() {
	void newf(unsigned char);
	void newf(int);
	unsigned char uc = VIRTUAL;

	newf(VIRTUAL); // calls newf(int)
	newf(uc); //TEST //																																	calls newf(unsigned char)// calls newf(unsigned char)
}

int main() {
	print_file_line();

	Tokens curTok = INLINE;
	ff(128); // exactly matches ff(int)
	ff(INLINE); //TEST //																																exactly matches ff(Tokens)
	ff(curTok); //TEST //																																exactly matches ff(Tokens)// exactly matches ff(Tokens)

	return 0;
}
#pragma endregion
#endif