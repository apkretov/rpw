#include "afxwin.h"						// MFC �������� � ����������� ����������
#include "afxext.h"						// MFC ����������
#include "resource.h"
#define IDC_MYBUTTON	100				// ������������� ������
#define IDC_MYEDIT	102				// ������������� ���� ��������������
#define IDC_LIST1		103				// ������������� ���� �� �������

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

class CMyPaintDC: public CPaintDC {
public:
	CMyPaintDC(CWnd* pWnd);						// �����������
	void DrawCross(int iPosX, int iPosY);	// ������� ��������� ������
};

CMyPaintDC::CMyPaintDC(CWnd* pWnd) : CPaintDC(pWnd)	{ } // �� ���� CPainDC

void CMyPaintDC::DrawCross(int iPosX, int iPosY) {	// ��� �������� ����� ������ ���������� ������� CPaintDC 
	MoveTo(iPosX-50, iPosY);
	LineTo(iPosX+50, iPosY);
	MoveTo(iPosX, iPosY-50);
	LineTo(iPosX, iPosY+50);
}

class CMyDialog : public CDialog {
	CListBox *cListBox;	// ��������� �� ������� ����������
	CString csListTextItem;	// ������������ ��������
public:
	CMyDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);	// �����������
	~CMyDialog();	// ����������
	virtual BOOL OnInitDialog();	// �������������
	virtual void OnOK();	// ������� �� ������� OK
	CString GetString();	// �������� ������
};

CMyDialog::CMyDialog(UINT nIDTemplate, CWnd* pParentWnd):CDialog(nIDTemplate, pParentWnd) { cListBox = NULL; } // ������� ���, NULL
CMyDialog::~CMyDialog() { if (cListBox !=  NULL) delete cListBox;	} // ���� ������ ��� ������ �������
CString CMyDialog::GetString() {	return csListTextItem; } // ������� ���������

void CMyDialog::OnOK() { // ����� ������ ������ OK
	if (cListBox->GetCurSel() ==  LB_ERR)	AfxMessageBox(_T("Select Item List Box"));	// ���� � ������ ������ �� ������� // �������� � ������
	else { // �����, �� ���� ���-�� �������
		cListBox->GetText(cListBox->GetCurSel(), csListTextItem); // �������� ���������
		CDialog::OnOK(); // ������� ������� ������
}	}

BOOL CMyDialog::OnInitDialog() {
	CDialog::OnInitDialog(); // ����� ������
	CenterWindow(); // �� ������ ����
	CRect rect(10, 10, 100, 100);	// ���������� ��� ������
	cListBox = new CListBox(); // ������� ������ ������
	cListBox->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|LBS_NOTIFY|WS_VSCROLL|WS_BORDER, rect, this, IDC_LIST1); // � ��� ������ ������ ��� � ���������������
	if (cListBox !=  NULL) {
		cListBox->AddString(_T("Good"));	// �������� ������
		cListBox->AddString(_T("Bad"));	// ���
		cListBox->AddString(_T("VOID"));	// ���
		return TRUE;	// ������� ��� ��� ������.
	}
	else return FALSE;	// �� ������ ������� ������
}

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
	afx_msg void OnLButtonDblClk(UINT, CPoint);	// ����������� ��������� ������ �� ����� ������
	afx_msg void OnRButtonDblClk(UINT, CPoint);	// ����������� ��������� ������ �� ������ ������
	afx_msg void OnKeyDown(UINT, UINT, UINT);		// ����������� ��������� ������ �� �������
	int OnCreate(LPCREATESTRUCT lpCreateStruct);	// ��� ������� ���������� ��� �������� ����
	void MenuExit();										// ��������� ������� �� ����� ������ ���� 
	void MenuSwitch();									// ��������� ������� �� ����� ������ ���� 
	afx_msg void OnPaint();								// �������������� ������� ��������� � ����
	void OnOpen();											// ��� ������� ��������� ��� ������ ���� Open
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)		// ������� �������� �� ��������� 
	ON_WM_LBUTTONDBLCLK()     					// ������� �� ������� ����� ������ ����
	ON_WM_RBUTTONDBLCLK()     					// ������� �� ������� ������ ������ �����
	ON_WM_KEYDOWN()     							// ������� �� ������� �������
	ON_WM_CREATE()									// ������� �������� ����
	ON_COMMAND(ID_FILE_EXIT, MenuExit)		// ��� ��� , ��������� ������� �� ����� ����
	ON_COMMAND(ID_FILE_SWITCH, MenuSwitch)	// ������� �� ����� ������ � ������������ ����� ����
	ON_WM_PAINT()									// ��� �������. ���� ���� ���� �������, ��� ��� �����.
	ON_COMMAND(ID_OPEN, OnOpen)				// ������� �� ����� ���� Open
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	blMenu = FALSE;	// ������������� TRUE ������������� IDR_MENU
	Create(NULL, _T("Step15"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // ������� ���� ���������
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

void CMainWnd::OnLButtonDblClk(UINT, CPoint) { 
	CMyDialog about(IDD_DIALOG2);	// ������� ������ ������ ������
	if (about.DoModal() ==  IDOK)	AfxMessageBox(about.GetString()); // ���� ������������ ������ OK // �������� ���������
}
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
	CMyPaintDC dc(this);	// ��� ����� 
	CPen MyPen(PS_DASHDOT, 1, RGB(0, 255, 0));	// ����������� ����
	dc.SelectObject(MyPen);	// �������� ����
	for (int x = 1;x<400;x = x+50)	dc.DrawCross(100+x, 100+x);	// ���� �������
}

void CMainWnd::OnOpen() {
	CFileDialog fileDialog(TRUE, NULL, _T("*.cpp"));	//������ ������ ������ �����
	int result = fileDialog.DoModal();	//��������� ���������� ����
	if (result ==  IDOK) AfxMessageBox(fileDialog.GetPathName()); //���� ���� ������ // �������� ������ ����
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
