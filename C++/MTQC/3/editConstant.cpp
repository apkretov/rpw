#include "stdafx.h"
#include "editConstant.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(editConstant, CDialogEx)

editConstant::editConstant(CWnd* pParent /*=NULL*/): CDialogEx(IDD_DIALOG_CONSTANT, pParent) {}
editConstant::~editConstant() {}

/*KTB
void AFXAPI ddxTextName(CDataExchange* pDx, int ID, CString& strName) { //Шаг 37 - Пользовательская функция DDX - наш обмен @ http://www.firststeps.ru/mfc/steps/r.php?37
	if (pDx->m_bSaveAndValidate) { // Что происходит. Чтение или запись ? //При сохранении мы вызываем функцию DDX_Text для получения данных и потом модифицируем... @ http://www.firststeps.ru/mfc/steps/r.php?37
		DDX_Text(pDx, ID, strName); 
		//ORIG strName = strName + L" Save DDX";
	} else { //... а при чтении наоборот - сначала изменяем, а потом вызываем DDX_Text. @ http://www.firststeps.ru/mfc/steps/r.php?37
		//ORIG strName = strName + L" Read DDX"; 
		DDX_Text(pDx, ID, strName);
}	}
*/

void editConstant::DoDataExchange(CDataExchange* pDX) { // функция обмена данными //отвечает за обмен данными. Вы не должны вызывать эту функцию непосредственно, вызов её происходит из функции UpdateDate. Эта функция вызывается при создании окна, закрытия окна, но вы можете вызвать её в любой момент. @ http://www.firststeps.ru/mfc/steps/r.php?34
	CDialogEx::DoDataExchange(pDX); // функция родителя
	DDX_Text(pDX, IDC_EDIT_NAME, cstrName); //
	//KTB Either this command (if own read/write modifications are needed) or the one above: ddxTextName(pDX, IDC_EDIT_NAME, cstrName); //Шаг 37 - Пользовательская функция DDX - наш обмен @ http://www.firststeps.ru/mfc/steps/r.php?37
	DDX_Text(pDX, IDC_EDIT_VALUE, cstrValue);
}

BEGIN_MESSAGE_MAP(editConstant, CDialogEx)
END_MESSAGE_MAP()

CString editConstant::getName() const { return cstrName; }
void editConstant::setName(const CString& strName) { cstrName = strName; }

CString editConstant::getValue() const { return cstrValue; }
void editConstant::setValue(const CString& strValue) { cstrValue = strValue; }
