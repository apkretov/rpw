#include "afxwin.h"	  // это для MFC
#include "resource.h" // идентификаторы ресурсов

class CMyDoc : public CDocument { // класс документа
protected: 
	CMyDoc() { csData = "Hello View - Doc"; }; // устанавливаем данные
	CString csData; // здесь будем хранить
	DECLARE_DYNCREATE(CMyDoc)		
public:
	CString GetData()	{ return csData; }; // получить данные // выдаем
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

class CMyView : public CView { // класс просмотр
protected: 
	CMyView() { };
	CMyDoc* GetDocument() { // получить документ
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));	// проверить есть ли класс документа
		return (CMyDoc*)m_pDocument; // вернуть результат.
	}
	DECLARE_DYNCREATE(CMyView)	// Эта функция вызывается для прорисовки вида	
public:
	void OnDraw(CDC* pDC) {
		CMyDoc* tempDoc = GetDocument(); //получить класс документа
		pDC->TextOut(10, 10, tempDoc->GetData()); //вывести строку на экран из документа
}	};
IMPLEMENT_DYNCREATE(CMyView, CView)

class CMainFrame : public CFrameWnd	{ // класс рамки окна	
protected:							
	CMainFrame() {	};					
	DECLARE_DYNCREATE(CMainFrame)	
public:
};
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

class CStep2App : public CWinApp { // класс приложения
public:
	CStep2App() { };					
	virtual BOOL InitInstance() {
		CSingleDocTemplate* pDocTemplate;	// новый шаблон
		pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*идентификатор меню*/, 	RUNTIME_CLASS(CMyDoc)/* документ	 ----|*/, RUNTIME_CLASS(CMainFrame) /* рамка окна ---| Документ вид однако.*/, RUNTIME_CLASS(CMyView)/* просмотр	 ----|*/);
		AddDocTemplate(pDocTemplate);		// добавить шаблон
		CCommandLineInfo cmdInfo;			// Класс команд 
		ParseCommandLine(cmdInfo);			// разбор командной строки			
		if (!ProcessShellCommand(cmdInfo)) return FALSE; // запуск команд на выполнение
		m_pMainWnd->ShowWindow(SW_SHOW);    // показать окно		
		m_pMainWnd->UpdateWindow();			// запустить цикл обработки сообщений	
		return TRUE;								
};	};

CStep2App theApp;
