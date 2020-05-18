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
	char * buffer;								// ��������� �� ������
	if (AfxGetMainWnd()->OpenClipboard())		// ���� ����� ������ ������� ������� ��
	{
		buffer = (char*)GetClipboardData(CF_TEXT); // �������� �� ������ �����		
		CloseClipboard();						   // ������� ����� ������ 
		return buffer;							   // ������� ���������
	}
	return "";
}

void CMyClip::CopyText(CString test) {
	//if (AfxGetMainWnd()->OpenClipboard())	// ���� ����� ������ ������� ������� ��
	//{
	//	if (EmptyClipboard())			// �������� �����
	//	{
	//		HGLOBAL clipbuffer;
	//		char * buffer;				// ��������� �� ������	
	//		clipbuffer = GlobalAlloc(GMEM_DDESHARE, test.GetLength() + 1);	// �������� ������
	//		buffer = (char*)GlobalLock(clipbuffer);						// ����������� �����
	//		strcpy(buffer, LPCSTR(test));								// ���������� � ���� ������
	//		GlobalUnlock(clipbuffer);									// ��������������
	//		SetClipboardData(CF_TEXT, clipbuffer);					    // ���������� ������ � ���
	//		if (!CloseClipboard()) AfxMessageBox(L"Error Close");			// �������
	//	}
	//	else AfxMessageBox(L"Error Empty");
	//}
	//else AfxMessageBox(L"Error Open");
}

