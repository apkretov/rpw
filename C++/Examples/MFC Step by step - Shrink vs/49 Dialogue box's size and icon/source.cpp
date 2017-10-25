#include "afxwin.h" 
#include "afxinet.h"	// ������� ������ � �������� ��� ���������.
#include "resource.h" // ������ �� �������
#include "afxdlgs.h" // ��� ����������� ���� ������

#pragma comment(lib, "shell32.lib") // ���������� LIB ����

#define IDM_MYMENU 102 // ������������� ������ ����.

class CTestDlg : public CDialog { // ����� ����������� ����
protected:
	CString m_edit; // �����
	CString m_newedit; // ������ ������
	DECLARE_MESSAGE_MAP(); // ������� ��������
public:
	CTestDlg(CWnd* pParent = NULL);
	virtual void DoDataExchange(CDataExchange* pDX); // ������� ������ ������� 
	void SetEditStr(CString  csEdit); // ���������� ������
	CString GetEditStr(); // �������� ������
	void OnSend(); //������� �������
	BOOL OnInitDialog(); // ������� ��������
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor); // ��������� �����
	CBrush my_color; // ���� �����
};

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnSend)
	ON_WM_CTLCOLOR() // ��������� �����
END_MESSAGE_MAP()

HBRUSH CTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) { return my_color; } // ������� ���� �����

BOOL CTestDlg::OnInitDialog() {
	CDialog::OnInitDialog(); // ����� ������
	CMenu* pSysMenu = GetSystemMenu(FALSE); // �������� ��������� ����
	if (pSysMenu != NULL) { // ���� ������� ��� ����
		pSysMenu->AppendMenu(MF_SEPARATOR); // �������� �����������
		pSysMenu->AppendMenu(MF_STRING, IDM_MYMENU, (LPCTSTR)"MyMenu"); // �������� ��� �����.
	}
	my_color.CreateSolidBrush(RGB(0, 255, 155));	// ������� �����
	return TRUE;
}

void CTestDlg::OnSend() {
	MoveWindow(100, 100, 300, 300, TRUE); // ����������� ����
	HICON newIcon = AfxGetApp()->LoadIcon(IDI_ICON1); // ��������� �����
	SetIcon(newIcon, TRUE); // ���������� �����
	SetWindowText(L"Move");	// �������� ���������
}

void CTestDlg::SetEditStr(CString  csEdit) {	m_edit = csEdit; }

CString CTestDlg::GetEditStr() { return m_edit;}

void CTestDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);	// ������� ��������
	DDX_Text(pDX, IDC_EDIT1, m_edit); // ��� �����
	DDX_Text(pDX, IDC_EDIT2, m_newedit); // ��� �����
	DDV_MaxChars(pDX, m_newedit, 2); // �������� ������
}

CTestDlg::CTestDlg(CWnd* pParent) : CDialog(IDD_DIALOG1, pParent) {}

class CTestApp : public CWinApp {
public:
	virtual BOOL InitInstance();
};

BOOL CTestApp::InitInstance() {
	CTestDlg dlg; // ������� ������ ����������� ����
	m_pMainWnd = &dlg; // ������� ���� ��������� ��� ���������� ����
	dlg.SetEditStr("Hello DDX"); // ���������� ������
	dlg.DoModal();
	TRACE(dlg.GetEditStr()); // �������� ������ � ������� � ���� �������
	return FALSE;
}

CTestApp theApp;
