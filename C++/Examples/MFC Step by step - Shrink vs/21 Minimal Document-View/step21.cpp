#include "afxwin.h"	  // это дл€ MFC
#include "resource.h" // идентификаторы ресурсов

class CMyDoc : public CDocument { // класс документа
protected: 
	CMyDoc() { };						
	DECLARE_DYNCREATE(CMyDoc)		
public:
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

class CMyView : public CView { // класс просмотр
protected: 
	CMyView() { };
	DECLARE_DYNCREATE(CMyView)	// Ёта функци€ вызываетс€ дл€ прорисовки вида	
public:
	virtual void OnDraw(CDC* pDC) { };
};
IMPLEMENT_DYNCREATE(CMyView, CView)

class CMainFrame : public CFrameWnd	{ // класс рамки окна	
protected:							
	CMainFrame() {	};					
	DECLARE_DYNCREATE(CMainFrame)	
public:
};
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

class CStep2App : public CWinApp { // класс приложени€
public:
	CStep2App() { };					
	virtual BOOL InitInstance() {
		CSingleDocTemplate* pDocTemplate;	// новый шаблон
		pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*идентификатор меню*/, 	RUNTIME_CLASS(CMyDoc)/* документ	 ----|*/, RUNTIME_CLASS(CMainFrame) /* рамка окна ---| ƒокумент вид однако.*/, RUNTIME_CLASS(CMyView)/* просмотр	 ----|*/);
		AddDocTemplate(pDocTemplate);		// добавить шаблон
		CCommandLineInfo cmdInfo;			//  ласс команд 
		ParseCommandLine(cmdInfo);			// разбор командной строки			
		if (!ProcessShellCommand(cmdInfo)) return FALSE; // запуск команд на выполнение
		m_pMainWnd->ShowWindow(SW_SHOW);    // показать окно		
		m_pMainWnd->UpdateWindow();			// запустить цикл обработки сообщений	
		return TRUE;								
};	};

CStep2App theApp;
