#include "stdafx.h"
#include "Dia.h"
#include "DiaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDiaDlg::CDiaDlg(CWnd* pParent /* = NULL*/) : CDialogEx(IDD_DIA_DIALOG, pParent) {	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); }

void CDiaDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CDiaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDSAVE, &CDiaDlg::OnBnClickedSave)
END_MESSAGE_MAP()

BOOL CDiaDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);	// Set the icon for this dialog. The framework does this automatically when the application's main window is not a dialog // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon
	m_List.AddString(_T("Hello")); // Заносим наши данные
	m_List.AddString(_T("App"));
	m_List.AddString(_T("Wizard"));
	return TRUE; // return TRUE  unless you set the focus to a control
}

void CDiaDlg::OnPaint() {
	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON); // Center icon in client rectangle
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon); // Draw the icon
	}
	else CDialogEx::OnPaint();
}

HCURSOR CDiaDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); } // The system calls this function to obtain the cursor to display while the user drags the minimized window.
void CDiaDlg::OnBnClickedSave() { AfxMessageBox(_T("Save")); }
