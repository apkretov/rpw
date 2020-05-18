Attribute VB_Name = "Util"
Option Explicit

' Return the number of the lines skipped to reach the specified time.
' Return zero, unless the time is existent.
Public Function LinSkip(ByVal strFlPath As String, ByVal strTimeSkip As String) As Long
On Error GoTo ErrHnd
   Dim obCandleStick As New CandleStick
   Dim fsoTxtStrm As TextStream
   Dim lngLinSkip As Long
   Dim blnExists As Boolean
   Set fsoTxtStrm = OpenFile(strFlPath).OpenAsTextStream(ForReading) 'Read the contents of the file.
   Do Until fsoTxtStrm.AtEndOfStream
      obCandleStick.ReadOHLC fsoTxtStrm.ReadLine, False
      If obCandleStick.Time = strTimeSkip Then 'Time exists?
         blnExists = True
         Exit Do
      Else
         lngLinSkip = lngLinSkip + 1
      End If
   Loop
   If blnExists Then LinSkip = lngLinSkip
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a text stream with the specified number of lines skipped.
Public Function TxtStrm(ByVal strFlPath As String, ByVal lngLinSkip As Long) As TextStream
On Error GoTo ErrHnd
   Dim fsoTxtStrm As TextStream
   Dim I As Long
   Set fsoTxtStrm = OpenFile(strFlPath).OpenAsTextStream(ForReading) 'Read the contents of the file.
   For I = 1 To lngLinSkip 'Skip.
      fsoTxtStrm.SkipLine
   Next
   Set TxtStrm = fsoTxtStrm
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Covert the number of boxes to the pts represented.
Public Function BoxesToQut(ByVal sngBoxes As Single, ByVal intIncrement As Integer, ByVal lngLevrg As Long) As Single
On Error GoTo ErrHnd
   BoxesToQut = sngBoxes * intIncrement / lngLevrg
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a semi-integer quote by cutting off all figures beyond the last quote decimal.
Public Function IntQut(ByVal sngQut As Single, ByVal lngLevrg As Long) As Single
On Error GoTo ErrHnd
   IntQut = Int(Round(sngQut * lngLevrg)) / lngLevrg
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a text stream with the specified number of lines skipped.
Public Function OpenFile(ByVal strFlPath As String) As File
On Error GoTo ErrHnd
   Dim fsoFSO As New FileSystemObject
   Set OpenFile = fsoFSO.GetFile(strFlPath) 'Open the file.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
