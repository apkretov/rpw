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
   Begin VB.Timer tmrTimer 
      Enabled         =   0   'False
      Interval        =   125
      Left            =   1320
      Top             =   1440
   End
   Begin VB.TextBox txtDB 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1320
      TabIndex        =   8
      Top             =   1560
      Width           =   1245
   End
   Begin VB.TextBox txtServer 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1320
      TabIndex        =   6
      Top             =   1200
      Width           =   1245
   End
   Begin VB.CheckBox chkParam 
      Caption         =   "&Параметры базы данных"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   960
      Width           =   2415
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   360
      Left            =   2760
      TabIndex        =   10
      Tag             =   "Cancel"
      Top             =   1515
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   360
      Left            =   2760
      TabIndex        =   9
      Tag             =   "OK"
      Top             =   1080
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   525
      Width           =   2565
   End
   Begin VB.TextBox txtUserName 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1305
      TabIndex        =   1
      Top             =   120
      Width           =   2550
   End
   Begin VB.Label lblDB 
      Caption         =   "&База данных:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   1560
      Width           =   1095
   End
   Begin VB.Label lblServer 
      Caption         =   "&Сервер:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1320
      Width           =   975
   End
   Begin VB.Label lblPassword 
      Caption         =   "П&ароль:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   480
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
Attribute VB_Name = "frmLogon"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mobUtilDB As UtilDB
Dim mobFormtCtl As FormtCtl

Const mintCmdOk2 As Integer = 1 'Count from 1 to enable resetting by nullifying.
Const mintCmdOk3 As Integer = 2
Dim mintProc As Integer

Dim mblnOk As Boolean

' Hide/unhide the server controls.
Private Sub chkParam_Click()
On Error GoTo ErrHnd
    If chkParam.Value = 1 Then
        lblServer.Visible = True
        txtServer.Visible = True
        lblDB.Visible = True
        txtDB.Visible = True
    Else
        lblServer.Visible = False
        txtServer.Visible = False
        lblDB.Visible = False
        txtDB.Visible = False
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Invoke the specified procedures.
Private Sub tmrTimer_Timer()
On Error GoTo ErrHnd
   tmrTimer.Enabled = False 'Disable.
   Select Case mintProc
   Case mintCmdOk2
      mintProc = 0 'Reset.
      Call CmdOK2
   Case mintCmdOk3
      mintProc = 0 'Reset.
      Call CmdOK3
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDB_GotFocus()
On Error GoTo ErrHnd
   mobFormtCtl.SelTxt txtDB
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDB_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtTxtUnfoc txtDB
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the module level objects, variables & the form's controls.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Dim sBuffer As String
   Dim lSize As Long
   Set mobUtilDB = New UtilDB
   Set mobFormtCtl = New FormtCtl
   With mobUtilDB
      txtUserName = .User 'Get a user name
      txtServer = .Server 'Get a server name.
      txtDB = .DB 'Get a DB name.
   End With
   lblServer.Visible = False
   txtServer.Visible = False
   lblDB.Visible = False
   txtDB.Visible = False
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the form.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
'   Call frmMDI.SwchMenuLog(False) 'Disable the toolbar & most of menu items.
   Unload Me
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
      If CmdOK1 Then 'The 1st procedure.
         mintProc = mintCmdOk2
         tmrTimer.Enabled = True 'Inovke the 2nd procedure.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Exit the application if the authontication has failed.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   If Not mblnOk Then Unload frmMDI
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
Private Sub txtServer_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtTxtUnfoc txtServer
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
Private Sub txtPassword_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtTxtUnfoc txtPassword
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

' Format the control.
Private Sub txtUserName_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtTxtUnfoc txtUserName
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate filling all DB parameters. Messaga on an error.
' Return True, if succeeds.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   Dim strLabel As String
   If txtUserName <> "" Then 'Validate.
      If txtServer <> "" Then
         If txtDB <> "" Then
            Vld = True 'Succeeded.
         Else
            chkParam.Value = 1
            Set ctlCtl = txtDB
            strLabel = lblDB.Caption
         End If
      Else
         chkParam.Value = 1
         Set ctlCtl = txtServer
         strLabel = lblServer.Caption
      End If
   Else
      Set ctlCtl = txtUserName
      strLabel = lblUserName.Caption
   End If
   If Not Vld Then Call Util.MissParam(ctlCtl, strLabel) 'Message & focus.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Private Function CmdOK1() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(True, LoadResString(102)) 'Message about connecting.
   With mobUtilDB 'Connect to a DB.
      .Server = Trim$(txtServer)
      .DB = Trim$(txtDB)
      .User = Trim$(txtUserName)
      .Pwd = txtPassword 'Don't trim the password - it might contain spaces.
      If .Connect(True) Then 'Proceed, if connected.
         Set gobTblCtrlParam = New TblCtrlParam 'Initialise control parameters & settings.
         Set obDatTbl = gobTblCtrlParam
         obDatTbl.Sel
         Set gobFormtCtl = New FormtCtl
         Set gobSetng = New Setng
         Me.Hide 'Hide the form.
         CmdOK1 = True 'Succeeds.
      Else 'Handle an error.
            GoTo SkipErrDesc
      End If
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
   Me.Show
SkipErrDesc:
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
   txtPassword = ""
   chkParam.Value = 1
   txtUserName.SetFocus
End Function

' Execute the cmdOk_Click procedure's part 2 after hiding the form.
' Enable the tmrTimer to invoke the 3rd procedure.
Private Sub CmdOK2()
On Error GoTo ErrHnd
   Load frmBrsShGShow 'Load the frmBrsShG & frmBrsShGShow forms.
   Load frmBrsShG
   With frmMDI.staStatusBar.Panels
      .Item("pnlServer").Text = .Item("pnlServer").Text & mobUtilDB.Server & Space(1)
      .Item("pnlDB").Text = .Item("pnlDB").Text & mobUtilDB.DB & Space(1)
      .Item("pnlUser").Text = .Item("pnlUser").Text & mobUtilDB.User & Space(1)
   End With
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
   Call frmMDI.LoadNewShG 'Load a new frmShG form.
   mintProc = mintCmdOk3
   tmrTimer.Enabled = True 'Inovke the 2nd procedure.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Me.Show
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
   txtPassword = ""
   chkParam.Value = 1
   txtUserName.SetFocus
End Sub

' Execute the cmdOk_Click procedure's part 3 after hiding the form.
Private Sub CmdOK3()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim intCountFrm As Integer
   Dim I As Integer
   If mobUtilDB.User <> mobUtilDB.UserSA Then
      With frmMDI 'Disable the adminstrative menu items for non SA users.
         .mnuSetngDBBackup.Enabled = False
         .mnuSetngDBRestr.Enabled = False
         .mnuSetngExport.Enabled = False
         .mnuSetngPwdSet.Enabled = False
      End With
   End If
   Set mobUtilDB = Nothing 'Destroy explicitly to invoke the class's terminate proc.
   Set obDatTbl = gobTblCtrlParam 'Varify the control parameters.
   If Not obDatTbl.Full Then
      Call frmMDI.mnuFileClose_Click 'Unload the frmInven form.
      mblnOk = True 'Prevent unloading the frmMDI form in this form's Form_Unload proc.
   Else
      mblnOk = True 'Prevent unloading the frmMDI form in this form's Form_Unload proc.
      Unload Me 'Unload this form to show the frmBrsShG modal form.
      With frmMDI.ActiveForm 'Show the frmBrsShG form.
         .Controls("cmdID")(.Controls("tabShG").SelectedItem.Index).Value = True
      End With
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
   intCountFrm = frmMDI.CountFrm 'Unload all frmMDI-child forms.
   For I = 1 To intCountFrm
      Unload frmMDI.ActiveForm
   Next
   Me.Show
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
   txtPassword = ""
   chkParam.Value = 1
   txtUserName.SetFocus
End Sub
