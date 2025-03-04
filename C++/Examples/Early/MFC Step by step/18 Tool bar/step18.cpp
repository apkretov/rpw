#include "afxwin.h"						// MFC �������� � ����������� ����������
#include "afxext.h"						// MFC ����������
#include "resource.h"					// �������������� ��������
#include "MyClip.h"						// �������� ������ ������

#define IDC_MYBUTTON	100				// ������������� ������
#define IDC_MYEDIT		102				// ������������� ���� ��������������
#define IDC_LIST1       103				// ������������� ���� �� �������

static UINT indicators[] = { IDS_STRING2, IDS_STRING1 }; // ������������� ������ ������ � �������� // ������������� ������ ������ � ��������

class CMyDialog : public CDialog {
public:
	CMyDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);	// �����������
	~CMyDialog();											// ����������
	virtual BOOL OnInitDialog();							// �������������
	virtual void OnOK();									// ������� �� ������� OK
	CString GetString();									// �������� ������
private:
	CListBox *cListBox;										// ��������� �� ������� ����������
	CString csListTextItem;									// ������������ ��������	
};

CMyDialog::~CMyDialog()
{
	if (cListBox !=  NULL) delete cListBox;					// ���� ������ ��� ������ �������
}

CString CMyDialog::GetString()
{
	return csListTextItem;									// ������� ���������
}

void CMyDialog::OnOK()										// ����� ������ ������ OK
{
	if (cListBox->GetCurSel() ==  LB_ERR)						// ���� � ������ ������ �� ������
    {
		//AfxMessageBox("Select Item List Box");				// �������� � ������
	}
	else													// ����� �� ���� ��� �� �������
	{
        cListBox->GetText(cListBox->GetCurSel(), csListTextItem); // �������� ���������
		CDialog::OnOK();										 // ������� ������� ������	
    }
}


CMyDialog::CMyDialog(UINT nIDTemplate, CWnd* pParentWnd)
           :CDialog(nIDTemplate, pParentWnd)
{
	cListBox = NULL;								// ������� ��� NULL
}


BOOL CMyDialog::OnInitDialog()
{
  CDialog::OnInitDialog();						// ����� ������
  CenterWindow();								// �� ������ ����
  CRect rect(10, 10, 100, 100);					// ���������� ��� ������
  cListBox = new CListBox();						// ������� ������ �����
  cListBox->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |LBS_NOTIFY | WS_VSCROLL   | WS_BORDER, rect, 
					this, IDC_LIST1);	
  if (cListBox !=  NULL)
  {
  //cListBox->AddString("God");					// �������� ������
  //cListBox->AddString("Bad");					// ���
  //cListBox->AddString("VOID");					// ������� ��� ��� ������.
  return TRUE;
  }
  else return FALSE;							// �������� ������� ������
}



class CMyPaintDC: public CPaintDC
{
public:
 CMyPaintDC(CWnd* pWnd);					// �����������
 void DrawCross(int iPosX, int iPosY);		// ������� ��������� ������
};

CMyPaintDC::CMyPaintDC(CWnd* pWnd)
	       :CPaintDC(pWnd)					// �� ���� CPainDC       
{
}

void CMyPaintDC::DrawCross(int iPosX, int iPosY)	// ��� �������� ����� ������ ����������
{													// ������� CPaintDC
	MoveTo(iPosX-50, iPosY);
	LineTo(iPosX+50, iPosY);
	MoveTo(iPosX, iPosY-50);
	LineTo(iPosX, iPosY+50);
}

class CMyButton: public CButton 
{ 
public:
   afx_msg void OnLButtonDblClk(UINT, CPoint);
   afx_msg void OnRButtonDblClk(UINT, CPoint); 
private:
   DECLARE_MESSAGE_MAP(); 			// ������� �������� ������ 
};


void CMyButton::OnLButtonDblClk(UINT, CPoint) 
{
   MoveWindow(CRect(120, 100, 220, 150), TRUE); 
}

void CMyButton::OnRButtonDblClk(UINT, CPoint) 
{
   MoveWindow(CRect(120, 10, 220, 50), TRUE); 
}
 
BEGIN_MESSAGE_MAP(CMyButton, CButton)         // ������� �������� �� ��������� 
 ON_WM_LBUTTONDBLCLK() 
 ON_WM_RBUTTONDBLCLK() 
END_MESSAGE_MAP()

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();							// ����������� �� ���������
	void OnCopyBuffer();				// ���������� � �����
	void OnOpen();						// ��� ������� ��������� ��� ������ ���� Open
	afx_msg void OnLButtonDblClk(UINT, CPoint);          // ����������� ��������� ������ �� ����� ������
    afx_msg void OnRButtonDblClk(UINT, CPoint);          // ����������� ��������� ������ �� ������ ������
    afx_msg void OnKeyDown(UINT, UINT, UINT);            // ����������� ��������� ������ �� �������
	int OnCreate(LPCREATESTRUCT lpCreateStruct);           // ��� ������� ���������� ��� �������� ����
	void MenuExit();										// ��������� ������� �� ����� ������ ���� 
	void MenuSwitch();										// ��������� ������� �� ����� ������ ����
	afx_msg void OnPaint();	            // �������������� ������� ��������� � ���� 
	afx_msg void OnMouseMove(UINT, CPoint cp);		// ��� ������� ����� ���������� ��� �������� ����
	~CMainWnd();						// ���������� 
private:    
	BOOL blMenu;					// ����� ���� �������
	CStatic* MyStatic;				// ��������� �� ������ �������
    CMyButton* MyButton;			// ������� ���������� ������
    CEdit* MyEdit;					// ��������� �� ������ ���� ��������������
	CStatusBar m_wndStatusBar;		// ����� ������ ���������
	CMenu m_wndMenu;				// ��� ��� ����� ����
	CMyClip clip;					// ��� ����� ������ ������
	CToolBar   my_ToolBar;		// ��� ��� ����� ������ ������������ 
	DECLARE_MESSAGE_MAP();			// ������� ��������
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd) // ������� �������� �� ��������� 
	ON_WM_LBUTTONDBLCLK()     		       // ������� �� ������� ����� ������ ����
	ON_WM_RBUTTONDBLCLK()     		       // ������� �� ������� ������ ������ �����
	ON_WM_KEYDOWN()     			       // ������� �� ������� �������
	ON_WM_CREATE()						   // ������� �������� ����
	ON_WM_PAINT()						   // ��� �������. ���� ���� ���� ������� , ��� ��� �����.
	ON_COMMAND(ID_OPEN, OnOpen)			   // ������� �� ����� ���� Open
	ON_BN_CLICKED(IDC_MYBUTTON, OnCopyBuffer)	// ������ �� ������ ����� ������� ����
	ON_COMMAND(ID_FILE_EXIT, MenuExit)		   // ��� ��� , ��������� ������� �� ����� ���� 
	ON_COMMAND(ID_FILE_SWITCH, MenuSwitch)		// ������� �� ����� ������ � ������������ ����� ����
	ON_WM_MOUSEMOVE()					   // ���� ���������
END_MESSAGE_MAP()

void CMainWnd::OnCopyBuffer()
{
 clip.CopyText("Hello My Text"); // ���������� � ����� �����
}


void CMainWnd::OnOpen()
{
  //CFileDialog fileDialog(TRUE, NULL, "*.mak", NULL, "File Mak (*.mak)|*.mak|Resouce Files (*.res)|*.res|");
 //int result = fileDialog.DoModal();

	
}


void CMainWnd::MenuExit()  
{	
	DestroyWindow(); // ���������� ����   
}


void CMainWnd::OnPaint()
{
	CMyPaintDC dc(this);					// ��� ����� 
	CPen MyPen(PS_DASHDOT, 1, RGB(0, 255, 0));	// ������������ ����
	dc.SelectObject(MyPen);					// �������� ����
	for (int x = 1;x<400;x = x+50)
	{
          dc.DrawCross(100+x, 100+x);		// ���� �������
	}
}

void CMainWnd::MenuSwitch()
{
	m_wndMenu.DestroyMenu();	// ���������� ������
	switch (blMenu)
	{
	case TRUE:
		m_wndMenu.LoadMenu(IDR_MENU);	// ������ �����
		break;
	case FALSE:
		m_wndMenu.LoadMenu(IDR_MENU_RUS);	// ������ �����
		break;
	}
	blMenu = !blMenu;				// ������ ����������
	SetMenu(&m_wndMenu);		// ������������� ����
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CFrameWnd::OnCreate(lpCreateStruct) ==   -1)  return -1;
  m_wndStatusBar.Create(this); 
  m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)); // ���������� � ������ ��������������
  m_wndMenu.LoadMenu(IDR_MENU); // ��������� ���� �� ����� �������
  SetMenu(&m_wndMenu); // ���������� ����
  my_ToolBar.Create(this);						    // ������� ������ �������������
  my_ToolBar.LoadToolBar(IDR_TOOLBAR1);					    // ����� �� �� ��������
  my_ToolBar.SetBarStyle(my_ToolBar.GetBarStyle()  | CBRS_SIZE_DYNAMIC);    // ��������� �����
  my_ToolBar.EnableDocking(CBRS_ALIGN_ANY);				    // ����� �� ������ ���������
  EnableDocking(CBRS_ALIGN_ANY);					    // ������� ���� ��� ���������� �������
  DockControlBar(&my_ToolBar); 
  return 0;
}

void CMainWnd::OnKeyDown(UINT, UINT, UINT) 
{
    AfxMessageBox(clip.GetText());				// �������� �����
}

void CMainWnd::OnRButtonDblClk(UINT, CPoint) 
{
    CDialog about(IDD_DIALOG1);		// ������� ������ ������ ����������� ����    
	//if (about.DoModal() ==  IDOK) AfxMessageBox("Ok");	// ������������ ������ OK
 //   else AfxMessageBox("Cancel");						// ������������ ������ Cansel
}

void CMainWnd::OnLButtonDblClk(UINT, CPoint) 
{
    CMyDialog about(IDD_DIALOG2);		// ������� ������ ������ ������
	if (about.DoModal() ==  IDOK)			// ���� ������������ ������ OK 
	{
	 AfxMessageBox(about.GetString());	// �������� ��������� 
	} 
}

void CMainWnd::OnMouseMove(UINT, CPoint cp) {
	char chX[10];				// ����� ��� ���������
	char chY[10];				// ����� ��� ���������
	_itoa_s(cp.x, chX, 10);			// ����� ��������� � ������
	_itoa_s(cp.y, chY, 10);			// ����� ��������� � ������
	CString  csStatusX(chX);		// ��������� ������
	CString  csStatusY(chY);		// ��������� ������
	m_wndStatusBar.SetPaneText(0, csStatusX);		// �������  ������ ������
	m_wndStatusBar.SetPaneText(1, csStatusY);		// �������   ������ ������ 
}

CMainWnd::CMainWnd() {
	blMenu = FALSE; // ������������� TRUE ������������� IDR_MENU
	Create(NULL, _T("Step18"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // ������� ���� ���������
	MyStatic = new CStatic();				
	if (MyStatic !=  NULL)  MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(10, 50, 100, 100), this); // ������� 
	MyButton = new CMyButton(); // ������ ����� �� ������ �������� ��������� ������
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 50, 220, 100), this, IDC_MYBUTTON); 
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 50, 340, 100), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd() {
	if (MyStatic !=  NULL)	delete MyStatic;	// ������� ������������ ������
	if (MyButton !=  NULL)delete MyButton;		// ������� ������������ ������
	if (MyEdit !=  NULL)delete MyEdit;			// ������� ������������ ������
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

