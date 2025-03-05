VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Begin VB.Form frmClient 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Клиентский терминал"
   ClientHeight    =   6570
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   11340
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6570
   ScaleWidth      =   11340
   ShowInTaskbar   =   0   'False
   Begin VB.ComboBox cmbTools 
      Height          =   315
      ItemData        =   "frmClient_Prev.frx":0000
      Left            =   4320
      List            =   "frmClient_Prev.frx":0002
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   120
      Width           =   1815
   End
   Begin MSComctlLib.ListView lvwStatus 
      Height          =   3135
      Index           =   0
      Left            =   240
      TabIndex        =   7
      Top             =   2880
      Width           =   8955
      _ExtentX        =   15796
      _ExtentY        =   5530
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton cmdHideSec 
      Caption         =   "&Скрыть символ"
      Height          =   325
      Left            =   4320
      TabIndex        =   4
      Top             =   1080
      Width           =   1815
   End
   Begin VB.CommandButton cmdAddSec 
      Caption         =   "&Добавить символ"
      Height          =   325
      Left            =   4320
      TabIndex        =   3
      Top             =   600
      Width           =   1815
   End
   Begin VB.CommandButton cmdLogin 
      Caption         =   "&Логин"
      Height          =   325
      Left            =   9480
      TabIndex        =   5
      Top             =   240
      Width           =   1815
   End
   Begin VB.CommandButton cmdExit 
      Cancel          =   -1  'True
      Caption         =   "&Выход"
      Height          =   325
      Left            =   9600
      TabIndex        =   6
      Top             =   6000
      Width           =   1695
   End
   Begin MSComctlLib.TabStrip tabStatus 
      Height          =   3675
      Left            =   120
      TabIndex        =   0
      Top             =   2760
      Width           =   9195
      _ExtentX        =   16219
      _ExtentY        =   6482
      MultiRow        =   -1  'True
      Placement       =   1
      TabMinWidth     =   998
      TabStyle        =   1
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   2
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&Торговля"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&История счёта"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ListView lvwMarket 
      Height          =   2415
      Left            =   120
      TabIndex        =   1
      TabStop         =   0   'False
      Top             =   120
      Width           =   3735
      _ExtentX        =   6588
      _ExtentY        =   4260
      View            =   3
      LabelEdit       =   1
      Sorted          =   -1  'True
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      FullRowSelect   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Символ"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Бид"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Аск"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Object.Width           =   2540
      EndProperty
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Add the security selected from cmbTools.
Private Sub cmdAddSec_Click()
    '''''''''''''''
End Sub

Private Sub cmdExit_Click()
    Unload Me
End Sub

' Adjust the lvwMarket columns' width.
Private Sub MarketColWidth()
    Dim chdColumnHeader As ColumnHeader
    Const intColumns As Integer = 3
    For Each chdColumnHeader In lvwMarket.ColumnHeaders
       chdColumnHeader.Width = lvwMarket.Width / intColumns
    Next
End Sub

' Fill cmbTools with securities.
Private Sub FillSecsCmb()
    Const strCnnStr As String = "Driver={MySQL ODBC 3.51 Driver};Port=3306;Server=localhost;Database=Broker;Uid=root;Pwd=130997"
    Const lngCnnTimeout As Long = 30
    Dim cnnConnServ As ADODB.Connection
    Dim rstTools As ADODB.Recordset
    Dim strCmdTxt As String
    Set cnnConnServ = New ADODB.Connection
    With cnnConnServ 'Server-side connection.
        If .State = adStateOpen Then .Close 'Close to open again.
        .ConnectionTimeout = lngCnnTimeout
        .CursorLocation = adUseClient ' adUseServer
        .Open strCnnStr
    End With
   Set rstTools = New ADODB.Recordset
   'strCmdTxt = "SELECT * FROM Tools"
   strCmdTxt = "SELECT * FROM tools"
   With rstTools
      .Open strCmdTxt, cnnConnServ, adOpenDynamic, adLockOptimistic, adCmdText
      If .BOF = False And .EOF = False Then 'Any records?
         'Debug.Print .Fields("field1")
         Do While Not .EOF
         'Do
            '.MoveNext
            cmbTools.AddItem .Fields("Tool")
            .MoveNext
         Loop
         'Loop While Not .EOF
      End If
   End With
End Sub

' Fill cmbTools with securities.
Private Sub PREV_FillSecsCmb()
'    'Const strCnnStr As String = "Driver={MySQL ODBC 3.51 Driver};Port=3306;Server=localhost;Database=TestDB;Uid=root;Pwd=130997"
'    Const strCnnStr As String = "Driver={MySQL ODBC 3.51 Driver};Port=3306;Server=localhost;Database=Broker;Uid=root;Pwd=130997"
'    Const lngCnnTimeout As Long = 30
'    Dim cnnConnServ As ADODB.Connection
'    Dim rstTools As ADODB.Recordset
'    Dim strCmdTxt As String
'    Set cnnConnServ = New ADODB.Connection
'    With cnnConnServ 'Server-side connection.
'        If .State = adStateOpen Then .Close 'Close to open again.
'        .ConnectionTimeout = lngCnnTimeout
'        .CursorLocation = adUseClient ' adUseServer
'        .Open strCnnStr
'    End With
'   Set rstTools = New ADODB.Recordset
'   strCmdTxt = "SELECT * FROM table1"
''   With rstTools
''      .Open strCmdTxt, cnnConnServ, adOpenDynamic, adLockOptimistic, adCmdText
''      If .BOF = False And .EOF = False Then 'Any records?
''         Debug.Print .Fields("field1")
''      End If
''   End With
''Exit Sub
'   ' Set the data source for rstTools.
'   With adoTools
'       .ConnectionString = cnnConnServ.ConnectionString
'       '.CommandType = adCmdStoredProc
'       .CommandType = adCmdTable
'       '.RecordSource = "spSelect_Breeds_ID_B"
'       '.RecordSource = "SELECT * FROM Tools"
'       .RecordSource = "tools"
'   End With
'   With dbcTools
'        Set .RowSource = adoTools
'       .BoundColumn = "ID"
'       .ListField = "Tool"
'   End With
End Sub
'cmbTools.AddItem "EURUSD"

' Fill cmbTools with securities.
Private Sub KTB_FillSecsCmb()
'    'Const intNumbSecs As Integer = 10 ' The number of securities
'    'Dim Secs(intNumbSecs) As String * 8
'    cmbTools.AddItem "EURUSD"
'    cmbTools.AddItem "GBPUSD"
'    cmbTools.AddItem "USDCHF"
'    cmbTools.AddItem "USDJPY"
'    cmbTools.AddItem "GOLD"
'    cmbTools.AddItem "DJI"
End Sub

' Fill lvwMarket with selected securities.
Private Sub FillSecsLvw()
   '''''''''''
End Sub

'Private Sub Test()
'
'End Sub

' Fill out the lvwMarket control with the available market symbols.
Private Sub FillLst()
   
   Dim strKey As String
   strKey = "GBPUSD"
   lvwMarket.ListItems.Add , strKey, strKey
   'lvwMarket.ListItems(strKey).ListSubItems.Add 1, , .Sex
'   lvwMarket.ListItems(strKey).ListSubItems.Add 2, , gobFormtCtl.NumFrac(.WtBirth)
'   lvwMarket.ListItems(strKey).ListSubItems.Add 3, , .Liv
   strKey = "EURUSD"
   lvwMarket.ListItems.Add , strKey, strKey
End Sub

' Login & invoke the Connect method to initiate a connection.
Private Function LoginConnect() As Boolean
   Const lngRemotePort = 1001
   Dim frmNewLogin As frmLogin
   Set frmNewLogin = New frmLogin
   frmNewLogin.Show vbModal
   If frmNewLogin.LoginSucceeded Then
'      wskClient.RemoteHost = frmNewLogin.txtServer
'      wskClient.RemotePort = lngRemotePort
'      wskClient.Connect
   End If
   LoginConnect = frmNewLogin.LoginSucceeded
   Unload frmNewLogin
End Function

Private Sub Form_Load()
On Error GoTo ErrHnd
   If Not LoginConnect Then ' Login & invoke the Connect method to initiate a connection.
      Unload Me
   Else
      Call MarketColWidth
      Call FillSecsCmb
      Call FillLst
   End If
   'Call Connect
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

Private Sub lvwStatusTrd_BeforeLabelEdit(Cancel As Integer)

End Sub
