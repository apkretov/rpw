#include "afxwin.h"
#define IDC_MYBUTTON 100	// ������������� ������
#define IDC_MYEDIT 102	// ������������� ���� ��������������

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;	// ��������� �� ������ �������
	CButton* MyButton;	// ��������� �� ������ ������
	CEdit* MyEdit;	// ��������� �� ������ ���� ��������������
public:
	CMainWnd() { // ����������� �� ���������
		Create(NULL, _T("Step2"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // ������� ���� ���������
		MyStatic = new CStatic(); // �������� new �� ��������� � ������ ������ ������ NULL �������� ��������� �� NULL ���� ����������� ���������� �� ���������� ������
		if (MyStatic !=  NULL) MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(10, 10, 100, 50), this);	// �������
		MyButton = new CButton();
		if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON);
		MyEdit = new CEdit();
		if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
	}
	~CMainWnd() { // ����������
		if (MyStatic !=  NULL) delete MyStatic;	// ������� ������������ ������
		if (MyButton !=  NULL) delete MyButton;	// ������� ������������ ������
		if (MyEdit !=  NULL) delete MyEdit;	// ������� ������������ ������
	}
};

class CMyApp : public CWinApp {
public:
	CMyApp() {}; //����������� �� ���������
	virtual BOOL InitInstance() { //����������� �������������
		m_pMainWnd = new CMainWnd();	// ������� ����� ����
		ASSERT(m_pMainWnd);	// ��������� ��� ������������
		m_pMainWnd->ShowWindow(SW_SHOW);// �������� ����
		m_pMainWnd->UpdateWindow();	// �������� ����
		return TRUE;		// ������� ��� ��� ���������
	};
};

CMyApp theApp;	// ������ ����������