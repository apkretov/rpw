#include "stdafx.h"
#include <windows.h> //keybd_event function @ https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(keybd_event);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
   
int main() { //Based on Toggling the Num Lock, Caps Lock, and Scroll Lock keys - Simple Solution @ https://www.codeproject.com/Articles/2334/Toggling-the-Num-Lock-Caps-Lock-and-Scroll-Lock-ke
	::keybd_event(VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	::keybd_event(VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	return 0;
}
