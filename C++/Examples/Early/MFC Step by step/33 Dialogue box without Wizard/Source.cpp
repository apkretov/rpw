#include "afxwin.h"
#include "resource.h" // ������ �� �������

class CTestDlg : public CDialog { // ����� ����������� ����
 public:
   CTestDlg(CWnd* pParent = NULL) : CDialog(IDD_DIALOG, pParent) {};
};

class CTestApp : public CWinApp {
public:
	virtual BOOL InitInstance() {
		CTestDlg dlg; // ������� ������ ����������� ����
		m_pMainWnd = &dlg; // ������� ���� ��������� ��� ���������� ����
		dlg.DoModal();
		return FALSE; //��� 33 - ���������� ���� ���������� ��� ���������� - 1) �� ��� ��������� �������� ������� FALSE, ��� �������� MFC ������, ��� ������������� �� �������. 2) ������� ������������� ��������. @ http://www.firststeps.ru/mfc/steps/r.php?33
};	};

CTestApp theApp;
