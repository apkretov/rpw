#include "afxwin.h"
#define IDC_MYBUTTON 100	// Идентификатор кнопки
#define IDC_MYEDIT 102	// Идентификатор поля редактирования

class CMainWnd : public CFrameWnd {
	CStatic* MyStatic;	// Указатель на объект надпись
	CButton* MyButton;	// Указатель на объект кнопка
	CEdit* MyEdit;	// Указатель на объект поле редактирования
public:
	CMainWnd() { // Конструктор по умолчанию
		Create(NULL, _T("Step2"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); // Создать окно программы
		MyStatic = new CStatic(); // оператор new по умолчанию в случае ошибки вернет NULL проверка указателя на NULL дает возможность избавиться от дальнейших ошибок
		if (MyStatic !=  NULL) MyStatic->Create(_T("MyStatic"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(10, 10, 100, 50), this);	// создали
		MyButton = new CButton();
		if (MyButton !=  NULL) MyButton->Create(_T("MyButton"), WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120, 10, 220, 50), this, IDC_MYBUTTON);
		MyEdit = new CEdit();
		if (MyEdit !=  NULL) MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(240, 10, 340, 50), this, IDC_MYEDIT);
	}
	~CMainWnd() { // Деструктор
		if (MyStatic !=  NULL) delete MyStatic;	// удалить динамический объект
		if (MyButton !=  NULL) delete MyButton;	// удалить динамический объект
		if (MyEdit !=  NULL) delete MyEdit;	// удалить динамический объект
	}
};

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