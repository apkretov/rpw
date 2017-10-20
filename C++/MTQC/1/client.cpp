#include <exception>
using std::exception;
#include "terminal.h"
#include "messages.h"
using namespace mtqc;
#include "MT4QuikConnector.h"
using namespace mtqc::MT4QuikConnector;
#include "functions.h"
using namespace mtqc::functions;
using std::unique_ptr;

namespace mtqc {
	namespace client {
		//unique_ptr<LPTSTR/*IMPORTANT: Not char*/[]> wchar_tToChar(wchar_t* chrOrig) { // Convert from wchar_t to char. //"How to: Convert Between Various String Types" @ https://msdn.microsoft.com/en-us/library/ms235631.aspx
		unique_ptr<LPTSTR[]> wchar_tToChar(const wchar_t* const chrOrig) { // Convert from wchar_t to char. IMPORTANT: LPTSTR vs. char*! //"How to: Convert Between Various String Types" @ https://msdn.microsoft.com/en-us/library/ms235631.aspx
			size_t origsize = wcslen(chrOrig) + 1; // Convert the wchar_t string to a char* string. Record the length of the original string and add 1 to it to account for the terminating null character.
			size_t convertedChars = 0;
			const size_t newsize = origsize * 2; // Allocate two bytes in the multibyte output string for every wide character in the input string (including a wide character null). Because a multibyte character can be one or two bytes, you should allot two bytes for each character. Having extra space for the new string is not an error, but having insufficient space is a potential security problem.
			unique_ptr<LPTSTR[]> nstring = std::make_unique<LPTSTR[]>(newsize); //Введение в C++11: умные указатели - Вместо заключения - Для unique_ptr мы имеем дело с предопределенной специализацией для массивов. Для ее использования необходимо указать [] возле параметра шаблона. @ http://archive.kalnytskyi.com/2011/11/02/smart-pointers-in-cpp11/ //Resume
			wcstombs_s(&convertedChars, (char*)nstring.get(), newsize, chrOrig, _TRUNCATE); // Put a copy of the converted string into nstring
			return nstring;
}	}	}

//__declspec(dllexport) wchar_t* __stdcall messsagToMTQC(wchar_t* pWCBuffer) { //CHECKED: 1) The input and output are non-const due to MT4. 2) Outside the mtqc namespace due to MT4. //"Transactions on Named Pipes" @ https://msdn.microsoft.com/en-us/library/aa365789(v=vs.85).aspx
MTQC_API wchar_t* __stdcall messsagToMTQC(wchar_t* pWCBuffer) { //CHECKED: 1) The input and output are non-const due to MT4. 2) Outside the mtqc namespace due to MT4. //"Transactions on Named Pipes" @ https://msdn.microsoft.com/en-us/library/aa365789(v=vs.85).aspx
	try {
		constexpr int BUFSIZE = 4096;
		auto charToWchar_t = [](const char* const chrOrig) { return const_cast<wchar_t*>(stringToWstring(chrOrig).c_str()); };
		//LPTSTR lpszWrite = *wchar_tToChar(pWCBuffer);
		unique_ptr<LPTSTR[]> lpszWrite = client::wchar_tToChar(pWCBuffer);
		HANDLE hPipe;
		TCHAR chReadBuf[BUFSIZE];
		BOOL fSuccess;
		DWORD cbRead, dwMode;
		LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");
		//wchar_t* chrMsgFromQuik;
		wchar_t* chrMsgFromQuik{};
		//char* chrMsgFromQuik;
		do { // Try to open a named pipe; wait for it, if necessary. 
			hPipe = CreateFile(lpszPipename /*pipe name*/, GENERIC_READ | GENERIC_WRITE /*read and write access*/, 0 /*no sharing*/, NULL /*default security attributes*/, OPEN_EXISTING /*opens existing pipe*/, 0 /*default attributes*/, NULL /*no template file*/);
			if (hPipe != INVALID_HANDLE_VALUE) break; // Break if the pipe handle is valid. 
			if (GetLastError() != ERROR_PIPE_BUSY) return L"Could not open pipe"; // Exit if an error other than ERROR_PIPE_BUSY occurs. 
			if (!WaitNamedPipe(lpszPipename, 1000)) return L"Could not open pipe"; // All pipe instances are busy, so wait for 20 seconds. 
		} while (gobjTerminal.getRun());
		dwMode = PIPE_READMODE_MESSAGE; // The pipe connected; change to message-read mode. 
		fSuccess = SetNamedPipeHandleState(hPipe /*pipe handle */, &dwMode /*new pipe mode*/, NULL /*don't set maximum bytes*/, NULL /*don't set maximum time*/);
		if (!fSuccess) return L"SetNamedPipeHandleState failed.";
		//fSuccess = TransactNamedPipe(hPipe /*pipe handle*/, lpszWrite /*message to server*/, // Send a message to the pipe server and read the response.
		//	(lstrlen(lpszWrite) + 1) * sizeof(TCHAR) /*message length*/, //get length of `wchar_t*` in c++ @ http://stackoverflow.com/questions/2853615/get-length-of-wchar-t-in-c
		//	chReadBuf /*buffer to receive reply*/, BUFSIZE*sizeof(TCHAR) /*size of read buffer*/, &cbRead /*bytes read*/, NULL /*not overlapped*/
		//); 
		fSuccess = TransactNamedPipe(hPipe /*pipe handle*/, lpszWrite.get() /*message to server*/, // Send a message to the pipe server and read the response.
			(lstrlen((LPCSTR)lpszWrite.get()) + 1) * sizeof(TCHAR) /*message length*/, //get length of `wchar_t*` in c++ @ http://stackoverflow.com/questions/2853615/get-length-of-wchar-t-in-c
			chReadBuf /*buffer to receive reply*/, BUFSIZE*sizeof(TCHAR) /*size of read buffer*/, &cbRead /*bytes read*/, NULL /*not overlapped*/
		); 
		if (!fSuccess && (GetLastError() != ERROR_MORE_DATA)) return L"TransactNamedPipe failed.";
		do {
			if (fSuccess) { // Break if TransactNamedPipe or ReadFile is successful
				chrMsgFromQuik = charToWchar_t(chReadBuf);
				//chrMsgFromQuik = chReadBuf;
				break;
			}
			fSuccess = ReadFile(hPipe /*pipe handle*/, chReadBuf /*buffer to receive reply*/, BUFSIZE*sizeof(TCHAR) /*size of buffer*/, &cbRead /*number of bytes read*/, NULL /*not overlapped*/); // Read from the pipe if there is more data in the message.
			if (!fSuccess && (GetLastError() != ERROR_MORE_DATA)) break; // Exit if an error other than ERROR_MORE_DATA occurs.
			chrMsgFromQuik = charToWchar_t(chReadBuf);
			//chrMsgFromQuik = chReadBuf;
		} while (gobjTerminal.getRun());
		CloseHandle(hPipe);
		return chrMsgFromQuik;
	}
	catch (const exception& objException) {
		messages::messageException(objException, __FUNCTION__, __LINE__);
		return L"";
	}	
}

