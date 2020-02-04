VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmTradeHist 
   BorderStyle     =   5  'Sizable ToolWindow
   Caption         =   "Клиентский терминал"
   ClientHeight    =   6465
   ClientLeft      =   60
   ClientTop       =   300
   ClientWidth     =   11340
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   MinButton       =   0   'False
   ScaleHeight     =   6465
   ScaleWidth      =   11340
   ShowInTaskbar   =   0   'False
   Begin MSComctlLib.ListView lvwStatus 
      Height          =   6015
      Index           =   0
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   11355
      _ExtentX        =   20029
      _ExtentY        =   10610
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSComctlLib.TabStrip tabStatus 
      Height          =   6435
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   11355
      _ExtentX        =   20029
      _ExtentY        =   11351
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
End
Attribute VB_Name = "frmTradeHist"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdExit_Click()
    Unload Me
End Sub

' Adjust the lvwMarket columns' width.
Private Sub KTB_MarketColWidth()
'    Dim chdColumnHeader As ColumnHeader
'    Const intColumns As Integer = 3
'    For Each chdColumnHeader In lvwMarket.ColumnHeaders
'       chdColumnHeader.Width = lvwMarket.Width / intColumns
'    Next
End Sub

' Fill cmbTools with securities.
Private Sub KTB_FillSecsCmb()
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
'   'strCmdTxt = "SELECT * FROM Tools"
'   strCmdTxt = "SELECT * FROM tools"
'   With rstTools
'      .Open strCmdTxt, cnnConnServ, adOpenDynamic, adLockOptimistic, adCmdText
'      If .BOF = False And .EOF = False Then 'Any records?
'         'Debug.Print .Fields("field1")
'         Do While Not .EOF
'         'Do
'            '.MoveNext
'            cmbTools.AddItem .Fields("Tool")
'            .MoveNext
'         Loop
'         'Loop While Not .EOF
'      End If
'   End With
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

' Fill out the lvwMarket control with the available market symbols.
Private Sub KTB_FillLst()
'   Dim strKey As String
'   strKey = "GBPUSD"
'   lvwMarket.ListItems.Add , strKey, strKey
'   strKey = "EURUSD"
'   lvwMarket.ListItems.Add , strKey, strKey
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
      'Call MarketColWidth
      'Call FillSecsCmb
      'Call FillLst
   End If
   'Call Connect
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub
