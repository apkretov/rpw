#include "afxwin.h"						// MFC �������� � ����������� ����������
#include "afxext.h"						// MFC ����������
#include "resource.h"
#define IDC_MYBUTTON	100				// ������������� ������
#define IDC_MYEDIT	102				// ������������� ���� ��������������

class CMyButton: public CButton { 
   DECLARE_MESSAGE_MAP(); 			// ������� �������� ������ 
public:
   afx_msg void OnLButtonDblClk(UINT, CPoint);
   afx_msg void OnRButtonDblClk(UINT, CPoint); 
};

void CMyButton::OnLButtonDblClk(UINT, CPoint) { MoveWindow(CRect(120, 100, 220, 150), TRUE); }
void CMyButton::OnRButtonDblClk(UINT, CPoint) { MoveWindow(CRect(120, 10, 220, 50), TRUE); }
 
BEGIN_MESSAGE_MAP(CMyButton, CButton)         // ������� �������� �� ��������� 
	ON_WM_LBUTTONDBLCLK() 
	ON_WM_RBUTTONDBLCLK() 
END_MESSAGE_MAP()

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;			// ��������� �� ������ �������
	CMyButton* MyButton;			// ������� ���������� ������
	CEdit* MyEdit;					// ��������� �� ������ ���� ��������������
	CStatusBar m_wndStatusBar;	// ����� ������ ��������� //�� ������� ����������. �� ���� ��� �������� ������� ����, ������������� ��������� ����� ������ ���������, � �� ����� ����, ���� ����� ������ ����� ����. ��� � �����. ���� ����� � �����������. @ http://www.firststeps.ru/mfc/steps/r.php?4
	CMenu m_wndMenu;				// ��� ��� ����� ����
	DECLARE_MESSAGE_MAP();		// ������� ��������
	BOOL blMenu;					// ����� ���� �������
public:
	CMainWnd();						// ����������� �� ���������
	~CMainWnd();					// ���������� 
	afx_msg void OnLButtonDblClk(UINT, CPoint);   // ����������� ��������� ������ �� ����� ������
	afx_msg void OnRButtonDblClk(UINT, CPoint);   // ����������� ��������� ������ �� ������ ������
	afx_msg void OnKeyDown(UINT, UINT, UINT);     // ����������� ��������� ������ �� �������
	int OnCreate(LPCREATESTRUCT lpCreateStruct);    // ��� ������� ���������� ��� �������� ����
	void MenuExit();											// ��������� ������� �� ����� ������ ���� 
	void MenuSwitch();										// ��������� ������� �� ����� ������ ���� 
	afx_msg void OnPaint();									// �������������� ������� ��������� � ����
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)		// ������� �������� �� ��������� 
	ON_WM_LBUTTONDBLCLK()     					// ������� �� ������� ����� ������ ����
	ON_WM_RBUTTONDBLCLK()     					// ������� �� ������� ������ ������ �����
	ON_WM_KEYDOWN()     							// ������� �� ������� �������
	ON_WM_CREATE()									// ������� �������� ����
	ON_COMMAND(ID_FILE_EXIT, MenuExit)		// ��� ��� , ��������� ������� �� ����� ����
	ON_COMMAND(ID_FILE_SWITCH, MenuSwitch)	// ������� �� ����� ������ � ������������ ����� ����
	ON_WM_PAINT()	// ��� �������. ���� ���� ���� �������, ��� ��� �����.
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	blMenu = FALSE;	// ������������� TRUE ������������� IDR_MENU
	Create(NULL, _T("Step10"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // ������� ���� ���������
	MyStatic = new CStatic();				
	if (MyStatic !=  NULL)  MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, 	CRect(10, 10, 100, 50), this); // ������� 
	MyButton = new CMyButton(); // ������ ����� �� ������ �������� ��������� ������
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON); 
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd() {
	if (MyStatic !=  NULL) delete MyStatic;	// ������� ������������ ������
	if (MyButton !=  NULL) delete MyButton;	// ������� ������������ ������
	if (MyEdit !=  NULL) delete MyEdit;			// ������� ������������ ������
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) ==   -1)  return -1;
	m_wndStatusBar.Create(this); 
	m_wndMenu.LoadMenu(IDR_MENU);	// ��������� ���� �� ����� �������
	SetMenu(&m_wndMenu);	// ���������� ����
	return 0;
}

void CMainWnd::OnKeyDown(UINT, UINT, UINT) { AfxMessageBox(_T(" Key Button Down ")); }

void CMainWnd::OnRButtonDblClk(UINT, CPoint) {
	CDialog about(IDD_DIALOG1);	// ������� ������ ������ ����������� ����
	if (about.DoModal() ==  IDOK)
		AfxMessageBox(_T("Ok"));	// ������������ ������ OK
	else
		AfxMessageBox(_T("Cancel"));	// ������������ ������ Can�el
}

void CMainWnd::OnLButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Left Button Click ")); }
void CMainWnd::MenuExit() { DestroyWindow(); } // ���������� ���� 

void CMainWnd::MenuSwitch() {
	m_wndMenu.DestroyMenu(); // ���������� ������
	switch (blMenu) {
		case TRUE: m_wndMenu.LoadMenu(IDR_MENU); break; // ������ �����
		case FALSE: m_wndMenu.LoadMenu(IDR_MENU_RUS); break; // ������ �����
	}
	blMenu = !blMenu; // ������ ����������
	SetMenu(&m_wndMenu);	// ������������� ����
}

void CMainWnd::OnPaint() {
	CPaintDC dc(this);	// �������� �������� ����������
	dc.TextOut(200, 200, "Hello MFC Programm");	// �������� � ��� ������
	dc.MoveTo(300, 300);	// ������ �������� �����
	dc.LineTo(600, 105);	// � ���������� �������� �����
	dc.LineTo(105, 105);	// � ��� ���������� �������� �����
}

class CMyApp : public CWinApp {
public:
	CMyApp();								// ����������� �� ���������
	virtual BOOL InitInstance();		// ����������� �������������
};

CMyApp::CMyApp() {}						// ����������� �������� ������ ����������

BOOL CMyApp::InitInstance() {			// ����������� �������������
	m_pMainWnd = new CMainWnd();			// ������� ����� ����
	ASSERT(m_pMainWnd);					// ��������� ��� ������������
	m_pMainWnd->ShowWindow(SW_SHOW);	// �������� ����
	m_pMainWnd->UpdateWindow();		// �������� ����
	return TRUE;							// ������� ��� ��� ��������� 
};

CMyApp theApp;								// ������ ����������
