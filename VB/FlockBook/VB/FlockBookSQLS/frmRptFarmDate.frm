VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmRptFarmDate 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   4950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7320
   Icon            =   "frmRptFarmDate.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4950
   ScaleWidth      =   7320
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtDate 
      Height          =   315
      Left            =   2880
      MaxLength       =   10
      TabIndex        =   4
      ToolTipText     =   "F4 - Открыть календарь"
      Top             =   2760
      Width           =   1335
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   6
      Tag             =   "OK"
      Top             =   4440
      Width           =   1215
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   5880
      TabIndex        =   7
      Tag             =   "Cancel"
      Top             =   4440
      Width           =   1215
   End
   Begin MSDataListLib.DataCombo dbcFarm 
      Height          =   315
      Left            =   2880
      TabIndex        =   2
      ToolTipText     =   "F4 - Открыть список"
      Top             =   2040
      Width           =   1095
      _ExtentX        =   1931
      _ExtentY        =   556
      _Version        =   393216
      MatchEntry      =   -1  'True
      Text            =   ""
   End
   Begin MSComCtl2.DTPicker dtpDate 
      Height          =   315
      Left            =   2880
      TabIndex        =   5
      TabStop         =   0   'False
      Top             =   2760
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   556
      _Version        =   393216
      CheckBox        =   -1  'True
      DateIsNull      =   -1  'True
      Format          =   22937601
      CurrentDate     =   37389
   End
   Begin MSAdodcLib.Adodc adoFarms 
      Height          =   330
      Left            =   2880
      Top             =   2280
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
   Begin VB.Label lblFarm 
      Caption         =   "&Ферма:"
      Height          =   255
      Left            =   1080
      TabIndex        =   1
      Top             =   2040
      Width           =   735
   End
   Begin VB.Label lblDate 
      Caption         =   "Да&та:"
      Height          =   255
      Left            =   1080
      TabIndex        =   3
      Top             =   2775
      Width           =   615
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
   Begin VB.Line linBtn 
      BorderColor     =   &H80000005&
      Index           =   1
      X1              =   0
      X2              =   7350
      Y1              =   4215
      Y2              =   4215
   End
   Begin VB.Line linBtn 
      BorderColor     =   &H80000011&
      Index           =   0
      X1              =   0
      X2              =   7350
      Y1              =   4200
      Y2              =   4200
   End
End
Attribute VB_Name = "frmRptFarmDate"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mintIdxSumGenEval As Integer = 1 'Count from 1 to enable resetting by nullifying.
Const mintIdxSumPerform As Integer = 2
Const mintIdxFrmInvMat As Integer = 3
Const mintIdxFrmLmK As Integer = 4
Const mintIdxFrmWtLmK As Integer = 5
Const mintIdxFrmWtWool As Integer = 6
Const mintIdxFrmAppr As Integer = 7

Dim mobUtilRpt As UtilRpt
Dim mintIdx As Integer

Dim mstrIDFarmOrig As String

Public IsDirty As Boolean

Public Event GetIdx(ByRef intIdx As Integer) 'Get the report index.

' Unload the form, if it's clear.
' Clear the dbcFarm control.
' Return the focus to dbcFarm
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If IsDirty Then 'Cancel.
      Call CtlClear 'Clear.
      IsDirty = False 'Mark clear.
   Else 'Unload.
      Unload Me
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Query data for the specified farm by executing a stored procedure.
' Query the rptSumGenEval report's underlying recordset depending on its state.
' Show the rptSumGenEval report.
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

' Mark a change in the form.
Private Sub Form_KeyPress(KeyAscii As Integer)
   IsDirty = True
End Sub

' Set the size of the window.
' Switch the menu.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set mobUtilRpt = New UtilRpt 'Report processing object.
   Set mobUtilRpt.Frm = Me
   Call InitCtl 'Initialise the form's controls.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the menu, unless switching prevented in the cmdSumGenEval_Click procedure.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Screen.MousePointer = vbDefault
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Screen.MousePointer = vbDefault
End Sub

'' Set the form's & lblNote lable's captions.
' Set the data source for the adoFarms & dbcFarm controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   Call IdxInitCtl
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

' Check whether a farm has been inputted.
' Validate a typed farm ID, uless selected from the dbcFarm list.
' Return True, if succeeds.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   Dim blnCancel As Boolean
   If dbcFarm.BoundText = "" Then
      Call Util.MissParam(dbcFarm, lblFarm.Caption) 'Farm missing.
   ElseIf Trim$(txtDate) = "" Then
      Call Util.MissParam(txtDate, lblDate.Caption) 'Date missing.
   ElseIf gobFormtCtl.VldDate(txtDate, dtpDate, blnCancel) Then 'Validate date format.
      If Not blnCancel Then 'Not a future date?
         With adoFarms.Recordset 'Validate the farm ID: search for it.
            .Find ("IDFarm = '" & dbcFarm.Text & "'")
            If .EOF Then 'Check the search's result.
               With dbcFarm 'Wrong typed ID.
Debug.Assert 0 = 1 'Verify
                  MsgBox LoadResString(132) & .Text & LoadResString(133), vbExclamation, _
                     LoadResString(131)
                  .Text = ""
                  .SetFocus
               End With
            Else
               Vld = True 'Succeeded.
            End If
            .MoveFirst 'Move the cursor to the first record.
         End With
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Convert the selected date from the dtpDate control to txtDate.
Private Sub dtpDate_CloseUp()
On Error GoTo ErrHnd
    txtDate = Format$(dtpDate.Value, "Short Date")
    txtDate.SetFocus
    IsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select the entire field.
Private Sub txtDate_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtDate
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing F4 open the dtpDate.
Private Sub txtDate_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.OpenDTPick KeyCode, dtpDate, txtDate
   IsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDate_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.TypeDate KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted date.
Private Sub txtDate_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   gobFormtCtl.VldDate txtDate, dtpDate, Cancel
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear the form's controls.
Public Sub CtlClear()
On Error GoTo ErrHnd
   dbcFarm.SetFocus
   dbcFarm.Text = ""
   gobFormtCtl.WriteDate txtDate, dtpDate, 0
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Public Function CmdOK1() As Boolean
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   If Vld Then 'Validate a farm.
      Set obUtilDB = New UtilDB
      If obUtilDB.BusySet(True) Then 'Mark busy.
         Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
         Call frmMDI.StatusMsg(True, LoadResString(101))  'Message about connecting.
         If IdxDatTblSel.Sel(dbcFarm, txtDate) Then 'Query the data.
            If mobUtilRpt.Vld(IdxRstVld, dbcFarm) Then
               If mobUtilRpt.Requery(IdxRstDat) Then 'Requery.
                  Me.Hide 'Hide this modal form to focus the report.
                  CmdOK1 = True 'Succeeded.
               Else
Debug.Assert 0 = 1 'Verify
                  obUtilDB.BusySet False 'Reset the busy mark.
               End If
            Else
               obUtilDB.BusySet False 'Reset the busy mark.
            End If
         Else 'The query failed.
            mobUtilRpt.ErrHnd 'Handle the report's error.
         End If
      End If
   End If
Exit Function
ErrHnd:
   MsgBox Err.Description
   mobUtilRpt.ErrHnd 'Handle the report's error.
End Function

' Execute the cmdOk_Click procedure's part 2 after hiding the form.
' Enable the tmrTimer to invoke the 3rd procedure.
Public Sub CmdOK2()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Call IdxShow 'Show the report.
   Call frmMDI.StatusMsg(False) 'Remove message.
   Set obUtilDB = New UtilDB
   obUtilDB.BusySet False 'Reset the busy mark.
   Unload Me
Exit Sub
ErrHnd:
   MsgBox Err.Description
   mobUtilRpt.ErrHnd 'Handle the report's error.
End Sub

' Set the form's & lblNote lable's captions based on the report index.
Private Sub IdxInitCtl()
On Error GoTo ErrHnd
   Const intIndtHead As Integer = 5 'Head indent spaces.
   Const intIndtLow As Integer = 10 'Lower indent spaces.
   Dim strIndtHead As String
   Dim strIndtLow As String
   RaiseEvent GetIdx(mintIdx) 'Get the report index.
   strIndtHead = Space$(intIndtHead) 'Head indent.
   strIndtLow = Space$(intIndtLow) 'Lower indent.
   Select Case mintIdx
   Case mintIdxSumGenEval 'rptSumGenEval
      Me.Caption = LoadResString(489)
      lblNote = vbCrLf & strIndtHead & LoadResString(480) & vbCrLf & strIndtLow & _
         LoadResString(481)
   Case mintIdxSumPerform 'rptSumPerform
      Me.Caption = LoadResString(490)
      lblNote = vbCrLf & strIndtHead & LoadResString(480) & vbCrLf & strIndtLow & _
         LoadResString(482)
   Case mintIdxFrmInvMat 'rptFrmInvMat
      Me.Caption = LoadResString(491)
      lblNote = vbCrLf & strIndtHead & LoadResString(486) & vbCrLf & strIndtLow & _
         LoadResString(487) & vbCrLf & strIndtLow & LoadResString(488)
   Case mintIdxFrmLmK 'rptFrmLmK
      Me.Caption = LoadResString(494)
      lblNote = vbCrLf & strIndtHead & LoadResString(492) & vbCrLf & strIndtLow & _
         LoadResString(493) & vbCrLf & strIndtLow & LoadResString(499)
   Case mintIdxFrmWtLmK 'rptFrmWtLmK
      Me.Caption = LoadResString(498)
      lblNote = vbCrLf & strIndtHead & LoadResString(495) & vbCrLf & strIndtLow & _
         LoadResString(496) & vbCrLf & strIndtLow & LoadResString(497)
   Case mintIdxFrmWtWool 'rptFrmWtWool
      Me.Caption = LoadResString(502)
      lblNote = vbCrLf & strIndtHead & LoadResString(500) & vbCrLf & strIndtLow & _
         LoadResString(501)
   Case mintIdxFrmAppr 'rptFrmAppr
      Me.Caption = LoadResString(505)
      lblNote = vbCrLf & strIndtHead & LoadResString(503) & vbCrLf & strIndtLow & _
         LoadResString(504)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Create the data object based on the report index.
Private Function IdxDatTblSel() As DatTblSel
On Error GoTo ErrHnd
   Dim obSumGenEval As SumGenEval
   Dim obSumPerform As SumPerform
   Dim obFrmInvMat As FrmInvMat
   Dim obFrmLmKRpt As FrmLmKRpt
   Dim obFrmWtLmKRpt As FrmWtLmKRpt
   Dim obFrmWtWoolRpt As FrmWtWoolRpt
   Dim obFrmApprRpt As FrmApprRpt
   Select Case mintIdx
   Case mintIdxSumGenEval 'rptSumGenEval
      Set obSumGenEval = New SumGenEval
      Set IdxDatTblSel = obSumGenEval
   Case mintIdxSumPerform 'rptSumPerform
      Set obSumPerform = New SumPerform
      Set IdxDatTblSel = obSumPerform
   Case mintIdxFrmInvMat 'rptFrmInvMat
      Set obFrmInvMat = New FrmInvMat
      Set IdxDatTblSel = obFrmInvMat
   Case mintIdxFrmLmK 'rptFrmInvMat
      Set obFrmLmKRpt = New FrmLmKRpt
      Set IdxDatTblSel = obFrmLmKRpt
   Case mintIdxFrmWtLmK 'rptFrmWtLmK
      Set obFrmWtLmKRpt = New FrmWtLmKRpt
      Set IdxDatTblSel = obFrmWtLmKRpt
   Case mintIdxFrmWtWool 'rptFrmWtWool
      Set obFrmWtWoolRpt = New FrmWtWoolRpt
      Set IdxDatTblSel = obFrmWtWoolRpt
   Case mintIdxFrmAppr 'rptFrmAppr
      Set obFrmApprRpt = New FrmApprRpt
      Set IdxDatTblSel = obFrmApprRpt
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the validation recordset based on the report index.
Private Property Get IdxRstVld() As ADODB.Recordset
On Error GoTo ErrHnd
   Select Case mintIdx
   Case mintIdxSumGenEval 'rptSumGenEval
      Set IdxRstVld = deFlockBook.rsSumGenEvalV_Valid
   Case mintIdxSumPerform 'rptSumPerform
      Set IdxRstVld = deFlockBook.rsSumPerformV_Valid
   Case mintIdxFrmInvMat 'rptFrmInvMat
      Set IdxRstVld = deFlockBook.rsFrmInvMat_Valid
   Case mintIdxFrmLmK 'rptFrmInvMat
      Set IdxRstVld = deFlockBook.rsFrmLmKV_Valid
   Case mintIdxFrmWtLmK 'rptFrmWtLmK
      Set IdxRstVld = deFlockBook.rsFrmWtLmK_Valid
   Case mintIdxFrmWtWool 'rptFrmWtWool
      Set IdxRstVld = deFlockBook.rsFrmWtWool_Valid
   Case mintIdxFrmAppr 'rptFrmAppr
      Set IdxRstVld = deFlockBook.rsFrmAppr_Valid
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get the data recordset based on the report index.
Private Property Get IdxRstDat() As ADODB.Recordset
On Error GoTo ErrHnd
   Select Case mintIdx
   Case mintIdxSumGenEval 'rptSumGenEval
      Set IdxRstDat = deFlockBook.rsSumGenEval_Farms
   Case mintIdxSumPerform 'rptSumPerform
      Set IdxRstDat = deFlockBook.rsSumPerformV_Farms
   Case mintIdxFrmInvMat 'rptFrmInvMat
      Set IdxRstDat = deFlockBook.rsRptFarm_FrmInvMat
   Case mintIdxFrmLmK 'rptFrmInvMat
      Set IdxRstDat = deFlockBook.rsRptFarm_FrmLmK
   Case mintIdxFrmWtLmK 'rptFrmWtLmK
      Set IdxRstDat = deFlockBook.rsRptFarm_FrmWtLmK
   Case mintIdxFrmWtWool 'rptFrmWtWool
      Set IdxRstDat = deFlockBook.rsRptFarm_FrmWtWool
   Case mintIdxFrmAppr 'rptFrmAppr
      Set IdxRstDat = deFlockBook.rsRptFarm_FrmAppr
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Show the data report based on the report index.
Private Sub IdxShow()
On Error GoTo ErrHnd
   Dim rptNewSumGenEval As rptSumGenEval
   Dim rptNewSumPerform As rptSumPerform
   Dim rptNewFrmInvMat As rptFrmInvMat
   Dim rptNewFrmLmK As rptFrmLmK
   Dim rptNewFrmWtLmK As rptFrmWtLmK
   Dim rptNewFrmWtWool As rptFrmWtWool
   Dim rptNewFrmAppr As rptFrmAppr
   Select Case mintIdx
   Case mintIdxSumGenEval 'rptSumGenEval
      Set rptNewSumGenEval = New rptSumGenEval
      With rptNewSumGenEval
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   Case mintIdxSumPerform 'rptSumPerform
      Set rptNewSumPerform = New rptSumPerform
      With rptNewSumPerform
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   Case mintIdxFrmInvMat 'rptFrmInvMat
      Set rptNewFrmInvMat = New rptFrmInvMat
      With rptNewFrmInvMat
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   Case mintIdxFrmLmK 'rptFrmInvMat
      Set rptNewFrmLmK = New rptFrmLmK
      With rptNewFrmLmK
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   Case mintIdxFrmWtLmK 'rptFrmWtLmK
      Set rptNewFrmWtLmK = New rptFrmWtLmK
      With rptNewFrmWtLmK
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   Case mintIdxFrmWtWool 'rptFrmWtWool
      Set rptNewFrmWtWool = New rptFrmWtWool
      With rptNewFrmWtWool
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   Case mintIdxFrmAppr 'rptFrmAppr
      Set rptNewFrmAppr = New rptFrmAppr
      With rptNewFrmAppr
         .Caption = Me.Caption
         .Title = FarmFarmerDate 'Get the title.
         .Show , frmMDI
      End With
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Compose the report title containing the farm ID, farmer's name & date.
Private Function FarmFarmerDate() As String
On Error GoTo ErrHnd
   Dim strFarm As String
   Dim strFarmer As String
   Dim strDate As String
   strFarm = LoadResString(90) & String(10, vbTab) & dbcFarm & vbCrLf 'Farm ID &
   With IdxRstDat                                                     'farmer's name.
      strFarmer = LoadResString(91) & String(8, vbTab) & UCase$(.Fields("Nam")) & vbCrLf
'      strFarmer = LoadResString(91) & String(8, vbTab) & UCase(.Fields("Nam")) & _
         space(1) & IIf(.Fields("NamFirst") = "-", Chr(0), UCase(.Fields("NamFirst")) & _
         space(1) & UCase(.Fields("NamPatr"))) & vbCrLf
      strDate = LoadResString(94) & String(14, vbTab) & txtDate
      .Close
   End With
   FarmFarmerDate = strFarm & strFarmer & strDate
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' The rptSumGenEval report's index.
Public Property Get IdxSumGenEval() As Integer
   IdxSumGenEval = mintIdxSumGenEval
End Property

' The rptSumPerform report's index.
Public Property Get IdxSumPerform() As Integer
   IdxSumPerform = mintIdxSumPerform
End Property

' The rptFrmInvMat report's index.
Public Property Get IdxFrmInvMat() As Integer
   IdxFrmInvMat = mintIdxFrmInvMat
End Property

' The rptFrmLmK report's index.
Public Property Get IdxFrmLmK() As Integer
   IdxFrmLmK = mintIdxFrmLmK
End Property

' The rptFrmWtLmK report's index.
Public Property Get IdxFrmWtLmK() As Integer
   IdxFrmWtLmK = mintIdxFrmWtLmK
End Property

' The rptFrmWtWool report's index.
Public Property Get IdxFrmWtWool() As Integer
   IdxFrmWtWool = mintIdxFrmWtWool
End Property

' The rptFrmAppr report's index.
Public Property Get IdxFrmAppr() As Integer
   IdxFrmAppr = mintIdxFrmAppr
End Property

