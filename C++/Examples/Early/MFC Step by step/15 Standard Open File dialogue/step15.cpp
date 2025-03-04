#include "afxwin.h"						// MFC Основные и стандартные компоненты
#include "afxext.h"						// MFC Расширения
#include "resource.h"
#define IDC_MYBUTTON	100				// Идентификатор кнопки
#define IDC_MYEDIT	102				// Идентификатор поля редактирования
#define IDC_LIST1		103				// Идентификатор поля со списком

class CMyButton: public CButton { 
   DECLARE_MESSAGE_MAP(); 			// таблица откликов кнопки 
public:
   afx_msg void OnLButtonDblClk(UINT, CPoint);
   afx_msg void OnRButtonDblClk(UINT, CPoint); 
};

void CMyButton::OnLButtonDblClk(UINT, CPoint) { MoveWindow(CRect(120, 100, 220, 150), TRUE); }
void CMyButton::OnRButtonDblClk(UINT, CPoint) { MoveWindow(CRect(120, 10, 220, 50), TRUE); }
 
BEGIN_MESSAGE_MAP(CMyButton, CButton)         // таблица откликов на сообщения 
	ON_WM_LBUTTONDBLCLK() 
	ON_WM_RBUTTONDBLCLK() 
END_MESSAGE_MAP()

class CMyPaintDC: public CPaintDC {
public:
	CMyPaintDC(CWnd* pWnd);						// конструктор
	void DrawCross(int iPosX, int iPosY);	// функция рисования креста
};

CMyPaintDC::CMyPaintDC(CWnd* pWnd) : CPaintDC(pWnd)	{ } // мы дети CPainDC

void CMyPaintDC::DrawCross(int iPosX, int iPosY) {	// для создания своей фигуры используем функции CPaintDC 
	MoveTo(iPosX-50, iPosY);
	LineTo(iPosX+50, iPosY);
	MoveTo(iPosX, iPosY-50);
	LineTo(iPosX, iPosY+50);
}

class CMyDialog : public CDialog {
	CListBox *cListBox;	// указатель на элемент управления
	CString csListTextItem;	// возвращаемое значение
public:
	CMyDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);	// конструктор
	~CMyDialog();	// деструктор
	virtual BOOL OnInitDialog();	// инициализация
	virtual void OnOK();	// реакция на нажатие OK
	CString GetString();	// получить строку
};

CMyDialog::CMyDialog(UINT nIDTemplate, CWnd* pParentWnd):CDialog(nIDTemplate, pParentWnd) { cListBox = NULL; } // Объекта нет, NULL
CMyDialog::~CMyDialog() { if (cListBox !=  NULL) delete cListBox;	} // если объект был создан удалить
CString CMyDialog::GetString() {	return csListTextItem; } // вернуть результат

void CMyDialog::OnOK() { // когда нажмут кнопку OK
	if (cListBox->GetCurSel() ==  LB_ERR)	AfxMessageBox(_T("Select Item List Box"));	// если в списке ничего не выбрано // сообщить о ошибке
	else { // иначе, то есть что-то выбрано
		cListBox->GetText(cListBox->GetCurSel(), csListTextItem); // получить результат
		CDialog::OnOK(); // вызвать функцию предка
}	}

BOOL CMyDialog::OnInitDialog() {
	CDialog::OnInitDialog(); // метод предка
	CenterWindow(); // по центру окна
	CRect rect(10, 10, 100, 100);	// координаты для списка
	cListBox = new CListBox(); // создать объект списка
	cListBox->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|LBS_NOTIFY|WS_VSCROLL|WS_BORDER, rect, this, IDC_LIST1); // и сам список связав его с идентификатором
	if (cListBox !=  NULL) {
		cListBox->AddString(_T("Good"));	// добавить строку
		cListBox->AddString(_T("Bad"));	// еще
		cListBox->AddString(_T("VOID"));	// еще
		return TRUE;	// сказать что все удачно.
	}
	else return FALSE;	// не смогли создать список
}

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;			// Указатель на объект надпись
	CMyButton* MyButton;			// Элемент управления кнопка
	CEdit* MyEdit;					// Указатель на объект поле редактирования
	CStatusBar m_wndStatusBar;	// класс панели состояния //Он включен статически. То есть при создании объекта окна, автоматически создается класс панели состояния, и он будет жить, пока живет объект рамки окна. Это и нужно. Хотя можно и динамически. @ http://www.firststeps.ru/mfc/steps/r.php?4
	CMenu m_wndMenu;				// Это наш класс Меню
	DECLARE_MESSAGE_MAP();		// таблица откликов
	BOOL blMenu;					// какое меню активно
public:
	CMainWnd();						// Конструктор по умолчанию
	~CMainWnd();					// Деструктор 
	afx_msg void OnLButtonDblClk(UINT, CPoint);	// виртуальная процедура ответа на левую кнопку
	afx_msg void OnRButtonDblClk(UINT, CPoint);	// виртуальная процедура ответа на правую кнопку
	afx_msg void OnKeyDown(UINT, UINT, UINT);		// виртуальная процедура ответа на клавишу
	int OnCreate(LPCREATESTRUCT lpCreateStruct);	// эта функция вызывается при создании окна
	void MenuExit();										// Процедура реакции на выбор пункта меню 
	void MenuSwitch();									// Процедура реакции на выбор пункта меню 
	afx_msg void OnPaint();								// Переопределяем функцию рисования в окне
	void OnOpen();											// эта функция вызовется при выборе меню Open
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)		// таблица откликов на сообщения 
	ON_WM_LBUTTONDBLCLK()     					// реакция на нажатие левой кнопки мыши
	ON_WM_RBUTTONDBLCLK()     					// реакция на нажатие правой кнопки мышки
	ON_WM_KEYDOWN()     							// реакция на нажатие клавиши
	ON_WM_CREATE()									// событие создания окна
	ON_COMMAND(ID_FILE_EXIT, MenuExit)		// Вот она , обработка реакции на выбор меню
	ON_COMMAND(ID_FILE_SWITCH, MenuSwitch)	// Реакция на выбор пункта о переключении языка меню
	ON_WM_PAINT()									// Это реакция. Если нету этой строчки, бог вам судья.
	ON_COMMAND(ID_OPEN, OnOpen)				// Реакция на выбор меню Open
END_MESSAGE_MAP()

CMainWnd::CMainWnd() {
	blMenu = FALSE;	// инициализация TRUE соответствует IDR_MENU
	Create(NULL, _T("Step15"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // Создать окно программы
	MyStatic = new CStatic();				
	if (MyStatic !=  NULL)  MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, 	CRect(10, 10, 100, 50), this); // создали 
	MyButton = new CMyButton(); // Меняем класс на основе которого создается объект
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON); 
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd() {
	if (MyStatic !=  NULL) delete MyStatic;	// удалить динамический объект
	if (MyButton !=  NULL) delete MyButton;	// удалить динамический объект
	if (MyEdit !=  NULL) delete MyEdit;			// удалить динамический объект
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CFrameWnd::OnCreate(lpCreateStruct) ==   -1)  return -1;
	m_wndStatusBar.Create(this); 
	m_wndMenu.LoadMenu(IDR_MENU);	// Загрузить меню из файла ресурса
	SetMenu(&m_wndMenu);	// Установить меню
	return 0;
}

void CMainWnd::OnKeyDown(UINT, UINT, UINT) { AfxMessageBox(_T(" Key Button Down ")); }

void CMainWnd::OnRButtonDblClk(UINT, CPoint) {
	CDialog about(IDD_DIALOG1);	// создаем объект класса диалогового окна
	if (about.DoModal() ==  IDOK)
		AfxMessageBox(_T("Ok"));	// пользователь выбрал OK
	else
		AfxMessageBox(_T("Cancel"));	// пользователь выбрал Canсel
}

void CMainWnd::OnLButtonDblClk(UINT, CPoint) { 
	CMyDialog about(IDD_DIALOG2);	// создать объект нашего класса
	if (about.DoModal() ==  IDOK)	AfxMessageBox(about.GetString()); // если пользователь выбрал OK // показать результат
}
void CMainWnd::MenuExit() { DestroyWindow(); } // Уничтожить окно 

void CMainWnd::MenuSwitch() {
	m_wndMenu.DestroyMenu(); // Уничтожаем старое
	switch (blMenu) {
		case TRUE: m_wndMenu.LoadMenu(IDR_MENU); break; // Читаем новое
		case FALSE: m_wndMenu.LoadMenu(IDR_MENU_RUS); break; // Читаем новое
	}
	blMenu = !blMenu; // Меняет переменную
	SetMenu(&m_wndMenu);	// Устанавливаем меню
}

void CMainWnd::OnPaint() {
	CMyPaintDC dc(this);	// наш класс 
	CPen MyPen(PS_DASHDOT, 1, RGB(0, 255, 0));	// настраиваем перо
	dc.SelectObject(MyPen);	// выбираем перо
	for (int x = 1;x<400;x = x+50)	dc.DrawCross(100+x, 100+x);	// наша функция
}

void CMainWnd::OnOpen() {
	CFileDialog fileDialog(TRUE, NULL, _T("*.cpp"));	//объект класса выбора файла
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result ==  IDOK) AfxMessageBox(fileDialog.GetPathName()); //если файл выбран // показать полный путь
}

class CMyApp : public CWinApp {
public:
	CMyApp();								// конструктор по умолчанию
	virtual BOOL InitInstance();		// стандартная инициализация
};

CMyApp::CMyApp() {}						// конструктор главного класса приложения

BOOL CMyApp::InitInstance() {			// стандартная инициализация
	m_pMainWnd = new CMainWnd();			// создать класс окна
	ASSERT(m_pMainWnd);					// проверить его правильность
	m_pMainWnd->ShowWindow(SW_SHOW);	// Показать окно
	m_pMainWnd->UpdateWindow();		// Обновить окно
	return TRUE;							// Вернуть что все нормально 
};

CMyApp theApp;								// запуск приложения
