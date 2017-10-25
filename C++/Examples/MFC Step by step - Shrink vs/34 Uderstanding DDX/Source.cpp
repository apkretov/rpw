#include "afxwin.h"
#include "resource.h" 

class CTestDlg : public CDialog { 
protected:
   CString m_edit;
public:
   CTestDlg(CWnd* pParent = NULL) : CDialog(IDD_DIALOG, pParent) {};
	void SetEditStr(CString csEdit) { m_edit = csEdit; }; // ���������� ������
	CString GetEditStr() { return m_edit; }; // �������� ������
   
	virtual void DoDataExchange(CDataExchange* pDX)	{ // ������� ������ ������� //�������� �� ����� �������. �� �� ������ �������� ��� ������� ���������������, ����� � ���������� �� ������� UpdateDate. ��� ������� ���������� ��� �������� ����, �������� ����, �� �� ������ ������� � � ����� ������. @ http://www.firststeps.ru/mfc/steps/r.php?34
		CDialog::DoDataExchange(pDX); // ������� ��������
		DDX_Text(pDX, IDC_EDIT1, m_edit); // ��� �����
};	};

class CTestApp : public CWinApp {
public:
	virtual BOOL InitInstance() {
		CTestDlg dlg; // ������� ������ ����������� ����
		m_pMainWnd = &dlg; // ������� ���� ��������� ��� ���������� ����
		dlg.SetEditStr("Hello DDX"); // ���������� ������
		dlg.DoModal(); //
		TRACE(dlg.GetEditStr()); // �������� ������ � ������� � ���� �������
		return FALSE;
};	};

CTestApp theApp;
