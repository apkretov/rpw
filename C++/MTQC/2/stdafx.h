#pragma once // stdafx.h : include file for standard system include files, or project specific include files that are used frequently, but are changed infrequently

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from windows.h //What does #defining WIN32_LEAN_AND_MEAN exclude exactly? @ http://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly
#include <windows.h>
#include <string>

#ifdef MTQC_EXPORTS //Exporting functions from a DLL with dllexport - Exporting/Importing DLL Libs in VC++ @ https://stackoverflow.com/questions/538134/exporting-functions-from-a-dll-with-dllexport
	#define MTQC_API __declspec(dllexport)
#else
	#define MTQC_API __declspec(dllimport)
#endif
