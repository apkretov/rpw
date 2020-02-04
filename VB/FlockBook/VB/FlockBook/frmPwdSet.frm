VERSION 5.00
Begin VB.Form frmPwdSet 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Изменение пароля"
   ClientHeight    =   1950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3990
   Icon            =   "frmPwdSet.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1950
   ScaleWidth      =   3990
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Tag             =   "Login"
   Begin VB.TextBox txtPasswordConfm 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1410
      MaxLength       =   128
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   840
      Width           =   2445
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   360
      Left            =   2760
      TabIndex        =   5
      Tag             =   "Cancel"
      Top             =   1515
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   360
      Left            =   1440
      TabIndex        =   4
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
      TabIndex        =   1
      Top             =   240
      Width           =   2445
   End
   Begin VB.Label lblPasswordConfm 
      Caption         =   "&Подтвердите новый пароль:"
      Height          =   375
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   1215
   End
   Begin VB.Label lblPassword 
      Caption         =   "&Введите новый пароль:"
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Top             =   210
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
'   Call InitCtl
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
      mobUtilDB.PwdSet txtPassword 'Change.
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
      MsgBox LoadResString(31), vbExclamation, LoadResString(131)
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
