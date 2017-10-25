#include "afxwin.h"
#include "resource.h" // ������ �� �������

void AFXAPI DDX_MyText(CDataExchange* pDx, int ID, CString& Data) {
	if (pDx->m_bSaveAndValidate) { // ��� ����������. ������ ��� ������ ?
		DDX_Text(pDx, ID, Data); //��� ���������� �� �������� ������� DDX_Text ��� ��������� ������ � ����� ������������... @ http://www.firststeps.ru/mfc/steps/r.php?37
		Data = Data + " Save DDX";
	} else {
		Data = Data + " Read DDX"; //... � ��� ������ �������� - ������� ��������, � ����� �������� DDX_Text. @ http://www.firststeps.ru/mfc/steps/r.php?37
		DDX_Text(pDx, ID, Data);
}	}

class CTestDlg : public CDialog { // ����� ����������� ����
protected:
   CString m_edit; // ������
public:
   CTestDlg(CWnd* pParent = NULL) : CDialog(IDD_DIALOG, pParent) {};
   virtual void DoDataExchange(CDataExchange* pDX)	{ // ������� ������ ������� 
		CDialog::DoDataExchange(pDX); // ������� ��������
		DDX_MyText(pDX, IDC_EDIT1, m_edit);	// ��� �����
	};
	void SetEditStr(CString csEdit) { m_edit = csEdit; } ; // ���������� ������
	CString GetEditStr() { return m_edit; }; // �������� ������
};

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
