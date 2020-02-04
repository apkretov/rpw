#pragma once

class CMy63MultithreadingDlg : public CDialogEx {
public:
	CMy63MultithreadingDlg(CWnd* pParent = NULL);	// standard constructor
#ifdef AFX_DESIGN_TIME // Dialog Data
	enum { IDD = IDD_MY63MULTITHREADING_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
protected: // Implementation
	HICON m_hIcon;
	virtual BOOL OnInitDialog(); // Generated message map functions
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
