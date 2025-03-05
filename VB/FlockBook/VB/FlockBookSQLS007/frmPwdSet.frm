VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Begin VB.Form frmPwdSet 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Изменение пароля"
   ClientHeight    =   1950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3990
   Icon            =   "frmPwdSet.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1950
   ScaleWidth      =   3990
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Tag             =   "Login"
   Begin MSDataListLib.DataCombo dbcUserName 
      Height          =   315
      Left            =   1410
      TabIndex        =   1
      ToolTipText     =   "F4 - Открыть список"
      Top             =   120
      Width           =   2445
      _ExtentX        =   4313
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin VB.TextBox txtPasswordConfm 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1410
      MaxLength       =   128
      PasswordChar    =   "*"
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
      MaxLength       =   128
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   600
      Width           =   2445
   End
   Begin MSAdodcLib.Adodc adoUserName 
      Height          =   330
      Left            =   1410
      Top             =   360
      Visible         =   0   'False
      Width           =   2445
      _ExtentX        =   4313
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   1
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   1
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   ""
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   ""
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   "SELECT name FROM syslogins WHERE name IS NOT NULL ORDER BY name"
      Caption         =   "adoUserName"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin VB.Label lblPasswordConfm 
      Caption         =   "&Подтвердите новый пароль:"
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   1215
   End
   Begin VB.Label lblPassword 
      Caption         =   "&Введите новый пароль:"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   570
      Width           =   1215
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
Attribute VB_Name = "frmPwdSet"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mobFormtCtl As FormtCtl
Dim mobUtilDB As UtilDB

' Enable Esc.
Private Sub dbcUserName_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If KeyCode = gobFormtCtl.CodeEsc Then Call cmdCancel_Click
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the module level objects, variables & the form's controls.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set mobFormtCtl = New FormtCtl
   Set mobUtilDB = New UtilDB
   Call InitCtl
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the form.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the user's current password to a new password.
' Validate beforehand the new password.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   If Vld Then 'Validate.
      Set mobUtilDB = New UtilDB
      mobUtilDB.PwdSet dbcUserName, txtPassword 'Change.
      Unload Me
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtPasswordConfm_GotFocus()
On Error GoTo ErrHnd
   mobFormtCtl.SelTxt txtPasswordConfm
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

' Validate filling the new & confirmed new password. Messaga on an error.
' Return True, if succeeds.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   If txtPassword = "" And txtPasswordConfm = "" Then
      Beep 'No new pwd - confirm deleting the current pwd.
      Vld = VldConfm(MsgBox(LoadResString(30), vbQuestion + vbYesNoCancel, Me.Caption))
   ElseIf txtPassword = "" Then
      Call Util.MissParam(txtPassword, lblPassword) 'Pwd.
   ElseIf txtPasswordConfm = "" Then
      Call Util.MissParam(txtPasswordConfm, lblPasswordConfm) 'Confirmed Pwd.
   ElseIf txtPassword <> txtPasswordConfm Then
      MsgBox LoadResString(31), vbCritical, LoadResString(131)
      Call CtlClear 'Clear the controls.
   Else
      Beep 'Confirm the change.
      Vld = VldConfm(MsgBox(LoadResString(32), vbQuestion + vbYesNoCancel, Me.Caption))
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Clear the controls & focus the txtPassword textbox.
Private Sub CtlClear()
On Error GoTo ErrHnd
   txtPassword = ""
   txtPasswordConfm = ""
   txtPassword.SetFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Confirm the Vld procedure's choice.
' Return True, if confirmed, clear the controls, if denied or unload the form, if
'  canceled.
Private Function VldConfm(ByVal intResp As String) As Boolean
On Error GoTo ErrHnd
   Select Case intResp
   Case vbYes 'Confirmed.
      VldConfm = True
   Case vbNo
      Call CtlClear 'Clear the controls.
   Case vbCancel 'Unload the form.
      Unload Me
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise the form's controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Set obUtilDB = New UtilDB
   With obUtilDB 'The list of the existing DB's on the server.
      adoUserName.ConnectionString = "driver={SQL Server};server=" & .Server & _
         ";uid=" & .UserSA & ";pwd=" & .Pwd & ";database=" & .DBMaster
   End With
   Call Util.DbcSetRowSrc(dbcUserName, adoUserName, "name", "name")
   dbcUserName = obUtilDB.User
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
