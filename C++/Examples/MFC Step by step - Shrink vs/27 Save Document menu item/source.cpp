#include "afxwin.h" // это для MFC
#include "afxext.h" // это для дополнительных возможностей
#include "resource.h" // идентификаторы ресурсов

class CMyDoc : public CDocument { // класс документа
protected: 
	CMyDoc() { TRACE("CMyDoc::CMyDoc()\n"); }; // вывести в окно отладки
	CString csData; // здесь будем хранить
	virtual BOOL OnNewDocument() { // будет вызываться при выборе меню New
		if (!CDocument::OnNewDocument()) return FALSE; // Если не удалось создать документ // Вернуть ошибку
		csData = "Hello View - Doc"; // Изменить данные в документе
		return TRUE;
	};
	virtual void Serialize(CArchive& ar) { // сохранение востановление файлов
		if (ar.IsStoring()) ar << csData; // если сохранение	// записываем
		else ; //для чтения
};	
	DECLARE_DYNCREATE(CMyDoc)		
public:
	CString GetData()	{ return csData; }; // получить данные // выдаем
	void OnAbout() {
		SetString(_T("Первые шаги (с)")); // установить строку
		UpdateAllViews(NULL); // обновить виды
	}
	void SetString(CString s) { csData = s; } // установить данные внутри документа
private:
	DECLARE_MESSAGE_MAP(); // таблица откликов
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
BEGIN_MESSAGE_MAP(CMyDoc, CDocument) 
	ON_COMMAND(ID_ABOUT, OnAbout)	//  при выборе меню
END_MESSAGE_MAP()	

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
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) { // создать клиента
		ASSERT(m_wndSplitter.CreateStatic(this, 1, 2)); // создать разделитель
		ASSERT(m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyView), CSize(100, 50), pContext)); // создать первый вид
		ASSERT(m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CNewView), CSize(100, 50), pContext)); // создать второй вид
		SetActiveView((CView*)m_wndSplitter.GetPane(0, 1)); // установить активную панель
		return TRUE;
	}
	CSplitterWnd m_wndSplitter; // разделитель
};
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

class CStep2App : public CWinApp { // класс приложения
	DECLARE_MESSAGE_MAP() // таблица откликов для класса приложения
public:
	CStep2App() { };					
	virtual BOOL InitInstance() {
		CSingleDocTemplate* pDocTemplate; // новый шаблон
		pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*идентификатор меню*/, 	RUNTIME_CLASS(CMyDoc)/* документ	 ----|*/, RUNTIME_CLASS(CMainFrame) /* рамка окна ---| Документ вид однако.*/, RUNTIME_CLASS(CMyView)/* просмотр	 ----|*/); //
		AddDocTemplate(pDocTemplate);		// добавить шаблон
		CCommandLineInfo cmdInfo;			// Класс команд 
		ParseCommandLine(cmdInfo);			// разбор командной строки			
		if (!ProcessShellCommand(cmdInfo)) return FALSE; // запуск команд на выполнение
		m_pMainWnd->ShowWindow(SW_SHOW);    // показать окно		
		m_pMainWnd->UpdateWindow();			// запустить цикл обработки сообщений	
		return TRUE;								
	};
};
BEGIN_MESSAGE_MAP(CStep2App, CWinApp) 
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew) // пункт меню New	
END_MESSAGE_MAP() 

CStep2App theApp;
