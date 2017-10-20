VERSION 5.00
Begin VB.Form frmCert 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Карточка племенного животного"
   ClientHeight    =   4950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7320
   Icon            =   "frmCert.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4950
   ScaleWidth      =   7320
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer tmrTimer 
      Enabled         =   0   'False
      Interval        =   125
      Left            =   120
      Top             =   4440
   End
   Begin VB.TextBox txtShG 
      Height          =   315
      Left            =   2880
      MaxLength       =   6
      TabIndex        =   2
      Top             =   2280
      Width           =   1095
   End
   Begin VB.CommandButton cmdShG 
      Height          =   375
      Left            =   4080
      Picture         =   "frmCert.frx":1042
      Style           =   1  'Graphical
      TabIndex        =   3
      ToolTipText     =   "Выбрать животное"
      Top             =   2280
      Width           =   375
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   4
      Tag             =   "OK"
      Top             =   4440
      Width           =   1215
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   5880
      TabIndex        =   5
      Tag             =   "Cancel"
      Top             =   4440
      Width           =   1215
   End
   Begin VB.Label lblShG 
      Caption         =   "&Номер:"
      Height          =   255
      Left            =   1080
      TabIndex        =   1
      Top             =   2280
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
Attribute VB_Name = "frmCert"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Implements MsgRecip

Dim mcolMsgs As Collection

Dim mobUtilRpt As UtilRpt
Dim mobTblShG As TblShG
Dim mrsCertV_IndividInfo As ADODB.Recordset
Dim mblnVldShG As Boolean

Public IsDirty As Boolean

' Unload the form, if it's clear.
' Clear the txtShG control.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If IsDirty Then 'Cancel.
      txtShG = ""
      txtShG = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID in the txtShG.
      cmdCancel.SetFocus 'Focus cmdCancel to invoke the txtShG_GotFocus proc.
      txtShG.SetFocus
      IsDirty = False 'Mark clear.
   Else 'Unload.
      Unload Me
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the sheep/goat.
' Query the data for the specified sheep/goat by executing stored procedures.
' Show the rptCertRH/ES report.
' Unload this form.
' Switch the menu.
' To get rid of mixed forms when this form unloads & the report loads this operation is
'  splited in 2 procedures (CmdOK1 & CmdOK2) with a break between them. Call the former
'  procedure from this one. Enable the frmMDI.tmrTimer to invoke the latter procedure.
Public Sub cmdOk_Click()
On Error GoTo ErrHnd
   Const lngTimeIntrv As Long = 3000 '4000 'The timer's interval.
   mobUtilRpt.Show lngTimeIntrv
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open the frmBrsShG form.
' Prior to opening show this form nonmodal; after hiding the frmBrsShG form show the
'  former modal again. The frmBrsShGShow requires this manipulation to prevent an error.
Private Sub cmdShG_Click()
On Error GoTo ErrHnd
   With frmBrsShG 'Pass this form's parameters.
      Set .FrmCall = Me
      .FrmCallNam = gobSetng.FrmInvenNam
      Set .IDTxt = txtShG
      Set .CmdButton = cmdShG
      .DatFrmEntr = False
      .FrmCallNew = False
      .RefrshTreeDo 'Refresh the tree veiw, if necessary.
   End With
   Me.Hide
   frmBrsShGShow.cmdShG = True
   Me.Hide
   Me.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Mark a change in the form.
Private Sub Form_KeyPress(KeyAscii As Integer)
   IsDirty = True
End Sub

' Initialise the form & controls.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set mcolMsgs = New Collection 'Create a new mcolMsgs object.
   Set mobUtilRpt = New UtilRpt 'Report processing object.
   Set mobUtilRpt.Frm = Me
   lblNote = vbCrLf & Space$(5) & LoadResString(483) 'Set the lblNote lable's caption.
   txtShG = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID in the txtShG.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the menu, unless switching prevented in the cmdOk_Click procedure.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Screen.MousePointer = vbDefault
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Screen.MousePointer = vbDefault
End Sub

' Check whether a ewe/she-goat has been inputted.
' Return True, if succeeds.
Private Function VldShG() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Call txtShG_Validate(False) 'Validate the length of the ID.
   VldShG = mblnVldShG
   If VldShG Then
      If Trim$(txtShG) = "" Then
         VldShG = False 'Ewe/she-goat missing.
         MsgBox "Введите номер", vbExclamation, "Ошибка"
      Else
         Set mobTblShG = New TblShG 'Validate the ID.
         Set obDatTbl = mobTblShG
         obDatTbl.Sel txtShG
         With gobMsgInst
            VldShG = mobTblShG.Full 'Check message.
            .Rest Me 'Reset messages. DO YOU STILL NEED THIS?
         End With
       End If
   End If
   If Not VldShG Then txtShG.SetFocus 'Focus txtShG on failure.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Format the control.
Private Sub txtShG_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Type in upper case.
Private Sub txtShG_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   KeyAscii = gobFormtCtl.UpCase(KeyAscii)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtShG_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtIDUnfoc txtShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus, if fewer than six characters are inputted & mark this error for the
'  VldShG procedure.
Private Sub txtShG_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   Cancel = Not gobFormtCtl.VldIDShG(txtShG, lblShG)
'   gobFormtCtl.VldIDShG txtShG, lblShG, Cancel
   mblnVldShG = Not Cancel
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mcolMsgs collection to the gobMsgInst object to read/write messages to the form.
Private Property Get MsgRecip_Msgs() As Collection
   Set MsgRecip_Msgs = mcolMsgs
End Property

' Query the data by calling the obDatTblSel.sel procedure for a male/female.
' Return True, if succeeds.
Private Function QueryDat() As Boolean
On Error GoTo ErrHnd
   Dim obCertRH As CertRH
   Dim obCertES As CertES
   Dim obDatTblSel As DatTblSel
   Select Case mobTblShG.IDSex
   Case gobSetng.IDSexMl 'Male.
      Set obCertRH = New CertRH
      Set obDatTblSel = obCertRH
   Case gobSetng.IDSexFm 'Female.
      Set obCertES = New CertES
      Set obDatTblSel = obCertES
   End Select
   QueryDat = obDatTblSel.Sel(txtShG) 'Query the data.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the report's recordset for a male/female.
' Use the ByRef technique to improve the performance.
' Return True, if succeeds.
Private Function RepRst(ByRef rstRepRst As ADODB.Recordset) As Boolean
On Error GoTo ErrHnd
   Select Case mobTblShG.IDSex 'Initialise variables for male/female.
   Case gobSetng.IDSexMl 'Male.
      Set rstRepRst = deFlockBook.rsCertV_IndividInfoRH
   Case gobSetng.IDSexFm 'Female.
      Set rstRepRst = deFlockBook.rsCertV_IndividInfoES
   End Select
   RepRst = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Show a male/female's report & set its title including of farm, farmer & date.
Private Sub RepShow(ByVal strTitle As String)
On Error GoTo ErrHnd
   Dim rptNewCertRH As rptCertRH
   Dim rptNewCertES As rptCertES
   Select Case mobTblShG.IDSex 'Show the report.
   Case gobSetng.IDSexMl 'Male.
      Set rptNewCertRH = New rptCertRH
      With rptNewCertRH
         .Show , frmMDI
         .Title = strTitle
      End With
   Case gobSetng.IDSexFm 'Female.
      Set rptNewCertES = New rptCertES
      With rptNewCertES
         .Show , frmMDI
         .Title = strTitle
      End With
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Public Function CmdOK1() As Boolean
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   If VldShG Then
      Set obUtilDB = New UtilDB
      If obUtilDB.BusySet(True) Then 'Mark busy.
         Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
         Call frmMDI.StatusMsg(True, LoadResString(101))  'Message about connecting.
         If QueryDat Then 'Query the data.
            If RepRst(mrsCertV_IndividInfo) Then 'Report's recordset.
               CmdOK1 = True 'Succeeded.
            Else
Debug.Assert 0 = 1 'Verify
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
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove message.
End Function

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Public Sub CmdOK2()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   If mobUtilRpt.Requery(mrsCertV_IndividInfo) Then 'Requery.
      Me.Hide 'Hide this modal form to focus the report.
         With tmrTimer
            .Interval = gobSetng.TimeIntrv 'Set the interval.
            .Enabled = True 'Inovke the 3rd procedure.
         End With
   Else
      Set obUtilDB = New UtilDB
      obUtilDB.BusySet False 'Reset the busy mark.
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove message.
End Sub

' Execute the cmdOk_Click procedure's part 2 after hiding the form.
' Enable the tmrTimer to invoke the 3rd procedure.
Public Sub CmdOK3()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Dim strFarm As String
   Dim strFarmer As String
   Dim strDate As String
   With mrsCertV_IndividInfo 'Show the farm ID & farmer's name
      strFarm = LoadResString(90) & String(10, vbTab) & .Fields("IDFarm") & vbCrLf
      strFarmer = LoadResString(91) & String(8, vbTab) & UCase$(.Fields("Nam")) & vbCrLf
      strDate = LoadResString(94) & String(14, vbTab) & Format$(Date$, "Short Date")
      Call RepShow(strFarm & strFarmer & strDate) 'Show the report.
      Call frmMDI.StatusMsg(False) 'Remove message.
      Set obUtilDB = New UtilDB
      obUtilDB.BusySet False 'Reset the busy mark.
      Unload Me
      .Close
   End With
   gobDatFrms.IDFrmLastSet mobTblShG.IDShG, gobSetng.FrmCertNam 'Remember IDFrmLast.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Call Util.SwchBtnMouse(Me, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove report-preparation message.
End Sub

' Invoke the specified procedure after the tmrTimer timer's delay.
Private Sub tmrTimer_Timer()
On Error GoTo ErrHnd
   Const strCmdOK3 As String = "CmdOK3"
   tmrTimer.Enabled = False 'Disable.
   CallByName Me, strCmdOK3, VbMethod
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

