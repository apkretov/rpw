VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UtilDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Dim mdmoSQLServer As SQLDMO.SQLServer

Public Server As String 'SQL Server.
Public DB As String 'SQL Server DB.
Public User As String 'User name.
Public Pwd As String 'User's password.

' Start the specified SQL Server.
' Return True, if succeeds.
Public Function StartServ() As Boolean
On Error GoTo ErrHnd
   Call InitServer 'Initialise mdmoSQLServer.
   With mdmoSQLServer
      Select Case .Status
      Case SQLDMOSvc_Stopped
         .Start False
      Case SQLDMOSvc_Paused
         .Continue
      End Select
   End With
   StartServ = True 'Started.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Start the specified SQL Server.
' Return True, if succeeds.
Private Function PREV_StartServ() As Boolean
On Error GoTo ErrHnd
'   Dim mdmoSQLServer As SQLDMO.SQLServer
'   Set mdmoSQLServer = New SQLDMO.SQLServer
'   With mdmoSQLServer
'      .Name = Server
'      .Login = User
'      .Password = Pwd
'      Select Case .Status
'      Case SQLDMOSvc_Stopped
'         .Start False
'      Case SQLDMOSvc_Paused
'         .Continue
'      End Select
'   End With
'   StartServ = True 'Started.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Change the password.
Public Sub PwdSet(ByVal strPwdNew As String)
On Error GoTo ErrHnd
   Dim dmoLogin As SQLDMO.Login
   Call InitServer
   Set dmoLogin = mdmoSQLServer.Logins(User)
   dmoLogin.SetPassword Pwd, strPwdNew
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the password.
Private Sub PREV_PwdChng(ByVal strPwdNew As String)
On Error GoTo ErrHnd
'   Call InitServer
'   mdmoSQLServer.Password = strPwdNew
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the module-level variables.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mdmoSQLServer = New SQLDMO.SQLServer
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the mdmoSQLServer object.
Private Sub InitServer()
On Error GoTo ErrHnd
   With mdmoSQLServer
      .Name = Server
      .Login = User
      .Password = Pwd
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
