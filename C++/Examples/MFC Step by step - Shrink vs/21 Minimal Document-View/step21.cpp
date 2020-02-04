#include "afxwin.h"	  // ��� ��� MFC
#include "resource.h" // �������������� ��������

class CMyDoc : public CDocument { // ����� ���������
protected: 
	CMyDoc() { };						
	DECLARE_DYNCREATE(CMyDoc)		
public:
};
IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

class CMyView : public CView { // ����� ��������
protected: 
	CMyView() { };
	DECLARE_DYNCREATE(CMyView)	// ��� ������� ���������� ��� ���������� ����	
public:
	virtual void OnDraw(CDC* pDC) { };
};
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
