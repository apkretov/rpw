VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "msadodc.ocx"
Object = "{CDE57A40-8B86-11D0-B3C6-00A0C90AEA82}#1.0#0"; "MSDatGrd.ocx"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDatLst.ocx"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TabCtl32.ocx"
Begin VB.Form frmBrsShG 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Обзор овец/коз"
   ClientHeight    =   6960
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   11475
   Icon            =   "frmBrsShG.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6960
   ScaleWidth      =   11475
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin MSDataListLib.DataList dblSortInven 
      Bindings        =   "frmBrsShG.frx":1042
      DataField       =   "IDSort"
      DataMember      =   "BrsShG_Sort_ShG"
      DataSource      =   "deFlockBook"
      Height          =   1035
      Left            =   6360
      TabIndex        =   48
      Top             =   5760
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   1826
      _Version        =   393216
      ListField       =   "Sort"
      BoundColumn     =   "IDSort"
      Object.DataMember      =   "BrsShG_Sort_ShG"
   End
   Begin VB.Frame fraFiltInven 
      Caption         =   "Отобразить категории:"
      Height          =   1335
      Left            =   120
      TabIndex        =   7
      Top             =   5520
      Width           =   6015
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "&Выбывшие"
         Height          =   255
         Index           =   7
         Left            =   4680
         TabIndex        =   15
         Top             =   840
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "По&месные"
         Height          =   255
         Index           =   3
         Left            =   1560
         TabIndex        =   11
         Top             =   840
         Value           =   1  'Checked
         Width           =   1575
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "&Чистопородные"
         Height          =   255
         Index           =   2
         Left            =   1560
         TabIndex        =   10
         Top             =   360
         Value           =   1  'Checked
         Width           =   1575
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "> 1 &года"
         Height          =   255
         Index           =   5
         Left            =   3360
         TabIndex        =   13
         Top             =   840
         Value           =   1  'Checked
         Width           =   975
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "< &1 года"
         Height          =   255
         Index           =   4
         Left            =   3360
         TabIndex        =   12
         Top             =   360
         Value           =   1  'Checked
         Width           =   975
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "&На учёте"
         Height          =   255
         Index           =   6
         Left            =   4680
         TabIndex        =   14
         Top             =   360
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "Сам&ки"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   9
         Top             =   840
         Value           =   1  'Checked
         Width           =   1095
      End
      Begin VB.CheckBox chkFiltInven 
         Caption         =   "Сам&цы"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   8
         Top             =   360
         Value           =   1  'Checked
         Width           =   1095
      End
   End
   Begin MSAdodcLib.Adodc adoShG 
      Height          =   330
      Left            =   3600
      Top             =   4920
      Visible         =   0   'False
      Width           =   7695
      _ExtentX        =   13573
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   2
      LockType        =   3
      CommandType     =   1
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
   Begin MSDataListLib.DataList dblSortWtWool 
      Bindings        =   "frmBrsShG.frx":106C
      DataField       =   "IDSort"
      DataMember      =   "BrsShG_Sort_WtWool"
      DataSource      =   "deFlockBook"
      Height          =   1035
      Left            =   6360
      TabIndex        =   52
      Top             =   5760
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   1826
      _Version        =   393216
      ListField       =   "Sort"
      BoundColumn     =   "IDSort"
      Object.DataMember      =   "BrsShG_Sort_WtWool"
   End
   Begin VB.Frame fraFiltWtLmK 
      Caption         =   "Отобразить категории:"
      Height          =   1335
      Left            =   120
      TabIndex        =   32
      Top             =   5520
      Width           =   6015
      Begin VB.CheckBox chkFiltWtLmK 
         Caption         =   "&Выбывшие"
         Height          =   255
         Index           =   3
         Left            =   4440
         TabIndex        =   36
         Top             =   840
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltWtLmK 
         Caption         =   "Взвешивания &при отбивке"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   33
         Top             =   360
         Value           =   1  'Checked
         Width           =   2415
      End
      Begin VB.CheckBox chkFiltWtLmK 
         Caption         =   "Взвешивания в &7 месяцев"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   34
         Top             =   840
         Value           =   1  'Checked
         Width           =   2415
      End
      Begin VB.CheckBox chkFiltWtLmK 
         Caption         =   "&На учёте"
         Height          =   255
         Index           =   2
         Left            =   4440
         TabIndex        =   35
         Top             =   360
         Value           =   1  'Checked
         Width           =   1155
      End
   End
   Begin MSDataListLib.DataList dblSortWtLmK 
      Bindings        =   "frmBrsShG.frx":1099
      DataField       =   "IDSort"
      DataMember      =   "BrsShG_Sort_WtLmK"
      DataSource      =   "deFlockBook"
      Height          =   1035
      Left            =   6360
      TabIndex        =   51
      Top             =   5760
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   1826
      _Version        =   393216
      ListField       =   "Sort"
      BoundColumn     =   "IDSort"
      Object.DataMember      =   "BrsShG_Sort_WtLmK"
   End
   Begin VB.Frame fraFiltAppr 
      Caption         =   "Отобразить категории:"
      Height          =   1335
      Left            =   120
      TabIndex        =   42
      Top             =   5520
      Width           =   6015
      Begin VB.CheckBox chkFiltAppr 
         Caption         =   "&Выбывшие"
         Height          =   255
         Index           =   3
         Left            =   4440
         TabIndex        =   46
         Top             =   840
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltAppr 
         Caption         =   "Циклы &без пороков"
         BeginProperty DataFormat 
            Type            =   4
            Format          =   "0"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1049
            SubFormatType   =   8
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   43
         Top             =   360
         Value           =   1  'Checked
         Width           =   1815
      End
      Begin VB.CheckBox chkFiltAppr 
         Caption         =   "&Циклы с пороками"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   44
         Top             =   840
         Value           =   1  'Checked
         Width           =   1815
      End
      Begin VB.CheckBox chkFiltAppr 
         Caption         =   "&На учёте"
         Height          =   255
         Index           =   2
         Left            =   4440
         TabIndex        =   45
         Top             =   360
         Value           =   1  'Checked
         Width           =   1155
      End
   End
   Begin VB.Frame fraFiltWtWool 
      Caption         =   "Отобразить категории:"
      Height          =   1335
      Left            =   120
      TabIndex        =   37
      Top             =   5520
      Width           =   6015
      Begin VB.CheckBox chkFiltWtWool 
         Caption         =   "&На учёте"
         Height          =   255
         Index           =   2
         Left            =   4440
         TabIndex        =   40
         Top             =   360
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltWtWool 
         Caption         =   "Ст&рижки"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   39
         Top             =   840
         Value           =   1  'Checked
         Width           =   1455
      End
      Begin VB.CheckBox chkFiltWtWool 
         Caption         =   "В&звешивания"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   38
         Top             =   360
         Value           =   1  'Checked
         Width           =   1455
      End
      Begin VB.CheckBox chkFiltWtWool 
         Caption         =   "&Выбывшие"
         Height          =   255
         Index           =   3
         Left            =   4440
         TabIndex        =   41
         Top             =   840
         Value           =   1  'Checked
         Width           =   1155
      End
   End
   Begin VB.Frame fraFiltLmK 
      Caption         =   "Отобразить категории:"
      Height          =   1335
      Left            =   120
      TabIndex        =   21
      Top             =   5520
      Width           =   6015
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "&Мёртвые"
         Height          =   255
         Index           =   7
         Left            =   4800
         TabIndex        =   31
         Top             =   840
         Value           =   1  'Checked
         Width           =   1035
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "&Живые"
         Height          =   255
         Index           =   6
         Left            =   4800
         TabIndex        =   30
         Top             =   480
         Value           =   1  'Checked
         Width           =   1035
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "Самк&ки"
         Height          =   255
         Index           =   5
         Left            =   3600
         TabIndex        =   29
         Top             =   840
         Value           =   1  'Checked
         Width           =   1095
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "Сам&цы"
         Height          =   255
         Index           =   4
         Left            =   3600
         TabIndex        =   28
         Top             =   480
         Value           =   1  'Checked
         Width           =   1095
      End
      Begin VB.Frame fraFiltLmKOffsp 
         Caption         =   "Ягнята/козлята"
         Height          =   975
         Left            =   3480
         TabIndex        =   27
         Top             =   240
         Width           =   2400
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "&На учёте"
         Height          =   255
         Index           =   2
         Left            =   2160
         TabIndex        =   25
         Top             =   480
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "&Выбывшие"
         Height          =   255
         Index           =   3
         Left            =   2160
         TabIndex        =   26
         Top             =   840
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "&Ягнения/козления"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   23
         Top             =   480
         Value           =   1  'Checked
         Width           =   1815
      End
      Begin VB.CheckBox chkFiltLmK 
         Caption         =   "&Аборты"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   24
         Top             =   840
         Value           =   1  'Checked
         Width           =   1815
      End
      Begin VB.Frame fraFiltLmKDam 
         Caption         =   "Овцематки/козоматки"
         Height          =   975
         Left            =   120
         TabIndex        =   22
         Top             =   240
         Width           =   3255
      End
   End
   Begin VB.Frame fraFiltMat 
      Caption         =   "Отобразить категории:"
      Height          =   1335
      Left            =   120
      TabIndex        =   16
      Top             =   5520
      Width           =   6015
      Begin VB.CheckBox chkFiltMat 
         Caption         =   "&На учёте"
         Height          =   255
         Index           =   2
         Left            =   4440
         TabIndex        =   19
         Top             =   360
         Value           =   1  'Checked
         Width           =   1155
      End
      Begin VB.CheckBox chkFiltMat 
         Caption         =   "&Циклы с ягнениями/козлениями"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   18
         Top             =   840
         Value           =   1  'Checked
         Width           =   2895
      End
      Begin VB.CheckBox chkFiltMat 
         Caption         =   "Циклы &без ягнений/козлений"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   17
         Top             =   360
         Value           =   1  'Checked
         Width           =   2895
      End
      Begin VB.CheckBox chkFiltMat 
         Caption         =   "&Выбывшие"
         Height          =   255
         Index           =   3
         Left            =   4440
         TabIndex        =   20
         Top             =   840
         Value           =   1  'Checked
         Width           =   1155
      End
   End
   Begin MSComctlLib.ImageList ilsSgG 
      Left            =   3720
      Top             =   4320
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   6
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":10C5
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":1917
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":3579
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":412F
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":4981
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":51D3
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSDataGridLib.DataGrid dgdShG 
      Height          =   4575
      Left            =   3600
      TabIndex        =   6
      Top             =   720
      Width           =   7695
      _ExtentX        =   13573
      _ExtentY        =   8070
      _Version        =   393216
      AllowUpdate     =   0   'False
      HeadLines       =   2
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
   Begin MSDataListLib.DataList dblSortLmK 
      Bindings        =   "frmBrsShG.frx":5B35
      DataField       =   "IDSort"
      DataMember      =   "BrsShG_Sort_LmK"
      DataSource      =   "deFlockBook"
      Height          =   1035
      Left            =   6360
      TabIndex        =   50
      Top             =   5760
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   1826
      _Version        =   393216
      ListField       =   "Sort"
      BoundColumn     =   "IDSort"
      Object.DataMember      =   "BrsShG_Sort_LmK"
   End
   Begin MSDataListLib.DataList dblSortMat 
      Bindings        =   "frmBrsShG.frx":5B5F
      DataField       =   "IDSort"
      DataMember      =   "BrsShG_Sort_Mate"
      DataSource      =   "deFlockBook"
      Height          =   1035
      Left            =   6360
      TabIndex        =   49
      Top             =   5760
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   1826
      _Version        =   393216
      ListField       =   "Sort"
      BoundColumn     =   "IDSort"
      Object.DataMember      =   "BrsShG_Sort_Mate"
   End
   Begin VB.Timer tmrTimer 
      Enabled         =   0   'False
      Interval        =   125
      Left            =   720
      Top             =   4440
   End
   Begin MSAdodcLib.Adodc adoFarms 
      Height          =   330
      Left            =   240
      Top             =   4920
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
      CommandType     =   2
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
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Enabled         =   0   'False
      Height          =   375
      Left            =   10170
      TabIndex        =   55
      Top             =   6420
      Width           =   1215
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "&ОК"
      Enabled         =   0   'False
      Height          =   375
      Left            =   10170
      TabIndex        =   54
      Top             =   5880
      Width           =   1215
   End
   Begin MSComctlLib.ImageList ilsFarms 
      Left            =   120
      Top             =   4320
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   2
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":5B8A
            Key             =   "Folder"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBrsShG.frx":5CE4
            Key             =   "Folderop"
         EndProperty
      EndProperty
   End
   Begin TabDlg.SSTab tabFarms 
      Height          =   5055
      Left            =   120
      TabIndex        =   1
      Top             =   360
      Width           =   3405
      _ExtentX        =   6006
      _ExtentY        =   8916
      _Version        =   393216
      Style           =   1
      Tabs            =   2
      Tab             =   1
      TabHeight       =   520
      TabCaption(0)   =   "Населённым пунктам"
      TabPicture(0)   =   "frmBrsShG.frx":5E3E
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "treFarms"
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Алфавиту"
      TabPicture(1)   =   "frmBrsShG.frx":5E5A
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "dbcFarms"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).ControlCount=   1
      Begin MSDataListLib.DataCombo dbcFarms 
         Height          =   4545
         Left            =   120
         TabIndex        =   3
         Top             =   360
         Width           =   3150
         _ExtentX        =   5556
         _ExtentY        =   8017
         _Version        =   393216
         IntegralHeight  =   0   'False
         Style           =   1
         ListField       =   ""
         Text            =   ""
         Object.DataMember      =   ""
      End
      Begin MSComctlLib.TreeView treFarms 
         Height          =   4545
         Left            =   -74880
         TabIndex        =   2
         Top             =   360
         Width           =   3150
         _ExtentX        =   5556
         _ExtentY        =   8017
         _Version        =   393217
         Indentation     =   529
         Style           =   7
         ImageList       =   "ilsFarms"
         Appearance      =   1
      End
   End
   Begin MSDataListLib.DataList dblSortAppr 
      Bindings        =   "frmBrsShG.frx":5E76
      DataField       =   "IDSort"
      DataMember      =   "BrsShG_Sort_Appr"
      DataSource      =   "deFlockBook"
      Height          =   1035
      Left            =   6360
      TabIndex        =   53
      Top             =   5760
      Width           =   3375
      _ExtentX        =   5953
      _ExtentY        =   1826
      _Version        =   393216
      ListField       =   "Sort"
      BoundColumn     =   "IDSort"
      Object.DataMember      =   "BrsShG_Sort_Appr"
   End
   Begin MSComctlLib.TabStrip tabShG 
      Height          =   5055
      Left            =   3540
      TabIndex        =   5
      Top             =   360
      Width           =   7845
      _ExtentX        =   13838
      _ExtentY        =   8916
      MultiRow        =   -1  'True
      TabMinWidth     =   998
      TabStyle        =   1
      ImageList       =   "ilsSgG"
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   6
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Инвентаризация"
            ImageVarType    =   2
            ImageIndex      =   1
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Случка"
            ImageVarType    =   2
            ImageIndex      =   2
         EndProperty
         BeginProperty Tab3 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Ягнение/козление"
            ImageVarType    =   2
            ImageIndex      =   3
         EndProperty
         BeginProperty Tab4 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Взвешивание ягнят/козлят"
            ImageVarType    =   2
            ImageIndex      =   4
         EndProperty
         BeginProperty Tab5 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Взвешивание и стрижка"
            ImageVarType    =   2
            ImageIndex      =   5
         EndProperty
         BeginProperty Tab6 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Object.ToolTipText     =   "Бонитировка"
            ImageVarType    =   2
            ImageIndex      =   6
         EndProperty
      EndProperty
   End
   Begin VB.Label lblSort 
      Caption         =   "&Сортировать по полю:"
      Height          =   255
      Left            =   6360
      TabIndex        =   47
      Top             =   5520
      Width           =   1695
   End
   Begin VB.Label lblShG 
      Caption         =   "В&ыберите животное:"
      Height          =   255
      Left            =   3600
      TabIndex        =   4
      Top             =   120
      Width           =   1695
   End
   Begin VB.Label lblFarms 
      Caption         =   "Выберите &ферму по:"
      Height          =   255
      Left            =   180
      TabIndex        =   0
      Top             =   120
      Width           =   1695
   End
End
Attribute VB_Name = "frmBrsShG"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mintCmdOk2 As Integer = 1 'Count from 1 to enable resetting by nullifying.
Const mintFrmAct2 As Integer = 2

Dim mobTblTree As TblTree

Dim mobTblBrsShG As TblBrsShG
Dim mobTblBrsMat As TblBrsMat
Dim mobTblBrsLmK As TblBrsLmK
Dim mobTblBrsWtLmK As TblBrsWtLmK
Dim mobTblBrsWtWool As TblBrsWtWool
Dim mobTblBrsAppr As TblBrsAppr

Dim mstrFrmCallNamPrev
Dim mintProc As Integer
Dim mstrIDFarm As String
Dim mblnEscTabClick As Boolean
Dim mblnNewUnld As Boolean
Dim mintWndState As Integer

Public FrmCall As Form 'The calling form to insert a selected animal's ID & press Enter.
Public FrmCallNam As String 'The calling form's name to identify a recordset to show.
Public FrmCallNew As Boolean 'Mark to load a new frmShG form.
Public IDTxt As TextBox 'The calling form's ID text box to write the selected ShG's ID to
Public CmdButton As CommandButton 'The calling form's ID button to be enabled, if canceld
Public DatFrmEntr As Boolean 'Pressing Enter along with writing the ID.
Public AllowUnload As Boolean 'Mark to unload the form on quitting the application.

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub chkFiltAppr_Click(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshFilt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub chkFiltInven_Click(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshFilt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub chkFiltLmK_Click(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshFilt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub chkFiltMat_Click(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshFilt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub chkFiltWtLmK_Click(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshFilt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub chkFiltWtWool_Click(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshFilt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide this form. Disable the cmdOk & cmdCancel buttons to make shure ShG's are
'  uninterruptably populated until either button is pressed at the form's next activation
' Focus the calling form's ID field. Prior to focusing make sure the calling form is
'  visible.
' If the calling form is newly loaded unload it & focus a remaining data form, if any.
' Remember the tabFarms contorl's current tab.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If cmdCancel.Enabled Then 'Proceed, if enabled.
      Select Case FrmCallNew
      Case True 'Unload new frmShG.
         mintWndState = FrmCall.WindowState 'Remember the state to restore in FocFrmAny.
         Unload FrmCall
         Me.Hide
         Call FocFrmAny 'Focus any data form.
      Case False 'Focus frmShG.
         Call SwchBtn(False) 'Disable cmdOk & cmdCancel.
         Me.Hide
         If Not FrmCall.Visible Then FrmCall.Visible = True 'Unhide the calling form.
         With IDTxt 'Escape the error ocurred probably because I hide inactive data forms'
            If .Visible And .Enabled Then .SetFocus 'Focus.     'frames with the controls.
         End With
         CmdButton.Enabled = True 'Enable the ID button.
      End Select
      gobSetng.LastTabBrsShG = tabFarms.Tab 'Remember the tabFarms tab.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the selected sheep/goat's ID,if any, into the calling form's ID control.
'  Otherwise nullify the ID or unload the new frmShG form, if newly loaded.
' Mark a change in the form
' Focus the ID control. Prior to focusing make sure the calling form is visible.
' Press Enter, if required, or otherwise enable the calling form's ID button.
' Remember the tabFarms contorl's current tab.
' Hide this form. Disable the cmdOk & cmdCancel buttons to make shure ShG's are
'  uninterruptably populated until either button is pressed at a next form's activation.
' To get rid of mixed forms when this form unloads & the frmBrsShG form loads this
'  operation is splited up to two procedures (CmdOK1 & CmdOK2) with a break
'  between them. Call the former procedure from this one. Enable the tmrTimer to invoke
'  the latter procedure.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   If cmdOk.Enabled Then 'Proceed, if enabled.
      Call SwchBtn(False) 'Disable cmdOk & cmdCancel.
      If CmdOK1 Then 'The 1st procedure.
         mintProc = mintCmdOk2
         tmrTimer.Interval = gobSetng.TimeIntrv
         tmrTimer.Enabled = True 'Inovke the 2nd procedure.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Type in upper case.
Private Sub dbcFarms_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   KeyAscii = gobFormtCtl.UpCase(KeyAscii)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the selected farm's sheep/goats.
' Enable Esc.
Private Sub dbcFarms_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    If KeyCode = gobFormtCtl.CodeEsc Then
        Call cmdCancel_Click
    Else
        Call FillShG(dbcFarms.BoundText)
        Call SwchFiltSort 'Enable/disable filter & sort.
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the selected farm's sheep/goats.
Private Sub dbcFarms_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
    As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
    Call SwchFiltSort 'Enable/disable filter & sort.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortAppr_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortAppr_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
   As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortInven_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortInven_MouseUp(Button As Integer, Shift As Integer, x As Single, _
    Y As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortLmK_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortLmK_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
    As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortMat_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortMat_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
    As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortWtLmK_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortWtLmK_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
    As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortWtWool_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid with the sheep/goats sorted by the selected field.
Private Sub dblSortWtWool_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
    Call FillShG(dbcFarms.BoundText)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable the dgdShG grid to enable focusing the calling form.
' Click OK.
Private Sub dgdShG_DblClick()
On Error GoTo ErrHnd
   dgdShG.Enabled = False
   Call cmdOk_Click
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing Enter, disable the dgdShG grid to enable focusing the calling form &
'  enable Enter.
' On pressing Esc, click cmdCancel not to press manually Esc twice, only if a selected
'  farm is full.
Private Sub dgdShG_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .AscEnter 'Enter.
         dgdShG.Enabled = False
         Call cmdOk_Click
      Case .CodeEsc 'Esc.
         If Full Then cmdCancel = True
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show sheep/goats on farms distributed geografically or alphabetically.
' Populate the sheep/goats from the 1st farm or from that last selected.
' If no farms are registered hide the form.
' Execute only once or after renumbering/deleting a ShG (RefrshFarm = True).
' Enable the cmdOk & cmdCancel buttons. They are disabled to make shure ShG's are
'  uninterruptably populated until either button is pressed.
' To get rid of mixed forms when sheep/goats fill the form this operation is splited up
'  to 2 procedures (FrmAct1-2) with breaks between them. Call the 1st procedure from this
'  one. Enable the tmrTimer to invoke the 2nd procedure.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   AllowUnload = True 'Allow to unload the form in case an error occurs during activating.
   Call InitCtl 'Initialise controls.
   If FrmAct1 Then 'The 1st procedure.
      mintProc = mintFrmAct2
      tmrTimer.Interval = gobSetng.TimeIntrv
      tmrTimer.Enabled = True 'Inovke the 2nd procedure.
   End If
   AllowUnload = False 'Prevent unloading after activating.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Destroy the dgdShG grid's module-level data source object to release the system
'  resourses.
Private Sub Form_Deactivate()
On Error GoTo ErrHnd
   Call IdxDestrDatSrc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the form's parameters.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set mobTblTree = New TblTree
   mobTblTree.IDClnt = mobTblTree.IDClntNew
   Set obDatTbl = mobTblTree
   obDatTbl.Ins
   AllowUnload = True 'Allow to unload the form in case an error occurs during loading.
   tabFarms.Tab = gobSetng.LastTabBrsShG 'Focus the current tab.
   Call FillTree 'Fill the Farms tree view.
   adoFarms.ConnectionString = gcnnConn.ConnectionString 'adoFarms & dbcFarms.
   adoShG.ConnectionString = gcnnConn.ConnectionString
   Call Util.DbcSetRowSrc(dbcFarms, adoFarms, "IDFarm", "IDFarm")
   With tabShG 'Resize dgdShG.
      dgdShG.Move .ClientLeft, .ClientTop, .ClientWidth, .ClientHeight
   End With
   AllowUnload = False 'Prevent unloading after loading.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unless the application is quitted cancel unloading the form & execute the
'  cmdCancel_Click procedure instead. Otherwise, delete this application's client record
'  from the Tree table.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   If AllowUnload Then 'Delete the application's client record.
      Set obDatTbl = mobTblTree
      obDatTbl.Del
   Else 'Invoke cmdCancel.
      Cancel = True
      Call cmdCancel_Click
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable/disable the controls located in the tabFarms control.
Private Sub tabFarms_Click(PreviousTab As Integer)
On Error GoTo ErrHnd
   Call SwchTabCtls(tabFarms.Tab)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Enter.
Private Sub tabFarms_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If KeyCode = gobFormtCtl.AscEnter Then
      Call cmdOk_Click
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the selected data form's data.
Private Sub tabShG_Click()
On Error GoTo ErrHnd
   If Not mblnEscTabClick Then 'Proceed, unless escaped.
      Call Util.SwchBtnMouse(Me, False, True) 'Switch the mouse.
      FrmCallNam = gobSetng.FrmNamByIdx(tabShG.SelectedItem.Index)
      Call Form_Activate 'Show.
      tabShG.SetFocus 'Return the focus to itself.
      Call Util.SwchBtnMouse(Me, True, True) 'Reset the mouse.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Invoke the specified procedures.
Private Sub tmrTimer_Timer()
On Error GoTo ErrHnd
   tmrTimer.Enabled = False 'Disable.
   Select Case mintProc
   Case mintCmdOk2
      mintProc = 0 'Reset.
      Call CmdOK2
   Case mintFrmAct2
      mintProc = 0 'Reset.
      Call FrmAct2
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Prevent editting the lable.
Private Sub treFarms_BeforeLabelEdit(Cancel As Integer)
On Error GoTo ErrHnd
    Cancel = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid.
Private Sub treFarms_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   Call ReloadFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reload the dgdShG grid.
Private Sub treFarms_MouseUp(Button As Integer, Shift As Integer, x As Single, Y _
    As Single)
On Error GoTo ErrHnd
   Call ReloadFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable the calling form's ID button.
' Switch the tabFarms controls.
' Focus the dgdShG grid; enable it, if disabled after pressing Enter in it.
' Hide/unhide the frames & the data bound lists by the calling form.
Private Sub InitCtl()
On Error GoTo ErrHnd
   CmdButton.Enabled = False
   Call SwchTabCtls(gobSetng.LastTabBrsShG)
   With dgdShG
      If Not .Enabled Then .Enabled = True
      .SetFocus
   End With
   If FrmCallNam <> mstrFrmCallNamPrev Then 'Prevent unncessary operation.
      mstrFrmCallNamPrev = FrmCallNam
      mblnEscTabClick = True 'Prevent the tab click operation.
      With gobSetng 'Hide/unhide the frames & lists.
         Select Case FrmCallNam
         Case .FrmInvenNam
            tabShG.Tabs(.FrmInvenIdx).Selected = True 'Synronise tabShG.
            Call HideCtl(fraFiltInven.Name, dblSortInven.Name)
         Case .FrmMatNam
            tabShG.Tabs(.FrmMatIdx).Selected = True 'Synronise tabShG.
            Call HideCtl(fraFiltMat.Name, dblSortMat.Name)
         Case .FrmLmKNam
            tabShG.Tabs(.FrmLmKIdx).Selected = True 'Synronise tabShG.
            Call HideCtl(fraFiltLmK.Name, dblSortLmK.Name)
            fraFiltLmKDam.Visible = True 'Visualise fraFiltLmK's child frames.
            fraFiltLmKOffsp.Visible = True
         Case .FrmWtLmKNam
            tabShG.Tabs(.FrmWtLmKIdx).Selected = True 'Synronise tabShG.
            Call HideCtl(fraFiltWtLmK.Name, dblSortWtLmK.Name)
         Case .FrmWtWoolNam
            tabShG.Tabs(.FrmWtWoolIdx).Selected = True 'Synronise tabShG.
            Call HideCtl(fraFiltWtWool.Name, dblSortWtWool.Name)
         Case .FrmApprNam
            tabShG.Tabs(.FrmApprIdx).Selected = True 'Synronise tabShG.
            Call HideCtl(fraFiltAppr.Name, dblSortAppr.Name)
         End Select
      End With
      mblnEscTabClick = False 'Reset.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the treFarms control with farms distributed among town/villages.
' Create a hierarchy of countries, oblasts, rayons, town/villages, & farms.
Public Sub FillTree()
On Error GoTo ErrHnd
   Dim obSQL As SQL
   Dim rstOblasts As ADODB.Recordset
   Dim rstRayons As ADODB.Recordset
   Dim rstTwnVll As ADODB.Recordset
   Dim rstFarms As ADODB.Recordset
   Dim lngIDCountry As Long
   Dim lngIDOblast As Long
   Dim lngIDRayon As Long
   Dim lngIDTwnVll As Long
   Dim strKeyCountry As String
   Dim strKeyOblast As String
   Dim strKeyRayon As String
   Dim strKeyTwnVll As String
   Set obSQL = New SQL
   With deFlockBook.rsspSelect_BrsShG_Countries
      If .State = adStateOpen Then .Close 'Close to open again.
      .Open
      Do Until .EOF 'Loop through countries - the roots.
         lngIDCountry = .Fields("IDCountry") ' Remember the county.
         strKeyCountry = "County" & CStr(lngIDCountry)
         treFarms.Nodes.Add , , strKeyCountry, .Fields("Country"), "Folder", "Folderop"
         Set rstOblasts = obSQL.Oblasts(lngIDCountry) ' Get rstOblasts.
         With rstOblasts
            Do Until .EOF 'Loop through oblasts.
               lngIDOblast = .Fields("IDOblast") ' Remember the oblast.
               strKeyOblast = "Oblast" & CStr(lngIDOblast)
               treFarms.Nodes.Add strKeyCountry, tvwChild, strKeyOblast, .Fields _
                  ("Oblast") & " область", "Folder", "Folderop"
               Set rstRayons = obSQL.Rayons(lngIDOblast)
               With rstRayons
                  Do Until .EOF 'Loop through rayons.
                     lngIDRayon = .Fields("IDRayon") ' Remember the rayon.
                     strKeyRayon = "Rayon" & CStr(lngIDRayon)
                     treFarms.Nodes.Add strKeyOblast, tvwChild, strKeyRayon, .Fields( _
                        "Rayon") & Space$(1) & "район", "Folder", "Folderop"
                     Set rstTwnVll = obSQL.TwnVll(lngIDRayon)
                     With rstTwnVll
                        Do Until .EOF 'Loop through towns/villages.
                           lngIDTwnVll = .Fields("IDTownVill") ' Town/vil
                           strKeyTwnVll = "TwnVll" & CStr(lngIDTwnVll)
                           treFarms.Nodes.Add strKeyRayon, tvwChild, strKeyTwnVll, _
                              .Fields("TownVill"), "Folder", "Folderop"
                           Set rstFarms = obSQL.Farms(lngIDTwnVll)
                           With rstFarms
                              Do Until .EOF 'Loop through farms.
                                 treFarms.Nodes.Add strKeyTwnVll, tvwChild, .Fields( _
                                    "IDFarm"), "Ферма " & .Fields("IDFarm"), "Folder", _
                                    "Folderop"
                                 .MoveNext
                              Loop
                           End With
                           .MoveNext
                        Loop
                     End With
                     .MoveNext
                  Loop
               End With
               .MoveNext
            Loop
         End With
         .MoveNext
      Loop
      .Close
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the dgdShG grid with the selected farm's sheep/goats based on the calling form's
'  data.
' Sort the sheep/goats by the field selected in the dblSort.
' Format the dgdShG grid's columns.
Private Sub FillShG(ByVal strIDFarm As String)
On Error GoTo ErrHnd
   Static strIDFarmPrev As String
   Dim lngDateDispMin As Long
   Dim lngDateDispMax As Long
   Dim intLeng As Integer
   intLeng = Len(strIDFarm) 'The proper length is equal to 2.
   If intLeng = gobFormtCtl.LengIDFarm Then 'Prevent unnecessary operation.
      strIDFarmPrev = strIDFarm 'Remember the farm.
      Call DateDisp(lngDateDispMin, lngDateDispMax) 'DateDisp min/max kept/disposed days.
      With gobSetng
         Select Case FrmCallNam 'Set the data source of the grid, fill, sort & format its
         Case .FrmInvenNam                            'columns for the calling form.
            Call FillShGInven(strIDFarm, lngDateDispMin, lngDateDispMax)
         Case .FrmMatNam
            Call FillShGMat(strIDFarm, lngDateDispMin, lngDateDispMax)
         Case .FrmLmKNam
            Call FillShGLmK(strIDFarm, lngDateDispMin, lngDateDispMax)
         Case .FrmWtLmKNam
            Call FillShGWtLmK(strIDFarm, lngDateDispMin, lngDateDispMax)
         Case .FrmWtWoolNam
            Call FillShGWtWool(strIDFarm, lngDateDispMin, lngDateDispMax)
         Case .FrmApprNam
            Call FillShGAppr(strIDFarm, lngDateDispMin, lngDateDispMax)
         End Select
         dgdShG.Refresh 'Refresh.
      End With
   ElseIf intLeng > gobFormtCtl.LengIDFarm Then 'Restore the previous farm.
      Beep
      dbcFarms.Text = strIDFarmPrev
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
' Based on the calling form, enable or disable the frames & data lists to prevent
'  filtering & sorting empty Sheep/Goats list.
' Reset the filter's receintly clicked category, if its criteria are mutually exclusive
'   to the rest ones.
Private Sub SwchFiltSort(Optional ByVal blnFilt As Boolean, Optional ByVal intIdx _
   As Integer)
On Error GoTo ErrHnd
   Dim blnEnable As Boolean
   Dim intIdxPair As Integer
   Dim I As Integer
   blnEnable = IIf(dgdShG.ApproxCount = 0, False, True) 'Enabled/disabled.
   If blnEnable = False And blnFilt Then 'Verify a contradiction.
      MsgBox LoadResString(175) & dbcFarms & LoadResString(141), vbExclamation, _
         LoadResString(142)
      intIdxPair = IdxPair(intIdx) 'Determine the pair index.
      ChkBox(intIdx) = vbChecked 'Restore the Filter.
      ChkBox(intIdxPair) = vbChecked
   ElseIf DatLst.Enabled <> blnEnable Then 'Enable/disable, if necassary.
      DatLst.Enabled = blnEnable
      For I = 0 To IdxChkBoxMax 'Switch fraFilt's check boxes.
         ChkBox(I).Enabled = blnEnable
      Next
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Prevent mutually exclusive Filt pairs from being deselected by automatically switching
'  on the last one deselected.
' Select a Filt to switch based on the calling form.
Private Sub SwchFilt(ByVal intIdx As Integer)
On Error GoTo ErrHnd
   Dim intIdxPair As Integer
   intIdxPair = IdxPair(intIdx) 'Determine the control's index to switch on.
   If ChkBox(intIdx) = vbUnchecked And ChkBox(intIdxPair) = vbUnchecked Then 'Mutual exclusion
      MsgBox LoadResString(140), vbExclamation, LoadResString(142)
      ChkBox(intIdx) = vbChecked
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the dgdShG grid's columns for the Inven form's context.
Private Sub FormtInven()
On Error GoTo ErrHnd
   With dgdShG.Columns
      .Item(0).Caption = LoadResString(668)
      .Item(1).Caption = LoadResString(620)
      .Item(2).Caption = LoadResString(621)
      .Item(3).Caption = LoadResString(622)
      .Item(4).Caption = LoadResString(623)
      .Item(5).Caption = LoadResString(624)
      .Item(6).Caption = LoadResString(625)
      .Item(7).Caption = LoadResString(626)
      .Item(8).Caption = LoadResString(627)
      .Item(9).Caption = LoadResString(628)
      .Item(10).Caption = LoadResString(629)
      .Item(11).Caption = LoadResString(630)
      .Item(12).Caption = LoadResString(631)
      .Item(13).Caption = LoadResString(632)
      .Item(0).Width = 700
      .Item(1).Width = 800
      .Item(2).Width = 700
      .Item(3).Width = 1260
      .Item(4).Width = 950
      .Item(5).Width = 800
      .Item(6).Width = 800
      .Item(7).Width = 950
      .Item(8).Width = 950
      .Item(9).Width = 850
      .Item(10).Width = 1300
      .Item(11).Width = 1000
      .Item(12).Width = 1200
      .Item(13).Width = 2000
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the dgdShG grid's columns for the Mate form's context.
Private Sub FormtMat()
On Error GoTo ErrHnd
   With dgdShG.Columns
      .Item(0).Caption = LoadResString(668) '"Ферма" 'Write the captions.
      .Item(1).Caption = LoadResString(633) '"Овцематка/ козоматка"
      .Item(2).Caption = LoadResString(634) '"Цикл"
      .Item(3).Caption = LoadResString(635) '№ Барана/ козла
      .Item(4).Caption = LoadResString(636) 'Дата случки
      .Item(5).Caption = LoadResString(637) 'Дата ягнения/ козления
      .Item(0).Width = 700 'Adjust the width.
      .Item(1).Width = 1300
      .Item(2).Width = 950
      .Item(3).Width = 1050
      .Item(4).Width = 1150
      .Item(5).Width = 1300
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the dgdShG grid's columns for the WtLmK form's context.
Private Sub FormtWtLmK()
On Error GoTo ErrHnd
   With dgdShG.Columns
      .Item(0).Caption = LoadResString(668) 'IDFarm
      .Item(1).Caption = LoadResString(620) 'IDLambKid
      .Item(2).Caption = LoadResString(638) 'DateWean
      .Item(3).Caption = LoadResString(639) 'WtWean
      .Item(4).Caption = LoadResString(640) 'Date7Mon
      .Item(5).Caption = LoadResString(641) 'Wt7Mon
      .Item(0).Width = 700
      .Item(1).Width = 950
      .Item(2).Width = 1200
      .Item(3).Width = 1200
      .Item(4).Width = 1200
      .Item(5).Width = 1200
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the dgdShG grid's columns for the WtWool form's context.
Private Sub FormtWtWool()
On Error GoTo ErrHnd
   With dgdShG.Columns
      .Item(0).Caption = LoadResString(668) 'IDFarm
      .Item(1).Caption = LoadResString(620) 'IDSheepGoat
      .Item(2).Caption = LoadResString(634) 'Age
      .Item(3).Caption = LoadResString(609) 'DateAnnl
      .Item(4).Caption = LoadResString(614) 'WtAnnl
      .Item(5).Caption = LoadResString(348) 'DateShearAnnl
      .Item(6).Caption = LoadResString(610) 'GreaseAnnl
      .Item(0).Width = 700
      .Item(1).Width = 950
      .Item(2).Width = 950
      .Item(3).Width = 1200
      .Item(4).Width = 1000
      .Item(5).Width = 1100
      .Item(6).Width = 1000
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the dgdShG grid's columns for the Appr form's context.
Private Sub FormtAppr()
On Error GoTo ErrHnd
   With dgdShG.Columns
      .Item(0).Caption = LoadResString(668) 'IDFarm
      .Item(1).Caption = LoadResString(620) 'IDSheepGoat
      .Item(2).Caption = LoadResString(634) 'Age
      .Item(3).Caption = LoadResString(650) 'DateAppr
      .Item(4).Caption = LoadResString(651) 'Leng
      .Item(5).Caption = LoadResString(652) 'Diam
      .Item(6).Caption = LoadResString(653) 'Mass
      .Item(7).Caption = LoadResString(654) 'Crimpins
      .Item(8).Caption = LoadResString(655) 'Evens
      .Item(9).Caption = LoadResString(656) 'Density
      .Item(10).Caption = LoadResString(657) 'Strength
      .Item(11).Caption = LoadResString(658) 'Colour
      .Item(12).Caption = LoadResString(659) 'Quality
      .Item(13).Caption = LoadResString(660) 'FluffColour
      .Item(14).Caption = LoadResString(661) 'Fluff
      .Item(15).Caption = LoadResString(662) 'FibreYield
      .Item(16).Caption = LoadResString(663) 'BodyType
      .Item(17).Caption = LoadResString(664) 'Constitutn
      .Item(18).Caption = LoadResString(665) 'BodySize
      .Item(19).Caption = LoadResString(666) 'FatTail
      .Item(20).Caption = LoadResString(667) 'Defect
      .Item(0).Width = 700 'Adjust the width.
      .Item(1).Width = 800
      .Item(2).Width = 500
      .Item(3).Width = 950 '800
      .Item(4).Width = 1050
      .Item(5).Width = 700
      .Item(6).Width = 600
      .Item(7).Width = 600
      .Item(8).Width = 800
      .Item(9).Width = 1000
      .Item(10).Width = 600
      .Item(11).Width = 1500
      .Item(12).Width = 850
      .Item(13).Width = 1650
      .Item(14).Width = 800
      .Item(15).Width = 900
      .Item(16).Width = 500
      .Item(17).Width = 700
      .Item(18).Width = 550
      .Item(19).Width = 800
      .Item(20).Width = 2700
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the index of the Filt check box, which is a pair to the specified one.
Private Function IdxPair(ByVal intIdx As Integer) As Integer
On Error GoTo ErrHnd
   Select Case intIdx 'Determine the control's index to switch on.
      Case 0
         IdxPair = 1
      Case 1
         IdxPair = 0
      Case 1
         IdxPair = 0
      Case 2
         IdxPair = 3
      Case 3
         IdxPair = 2
      Case 4
         IdxPair = 5
      Case 5
         IdxPair = 4
      Case 6
         IdxPair = 7
      Case 7
         IdxPair = 6
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Switch the controls located in the tabFarms control.
Private Sub SwchTabCtls(ByVal intLastTab As Integer)
On Error GoTo ErrHnd
   Select Case intLastTab 'Enable/disable.
      Case 0
         treFarms.Enabled = True
         dbcFarms.Enabled = False
      Case 1
         treFarms.Enabled = False
         dbcFarms.Enabled = True
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return True, if a selected farm is full, i.e. the dgdShG grid has a single record.
Private Function Full() As Boolean
On Error GoTo ErrHnd
   Full = IIf(dgdShG.ApproxCount > 0, True, False)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Reload the dgdShG grid with the selected farm's sheep/goats, if a lable with a farm is
'  in focus.
Private Sub ReloadFarm()
On Error GoTo ErrHnd
    Dim strKey As String
    strKey = treFarms.SelectedItem.Key
    If Len(strKey) = gobFormtCtl.LengIDFarm Then 'This is a farm node.
        Call FillShG(strKey) 'Fill.
        Call SwchFiltSort 'Enable/disable Filt & sort.
        dbcFarms = strKey
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the cmdOk_Click procedure's part 1 before hiding the form.
' Return True, if succeeds.
Private Function CmdOK1() As Boolean
On Error GoTo ErrHnd
   Const intColID As Integer = 1 'ID column.
   Dim obDatFrm As DatFrm
   If Full Then
      If FrmCallNew Then 'Write the ID for new frmShG vs. other cases.
         FrmCall.tabShG.Tabs(tabShG.SelectedItem.Index).Selected = True 'Select the same tab in new frmShG.
         Set obDatFrm = FrmCall
         obDatFrm.IDCtl = dgdShG.Columns(intColID)
      Else 'Anohter case.
         IDTxt = dgdShG.Columns(intColID)
      End If
      Select Case FrmCall.Name 'Set IsDirty distiguishing by form.
      Case gobSetng.FrmShGNam
         Set obDatFrm = FrmCall
         obDatFrm.IsDirty = True
      Case gobSetng.FrmCertNam
         FrmCall.IsDirty = True
      End Select
   Else
      If FrmCallNew Then
Debug.Assert 0 = 1 'Verify mintWndState
         mintWndState = FrmCall.WindowState 'Remember the state to restore in FocFrmAny.
         Unload FrmCall 'Unload new frmShG.
         mblnNewUnld = True 'Mark the new form unloaded for CmdOK1 proc.
      Else
         IDTxt = "" 'Nullify
      End If
   End If
   Me.Hide
   CmdOK1 = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the cmdOk_Click procedure's part 2 after hiding the form.
Private Sub CmdOK2()
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   If Not mblnNewUnld Then
      If Not FrmCall.Visible Then FrmCall.Visible = True 'Unhide the calling form.
      With IDTxt 'Escape the error ocurred probably because I hide inactive data forms'
         If .Visible And .Enabled Then .SetFocus 'Focus.     'frames with the controls.
      End With
   Else
      mblnNewUnld = False 'Reset.
      Call FocFrmAny 'Focus any data form.
   End If
   If DatFrmEntr Then 'Press Enter.
      If Full Then
         Set obDatFrm = FrmCall
         Call frmMDI.SwchMnuMode(obDatFrm.Mode)  'Switch the menu & toolbar.
         obDatFrm.IDCtlPress gobFormtCtl.AscEnter
      End If
   Else
      CmdButton.Enabled = True
   End If
   gobSetng.LastTabBrsShG = tabFarms.Tab 'Remember the tabFarms tab.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the Form_Activate procedure's part 1 before filling the form.
' Return True, if succeeds.
Private Function FrmAct1() As Boolean
On Error GoTo ErrHnd
   If Len(dbcFarms) = gobFormtCtl.LengIDFarm Then 'Define a farm to populate sheep/goats
      mstrIDFarm = dbcFarms                        'from.
      FrmAct1 = True 'Succeeded.
   Else
      With adoFarms.Recordset
         If Not (.EOF And .BOF) Then
            mstrIDFarm = .Fields("IDFarm") 'Get the 1st farm.
            dbcFarms = mstrIDFarm 'Show it to the user.
            FrmAct1 = True 'Succeeded.
         Else
            MsgBox LoadResString(173), vbCritical, LoadResString(172)
            Me.Hide
         End If
      End With
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the Form_Activate procedure's part 2.
Private Sub FrmAct2()
On Error GoTo ErrHnd
   Call FillShG(mstrIDFarm) 'Populate the farm's sheep/goats.
   Call SwchFiltSort 'Enable/disable filter & sort.
   mstrIDFarm = "" 'Reset.
   Call SwchBtn(True) 'Enable cmdOk & cmdCancel.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Filter the dgdShG grid's data source's recordset by the selected categories & refresh
'  the control.
Private Sub RefrshFilt(ByVal intIdx As Integer)
On Error GoTo ErrHnd
   Call SwchFilt(intIdx) 'Prevent mutual exclustions.
   Call FillShG(dbcFarms.BoundText) 'Populate sheep/goats.
   Call SwchFiltSort(True, intIdx) 'Enable/disable filter & sort.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill, sort & format the dgdShG grid for the frmInven form.
Private Sub FillShGInven(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long)
On Error GoTo ErrHnd
   Dim obTblBrs As TblBrs
   Call IdxDestrDatSrc 'Destroy mobTblBrsShG.
   Set mobTblBrsShG = New TblBrsShG
   Set obTblBrs = mobTblBrsShG 'Populate farm's sheep/goat
   obTblBrs.Sel strIDFarm, lngDateDispMin, lngDateDispMax, adoShG, DatLst.BoundText, _
      chkFiltInven(0), chkFiltInven(1), chkFiltInven(2), chkFiltInven(3), chkFiltInven(4), _
      chkFiltInven(5), chkFiltInven(6), chkFiltInven(7)
   Set dgdShG.DataSource = adoShG 'Set data source.
   Call FormtInven 'Format the columns.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill, sort & format the dgdShG grid for the frmMat form.
Private Sub FillShGMat(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long)
On Error GoTo ErrHnd
   Dim obTblBrs As TblBrs
   Call IdxDestrDatSrc 'Destroy mobTblBrsMat.
   Set mobTblBrsMat = New TblBrsMat
   Set obTblBrs = mobTblBrsMat 'Populate farm's sheep/goat
   obTblBrs.Sel strIDFarm, lngDateDispMin, lngDateDispMax, adoShG, DatLst.BoundText, _
      chkFiltMat(0), chkFiltMat(1), chkFiltMat(2), chkFiltMat(3)
   Set dgdShG.DataSource = adoShG
   Call FormtMat 'Format the columns.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill, sort & format the dgdShG grid for the frmLmK form.
Private Sub FillShGLmK(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long)
On Error GoTo ErrHnd
   Dim obTblBrs As TblBrs
   Call IdxDestrDatSrc 'Destroy mobTblBrsLmK.
   Set mobTblBrsLmK = New TblBrsLmK
   Set obTblBrs = mobTblBrsLmK 'Populate farm's sheep/goat
   obTblBrs.Sel strIDFarm, lngDateDispMin, lngDateDispMax, adoShG, DatLst.BoundText, _
      chkFiltLmK(0), chkFiltLmK(1), chkFiltLmK(2), chkFiltLmK(3), chkFiltLmK(4), _
      chkFiltLmK(5), chkFiltLmK(6), chkFiltLmK(7)
   Set dgdShG.DataSource = adoShG
   Call FormtLmK 'Format the columns.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill, sort & format the dgdShG grid for the frmWtLmK form.
Private Sub FillShGWtLmK(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long)
On Error GoTo ErrHnd
   Dim obTblBrs As TblBrs
   Call IdxDestrDatSrc 'Destroy mobTblBrsWtLmK.
   Set mobTblBrsWtLmK = New TblBrsWtLmK
   Set obTblBrs = mobTblBrsWtLmK 'Populate farm's sheep/goat
   obTblBrs.Sel strIDFarm, lngDateDispMin, lngDateDispMax, adoShG, DatLst.BoundText, _
      chkFiltWtLmK(0), chkFiltWtLmK(1), chkFiltWtLmK(2), chkFiltWtLmK(3)
   Set dgdShG.DataSource = adoShG
   Call FormtWtLmK 'Format the columns.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill, sort & format the dgdShG grid for the frmWtWool form.
Private Sub FillShGWtWool(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, _
   ByVal lngDateDispMax As Long)
On Error GoTo ErrHnd
   Dim obTblBrs As TblBrs
   Call IdxDestrDatSrc 'Destroy mobTblBrsWtWool.
   Set mobTblBrsWtWool = New TblBrsWtWool
   Set obTblBrs = mobTblBrsWtWool 'Populate farm's sheep/goat
   obTblBrs.Sel strIDFarm, lngDateDispMin, lngDateDispMax, adoShG, DatLst.BoundText, _
      chkFiltWtWool(0), chkFiltWtWool(1), chkFiltWtWool(2), chkFiltWtWool(3)
   Set dgdShG.DataSource = adoShG
   Call FormtWtWool 'Format the columns.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill, sort & format the dgdShG grid for the frmWtWool form.
Private Sub FillShGAppr(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, _
   ByVal lngDateDispMax As Long)
On Error GoTo ErrHnd
   Dim obTblBrs As TblBrs
   Call IdxDestrDatSrc 'Destroy mobTblBrsAppr.
   Set mobTblBrsAppr = New TblBrsAppr
   Set obTblBrs = mobTblBrsAppr 'Populate farm's sheep/goat
   obTblBrs.Sel strIDFarm, lngDateDispMin, lngDateDispMax, adoShG, DatLst.BoundText, _
      chkFiltAppr(0), chkFiltAppr(1), chkFiltAppr(2), chkFiltAppr(3)
   Set dgdShG.DataSource = adoShG
   Call FormtAppr 'Format the columns.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the dgdShG grid's columns for the frmLmK form's context.
Private Sub FormtLmK()
On Error GoTo ErrHnd
   With dgdShG.Columns
      .Item(0).Caption = LoadResString(668) 'IDFarm   'Captions.
      .Item(1).Caption = LoadResString(633) 'IDDam
      .Item(2).Caption = LoadResString(634) 'Cycle
      .Item(3).Caption = LoadResString(637) 'DateLambKid
      .Item(4).Caption = LoadResString(611) 'AbortYN
      .Item(5).Caption = LoadResString(607) 'IDLambKid
      .Item(6).Caption = LoadResString(613) 'Sex
      .Item(7).Caption = LoadResString(614) 'WtBirth
      .Item(8).Caption = LoadResString(615) 'Liv
      .Item(0).Width = 700 'IDFarm                    'Width.
      .Item(1).Width = 1300 'IDDam
      .Item(2).Width = 500 'Cycle
      .Item(3).Width = 1250 'DateLambKid
      .Item(4).Width = 800 'AbortYN
      .Item(5).Width = 950 'IDLambKid
      .Item(6).Width = 650 'Sex
      .Item(7).Width = 850 'WtBirth
      .Item(8).Width = 1600 'Liv
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unhide the specified frame & data bound list. Hide the others.
Private Sub HideCtl(ByVal strNamFra As String, ByVal strNamDbl As String)
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   For Each ctlCtl In Me.Controls
      With ctlCtl
         If TypeOf ctlCtl Is Frame Then 'Frame.
            .Visible = IIf(.Name = strNamFra, True, False) 'Unhide the matching frame
         ElseIf TypeOf ctlCtl Is DataList Then 'List.
            .Visible = IIf(.Name = strNamDbl, True, False) 'Unhide the matching frame
         End If
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get a check box by the specified index based on the calling form.
Private Property Get ChkBox(ByVal intIdx As Integer) As CheckBox
On Error GoTo ErrHnd
   With gobSetng
      Select Case FrmCallNam 'Distinguish by form.
      Case .FrmInvenNam
         Set ChkBox = chkFiltInven(intIdx)
      Case .FrmMatNam
         Set ChkBox = chkFiltMat(intIdx)
      Case .FrmLmKNam
         Set ChkBox = chkFiltLmK(intIdx)
      Case .FrmWtLmKNam
         Set ChkBox = chkFiltWtLmK(intIdx)
      Case .FrmWtWoolNam
         Set ChkBox = chkFiltWtWool(intIdx)
      Case .FrmApprNam
         Set ChkBox = chkFiltAppr(intIdx)
      End Select
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get a data list based on the calling form.
Private Property Get DatLst() As DataList
On Error GoTo ErrHnd
   With gobSetng
      Select Case FrmCallNam 'Distinguish by form.
      Case .FrmInvenNam
         Set DatLst = dblSortInven
      Case .FrmMatNam
         Set DatLst = dblSortMat
      Case .FrmLmKNam
         Set DatLst = dblSortLmK
      Case .FrmWtLmKNam
         Set DatLst = dblSortWtLmK
      Case .FrmWtWoolNam
         Set DatLst = dblSortWtWool
      Case .FrmApprNam
         Set DatLst = dblSortAppr
      End Select
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get the maximal index of the check boxes based on the calling form.
Private Property Get IdxChkBoxMax() As Integer
On Error GoTo ErrHnd
   Const intChk7 As Integer = 7
   Const intChk3 As Integer = 3
   With gobSetng
      Select Case FrmCallNam 'Distinguish by form.
'      Case .FrmShGNam, .FrmLmKNam
      Case .FrmInvenNam, .FrmLmKNam
         IdxChkBoxMax = intChk7
      Case Else
         IdxChkBoxMax = intChk3
      End Select
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get a TblBrs object based on the calling form.
Private Property Get TblBrsOb() As TblBrs
On Error GoTo ErrHnd
   With gobSetng
      Select Case FrmCallNam 'Distinguish by form.
      Case .FrmInvenNam
         Set TblBrsOb = mobTblBrsShG
      Case .FrmMatNam
         Set TblBrsOb = mobTblBrsMat
      Case .FrmLmKNam
         Set TblBrsOb = mobTblBrsLmK
      Case .FrmWtLmKNam
         Set TblBrsOb = mobTblBrsWtLmK
      Case .FrmWtWoolNam
         Set TblBrsOb = mobTblBrsWtWool
      Case .FrmApprNam
         Set TblBrsOb = mobTblBrsAppr
      End Select
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Enable/disable the cmdOk & cmdCancel buttons.
Private Sub SwchBtn(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
    cmdOk.Enabled = blnEnable
    cmdCancel.Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Define the DateDisp minimal/maximal kept/disposed days for a TblBrs-data-sourse of the
'  dgdShG grid based on the selected disposition filter check boxes. The TblBrs-data-
'  sourse object's Sel method requires these values.
Private Sub DateDisp(ByRef lngDateDispMin As Long, ByRef lngDateDispMax As Long)
On Error GoTo ErrHnd
   Const lngKeptOn As Long = 2 '0 'Kept-ShG-On days value.
   Const lngKeptOff As Long = 3 '1 'Kept-ShG-Off days value.
   Const lngDispOff As Long = 2 '0 'Disposed-ShG-Off days value.
   Const intIdxDispLmK As Integer = 3 ' The index of the 2nd disp. check box for frmLmK.
   Dim intIdxDisp1st As Integer
   Dim intIdxDisp2nd As Integer
   If FrmCallNam = gobSetng.FrmLmKNam Then 'The index of the 2nd disp. check box.
      intIdxDisp2nd = intIdxDispLmK 'For frmLmK only.
   Else
      intIdxDisp2nd = IdxChkBoxMax 'For the rest forms.
   End If
   intIdxDisp1st = IdxPair(intIdxDisp2nd) 'The 1st disp. index.
   lngDateDispMin = IIf(ChkBox(intIdxDisp1st) = vbChecked, lngKeptOn, lngKeptOff) 'Kept/not kept days.
   lngDateDispMax = IIf(ChkBox(intIdxDisp2nd) = vbChecked, gobSetng.SQLDaysMax, _
      lngDispOff) 'Disposed/not days.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the Farms tree view, if the mobTblTree object's Refrsh mark is True.
Public Sub RefrshTreeDo()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set obDatTbl = mobTblTree
   obDatTbl.Sel mobTblTree.IDClnt
   If mobTblTree.Refrsh Then
      mobTblTree.Refrsh = False 'Reset.
      Set obDatTbl = mobTblTree
      obDatTbl.Upd
      Call frmMDI.StatusMsg(True, LoadResString(102)) 'Message about loading parameters.
      Call Util.SwchBtnMouse(FrmCall, False, True) 'Switch off the calling form's mouse
      treFarms.Nodes.Clear 'Clear the tree view.
      Call FillTree 'Refill.
      adoFarms.Refresh 'Refresh the farm list.
      Call frmMDI.StatusMsg(False) 'Remove the message.
      Util.SwchBtnMouse FrmCall, True, True 'Mouse on.
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Resume refresh the tree view & switch the mouse.
End Sub

' Destroy the dgdShG grid's module-level data source object to reload with new data it or
'  to release the system resourses on quiting the form.
' Distinguish the objects by the calling form.
Private Sub IdxDestrDatSrc()
On Error GoTo ErrHnd
   With gobSetng
      Select Case FrmCallNam
      Case .FrmInvenNam
         Set mobTblBrsShG = Nothing
      Case .FrmMatNam
         Set mobTblBrsMat = Nothing
      Case .FrmLmKNam
         Set mobTblBrsLmK = Nothing
      Case .FrmWtLmKNam
         Set mobTblBrsWtLmK = Nothing
      Case .FrmWtWoolNam
         Set mobTblBrsWtWool = Nothing
      Case .FrmApprNam
         Set mobTblBrsAppr = Nothing
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Link to mobTblTree object.
Public Property Get TblTree() As TblTree
   Set TblTree = mobTblTree
End Property

' If the newly loaded calling form is unload focus a remaining data form, if any.
' The explicit focusing is required because the application doesn't focus another
'  MDI-child form after another has been unloaded.
' Restore the other form's window state because unloading also causes maximised windows
'  to resize.
Private Sub FocFrmAny()
On Error GoTo ErrHnd
   Dim frmForm As Form
   With gobDatFrms
      If .Count > 0 Then
         Set frmForm = .FrmHostAny
         With frmForm
            If .WindowState <> vbMinimized Then .WindowState = mintWndState 'Restore the
            .SetFocus                                          'state, unless minimised.
         End With
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
