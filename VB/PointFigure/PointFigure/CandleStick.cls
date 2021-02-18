VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CandleStick"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mstrSeprt As String = "," 'The separator symbol.

Private Type CandleStickTp
   Time As String
   O As Single 'The open, high, low & close quotes.
   H As Single
   L As Single
   C As Single
   QutEnd As Integer
   QutBeg As Integer
End Type
Dim mudtCandleStick As CandleStickTp

Public Event RefreshQut(ByVal sngQut As Single) 'Message about the latest quote to be refreshed.

' Get the date & time.
Public Property Get Time() As String
   Time = mudtCandleStick.Time
End Property

' Get the high.
Public Property Get H() As Single
   H = mudtCandleStick.H
End Property

' Get the low.
Public Property Get L() As Single
   L = mudtCandleStick.L
End Property

' Read the date & time & the open, high, low & close quotes of the candlestick.
Public Sub ReadOHLC(ByVal strLine As String, ByVal blnDoEvents As Boolean)
On Error GoTo ErrHnd
   With mudtCandleStick
      .Time = ReadTime(strLine)
      .C = ReadQut(strLine)
      .L = ReadQut(strLine)
      .H = ReadQut(strLine)
      .O = ReadQut(strLine)
      .QutBeg = 0 'Reset for later use.
      .QutEnd = 0
   End With
   If blnDoEvents Then Call DoRefreshQut 'Define the growth direction, if required.
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to reset QutBeg & QutEnd.
End Sub

' Raise RefreshQut event as the candlestick grows up or down.
' If the direction if indefinite continue the previous one.
Private Sub DoRefreshQut()
On Error GoTo ErrHnd
   Static blnPrevUp As Boolean
   Static blnPrevDown As Boolean
      If mudtCandleStick.O < mudtCandleStick.C Then 'Up.
         Call DoRefreshQutUp
         blnPrevUp = True 'Save the direction for later use.
         blnPrevDown = False
      ElseIf mudtCandleStick.O > mudtCandleStick.C Then 'Down.
         Call DoRefreshQutDown
         blnPrevDown = True 'Save the direction for later use.
         blnPrevUp = False
      Else 'Indefinite direction - continue the previous one.
         If blnPrevUp Then 'Up.
            Call DoRefreshQutUp
         ElseIf blnPrevDown Then 'Down.
            Call DoRefreshQutDown
         End If
      End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the quote read from the end of the line containing the quoutes.
' Calculate the beginning of the quote by coutning backwards from its end up to the 1st separator symbol encountered.
Private Function ReadQut(ByVal strLine As String) As Single
On Error GoTo ErrHnd
   With mudtCandleStick
      If .QutEnd = 0 Then 'Not calculated yet?
         .QutEnd = InStrRev(strLine, mstrSeprt) 'The quote's end.
      Else 'Shift the end before the previous beginning.
         .QutEnd = .QutBeg - 1
      End If
      .QutBeg = InStrRev(strLine, mstrSeprt, .QutEnd - 1) + 1
      ReadQut = Val(Mid$(strLine, .QutBeg, .QutEnd - .QutBeg))
   End With
Exit Function
ErrHnd:
   Call frmMain.ActiveForm.CycleErrHnd(Err.Description) 'Handle a cyclical error.
End Function

' Return the date & time string.
Private Function ReadTime(ByVal strLine As String) As String
On Error GoTo ErrHnd
   Dim intLeng As Integer
   Dim intEndDate As Integer
   Dim intEndTime As Integer
   intEndDate = InStr(strLine, mstrSeprt) 'The end of the date string.
   intEndTime = InStr(intEndDate + 1, strLine, mstrSeprt) 'The end of the time string.
   intLeng = intEndTime - 1 'The length of the date & time string.
   ReadTime = Left$(strLine, intLeng) 'Read the date & time.
Exit Function
ErrHnd:
   Call frmMain.ActiveForm.CycleErrHnd(Err.Description) 'Handle a cyclical error.
End Function

' Raise RefreshQut event as the candlestick grows up.
Private Sub DoRefreshQutUp()
On Error GoTo ErrHnd
   With mudtCandleStick
      RaiseEvent RefreshQut(.O)
      RaiseEvent RefreshQut(.L)
      RaiseEvent RefreshQut(.H)
      RaiseEvent RefreshQut(.C)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Raise RefreshQut event as the candlestick grows down.
Private Sub DoRefreshQutDown()
On Error GoTo ErrHnd
   With mudtCandleStick
      RaiseEvent RefreshQut(.O)
      RaiseEvent RefreshQut(.H)
      RaiseEvent RefreshQut(.L)
      RaiseEvent RefreshQut(.C)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

