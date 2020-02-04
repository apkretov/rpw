VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCT2.OCX"
Begin VB.Form frmTransFarm 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Племпродажа"
   ClientHeight    =   3330
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   5475
   Icon            =   "frmTransFarm.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3330
   ScaleWidth      =   5475
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtDateTrans 
      Height          =   315
      Left            =   720
      MaxLength       =   10
      TabIndex        =   1
      ToolTipText     =   "F4 - Открыть календарь"
      Top             =   120
      Width           =   1170
   End
   Begin VB.CommandButton cmdEdit 
      Caption         =   "&Изменить"
      Height          =   375
      Left            =   4320
      TabIndex        =   7
      ToolTipText     =   "Изменить племпродажу"
      Top             =   1200
      Width           =   1065
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   4320
      TabIndex        =   10
      Top             =   2880
      Width           =   1065
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "&ОК"
      Enabled         =   0   'False
      Height          =   375
      Left            =   4320
      TabIndex        =   9
      Top             =   2400
      Width           =   1065
   End
   Begin VB.CommandButton cmdDel 
      Caption         =   "&Удалить"
      Height          =   375
      Left            =   4320
      TabIndex        =   8
      ToolTipText     =   "Удалить племпродажу"
      Top             =   1680
      Width           =   1065
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Добавить"
      Height          =   375
      Left            =   4320
      TabIndex        =   6
      ToolTipText     =   "Добавить племпродажу"
      Top             =   720
      Width           =   1065
   End
   Begin MSComCtl2.DTPicker dtpDateTrans 
      Height          =   315
      Left            =   720
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   120
      Width           =   1455
      _ExtentX        =   2566
      _ExtentY        =   556
      _Version        =   393216
      CheckBox        =   -1  'True
      DateIsNull      =   -1  'True
      Format          =   22806529
      CurrentDate     =   37389
   End
   Begin MSDataListLib.DataCombo dbcFarm 
      Height          =   315
      Left            =   3480
      TabIndex        =   4
      ToolTipText     =   "F4 - Открыть список"
      Top             =   120
      Width           =   1095
      _ExtentX        =   1931
      _ExtentY        =   556
      _Version        =   393216
      MatchEntry      =   -1  'True
      Text            =   ""
   End
   Begin MSComctlLib.ListView lvwTransFarm 
      Height          =   2535
      Left            =   0
      TabIndex        =   5
      Top             =   720
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   4471
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      FullRowSelect   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSAdodcLib.Adodc adoFarms 
      Height          =   330
      Left            =   3480
      Top             =   360
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
      Left            =   2640
      TabIndex        =   3
      Top             =   120
      Width           =   735
   End
   Begin VB.Label lblDateTrans 
      Caption         =   "Да&та:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   495
   End
End
Attribute VB_Name = "frmTransFarm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mintColDate As Integer = 1 'Column idexes.
Const mintColSort As Integer = 2

Dim mobDatFrm As DatFrm
Dim mdbcFarm As DataCombo

Dim mstrIDFarmOrig As String

' Add a farm transfer to lvwTransFarm.
' Prior to addition, make sure the date & farm of transfer have been inputted.
' Enable the cmdEdit, cmdDel, & cmdOk buttons, if disabled.
' Set focus to the txtDateTrans control.
Private Sub cmdAdd_Click()
On Error GoTo ErrHnd
   Dim strKey As String
   Dim strErr As String
   If VldTrans Then 'Validate the date & farm of transfer.
      strKey = txtDateTrans 'Add the farm transfer.
      lvwTransFarm.ListItems.Add , strKey, txtDateTrans
      lvwTransFarm.ListItems(strKey).ListSubItems.Add mintColDate, , dbcFarm.BoundText
      lvwTransFarm.ListItems(strKey).ListSubItems.Add mintColDate, , dbcFarm.BoundText
      lvwTransFarm.ListItems(strKey).ListSubItems.Add mintColSort, , CLng(CDate( _
         txtDateTrans))
'Continue:
      gobFormtCtl.WriteDate txtDateTrans, dtpDateTrans, 0 'Clear txtDateTrans, dbcFarm & set focus to them.
      dbcFarm.BoundText = ""
Continue:
      txtDateTrans.SetFocus
      Call SwchBtn(True) 'Enable the buttons.
      txtDateTrans.SetFocus 'Focus dbcBrdCrs.
   End If
Exit Sub
ErrHnd:
   strErr = Err.Description
   If Err.Number = 35602 Then
      MsgBox LoadResString(211), vbExclamation, LoadResString(50) 'Duplicate transf. date.
   Else
      MsgBox strErr 'Some other error.
   End If
   Resume Continue
End Sub

' Unload the form with no data saved.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
    Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete a farm transfer from lvwTransFarm.
' Prior to deletion, make sure there are farm transfers in lvwTransFarm
'   to delete.
' Enable the cmdOk button, if inactive.
Private Sub cmdDel_Click()
On Error GoTo ErrHnd
    If lvwTransFarm.ListItems.Count > 0 Then
        With lvwTransFarm
           ' Delete.
           .ListItems.Remove (.SelectedItem.Key)
            ' Mark out the remaining selected row, if any.
            If .ListItems.Count > 0 Then .SelectedItem.Selected = True
        End With
        ' Enable cmdOk.
        If cmdOK.Enabled = False Then cmdOK.Enabled = True
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Remove a farm transfer from lvwTransFarm & put it to txtDateTrans & dbcFarm to edit.
' Prior to the move, make sure there are farm transfers in lvwTransFarm to edit.
' Disable the cmdEdit, cmdDel & cmdOk buttons to make the user either complete or cancel
'  the edition altogether.
' Set focus to the txtDateTrans control.
Private Sub cmdEdit_Click()
On Error GoTo ErrHnd
   If lvwTransFarm.ListItems.Count > 0 Then
      With lvwTransFarm
         gobFormtCtl.WriteDate txtDateTrans, dtpDateTrans, .SelectedItem.Text 'Move to
         dbcFarm.BoundText = ""                                 'txtDateTrans & dbcFarm.
         dbcFarm.BoundText = .ListItems(.SelectedItem.Key).ListSubItems.Item(1)
         .ListItems.Remove (.SelectedItem.Key) 'Delete.
         If .ListItems.Count > 0 Then .SelectedItem.Selected = True 'Mark out the
      End With                                    'remaining selected row, if any.
      Call SwchBtn(False) 'Disable the buttons.
      txtDateTrans.SetFocus 'Focus txtDateTrans.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the changes to the ShG object to put them later to the DB.
' Set frmInvetory's dbcFarm control equal to the last farm transferred to, if any.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   Dim intCount As Integer
   Call FrmToDB 'Write the farm transfers.
   intCount = lvwTransFarm.ListItems.Count 'Update frmInvetory's dbcFarm.
   If intCount > 0 Then mdbcFarm.BoundText = lvwTransFarm.ListItems(intCount) _
      .ListSubItems(1).Text
   Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Description
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
   If KeyCode = gobFormtCtl.CodeEsc Then Call cmdCancel_Click
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

' Convert the selected date from the dtpDateTrans control to txtDateTrans.
Private Sub dtpDateTrans_CloseUp()
On Error GoTo ErrHnd
    txtDateTrans = Format$(dtpDateTrans.Value, "Short Date")
    txtDateTrans.SetFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form.
Private Sub Form_Load()
   Call InitCtl 'Initialise the form's controls.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDateTrans_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtDateTrans
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing F4 open the dtpDateTrans.
Private Sub txtDateTrans_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.OpenDTPick KeyCode, dtpDateTrans, txtDateTrans
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDateTrans_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.TypeDate KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted date.
Private Sub txtDateTrans_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   gobFormtCtl.VldDate txtDateTrans, dtpDateTrans, Cancel
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form's controls.
' Set the data source for the dbcFarm.
' Adjust the lvwTransFarm list view's columns.
Private Sub InitCtl()
On Error GoTo ErrHnd
   Dim colDateTrans As ColumnHeader
   Dim colIDFarm As ColumnHeader
   Dim colSort As ColumnHeader
   With adoFarms 'Set the data source for adoFarms & dbcFarm.
       .ConnectionString = gcnnConn.ConnectionString
       .CommandType = adCmdTable
       .RecordSource = "spSelect_Farms_Dbc"
   End With
   Set dbcFarm.RowSource = adoFarms
   With dbcFarm
       .BoundColumn = "IDFarm"
       .ListField = "IDFarm"
   End With
   With lvwTransFarm
      Set colDateTrans = .ColumnHeaders.Add() 'Set lvwTransFarm's column headers.
      colDateTrans.Text = "Дата"
      colDateTrans.Width = .Width * 0.6
      Set colIDFarm = .ColumnHeaders.Add()
      colIDFarm.Text = "Ферма"
      colIDFarm.Width = .Width * 0.4
      Set colSort = .ColumnHeaders.Add()
      colSort.Text = "Sort"
      colSort.Width = 0
      .Sorted = True
      .SortKey = mintColSort
      .SortOrder = lvwAscending
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the form's controls from the obShG in the Edit mode or, if a new farm transfer has
'  been inputted & saved only in the ShG object but not the DB yet.
Private Sub DBtoFrm()
On Error GoTo ErrHnd
   With gobShGs(mobDatFrm.IDFrm).TblShG
      If .TransFarmChand Then 'Define whether farm transfers' data have already changed.
         Call FillLst(.TransFarmsNew) 'Fill out lvwTransFarm.
      Else
         Call FillLst(.TransFarms) 'Fill out lvwTransFarm.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Check whether the date & farm of tranfer have been inputted.
' Return True, if succeeds.
Private Function VldTrans() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If txtDateTrans = "" Or dbcFarm.BoundText = "" Then
      MsgBox LoadResString(212), vbExclamation, LoadResString(21)
      txtDateTrans.SetFocus
   ElseIf Not gobShGs(mobDatFrm.IDFrm).Lives(txtDateTrans, Me.Caption, strPromt:= _
      strPromt) Then
      MsgBox strPromt, vbExclamation, LoadResString(131)
      txtDateTrans.SetFocus
   Else 'Succeeded.
      VldTrans = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Write lvwTransFarm's content to the obShG object.
Private Sub FrmToDB()
On Error GoTo ErrHnd
   Dim intIdx As Integer
   Dim dtmDateTrans As Date
   Dim strIDFarm As String
   With gobShGs(mobDatFrm.IDFrm).TblShG
      .TransFarmResetNew 'Prepare a storage to save the new data.
      .TransFarmChand = True 'Mark the change.
      intIdx = 1
      Do While intIdx <= lvwTransFarm.ListItems.Count
         With lvwTransFarm
            dtmDateTrans = CDate(.ListItems(intIdx).Text)
            strIDFarm = .ListItems(intIdx).ListSubItems(1).Text
         End With
         .TransFarmSaveNew dtmDateTrans, strIDFarm
         intIdx = intIdx + 1
      Loop
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable or disable cmdEdit, cmdDel, & cmdOk buttons & the lvwTransFarm control.
Private Sub SwchBtn(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
    cmdEdit.Enabled = blnEnable
    cmdDel.Enabled = blnEnable
    cmdOK.Enabled = blnEnable
    Call Util.SwchListView(lvwTransFarm, blnEnable) 'Switch lvwTransFarm.
'    lvwTransFarm.Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the module-level mobDatFrm object from the calling frmShG form.
Public Property Set DatFrmCallFrm(ByVal obDatFrmCallFrm As DatFrm)
On Error GoTo ErrHnd
   Set mobDatFrm = obDatFrmCallFrm
   With mobDatFrm 'Fill the controls.
      If .Mode = gobSetng.ModeEdit Or gobShGs(.IDFrm).TblShG.TransFarmChand Then Call _
         DBtoFrm
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Set the frmShG form's Farm data combo to write the last transfer farm's ID to.
Public Property Set FarmDbc(ByVal dbcFarm As DataCombo)
   Set mdbcFarm = dbcFarm
End Property

' Fill out the lvwTransFarm list view.
Private Sub FillLst(ByVal obTransFarms As TransFarms)
On Error GoTo ErrHnd
   Dim obTblTransFarm As TblTransFarm
   Dim strKey As String
   Dim intIdx As Integer
   For Each obTblTransFarm In obTransFarms 'Fill out lvwTransFarm.
      With obTblTransFarm
         intIdx = intIdx + 1
         strKey = .DateTrans
         lvwTransFarm.ListItems.Add intIdx, CStr(.DateTrans), .DateTrans
         lvwTransFarm.ListItems(strKey).ListSubItems.Add mintColDate, , .IDFarm
         lvwTransFarm.ListItems(strKey).ListSubItems.Add mintColSort, , CLng(.DateTrans)
      End With
   Next obTblTransFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
