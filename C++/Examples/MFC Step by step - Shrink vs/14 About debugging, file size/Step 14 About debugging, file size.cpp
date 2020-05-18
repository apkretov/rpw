#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;
#include "afxwin.h"	// библиотека MFC
#include "conio.h"

void main() {
	cout << "This not debug" << endl;
#ifdef _DEBUG
	cout << "debug code" << endl;
#endif
	_getch(); // дождаться нажатия клавиши
}
