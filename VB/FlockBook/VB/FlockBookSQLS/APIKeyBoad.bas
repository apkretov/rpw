Attribute VB_Name = "APIKeyBoad"
Option Explicit

' Virtual key constants.
'Const VK_MENU = &H12
Const VK_CONTROL = &H11
'Const VK_SHIFT = &H10
'Const VK_ESCAPE = &H1B
'Const VK_TAB = &H9
'Const VK_DELETE = &H2E
'Const VK_END = &H23
'Const VK_HOME = &H24
'Const VK_LEFT = &H25
'Const VK_RIGHT = &H27
Const VK_F4 = &H73
'Const VK_F9 = &H78

Const KEYEVENTF_KEYUP = &H2

' Determine the virtual key code & shift states for an ASCII character in the Windows
'  character set.
Private Declare Function VkKeyScan Lib "user32" Alias "VkKeyScanA" (ByVal cChar _
   As Byte) As Integer
   
' Perform various scan code & character conversions depending on the mapping type
'  specified.
Private Declare Function MapVirtualKey Lib "user32" Alias "MapVirtualKeyA" (ByVal wCode _
   As Long, ByVal wMapType As Long) As Long
   
' Simulate keyboard action.
Private Declare Sub keybd_event Lib "user32" (ByVal bVk As Byte, ByVal bScan As Byte, _
   ByVal dwFlags As Long, ByVal dwExtraInfo As Long)

' Press the F4 key to open a Date Time Picker control.
Public Sub PressF4()
On Error GoTo ErrHnd
   Call KeyBdEvent(VK_F4)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Simulate Down & Up keyboard actions applying the keybd_event function.
Private Sub KeyBdEvent(ByVal intVirtKey As Integer)
On Error GoTo ErrHnd
   Dim intScan As Integer
   intScan = MapVirtualKey(intVirtKey, 0) 'Scan code.
   Call keybd_event(intVirtKey, intScan, 0, 0)  'Down.
   Call keybd_event(intVirtKey, intScan, KEYEVENTF_KEYUP, 0)  'Up.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Simulate a Down keyboard action applying the keybd_event function.
Private Sub KeyBdEventDown(ByVal intVirtKey As Integer)
On Error GoTo ErrHnd
   Dim intScan As Integer
   intScan = MapVirtualKey(intVirtKey, 0) 'Scan code.
   Call keybd_event(intVirtKey, intScan, 0, 0)  'Down.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Simulate an Up keyboard action applying the keybd_event function.
Private Sub KeyBdEventUp(ByVal intVirtKey As Integer)
On Error GoTo ErrHnd
   Dim intScan As Integer
   intScan = MapVirtualKey(intVirtKey, 0) 'Scan code.
   Call keybd_event(intVirtKey, intScan, KEYEVENTF_KEYUP, 0) 'Up.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press the key combination:
'  CTRL+Z.
Public Sub PressCtrlZ()
On Error GoTo ErrHnd
   Dim intVK As Integer
   Call KeyBdEventDown(VK_CONTROL) 'CTRL down.
   intVK = VkKeyScan(gobFormtCtl.AscEngUpZ) And &HFF 'Get the virtual key code for Z.
   Call KeyBdEvent(intVK) 'Press Z.
   Call KeyBdEventUp(VK_CONTROL) 'CTRL up.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

