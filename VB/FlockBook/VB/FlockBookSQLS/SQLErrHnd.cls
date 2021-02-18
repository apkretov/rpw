VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SQLErrHnd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintErrPK As Integer = 2627 'PRIMARY KEY violation error index.

Private Type SQLErrHndTp
   OrigDescr As String
   NatvIdx1 As Long
   NatvDescr1 As String
   NatvTitl1 As String
   NatvIdx2 As Long
   NatvDescr2 As String
   NatvTitl2 As String
End Type

' Handle the SQL Server's erorr: show the description & mark the error.
Public Sub Genrl(ByVal strErrDescr As String)
On Error GoTo ErrHnd
   gobMsgInst.SQLErrSnd frmMDI.ActiveForm ' Mark an error.
   MsgBox strErrDescr
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Complete the task.
End Sub

' Handle the SQL Server's erorr for a modal form: show the description & mark the error.
Public Sub GenrlModl(ByVal strErrDescr As String, ByRef frmRecipModl As Form)
On Error GoTo ErrHnd
   gobMsgInst.SQLErrSnd frmRecipModl ' Mark an error.
   MsgBox strErrDescr
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Complete the task.
End Sub

' Handle the SQL Server's erorr: 'Violation of PRIMARY KEY constraint'.
Public Sub KeyPrim(ByVal strErrDescr As String)
On Error GoTo ErrHnd
   Dim udtSQLErrHnd As SQLErrHndTp
   With udtSQLErrHnd 'Fill the parameters for ErrMsg
      .OrigDescr = strErrDescr
      .NatvIdx1 = mintErrPK
      .NatvDescr1 = LoadResString(73)
      .NatvTitl1 = LoadResString(50)
      .NatvIdx2 = -1 'Unspecified to differ from zero.
   End With
   Call ErrMsg(udtSQLErrHnd) 'Message.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Complete the task.
End Sub

' Handle the SQL Server's erorr: 'Violation of FOREIGN/PRIMARY KEY constraint'.
Public Sub KeyPrimForgn(ByVal strOrigDescr As String, ByVal strNatvDescr As String, _
   ByVal strNatvTitl As String)
On Error GoTo ErrHnd
   Const intErrFK As Integer = 547 'Foreign contraint violation error.
   Dim udtSQLErrHnd As SQLErrHndTp
   With udtSQLErrHnd 'Fill the parameters for ErrMsg
      .OrigDescr = strOrigDescr
      .NatvIdx1 = mintErrPK
      .NatvDescr1 = LoadResString(73)
      .NatvTitl1 = LoadResString(50)
      .NatvIdx2 = intErrFK
      .NatvDescr2 = strNatvDescr
      .NatvTitl2 = strNatvTitl
   End With
   Call ErrMsg(udtSQLErrHnd) 'Message.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Complete the task.
End Sub

' Handle the SQL Server native erorr.
' Send the SQLErrSnd message to the active recipient form.
' Translate the specified error's message, if that's the case, or otherwise show a
'  standard message.
Private Sub ErrMsg(ByRef udtSQLErrHnd As SQLErrHndTp)
On Error GoTo ErrHnd
   gobMsgInst.SQLErrSnd frmMDI.ActiveForm ' Mark an error.
   With udtSQLErrHnd
      Select Case gcnnConnServ.Errors(0).NativeError 'Define the promt.
      Case .NatvIdx1 'Native error 1.
         MsgBox .NatvDescr1, vbExclamation, .NatvTitl1
      Case .NatvIdx2 'Native error 2.
         MsgBox .NatvDescr2, vbExclamation, .NatvTitl2
      Case Else 'Another error.
         MsgBox .OrigDescr
      End Select
   End With
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Complete the task.
End Sub

