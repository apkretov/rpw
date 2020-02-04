// Step4.cpp // ���� ������ ���� (firststeps.narod.ru) ���� ����� (1999-2001) ��������  1999 �. ���������� 25.06.2001				
#include "afxwin.h"					// MFC �������� � ����������� ����������
#define IDC_MYBUTTON	100			// ������������� ������
#define IDC_MYEDIT	102			// ������������� ���� ��������������

class CMyButton : public CButton {
	DECLARE_MESSAGE_MAP(); 				// ������� �������� ������ 
public:
	afx_msg void OnLButtonDblClk(UINT, CPoint);
	afx_msg void OnRButtonDblClk(UINT, CPoint);
};

BEGIN_MESSAGE_MAP(CMyButton, CButton)	// ������� �������� �� ��������� 
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

void CMyButton::OnLButtonDblClk(UINT, CPoint) { MoveWindow(CRect(120, 100, 220, 150), TRUE); }
void CMyButton::OnRButtonDblClk(UINT, CPoint) { MoveWindow(CRect(120, 10, 220, 50), TRUE); }

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;				// ��������� �� ������ �������
	CMyButton* MyButton;				// ������� ���������� ������
	CEdit* MyEdit;						// ��������� �� ������ ���� ��������������
	DECLARE_MESSAGE_MAP();			// ������� ��������
public:
	CMainWnd();							// ����������� �� ���������
	~CMainWnd();						// ���������� 
	afx_msg void OnLButtonDblClk(UINT, CPoint);          // ����������� ��������� ������ �� ����� ������
	afx_msg void OnRButtonDblClk(UINT, CPoint);          // ����������� ��������� ������ �� ������ ������
	afx_msg void OnKeyDown(UINT, UINT, UINT);            // ����������� ��������� ������ �� �������
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd) // ������� �������� �� ��������� 
	ON_WM_LBUTTONDBLCLK()     		      // ������� �� ������� ����� ������ ����
	ON_WM_RBUTTONDBLCLK()     		      // ������� �� ������� ������ ������ �����
	ON_WM_KEYDOWN()     						// ������� �� ������� �������
END_MESSAGE_MAP()

void CMainWnd::OnKeyDown(UINT, UINT, UINT) { AfxMessageBox(_T(" Key Button Down ")); }
void CMainWnd::OnRButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Rigth Button Click ")); }
//ORIG void CMainWnd::OnLButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Left Button Click ")); }
void CMainWnd::OnLButtonDblClk(UINT, CPoint) { //TEST
	MoveWindow(CRect(120, 100, 1220, 650), TRUE);
	AfxMessageBox(_T(" Left Button Click "));
}

CMainWnd::CMainWnd() {
	Create(NULL, _T("Step4"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);						// ������� ���� ���������
	MyStatic = new CStatic(); // �������� new �� ��������� � ������ ������ ������ NULL // �������� ��������� �� NULL ���� ����������� ���������� �� ���������� ������
	if (MyStatic !=  NULL)  MyStatic->Create(_T("MyStatic"), WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(10, 10, 100, 50), this);			// ������� 
	MyButton = new CMyButton();       // ������ ����� �� ������ �������� ��������� ������
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON);
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd() {
	if (MyStatic !=  NULL) delete MyStatic;	// ������� ������������ ������
	if (MyButton !=  NULL) delete MyButton;		// ������� ������������ ������
	if (MyEdit !=  NULL) delete MyEdit;			// ������� ������������ ������
}

class CMyApp : public CWinApp {
public:
	CMyApp();							// ����������� �� ���������
	virtual BOOL InitInstance();		// ����������� �������������
};

CMyApp::CMyApp()						// ����������� �������� ������ ����������
{}

BOOL CMyApp::InitInstance()				// ����������� �������������
{
	m_pMainWnd = new CMainWnd();			// ������� ����� ����
	ASSERT(m_pMainWnd);					// ��������� ��� ������������
	m_pMainWnd->ShowWindow(SW_SHOW);	// �������� ����
	m_pMainWnd->UpdateWindow();			// �������� ����
	return TRUE;						// ������� ��� ��� ��������� 
};

CMyApp theApp;							// ������ ����������

