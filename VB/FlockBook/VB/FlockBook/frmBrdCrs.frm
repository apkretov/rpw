VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Begin VB.Form frmBrdCrs 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "Помесная порода"
   ClientHeight    =   4785
   ClientLeft      =   165
   ClientTop       =   2040
   ClientWidth     =   5715
   Icon            =   "frmBrdCrs.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   5715
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdEdit 
      Caption         =   "&Изменить"
      Height          =   375
      Left            =   4560
      TabIndex        =   10
      ToolTipText     =   "Изменить составляющую породу"
      Top             =   2640
      Width           =   1065
   End
   Begin MSComctlLib.ListView lvwBrdCrs 
      Height          =   2535
      Left            =   0
      TabIndex        =   8
      Top             =   2160
      Width           =   4455
      _ExtentX        =   7858
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
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   4560
      TabIndex        =   13
      Top             =   4320
      Width           =   1065
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "&ОК"
      Enabled         =   0   'False
      Height          =   375
      Left            =   4560
      TabIndex        =   12
      Top             =   3840
      Width           =   1065
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Добавить"
      Height          =   375
      Left            =   4560
      TabIndex        =   9
      ToolTipText     =   "Добавить составляющую породу"
      Top             =   2160
      Width           =   1065
   End
   Begin MSDataListLib.DataCombo dbcBrdBas 
      Height          =   315
      Left            =   2040
      TabIndex        =   1
      ToolTipText     =   "F4 - Открыть список"
      Top             =   120
      Width           =   3585
      _ExtentX        =   6324
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSDataListLib.DataCombo dbcBrdDen 
      Height          =   315
      Left            =   4560
      TabIndex        =   3
      ToolTipText     =   "F4 - Открыть список"
      Top             =   600
      Width           =   1065
      _ExtentX        =   1879
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSDataListLib.DataCombo dbcBrdCrs 
      Height          =   315
      Left            =   2040
      TabIndex        =   5
      ToolTipText     =   "F4 - Открыть список"
      Top             =   1200
      Width           =   3585
      _ExtentX        =   6324
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoBrd 
      Height          =   330
      Left            =   2040
      Top             =   240
      Visible         =   0   'False
      Width           =   3585
      _ExtentX        =   6324
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
      Caption         =   "adoBreeds"
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
   Begin MSAdodcLib.Adodc adoBrdDen 
      Height          =   330
      Left            =   4440
      Top             =   720
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
      Caption         =   "adoBreedDen"
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
   Begin MSDataListLib.DataCombo dbcBrdNum 
      Height          =   315
      Left            =   4560
      TabIndex        =   7
      ToolTipText     =   "F4 - Открыть список"
      Top             =   1680
      Width           =   1065
      _ExtentX        =   1879
      _ExtentY        =   556
      _Version        =   393216
      MatchEntry      =   -1  'True
      Text            =   ""
   End
   Begin VB.CommandButton cmdDel 
      Caption         =   "&Удалить"
      Height          =   375
      Left            =   4560
      TabIndex        =   11
      ToolTipText     =   "Удалить составляющую породу"
      Top             =   3120
      Width           =   1065
   End
   Begin MSAdodcLib.Adodc adoBrdNum 
      Height          =   330
      Left            =   4440
      Top             =   1800
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
      Caption         =   "adoBreedNum"
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
   Begin VB.Line linSepar 
      BorderColor     =   &H80000010&
      Index           =   0
      X1              =   0
      X2              =   5865
      Y1              =   1065
      Y2              =   1065
   End
   Begin VB.Line linSepar 
      BorderColor     =   &H80000005&
      Index           =   1
      X1              =   0
      X2              =   5865
      Y1              =   1080
      Y2              =   1080
   End
   Begin VB.Label lblBrdNum 
      Caption         =   "&Числитель составляющей породы:"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   1680
      Width           =   2775
   End
   Begin VB.Label lblBrdCrs 
      Caption         =   "&Составляющая порода:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1200
      Width           =   1815
   End
   Begin VB.Label lblBrdDen 
      Caption         =   "Общий &знаменатель всех составляющих пород:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   3735
   End
   Begin VB.Label lblBrdBas 
      Caption         =   "&Базовая порода:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1335
   End
End
Attribute VB_Name = "frmBrdCrs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mintColIDBrd As Integer = 1 'The columns.
Const mintColNumDen As Integer = 2
Const mintColSort As Integer = 3

Dim mobShG As ShG
Dim mobShGTest As ShG
Dim mintMode As Integer

Dim mblnCallTblOffsp As Boolean

Dim moptBrdPure As OptionButton 'Purebred controls.
Dim mdbcBrdPure As DataCombo
Dim mtxtBrdCrs As TextBox 'Crossbred controls.

' Add a cross breed to lvwBrdCrs.
' Prior to addition, make sure the base breed & a cross one has been inputted.
' Clear the cross breed comboboxes.
' Enable the cmdEdit, cmdDel, & cmdOk buttons, if disabled.
' Set focus to the dbcBrdCrs control.
Private Sub cmdAdd_Click()
On Error GoTo ErrHnd
   Dim strFormtSort As String
   Dim strErr As String
   Dim obTblBrd As TblBrd
   Dim obDatTbl As DatTbl
   If VldAdd Then 'Validate the base & cross breeds.
      Set obTblBrd = New TblBrd
      Set obDatTbl = obTblBrd
      obDatTbl.Sel dbcBrdCrs.BoundText 'Add the combo boxes content.
      strFormtSort = FormtSort 'Get the sort formatting string.
      With lvwBrdCrs
         .ListItems.Add , dbcBrdCrs.BoundText, obTblBrd.Brd
         .ListItems(dbcBrdCrs.BoundText).ListSubItems.Add mintColIDBrd, , _
            dbcBrdCrs.BoundText
         .ListItems(dbcBrdCrs.BoundText).ListSubItems.Add mintColNumDen, , _
            dbcBrdNum.BoundText & gobSetng.BrdCrsSlash & dbcBrdDen.BoundText
         .ListItems(dbcBrdCrs.BoundText).ListSubItems.Add mintColSort, , Format$( _
            dbcBrdNum, strFormtSort)
      End With
Continue:
      dbcBrdCrs.BoundText = "" 'Clear the Cross Breed combo boxes & focus them.
      dbcBrdNum.BoundText = ""
      dbcBrdCrs.SetFocus
      Call SwchBtn(True) 'Enable the buttons.
      dbcBrdCrs.SetFocus 'Focus dbcBrdCrs.
   End If
Exit Sub
ErrHnd:
   strErr = Err.Description
   If Err.Number = 35602 Then ' Duplicate cross breed.
      MsgBox LoadResString(414), vbExclamation, LoadResString(131)
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

' Delete a cross breed from lvwBrdCrs.
' Prior to the deletion, make sure there are cross breeds in
'   lvwBrdCrs to delete.
' Enable the cmdOk button, if inactive.
Private Sub cmdDel_Click()
On Error GoTo ErrHnd
    If lvwBrdCrs.ListItems.Count > 0 Then
        With lvwBrdCrs
           ' Delete.
           .ListItems.Remove (.SelectedItem.Key)
            ' Mark out the remaining selected row, if any.
            If .ListItems.Count > 0 Then .SelectedItem.Selected = True
        End With
        cmdOK.Enabled = True 'Enable cmdOk.
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Move the selected cross breed from lvwBrdCrs & put it to the cross breed comboboxes
'   to edit.
' Prior to the move, make sure there are cross breeds in lvwBrdCrs to edit.
' Disable the cmdEdit, cmdDel, & cmdOk buttons to make the user either complete or
'   cancel the edition altogether.
' Set focus to the dbcBrdCrs control.
Private Sub cmdEdit_Click()
On Error GoTo ErrHnd
   Dim strShare As String
   Dim strBrdNum As String
   If lvwBrdCrs.ListItems.Count > 0 Then
      With lvwBrdCrs
         dbcBrdCrs.BoundText = "" 'Move to the combo boxes.
         dbcBrdCrs.BoundText = .SelectedItem.Key
         dbcBrdNum.BoundText = ""
         strShare = .ListItems(.SelectedItem.Key).ListSubItems(mintColNumDen) 'Share for ShareNumDen
         Call ShareNumDen(strShare, strBrdNum) 'Get the numerator for dbcBrdNum.
         dbcBrdNum.BoundText = strBrdNum 'Set the bound text here vs. from withing ShareNumDen.
         .ListItems.Remove (.SelectedItem.Key) 'Delete.
         If .ListItems.Count > 0 Then .SelectedItem.Selected = True 'Mark out the remaining selected row, if any.
      End With
      Call SwchBtn(False) 'Disable the buttons.
      dbcBrdCrs.SetFocus 'Focus dbcBrdCrs.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the changes to the ShG object to put them later to the DB.
' Make sure the base & cross breeds are specified.
' Reduce the denomimator & numerators, if relevant. Remove a 1/32 cross breed share, if
'  present.
' Fill the frmInven form's crossbred controls & clear the purebred ones, if the breed is
'  crossed. Otherwise, go the other way around.
' Unload the form, unless no error occurs.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   If VldFillCtl Then 'Validate filling the controls.
      If VldBrd Then 'Validate the cross breed.
         With mobShG
            Call CtlRead(.TblShG) 'Write the new breeds.
            With .TblShG
               .BrdCrsesNew.ReducDenNum 'Reduce the denomimator & numerators.
               If .BrdCrsesNew.Remv32nd(True) Then 'Remove the 1/32 cross breed share.
Debug.Assert 0 = 1 'Verify
                  If Not mblnCallTblOffsp Then 'For frmShG only.
   Debug.Assert 0 = 1 'Verify from both frmShG & TblOffsp
                     moptBrdPure = True 'Fill purebred.
   '                  BrdPureOpt = True 'Fill purebred.
   Debug.Assert 0 = 1 'Verify from both frmShG & TblOffsp
                     mdbcBrdPure.BoundText = .IDBrdBasNew
   '                  BrdPureDbc.BoundText = .IDBrdBasNew
   Debug.Assert 0 = 1 'Verify from both frmShG & TblOffsp
                     mtxtBrdCrs = ""
   '                  BrdCrsTxt.Text = ""
                  End If
               Else
                  If Not mblnCallTblOffsp Then 'For frmShG only.
                     mdbcBrdPure.BoundText = ""
                     mtxtBrdCrs = .BrdCrsNew
                  End If
               End If
            End With
         End With
         Unload Me
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable cmdOk button to allow saving a changed based breed.
Private Sub dbcBrdBas_Click(Area As Integer)
On Error GoTo ErrHnd
   cmdOK.Enabled = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del.
' Enable Esc.
Private Sub dbcBrdBas_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    If KeyCode = gobFormtCtl.CodeDel Then
        dbcBrdBas.BoundText = ""
    ElseIf KeyCode = gobFormtCtl.CodeEsc Then
        Call cmdCancel_Click
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate changing the active ShG's basic breed in the frmShG data form's Edit mode.
Private Sub dbcBrdBas_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   If Not mblnCallTblOffsp Then If mintMode = gobSetng.ModeEdit Then Cancel = Not _
      gobFormtCtl.VldIDBrdSpcs(dbcBrdBas, mobShG, True) 'For frmShG only.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del.
' Enable Esc.
Private Sub dbcBrdCrs_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    If KeyCode = gobFormtCtl.CodeDel Then
        dbcBrdCrs.BoundText = ""
    ElseIf KeyCode = gobFormtCtl.CodeEsc Then
        Call cmdCancel_Click
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del.
' Enable Esc.
Private Sub dbcBrdDen_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    If KeyCode = gobFormtCtl.CodeDel Then
        dbcBrdDen.BoundText = ""
    ElseIf KeyCode = gobFormtCtl.CodeEsc Then
        Call cmdCancel_Click
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Esc.
Private Sub dbcBrdNum_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    If KeyCode = gobFormtCtl.CodeEsc Then Call cmdCancel_Click
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted number for formatting & minimum/maximum taken from the adoBrdNum
'  control.
Private Sub dbcBrdNum_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   Const intBrdNumMin As Integer = 1 'The min numerator.
   If gobFormtCtl.VldNum(dbcBrdNum, intBrdNumMin, gobSetng.BrdCrsMaxDen - 1, True) Then 'Validate.
      If CInt(dbcBrdNum) = 0 Then dbcBrdNum = "" 'Clear, if zero.
   Else
      Cancel = True 'Restrict the focus.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Call InitCtl 'Set the data sources for the comboboxes.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form's controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   Dim colBrd As ColumnHeader
   Dim colBrdNumDen As ColumnHeader
   Dim colSort As ColumnHeader
   ' Set the data source for adoBrd, dbcBrdBas & dbcBrdCrs.
   With adoBrd
       .ConnectionString = gcnnConn.ConnectionString
       .CommandType = adCmdTable
       .RecordSource = "spSelect_Breeds_ID_B"
   End With
   Set dbcBrdBas.RowSource = adoBrd
   With dbcBrdBas
       .BoundColumn = "IDBreed"
       .ListField = "Breed"
   End With
   Set dbcBrdCrs.RowSource = adoBrd
   With dbcBrdCrs
       .BoundColumn = "IDBreed"
       .ListField = "Breed"
   End With
   ' Set the data source for adoBrdDen & dbcBrdDen.
   With adoBrdDen
       .ConnectionString = gcnnConn.ConnectionString
       .CommandType = adCmdTable
       .RecordSource = "BreedDen"
   End With
   Set dbcBrdDen.RowSource = adoBrdDen
   With dbcBrdDen
       .BoundColumn = "BreedDen"
       .ListField = "BreedDen"
   End With
   ' Set the data source for adoBrdNum & dbcBrdNum.
   With adoBrdNum
       .ConnectionString = gcnnConn.ConnectionString
       .CommandType = adCmdTable
       .RecordSource = "BreedNum"
   End With
   Set dbcBrdNum.RowSource = adoBrdNum
   With dbcBrdNum
       .BoundColumn = "BreedNum"
       .ListField = "BreedNum"
   End With
   ' Set lvwBrdCrs's column headers.
   Set colBrd = lvwBrdCrs.ColumnHeaders.Add()
   With colBrd
        .Text = "Составляющая порода"
        .Width = lvwBrdCrs.Width * 0.7
   End With
   Set colBrdNumDen = lvwBrdCrs.ColumnHeaders.Add()
   With colBrdNumDen
        .Text = "Код"
        .Width = lvwBrdCrs.Width * 0.13
   End With
   Set colBrdNumDen = lvwBrdCrs.ColumnHeaders.Add()
   With colBrdNumDen
        .Text = "Доля"
        .Width = lvwBrdCrs.Width * 0.17
   End With
   Set colSort = lvwBrdCrs.ColumnHeaders.Add()
   colSort.Text = "Sort"
   colSort.Width = 0
   With lvwBrdCrs
      .Sorted = True
      .SortKey = mintColSort
      .SortOrder = lvwDescending
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the form's controls from the obShG in a case of the Edit mode or if new cross
'  breeds have been inputted & saved only in the ShG object but not the DB yet.
Private Sub DBtoFrm()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim obTblBrdCrs As TblBrdCrs
   Dim obTblBrd As TblBrd
   Dim intIdx As Integer
   Dim strFormtSort As String
   Set obTblBrd = New TblBrd
   Set obDatTbl = obTblBrd
   With mobShG.TblShG
      strFormtSort = FormtSort 'Get the sort formatting string.
      If .BrdCrsChand Or mblnCallTblOffsp Then 'Define whether the cross breed have already changed.
         dbcBrdBas.BoundText = .IDBrdBasNew
         dbcBrdDen.BoundText = CStr(.BrdCrsDenNew)
         For Each obTblBrdCrs In .BrdCrsesNew 'Fill out lvwBrdCrs.
            With obTblBrdCrs
               obDatTbl.Sel .IDBrd
               intIdx = intIdx + 1
               lvwBrdCrs.ListItems.Add intIdx, .IDBrd, obTblBrd.Brd
               lvwBrdCrs.ListItems(.IDBrd).ListSubItems.Add , , .IDBrd
               lvwBrdCrs.ListItems(.IDBrd).ListSubItems.Add , , .BrdNum & gobSetng _
                  .BrdCrsSlash & .BrdDen
               lvwBrdCrs.ListItems(.IDBrd).ListSubItems.Add , , Format$(.BrdNum, _
                  strFormtSort)
            End With
         Next obTblBrdCrs
      Else
         dbcBrdBas.BoundText = .IDBrdBas 'Set the base breed's combo boxes.
         dbcBrdDen.BoundText = CStr(.BrdCrsDen)
         For Each obTblBrdCrs In .BrdCrses 'Fill out lvwBrdCrs.
            With obTblBrdCrs
               obDatTbl.Sel .IDBrd
               intIdx = intIdx + 1
               lvwBrdCrs.ListItems.Add intIdx, .IDBrd, obTblBrd.Brd
               lvwBrdCrs.ListItems(.IDBrd).ListSubItems.Add , , .IDBrd
               lvwBrdCrs.ListItems(.IDBrd).ListSubItems.Add , , .BrdNum & gobSetng _
                  .BrdCrsSlash & .BrdDen
               lvwBrdCrs.ListItems(.IDBrd).ListSubItems.Add , , Format$(.BrdNum, _
                  strFormtSort)
            End With
         Next obTblBrdCrs
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the number of cross breed shares up to 6.
' Validate that the base breed & a cross breed are inputted on pressing the Add button.
' Return True, if succeeds.
Private Function VldAdd() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If Not LimitMaxShare(True) Then 'Limit the number of cross breed shares.
      cmdAdd.SetFocus
   Else
      If dbcBrdBas.BoundText = "" Or dbcBrdDen.BoundText = "" Then 'Base breed.
Debug.Assert 0 = 1 'Verify
         Call MsgFocBrdBas 'Message & focus.
   '      MsgBox LoadResString(410), vbExclamation, LoadResString(131)
   '      dbcBrdBas.SetFocus
      ElseIf dbcBrdCrs.BoundText = "" Or dbcBrdNum.BoundText = "" Then 'Cross breed.
         MsgBox LoadResString(411), vbExclamation, LoadResString(131)
         dbcBrdCrs.SetFocus
      ElseIf CInt(dbcBrdNum) >= CInt(dbcBrdDen) Then 'Are numerator & denomimator equal?
         strPromt = Util.CutColonAmpers(lblBrdNum.Caption) & " (= " & dbcBrdNum & _
            LoadResString(415) & dbcBrdDen & ")."
         MsgBox strPromt, vbExclamation, LoadResString(131)
         dbcBrdNum.SetFocus
      Else
         VldAdd = True 'Succeeded.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' On pressing the Ok button, make sure that there are the base breed & cross breeds to
'  save, if lvwBrdCrs is filled.
' Return True, if succeeds.
Private Function VldFillCtl() As Boolean
On Error GoTo ErrHnd
   Const intMinShares As Integer = 2 'Minimal number or shares to be inputted.
   If (lvwBrdCrs.ListItems.Count <> 0) And (dbcBrdBas.BoundText = "" Or dbcBrdDen _
      .BoundText = "") Then 'Base breed.
      Call MsgFocBrdBas 'Message & focus.
   ElseIf lvwBrdCrs.ListItems.Count <> 0 And lvwBrdCrs.ListItems.Count < intMinShares _
      Then 'No cross breeds to save.
      MsgBox LoadResString(413), vbExclamation, LoadResString(131)
      dbcBrdCrs.SetFocus
   Else
      If Not LimitMaxShare(False) Then 'Limit the number of cross breed shares.
         lvwBrdCrs.SetFocus
      Else
         VldFillCtl = True 'Succeeded.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Derive the specified cross breed share's numerator & denominator from lvwBrdCrs's Cross
'   Breed Share column.
Private Sub ShareNumDen(ByVal strShare As String, ByRef strBrdNum As String, Optional _
   ByRef strBrdDen As String)
On Error GoTo ErrHnd
   Dim intSlashPlace As Integer
   Dim strChar As String
   Do Until strChar = gobSetng.BrdCrsSlash 'Define the position of the slash between the numerator &
      intSlashPlace = intSlashPlace + 1            'denominator in the share.
      strChar = Mid(strShare, intSlashPlace, 1)
   Loop
   strBrdNum = Left$(strShare, intSlashPlace - 1) 'Derive the numerator.
   strBrdDen = Mid$(strShare, intSlashPlace + 1) 'Derive the denominator.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the form's controls' content to the obShG object.
' Delete all cross breeds from the obShG object, if lvwBrdCrs is empty.
Private Sub CtlRead(ByRef obTblShG As TblShG)
On Error GoTo ErrHnd
   Dim intIdx As Integer
   Dim strShare As String
   Dim strIDBrd As String
   Dim strBrdNum As String
   Dim strBrdDen As String
   With obTblShG
      .BrdCrsResetNew 'Prepare a storage to save the new data.
      .BrdCrsChand = True 'Mark the change.
      If lvwBrdCrs.ListItems.Count <> 0 Then 'Save cross breeds, if any.
         .IDBrdBasNew = dbcBrdBas.BoundText 'Breed base.
         .BrdCrsDenNew = CInt(dbcBrdDen.BoundText)
         intIdx = 1 'Cross breeds.
         Do While intIdx <= lvwBrdCrs.ListItems.Count
            With lvwBrdCrs
               strIDBrd = .ListItems(intIdx).ListSubItems(mintColIDBrd).Text
               strShare = .ListItems(intIdx).ListSubItems(mintColNumDen).Text 'Share for ShareNumDen proc.
               Call ShareNumDen(strShare, strBrdNum, strBrdDen) 'Get the num/den.
            End With
            .BrdCrsSaveNew strIDBrd, CInt(strBrdNum), CInt(strBrdDen)
            intIdx = intIdx + 1
         Loop
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable or disable cmdEdit, cmdDel, & cmdOk buttons & the lvwBrdCrs control.
Private Sub SwchBtn(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   cmdEdit.Enabled = blnEnable
   cmdDel.Enabled = blnEnable
   cmdOK.Enabled = blnEnable
   Call Util.SwchListView(lvwBrdCrs, blnEnable) 'Switch lvwBrdCrs.
'    lvwBrdCrs.Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resize the linSeparLight & linSeparDark lines.
Private Sub Form_Resize()
On Error GoTo ErrHnd
'   gobFormtCtl.ResizeLin Me, linSepar(0), linSepar(1)
'   With Me
'      linSeparLight.X1 = .ScaleLeft
'      linSeparLight.X2 = .ScaleWidth
'      linSeparDark.X1 = .ScaleLeft
'      linSeparDark.X2 = .ScaleWidth
'   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the module-level variables & fill the controls.
Public Sub InitFrm(ByRef obShG As ShG, ByVal blnCallTblOffspVsFrmShG As Boolean, _
   Optional ByVal intMode As Integer = 0, Optional ByRef optBrdPure As OptionButton, _
   Optional ByRef dbcBrdPure As DataCombo, Optional ByRef txtBrdCrs As TextBox)
On Error GoTo ErrHnd
   Set mobShG = obShG
   mblnCallTblOffsp = blnCallTblOffspVsFrmShG
   mintMode = intMode
   If Not mblnCallTblOffsp Then 'Link to frmShG's breed controls.
      Set moptBrdPure = optBrdPure
      Set mdbcBrdPure = dbcBrdBas
      Set mtxtBrdCrs = txtBrdCrs
   End If
   If (intMode = gobSetng.ModeEdit Or obShG.TblShG.BrdCrsChand) Or _
      (blnCallTblOffspVsFrmShG) Then Call DBtoFrm 'Fill the controls.
   If blnCallTblOffspVsFrmShG Then dbcBrdBas.Enabled = False 'Prevent changing the
Exit Sub                                                     'basic breed for TblOffsp.
ErrHnd:
MsgBox Err.Description
End Sub

' Validate all the aspects of inputting a cross breed.
' Create a testing obShG object & fill first its cross breed to verify.
' Return True, if succeeds.
Private Function VldBrd() As Boolean
On Error GoTo ErrHnd
   If lvwBrdCrs.ListItems.Count = 0 Then 'Validate cross breed shares, if any.
      VldBrd = True 'No shares.
   Else
      Set mobShGTest = New ShG 'Initialise the thesting ShG.
      With mobShGTest
         .IDShG = mobShG.IDShG
         Call CtlRead(.TblShG) 'Read the new cross breed.
      End With 'Below: 'Validate the denomimators, numerators & the basic breed share.
      If VldBrdDen Then If VldBrdNum Then VldBrd = VldBrdBas
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate all cross breed shares' denominators that they be equal to the dbcBrdBas combo
'  box's value & to each other's.
' Return True, if succeeds.
Private Function VldBrdDen() As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim blnFail As Boolean
   Dim strPromt As String
   For Each obTblBrdCrs In mobShGTest.TblShG.BrdCrsesNew 'Loop through all shares.
      With obTblBrdCrs
         If .BrdDen <> CInt(dbcBrdDen) Then 'Equal to dbcBrdBas?
            blnFail = True 'Failed.
            Exit For
         End If
      End With
   Next
   If blnFail Then 'Message & focus.
      strPromt = LoadResString(412) & Util.CutColonAmpers(lblBrdDen.Caption) & _
         LoadResString(416)
      MsgBox strPromt, vbExclamation, LoadResString(131)
      dbcBrdDen.SetFocus
   Else 'Succeeded.
      VldBrdDen = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the format string to format breed numerators in the lvwBrdCrs list. The format
'  string is based on the maximal numerator's length.
Private Function FormtSort() As String
On Error GoTo ErrHnd
   Dim intMaxLeng As Integer
   intMaxLeng = Len(CStr(gobSetng.BrdCrsMaxDen - 1)) 'The max numerator's length.
   FormtSort = String$(intMaxLeng - 1, "0") & "#"
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the numerators so that their sum be equal to the denominator.
' Return True, if succeeds.
Private Function VldBrdNum() As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim intSum As Integer
   Dim strPromt As String
   With mobShGTest.TblShG
      For Each obTblBrdCrs In .BrdCrsesNew 'Loop to sum.
         intSum = intSum + obTblBrdCrs.BrdNum
      Next
      If intSum = .BrdCrsDenNew Then
         VldBrdNum = True 'Succeeded.
      Else
         strPromt = LoadResString(417) & intSum & LoadResString(418) & .BrdCrsDenNew & _
            ")."
         MsgBox strPromt, vbExclamation, LoadResString(131)
         lvwBrdCrs.SetFocus
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the basic breed's share that must be present among the selected breeds & be
'  the biggest or a half.
' Return True, if succeeds.
Private Function VldBrdBas() As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim intBrdNumBas As Integer
   Dim intBrdNumMax As Integer
   Dim blnFail As Boolean
   Dim strPromt As String
   For Each obTblBrdCrs In mobShGTest.TblShG.BrdCrsesNew 'Look for the basic breed.
      With obTblBrdCrs
         If intBrdNumMax < .BrdNum Then intBrdNumMax = .BrdNum 'Define the max numerator.
         If .IDBrd = dbcBrdBas.BoundText Then intBrdNumBas = .BrdNum 'Basic breed numerator.
      End With
   Next
   If intBrdNumBas = 0 Then 'No basic breed?
      blnFail = True
      strPromt = LoadResString(419) & dbcBrdBas & LoadResString(420)
   Else 'Proceed, if basic breed is present.
      If intBrdNumBas < intBrdNumMax Then 'Basic breed numerator smaller than max?
         blnFail = True
         strPromt = LoadResString(421) & intBrdNumBas & LoadResString(422) & dbcBrdBas _
            & LoadResString(423) & dbcBrdDen & ")."
      End If
   End If
   If blnFail Then 'Message & focus.
      MsgBox strPromt, vbExclamation, LoadResString(131)
      lvwBrdCrs.SetFocus
   Else 'Succeeded.
      VldBrdBas = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Message about the missing bacic breed & focus the dbcBrdBas datacombo if enabled.
'  Otherwise focus the dbcBrdDen combo next to the former.
' The dbcBrdBas datacombo is disabled, if the form is loaded from the TblOffsp class.
Private Sub MsgFocBrdBas()
On Error GoTo ErrHnd
   MsgBox LoadResString(410), vbExclamation, LoadResString(131)
   If dbcBrdBas.Enabled Then
      dbcBrdBas.SetFocus
   Else
      dbcBrdDen.SetFocus
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Limit the number of cross breed shares up to 6.
' If added, i.e. blnAddVsOk = True, the maximum number of inputted so far shares is 5 to
'  accomodate 1 more up to 6. If saved, i.e. blnAddVsOk = False, the maximum to validate
'  according to is 6.
' Return True, if succeeds.
Private Function LimitMaxShare(ByVal blnAddVsOk As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If blnAddVsOk And lvwBrdCrs.ListItems.Count < gobSetng.BrdCrsMaxShare Then
      LimitMaxShare = True 'Succeeded.
   ElseIf blnAddVsOk = False And lvwBrdCrs.ListItems.Count <= gobSetng.BrdCrsMaxShare Then
      LimitMaxShare = True 'Succeeded.
   Else
      strPromt = LoadResString(424) & gobSetng.BrdCrsMaxShare & "."
      MsgBox strPromt, vbExclamation, LoadResString(131)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
