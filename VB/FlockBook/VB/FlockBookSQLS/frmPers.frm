VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmPers 
   Caption         =   "Участники"
   ClientHeight    =   6045
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9840
   DrawMode        =   14  'Copy Pen
   Icon            =   "frmPers.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   6045
   ScaleWidth      =   9840
   Begin TabDlg.SSTab tabFarmerCont 
      Height          =   1635
      Left            =   5640
      TabIndex        =   15
      Top             =   3600
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   2884
      _Version        =   393216
      Style           =   1
      Tabs            =   2
      TabHeight       =   520
      TabCaption(0)   =   "Фермер"
      TabPicture(0)   =   "frmPers.frx":1042
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "dgdFarmFarmer"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "adoFarmFarmer"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "Контактное лицо"
      TabPicture(1)   =   "frmPers.frx":105E
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "adoFarmCont"
      Tab(1).Control(1)=   "dgdFarmCont"
      Tab(1).ControlCount=   2
      Begin MSAdodcLib.Adodc adoFarmCont 
         Height          =   330
         Left            =   -74880
         Top             =   1080
         Visible         =   0   'False
         Width           =   3765
         _ExtentX        =   6641
         _ExtentY        =   582
         ConnectMode     =   0
         CursorLocation  =   3
         IsolationLevel  =   -1
         ConnectionTimeout=   15
         CommandTimeout  =   30
         CursorType      =   3
         LockType        =   3
         CommandType     =   4
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
         Caption         =   "adoFarmCont"
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
      Begin MSDataGridLib.DataGrid dgdFarmCont 
         Height          =   1095
         Left            =   -74940
         TabIndex        =   17
         TabStop         =   0   'False
         Top             =   360
         Width           =   3825
         _ExtentX        =   6747
         _ExtentY        =   1931
         _Version        =   393216
         AllowUpdate     =   0   'False
         HeadLines       =   1
         RowHeight       =   15
         BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ColumnCount     =   2
         BeginProperty Column00 
            DataField       =   ""
            Caption         =   ""
            BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
               Type            =   0
               Format          =   ""
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1049
               SubFormatType   =   0
            EndProperty
         EndProperty
         BeginProperty Column01 
            DataField       =   ""
            Caption         =   ""
            BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
               Type            =   0
               Format          =   ""
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1049
               SubFormatType   =   0
            EndProperty
         EndProperty
         SplitCount      =   1
         BeginProperty Split0 
            ScrollBars      =   2
            BeginProperty Column00 
            EndProperty
            BeginProperty Column01 
            EndProperty
         EndProperty
      End
      Begin MSAdodcLib.Adodc adoFarmFarmer 
         Height          =   330
         Left            =   120
         Top             =   1080
         Visible         =   0   'False
         Width           =   3765
         _ExtentX        =   6641
         _ExtentY        =   582
         ConnectMode     =   0
         CursorLocation  =   3
         IsolationLevel  =   -1
         ConnectionTimeout=   15
         CommandTimeout  =   30
         CursorType      =   3
         LockType        =   3
         CommandType     =   4
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
         Caption         =   "adoFarmFarmer"
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
      Begin MSDataGridLib.DataGrid dgdFarmFarmer 
         Height          =   1095
         Left            =   60
         TabIndex        =   16
         TabStop         =   0   'False
         Top             =   360
         Width           =   3825
         _ExtentX        =   6747
         _ExtentY        =   1931
         _Version        =   393216
         AllowUpdate     =   0   'False
         HeadLines       =   1
         RowHeight       =   15
         BeginProperty HeadFont {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ColumnCount     =   2
         BeginProperty Column00 
            DataField       =   ""
            Caption         =   ""
            BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
               Type            =   0
               Format          =   ""
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1049
               SubFormatType   =   0
            EndProperty
         EndProperty
         BeginProperty Column01 
            DataField       =   ""
            Caption         =   ""
            BeginProperty DataFormat {6D835690-900B-11D0-9484-00A0C91110ED} 
               Type            =   0
               Format          =   ""
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1049
               SubFormatType   =   0
            EndProperty
         EndProperty
         SplitCount      =   1
         BeginProperty Split0 
            ScrollBars      =   2
            BeginProperty Column00 
            EndProperty
            BeginProperty Column01 
            EndProperty
         EndProperty
      End
   End
   Begin VB.PictureBox picBtn 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   735
      Left            =   0
      ScaleHeight     =   735
      ScaleWidth      =   9840
      TabIndex        =   18
      TabStop         =   0   'False
      Top             =   5310
      Width           =   9840
      Begin VB.CommandButton cmdOk 
         Caption         =   "&ОК"
         Height          =   375
         Left            =   6840
         TabIndex        =   19
         Top             =   240
         Width           =   1215
      End
      Begin VB.CommandButton cmdCancel 
         Cancel          =   -1  'True
         Caption         =   "Отмена"
         Height          =   375
         Left            =   8160
         TabIndex        =   20
         Top             =   240
         Width           =   1215
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000005&
         Index           =   1
         X1              =   0
         X2              =   10905
         Y1              =   15
         Y2              =   15
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000010&
         Index           =   0
         X1              =   0
         X2              =   10905
         Y1              =   0
         Y2              =   0
      End
   End
   Begin MSAdodcLib.Adodc adoNamBrs 
      Height          =   330
      Left            =   240
      Top             =   4800
      Visible         =   0   'False
      Width           =   3135
      _ExtentX        =   5530
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   4
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
      RecordSource    =   "spSelect_Persons_Dbc"
      Caption         =   "adoNamBrs"
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
   Begin MSDataListLib.DataList dblNamBrs 
      Height          =   4740
      Left            =   240
      TabIndex        =   1
      Top             =   480
      Width           =   3135
      _ExtentX        =   5530
      _ExtentY        =   8361
      _Version        =   393216
   End
   Begin VB.TextBox txtEmail 
      Height          =   315
      Left            =   5640
      MaxLength       =   50
      TabIndex        =   11
      Top             =   2400
      Width           =   3975
   End
   Begin VB.TextBox txtPhone 
      Height          =   315
      Left            =   5640
      MaxLength       =   50
      TabIndex        =   9
      Top             =   1920
      Width           =   3975
   End
   Begin VB.TextBox txtAddress 
      Height          =   495
      Left            =   5640
      MaxLength       =   150
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   7
      Top             =   1200
      Width           =   3975
   End
   Begin VB.TextBox txtNam 
      Height          =   315
      Left            =   5640
      MaxLength       =   100
      TabIndex        =   3
      ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
      Top             =   240
      Width           =   3975
   End
   Begin VB.TextBox txtRemark 
      Height          =   495
      Left            =   5640
      MaxLength       =   150
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   13
      Top             =   2880
      Width           =   3975
   End
   Begin MSDataListLib.DataCombo dbcTwnVll 
      Height          =   315
      Left            =   5640
      TabIndex        =   5
      ToolTipText     =   "F4 - Открыть список"
      Top             =   720
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoTwnVll 
      Height          =   330
      Left            =   5640
      Top             =   960
      Visible         =   0   'False
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   3
      CommandType     =   4
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
      RecordSource    =   "spSelect_TownVill_Dbc"
      Caption         =   "adoTwnVll"
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
      Caption         =   "&Фермы с участни- ком в качестве фермера или кон- тактного лица:"
      Height          =   855
      Left            =   3840
      TabIndex        =   14
      Top             =   3600
      Width           =   1575
   End
   Begin VB.Label lblNamBrs 
      Caption         =   "В&ыберите участника:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1695
   End
   Begin VB.Label lblEmail 
      Caption         =   "&Email:"
      Height          =   255
      Left            =   3840
      TabIndex        =   10
      Top             =   2400
      Width           =   495
   End
   Begin VB.Label lblPhone 
      Caption         =   "&Телефон:"
      Height          =   255
      Left            =   3840
      TabIndex        =   8
      Top             =   1920
      Width           =   855
   End
   Begin VB.Label lblAddress 
      Caption         =   "&Адрес:"
      Height          =   255
      Left            =   3840
      TabIndex        =   6
      Top             =   1200
      Width           =   615
   End
   Begin VB.Label lblNam 
      Caption         =   "&Участник:"
      Height          =   255
      Left            =   3840
      TabIndex        =   2
      Top             =   240
      Width           =   855
   End
   Begin VB.Label lblRemark 
      Caption         =   "&Заметки:"
      Height          =   255
      Left            =   3840
      TabIndex        =   12
      Top             =   2880
      Width           =   855
   End
   Begin VB.Label lblTwnVll 
      Caption         =   "&Населённый пункт:"
      Height          =   375
      Left            =   3840
      TabIndex        =   4
      Top             =   690
      Width           =   1575
   End
End
Attribute VB_Name = "frmPers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Implements MsgRecip
Implements DatFrm
Implements SetngFrm

Const mintTab0 As Integer = 0 'Tab 0 index.

Dim mcolMsgs As Collection
Dim mobTblPers As TblPers
Dim mobDatFrm As DatFrm
Dim mobUtilDatFrm As UtilDatFrm

Dim mstrIDFrm As String
Dim mstrFrmHostNam As String
Dim mstrFrmHostCapt As String
Dim mintMode As Integer
Dim mblnIsDirty As Boolean

' Unload the form, if it's clear.
' Cancel the changes.
' Clear the controls.
' Return the focus to txtNam
Public Sub cmdCancel_Click()
On Error GoTo ErrHnd
   mobUtilDatFrm.Cancel_Click dblNamBrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtNam.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   mobUtilDatFrm.Ok_Click dblNamBrs, LoadResString(298)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear controls.
Private Sub DatFrm_CtlClear()
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_CtlClear
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the form's controls.
Private Sub DatFrm_CtlWrite()
On Error GoTo ErrHnd
   With mobTblPers
      dbcTwnVll.BoundText = .IDTwnVll
      txtAddress = .Address
      txtPhone = .Phone
      txtEmail = .Email
      txtRemark = .Remark
   End With
   Call GridRecSrc 'Set adoFarmFarmer's record source.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the data from the form's controls.
Private Sub DatFrm_CtlRead()
On Error GoTo ErrHnd
   With mobTblPers
      .Nam = Trim$(txtNam)
      .IDTwnVll = CLng(Util.DbcReadBoundTxt(dbcTwnVll, adoTwnVll))
      .Address = Trim$(txtAddress)
      .Phone = Trim$(txtPhone)
      .Email = Trim$(txtEmail)
      .Remark = Trim$(txtRemark)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Link to Me.
Private Property Get DatFrm_FrmHost() As Form
   Set DatFrm_FrmHost = Me
End Property

' Let & get the hosting form name.
Private Property Let DatFrm_FrmHostNam(ByVal strFrmHostNam As String)
    mstrFrmHostNam = strFrmHostNam
End Property

' Get the host form's name.
Private Property Get DatFrm_FrmHostNam() As String
    DatFrm_FrmHostNam = mstrFrmHostNam
End Property

' Get the ID control.
Private Property Get DatFrm_IDCtl() As TextBox
   Set DatFrm_IDCtl = txtNam
End Property

' Let & IDShG to identify this data form.
Private Property Let DatFrm_IDFrm(ByVal strIDFrm As String)
    mstrIDFrm = strIDFrm
End Property

' Get IDFrm to identify this data form.
Private Property Get DatFrm_IDFrm() As String
    DatFrm_IDFrm = mstrIDFrm
End Property

' Implements or not the SetngFrm class.
Private Property Get DatFrm_IsSetngFrm() As Boolean
   DatFrm_IsSetngFrm = True
End Property

' Register the data form itself under a new ID. Delete it under the previous ID, if any,
'  & register under a new one.
Private Sub DatFrm_RegistFrm(ByVal strNewIDFrm As String, ByVal blnDelPrev As Boolean)
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   Dim obDatTbl As DatTbl
   If Not blnPassed Then 'Execute once.
      blnPassed = True
      Set mobDatFrm = Me
      Set mobTblPers = New TblPers
      Set obDatTbl = mobTblPers
      Set mobUtilDatFrm = New UtilDatFrm
      mobUtilDatFrm.InitCls Me, obDatTbl ', mblnFrmFilld ', mblnSwch 'Initialise
   End If                                                          'mobUtilDatFrm.
   mobUtilDatFrm.DatFrm_RegistFrm strNewIDFrm, blnDelPrev
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Shwitch on/off the data form's controls depending on whether the txtNam is filled.
Private Sub DatFrm_SwchCtlFill(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_SwchCtlFill blnEnable, blnEnableID, lblNam.Name, lblNamBrs _
      .Name, dblNamBrs.Name
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
' Switch the controls to save a new ID.
Private Sub DatFrm_SwchCtlMode()
On Error GoTo ErrHnd
   With mobUtilDatFrm
      .DatFrm_SwchCtlMode lblNamBrs.Name, dblNamBrs.Name, dbcTwnVll.Name
      .SwchGridMode dgdFarmFarmer 'Disable the grids in the Add mode.
      .SwchGridMode dgdFarmCont
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function DatFrm_Vld() As Boolean
On Error GoTo ErrHnd
   If dbcTwnVll.BoundText = "" Then 'Define the town/village.
      Call Util.MissParam(dbcTwnVll, lblTwnVll) 'Message & focus.
   Else
      DatFrm_Vld = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Enable Del.
' Enable Esc.
Private Sub dbcTwnVll_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
         dbcTwnVll.BoundText = ""
      Case .CodeEsc
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Syncronise the txtNam with this control.
Private Sub dblNamBrs_Click()
On Error GoTo ErrHnd
   txtNam = dblNamBrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter.
' Avoid opening another duplicate data form by ivoking the LostFocus procedure.
Private Sub dblNamBrs_DblClick()
On Error GoTo ErrHnd
   Call Util.IDCtlEnter(mobDatFrm, gobFormtCtl.AscEnter)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Call the txtNam_KeyPress procedure in the Edit/Del mode, if Enter is pressed.
Private Sub dblNamBrs_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   Call Util.IDCtlEnter(mobDatFrm, KeyAscii)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the Edit tool bar's buttons & the Edit menu.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   Call frmMDI.SwchMnuMode(mobDatFrm.Mode) ', IsDirty)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the relevant to data form forms menu's & tool bar's items.
Private Sub Form_Deactivate()
On Error GoTo ErrHnd
   Call frmMDI.SwchMnuMode(gobSetng.ModeOff)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the form's controls & variables.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Const lngWdth As Long = 9960 '9720 '9150
   Const lngHght As Long = 6450 '6570
   Set mcolMsgs = New Collection 'Create a new mcolMsgs object.
   mobDatFrm.SwchCtlFill False, True
   mobDatFrm.FrmHostCaptOrig = Me.Caption
   Call InitCtl 'Initialise controls.
   txtNam = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID.
   Call frmMDI.SwchMnuWin(True)  'Switch the menu & toolbar buttons.
   Call frmMDI.WinPosn(Me, lngWdth, lngHght) 'Place the the window & adjust its size.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub Form_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the window state, if changed.
' Resize controls & move the buttons.
Private Sub Form_Resize()
On Error GoTo ErrHnd
   With mobUtilDatFrm
      .Form_Resize dblNamBrs
      .TabResize tabFarmerCont, dgdFarmFarmer, dgdFarmCont
   End With
'   txtNam.Width = txtRemark.Width 'Change txtNam/txtAddress's width.
   txtAddress.Width = txtRemark.Width
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current data form from the DatFrms collection.
' Reset the relevant to windows & data form forms menu's & tool bar's items.
' Reset the gobMsgInst object.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   With mobDatFrm
      gobDatFrms.Del .IDFrm, .FrmHostNam 'Delete the data form.
   End With
   Call frmMDI.SwchMnuWin(False) 'Switch the buttons.
   Call frmMDI.SwchMnuMode(gobSetng.ModeOff)
   gobMsgInst.Rest Me 'Reset gobMsgInst.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cancel the current changes.
' Switch controls.
' Nullify this data form's marks.
' Re-register the data form under zero-length-string ID.
' Switch the menu & toolbar.
' Reset the gobMsgInst object.
Private Sub DatFrm_Cancel(ByVal blnCtlClear As Boolean)
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_Cancel blnCtlClear ', mblnFrmFilld
   Call GridRecSrc 'Reset adoFarmFarmer's record source.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the mobTblPers object.
Private Sub DatFrm_FrmToDB()
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_FrmToDB LoadResString(280), LoadResString(319)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Get DatFrm_Mode() As Integer
   DatFrm_Mode = mintMode
End Property

' Set the form's mode to the specified option unless there is unsaved data.
Private Sub DatFrm_ModeSet(ByVal intMode As Integer)
On Error GoTo ErrHnd
   mintMode = intMode
   Call frmMDI.SwchMnuMode(intMode) ', IsDirty)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mcolMsgs collection to the gobMsgInst object to read/write messages to the form
Private Property Get MsgRecip_Msgs() As Collection
   Set MsgRecip_Msgs = mcolMsgs
End Property

Private Sub tabPersFarm_DblClick()

End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub tabPersFarm_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
   As Single)
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let SetngFrm_RefrshResm(ByVal RHS As Boolean)

End Property

Private Property Get SetngFrm_RefrshResm() As Boolean

End Property

Private Property Let SetngFrm_RefrshSusp(ByVal RHS As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Property Get SetngFrm_RefrshSusp() As Boolean
'If necessary modify the code to use this procedure.
End Property

' Switch on the active tab's grid's TabStop & switch off the previous tab's.
Private Sub tabFarmerCont_Click(PreviousTab As Integer)
On Error GoTo ErrHnd
   Call SwchTabStop(tabFarmerCont.Tab, True) 'The active tab's on.
   Call SwchTabStop(PreviousTab, False) 'The previous tab's off.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtEmail_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtEmail
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtEmail_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtTxtUnfoc txtEmail
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter.
Private Sub txtNam_DblClick()
On Error GoTo ErrHnd
   mobDatFrm.IDCtlPress gobFormtCtl.AscEnter
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtNam_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtNam
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub txtNam_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   mobDatFrm.IDCtlPress KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Prevent a duplication.
' Reset the gobMsgInst object for later use.
' Unless the Util.DuplFrmtRest procedure unloads the form complete switching the
'  controls in the Edit mode after filling the form to restrict the access to the this
'  control until saving or canceling.
Private Sub txtNam_LostFocus()
On Error GoTo ErrHnd
   mobUtilDatFrm.IDCtl_LostFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the DB to fill this form.
Private Sub DatFrm_DBtoFrm()
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_DBtoFrm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form's controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   adoNamBrs.ConnectionString = gcnnConnServ.ConnectionString 'adoNamBrs & dblNamBrs.
   With dblNamBrs
      Set .RowSource = adoNamBrs
      .BoundColumn = "IDPers"
      .ListField = "Nam"
   End With
   adoFarmFarmer.ConnectionString = gcnnConnServ.ConnectionString
   adoFarmCont.ConnectionString = gcnnConnServ.ConnectionString
   Call GridRecSrc 'Set adoFarmFarmer/adoFarmCont's record source.
   Set dgdFarmFarmer.DataSource = adoFarmFarmer 'Set the grids' data source.
   Set dgdFarmCont.DataSource = adoFarmCont
   adoTwnVll.ConnectionString = gcnnConnServ.ConnectionString 'adoTwnVll & dbcTwnVll
   With dbcTwnVll
      Set .RowSource = adoTwnVll
      .BoundColumn = "IDTownVill"
      .ListField = "TownVill"
   End With
   tabFarmerCont.Tab = mintTab0 'Select the 1st tab.
   Call SwchTabStop(mintTab0, True) 'Switch the 1st tab's grid's TabStop.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the adoFarmFarmer/adoFarmCont control's record source.
Private Sub GridRecSrc()
On Error GoTo ErrHnd
   With mobUtilDatFrm
      .GridRecSrc adoFarmFarmer, "spSelect_Farms_GridFarmer('" & mobDatFrm.IDFrm & _
         "')", dgdFarmFarmer
      .GridRecSrc adoFarmCont, "spSelect_Farms_GridCont('" & mobDatFrm.IDFrm & "')", _
         dgdFarmCont
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display the File menu as a pop-up menu.
Private Sub picBtn_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus, if the field is left blank in the Edit mode after changing the ID.
Private Sub txtNam_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   mobUtilDatFrm.IDCtl_Validate Cancel, lblNam
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtPhone_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtPhone
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtPhone_LostFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.FormtTxtUnfoc txtPhone
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh all settings-relevant Ado's.
Private Sub SetngFrm_RefrshAdo()
On Error GoTo ErrHnd
   adoNamBrs.Refresh
   adoTwnVll.Refresh
   adoFarmFarmer.Refresh
   adoFarmCont.Refresh
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Syncronise the browsing list with the ID control.
Private Sub SetngFrm_SyncBrs()
On Error GoTo ErrHnd
   dblNamBrs.Text = txtNam
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Let & get IsDirty.
Private Property Let DatFrm_IsDirty(ByVal blnIsDirty As Boolean)
   mblnIsDirty = blnIsDirty
End Property

Private Property Get DatFrm_IsDirty() As Boolean
   DatFrm_IsDirty = mblnIsDirty
End Property

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub DatFrm_IDCtlPress(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   mobUtilDatFrm.IDCtl_KeyPress intKeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Prevent a duplication.
' Reset the gobMsgInst object for later use.
' Unless the Util.DuplFrmtRest procedure unloads the form complete switching the
'  controls in the Edit mode after filling the form to restrict the access to the this
'  control until saving or canceling.
Private Sub DatFrm_IDCtlLostFoc()
On Error GoTo ErrHnd
   mobUtilDatFrm.IDCtl_LostFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified tab's grid's TabStop.
Private Sub SwchTabStop(ByVal intIdx As Integer, ByVal blnTabStop As Boolean)
On Error GoTo ErrHnd
   Const intTab1 As Integer = 1
   Select Case intIdx 'Select the active tab.
   Case mintTab0
      dgdFarmFarmer.TabStop = blnTabStop
   Case intTab1
      dgdFarmCont.TabStop = blnTabStop
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' The form's caption.
Private Property Get DatFrm_FrmHostCaptOrig() As String
   DatFrm_FrmHostCaptOrig = mstrFrmHostCapt
End Property

' The form's caption.
Private Property Let DatFrm_FrmHostCaptOrig(ByVal strFrmHostCapt As String)
   mstrFrmHostCapt = strFrmHostCapt
End Property

