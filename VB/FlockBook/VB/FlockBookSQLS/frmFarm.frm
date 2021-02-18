VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmFarm 
   Caption         =   "Фермы"
   ClientHeight    =   6150
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9510
   DrawMode        =   14  'Copy Pen
   Icon            =   "frmFarm.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   6150
   ScaleWidth      =   9510
   Begin VB.TextBox txtFarm 
      Height          =   315
      Left            =   4320
      MaxLength       =   2
      TabIndex        =   3
      ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
      Top             =   240
      Width           =   975
   End
   Begin VB.PictureBox picBtn 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   735
      Left            =   0
      ScaleHeight     =   735
      ScaleWidth      =   9510
      TabIndex        =   17
      TabStop         =   0   'False
      Top             =   5415
      Width           =   9510
      Begin VB.CommandButton cmdOk 
         Caption         =   "&ОК"
         Height          =   375
         Left            =   6720
         TabIndex        =   18
         Top             =   240
         Width           =   1215
      End
      Begin VB.CommandButton cmdCancel 
         Cancel          =   -1  'True
         Caption         =   "Отмена"
         Height          =   375
         Left            =   8040
         TabIndex        =   19
         Top             =   240
         Width           =   1215
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000005&
         Index           =   1
         X1              =   0
         X2              =   10335
         Y1              =   15
         Y2              =   15
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000010&
         Index           =   0
         X1              =   0
         X2              =   10335
         Y1              =   0
         Y2              =   0
      End
   End
   Begin VB.TextBox txtRemark 
      Height          =   495
      Left            =   4320
      MaxLength       =   150
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   11
      Top             =   2160
      Width           =   4935
   End
   Begin MSDataListLib.DataCombo dbcTwnVll 
      Height          =   315
      Left            =   4320
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
      Left            =   4320
      Top             =   840
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
   Begin MSDataListLib.DataCombo dbcPersFarm 
      Height          =   315
      Left            =   4320
      TabIndex        =   7
      ToolTipText     =   "F4 - Открыть список"
      Top             =   1200
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoPersFarm 
      Height          =   330
      Left            =   4320
      Top             =   1320
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
      RecordSource    =   "spSelect_Persons_Dbc"
      Caption         =   "adoPersFarm"
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
   Begin MSDataListLib.DataCombo dbcPersCont 
      Height          =   315
      Left            =   4320
      TabIndex        =   9
      ToolTipText     =   "F4 - Открыть список"
      Top             =   1680
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoPersCont 
      Height          =   330
      Left            =   4320
      Top             =   1800
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
      RecordSource    =   "spSelect_Persons_Dbc"
      Caption         =   "adoPersCont"
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
   Begin MSAdodcLib.Adodc adoFarmBrs 
      Height          =   330
      Left            =   240
      Top             =   4920
      Visible         =   0   'False
      Width           =   1845
      _ExtentX        =   3254
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
      RecordSource    =   "spSelect_Farms_Dbc"
      Caption         =   "adoFarmBrs"
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
   Begin MSDataListLib.DataList dblFarmBrs 
      Height          =   4935
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   1845
      _ExtentX        =   3254
      _ExtentY        =   8705
      _Version        =   393216
   End
   Begin TabDlg.SSTab tabShG 
      Height          =   2415
      Left            =   4320
      TabIndex        =   13
      Top             =   2880
      Width           =   4935
      _ExtentX        =   8705
      _ExtentY        =   4260
      _Version        =   393216
      Style           =   1
      TabHeight       =   520
      TabCaption(0)   =   "Находящиеся"
      TabPicture(0)   =   "frmFarm.frx":1042
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "dgdShG"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "adoShG"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "Рождённые"
      TabPicture(1)   =   "frmFarm.frx":105E
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "adoShGBorn"
      Tab(1).Control(1)=   "dgdShGBorn"
      Tab(1).ControlCount=   2
      TabCaption(2)   =   "Проданные"
      TabPicture(2)   =   "frmFarm.frx":107A
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "adoShGTrans"
      Tab(2).Control(1)=   "dgdShGTrans"
      Tab(2).ControlCount=   2
      Begin MSAdodcLib.Adodc adoShG 
         Height          =   330
         Left            =   120
         Top             =   2040
         Visible         =   0   'False
         Width           =   4725
         _ExtentX        =   8334
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
         Caption         =   "adoShG"
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
      Begin MSDataGridLib.DataGrid dgdShG 
         Height          =   1575
         Left            =   60
         TabIndex        =   14
         TabStop         =   0   'False
         Top             =   360
         Width           =   4815
         _ExtentX        =   8493
         _ExtentY        =   2778
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
            BeginProperty Column00 
            EndProperty
            BeginProperty Column01 
            EndProperty
         EndProperty
      End
      Begin MSAdodcLib.Adodc adoShGBorn 
         Height          =   330
         Left            =   -74880
         Top             =   2040
         Visible         =   0   'False
         Width           =   4725
         _ExtentX        =   8334
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
         Caption         =   "adoShGBorn"
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
      Begin MSDataGridLib.DataGrid dgdShGBorn 
         Height          =   1575
         Left            =   -74940
         TabIndex        =   15
         TabStop         =   0   'False
         Top             =   360
         Width           =   4815
         _ExtentX        =   8493
         _ExtentY        =   2778
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
            BeginProperty Column00 
            EndProperty
            BeginProperty Column01 
            EndProperty
         EndProperty
      End
      Begin MSAdodcLib.Adodc adoShGTrans 
         Height          =   330
         Left            =   -74880
         Top             =   2040
         Visible         =   0   'False
         Width           =   4725
         _ExtentX        =   8334
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
         Caption         =   "adoShGTrans"
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
      Begin MSDataGridLib.DataGrid dgdShGTrans 
         Height          =   1575
         Left            =   -74940
         TabIndex        =   16
         TabStop         =   0   'False
         Top             =   360
         Width           =   4815
         _ExtentX        =   8493
         _ExtentY        =   2778
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
            BeginProperty Column00 
            EndProperty
            BeginProperty Column01 
            EndProperty
         EndProperty
      End
   End
   Begin VB.Label lblFarmBrs 
      Caption         =   "В&ыберите ферму:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin VB.Label lblShG 
      Caption         =   "&Животные, находя- щиеся/рождённые на ферме или про- данные на ферму:"
      Height          =   855
      Left            =   2520
      TabIndex        =   12
      Top             =   2880
      Width           =   1575
   End
   Begin VB.Label lblPersCont 
      Caption         =   "&Контактное лицо:"
      Height          =   255
      Left            =   2520
      TabIndex        =   8
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Label lblPersFarm 
      Caption         =   "Ф&ермер:"
      Height          =   255
      Left            =   2520
      TabIndex        =   6
      Top             =   1200
      Width           =   735
   End
   Begin VB.Label lblFarm 
      Caption         =   "Код &фермы:"
      Height          =   255
      Left            =   2520
      TabIndex        =   2
      Top             =   240
      Width           =   975
   End
   Begin VB.Label lblRemark 
      Caption         =   "&Заметки:"
      Height          =   255
      Left            =   2520
      TabIndex        =   10
      Top             =   2160
      Width           =   855
   End
   Begin VB.Label lblTwnVll 
      Caption         =   "&Населённый пункт:"
      Height          =   255
      Left            =   2520
      TabIndex        =   4
      Top             =   720
      Width           =   1575
   End
End
Attribute VB_Name = "frmFarm"
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
Dim mobTblFarm As TblFarm
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
' Return the focus to txtFarm
Public Sub cmdCancel_Click()
On Error GoTo ErrHnd
   mobUtilDatFrm.Cancel_Click dblFarmBrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtFarm.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   mobUtilDatFrm.Ok_Click dblFarmBrs, LoadResString(299)
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
   With mobTblFarm
      dbcTwnVll.BoundText = .IDTwnVll
      dbcPersFarm.BoundText = .IDPersFarm
      dbcPersCont.BoundText = .IDPersCont
      txtRemark = .Remark
   End With
   Call GridRecSrc 'Set Ado's record source.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the data from the form's controls.
Private Sub DatFrm_CtlRead()
On Error GoTo ErrHnd
   With mobTblFarm
      .IDFarm = txtFarm
      .IDTwnVll = CLng(Util.DbcReadBoundTxt(dbcTwnVll, adoTwnVll))
      .IDPersFarm = CLng(Util.DbcReadBoundTxt(dbcPersFarm, adoPersFarm))
      If dbcPersCont.BoundText <> "" Then 'IDPersCont value or zero value.
      .IDPersCont = CLng(Util.DbcReadBoundTxt(dbcPersCont, adoPersCont))
      Else
         .IDPersCont = 0
      End If
      .Remark = txtRemark
   End With
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
   Set DatFrm_IDCtl = txtFarm
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

' Let & IDShG to identify this data form.
Private Property Let DatFrm_IDFrm(ByVal strIDFrm As String)
    mstrIDFrm = strIDFrm
End Property

' Get IDFrm to identify this data form.
Private Property Get DatFrm_IDFrm() As String
    DatFrm_IDFrm = mstrIDFrm
End Property

' Let & get IsDirty.
Private Property Let DatFrm_IsDirty(ByVal blnIsDirty As Boolean)
   mblnIsDirty = blnIsDirty
End Property

Private Property Get DatFrm_IsDirty() As Boolean
   DatFrm_IsDirty = mblnIsDirty
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
      Set mobTblFarm = New TblFarm
      Set obDatTbl = mobTblFarm
      Set mobUtilDatFrm = New UtilDatFrm
      mobUtilDatFrm.InitCls Me, obDatTbl ', mblnFrmFilld ', mblnSwch 'Initialise
   End If                                                          'mobUtilDatFrm.
   mobUtilDatFrm.DatFrm_RegistFrm strNewIDFrm, blnDelPrev
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Shwitch on/off the data form's controls depending on whether the txtFarm is filled.
Private Sub DatFrm_SwchCtlFill(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_SwchCtlFill blnEnable, blnEnableID, lblFarm.Name, lblFarmBrs _
      .Name, dblFarmBrs.Name
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
' Switch the controls to save a new ID.
Private Sub DatFrm_SwchCtlMode()
On Error GoTo ErrHnd
   With mobUtilDatFrm
      .DatFrm_SwchCtlMode lblFarmBrs.Name, dblFarmBrs.Name, dbcTwnVll.Name
      .SwchGridMode dgdShG 'Disable the grids in the Add mode.
      .SwchGridMode dgdShGBorn
      .SwchGridMode dgdShGTrans
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
   ElseIf dbcPersFarm.BoundText = "" Then 'Define the farmer.
      Call Util.MissParam(dbcPersFarm, lblPersFarm) 'Message & focus.
   Else
      DatFrm_Vld = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Enable Del.
' Enable Esc.
Private Sub dbcPersCont_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
'   If KeyCode = gobFormtCtl.CodeEsc Then Call cmdCancel_Click
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
Debug.Assert 0 = 1 'Verify
         dbcPersCont.BoundText = ""
      Case .CodeEsc
Debug.Assert 0 = 1 'Verify
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Esc.
' Enable Del.
Private Sub dbcPersFarm_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
'   If KeyCode = gobFormtCtl.CodeEsc Then Call cmdCancel_Click
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
Debug.Assert 0 = 1 'Verify
         dbcPersFarm.BoundText = ""
      Case .CodeEsc
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del.
' Enable Esc.
Private Sub dbcTwnVll_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
Debug.Assert 0 = 1 'Verify
         dbcTwnVll.BoundText = ""
      Case .CodeEsc
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Syncronise the txtObl with this control.
Private Sub dblFarmBrs_Click()
On Error GoTo ErrHnd
   txtFarm = dblFarmBrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter.
' Avoid opening another duplicate data form by ivoking the LostFocus procedure.
Private Sub dblFarmBrs_DblClick()
On Error GoTo ErrHnd
   Call Util.IDCtlEnter(mobDatFrm, gobFormtCtl.AscEnter)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Call the txtObl_KeyPress procedure in the Edit/Del mode, if Enter is pressed.
Private Sub dblFarmBrs_KeyPress(KeyAscii As Integer)
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
   Const lngWdth As Long = 9630 '10335 '9420
   Const lngHght As Long = 6555 '6675
   Set mcolMsgs = New Collection 'Create a new mcolMsgs object.
   mobDatFrm.SwchCtlFill False, True
   mobDatFrm.FrmHostCaptOrig = Me.Caption
   Call InitCtl 'Initialise controls.
   txtFarm = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID.
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
      .Form_Resize dblFarmBrs
      .TabResize tabShG, dgdShG, dgdShGBorn, dgdShGTrans
   End With
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
   mobUtilDatFrm.DatFrm_Cancel blnCtlClear
   Call GridRecSrc 'Set Ado's record source.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the mobTblFarm object.
Private Sub DatFrm_FrmToDB()
On Error GoTo ErrHnd
   mobUtilDatFrm.DatFrm_FrmToDB LoadResString(281), LoadResString(311)
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

' Refresh all settings-relevant Ado's.
Private Sub SetngFrm_RefrshAdo()
On Error GoTo ErrHnd
   adoFarmBrs.Refresh
   adoTwnVll.Refresh
   adoPersFarm.Refresh
   adoPersCont.Refresh
   adoShG.Refresh
   adoShGBorn.Refresh
   adoShGTrans.Refresh
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let SetngFrm_RefrshResm(ByVal RHS As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Property Get SetngFrm_RefrshResm() As Boolean
'If necessary modify the code to use this procedure.
End Property

' Syncronise the browsing list with the ID control.
Private Sub SetngFrm_SyncBrs()
On Error GoTo ErrHnd
   dblFarmBrs.Text = txtFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let SetngFrm_RefrshSusp(ByVal RHS As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Property Get SetngFrm_RefrshSusp() As Boolean
'If necessary modify the code to use this procedure.
End Property

' Switch on the active tab's grid's TabStop & switch off the previous tab's.
Private Sub tabShG_Click(PreviousTab As Integer)
On Error GoTo ErrHnd
   Call SwchTabStop(tabShG.Tab, True) 'The active tab's on.
   Call SwchTabStop(PreviousTab, False) 'The previous tab's off.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter.
Private Sub txtFarm_DblClick()
On Error GoTo ErrHnd
   mobDatFrm.IDCtlPress gobFormtCtl.AscEnter
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' To prevent beeping beyond the ID length, cancel the length restriction for Enter.
Private Sub txtFarm_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If KeyCode = gobFormtCtl.AscEnter Then txtFarm.MaxLength = 0
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restore the length restriction, if it was canceled for Enter on the KeyDown event.
Private Sub txtFarm_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If txtFarm.MaxLength = 0 Then txtFarm.MaxLength = gobFormtCtl.LengIDFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus, if fewer than six characters are inputted.
Private Sub txtFarm_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   mobUtilDatFrm.IDCtl_Validate Cancel, lblFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mcolMsgs collection to the gobMsgInst object to read/write messages to the form
Private Property Get MsgRecip_Msgs() As Collection
   Set MsgRecip_Msgs = mcolMsgs
End Property

' Format the control.
Private Sub txtFarm_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub txtFarm_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   KeyAscii = gobFormtCtl.UpCase(KeyAscii) 'Type in upper case.
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
Private Sub txtFarm_LostFocus()
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
   adoFarmBrs.ConnectionString = gcnnConnServ.ConnectionString 'adoFarmBrs & dblFarmBrs.
   With dblFarmBrs
      Set .RowSource = adoFarmBrs
      .BoundColumn = "IDFarm"
      .ListField = "IDFarm"
   End With
   adoTwnVll.ConnectionString = gcnnConnServ.ConnectionString 'adoTwnVll & dbcTwnVll.
   With dbcTwnVll
      Set .RowSource = adoTwnVll
      .BoundColumn = "IDTownVill"
      .ListField = "TownVill"
   End With
   adoPersFarm.ConnectionString = gcnnConnServ.ConnectionString 'adoPersFarm &
   With dbcPersFarm                                             'dbcPersFarm.
      Set .RowSource = adoPersFarm
      .BoundColumn = "IDPers"
      .ListField = "Nam"
   End With
   adoPersCont.ConnectionString = gcnnConnServ.ConnectionString 'adoPersCont &
   With dbcPersCont                                             'dbcPersCont.
      Set .RowSource = adoPersCont
      .BoundColumn = "IDPers"
      .ListField = "Nam"
   End With
   adoShG.ConnectionString = gcnnConnServ.ConnectionString 'adoShG & dgdShG.
   adoShGBorn.ConnectionString = gcnnConnServ.ConnectionString 'adoShGBorn & dgdShGBorn.
   adoShGTrans.ConnectionString = gcnnConnServ.ConnectionString 'adoShGTrans &
   Call GridRecSrc 'Set Ado's record source.                    'dgdShGTrans.
   Set dgdShG.DataSource = adoShG
   Set dgdShGBorn.DataSource = adoShGBorn
   Set dgdShGTrans.DataSource = adoShGTrans
   tabShG.Tab = mintTab0 'Select the 1st tab.
   Call SwchTabStop(mintTab0, True) 'Switch the 1st tab's grid's TabStop.
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

' Set the adoShG, adoShGBorn & adoShGTrans control's record sources.
Private Sub GridRecSrc()
On Error GoTo ErrHnd
   With mobUtilDatFrm
      .GridRecSrc adoShG, "spSelect_SheepGoat_Grid('" & mobDatFrm.IDFrm & "')", dgdShG
      .GridRecSrc adoShGBorn, "spSelect_SheepGoat_GridBorn('" & mobDatFrm.IDFrm & "')", _
         dgdShGBorn
      .GridRecSrc adoShGTrans, "spSelect_TransFarm_Grid('" & mobDatFrm.IDFrm & "')", _
         dgdShGTrans
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified tab's grid's TabStop.
Private Sub SwchTabStop(ByVal intIdx As Integer, ByVal blnTabStop As Boolean)
On Error GoTo ErrHnd
   Const intTab1 As Integer = 1 'Tabs' idexes.
   Const intTab2 As Integer = 2
   Select Case intIdx 'Select the active tab.
   Case mintTab0
      dgdShG.TabStop = blnTabStop
   Case intTab1
      dgdShGBorn.TabStop = blnTabStop
   Case intTab2
      dgdShGTrans.TabStop = blnTabStop
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

