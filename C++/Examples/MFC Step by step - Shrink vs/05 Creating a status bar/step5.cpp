#include "afxwin.h"						// MFC Основные и стандартные компоненты
#include "afxext.h"						// MFC Расширения
#define IDC_MYBUTTON	100				// Идентификатор кнопки
#define IDC_MYEDIT	102				// Идентификатор поля редактирования

class CMyButton: public CButton { 
public:
   afx_msg void OnLButtonDblClk(UINT, CPoint);
   afx_msg void OnRButtonDblClk(UINT, CPoint); 
private:
   DECLARE_MESSAGE_MAP(); 			// таблица откликов кнопки 
};

void CMyButton::OnLButtonDblClk(UINT, CPoint) 
{
   MoveWindow(CRect(120, 100, 220, 150), TRUE); 
}

void CMyButton::OnRButtonDblClk(UINT, CPoint) 
{
   MoveWindow(CRect(120, 10, 220, 50), TRUE); 
}
 
BEGIN_MESSAGE_MAP(CMyButton, CButton)         // таблица откликов на сообщения 
 ON_WM_LBUTTONDBLCLK() 
 ON_WM_RBUTTONDBLCLK() 
END_MESSAGE_MAP()

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;				// Указатель на объект надпись
	CMyButton* MyButton;			// Элемент управления кнопка
	CEdit* MyEdit;					// Указатель на объект поле редактирования
	CStatusBar m_wndStatusBar;		// класс панели состояния //Он включен статически. То есть при создании объекта окна, автоматически создается класс панели состояния, и он будет жить, пока живет объект рамки окна. Это и нужно. Хотя можно и динамически. @ http://www.firststeps.ru/mfc/steps/r.php?4
	DECLARE_MESSAGE_MAP();			// таблица откликов
public:
	CMainWnd();							// Конструктор по умолчанию
	afx_msg void OnLButtonDblClk(UINT, CPoint);          // виртуальная процедура ответа на левую кнопку
	afx_msg void OnRButtonDblClk(UINT, CPoint);          // виртуальная процедура ответа на правую кнопку
	afx_msg void OnKeyDown(UINT, UINT, UINT);            // виртуальная процедура ответа на клавишу
	int OnCreate(LPCREATESTRUCT lpCreateStruct);           // эта функция вызывается при создании окна
	~CMainWnd();						// Деструктор 
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd) // таблица откликов на сообщения 
	ON_WM_LBUTTONDBLCLK()     		       // реакция на нажатие левой кнопки мыши
	ON_WM_RBUTTONDBLCLK()     		       // реакция на нажатие правой кнопки мышки
	ON_WM_KEYDOWN()     			       // реакция на нажатие клавиши
	ON_WM_CREATE()						   // событие создания окна
END_MESSAGE_MAP()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) ==   -1)  return -1;
	m_wndStatusBar.Create(this); 
	return 0;
}

void CMainWnd::OnKeyDown(UINT, UINT, UINT) { AfxMessageBox(_T(" Key Button Down ")); }
void CMainWnd::OnRButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Rigth Button Click ")); }
void CMainWnd::OnLButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Left Button Click ")); }

CMainWnd::CMainWnd() {
	Create(NULL, _T("Step5"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);						// Создать окно программы
	MyStatic = new CStatic();				
	if (MyStatic !=  NULL)  MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, 	CRect(10, 10, 100, 50), this);			// создали 
	MyButton = new CMyButton();       // Меняем класс на основе которого создается объект
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON); 
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd()
{
	if (MyStatic !=  NULL)	delete MyStatic;	// удалить динамический объект
    if (MyButton !=  NULL)delete MyButton;		// удалить динамический объект
    if (MyEdit !=  NULL)delete MyEdit;			// удалить динамический объект
}

class CMyApp : public CWinApp
{

public:
	CMyApp();							// конструктор по умолчанию
	virtual BOOL InitInstance();		// стандартная инициализация
};

CMyApp::CMyApp()						// конструктор главного класса приложения
{}

BOOL CMyApp::InitInstance()				// стандартная инициализация
{ 
	m_pMainWnd = new CMainWnd();			// создать класс окна
	ASSERT(m_pMainWnd);					// проверить его правильность
	m_pMainWnd->ShowWindow(SW_SHOW);	// Показать окно
	m_pMainWnd->UpdateWindow();			// Обновить окно
	return TRUE;						// Вернуть что все нормально 
};

CMyApp theApp;							// запуск приложения

