#pragma once
#include "afxwin.h"

class CDiaDlg : public CDialogEx {
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDiaDlg(CWnd* pParent = NULL);
	CListBox m_List;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIA_DIALOG };
#endif
};
