VERSION 5.00
Begin VB.Form frmLogon 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Вход"
   ClientHeight    =   1950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3990
   Icon            =   "frmLogon.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1950
   ScaleWidth      =   3990
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Tag             =   "Login"
   Begin VB.TextBox txtServer 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1410
      TabIndex        =   5
      Top             =   1080
      Width           =   2445
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   360
      Left            =   2760
      TabIndex        =   7
      Tag             =   "Cancel"
      Top             =   1515
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   360
      Left            =   1440
      TabIndex        =   6
      Tag             =   "OK"
      Top             =   1515
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1410
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   600
      Width           =   2445
   End
   Begin VB.TextBox txtUserName 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1410
      TabIndex        =   1
      Top             =   120
      Width           =   2445
   End
   Begin VB.Label lblServer 
      Caption         =   "&Сервер:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   975
   End
   Begin VB.Label lblPassword 
      Caption         =   "П&ароль:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   735
   End
   Begin VB.Label lblUserName 
      Caption         =   "По&льзователь:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmLogon"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mobUtilDB As UtilDB
Dim mobFormtCtl As FormtCtl

' Initialise the module level objects, variables & the form's controls.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Const strServerLocal As String = "(local)" 'The local default server.
   Set mobUtilDB = New UtilDB
   Set mobFormtCtl = New FormtCtl
   txtUserName = mobUtilDB.UserSA 'Type defaults.
   txtServer = strServerLocal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the form.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
'   Call frmMDI.SwchMenuLog(False) 'Disable the toolbar & most of menu items.
   Unload Me
   Unload frmDBRestr
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the global objects.
' Start up the frmInven & frmBrsShG forms.
' To get rid of mixed forms when this form unloads & the frmBrsShG form loads this
'  operation is splited up to 3 procedures (CmdOK1-3) with breaks between them. Call the
'  1st procedure from this one. Enable the tmrTimer to invoke the 2nd procedure.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   If Vld Then 'Validate the inputs.
      Call CmdOK1 'The 1st procedure - & the onle one for the this project vs. FlockBook.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtServer_GotFocus()
On Error GoTo ErrHnd
   mobFormtCtl.SelTxt txtServer
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtPassword_GotFocus()
On Error GoTo ErrHnd
   mobFormtCtl.SelTxt txtPassword
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtUserName_GotFocus()
On Error GoTo ErrHnd
   mobFormtCtl.SelTxt txtUserName
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate filling all DB parameters. Messaga on an error.
' Return True, if succeeds.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If txtUserName = "" Then
      Call Util.MissParam(txtUserName, lblUserName) 'User.
   ElseIf txtServer = "" Then
Debug.Assert 0 = 1 'Verify
      Call Util.MissParam(txtServer, lblServer) 'Server.
   ElseIf txtUserName <> mobUtilDB.UserSA Then
      strPromt = LoadResString(769) & mobUtilDB.UserSA & LoadResString(770)
      MsgBox strPromt, vbExclamation, Me.Caption
      txtUserName.SetFocus
   Else
      Vld = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate filling all DB parameters. Messaga on an error.
' Return True, if succeeds.
Private Function PREV_Vld() As Boolean
On Error GoTo ErrHnd
'   If txtUserName = "" Then
'      Call Util.MissParam(txtUserName, lblUserName) 'User.
'   ElseIf txtServer = "" Then
'Debug.Assert 0 = 1 'Verify
'      Call Util.MissParam(txtServer, lblServer) 'Server.
'   Else
'      Vld = True 'Succeeded.
'   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Private Function CmdOK1() As Boolean
On Error GoTo ErrHnd
   Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
   With mobUtilDB 'Connect to a DB.
      .Server = Trim$(txtServer)
      .DB = .DBMaster
      .User = Trim$(txtUserName)
      .Pwd = Trim$(txtPassword)
      If .Connect(True) Then 'Proceed, if connected.
         Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
         With frmDBRestr 'Load the list of the existing DB's on the server.
            .adoDBServ.RecordSource = "SELECT name FROM sysdatabases WHERE name" _
               & " NOT IN ('master', 'model', 'msdb', 'tempdb', 'Northwind', 'pubs')"
            .adoDBServ.ConnectionString = "driver={SQL Server};server=" & Trim$ _
               (txtServer) & ";uid=" & Trim$(txtUserName) & ";pwd=" & txtPassword & _
               ";database=" & mobUtilDB.DBMaster
            Set .dblDBServ.RowSource = .adoDBServ
            .dblDBServ.BoundColumn = "name"
            .dblDBServ.ListField = "name"
            .adoDBServ.Refresh
            .dblDBServ.Refresh
         End With
         Unload Me
      Else 'Handle an error.
         GoTo SkipErrDesc
      End If
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
SkipErrDesc:
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   txtPassword = ""
   txtUserName.SetFocus
End Function

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Private Function KTB_CmdOK1() As Boolean
'On Error GoTo ErrHnd
'   Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
'   With mobUtilDB 'Connect to a DB.
'      .Server = Trim$(txtServer)
'      .DB = .DBMaster
'      .User = Trim$(txtUserName)
'      .Pwd = Trim$(txtPassword)
'      If .StartServ Then
'         If .Connect(True) Then 'Proceed, if connected.
'            Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
'            With frmDBRestr 'Load the list of the existing DB's on the server.
'               .adoDBServ.RecordSource = "SELECT name FROM sysdatabases WHERE name" _
'                  & " NOT IN ('master', 'model', 'msdb', 'tempdb', 'Northwind', 'pubs')"
'               .adoDBServ.ConnectionString = "driver={SQL Server};server=" & Trim$ _
'                  (txtServer) & ";uid=" & Trim$(txtUserName) & ";pwd=;database=" & _
'                  mobUtilDB.DBMaster
'               Set .dblDBServ.RowSource = .adoDBServ
'               .dblDBServ.BoundColumn = "name"
'               .dblDBServ.ListField = "name"
'               .adoDBServ.Refresh
'               .dblDBServ.Refresh
'            End With
'            Unload Me
'         Else 'Handle an error.
'            GoTo SkipErrDesc
'         End If
'      Else 'Handle an error.
'Debug.Assert 0 = 1 'Verify
'         GoTo SkipErrDesc
'      End If
'   End With
'Exit Function
'ErrHnd:
'   MsgBox Err.Description
'SkipErrDesc:
'   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
'   txtPassword = ""
'   txtUserName.SetFocus
End Function

