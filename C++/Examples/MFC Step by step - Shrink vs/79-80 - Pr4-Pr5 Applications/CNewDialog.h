#pragma once
#include "afxwin.h"

class CNewDialog : public CDialogEx {
	DECLARE_DYNAMIC(CNewDialog)
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	CNewDialog(CWnd* pParent = NULL); 
	virtual ~CNewDialog();
	#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_DIALOG1 };
	#endif
	CString m_Edits;
};
