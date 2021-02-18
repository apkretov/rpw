#include "afxwin.h"
#include "resource.h" // ссылка на ресурсы

class CTestDlg : public CDialog { // класс диалогового окна
 public:
   CTestDlg(CWnd* pParent = NULL) : CDialog(IDD_DIALOG, pParent) {};
};

class CTestApp : public CWinApp {
public:
	virtual BOOL InitInstance() {
		CTestDlg dlg; // Создать объект диалогового окна
		m_pMainWnd = &dlg; // главное окно программы это диалоговое окно
		dlg.DoModal();
		return FALSE; //Шаг 33 - Диалоговое окно приложения без волшебника - 1) Но вот результат возврата функции FALSE, чем обманули MFC сказав, что инициализация не удалась. 2) Заверши инициализацию неудачей. @ http://www.firststeps.ru/mfc/steps/r.php?33
};	};

CTestApp theApp;
