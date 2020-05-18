#include "afxwin.h"
#include "resource.h" // ссылка на ресурсы

void AFXAPI DDX_MyText(CDataExchange* pDx, int ID, CString& Data) {
	if (pDx->m_bSaveAndValidate) { // Что происходит. Чтение или запись ?
		DDX_Text(pDx, ID, Data); //При сохранении мы вызываем функцию DDX_Text для получения данных и потом модифицируем... @ http://www.firststeps.ru/mfc/steps/r.php?37
		Data = Data + " Save DDX";
	} else {
		Data = Data + " Read DDX"; //... а при чтении наоборот - сначала изменяем, а потом вызываем DDX_Text. @ http://www.firststeps.ru/mfc/steps/r.php?37
		DDX_Text(pDx, ID, Data);
}	}

class CTestDlg : public CDialog { // класс диалогового окна
protected:
   CString m_edit; // данные
public:
   CTestDlg(CWnd* pParent = NULL) : CDialog(IDD_DIALOG, pParent) {};
   virtual void DoDataExchange(CDataExchange* pDX)	{ // функция обмена данными 
		CDialog::DoDataExchange(pDX); // функция родителя
		DDX_MyText(pDX, IDC_EDIT1, m_edit);	// наш обмен
	};
	void SetEditStr(CString csEdit) { m_edit = csEdit; } ; // установить строку
	CString GetEditStr() { return m_edit; }; // получить строку
};

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
