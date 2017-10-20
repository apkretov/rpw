#pragma once //The dialog class added based on this tutorial: (35) VC++/C++ MFC tutorial 1: Creating a Dialog box for user input @ https://www.youtube.com/watch?v=Vp81ypJAyVs
#include "resource.h"

class editConstant : public CDialogEx { // editConstant dialog
	DECLARE_DYNAMIC(editConstant)
	CString cstrName; //CString::CString - CString s1; // Empty string @ https://msdn.microsoft.com/en-us/library/aa314317(v=vs.60).aspx
	CString cstrValue;
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	editConstant(CWnd* pParent = NULL); // standard constructor
	virtual ~editConstant();
	#ifdef AFX_DESIGN_TIME // Dialog Data
		enum { IDD = IDD_DIALOG_CONSTANT };
	#endif

	/*inline*/ CString getName() const;
	/*inline*/ void setName(const CString& strName);
	
	/*inline*/ CString getValue() const;
	/*inline*/ void setValue(const CString& strValue);
};
