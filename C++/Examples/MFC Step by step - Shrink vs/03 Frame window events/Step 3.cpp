#include "afxwin.h"
#define IDC_MYBUTTON 100	// Идентификатор кнопки
#define IDC_MYEDIT 102	// Идентификатор поля редактирования

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;
	CButton* MyButton;
	CEdit* MyEdit;
	DECLARE_MESSAGE_MAP(); // таблица откликов
public:
	CMainWnd();
	~CMainWnd(); // деструктор
	afx_msg void OnKeyDown(UINT, UINT, UINT) { AfxMessageBox(_T(" Key Button Down ")); } //afx_msg воспринимайте как аналог virtual. @ http://www.firststeps.ru/mfc/steps/r.php?3
	afx_msg void OnRButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Rigth Button Click ")); }
	afx_msg void OnLButtonDblClk(UINT, CPoint) { AfxMessageBox(_T(" Left Button Click ")); }
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)	// таблица откликов на сообщения //Говорит о том, что данный класс будет реагировать на события. @ http://www.firststeps.ru/mfc/steps/r.php?3
	ON_WM_KEYDOWN()				// реакция на нажатие клавиши
	ON_WM_LBUTTONDBLCLK()		// реакция на нажатие левой кнопки мыши
	ON_WM_RBUTTONDBLCLK()		// реакция на нажатие правой кнопки мышки
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	Create(NULL, _T("Step3"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);// Создать окно программы
	MyStatic = new CStatic(); // оператор new по умолчанию в случае ошибки вернет NULL проверка указателя на NULL дает возможность избавиться от дальнейших ошибок
	if (MyStatic !=  NULL) MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(10, 10, 100, 50), this);	// создали
	MyButton = new CButton();
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON);
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd() {
	if (MyStatic !=  NULL) delete MyStatic;	// удалить динамический объект
	if (MyButton !=  NULL) delete MyButton;	// удалить динамический объект
	if (MyEdit !=  NULL) delete MyEdit;	// удалить динамический объект
}

class CMyApp : public CWinApp {
public:
	CMyApp() {}; //конструктор по умолчанию
	virtual BOOL InitInstance() { //стандартная инициализация
		m_pMainWnd = new CMainWnd();	// создать класс окна
		ASSERT(m_pMainWnd);	// проверить его правильность
		m_pMainWnd->ShowWindow(SW_SHOW);// Показать окно
		m_pMainWnd->UpdateWindow();	// Обновить окно
		return TRUE;		// Вернуть что все нормально
	};
};

CMyApp theApp;	// запуск приложения