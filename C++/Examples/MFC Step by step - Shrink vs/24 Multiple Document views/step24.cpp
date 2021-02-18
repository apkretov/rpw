#include "afxwin.h" // это для MFC
#include "afxext.h" // это для дополнительных возможностей
#include "resource.h" // идентификаторы ресурсов

class CMyDoc : public CDocument { // класс документа
private:
	DECLARE_MESSAGE_MAP(); // таблица откликов
protected: 
	CMyDoc() { csData = "Hello View - Doc"; }; // устанавливаем данные
	CString csData; // здесь будем хранить
	DECLARE_DYNCREATE(CMyDoc)		
public:
	CString GetData()	{ return csData; }; // получить данные // выдаем
	void OnAbout() {
		SetString(_T("Первые шаги (с)")); // установить строку
		UpdateAllViews(NULL); // обновить виды
	}
	void SetString(CString s) { csData = s; } // установить данные внутри документа
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
BEGIN_MESSAGE_MAP(CMyDoc, CDocument) 
	ON_COMMAND(ID_ABOUT, OnAbout)	
END_MESSAGE_MAP()	//  при выборе меню

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

class CNewView : public CView	{ // еще один класс вида
protected: 
	CNewView() { };
	DECLARE_DYNCREATE(CNewView)
public:
	CMyDoc* GetDocument() {
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
		return (CMyDoc*)m_pDocument;
	}	
	void OnDraw(CDC* pDC) {
		CMyDoc* tempDoc = GetDocument();
		pDC->SetTextColor(RGB(255, 0, 0));	// установить красный цвет
		pDC->TextOut(10, 10, tempDoc->GetData()); // вывести
}	};
IMPLEMENT_DYNCREATE(CNewView, CView)

class CMainFrame : public CFrameWnd	{ // класс рамки окна	
protected:							
	CMainFrame() {	};					
	DECLARE_DYNCREATE(CMainFrame)	
public:
	CSplitterWnd m_wndSplitter; // разделитель
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) { // создать клиента
		ASSERT(m_wndSplitter.CreateStatic(this, 1, 2)); // создать разделитель
		//TEST ASSERT(m_wndSplitter.CreateStatic(this, 2, 2));
		ASSERT(m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyView), CSize(100, 50), pContext)); // создать первый вид
		ASSERT(m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CNewView), CSize(100, 50), pContext)); // создать второй вид
		//TEST ASSERT(m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyView), CSize(100, 50), pContext)); // создать первый вид
		//TEST ASSERT(m_wndSplitter.CreateView(1, 1, RUNTIME_CLASS(CNewView), CSize(100, 50), pContext)); // создать второй вид
		SetActiveView((CView*)m_wndSplitter.GetPane(0, 1)); // установить активную панель
		return TRUE;
}	};
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

class CStep2App : public CWinApp { // класс приложения
public:
	CStep2App() { };					
	virtual BOOL InitInstance() {
		CSingleDocTemplate* pDocTemplate;	// новый шаблон
		pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*идентификатор меню*/, 	RUNTIME_CLASS(CMyDoc)/* документ	 ----|*/, RUNTIME_CLASS(CMainFrame) /* рамка окна ---| Документ вид однако.*/, RUNTIME_CLASS(CMyView)/* просмотр	 ----|*/); //
		//TEST pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*идентификатор меню*/, 	RUNTIME_CLASS(CMyDoc)/* документ	 ----|*/, RUNTIME_CLASS(CMainFrame) /* рамка окна ---| Документ вид однако.*/, RUNTIME_CLASS(CNewView)/* просмотр	 ----|*/);
		AddDocTemplate(pDocTemplate);		// добавить шаблон
		CCommandLineInfo cmdInfo;			// Класс команд 
		ParseCommandLine(cmdInfo);			// разбор командной строки			
		if (!ProcessShellCommand(cmdInfo)) return FALSE; // запуск команд на выполнение
		m_pMainWnd->ShowWindow(SW_SHOW);    // показать окно		
		m_pMainWnd->UpdateWindow();			// запустить цикл обработки сообщений	
		return TRUE;								
	};
};

CStep2App theApp;
