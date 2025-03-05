Attribute VB_Name = "APIUtilit"
Option Explicit

Private Declare Function Beep& Lib "kernel32" (ByVal dwFreq As Long, ByVal dwDuration _
As Long)

Public Sub PlaySound()
On Error GoTo ErrHnd
   Const lngFreq As Long = 440
   Const lngDuration As Long = 20000 '1000
   Call Beep(lngFreq, lngDuration)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

