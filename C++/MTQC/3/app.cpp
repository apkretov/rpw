#include "stdafx.h" //Based on: (1) Windows Explorer Application @ http://www.functionx.com/visualc/applications/explorer.htm , (2) Creating a Simple Drives Explorer Program @ https://www.codeproject.com/Articles/13366/Creating-a-Simple-Drives-Explorer-Program#_articleTop
#include "app.h"
#include "frame.h"
#include "doc.h"
#include "viewLeft.h"
#include "aboutDlg.h"
#include <exception>
using std::exception;
#include "2\display.h"

#ifdef _DEBUG
	#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(app, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &app::OnAppAbout)
	//KTB ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew) // Standard file based document commands
	//KTB ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &app::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &app::OnFileSave)
END_MESSAGE_MAP()


app::app() { // TODO: replace application ID string below with unique ID string; recommended format for string is CompanyName.ProductName.SubProduct.VersionInformation
	//try { 
		SetAppID(_T("mtqcMfc.AppID.NoVersion")); // TODO: add construction code here, place all significant initialization in InitInstance
	//} 
	//catch (const exception& objException) { messageException(objException, __FUNCTION__, __LINE__); }
}

namespace mtqcMFC { app theApp; } // The one and only app object 

BOOL app::InitInstance() { // app initialization
	INITCOMMONCONTROLSEX InitCtrls; // InitCommonControlsEx() is required on Windows XP if an application manifest specifies use of ComCtl32.dll version 6 or later to enable visual styles.  Otherwise, any window creation will fail.
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES; // Set this to include all the common control classes you want to use in your application.
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2(); // AfxInitRichEdit2() is required to use RichEdit control	

	SetRegistryKey(_T("Local AppWizard-Generated Applications")); // Standard initialization. If you are not using these features and wish to reduce the size of your final executable, you should remove from the following the specific initialization routines you do not need. Change the registry key under which our settings are stored // TODO: You should modify this string to be something appropriate such as the name of your company or organization
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	
	CSingleDocTemplate* pDocTemplate; // Register the application's document templates.  Document templates serve as the connection between documents, frame windows and views
	pDocTemplate = new CSingleDocTemplate( IDR_MAINFRAME, RUNTIME_CLASS(doc), RUNTIME_CLASS(frame) /*main SDI frame window*/, RUNTIME_CLASS(viewLeft));
	if (!pDocTemplate) return FALSE;
	AddDocTemplate(pDocTemplate);
	
	CCommandLineInfo cmdInfo; // Parse command line for standard shell commands, DDE, file open
	ParseCommandLine(cmdInfo);
	
	if (!ProcessShellCommand(cmdInfo)) return FALSE; // Dispatch commands specified on the command line.  Will return FALSE if app was launched with /RegServer, /Register, /Unregserver or /Unregister.

	m_pMainWnd->ShowWindow(SW_SHOW); // The one and only window has been initialized, so show and update it
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

void app::OnAppAbout() { // App command to run the dialog
	aboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void app::OnFileOpen() { //This feature isn's needed. Develop it, when needed.//MFC Doc/View: How to modify the default 'Open' dialog? @ http://forums.codeguru.com/showthread.php?352966-MFC-Doc-View-How-to-modify-the-default-Open-dialog
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, cchrFilter, AfxGetMainWnd());
	if (IDOK == dlgFile.DoModal()) OpenDocumentFile(dlgFile.GetPathName());
}

void app::OnFileSave() {
	CFileDialog FileDlg(FALSE, CString(".txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, cchrFilter);
	if (FileDlg.DoModal() == IDOK) {  
		AfxMessageBox(FileDlg.GetPathName());
	}	
}
