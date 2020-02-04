VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDATGRD.OCX"
Begin VB.Form frmClient 
   Caption         =   "Sphinx Trader - Клиентский терминал"
   ClientHeight    =   8220
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   11580
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   8220
   ScaleWidth      =   11580
   StartUpPosition =   3  'Windows Default
   Begin MSDataGridLib.DataGrid dgdTrades 
      Height          =   975
      Index           =   1
      Left            =   2640
      TabIndex        =   7
      Top             =   3240
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   1720
      _Version        =   393216
      AllowUpdate     =   -1  'True
      Appearance      =   0
      BorderStyle     =   0
      HeadLines       =   1
      RowHeight       =   15
      RowDividerStyle =   0
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
         MarqueeStyle    =   3
         Locked          =   -1  'True
         RecordSelectors =   0   'False
         Size            =   1935
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin MSDataGridLib.DataGrid dgdTrades 
      Height          =   975
      Index           =   2
      Left            =   5040
      TabIndex        =   8
      Top             =   3240
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   1720
      _Version        =   393216
      AllowUpdate     =   -1  'True
      Appearance      =   0
      BorderStyle     =   0
      HeadLines       =   1
      RowHeight       =   15
      RowDividerStyle =   0
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
         MarqueeStyle    =   3
         Locked          =   -1  'True
         RecordSelectors =   0   'False
         Size            =   1935
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin MSDataGridLib.DataGrid dgdTrades 
      Height          =   975
      Index           =   3
      Left            =   7320
      TabIndex        =   9
      Top             =   3240
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   1720
      _Version        =   393216
      AllowUpdate     =   -1  'True
      Appearance      =   0
      BorderStyle     =   0
      Enabled         =   -1  'True
      HeadLines       =   1
      RowHeight       =   15
      RowDividerStyle =   0
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
         MarqueeStyle    =   3
         Locked          =   -1  'True
         RecordSelectors =   0   'False
         Size            =   1935
         BeginProperty Column00 
         EndProperty
         BeginProperty Column01 
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Command1"
      Height          =   495
      Left            =   120
      TabIndex        =   6
      Top             =   4080
      Visible         =   0   'False
      Width           =   1215
   End
   Begin MSComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   7950
      Width           =   11580
      _ExtentX        =   20426
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   14790
            Text            =   "Status"
            TextSave        =   "Status"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "06.01.2009"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "18:56"
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   600
      Top             =   3240
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Left            =   0
      Top             =   3240
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmClient.frx":0000
            Key             =   "New"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmClient.frx":0112
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmClient.frx":0224
            Key             =   "Save"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   11580
      _ExtentX        =   20426
      _ExtentY        =   741
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imlToolbarIcons"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   2
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "1007"
            ImageKey        =   "New"
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TabStrip tabTrades 
      Height          =   2700
      Left            =   0
      TabIndex        =   2
      Top             =   480
      Width           =   9675
      _ExtentX        =   17066
      _ExtentY        =   4763
      MultiRow        =   -1  'True
      Placement       =   1
      TabMinWidth     =   998
      TabStyle        =   1
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   3
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&Открытые позиции"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&Заказы"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "&История счёта"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
   Begin MSAdodcLib.Adodc adoTrades 
      Height          =   330
      Index           =   1
      Left            =   2640
      Top             =   4200
      Visible         =   0   'False
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   1
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
      Caption         =   "adoTrades"
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
   Begin MSAdodcLib.Adodc adoTrades 
      Height          =   330
      Index           =   2
      Left            =   5040
      Top             =   4200
      Visible         =   0   'False
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   1
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
      Caption         =   "adoTrades"
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
   Begin MSAdodcLib.Adodc adoTrades 
      Height          =   330
      Index           =   3
      Left            =   7320
      Top             =   4200
      Visible         =   0   'False
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   1
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
      Caption         =   "adoTrades"
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
   Begin VB.Label lblBid 
      Alignment       =   2  'Center
      Caption         =   "lblBid"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   0
      Left            =   1320
      TabIndex        =   5
      Top             =   4320
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.Label lblTime 
      Alignment       =   2  'Center
      Caption         =   "lblTime"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Index           =   0
      Left            =   1320
      TabIndex        =   4
      Top             =   3600
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.Label lblNotify 
      Alignment       =   2  'Center
      Caption         =   "lblNotify"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Index           =   0
      Left            =   1320
      TabIndex        =   3
      Top             =   3240
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.Menu mnuFile 
      Caption         =   "Файл"
      Begin VB.Menu mnuFileNew 
         Caption         =   "Новый ордер"
         Shortcut        =   ^N
      End
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mintTradesOpn As Integer = 1 ' Open trades data grid's index.
Const mintTradesPend As Integer = 2 ' Pending trades data grid's index.
Const mintColIDTyp As Integer = 3 ' IDTyp columnt index in the open trades data grid.

Private Type Tools
   FractMult() As Integer
   Spreads() As Currency
End Type

Dim mudtTools As Tools

Private Sub Command1_Click()
   Debug.Print "To be deleted"
   Call lblNotify_LinkNotify(1)
End Sub

' Edit a selected trade record from the grid.
Private Sub dgdTrades_DblClick(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case mintTradesPend 'Open Trades data grid
      Call ModifyOrdPend(Index) ' Modify a pending order.
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Modify a pending order.
Private Sub ModifyOrdPend(ByVal intIndex As Integer)
   Dim objTrade As New Trade
   Dim frmOrder As New frmOrder
   With dgdTrades(intIndex)
      objTrade.ID = .Columns("ID")
      objTrade.IDType = .Columns("IDType")
      objTrade.Vol = .Columns("Vol")
      objTrade.IDTool = .Columns("IDTool")
      objTrade.PriceOpn = .Columns("PriceOpn")
      objTrade.SL = .Columns("SL")
      objTrade.TP = .Columns("TP")
   End With
'   Set frmOrder.gobjTrade = objTrade
   With frmOrder
      .Trade = objTrade
      .ModifPend = True
      .Show vbModal
   End With
End Sub

Private Sub Form_Load()
On Error GoTo ErrHnd
   Call PlaceForm ' Place & shape the form.
   Call SetTools 'Set tick monitoring notify lables.
   Call SetAdo(1, "Sel_TradesOpn") ' Set ADO controls' data sources.
   Call SetAdo(2, "Sel_TradesPend")
   Call SetAdo(3, "Sel_TradesHist")
   Call SetCtrl ' Set tab controls.
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Place & shape the form.
Private Sub PlaceForm()
   Call Util.LoadResStrings(Me)
   Me.Left = GetSetting(App.Title, "Settings", "MainLeft", 1000)
   Me.Top = GetSetting(App.Title, "Settings", "MainTop", 1000)
   Me.Width = GetSetting(App.Title, "Settings", "MainWidth", 6500)
   Me.Height = GetSetting(App.Title, "Settings", "MainHeight", 6500)
End Sub

' Set an ADO control's data source.
Private Sub SetAdo(ByVal intIndex As Integer, ByVal strSP As String)
   adoTrades(intIndex).ConnectionString = gcnnConnServ.ConnectionString
   adoTrades(intIndex).RecordSource = strSP & "(" & gintIDAcc & ")"
End Sub

' Set tab & data grid controls.
Private Sub SetCtrl()
   Dim intCounter As Integer
   For intCounter = 1 To dgdTrades.Count
      Set dgdTrades(intCounter).DataSource = adoTrades(intCounter)
      With tabTrades
         dgdTrades(intCounter).Move .ClientLeft, .ClientTop, .ClientWidth, .ClientHeight
      End With
   Next
   Call HideIDs(mintTradesOpn) ' Hide Trades grids' ID columns.
   Call HideIDs(mintTradesPend)
   Call HideIDs(mintColIDTyp)
End Sub

' Hide Trades grids' ID columns.
Private Sub HideIDs(ByVal intIndex As Integer)
   With dgdTrades(intIndex)
      .Columns("IDType").Visible = False
      .Columns("IDTool").Visible = False
   End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim i As Integer
    For i = Forms.Count - 1 To 1 Step -1     'close all sub forms
        Unload Forms(i)
    Next
    If Me.WindowState <> vbMinimized Then
        SaveSetting App.Title, "Settings", "MainLeft", Me.Left
        SaveSetting App.Title, "Settings", "MainTop", Me.Top
        SaveSetting App.Title, "Settings", "MainWidth", Me.Width
        SaveSetting App.Title, "Settings", "MainHeight", Me.Height
    End If
End Sub

' Close the form on Esc press.
Private Sub Form_KeyPress(KeyAscii As Integer)
   If KeyAscii = vbKeyEscape Then Unload Me
'   End If
End Sub

' Send a tool price tick to the server.
Private Sub lblNotify_LinkNotify(Index As Integer)
On Error GoTo ErrHnd
   Static intCounter As Integer
   Dim curBid As Currency
   curBid = Util.ConvCur(lblBid(Index).Caption) ' Bid.
'   Debug.Print "To be deleted"
'   curBid = 1.4998
   gcnnConnServ.Execute "Upd_Trades('" & lblTime(Index).Caption & "', " & Index & ", " & curBid * mudtTools.FractMult(Index) & ", " & (curBid + mudtTools.Spreads(Index)) * mudtTools.FractMult(Index) & ", " & mudtTools.FractMult(Index) & ")", , adCmdStoredProc + adExecuteNoRecords
   intCounter = intCounter + 1
   Debug.Print intCounter & vbTab & lblNotify(Index).Caption & vbTab & curBid
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

Private Sub tabTrades_Click()
   dgdTrades(tabTrades.SelectedItem.Index).ZOrder 0
End Sub
'picRTF(tabRTF.SelectedItem.Index - 1).ZOrder 0

Private Sub tbToolBar_ButtonClick(ByVal Button As MSComctlLib.Button)
    On Error Resume Next
    Select Case Button.Key
        Case "New"
            Call mnuFileNew_Click
'        Case "Open"
'            Call mnuFileOpen_Click
'        Case "Save"
'            'ToDo: Add 'Save' button code.
'            MsgBox "Add 'Save' button code."
    End Select
End Sub

Private Sub mnuHelpAbout_Click()
    MsgBox "Version " & App.Major & "." & App.Minor & "." & App.Revision
End Sub

Private Sub mnuFileExit_Click()
    'unload the form
    Unload Me
End Sub

Private Sub mnuFileClose_Click()
    'ToDo: Add 'mnuFileClose_Click' code.
    MsgBox "Add 'mnuFileClose_Click' code."
End Sub

Private Sub mnuFileOpen_Click()
    Dim sFile As String
    With dlgCommonDialog
        .DialogTitle = "Open"
        .CancelError = False
        'ToDo: set the flags and attributes of the common dialog control
        .Filter = "All Files (*.*)|*.*"
        .ShowOpen
        If Len(.FileName) = 0 Then
            Exit Sub
        End If
        sFile = .FileName
    End With
    'ToDo: add code to process the opened file
End Sub

' Place a new pending order
Private Sub mnuFileNew_Click()
On Error GoTo ErrHnd
    Dim frmOrder As New frmOrder
    frmOrder.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Set tick monitoring notify lables.
Private Sub SetTools()
   Const intIndent As Integer = 1000
   Dim rstTools As New ADODB.Recordset
   Dim intIndex As Integer
   With rstTools
      .Open "Tools", gcnnConnServ, adOpenStatic, adLockReadOnly, adCmdTable
      If Not (.BOF And .EOF) Then 'Any tools?
         intIndex = 0
         Do 'Create notify lables.
            intIndex = intIndex + 1
            Load lblNotify(intIndex)
            Load lblTime(intIndex)
            Load lblBid(intIndex)
            Call LblLeftVisible(lblNotify(intIndex), intIndex) ' Set the lable's Left & Visible properties.
            lblNotify(intIndex).Caption = rstTools.Fields("Tool")
            Call LblLeftVisible(lblTime(intIndex), intIndex) ' Set the lable's Left & Visible properties.
            Call LblLeftVisible(lblBid(intIndex), intIndex) ' Set the lable's Left & Visible properties.
            Call Util.LinkPrices(lblNotify(intIndex), gobjLinkConst.LinkModeNotify, .Fields("Tool"), gobjLinkConst.LinkTopicTime) ' Link the DDE price lables.
            Call Util.LinkPrices(lblTime(intIndex), gobjLinkConst.LinkModeAutomatic, .Fields("Tool"), gobjLinkConst.LinkTopicTime) ' Link the DDE time lables.
            Call Util.LinkPrices(lblBid(intIndex), gobjLinkConst.LinkModeAutomatic, .Fields("Tool"), gobjLinkConst.LinkTopicBid) ' Link the DDE time lables.
'            ReDim Preserve mcurSpreads(intIndex) 'Resize the spreads array.
            ReDim Preserve mudtTools.Spreads(intIndex) 'Remember tools' fractional multipliers & spreads.
            ReDim Preserve mudtTools.FractMult(intIndex)
'            mcurSpreads(intIndex) = .Fields("Spread") 'Remember the spread of the tool.
            mudtTools.FractMult(intIndex) = .Fields("FractMult")
            mudtTools.Spreads(intIndex) = .Fields("Spread")
            .MoveNext
         Loop Until .EOF
      End If
   End With
End Sub

' Set a lable's Left & Visible properties.
Private Sub LblLeftVisible(lblLblLeftVisible As Label, ByVal intIndex As Integer)
   Const intIndent As Integer = 1000
   With lblLblLeftVisible
      .Left = lblNotify(0).Left + intIndent * intIndex
      .Visible = True
   End With
End Sub
