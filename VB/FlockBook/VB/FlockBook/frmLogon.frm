VERSION 5.00
Begin VB.Form frmLogon 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Вход"
   ClientHeight    =   1950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4455
   Icon            =   "frmLogon.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1950
   ScaleWidth      =   4455
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Tag             =   "Login"
   Begin VB.CommandButton cmdDB 
      Height          =   375
      Left            =   3960
      Picture         =   "frmLogon.frx":1042
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   720
      Width           =   375
   End
   Begin VB.Timer tmrTimer 
      Enabled         =   0   'False
      Interval        =   125
      Left            =   120
      Top             =   1440
   End
   Begin VB.TextBox txtDB 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1320
      TabIndex        =   3
      Top             =   720
      Width           =   2565
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   360
      Left            =   3195
      TabIndex        =   6
      Tag             =   "Cancel"
      Top             =   1440
      Width           =   1140
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   360
      Left            =   1920
      TabIndex        =   5
      Tag             =   "OK"
      Top             =   1440
      Width           =   1140
   End
   Begin VB.TextBox txtPassword 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   1290
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   165
      Width           =   2565
   End
   Begin VB.Label lblDB 
      Caption         =   "&База данных:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   720
      Width           =   1095
   End
   Begin VB.Label lblPassword 
      Caption         =   "П&ароль:"
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

' Open the Common Dialog box to let the user select the DB file to write its path in the
'  txtDB text box.
Private Sub cmdDB_Click()
On Error GoTo ErrHnd
   With frmMDI.dlgFile
      .DialogTitle = LoadResString(757)
      .Filter = LoadResString(755) & mobUtilDB.DBFlExt & ")|*" & mobUtilDB.DBFlExt
      .InitDir = App.Path
      .FileName = "" 'Delete, if any.
      .Flags = cdlOFNHideReadOnly
      .ShowOpen
      If .FileName <> "" Then
         txtDB = .FileName
         cmdOK.SetFocus
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open the Common Dialog box to let the user select the DB file to write its path in the
'  txtDB text box.
Private Sub KTB_cmdDB_Click()
On Error GoTo ErrHnd
'   Dim strFldrData As String
'   With mobUtilDB
'      strFldrData = .AddPathSlash(App.Path) & .FldrNamData
'      .FldrCreate strFldrData 'Create the Data folder, if missing.
'   End With
'   With frmMDI.dlgFile
'      .DialogTitle = LoadResString(757)
'      .Filter = LoadResString(755) & mobUtilDB.DBFlExt & ")|*" & mobUtilDB.DBFlExt
'      .InitDir = strFldrData
'      .FileName = "" 'Delete, if any.
'      .Flags = cdlOFNHideReadOnly
'      .ShowOpen
'      If .FileName <> "" Then
'         txtDB = .FileName
'         cmdOK.SetFocus
'      End If
'   End With
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
   Call InitCtl
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
         tmrTimer.Interval = gobSetng.TimeIntrv
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
Private Sub txtPassword_GotFocus()
On Error GoTo ErrHnd
   mobFormtCtl.SelTxt txtPassword
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate filling all DB parameters. Message on an error.
' Return True, if succeeds.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   If txtDB <> "" Then 'Filled?
      If txtPassword = mobUtilDB.Pwd Then 'Valid password?
         If mobUtilDB.FlExist(txtDB) Then 'Exists DB file?
            Vld = True 'Succeeded.
         Else
            txtDB.SetFocus
         End If
      Else
         MsgBox LoadResString(33), vbCritical, Util.CutColonAmpers(lblPassword.Caption)
         txtPassword.SetFocus
      End If
   Else
      Call Util.MissParam(txtDB, lblDB.Caption) 'Message & focus.
   End If
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
'      .Server = Trim$(txtServer)
      .DB = Trim$(txtDB)
'      .User = Trim$(txtUserName)
'      .Pwd = txtPassword 'Don't trim the password - it might contain spaces.
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
End Function

' Execute the cmdOk_Click procedure's part 2 after hiding the form.
' Enable the tmrTimer to invoke the 3rd procedure.
Private Sub CmdOK2()
On Error GoTo ErrHnd
   Load frmBrsShGShow 'Load the frmBrsShG & frmBrsShGShow forms.
   Load frmBrsShG
   With frmMDI.staStatusBar.Panels
      .Item("pnlDB").Text = .Item("pnlDB").Text & mobUtilDB.DB & Space(1)
   End With
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
   Call frmMDI.LoadNewShG 'Load a new frmShG form.
   mintProc = mintCmdOk3
   tmrTimer.Interval = gobSetng.TimeIntrv
   tmrTimer.Enabled = True 'Inovke the 3rd procedure.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Me.Show
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
   txtPassword = ""
End Sub

' Execute the cmdOk_Click procedure's part 3 after hiding the form.
Private Sub CmdOK3()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim intCountFrm As Integer
   Dim I As Integer
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
Debug.Assert 0 = 1 'Verify uselessness.
'   chkParam.Value = 1
'   txtUserName.SetFocus
End Sub

' Initialise the contorls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   txtDB = mobUtilDB.DB 'Get a DB name.
   cmdDB.ToolTipText = LoadResString(757)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
