#pragma once

class DialogNew : public CDialogEx {
	DECLARE_DYNAMIC(DialogNew)
public:
	DialogNew(CWnd* pParent = NULL); // standard constructor
	virtual ~DialogNew();
#ifdef AFX_DESIGN_TIME // Dialog Data
	enum { IDD = IDD_DIALOGNew };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	DECLARE_MESSAGE_MAP()
};
