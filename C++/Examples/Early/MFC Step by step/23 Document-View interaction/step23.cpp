#include "afxwin.h"	  // ��� ��� MFC
#include "resource.h" // �������������� ��������

class CMyDoc : public CDocument { // ����� ���������
private:
	DECLARE_MESSAGE_MAP(); // ������� ��������
protected: 
	CMyDoc() { csData = "Hello View - Doc"; }; // ������������� ������
	CString csData; // ����� ����� �������
	DECLARE_DYNCREATE(CMyDoc)		
public:
	CString GetData()	{ return csData; }; // �������� ������ // ������
	void SetString(CString s) { csData = s; } // ���������� ������ ������ ���������
	void OnAbout() {
		SetString(_T("������ ���� (�)")); // ���������� ������
		UpdateAllViews(NULL); // �������� ����
	}
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)
BEGIN_MESSAGE_MAP(CMyDoc, CDocument) 
	ON_COMMAND(ID_ABOUT, OnAbout) //  ��� ������ ����
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

class CMainFrame : public CFrameWnd	{ // ����� ����� ����	
protected:							
	CMainFrame() {	};					
	DECLARE_DYNCREATE(CMainFrame)	
public:
};
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

class CStep2App : public CWinApp { // ����� ����������
public:
	CStep2App() { };					
	virtual BOOL InitInstance() {
		CSingleDocTemplate* pDocTemplate;	// ����� ������
		pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME /*������������� ����*/, 	RUNTIME_CLASS(CMyDoc)/* ��������	 ----|*/, RUNTIME_CLASS(CMainFrame) /* ����� ���� ---| �������� ��� ������.*/, RUNTIME_CLASS(CMyView)/* ��������	 ----|*/);
		AddDocTemplate(pDocTemplate);		// �������� ������
		CCommandLineInfo cmdInfo;			// ����� ������ 
		ParseCommandLine(cmdInfo);			// ������ ��������� ������			
		if (!ProcessShellCommand(cmdInfo)) return FALSE; // ������ ������ �� ����������
		m_pMainWnd->ShowWindow(SW_SHOW);    // �������� ����		
		m_pMainWnd->UpdateWindow();			// ��������� ���� ��������� ���������	
		return TRUE;								
};	};

CStep2App theApp;
