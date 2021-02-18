// MyClip.cpp: implementation of the CMyClip class.
//
//////////////////////////////////////////////////////////////////////

#include "MyClip.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyClip::CMyClip()
{
}

CMyClip::~CMyClip()
{
}


CString CMyClip::GetText()
{
	char * buffer;								// указатель на данные
	if (AfxGetMainWnd()->OpenClipboard())		// если буфер обмена удалось открыть то
	{
		buffer = (char*)GetClipboardData(CF_TEXT); // получить из буфера текст		
		CloseClipboard();						   // закрыть буфер обмена 
		return buffer;							   // вернуть результат
	}
	return "";
}

void CMyClip::CopyText(CString test) {
	//if (AfxGetMainWnd()->OpenClipboard())	// если буфер обмена удалось открыть то
	//{
	//	if (EmptyClipboard())			// Очистить буфер
	//	{
	//		HGLOBAL clipbuffer;
	//		char * buffer;				// указатель на данные	
	//		clipbuffer = GlobalAlloc(GMEM_DDESHARE, test.GetLength() + 1);	// выделить память
	//		buffer = (char*)GlobalLock(clipbuffer);						// блокировать буфер
	//		strcpy(buffer, LPCSTR(test));								// копировать в него данные
	//		GlobalUnlock(clipbuffer);									// разблокировать
	//		SetClipboardData(CF_TEXT, clipbuffer);					    // установить данные и тип
	//		if (!CloseClipboard()) AfxMessageBox(L"Error Close");			// закрыть
	//	}
	//	else AfxMessageBox(L"Error Empty");
	//}
	//else AfxMessageBox(L"Error Open");
}

