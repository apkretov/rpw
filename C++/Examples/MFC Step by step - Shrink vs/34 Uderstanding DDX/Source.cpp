#include "afxwin.h"
#include "resource.h" 

class CTestDlg : public CDialog { 
protected:
   CString m_edit;
public:
   CTestDlg(CWnd* pParent = NULL) : CDialog(IDD_DIALOG, pParent) {};
	void SetEditStr(CString csEdit) { m_edit = csEdit; }; // установить строку
	CString GetEditStr() { return m_edit; }; // получить строку
   
	virtual void DoDataExchange(CDataExchange* pDX)	{ // функция обмена данными //отвечает за обмен данными. Вы не должны вызывать эту функцию непосредственно, вызов её происходит из функции UpdateDate. Эта функция вызывается при создании окна, закрытия окна, но вы можете вызвать её в любой момент. @ http://www.firststeps.ru/mfc/steps/r.php?34
		CDialog::DoDataExchange(pDX); // функция родителя
		DDX_Text(pDX, IDC_EDIT1, m_edit); // наш обмен
};	};

class CTestApp : public CWinApp {
public:
	virtual BOOL InitInstance() {
		CTestDlg dlg; // Создать объект диалогового окна
		m_pMainWnd = &dlg; // главное окно программы это диалоговое окно
		dlg.SetEditStr("Hello DDX"); // установить данные
		dlg.DoModal(); //
		TRACE(dlg.GetEditStr()); // получить данные и вывести в окно отладки
		return FALSE;
};	};

CTestApp theApp;
