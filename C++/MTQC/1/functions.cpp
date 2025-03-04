using std::string;
using std::to_string;
using std::wstring;
using std::istringstream;
using std::stringstream;
#include <iomanip> // parameterized stream manipulators  
#include "display.h"
using namespace mtqc;
#include "terminalMT4.h"
using namespace mtqc::terminalMT4;
#include "switch.h"
#include "constants.h"
using namespace mtqc::constants;

namespace mtqc {
	namespace functions {
		/*KTB
		static struct { //The messages.
			std::atomic_flag messageFlag = ATOMIC_FLAG_INIT;
			std::queue<string> messages; 
		} msttMessages;
		*/

		#ifndef BLN_TEST_TRADE_SR_EVENING
			int roundToPts(double dblValue) { 
				return (int)MathRound(dblValue / gobjConstantsXML.getStockPoint());
			}
		#else
			int roundToPts(double dblValue) { 
				return (int)MathRound(dblValue / gobjConstantsXML.getFuturesPoint()); 
			}
		#endif

		// Convert OP_BUY=0 to OP_SELL=1 and vice versa. 
		//function abs. In C, only the int version exists. For the long int equivalent see labs. For the long long int equivalent see llabs. @ http://www.cplusplus.com/reference/cstdlib/abs/ 
		int BUYtoSELL(int intOperation) { 
			return abs(intOperation - 1); 
		} 

		// Convert OP_BUYLIMIT = 2 / OP_BUYSTOP = 4 to OP_BUY = 0 or OP_SELLLIMIT = 3 / OP_SELLSTOP = 5 to OP_SELL = 1. --You should use the '%' operator 
		// on positive numbers instead, as it is much faster. @ https ://maurits.tv/data/garrysmod/wiki/wiki.garrysmod.com/indexdaf1.html 
		int LIMITSTOPtoBUYSELL(int intOperation) { 
			return intOperation % 2; 
		} 

		/*KTB 
		string charToString(const char* chrChar) { 
			return string(chrChar); 
		}
		*/

		// Convert string to double //How can I convert string to double in C++? @ http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c 
		int stringToInt(const string& strNumber) { 
			istringstream i(strNumber);
			int intNumber;
			if (!(i >> intNumber)) 
				return 0;
			return intNumber;
		}

		// Convert string to double 
		//How can I convert string to double in C++? @ http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c 
		double stringToDouble(const string& strNumber) { 
			istringstream i(strNumber);
			double dblNumber;
			if (!(i >> dblNumber)) 
				return 0;
			return dblNumber;
		}	

		// Convert float to string with set precision & number of decimal digits. @ http://stackoverflow.com/questions/29200635/convert-float-to-string-with-set-precision-number-of-decimal-digits
		/*static*/ string threadIdToString(std::thread::id& objID) { 
			stringstream stream;
			stream << objID;
			return stream.str();
		}

		// Convert float to string with set precision & number of decimal digits. @ http://stackoverflow.com/questions/29200635/convert-float-to-string-with-set-precision-number-of-decimal-digits
		string numberToStringF(double dblNumber) { 
			stringstream stream;
			stream << std::fixed << std::setprecision(2) << dblNumber;
			return stream.str();
		}	

		//Convert int to const wchar_t*
		wchar_t* numberToWchar_t(int intNumber) { 
			wchar_t chrNumber[256]; //Convert int to const wchar_t* @ https://stackoverflow.com/questions/15109469/convert-int-to-const-wchar-t
			swprintf_s(chrNumber, L"%d", intNumber);
			return chrNumber;
		}
		
		//Convert int to const wchar_t*
		wchar_t* numberToWchar_t(double dblNumber) { 
			wchar_t chrNumber[256]; //Convert int to const wchar_t* @ https://stackoverflow.com/questions/15109469/convert-int-to-const-wchar-t
			swprintf_s(chrNumber, L"%f", dblNumber);
			return chrNumber;
		}

		// Convert pointer to string by using string representation of the address. 
		//Convert �this� pointer to string @ http://stackoverflow.com/questions/7850125/convert-this-pointer-to-string
		static string pointerToString(void* ptr) { 
			const void* address = static_cast<const void*>(ptr);
			stringstream ss;
			ss << address;  
			return(ss.str());
		}
		
		// Convert string to double 
		//How can I convert string to double in C++? @ http://stackoverflow.com/questions/392981/how-can-i-convert-string-to-double-in-c 
		template <typename T> 
		static void stringToNumber(const string& strNumber, T& varNumber) { 
			istringstream i(str);
			T varNumber_;
			if (!(i >> varNumber_)) 
				return 0;
			varNumber = varNumber_;
		}

		/*KTB Use std::wstring instead. //I want to convert std::string into a const wchar_t * @ http://stackoverflow.com/questions/246806/i-want-to-convert-stdstring-into-a-const-wchar-t
		//If this function is needed again arrange deleting the dynamically allocated chrWcstring.
		// Convert from char to wchar_t. 
		//"How to: Convert Between Various String Types" @ https://msdn.microsoft.com/en-us/library/ms235631.aspx
		wchar_t* charToWchar_t(const char* chrOrig) { 
			
			// intNewsize describes the length of the wchar_t string called chrWcstring in terms of the number of wide characters, not the number of bytes.
			size_t intNewsize = strlen(chrOrig) + 1; 
			
			// The following creates a buffer large enough to contain the exact number of characters in the original string in the new format. 
			//If you want to add more characters to the end of the string, increase the value of intNewsize to increase the size of the buffer.
			wchar_t* chrWcstring = new wchar_t[intNewsize]; 
			
			size_t convertedChars = 0; // Convert char* string to a wchar_t* string.
			mbstowcs_s(&convertedChars, chrWcstring, intNewsize, chrOrig, _TRUNCATE);
			return(chrWcstring);
		}
		*/

		#include <assert.h>
		
		//The placeholder: see the function in client.cpp.
		static void wchar_tToChar() { 
			assert(false); 
		} 
		//The placeholder: see the function in client.cpp.
		static void charToWchar_t() { 
			assert(false); 
		} 
		
		//The placeholder: see the function in functionsMT4dll.cpp.
		static void wchar_tToString() { 
			assert(false); 
		} 

		/*KTB Use std::wstring instead. //Use std::wstring instead. @ http://stackoverflow.com/questions/246806/i-want-to-convert-stdstring-into-a-const-wchar-t
		//If this function is needed again arrange deleting the dynamically allocated wString.
		wchar_t* charToLPCWSTR(const char* chrOrig) { //How to convert char* to LPCWSTR? @ http://stackoverflow.com/questions/19715144/how-to-convert-char-to-lpcwstr 
			size_t intNewsize = strlen(chrOrig) + 1;
			wchar_t* wString = new wchar_t[intNewsize];
				MultiByteToWideChar(CP_ACP, 0, chrOrig, -1, wString, intNewsize);
				return wString;
		}
		*/

		/*inline*/ wstring stringToWstring(const string& str) { 
			return wstring(str.cbegin(), str.cend()); 
		} 
		
		//How to convert wstring into string? @ https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string 
		/*inline*/ string wstringToString(const wstring& str) { 
			return string(str.cbegin(), str.cend()); 
		}; 

		/*KTB
		//������� ��������� � ��������� 
		//������ ���������� ������� ��������� ������ onalltrade ������ dll @ 
		//http://quikluacsharp.ru/qlua-c-cpp-csharp/primer-realizatsii-funktsii-obratnogo-vyzova-onalltrade-vnutri-dll/
		void message(lua_State* L, const char* chrMessage) { 
			if (L == 0) return; //Hasn't L been initialised?
			lua_getglobal(L, "message");
			lua_pushfstring(L, chrMessage);
			lua_pcall(L, 1, 0, 0);
		}
	
		void message(lua_State* L, const string& srtMessage) { 
			message(L, srtMessage.c_str());
		}
		*/

		/*KTB
		static void message_atomic(const string& strMessage, int intIcon_type, lua_State* L_ = nullptr) { 
			try {
				static lua_State* L = L_;
				
				while (msttMessages.messageFlag.test_and_set()) { //Acquire lock. //Spin.
				} 
				
				//���������� �nil� ��� ������ ���������� ��� ��� ����������� ������ �� ������� ����������. � ��������� ������� ���������� �1�. 
				lua_getglobal(L, "message");	
				lua_pushstring(L, strMessage.c_str()); 
				lua_pushinteger(L, intIcon_type); 
				lua_pcall(L, 2, 1, 0); 
				lua_pop(L, 1); 
								
				msttMessages.messageFlag.clear(); //Release lock.
			}
			
			catch (const std::exception& objException) { 
				messageException(objException, __FUNCTION__, __LINE__); 
			}
		}

		void messageAtomic(const string& srtMessage) { 
			static int intIcon_type_information = 1;
			thread objThread(message_atomic, srtMessage, intIcon_type_information, nullptr); 
			objThread.detach();
		}
		*/

		/*KTB
		#pragma warning(disable: 4996) //To use the localtime() function instead of a safe localtime_s() suggested. //TO DO: Use the safe localtime_s() function suggested.
		
		// ���� �� ���������� �������� ������� DLL (C/C++), ���������� � ����������� ������� @ 
		//http://quikluacsharp.ru/c-c-osnovy/odin-iz-prostejshih-sposobov-otladki-dll-c-c-rabotayushhej-s-imenovannoj-pamyatyu/ 
		void log(string strLog) { 
			const char* chrFileName = (gstrMTQC + " - Log.log").c_str();
			FILE* f = fopen(chrFileName, "a"); // ������� ���� ���� //fopen, _wfopen @ https://msdn.microsoft.com/en-us/library/yeby3zcb.aspx
			char DebugLine[256] = "";
			sprintf_s(DebugLine, "%s\n", strLog);
			//OFF if (pb != NULL) { sprintf_s(DebugLine, "%s   � ������:%s", DebugLine, pb); }
			fwrite(DebugLine, sizeof(DebugLine), 1, f);
			fwrite("\n", sizeof("\n"), 1, f);
			fflush(f);
			fclose(f);
		}*/

		/*KTB
		#include <fstream>
		
		namespace fncFile { 
			using std::ifstream;
			using std::ofstream;

			// Check if the file exists and return true. Otherwise create one and write an input to it. 
			bool checkOrCreate(const string& strFileName, const string& strInput) { 
				ifstream objFile(strFileName);
				if (objFile.good()) {
					objFile.close();
					return true; //Does it exist?
				}
				else { //Create a file and write an input to it, if necessary.
					ofstream objFile(strFileName);
					if (strInput != "") objFile << strInput; //Write an input to it, if necessary.
					objFile.close();
				}
			}
		}*/
	}
}