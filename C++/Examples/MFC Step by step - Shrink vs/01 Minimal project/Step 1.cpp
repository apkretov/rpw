#include "afxwin.h" //	Step1.cpp //Сайт Первые шаги (http://www.firststeps.ru/) Каев Артем (1999-2001) создано 1999 г.	обновление 24.06.2001 // MFC Основные и стандартные компоненты

class CMainWnd : public CFrameWnd {
public:
	CMainWnd() { Create(NULL, _T("Step1"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL); } // Создать окно программы;	// Конструктор по умолчанию
};

class CMyApp : public CWinApp {
public:
	CMyApp() {}; //конструктор по умолчанию
	virtual BOOL InitInstance() { //стандартная инициализация
		m_pMainWnd = new CMainWnd();	// создать класс окна
		ASSERT(m_pMainWnd);	// проверить его правильность
		m_pMainWnd->ShowWindow(SW_SHOW);// Показать окно
		m_pMainWnd->UpdateWindow();	// Обновить окно
		//TEST m_pMainWnd = nullptr; //Если по окончанию InitInstance() он будет равен нулю, то приложение завершится. И естественно, когда приложение завершается он обнуляется. @ http://www.firststeps.ru/mfc/steps/r.php?1
		return TRUE;		// Вернуть что все нормально
		//TEST return 0;
	};
};

CMyApp theApp;	// запуск приложения