#include "stdafx.h"

void __stdcall toggleScrollLock() { //Toggling the Num Lock, Caps Lock, and Scroll Lock keys - Simple Solution @ https://www.codeproject.com/Articles/2334/Toggling-the-Num-Lock-Caps-Lock-and-Scroll-Lock-ke
	::keybd_event(VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	::keybd_event(VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}
