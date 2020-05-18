#include "stdafx.h"
#include <iostream>
using std::cout;

//#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
//DECLARE_HANDLE(HWND);

struct HWND__{ 
	int unused; 
}; 
typedef struct HWND__* HWND;


int main() {
	HWND g_hbmBall = NULL;
	cout << g_hbmBall << "\n\n";
	return 0;
}

