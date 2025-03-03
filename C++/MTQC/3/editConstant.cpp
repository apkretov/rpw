#include "stdafx.h"
#include "editConstant.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(editConstant, CDialogEx)

editConstant::editConstant(CWnd* pParent /*=NULL*/): CDialogEx(IDD_DIALOG_CONSTANT, pParent) {}
editConstant::~editConstant() {}

/*KTB
void AFXAPI ddxTextName(CDataExchange* pDx, int ID, CString& strName) { //��� 37 - ���������������� ������� DDX - ��� ����� @ http://www.firststeps.ru/mfc/steps/r.php?37
	if (pDx->m_bSaveAndValidate) { // ��� ����������. ������ ��� ������ ? //��� ���������� �� �������� ������� DDX_Text ��� ��������� ������ � ����� ������������... @ http://www.firststeps.ru/mfc/steps/r.php?37
		DDX_Text(pDx, ID, strName); 
		//ORIG strName = strName + L" Save DDX";
	} else { //... � ��� ������ �������� - ������� ��������, � ����� �������� DDX_Text. @ http://www.firststeps.ru/mfc/steps/r.php?37
		//ORIG strName = strName + L" Read DDX"; 
		DDX_Text(pDx, ID, strName);
}	}
*/

void editConstant::DoDataExchange(CDataExchange* pDX) { // ������� ������ ������� //�������� �� ����� �������. �� �� ������ �������� ��� ������� ���������������, ����� � ���������� �� ������� UpdateDate. ��� ������� ���������� ��� �������� ����, �������� ����, �� �� ������ ������� � � ����� ������. @ http://www.firststeps.ru/mfc/steps/r.php?34
	CDialogEx::DoDataExchange(pDX); // ������� ��������
	DDX_Text(pDX, IDC_EDIT_NAME, cstrName); //
	//KTB Either this command (if own read/write modifications are needed) or the one above: ddxTextName(pDX, IDC_EDIT_NAME, cstrName); //��� 37 - ���������������� ������� DDX - ��� ����� @ http://www.firststeps.ru/mfc/steps/r.php?37
	DDX_Text(pDX, IDC_EDIT_VALUE, cstrValue);
}

BEGIN_MESSAGE_MAP(editConstant, CDialogEx)
END_MESSAGE_MAP()

CString editConstant::getName() const { return cstrName; }
void editConstant::setName(const CString& strName) { cstrName = strName; }

CString editConstant::getValue() const { return cstrValue; }
void editConstant::setValue(const CString& strValue) { cstrValue = strValue; }
