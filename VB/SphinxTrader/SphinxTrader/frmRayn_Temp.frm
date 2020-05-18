VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Begin VB.Form frmRayn 
   Caption         =   "Районы"
   ClientHeight    =   5490
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9510
   DrawMode        =   14  'Copy Pen
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   5490
   ScaleWidth      =   9510
   Begin VB.PictureBox picBtn 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   735
      Left            =   0
      ScaleHeight     =   735
      ScaleWidth      =   9510
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   4755
      Width           =   9510
      Begin VB.CommandButton cmdOk 
         Caption         =   "&ОК"
         Height          =   375
         Left            =   6720
         TabIndex        =   3
         Top             =   240
         Width           =   1215
      End
      Begin VB.CommandButton cmdCancel 
         Cancel          =   -1  'True
         Caption         =   "Отмена"
         Height          =   375
         Left            =   8040
         TabIndex        =   4
         Top             =   240
         Width           =   1215
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000005&
         Index           =   1
         X1              =   0
         X2              =   10695
         Y1              =   15
         Y2              =   15
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000010&
         Index           =   0
         X1              =   0
         X2              =   10695
         Y1              =   0
         Y2              =   0
      End
   End
   Begin MSDataListLib.DataCombo dbcObl 
      Height          =   315
      Left            =   4920
      TabIndex        =   1
      ToolTipText     =   "F4 - Открыть список"
      Top             =   840
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   556
      _Version        =   393216
      MatchEntry      =   -1  'True
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoObl 
      Height          =   330
      Left            =   4920
      Top             =   1080
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
      RecordSource    =   "spSelect_Oblasts_Dbc"
      Caption         =   "adoObl"
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
   Begin MSDataListLib.DataCombo dbcBrdBas 
      Height          =   315
      Left            =   1920
      TabIndex        =   5
      ToolTipText     =   "F4 - Открыть список"
      Top             =   0
      Width           =   3585
      _ExtentX        =   6324
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoBrd 
      Height          =   330
      Left            =   1920
      Top             =   120
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
   Begin VB.Label lblBrdBas 
      Caption         =   "&Базовая порода:"
      Height          =   255
      Left            =   0
      TabIndex        =   6
      Top             =   0
      Width           =   1335
   End
   Begin VB.Label lblObl 
      Caption         =   "О&бласть:"
      Height          =   255
      Left            =   3120
      TabIndex        =   0
      Top             =   840
      Width           =   735
   End
End
Attribute VB_Name = "frmRayn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
   Call InitCtl
End Sub

' Initialise the form's controls.
Private Sub InitCtl()
'   adoObl.ConnectionString = gcnnConnServ.ConnectionString 'adoObl & dbcObl.
'   With dbcObl
'      Set .RowSource = adoObl
''      .BoundColumn = "IDOblast"
'      .BoundColumn = "Tool"
'      .ListField = "Tool"
'   End With
   With adoBrd
       .ConnectionString = gcnnConnServ.ConnectionString
       .CommandType = adCmdStoredProc
'       .RecordSource = "spSelect_Breeds_ID_B"
       .RecordSource = "Sel_Tools_Temp()"
   End With
   Set dbcBrdBas.RowSource = adoBrd
   With dbcBrdBas
'       .BoundColumn = "IDBreed"
'       .ListField = "Breed"
       .BoundColumn = "Tool"
       .ListField = "Tool"
   End With
End Sub

