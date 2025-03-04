#include "stdafx.h" // Pr1.cpp : Defines the class behaviors for the application.
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Pr1.h"
#include "MainFrm.h"
#include "Pr1Doc.h"
#include "Pr1View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPr1App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPr1App::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew) // Standard file based document commands
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup) // Standard print setup command
END_MESSAGE_MAP()

CPr1App::CPr1App() {
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS; // support Restart Manager
#ifdef _MANAGED // If the application is built using Common Language Runtime support (/clr):	//     1) This additional setting is needed for Restart Manager support to work properly.	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
	SetAppID(_T("Pr1.AppID.NoVersion")); // TODO: replace application ID string below with unique ID string; recommended format for string is CompanyName.ProductName.SubProduct.VersionInformation
	// TODO: add construction code here, place all significant initialization in InitInstance
}

CPr1App theApp; // The one and only CPr1App object

BOOL CPr1App::InitInstance() { // CPr1App initialization
	INITCOMMONCONTROLSEX InitCtrls; // InitCommonControlsEx() is required on Windows XP if an application manifest specifies use of ComCtl32.dll version 6 or later to enable visual styles.  Otherwise, any window creation will fail.
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES; // Set this to include all the common control classes you want to use in your application.
	InitCommonControlsEx(&InitCtrls);
	CWinAppEx::InitInstance();
	if (!AfxOleInit()) { // Initialize OLE libraries
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	EnableTaskbarInteraction(FALSE);
	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();
	SetRegistryKey(_T("Local AppWizard-Generated Applications")); // Standard initialization	// If you are not using these features and wish to reduce the size of your final executable, you should remove from the following the specific initialization routines you do not need. Change the registry key under which our settings are stored // TODO: You should modify this string to be something appropriate such as the name of your company or organization
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	CSingleDocTemplate* pDocTemplate; // Register the application's document templates.  Document templates serve as the connection between documents, frame windows and views
	pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CPr1Doc), RUNTIME_CLASS(CMainFrame)/*main SDI frame window*/, 	RUNTIME_CLASS(CPr1View));
	if (!pDocTemplate) return FALSE;
	AddDocTemplate(pDocTemplate);
	CCommandLineInfo cmdInfo; // Parse command line for standard shell commands, DDE, file open
	ParseCommandLine(cmdInfo);
	EnableShellOpen(); // Enable DDE Execute open
	RegisterShellFileTypes(TRUE);
	if (!ProcessShellCommand(cmdInfo)) return FALSE; // Dispatch commands specified on the command line.  Will return FALSE if app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	m_pMainWnd->ShowWindow(SW_SHOW); // The one and only window has been initialized, so show and update it
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->DragAcceptFiles(); // call DragAcceptFiles only if there's a suffix //  In an SDI app, this should occur after ProcessShellCommand// Enable drag/drop open
	return TRUE;
}

int CPr1App::ExitInstance() {
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);
	return CWinAppEx::ExitInstance();
}

class CAboutDlg : public CDialogEx { // CAboutDlg dialog used for App About
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP() // Implementation
public:
	CAboutDlg();
#ifdef AFX_DESIGN_TIME // Dialog Data
	enum { IDD = IDD_ABOUTBOX };
#endif
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) { }

void CAboutDlg::DoDataExchange(CDataExchange* pDX) { CDialogEx::DoDataExchange(pDX); }

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CPr1App::OnAppAbout() { // App command to run the dialog
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
