#include "afxwin.h" //	Step1.cpp //���� ������ ���� (http://www.firststeps.ru/) ���� ����� (1999-2001) ������� 1999 �.	���������� 24.06.2001 // MFC �������� � ����������� ����������

class CMainWnd : public CFrameWnd {
public:
	CMainWnd() { Create(NULL, _T("Step1"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); } // ������� ���� ���������;	// ����������� �� ���������
};

class CMyApp : public CWinApp {
public:
	CMyApp() {}; //����������� �� ���������
	virtual BOOL InitInstance() { //����������� �������������
		m_pMainWnd = new CMainWnd();	// ������� ����� ����
		ASSERT(m_pMainWnd);	// ��������� ��� ������������
		m_pMainWnd->ShowWindow(SW_SHOW);// �������� ����
		m_pMainWnd->UpdateWindow();	// �������� ����
		//TEST m_pMainWnd = nullptr; //���� �� ��������� InitInstance() �� ����� ����� ����, �� ���������� ����������. � �����������, ����� ���������� ����������� �� ����������. @ http://www.firststeps.ru/mfc/steps/r.php?1
		return TRUE;		// ������� ��� ��� ���������
		//TEST return 0;
	};
};

CMyApp theApp;	// ������ ����������