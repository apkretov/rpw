VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmSumFlockManagm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Управление стадом"
   ClientHeight    =   4950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7320
   Icon            =   "frmSumFlockManagm.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4950
   ScaleWidth      =   7320
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtDateEnd 
      Height          =   315
      Left            =   2880
      MaxLength       =   10
      TabIndex        =   7
      ToolTipText     =   "F4 - Открыть календарь"
      Top             =   3240
      Width           =   1335
   End
   Begin VB.TextBox txtDateBeg 
      Height          =   315
      Left            =   2880
      MaxLength       =   10
      TabIndex        =   4
      ToolTipText     =   "F4 - Открыть календарь"
      Top             =   2520
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   9
      Tag             =   "OK"
      Top             =   4440
      Width           =   1215
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   5880
      TabIndex        =   10
      Tag             =   "Cancel"
      Top             =   4440
      Width           =   1215
   End
   Begin MSDataListLib.DataCombo dbcFarm 
      Height          =   315
      Left            =   2880
      TabIndex        =   2
      ToolTipText     =   "F4 - Открыть список"
      Top             =   1800
      Width           =   1095
      _ExtentX        =   1931
      _ExtentY        =   556
      _Version        =   393216
      MatchEntry      =   -1  'True
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoFarms 
      Height          =   330
      Left            =   2880
      Top             =   2040
      Visible         =   0   'False
      Width           =   1200
      _ExtentX        =   2117
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   8
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
      RecordSource    =   ""
      Caption         =   "adoFarms"
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
   Begin MSComCtl2.DTPicker dtpDateBeg 
      Height          =   315
      Left            =   2880
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   2520
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   556
      _Version        =   393216
      CheckBox        =   -1  'True
      DateIsNull      =   -1  'True
      Format          =   22806529
      CurrentDate     =   37389
   End
   Begin MSComCtl2.DTPicker dtpDateEnd 
      Height          =   315
      Left            =   2880
      TabIndex        =   8
      TabStop         =   0   'False
      Top             =   3240
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   556
      _Version        =   393216
      CheckBox        =   -1  'True
      DateIsNull      =   -1  'True
      Format          =   22806529
      CurrentDate     =   37389
   End
   Begin VB.Label lblDateBegin 
      Caption         =   "Начальная да&та:"
      Height          =   255
      Left            =   1080
      TabIndex        =   3
      Top             =   2520
      Width           =   1335
   End
   Begin VB.Label lblDateEnd 
      Caption         =   "Конечная д&ата:"
      Height          =   255
      Left            =   1080
      TabIndex        =   6
      Top             =   3240
      Width           =   1335
   End
   Begin VB.Label lblFarm 
      Caption         =   "&Ферма:"
      Height          =   255
      Left            =   1080
      TabIndex        =   1
      Top             =   1800
      Width           =   735
   End
   Begin VB.Label lblNote 
      BackColor       =   &H8000000E&
      BorderStyle     =   1  'Fixed Single
      Height          =   975
      Left            =   0
      TabIndex        =   0
      Top             =   -50
      Width           =   7335
   End
   Begin VB.Line linButton 
      BorderColor     =   &H80000005&
      Index           =   1
      X1              =   0
      X2              =   7350
      Y1              =   4215
      Y2              =   4215
   End
   Begin VB.Line linButton 
      BorderColor     =   &H80000011&
      Index           =   0
      X1              =   0
      X2              =   7350
      Y1              =   4200
      Y2              =   4200
   End
End
Attribute VB_Name = "frmSumFlockManagm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mobUtilRpt As UtilRpt

Dim mstrIDFarmOrig As String

Public IsDirty As Boolean

' Unload the form, if it's clear.
' Clear the controls.
' Return the focus to dbcFarm
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If IsDirty Then 'Cancel.
      With dbcFarm 'Clear.
         .SetFocus
         .Text = ""
      End With
      With gobFormtCtl
         .WriteDate txtDateBeg, dtpDateBeg, 0
         .WriteDate txtDateEnd, dtpDateEnd, 0
      End With
      IsDirty = False 'Mark clear.
   Else 'Unload.
      Unload Me
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Query or requery the rptSumFlockManagm report's underlying recordset depending on its
'   state.
' Show the rptSumFlockManagm report.
' Unload this form.
' Switch the menu.
' To get rid of mixed forms when this form unloads & the report loads this operation is
'  splited in 2 procedures (CmdOK1 & CmdOK2) with a break between them. Call the former
'  procedure from this one. Enable the frmMDI.tmrTimer to invoke the latter procedure.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   mobUtilRpt.Show
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Mark a change in the form.
Private Sub dbcFarm_Click(Area As Integer)
   IsDirty = True
End Sub

' Save the original farm ID to validate it, if changes.
Private Sub dbcFarm_GotFocus()
On Error GoTo ErrHnd
   mstrIDFarmOrig = dbcFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Esc.
Private Sub dbcFarm_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If KeyCode = gobFormtCtl.CodeEsc Then
      Call cmdCancel_Click
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Type in upper case.
Private Sub dbcFarm_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   KeyAscii = gobFormtCtl.UpCase(KeyAscii)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Verify that the farm exist in the DB.
Private Sub dbcFarm_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   Cancel = Not gobFormtCtl.VldFarm(dbcFarm, mstrIDFarmOrig)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Convert the selected date from the dtpDateBeg control to txtDateBeg.
Private Sub dtpDateBeg_CloseUp()
On Error GoTo ErrHnd
    txtDateBeg = Format$(dtpDateBeg.Value, "Short Date")
    txtDateBeg.SetFocus
    IsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Convert the selected date from the dtpDateEnd control to txtDateEnd.
Private Sub dtpDateEnd_CloseUp()
On Error GoTo ErrHnd
    txtDateEnd = Format$(dtpDateEnd.Value, "Short Date")
    txtDateEnd.SetFocus
    IsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Mark a change in the form.
Private Sub Form_KeyPress(KeyAscii As Integer)
   IsDirty = True
End Sub

'Initialise the form's controls & text boxes.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set mobUtilRpt = New UtilRpt 'Report processing object.
   Set mobUtilRpt.Frm = Me
   Call InitCtl
'   Call InitTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the window state, if changed.
Private Sub Form_Resize()
On Error GoTo ErrHnd
'   gobSetng.ChildWndStat = Me.WindowState
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the menu, unless switching prevented in the cmdSumFlockManagm_Click procedure.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Screen.MousePointer = vbDefault
'    frmMDI.MousePointer = vbDefault 'Default mouse pointer.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Screen.MousePointer = vbDefault
'   frmMDI.MousePointer = vbDefault 'Default mouse pointer.
End Sub

' Set the lblNote lable's caption.
' Set the data source for the adoFarms & dbcFarm controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   lblNote = vbCrLf & Space$(5) & LoadResString(484) & vbCrLf & Space$(10) & _
      LoadResString(485)
   With adoFarms
      .ConnectionString = gcnnConnServ.ConnectionString
      .CommandType = adCmdStoredProc
      .RecordSource = "spSelect_Farms_Dbc"
   End With
   With dbcFarm
      Set .RowSource = adoFarms
      .BoundColumn = "IDFarm"
      .ListField = "IDFarm"
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Varify a farm inputted.
' Validate a typed farm ID, uless selected from the dbcFarm list.
' Return True, if succeeds.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   If dbcFarm.BoundText = "" Then
      Call Util.MissParam(dbcFarm, lblFarm.Caption) 'Farm missing.
   Else
      With adoFarms.Recordset 'Validate the farm ID: search for it.
         .Find ("IDFarm = '" & dbcFarm.Text & "'")
         If .EOF Then 'Check the search's result.
            With dbcFarm 'Wrong typed ID.
               MsgBox LoadResString(132) & .Text & LoadResString(133), vbExclamation, _
                  LoadResString(131)
               .Text = ""
               .SetFocus
            End With
         Else
            Vld = True 'Validaton passed.
         End If
         .MoveFirst 'Set the cursor to the first record.
      End With
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Varify a beginning & end dates inputted. The dates must not overlap.
' Return True, if succeeds.
Private Function VldDate() As Boolean
On Error GoTo ErrHnd
   Dim blnCancel As Boolean
   With gobFormtCtl
      If Trim$(txtDateBeg) = "" Then 'Beginning date missing.
         Call Util.MissParam(txtDateBeg, lblDateBegin.Caption)
      ElseIf Trim$(txtDateEnd) = "" Then 'End date missing.
         Call Util.MissParam(txtDateEnd, lblDateEnd)
      ElseIf gobFormtCtl.VldDate(txtDateBeg, dtpDateBeg, blnCancel) Then 'Vld. date format.
         If Not blnCancel Then 'Not a future date?
            blnCancel = False 'Reset explicitely.
            If gobFormtCtl.VldDate(txtDateEnd, dtpDateEnd, blnCancel) Then 'Validate date format.
               If Not blnCancel Then 'Not a future date?
                  If CDate(txtDateBeg) >= CDate(txtDateEnd) Then 'Dates overlap.
                     MsgBox LoadResString(130), vbExclamation, LoadResString(131)
                     txtDateBeg.SetFocus
                  Else
                     VldDate = True 'Validaton passed.
                  End If
               End If
            End If
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Select the entire field.
Private Sub txtDateBeg_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtDateBeg
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing F4 open the dtpDateBeg.
Private Sub txtDateBeg_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.OpenDTPick KeyCode, dtpDateBeg, txtDateBeg
   IsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDateBeg_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.TypeDate KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted date.
Private Sub txtDateBeg_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   gobFormtCtl.VldDate txtDateBeg, dtpDateBeg, Cancel
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDateEnd_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtDateEnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing F4 open the dtpDateEnd.
Private Sub txtDateEnd_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.OpenDTPick KeyCode, dtpDateEnd, txtDateEnd
   IsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDateEnd_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.TypeDate KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted date.
Private Sub txtDateEnd_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   gobFormtCtl.VldDate txtDateEnd, dtpDateEnd, Cancel
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Public Function CmdOK1() As Boolean
On Error GoTo ErrHnd
   Dim obDatTblSel As DatTblSel
   Dim obSumFlockManagm As SumFlockManagm
   Dim obUtilDB As UtilDB
   If Vld Then
      If VldDate Then 'Validate a beginning & end dates.
         Set obUtilDB = New UtilDB
         If obUtilDB.BusySet(True) Then 'Mark busy.
            Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
            Call frmMDI.StatusMsg(True, LoadResString(101)) 'Message about connecting.
            Set obSumFlockManagm = New SumFlockManagm 'Query the data.
            Set obDatTblSel = obSumFlockManagm
            If obDatTblSel.Sel(dbcFarm, txtDateBeg, txtDateEnd) Then
               If mobUtilRpt.Requery(deFlockBook.rsSumFlockManagmV_Farms) Then 'Requery.
                  Me.Hide 'Hide this modal form to focus the report.
                  CmdOK1 = True 'Succeeded.
               Else
Debug.Assert 0 = 1 'Verify
                  obUtilDB.BusySet False 'Reset the busy mark.
               End If
            Else 'The query failed.
Debug.Assert 0 = 1 'Verify
               mobUtilRpt.ErrHnd 'Handle the report's error.
'               Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
'               Call frmMDI.StatusMsg(False) 'Remove message.
            End If
         End If
      End If
   End If
Exit Function
ErrHnd:
   MsgBox Err.Description
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove message.
End Function

' Execute the cmdOk_Click procedure's part 2 after hiding the form.
' Enable the tmrTimer to invoke the 3rd procedure.
Public Sub CmdOK2()
On Error GoTo ErrHnd
   Dim rptNewSumFlockManagm As rptSumFlockManagm
   Dim obUtilDB As UtilDB
   Dim strFarm As String
   Dim strFarmer As String
   Dim strDateBeg As String
   Dim strDateEnd As String
   With deFlockBook.rsSumFlockManagmV_Farms 'Requery rsSumFlockManagm_Farms.
      Set rptNewSumFlockManagm = New rptSumFlockManagm 'Load the report.
      strFarm = LoadResString(90) & String(25, vbTab) & dbcFarm & vbCrLf 'IDFarm & farmer's name.
      strFarmer = LoadResString(91) & String(23, vbTab) & UCase$(.Fields("Nam")) & vbCrLf
      strDateBeg = LoadResString(92) & String(4, vbTab) & txtDateBeg & vbCrLf
      strDateEnd = LoadResString(93) & String(7, vbTab) & txtDateEnd
      rptNewSumFlockManagm.Title = strFarm & strFarmer & strDateBeg & strDateEnd
      rptNewSumFlockManagm.Show , frmMDI 'Show the report.
      Call frmMDI.StatusMsg(False) 'Remove message.
      Set obUtilDB = New UtilDB
      obUtilDB.BusySet False 'Reset the busy mark.
      Unload Me 'Unload this form.
      .Close
   End With
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove report-preparation message.
End Sub
