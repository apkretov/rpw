#include <windows.h>
#include "resource.h" 
#include <string>
using std::string; 
using std::to_string;

BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
		case WM_INITDIALOG: // This is where we set up the dialog box, and initialise any default values
			SetDlgItemText(hwnd, IDC_TEXT, "This is a string"); //That's all it takes to change the text contained in the control (this can be used for pretty much any control that has a text value associated with it, STATICs, BUTTONs and so on). @ http://winprog.org/tutorial/controls.html
			SetDlgItemInt(hwnd, IDC_NUMBER, 5, FALSE);
			break;
		case WM_COMMAND: //The WM_COMMAND message uses both, wParam contains two values, HIWORD(wParam) is the notification message (if applicable) and LOWORD(wParam) is the control or menu id that sent the message. @ http://winprog.org/tutorial/message_loop.html //As you may remember from our earlier discussion of the message loop, windows communicate using messages, you send them to get a control to do something, and when an event occurs on the control it will send you a notification message back. For the standard controls this notification will be a WM_COMMAND message as we've already seen with buttons and menus. For the Common Controls which I may get to later, it will be WM_NOTIFY. @ http://winprog.org/tutorial/controls.html
			switch (LOWORD(wParam)) {
				case IDC_ADD: {
						BOOL bSuccess; // When somebody clicks the Add button, first we get the number of they entered
						int nTimes = GetDlgItemInt(hwnd, IDC_NUMBER, &bSuccess, FALSE); //GetDlgItemInt() works much like GetDlgItemText(), except that instead of copying the string to a buffer, it converts it internally into an integer and returns the value to you. The third parameter is optional, and takes a pointer to a BOOL. Since the function returns 0 on failure, there is no way to tell just from that whether or not the function failed or the user just entered 0. If you are fine with a value of 0 in the event of an error, then feel free to ignore this parameter. @ http://winprog.org/tutorial/controls.html
						if (bSuccess) { // Then we get the string they entered. First we need to find out how long it is so that we can allocate some memory
							int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_TEXT));
							if (len > 0) { // Now we allocate, and get the string into our buffer
								int i; 
								char* buf;
								buf = (char*)GlobalAlloc(GPTR, len + 1);
								GetDlgItemText(hwnd, IDC_TEXT, buf, len + 1); //Finally we can call GetDlgItemText() to retrieve the contents of the control into the memory buffer that we've just allocated. This call expects the size of the buffer INCLUDING the null terminator. The return value, which we ignored here, is the number of characters copied, NOT including the null terminator.... fun eh? :) @ http://winprog.org/tutorial/controls.html
								for (i = 0; i < nTimes; i++) { // Now we add the string to the list box however many times the user asked us to.
									int index = SendDlgItemMessage(hwnd, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)buf); /*Once you begin to use dialog boxes, you will need to send messages to the controls in order to communicate with them. You can do this either by using GetDlgItem() first to get the handle to the control using the ID and then use SendMessage(), OR you can use SendDlgItemMessage() which combines the steps. You give it a window handle and a child ID and it will get the child handle, and then send it the message. SendDlgItemMessage() and similar APIs like GetDlgItemText() will work on all windows, not just dialog boxes. @ http://winprog.org/tutorial/message_loop.html */
									SendDlgItemMessage(hwnd, IDC_LIST, LB_SETITEMDATA, (WPARAM)index, (LPARAM)nTimes); /* Here we are associating the value nTimes with the item just for the heck of it, we'll use it to display later. Normally you would put some more useful data here, such as a pointer. */
								}
								GlobalFree((HANDLE)buf); // Dont' forget to free the memory! //You may be or become aware of a second set of APIs named LocalAlloc(), LocalFree(), etc... which are legacy APIs from 16-bit windows. In Win32, the Local* and Global* memory functions are identical. @ http://winprog.org/tutorial/controls.html
							} else MessageBox(hwnd, "You didn't enter anything!", "Warning", MB_OK);
						} else MessageBox(hwnd, "Couldn't translate that number :(", "Warning", MB_OK);
					}break;
				case IDC_REMOVE: {
						HWND hList = GetDlgItem(hwnd, IDC_LIST); // When the user clicks the Remove button, we first get the number of selected items
						int count = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
						//TEST int count = SendDlgItemMessage(hwnd, IDC_LIST, LB_GETSELCOUNT, 0, 0);
						if (count != LB_ERR) {
							if (count != 0) {
								int i; // And then allocate room to store the list of selected items.
								int *buf = (int*)GlobalAlloc(GPTR, sizeof(int) * count);
								SendMessage(hList, LB_GETSELITEMS, (WPARAM)count, (LPARAM)buf);
								for (i = count - 1; i >= 0; i--) {
									int data = SendMessage(hList, LB_GETITEMDATA, (WPARAM)buf[i], 0); //TEST
									MessageBox(hwnd, ("data = " + to_string(data)).c_str(), "My test", 0); //TEST
									SendMessage(hList, LB_DELETESTRING, (WPARAM)buf[i], 0); // Now we loop through the list and remove each item that was selected. // WARNING!!! We loop backwards, because if we removed items from top to bottom, it would change the indexes of the other items!!!
								}
								GlobalFree(buf);
							} else MessageBox(hwnd, "No items selected.", "Warning", MB_OK);
						} else MessageBox(hwnd, "Error counting items :(", "Warning", MB_OK);
					}break;
				case IDC_CLEAR: SendDlgItemMessage(hwnd, IDC_LIST, LB_RESETCONTENT, 0, 0); break;
				case IDC_LIST:
					switch (HIWORD(wParam)) { //Handle the notification messages that the listbox passes to us. In this case, we are interested in LBN_SELCHANGE, which tells us that the selection has been modified by the user. The Notification Code is passed as the HIWORD of wParam, the other half of the parameter that gave us the control ID in the first place. @ http://winprog.org/tutorial/controls.html
						case LBN_SELCHANGE: {
							HWND hList = GetDlgItem(hwnd, IDC_LIST); // Get the number of items selected.
							int count = SendMessage(hList, LB_GETSELCOUNT, 0, 0);
							if (count != LB_ERR) {
								if (count == 1) { // We only want to continue if one and only one item is selected.
									int index; // Since we know ahead of time we're only getting one index, there's no need to allocate an array.
									int err = SendMessage(hList, LB_GETSELITEMS, (WPARAM)1, (LPARAM)&index);
									if (err != LB_ERR) { // Get the data we associated with the item above (the number of times it was added)
										int data = SendMessage(hList, LB_GETITEMDATA, (WPARAM)index, 0);
										SetDlgItemInt(hwnd, IDC_SHOWCOUNT, data, FALSE);
									} else MessageBox(hwnd, "Error getting selected item :(", "Warning", MB_OK);
								} else SetDlgItemText(hwnd, IDC_SHOWCOUNT, "-"); // No items selected, or more than one. Either way, we aren't going to process this. //That's all it takes to change the text contained in the control (this can be used for pretty much any control that has a text value associated with it, STATICs, BUTTONs and so on). @ http://winprog.org/tutorial/controls.html
							} else MessageBox(hwnd, "Error counting items :(", "Warning", MB_OK);
						}
						break;
					}
					break;
			}break;
		case WM_CLOSE: EndDialog(hwnd, 0); break;
		default: return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) { return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc); }
