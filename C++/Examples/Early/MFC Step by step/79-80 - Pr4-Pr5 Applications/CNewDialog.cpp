#include "stdafx.h"
#include "CNewDialog.h"
#include "afxdialogex.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CNewDialog, CDialogEx)

CNewDialog::CNewDialog(CWnd* pParent) : CDialogEx(IDD_DIALOG1, pParent) { }
CNewDialog::~CNewDialog() { }
void CNewDialog::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX); 
	DDX_Text(pDX, IDC_EDIT1, m_Edits);
}

BEGIN_MESSAGE_MAP(CNewDialog, CDialogEx)
END_MESSAGE_MAP()
