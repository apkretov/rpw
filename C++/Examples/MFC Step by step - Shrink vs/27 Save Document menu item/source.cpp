#include "afxwin.h" // ��� ��� MFC
#include "afxext.h" // ��� ��� �������������� ������������
#include "resource.h" // �������������� ��������

class CMyDoc : public CDocument { // ����� ���������
protected: 
	CMyDoc() { TRACE("CMyDoc::CMyDoc()\n"); }; // ������� � ���� �������
	CString csData; // ����� ����� �������
	virtual BOOL OnNewDocument() { // ����� ���������� ��� ������ ���� New
		if (!CDocument::OnNewDocument()) return FALSE; // ���� �� ������� ������� �������� // ������� ������
		csData = "Hello View - Doc"; // �������� ������ � ���������
		return TRUE;
	};
	virtual void Serialize(CArchive& ar) { // ���������� ������������� ������
		if (ar.IsStoring()) ar << csData; // ���� ����������	// ����������
		else ; //��� ������
};	
	DECLARE_DYNCREATE(CMyDoc)		
public:
	CString GetData()	{ return csData; }; // �������� ������ // ������
	void OnAbout() {
		SetString(_T("������ ���� (�)")); // ���������� ������
		UpdateAllViews(NULL); // �������� ����
	}
	void SetString(CString s) { csData = s; } // ���������� ������ ������ ���������
private:
	DECLARE_MESSAGE_MAP(); // ������� ��������
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
BEGIN_MESSAGE_MAP(CMyDoc, CDocument) 
	ON_COMMAND(ID_ABOUT, OnAbout)	//  ��� ������ ����
END_MESSAGE_MAP()	

class CMyView : public CView { // ����� ��������
protected: 
	CMyView() { };
	CMyDoc* GetDocument() { // �������� ��������
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));	// ��������� ���� �� ����� ���������
		return (CMyDoc*)m_pDocument; // ������� ���������.
	}
	DECLARE_DYNCREATE(CMyView)	// ��� ������� ���������� ��� ���������� ����	
public:
	void OnDraw(CDC* pDC) {
		CMyDoc* tempDoc = GetDocument(); //�������� ����� ���������
		pDC->TextOut(10, 10, tempDoc->GetData()); //������� ������ �� ����� �� ���������
}	};
IMPLEMENT_DYNCREATE(CMyView, CView)

class CNewView : public CView	{ // ��� ���� ����� ����
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
		pDC->SetTextColor(RGB(255, 0, 0));	// ���������� ������� ����
		pDC->TextOut(10, 10, tempDoc->GetData()); // �������
}	};
IMPLEMENT_DYNCREATE(CNewView, CView)

class CMainFrame : public CFrameWnd	{ // ����� ����� ����	
protected:							
	CMainFrame() {	};					
	DECLARE_DYNCREATE(CMainFrame)	
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) { // ������� �������
		ASSERT(m_wndSplitter.CreateStatic(this, 1, 2)); // ������� �����������
		ASSERT(m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMyView), CSize(100, 50), pContext)); // ������� ������ ���
		ASSERT(m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CNewView), CSize(100, 50), pContext)); // ������� ������ ���
		SetActiveView((CView*)m_wndSplitter.GetPane(0, 1)); // ���������� �������� ������
		return TRUE;
	}
	CSplitterWnd m_wndSplitter; // �����������
};
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

class CStep2App : public CWinApp { // ����� ����������
	DECLARE_MESSAGE_MAP() // ������� �������� ��� ������ ����������
public:
	CStep2App() { };					
	virtual BOOL InitInstance() {
		CSingleDocTemplate* pDocTemplate; // ����� ������
		pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*������������� ����*/, 	RUNTIME_CLASS(CMyDoc)/* ��������	 ----|*/, RUNTIME_CLASS(CMainFrame) /* ����� ���� ---| �������� ��� ������.*/, RUNTIME_CLASS(CMyView)/* ��������	 ----|*/); //
		AddDocTemplate(pDocTemplate);		// �������� ������
		CCommandLineInfo cmdInfo;			// ����� ������ 
		ParseCommandLine(cmdInfo);			// ������ ��������� ������			
		if (!ProcessShellCommand(cmdInfo)) return FALSE; // ������ ������ �� ����������
		m_pMainWnd->ShowWindow(SW_SHOW);    // �������� ����		
		m_pMainWnd->UpdateWindow();			// ��������� ���� ��������� ���������	
		return TRUE;								
	};
};
BEGIN_MESSAGE_MAP(CStep2App, CWinApp) 
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew) // ����� ���� New	
END_MESSAGE_MAP() 

CStep2App theApp;
