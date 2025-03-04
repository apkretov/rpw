// DialogNew.cpp : implementation file
//

#include "stdafx.h"
#include "MFC Creating new window.h"
#include "DialogNew.h"
#include "afxdialogex.h"


// DialogNew dialog

IMPLEMENT_DYNAMIC(DialogNew, CDialogEx)

DialogNew::DialogNew(CWnd* pParent /*=NULL*/) : CDialogEx(IDD_DIALOGNew, pParent) {

}

DialogNew::~DialogNew()
{
}

void DialogNew::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogNew, CDialogEx)
END_MESSAGE_MAP()


// DialogNew message handlers
