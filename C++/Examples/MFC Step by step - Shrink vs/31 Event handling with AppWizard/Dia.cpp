#include "stdafx.h"
#include "Dia.h"
#include "DiaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CDiaApp, CWinApp)	ON_COMMAND(ID_HELP, &CWinApp::OnHelp) END_MESSAGE_MAP()
CDiaApp::CDiaApp() {	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART; } // support Restart Manager
CDiaApp theApp; // The one and only CDiaApp object

BOOL CDiaApp::InitInstance() { // CDiaApp initialization
	INITCOMMONCONTROLSEX InitCtrls; // InitCommonControlsEx() is required on Windows XP if an application manifest specifies use of ComCtl32.dll version 6 or later to enable visual styles.  Otherwise, any window creation will fail.
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES; // Set this to include all the common control classes you want to use in your application.
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	CShellManager *pShellManager = new CShellManager; // Create the shell manager, in case the dialog contains any shell tree view or shell list view controls.
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows)); // Activate "Windows Native" visual manager for enabling themes in MFC controls
	SetRegistryKey(_T("Local AppWizard-Generated Applications")); // Standard initialization	// If you are not using these features and wish to reduce the size of your final executable, you should remove from the following the specific initialization routines you do not need Change the registry key under which our settings are stored	// TODO: You should modify this string to be something appropriate such as the name of your company or organization
	CDiaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse ==   IDOK) { /*TODO: Place code here to handle when the dialog is  dismissed with OK*/	}
	else if (nResponse ==   IDCANCEL) { /*TODO: Place code here to handle when the dialog is dismissed with Cancel*/	}
	else if (nResponse ==   -1) {
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
	if (pShellManager !=  NULL) delete pShellManager; // Delete the shell manager created above.
	return FALSE; // Since the dialog has been closed, return FALSE so that we exit the application, rather than start the application's message pump.
}

