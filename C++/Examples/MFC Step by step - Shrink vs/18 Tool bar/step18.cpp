#include "afxwin.h"						// MFC Основные и стандартные компоненты
#include "afxext.h"						// MFC Расширения
#include "resource.h"					// Идентификаторы ресурсов
#include "MyClip.h"						// описание нашего класса

#define IDC_MYBUTTON	100				// Идентификатор кнопки
#define IDC_MYEDIT		102				// Идентификатор поля редактирования
#define IDC_LIST1       103				// Идентификатор поля со списком

static UINT indicators[] = { IDS_STRING2, IDS_STRING1 }; // идентификатор второй строки в ресурсах // идентификатор первой строки в ресурсах

class CMyDialog : public CDialog {
public:
	CMyDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);	// конструктор
	~CMyDialog();											// деструктор
	virtual BOOL OnInitDialog();							// инициализация
	virtual void OnOK();									// реакция на нажатие OK
	CString GetString();									// получить строку
private:
	CListBox *cListBox;										// указатель на элемент управления
	CString csListTextItem;									// возвращаемое значение	
};

CMyDialog::~CMyDialog()
{
	if (cListBox !=  NULL) delete cListBox;					// если обьект был создан удалить
}

CString CMyDialog::GetString()
{
	return csListTextItem;									// вернуть результат
}

void CMyDialog::OnOK()										// когда нажмут кнопку OK
{
	if (cListBox->GetCurSel() ==  LB_ERR)						// если в списке нечего не выбано
    {
		//AfxMessageBox("Select Item List Box");				// сообщить о ошибке
	}
	else													// иначе то есть что то выбрано
	{
        cListBox->GetText(cListBox->GetCurSel(), csListTextItem); // получить результат
		CDialog::OnOK();										 // вызвать функцию предка	
    }
}


CMyDialog::CMyDialog(UINT nIDTemplate, CWnd* pParentWnd)
           :CDialog(nIDTemplate, pParentWnd)
{
	cListBox = NULL;								// Обьекта нет NULL
}


BOOL CMyDialog::OnInitDialog()
{
  CDialog::OnInitDialog();						// метод предка
  CenterWindow();								// по центру окна
  CRect rect(10, 10, 100, 100);					// координаты для списка
  cListBox = new CListBox();						// создать обьект спика
  cListBox->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP |LBS_NOTIFY | WS_VSCROLL   | WS_BORDER, rect, 
					this, IDC_LIST1);	
  if (cListBox !=  NULL)
  {
  //cListBox->AddString("God");					// добавить строку
  //cListBox->AddString("Bad");					// еще
  //cListBox->AddString("VOID");					// сказать что все удачно.
  return TRUE;
  }
  else return FALSE;							// несмогли создать список
}



class CMyPaintDC: public CPaintDC
{
public:
 CMyPaintDC(CWnd* pWnd);					// конструктор
 void DrawCross(int iPosX, int iPosY);		// функция рисования креста
};

CMyPaintDC::CMyPaintDC(CWnd* pWnd)
	       :CPaintDC(pWnd)					// мы дети CPainDC       
{
}

void CMyPaintDC::DrawCross(int iPosX, int iPosY)	// для создания своей фигуры используем
{													// функции CPaintDC
	MoveTo(iPosX-50, iPosY);
	LineTo(iPosX+50, iPosY);
	MoveTo(iPosX, iPosY-50);
	LineTo(iPosX, iPosY+50);
}

class CMyButton: public CButton 
{ 
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

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();							// Конструктор по умолчанию
	void OnCopyBuffer();				// копировать в буфер
	void OnOpen();						// эта функция вызовется при выборе меню Open
	afx_msg void OnLButtonDblClk(UINT, CPoint);          // виртуальная процедура ответа на левую кнопку
    afx_msg void OnRButtonDblClk(UINT, CPoint);          // виртуальная процедура ответа на правую кнопку
    afx_msg void OnKeyDown(UINT, UINT, UINT);            // виртуальная процедура ответа на клавишу
	int OnCreate(LPCREATESTRUCT lpCreateStruct);           // эта функция вызывается при создании окна
	void MenuExit();										// Процедура реакции на выбор пункта меню 
	void MenuSwitch();										// Процедура реакции на выбор пункта меню
	afx_msg void OnPaint();	            // Переопределяем функцию рисования в окне 
	afx_msg void OnMouseMove(UINT, CPoint cp);		// эта функция будет вызываться при движении мыши
	~CMainWnd();						// Деструктор 
private:    
	BOOL blMenu;					// какое меню активно
	CStatic* MyStatic;				// Указатель на объект надпись
    CMyButton* MyButton;			// Элемент управления кнопка
    CEdit* MyEdit;					// Указатель на объект поле редактирования
	CStatusBar m_wndStatusBar;		// класс панели состояния
	CMenu m_wndMenu;				// Это наш класс Меню
	CMyClip clip;					// Это класс буфера обмена
	CToolBar   my_ToolBar;		// Это наш класс панели инструментов 
	DECLARE_MESSAGE_MAP();			// таблица откликов
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd) // таблица откликов на сообщения 
	ON_WM_LBUTTONDBLCLK()     		       // реакция на нажатие левой кнопки мыши
	ON_WM_RBUTTONDBLCLK()     		       // реакция на нажатие правой кнопки мышки
	ON_WM_KEYDOWN()     			       // реакция на нажатие клавиши
	ON_WM_CREATE()						   // событие создания окна
	ON_WM_PAINT()						   // Это реакция. Если нету этой строчки , бог вам судья.
	ON_COMMAND(ID_OPEN, OnOpen)			   // Реакция на выбор меню Open
	ON_BN_CLICKED(IDC_MYBUTTON, OnCopyBuffer)	// нажали на кнопку левой кнопкой мыши
	ON_COMMAND(ID_FILE_EXIT, MenuExit)		   // Вот она , обработка реакции на выбор меню 
	ON_COMMAND(ID_FILE_SWITCH, MenuSwitch)		// Реакция на выбор пункта о переключении языка меню
	ON_WM_MOUSEMOVE()					   // мышь двигается
END_MESSAGE_MAP()

void CMainWnd::OnCopyBuffer()
{
 clip.CopyText("Hello My Text"); // копировать в буфер текст
}


void CMainWnd::OnOpen()
{
  //CFileDialog fileDialog(TRUE, NULL, "*.mak", NULL, "File Mak (*.mak)|*.mak|Resouce Files (*.res)|*.res|");
 //int result = fileDialog.DoModal();

	
}


void CMainWnd::MenuExit()  
{	
	DestroyWindow(); // Уничтожить окно   
}


void CMainWnd::OnPaint()
{
	CMyPaintDC dc(this);					// наш класс 
	CPen MyPen(PS_DASHDOT, 1, RGB(0, 255, 0));	// настравиваем перо
	dc.SelectObject(MyPen);					// выбираем перо
	for (int x = 1;x<400;x = x+50)
	{
          dc.DrawCross(100+x, 100+x);		// наша функция
	}
}

void CMainWnd::MenuSwitch()
{
	m_wndMenu.DestroyMenu();	// Уничтожаем старое
	switch (blMenu)
	{
	case TRUE:
		m_wndMenu.LoadMenu(IDR_MENU);	// Читаем новое
		break;
	case FALSE:
		m_wndMenu.LoadMenu(IDR_MENU_RUS);	// Читаем новое
		break;
	}
	blMenu = !blMenu;				// Меняет переменную
	SetMenu(&m_wndMenu);		// Устанавливаем меню
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CFrameWnd::OnCreate(lpCreateStruct) ==   -1)  return -1;
  m_wndStatusBar.Create(this); 
  m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)); // установить в строку идентификаторы
  m_wndMenu.LoadMenu(IDR_MENU); // Загрузить меню из файла ресурса
  SetMenu(&m_wndMenu); // Установить меню
  my_ToolBar.Create(this);						    // создать панель интструментов
  my_ToolBar.LoadToolBar(IDR_TOOLBAR1);					    // взять ее из ресурсов
  my_ToolBar.SetBarStyle(my_ToolBar.GetBarStyle()  | CBRS_SIZE_DYNAMIC);    // настроить стили
  my_ToolBar.EnableDocking(CBRS_ALIGN_ANY);				    // можно ли панели швартовка
  EnableDocking(CBRS_ALIGN_ANY);					    // функции окна для управления панелью
  DockControlBar(&my_ToolBar); 
  return 0;
}

void CMainWnd::OnKeyDown(UINT, UINT, UINT) 
{
    AfxMessageBox(clip.GetText());				// показать текст
}

void CMainWnd::OnRButtonDblClk(UINT, CPoint) 
{
    CDialog about(IDD_DIALOG1);		// создаем объект класса диалогового окна    
	//if (about.DoModal() ==  IDOK) AfxMessageBox("Ok");	// пользователь выбрал OK
 //   else AfxMessageBox("Cancel");						// пользователь выбрал Cansel
}

void CMainWnd::OnLButtonDblClk(UINT, CPoint) 
{
    CMyDialog about(IDD_DIALOG2);		// создать объект нашего класса
	if (about.DoModal() ==  IDOK)			// если пользователь выбрал OK 
	{
	 AfxMessageBox(about.GetString());	// показать результат 
	} 
}

void CMainWnd::OnMouseMove(UINT, CPoint cp) {
	char chX[10];				// буфер для координат
	char chY[10];				// буфер для координат
	_itoa_s(cp.x, chX, 10);			// число переводим в строку
	_itoa_s(cp.y, chY, 10);			// число переводим в строку
	CString  csStatusX(chX);		// Формируем строку
	CString  csStatusY(chY);		// Формируем строку
	m_wndStatusBar.SetPaneText(0, csStatusX);		// выводим  первую панель
	m_wndStatusBar.SetPaneText(1, csStatusY);		// выводим   вторую панель 
}

CMainWnd::CMainWnd() {
	blMenu = FALSE; // инициализация TRUE соответствует IDR_MENU
	Create(NULL, _T("Step18"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // Создать окно программы
	MyStatic = new CStatic();				
	if (MyStatic !=  NULL)  MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(10, 50, 100, 100), this); // создали 
	MyButton = new CMyButton(); // Меняем класс на основе которого создается объект
	if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 50, 220, 100), this, IDC_MYBUTTON); 
	MyEdit = new CEdit();
	if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 50, 340, 100), this, IDC_MYEDIT);
}

CMainWnd::~CMainWnd() {
	if (MyStatic !=  NULL)	delete MyStatic;	// удалить динамический объект
	if (MyButton !=  NULL)delete MyButton;		// удалить динамический объект
	if (MyEdit !=  NULL)delete MyEdit;			// удалить динамический объект
}


class CMyApp : public CWinApp {
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

