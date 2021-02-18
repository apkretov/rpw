#include "afxwin.h" 
#include "resource.h"		// ссылка на ресурсы
#include "afxcmn.h"			// это для элемента управления

#pragma comment(lib, "shell32.lib") // подключили LIB файл

#define IDM_MYMENU	102		// идентификатор нашего меню.

class CTestDlg : public CDialog	// класс диалогового окна
{
 public:
   CTestDlg(CWnd* pParent = NULL);
   virtual void DoDataExchange(CDataExchange* pDX);		// функция обмена данными 
   void SetEditStr(CString  csEdit);					// установить строку
   CString GetEditStr();								// получить строку
   void OnSend();										// функция реакции
   BOOL OnInitDialog();									// функция настроки
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	// получение кисти
   CBrush my_color;														// сама кисть
	CSliderCtrl  csSlider;	// класс элемента управления
 protected:
   CString m_edit;   // даные
   CString m_newedit;	// вторая строка
   DECLARE_MESSAGE_MAP();		// таблица откликов
};


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnSend)
	ON_WM_CTLCOLOR()					// требуется кисть
END_MESSAGE_MAP()


HBRUSH CTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return my_color;		// вернуть нашу кисть
}

BOOL CTestDlg::OnInitDialog()
{	
	CDialog::OnInitDialog();	// метод предка
	CMenu* pSysMenu = GetSystemMenu(FALSE);		// получить системное меню
	if (pSysMenu !=  NULL)						// если удалось все таки
	{
    pSysMenu->AppendMenu(MF_SEPARATOR);			// добавить разделитель
	pSysMenu->AppendMenu(MF_STRING, IDM_MYMENU, (LPCTSTR)"MyMenu");	// добавить наш пункт.
	}	
	my_color.CreateSolidBrush(RGB(0, 255, 155));	// создать кисть
	csSlider.SetRangeMin(0, TRUE);			// минимум
	csSlider.SetRangeMax(10, TRUE);	    		// максимум
	return TRUE;
}

void CTestDlg::OnSend() {	
    int i = csSlider.GetPos();	// получить позицию
    char csPos[10];		// буфер для результата			
    _itoa_s(i, csPos, 10);		// перевести в строку
    AfxMessageBox((LPCTSTR)csPos);	// показать результат
}


void CTestDlg::SetEditStr(CString  csEdit)
{
	m_edit = csEdit;
}

CString CTestDlg::GetEditStr()
{
	return m_edit;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);			// функция родителя
	DDX_Text(pDX, IDC_EDIT1, m_edit);		// наш обмен
	DDX_Text(pDX, IDC_EDIT2, m_newedit);	// наш обмен
	DDV_MaxChars(pDX, m_newedit, 2);		// проверка данных
	DDX_Control(pDX, IDC_SLIDER1, csSlider);  // наш обмен
}

CTestDlg::CTestDlg(CWnd* pParent)
	: CDialog(IDD_DIALOG1, pParent)
{
}

class CTestApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL CTestApp::InitInstance() {
	CTestDlg dlg;						// Создать объект диалогового окна
	m_pMainWnd = &dlg;					// главное окно программы это диалоговое окно
	dlg.SetEditStr("Hello DDX");		// установить данные
    dlg.DoModal();
	TRACE(dlg.GetEditStr());	// получить данные и вывести в окно отладки
	return FALSE;
}

CTestApp theApp;
