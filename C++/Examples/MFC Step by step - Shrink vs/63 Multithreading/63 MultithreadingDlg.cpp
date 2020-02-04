#include "stdafx.h"
#include "63 Multithreading.h"
#include "63 MultithreadingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMy63MultithreadingDlg::CMy63MultithreadingDlg(CWnd* pParent /* = NULL*/)	: CDialogEx(IDD_MY63MULTITHREADING_DIALOG, pParent) {	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); }
void CMy63MultithreadingDlg::DoDataExchange(CDataExchange* pDX) {	CDialogEx::DoDataExchange(pDX); }

BEGIN_MESSAGE_MAP(CMy63MultithreadingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy63MultithreadingDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CMy63MultithreadingDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model, 
//  this is automatically done for you by the framework.

void CMy63MultithreadingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CMy63MultithreadingDlg::OnQueryDragIcon() { return static_cast<HCURSOR>(m_hIcon); }

UINT proc1(LPVOID Param){
	for (int x = 1; x < 30; x++) Sleep(100); // задержка
   AfxMessageBox(L"proc1");	
	return 0;
}

UINT proc2(LPVOID Param) {
	for (int x = 1; x < 30; x++) Sleep(100); // задержка
	AfxMessageBox(L"proc2");
	return 0;
}

void CMy63MultithreadingDlg::OnBnClickedButton1() {
	AfxBeginThread(proc1, this);	 // Первый поток
	AfxBeginThread(proc2, this);	 // Второй поток
	AfxMessageBox(L"Thread");      // И основной поток
}
