VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFlxGd.ocx"
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "msadodc.ocx"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDatLst.ocx"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSComCt2.ocx"
Begin VB.Form frmShG 
   Caption         =   "Обработка данных овец/коз"
   ClientHeight    =   6000
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10695
   Icon            =   "frmShG.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   6000
   ScaleWidth      =   10695
   Begin VB.Frame fraFrame 
      Caption         =   "Инвентаризация"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5160
      Index           =   1
      Left            =   0
      TabIndex        =   1
      Top             =   15
      Visible         =   0   'False
      Width           =   10575
      Begin VB.Frame fraFrame 
         Caption         =   "Рождение"
         Height          =   2595
         Index           =   8
         Left            =   4320
         TabIndex        =   15
         Top             =   960
         Width           =   3135
         Begin VB.CommandButton cmdID 
            Height          =   375
            Index           =   8
            Left            =   2640
            Picture         =   "frmShG.frx":1042
            Style           =   1  'Graphical
            TabIndex        =   24
            TabStop         =   0   'False
            ToolTipText     =   "Найти мать"
            Top             =   1320
            Width           =   375
         End
         Begin VB.CommandButton cmdID 
            Height          =   375
            Index           =   7
            Left            =   1200
            Picture         =   "frmShG.frx":1144
            Style           =   1  'Graphical
            TabIndex        =   21
            TabStop         =   0   'False
            ToolTipText     =   "Найти отца"
            Top             =   1320
            Width           =   375
         End
         Begin VB.TextBox txtDate 
            Height          =   315
            Index           =   0
            Left            =   240
            MaxLength       =   10
            TabIndex        =   17
            ToolTipText     =   "F4 - Открыть календарь"
            Top             =   600
            Width           =   2010
         End
         Begin VB.TextBox txtID 
            Height          =   315
            Index           =   7
            Left            =   240
            MaxLength       =   6
            TabIndex        =   20
            Top             =   1320
            Width           =   855
         End
         Begin VB.TextBox txtID 
            Height          =   315
            Index           =   8
            Left            =   1680
            MaxLength       =   6
            TabIndex        =   23
            Top             =   1320
            Width           =   855
         End
         Begin MSComCtl2.DTPicker dtpDate 
            Height          =   315
            Index           =   0
            Left            =   240
            TabIndex        =   18
            TabStop         =   0   'False
            Top             =   600
            Width           =   2295
            _ExtentX        =   4048
            _ExtentY        =   556
            _Version        =   393216
            CheckBox        =   -1  'True
            DateIsNull      =   -1  'True
            Format          =   50593793
            CurrentDate     =   37389
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   3
            Left            =   1680
            TabIndex        =   28
            ToolTipText     =   "F4 - Открыть список"
            Top             =   2055
            Width           =   855
            _ExtentX        =   1508
            _ExtentY        =   556
            _Version        =   393216
            ListField       =   "    mstrIDSire = IIf(strIDSire = """", ""-     "", strIDSire)"
            Text            =   ""
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   2
            Left            =   240
            TabIndex        =   26
            ToolTipText     =   "Тип рождения - в числе скольких рождён (F4 - Открыть список)"
            Top             =   2055
            Width           =   855
            _ExtentX        =   1508
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   2
            Left            =   240
            Top             =   2280
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
            RecordSource    =   "spSelect_TypeBirth"
            Caption         =   "adoFld"
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
         Begin VB.Label lblID 
            Caption         =   "&№ Матери:"
            Height          =   255
            Index           =   8
            Left            =   1680
            TabIndex        =   22
            Top             =   1080
            Width           =   885
         End
         Begin VB.Label lblDate 
            Caption         =   "Да&та:"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   16
            Top             =   360
            Width           =   1005
         End
         Begin VB.Label lblID 
            Caption         =   "№ От&ца:"
            Height          =   255
            Index           =   7
            Left            =   240
            TabIndex        =   19
            Top             =   1080
            Width           =   765
         End
         Begin VB.Label lblFld 
            Caption         =   "Т&ип:"
            Height          =   255
            Index           =   2
            Left            =   240
            TabIndex        =   25
            Top             =   1800
            Width           =   525
         End
         Begin VB.Label lblFld 
            Caption         =   "Ме&сто:"
            Height          =   255
            Index           =   3
            Left            =   1680
            TabIndex        =   27
            Top             =   1800
            Width           =   645
         End
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Порода"
         Height          =   2145
         Index           =   7
         Left            =   240
         TabIndex        =   9
         Top             =   1410
         Width           =   3975
         Begin VB.OptionButton optFld 
            Caption         =   "&Чистопородная:"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   10
            TabStop         =   0   'False
            Top             =   360
            Value           =   -1  'True
            Width           =   1575
         End
         Begin VB.OptionButton optFld 
            Caption         =   "По&месная:"
            Height          =   255
            Index           =   1
            Left            =   120
            TabIndex        =   11
            TabStop         =   0   'False
            Top             =   1140
            Width           =   1215
         End
         Begin VB.TextBox txtMisc 
            BackColor       =   &H8000000F&
            Height          =   495
            Index           =   1
            Left            =   360
            Locked          =   -1  'True
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   13
            TabStop         =   0   'False
            Top             =   1470
            Width           =   2355
         End
         Begin VB.CommandButton cmdDlg 
            Caption         =   "&Породы..."
            Enabled         =   0   'False
            Height          =   375
            Index           =   0
            Left            =   2790
            TabIndex        =   14
            ToolTipText     =   "Ввести помесную породу"
            Top             =   1470
            Width           =   1065
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   6
            Left            =   360
            TabIndex        =   12
            ToolTipText     =   "F4 - Открыть список"
            Top             =   630
            Width           =   3495
            _ExtentX        =   6165
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   6
            Left            =   360
            Top             =   840
            Visible         =   0   'False
            Width           =   3495
            _ExtentX        =   6165
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
            RecordSource    =   "spSelect_Breeds_ID_B"
            Caption         =   "adoFld"
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
      End
      Begin VB.CommandButton cmdID 
         Height          =   375
         Index           =   1
         Left            =   2400
         Picture         =   "frmShG.frx":1246
         Style           =   1  'Graphical
         TabIndex        =   4
         ToolTipText     =   "Выбрать животное"
         Top             =   360
         Width           =   375
      End
      Begin VB.TextBox txtMisc 
         Height          =   1035
         Index           =   0
         Left            =   4560
         MaxLength       =   150
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   45
         Top             =   3960
         Width           =   5775
      End
      Begin VB.CheckBox chkFld 
         Caption         =   "Переведён в про&бники"
         Height          =   375
         Index           =   0
         Left            =   240
         TabIndex        =   40
         Top             =   4380
         Width           =   2055
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Движение"
         Height          =   2595
         Index           =   9
         Left            =   7560
         TabIndex        =   29
         Top             =   960
         Width           =   2775
         Begin VB.CommandButton cmdDlg 
            Caption         =   "На ф&ерму..."
            Height          =   375
            Index           =   1
            Left            =   1560
            TabIndex        =   32
            ToolTipText     =   "Ввести племпродажу на другую ферму"
            Top             =   360
            Width           =   1065
         End
         Begin VB.OptionButton optFld 
            Caption         =   "Племпрода&жа"
            Height          =   255
            Index           =   2
            Left            =   120
            TabIndex        =   30
            TabStop         =   0   'False
            Top             =   360
            Value           =   -1  'True
            Width           =   1395
         End
         Begin VB.OptionButton optFld 
            Caption         =   "&Выбытие"
            Height          =   315
            Index           =   3
            Left            =   120
            TabIndex        =   31
            TabStop         =   0   'False
            Top             =   720
            Width           =   1095
         End
         Begin VB.TextBox txtDate 
            Enabled         =   0   'False
            Height          =   315
            Index           =   1
            Left            =   360
            MaxLength       =   10
            TabIndex        =   34
            ToolTipText     =   "F4 - Открыть календарь"
            Top             =   1320
            Width           =   2010
         End
         Begin MSComCtl2.DTPicker dtpDate 
            Height          =   315
            Index           =   1
            Left            =   360
            TabIndex        =   35
            TabStop         =   0   'False
            Top             =   1320
            Width           =   2295
            _ExtentX        =   4048
            _ExtentY        =   556
            _Version        =   393216
            Enabled         =   0   'False
            CheckBox        =   -1  'True
            DateIsNull      =   -1  'True
            Format          =   50593793
            CurrentDate     =   37393.9668055556
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   4
            Left            =   360
            TabIndex        =   37
            ToolTipText     =   "F4 - Открыть список"
            Top             =   2040
            Width           =   2295
            _ExtentX        =   4048
            _ExtentY        =   556
            _Version        =   393216
            Enabled         =   0   'False
            Style           =   2
            ListField       =   "    mstrIDSire = IIf(strIDSire = """", ""-     "", strIDSire)"
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   4
            Left            =   360
            Top             =   2280
            Visible         =   0   'False
            Width           =   2295
            _ExtentX        =   4048
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
            RecordSource    =   "spSelect_Disposition"
            Caption         =   "adoFld"
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
         Begin VB.Label lblFld 
            Caption         =   "П&ричина:"
            Height          =   255
            Index           =   4
            Left            =   360
            TabIndex        =   36
            Top             =   1800
            Width           =   1005
         End
         Begin VB.Label lblDate 
            Caption         =   "Д&ата:"
            Height          =   255
            Index           =   1
            Left            =   360
            TabIndex        =   33
            Top             =   1080
            Width           =   1005
         End
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   1
         Left            =   1200
         MaxLength       =   6
         TabIndex        =   3
         ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
         Top             =   360
         Width           =   1095
      End
      Begin VB.TextBox txtDate 
         Height          =   315
         Index           =   2
         Left            =   2520
         MaxLength       =   10
         TabIndex        =   42
         ToolTipText     =   "F4 - Открыть календарь"
         Top             =   4680
         Width           =   1290
      End
      Begin MSDataListLib.DataCombo dbcFld 
         Height          =   315
         Index           =   1
         Left            =   1200
         TabIndex        =   8
         ToolTipText     =   "F4 - Открыть список"
         Top             =   960
         Width           =   1575
         _ExtentX        =   2778
         _ExtentY        =   556
         _Version        =   393216
         Style           =   2
         Text            =   ""
      End
      Begin MSAdodcLib.Adodc adoFld 
         Height          =   330
         Index           =   1
         Left            =   1200
         Top             =   1200
         Visible         =   0   'False
         Width           =   1575
         _ExtentX        =   2778
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
         RecordSource    =   "spSelect_Sex"
         Caption         =   "adoFld"
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
      Begin MSDataListLib.DataCombo dbcFld 
         Height          =   315
         Index           =   5
         Left            =   2520
         TabIndex        =   39
         ToolTipText     =   "F4 - Открыть список"
         Top             =   3840
         Width           =   1575
         _ExtentX        =   2778
         _ExtentY        =   556
         _Version        =   393216
         Style           =   2
         Text            =   ""
      End
      Begin MSDataListLib.DataCombo dbcFld 
         Height          =   315
         Index           =   0
         Left            =   4320
         TabIndex        =   6
         ToolTipText     =   "F4 - Открыть список"
         Top             =   360
         Width           =   1095
         _ExtentX        =   1931
         _ExtentY        =   556
         _Version        =   393216
         MatchEntry      =   -1  'True
         Text            =   ""
      End
      Begin MSAdodcLib.Adodc adoFld 
         Height          =   330
         Index           =   0
         Left            =   4320
         Top             =   600
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
         Caption         =   "adoFld"
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
      Begin MSAdodcLib.Adodc adoFld 
         Height          =   330
         Index           =   5
         Left            =   2520
         Top             =   4080
         Visible         =   0   'False
         Width           =   1575
         _ExtentX        =   2778
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
         RecordSource    =   "spSelect_CopmClass"
         Caption         =   "adoFld"
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
      Begin MSComCtl2.DTPicker dtpDate 
         Height          =   315
         Index           =   2
         Left            =   2520
         TabIndex        =   43
         TabStop         =   0   'False
         Top             =   4680
         Width           =   1575
         _ExtentX        =   2778
         _ExtentY        =   556
         _Version        =   393216
         CheckBox        =   -1  'True
         DateIsNull      =   -1  'True
         Format          =   50593793
         CurrentDate     =   37389
      End
      Begin VB.Label lblID 
         Caption         =   "&Номер:"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   615
      End
      Begin VB.Label lblFld 
         Caption         =   "По&л:"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   7
         Top             =   990
         Width           =   375
      End
      Begin VB.Label lblMisc 
         Caption         =   "&Заметки:"
         Height          =   255
         Index           =   0
         Left            =   4560
         TabIndex        =   44
         Top             =   3720
         Width           =   735
      End
      Begin VB.Label lblFld 
         Caption         =   "&Ферма:"
         Height          =   255
         Index           =   0
         Left            =   3360
         TabIndex        =   5
         Top             =   360
         Width           =   615
      End
      Begin VB.Label lblFld 
         Caption         =   "&Комплексная оценка:"
         Height          =   255
         Index           =   5
         Left            =   240
         TabIndex        =   38
         Top             =   3840
         Width           =   1695
      End
      Begin VB.Label lblDate 
         Caption         =   "Дата перевода&:"
         Height          =   255
         Index           =   2
         Left            =   2520
         TabIndex        =   41
         Top             =   4440
         Width           =   1275
      End
   End
   Begin VB.Frame fraFrame 
      Caption         =   "Бонитировка"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5160
      Index           =   6
      Left            =   0
      TabIndex        =   118
      Top             =   15
      Visible         =   0   'False
      Width           =   10575
      Begin MSAdodcLib.Adodc adoGrid 
         Height          =   330
         Index           =   3
         Left            =   240
         Top             =   4800
         Visible         =   0   'False
         Width           =   10095
         _ExtentX        =   17806
         _ExtentY        =   582
         ConnectMode     =   0
         CursorLocation  =   3
         IsolationLevel  =   -1
         ConnectionTimeout=   15
         CommandTimeout  =   30
         CursorType      =   3
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
         Caption         =   "adoGrid"
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
      Begin VB.Frame fraFrame 
         Caption         =   "Шерсть/пух"
         Height          =   3000
         Index           =   15
         Left            =   240
         TabIndex        =   125
         Top             =   615
         Width           =   5655
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   7
            Left            =   3480
            MaxLength       =   2
            TabIndex        =   153
            TabStop         =   0   'False
            Top             =   2520
            Width           =   495
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   8
            Left            =   5040
            MaxLength       =   2
            TabIndex        =   155
            TabStop         =   0   'False
            Top             =   2520
            Width           =   495
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   5
            Left            =   1560
            MaxLength       =   4
            TabIndex        =   127
            TabStop         =   0   'False
            Top             =   240
            Width           =   975
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   6
            Left            =   4560
            MaxLength       =   4
            TabIndex        =   141
            TabStop         =   0   'False
            Top             =   960
            Width           =   975
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   9
            Left            =   1560
            TabIndex        =   129
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   600
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            ListField       =   ""
            BoundColumn     =   ""
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   9
            Left            =   1560
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
            RecordSource    =   "spSelect_Diam"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   12
            Left            =   4560
            TabIndex        =   139
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   600
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   11
            Left            =   4560
            TabIndex        =   137
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   240
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   13
            Left            =   4560
            TabIndex        =   143
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   1320
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Bindings        =   "frmShG.frx":13B8
            DataSource      =   "(None)"
            Height          =   315
            Index           =   10
            Left            =   1560
            TabIndex        =   135
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   1320
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   12
            Left            =   4260
            Top             =   720
            Visible         =   0   'False
            Width           =   1215
            _ExtentX        =   2143
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
            RecordSource    =   "Evens"
            Caption         =   "adoFld"
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
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   11
            Left            =   4260
            Top             =   360
            Visible         =   0   'False
            Width           =   1215
            _ExtentX        =   2143
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
            RecordSource    =   "Crimpins"
            Caption         =   "adoFld"
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
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   13
            Left            =   4260
            Top             =   1440
            Visible         =   0   'False
            Width           =   1215
            _ExtentX        =   2143
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
            RecordSource    =   "Strength"
            Caption         =   "adoFld"
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
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   10
            Left            =   1560
            Top             =   1440
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
            RecordSource    =   "Mass"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   15
            Left            =   4560
            TabIndex        =   148
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   1920
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   15
            Left            =   4260
            Top             =   2040
            Visible         =   0   'False
            Width           =   1215
            _ExtentX        =   2143
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
            RecordSource    =   "Quality"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   14
            Left            =   600
            TabIndex        =   146
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   1920
            Width           =   1935
            _ExtentX        =   3413
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   14
            Left            =   1440
            Top             =   2040
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
            RecordSource    =   "spSelect_WlGrsColour"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   16
            Left            =   600
            TabIndex        =   151
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   2520
            Width           =   1935
            _ExtentX        =   3413
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   16
            Left            =   1320
            Top             =   2640
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
            RecordSource    =   "spSelect_FluffColour"
            Caption         =   "adoFld"
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
         Begin VB.Label lblFld 
            Caption         =   "Цв&ет:"
            Height          =   255
            Index           =   16
            Left            =   120
            TabIndex        =   150
            Top             =   2595
            Width           =   495
         End
         Begin VB.Label lblNum 
            Caption         =   "% &Чистого волокна:"
            Height          =   405
            Index           =   8
            Left            =   4200
            TabIndex        =   154
            Top             =   2475
            Width           =   885
         End
         Begin VB.Label lblNum 
            Caption         =   "% Пуха в &шерсти:"
            Height          =   405
            Index           =   7
            Left            =   2760
            TabIndex        =   152
            Top             =   2475
            Width           =   675
         End
         Begin VB.Line linLine 
            BorderColor     =   &H80000005&
            Index           =   3
            X1              =   1900
            X2              =   5520
            Y1              =   2415
            Y2              =   2415
         End
         Begin VB.Line linLine 
            BorderColor     =   &H80000010&
            Index           =   2
            X1              =   1900
            X2              =   5520
            Y1              =   2400
            Y2              =   2400
         End
         Begin VB.Label lblLin 
            Caption         =   "Пух, волокно (для коз)"
            Height          =   255
            Index           =   1
            Left            =   120
            TabIndex        =   149
            Top             =   2280
            Width           =   1815
         End
         Begin VB.Label lblFld 
            Caption         =   "&Качество:"
            Height          =   255
            Index           =   15
            Left            =   3000
            TabIndex        =   147
            Top             =   1920
            Width           =   975
         End
         Begin VB.Label lblFld 
            Caption         =   "&Цвет:"
            Height          =   255
            Index           =   14
            Left            =   120
            TabIndex        =   145
            Top             =   1950
            Width           =   495
         End
         Begin VB.Label lblLin 
            Caption         =   "Жиропот"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   144
            Top             =   1680
            Width           =   735
         End
         Begin VB.Line linLine 
            BorderColor     =   &H80000005&
            Index           =   1
            X1              =   720
            X2              =   5520
            Y1              =   1815
            Y2              =   1815
         End
         Begin VB.Line linLine 
            BorderColor     =   &H80000010&
            Index           =   0
            X1              =   720
            X2              =   5520
            Y1              =   1800
            Y2              =   1800
         End
         Begin VB.Label lblFld 
            Caption         =   "И&звитость:"
            Height          =   255
            Index           =   11
            Left            =   3000
            TabIndex        =   136
            Top             =   270
            Width           =   975
         End
         Begin VB.Label lblFld 
            Caption         =   "К&репость:"
            Height          =   255
            Index           =   13
            Left            =   3000
            TabIndex        =   142
            Top             =   1350
            Width           =   855
         End
         Begin VB.Label lblNum 
            Caption         =   "&Густота, волокон/см2:"
            Height          =   405
            Index           =   6
            Left            =   3000
            TabIndex        =   140
            Top             =   915
            Width           =   1095
         End
         Begin VB.Label lblFld 
            Caption         =   "Ма&сса:"
            Height          =   255
            Index           =   10
            Left            =   120
            TabIndex        =   134
            Top             =   1350
            Width           =   735
         End
         Begin VB.Label lblFld 
            Caption         =   "Уравненност&ь:"
            Height          =   255
            Index           =   12
            Left            =   3000
            TabIndex        =   138
            Top             =   600
            Width           =   1215
         End
         Begin VB.Label lblFld 
            Caption         =   "Тонин&а, шкала:"
            Height          =   255
            Index           =   9
            Left            =   120
            TabIndex        =   128
            Top             =   630
            Width           =   1215
         End
         Begin VB.Label lblNum 
            Caption         =   "Д&лина, см:"
            Height          =   255
            Index           =   5
            Left            =   120
            TabIndex        =   126
            Top             =   270
            Width           =   855
         End
         Begin VB.Label lblMisc 
            Caption         =   "Тонина, мкн:"
            Height          =   255
            Index           =   2
            Left            =   120
            TabIndex        =   130
            Top             =   975
            Width           =   1095
         End
         Begin VB.Label lblMisc 
            BorderStyle     =   1  'Fixed Single
            BeginProperty DataFormat 
               Type            =   1
               Format          =   "0,0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1049
               SubFormatType   =   1
            EndProperty
            Height          =   285
            Index           =   3
            Left            =   1560
            TabIndex        =   131
            Top             =   960
            Width           =   405
         End
         Begin VB.Label lblMisc 
            BorderStyle     =   1  'Fixed Single
            BeginProperty DataFormat 
               Type            =   1
               Format          =   "0,0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   1049
               SubFormatType   =   1
            EndProperty
            Height          =   285
            Index           =   5
            Left            =   2130
            TabIndex        =   133
            Top             =   960
            Width           =   405
         End
         Begin VB.Label lblMisc 
            Alignment       =   2  'Center
            Caption         =   "-"
            Height          =   255
            Index           =   4
            Left            =   1980
            TabIndex        =   132
            Top             =   960
            Width           =   135
         End
      End
      Begin VB.Frame fraFrame 
         Caption         =   "&Пороки"
         Height          =   1815
         Index           =   17
         Left            =   6000
         TabIndex        =   165
         Top             =   1800
         Width           =   4335
         Begin VB.CommandButton cmdAdd 
            Caption         =   "&Добавить"
            Height          =   375
            Index           =   1
            Left            =   3120
            TabIndex        =   168
            TabStop         =   0   'False
            ToolTipText     =   "Добавить порок"
            Top             =   240
            Width           =   1065
         End
         Begin VB.CommandButton cmdDel 
            Caption         =   "&Удалить"
            Height          =   375
            Index           =   1
            Left            =   3120
            TabIndex        =   169
            TabStop         =   0   'False
            ToolTipText     =   "Удалить порок"
            Top             =   720
            Width           =   1065
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   21
            Left            =   120
            TabIndex        =   166
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   240
            Width           =   2895
            _ExtentX        =   5106
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   21
            Left            =   120
            Top             =   360
            Visible         =   0   'False
            Width           =   2895
            _ExtentX        =   5106
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
            RecordSource    =   "spSelect_Defects"
            Caption         =   "adoFld"
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
         Begin MSComctlLib.ListView lvwList 
            Height          =   1020
            Index           =   1
            Left            =   120
            TabIndex        =   167
            TabStop         =   0   'False
            Top             =   720
            Width           =   2895
            _ExtentX        =   5106
            _ExtentY        =   1799
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
            NumItems        =   0
         End
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Экстерьер"
         Height          =   1080
         Index           =   16
         Left            =   6000
         TabIndex        =   156
         Top             =   615
         Width           =   4335
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   20
            Left            =   3240
            TabIndex        =   164
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   600
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   20
            Left            =   3255
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
            RecordSource    =   "spSelect_FatTail"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   19
            Left            =   3240
            TabIndex        =   162
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   240
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   19
            Left            =   3255
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
            RecordSource    =   "BodySize"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   18
            Left            =   1200
            TabIndex        =   160
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   600
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   18
            Left            =   1200
            Top             =   720
            Visible         =   0   'False
            Width           =   1215
            _ExtentX        =   2143
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
            RecordSource    =   "Constitutn"
            Caption         =   "adoFld"
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
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   17
            Left            =   1200
            TabIndex        =   158
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   240
            Width           =   975
            _ExtentX        =   1720
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   17
            Left            =   1200
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
            RecordSource    =   "BodyType"
            Caption         =   "adoFld"
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
         Begin VB.Label lblFld 
            Caption         =   "&Величина:"
            Height          =   255
            Index           =   19
            Left            =   2400
            TabIndex        =   161
            Top             =   270
            Width           =   855
         End
         Begin VB.Label lblFld 
            Caption         =   "Т&ип:"
            Height          =   255
            Index           =   17
            Left            =   120
            TabIndex        =   157
            Top             =   270
            Width           =   495
         End
         Begin VB.Label lblFld 
            Caption         =   "Конституци&я:"
            Height          =   255
            Index           =   18
            Left            =   120
            TabIndex        =   159
            Top             =   630
            Width           =   1095
         End
         Begin VB.Label lblFld 
            Caption         =   "Оценка курд&юка:"
            Height          =   405
            Index           =   20
            Left            =   2400
            TabIndex        =   163
            Top             =   555
            Width           =   855
         End
      End
      Begin VB.CommandButton cmdID 
         Height          =   375
         Index           =   6
         Left            =   2400
         Picture         =   "frmShG.frx":13CD
         Style           =   1  'Graphical
         TabIndex        =   121
         TabStop         =   0   'False
         ToolTipText     =   "Выбрать животное"
         Top             =   240
         Width           =   375
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   6
         Left            =   1200
         MaxLength       =   6
         TabIndex        =   120
         TabStop         =   0   'False
         ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
         Top             =   240
         Width           =   1095
      End
      Begin VB.TextBox txtDate 
         Height          =   315
         Index           =   9
         Left            =   4440
         MaxLength       =   10
         TabIndex        =   123
         TabStop         =   0   'False
         ToolTipText     =   "F4 - Открыть календарь"
         Top             =   240
         Width           =   1095
      End
      Begin MSComCtl2.DTPicker dtpDate 
         Height          =   315
         Index           =   9
         Left            =   4440
         TabIndex        =   124
         TabStop         =   0   'False
         Top             =   240
         Width           =   1335
         _ExtentX        =   2355
         _ExtentY        =   556
         _Version        =   393216
         CheckBox        =   -1  'True
         DateIsNull      =   -1  'True
         Format          =   50593793
         CurrentDate     =   37389
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid flexGrid 
         Height          =   1200
         Index           =   3
         Left            =   240
         TabIndex        =   171
         TabStop         =   0   'False
         Top             =   3960
         Width           =   10095
         _ExtentX        =   17806
         _ExtentY        =   2117
         _Version        =   393216
         Cols            =   19
         FixedRows       =   0
         FixedCols       =   0
         WordWrap        =   -1  'True
         FocusRect       =   2
         AllowUserResizing=   3
         _NumberOfBands  =   2
         _Band(0).Cols   =   18
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
         _Band(0).ColHeader=   1
         _Band(0).BandExpandable=   0   'False
         _Band(0)._NumMapCols=   19
         _Band(0)._MapCol(0)._Name=   "IDSheepGoat"
         _Band(0)._MapCol(0)._RSIndex=   0
         _Band(0)._MapCol(0)._Hidden=   -1  'True
         _Band(0)._MapCol(1)._Name=   "Age"
         _Band(0)._MapCol(1)._Caption=   "Цикл"
         _Band(0)._MapCol(1)._RSIndex=   1
         _Band(0)._MapCol(1)._Alignment=   7
         _Band(0)._MapCol(2)._Name=   "DateAppr"
         _Band(0)._MapCol(2)._Caption=   "Дата"
         _Band(0)._MapCol(2)._RSIndex=   2
         _Band(0)._MapCol(3)._Name=   "Leng"
         _Band(0)._MapCol(3)._Caption=   "Длина, см"
         _Band(0)._MapCol(3)._RSIndex=   3
         _Band(0)._MapCol(3)._Alignment=   7
         _Band(0)._MapCol(4)._Name=   "Diam"
         _Band(0)._MapCol(4)._Caption=   "Тонина"
         _Band(0)._MapCol(4)._RSIndex=   4
         _Band(0)._MapCol(5)._Name=   "Mass"
         _Band(0)._MapCol(5)._Caption=   "Масса"
         _Band(0)._MapCol(5)._RSIndex=   5
         _Band(0)._MapCol(6)._Name=   "Crimpins"
         _Band(0)._MapCol(6)._Caption=   "Извит"
         _Band(0)._MapCol(6)._RSIndex=   6
         _Band(0)._MapCol(7)._Name=   "Evens"
         _Band(0)._MapCol(7)._Caption=   "Уравн"
         _Band(0)._MapCol(7)._RSIndex=   7
         _Band(0)._MapCol(8)._Name=   "Density"
         _Band(0)._MapCol(8)._Caption=   "Густ, вол/см2"
         _Band(0)._MapCol(8)._RSIndex=   8
         _Band(0)._MapCol(8)._Alignment=   7
         _Band(0)._MapCol(9)._Name=   "Strength"
         _Band(0)._MapCol(9)._Caption=   "Крепс"
         _Band(0)._MapCol(9)._RSIndex=   9
         _Band(0)._MapCol(10)._Name=   "Colour"
         _Band(0)._MapCol(10)._Caption=   "Цвет жиропота"
         _Band(0)._MapCol(10)._RSIndex=   10
         _Band(0)._MapCol(11)._Name=   "Quality"
         _Band(0)._MapCol(11)._Caption=   "Кач-во жир-п"
         _Band(0)._MapCol(11)._RSIndex=   11
         _Band(0)._MapCol(12)._Name=   "FluffColour"
         _Band(0)._MapCol(12)._Caption=   "Цвет пуха"
         _Band(0)._MapCol(12)._RSIndex=   12
         _Band(0)._MapCol(13)._Name=   "Fluff"
         _Band(0)._MapCol(13)._Caption=   "% Пух в шер"
         _Band(0)._MapCol(13)._RSIndex=   13
         _Band(0)._MapCol(13)._Alignment=   7
         _Band(0)._MapCol(14)._Name=   "FibreYield"
         _Band(0)._MapCol(14)._Caption=   "% Чист вол"
         _Band(0)._MapCol(14)._RSIndex=   14
         _Band(0)._MapCol(14)._Alignment=   7
         _Band(0)._MapCol(15)._Name=   "BodyType"
         _Band(0)._MapCol(15)._Caption=   "Тип"
         _Band(0)._MapCol(15)._RSIndex=   15
         _Band(0)._MapCol(16)._Name=   "Constitutn"
         _Band(0)._MapCol(16)._Caption=   "Конст"
         _Band(0)._MapCol(16)._RSIndex=   16
         _Band(0)._MapCol(17)._Name=   "BodySize"
         _Band(0)._MapCol(17)._Caption=   "Велич"
         _Band(0)._MapCol(17)._RSIndex=   17
         _Band(0)._MapCol(18)._Name=   "FatTail"
         _Band(0)._MapCol(18)._Caption=   "Оцен курд"
         _Band(0)._MapCol(18)._RSIndex=   18
         _Band(1).BandIndent=   1
         _Band(1).Cols   =   1
         _Band(1).GridLinesBand=   1
         _Band(1).TextStyleBand=   0
         _Band(1).TextStyleHeader=   0
         _Band(1).ColHeader=   1
         _Band(1)._ParentBand=   0
         _Band(1)._NumMapCols=   4
         _Band(1)._MapCol(0)._Name=   "IDSheepGoat"
         _Band(1)._MapCol(0)._RSIndex=   0
         _Band(1)._MapCol(0)._Hidden=   -1  'True
         _Band(1)._MapCol(1)._Name=   "Age"
         _Band(1)._MapCol(1)._RSIndex=   1
         _Band(1)._MapCol(1)._Alignment=   7
         _Band(1)._MapCol(1)._Hidden=   -1  'True
         _Band(1)._MapCol(2)._Name=   "IDDefect"
         _Band(1)._MapCol(2)._RSIndex=   2
         _Band(1)._MapCol(2)._Hidden=   -1  'True
         _Band(1)._MapCol(3)._Name=   "Defect"
         _Band(1)._MapCol(3)._Caption=   "Порок"
         _Band(1)._MapCol(3)._RSIndex=   3
      End
      Begin VB.Label lblID 
         Caption         =   "&Номер:"
         Height          =   255
         Index           =   6
         Left            =   360
         TabIndex        =   119
         Top             =   240
         Width           =   615
      End
      Begin VB.Label lblGrid 
         Caption         =   "Для изменения или удаления бонитировки выберите её из списка и нажмите Enter (дважды щёлкните по ней):"
         Height          =   255
         Index           =   3
         Left            =   240
         TabIndex        =   170
         Top             =   3720
         Width           =   8535
      End
      Begin VB.Label lblDate 
         Caption         =   "Да&та:"
         Height          =   255
         Index           =   9
         Left            =   3720
         TabIndex        =   122
         Top             =   240
         Width           =   495
      End
   End
   Begin VB.Frame fraFrame 
      Caption         =   "Случка"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5160
      Index           =   2
      Left            =   0
      TabIndex        =   46
      Top             =   15
      Visible         =   0   'False
      Width           =   10575
      Begin MSAdodcLib.Adodc adoGrid 
         Height          =   330
         Index           =   0
         Left            =   240
         Top             =   4680
         Visible         =   0   'False
         Width           =   10095
         _ExtentX        =   17806
         _ExtentY        =   582
         ConnectMode     =   0
         CursorLocation  =   3
         IsolationLevel  =   -1
         ConnectionTimeout=   15
         CommandTimeout  =   30
         CursorType      =   3
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
         Caption         =   "adoGrid"
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
      Begin VB.TextBox txtDate 
         Height          =   315
         Index           =   3
         Left            =   6360
         MaxLength       =   10
         TabIndex        =   54
         TabStop         =   0   'False
         ToolTipText     =   "F4 - Открыть календарь"
         Top             =   990
         Width           =   1170
      End
      Begin VB.CommandButton cmdID 
         Height          =   375
         Index           =   2
         Left            =   3960
         Picture         =   "frmShG.frx":153F
         Style           =   1  'Graphical
         TabIndex        =   49
         TabStop         =   0   'False
         ToolTipText     =   "Выбрать овцематку/козоматку"
         Top             =   360
         Width           =   375
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   2
         Left            =   2760
         MaxLength       =   6
         TabIndex        =   48
         TabStop         =   0   'False
         ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
         Top             =   360
         Width           =   1095
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   9
         Left            =   2760
         MaxLength       =   6
         TabIndex        =   51
         TabStop         =   0   'False
         Top             =   990
         Width           =   1095
      End
      Begin VB.CommandButton cmdID 
         Enabled         =   0   'False
         Height          =   375
         Index           =   9
         Left            =   3960
         Picture         =   "frmShG.frx":16B1
         Style           =   1  'Graphical
         TabIndex        =   52
         TabStop         =   0   'False
         ToolTipText     =   "Найти барана/козла"
         Top             =   990
         Width           =   375
      End
      Begin MSComCtl2.DTPicker dtpDate 
         Height          =   315
         Index           =   3
         Left            =   6360
         TabIndex        =   55
         TabStop         =   0   'False
         Top             =   990
         Width           =   1455
         _ExtentX        =   2566
         _ExtentY        =   556
         _Version        =   393216
         CheckBox        =   -1  'True
         DateIsNull      =   -1  'True
         Format          =   50593793
         CurrentDate     =   37389
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid flexGrid 
         Height          =   3225
         Index           =   0
         Left            =   240
         TabIndex        =   57
         TabStop         =   0   'False
         Top             =   1800
         Width           =   10095
         _ExtentX        =   17806
         _ExtentY        =   5689
         _Version        =   393216
         Cols            =   9
         FixedRows       =   0
         FixedCols       =   0
         WordWrap        =   -1  'True
         FocusRect       =   2
         AllowUserResizing=   3
         _NumberOfBands  =   3
         _Band(0).Cols   =   3
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
         _Band(0).ColHeader=   1
         _Band(0).BandExpandable=   0   'False
         _Band(0)._NumMapCols=   5
         _Band(0)._MapCol(0)._Name=   "IDDam"
         _Band(0)._MapCol(0)._RSIndex=   0
         _Band(0)._MapCol(0)._Hidden=   -1  'True
         _Band(0)._MapCol(1)._Name=   "Cycle"
         _Band(0)._MapCol(1)._Caption=   "Цикл"
         _Band(0)._MapCol(1)._RSIndex=   1
         _Band(0)._MapCol(1)._Alignment=   7
         _Band(0)._MapCol(2)._Name=   "CycleLambKid"
         _Band(0)._MapCol(2)._RSIndex=   2
         _Band(0)._MapCol(2)._Alignment=   7
         _Band(0)._MapCol(2)._Hidden=   -1  'True
         _Band(0)._MapCol(3)._Name=   "IDSire"
         _Band(0)._MapCol(3)._Caption=   "№ Бар/козл"
         _Band(0)._MapCol(3)._RSIndex=   4
         _Band(0)._MapCol(4)._Name=   "DateMatFrom"
         _Band(0)._MapCol(4)._Caption=   "Дата случки"
         _Band(0)._MapCol(4)._RSIndex=   3
         _Band(1).BandIndent=   1
         _Band(1).Cols   =   2
         _Band(1).GridLinesBand=   1
         _Band(1).TextStyleBand=   0
         _Band(1).TextStyleHeader=   0
         _Band(1).BandExpandable=   0   'False
         _Band(1)._ParentBand=   0
         _Band(1)._NumMapCols=   7
         _Band(1)._MapCol(0)._Name=   "IDDam"
         _Band(1)._MapCol(0)._RSIndex=   0
         _Band(1)._MapCol(0)._Hidden=   -1  'True
         _Band(1)._MapCol(1)._Name=   "Cycle"
         _Band(1)._MapCol(1)._RSIndex=   1
         _Band(1)._MapCol(1)._Alignment=   7
         _Band(1)._MapCol(1)._Hidden=   -1  'True
         _Band(1)._MapCol(2)._Name=   "CycleLambKid"
         _Band(1)._MapCol(2)._RSIndex=   2
         _Band(1)._MapCol(2)._Alignment=   7
         _Band(1)._MapCol(2)._Hidden=   -1  'True
         _Band(1)._MapCol(3)._Name=   "DateLambKid"
         _Band(1)._MapCol(3)._Caption=   "Дата ягн/козл"
         _Band(1)._MapCol(3)._RSIndex=   3
         _Band(1)._MapCol(4)._Name=   "TypeBirth"
         _Band(1)._MapCol(4)._RSIndex=   4
         _Band(1)._MapCol(4)._Alignment=   7
         _Band(1)._MapCol(4)._Hidden=   -1  'True
         _Band(1)._MapCol(5)._Name=   "Abort"
         _Band(1)._MapCol(5)._RSIndex=   5
         _Band(1)._MapCol(5)._Hidden=   -1  'True
         _Band(1)._MapCol(6)._Name=   "AbortYN"
         _Band(1)._MapCol(6)._Caption=   "Аборт"
         _Band(1)._MapCol(6)._RSIndex=   6
         _Band(2).BandIndent=   2
         _Band(2).Cols   =   4
         _Band(2).GridLinesBand=   1
         _Band(2).TextStyleBand=   0
         _Band(2).TextStyleHeader=   0
         _Band(2)._ParentBand=   1
         _Band(2)._NumMapCols=   9
         _Band(2)._MapCol(0)._Name=   "IDDam"
         _Band(2)._MapCol(0)._RSIndex=   0
         _Band(2)._MapCol(0)._Hidden=   -1  'True
         _Band(2)._MapCol(1)._Name=   "Cycle"
         _Band(2)._MapCol(1)._RSIndex=   1
         _Band(2)._MapCol(1)._Alignment=   7
         _Band(2)._MapCol(1)._Hidden=   -1  'True
         _Band(2)._MapCol(2)._Name=   "NoLambKid"
         _Band(2)._MapCol(2)._RSIndex=   2
         _Band(2)._MapCol(2)._Alignment=   7
         _Band(2)._MapCol(2)._Hidden=   -1  'True
         _Band(2)._MapCol(3)._Name=   "IDLambKid"
         _Band(2)._MapCol(3)._Caption=   "№ Приплода"
         _Band(2)._MapCol(3)._RSIndex=   3
         _Band(2)._MapCol(4)._Name=   "IDSex"
         _Band(2)._MapCol(4)._RSIndex=   4
         _Band(2)._MapCol(4)._Hidden=   -1  'True
         _Band(2)._MapCol(5)._Name=   "Sex"
         _Band(2)._MapCol(5)._Caption=   "Пол"
         _Band(2)._MapCol(5)._RSIndex=   5
         _Band(2)._MapCol(6)._Name=   "WtBirth"
         _Band(2)._MapCol(6)._Caption=   "Жив мас, кг"
         _Band(2)._MapCol(6)._RSIndex=   6
         _Band(2)._MapCol(6)._Alignment=   7
         _Band(2)._MapCol(7)._Name=   "IDLiv"
         _Band(2)._MapCol(7)._RSIndex=   7
         _Band(2)._MapCol(7)._Hidden=   -1  'True
         _Band(2)._MapCol(8)._Name=   "Liv"
         _Band(2)._MapCol(8)._Caption=   "Состояние"
         _Band(2)._MapCol(8)._RSIndex=   8
      End
      Begin VB.Label lblID 
         Caption         =   "Номер &барана/козла:"
         Height          =   255
         Index           =   9
         Left            =   240
         TabIndex        =   50
         Top             =   990
         Width           =   1695
      End
      Begin VB.Label lblID 
         Caption         =   "&Номер овцематки/козоматки:"
         Height          =   255
         Index           =   2
         Left            =   240
         TabIndex        =   47
         Top             =   360
         Width           =   2415
         WordWrap        =   -1  'True
      End
      Begin VB.Label lblDate 
         Caption         =   "Да&та случки:"
         Height          =   255
         Index           =   3
         Left            =   5040
         TabIndex        =   53
         Top             =   990
         Width           =   1095
      End
      Begin VB.Label lblGrid 
         Caption         =   "Для изменения или удаления случки выберите её из списка и нажмите Enter (дважды щёлкните по ней):"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   56
         Top             =   1560
         Width           =   8055
      End
   End
   Begin VB.Frame fraFrame 
      Caption         =   "Взвешивание ягнят/козлят"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5160
      Index           =   4
      Left            =   0
      TabIndex        =   84
      Top             =   15
      Visible         =   0   'False
      Width           =   10575
      Begin VB.CommandButton cmdID 
         Height          =   375
         Index           =   4
         Left            =   2880
         Picture         =   "frmShG.frx":17B3
         Style           =   1  'Graphical
         TabIndex        =   87
         TabStop         =   0   'False
         ToolTipText     =   "Выбрать животное"
         Top             =   360
         Width           =   375
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Взвешивание в 7 месяцев"
         Height          =   2880
         Index           =   12
         Left            =   5640
         TabIndex        =   94
         Top             =   1200
         Width           =   3975
         Begin VB.TextBox txtDate 
            Height          =   315
            Index           =   6
            Left            =   2160
            MaxLength       =   10
            TabIndex        =   96
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть календарь"
            Top             =   600
            Width           =   1095
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   2
            Left            =   2160
            MaxLength       =   4
            TabIndex        =   99
            TabStop         =   0   'False
            Top             =   1800
            Width           =   1095
         End
         Begin MSComCtl2.DTPicker dtpDate 
            Height          =   315
            Index           =   6
            Left            =   2160
            TabIndex        =   97
            TabStop         =   0   'False
            Top             =   600
            Width           =   1335
            _ExtentX        =   2355
            _ExtentY        =   556
            _Version        =   393216
            CheckBox        =   -1  'True
            DateIsNull      =   -1  'True
            Format          =   50593793
            CurrentDate     =   37389
         End
         Begin VB.Label lblDate 
            Caption         =   "Д&ата:"
            Height          =   255
            Index           =   6
            Left            =   480
            TabIndex        =   95
            Top             =   600
            Width           =   615
         End
         Begin VB.Label lblNum 
            Caption         =   "&Живая масса, кг:"
            Height          =   255
            Index           =   2
            Left            =   480
            TabIndex        =   98
            Top             =   1800
            Width           =   1455
         End
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Взвешивание при отбивке"
         Height          =   2880
         Index           =   11
         Left            =   720
         TabIndex        =   88
         Top             =   1200
         Width           =   3975
         Begin VB.TextBox txtDate 
            Height          =   315
            Index           =   5
            Left            =   2160
            MaxLength       =   10
            TabIndex        =   90
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть календарь"
            Top             =   600
            Width           =   1095
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   1
            Left            =   2160
            MaxLength       =   4
            TabIndex        =   93
            TabStop         =   0   'False
            Top             =   1800
            Width           =   975
         End
         Begin MSComCtl2.DTPicker dtpDate 
            Height          =   315
            Index           =   5
            Left            =   2160
            TabIndex        =   91
            TabStop         =   0   'False
            Top             =   600
            Width           =   1335
            _ExtentX        =   2355
            _ExtentY        =   556
            _Version        =   393216
            CheckBox        =   -1  'True
            DateIsNull      =   -1  'True
            Format          =   50593793
            CurrentDate     =   37389
         End
         Begin VB.Label lblDate 
            Caption         =   "Да&та:"
            Height          =   255
            Index           =   5
            Left            =   480
            TabIndex        =   89
            Top             =   600
            Width           =   615
         End
         Begin VB.Label lblNum 
            Caption         =   "Живая ма&сса, кг:"
            Height          =   255
            Index           =   1
            Left            =   480
            TabIndex        =   92
            Top             =   1800
            Width           =   1455
         End
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   4
         Left            =   1680
         MaxLength       =   6
         TabIndex        =   86
         TabStop         =   0   'False
         ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label lblID 
         Caption         =   "&Номер:"
         Height          =   255
         Index           =   4
         Left            =   840
         TabIndex        =   85
         Top             =   360
         Width           =   615
      End
   End
   Begin VB.Frame fraFrame 
      Caption         =   "Ягнение/козление"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5160
      Index           =   3
      Left            =   0
      TabIndex        =   58
      Top             =   15
      Visible         =   0   'False
      Width           =   10575
      Begin MSAdodcLib.Adodc adoGrid 
         Height          =   330
         Index           =   1
         Left            =   240
         Top             =   4680
         Visible         =   0   'False
         Width           =   10095
         _ExtentX        =   17806
         _ExtentY        =   582
         ConnectMode     =   0
         CursorLocation  =   3
         IsolationLevel  =   -1
         ConnectionTimeout=   15
         CommandTimeout  =   30
         CursorType      =   3
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
         Caption         =   "adoGrid"
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
      Begin VB.TextBox txtDate 
         Height          =   315
         Index           =   4
         Left            =   1560
         MaxLength       =   10
         TabIndex        =   63
         TabStop         =   0   'False
         ToolTipText     =   "F4 - Открыть календарь"
         Top             =   1110
         Width           =   1095
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid flexGrid 
         Height          =   2265
         Index           =   1
         Left            =   240
         TabIndex        =   83
         TabStop         =   0   'False
         Top             =   2760
         Width           =   10095
         _ExtentX        =   17806
         _ExtentY        =   3995
         _Version        =   393216
         Cols            =   9
         FixedRows       =   0
         FixedCols       =   0
         FocusRect       =   2
         AllowUserResizing=   3
         _NumberOfBands  =   3
         _Band(0).Cols   =   3
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
         _Band(0).ColHeader=   1
         _Band(0).BandExpandable=   0   'False
         _Band(0)._NumMapCols=   5
         _Band(0)._MapCol(0)._Name=   "IDDam"
         _Band(0)._MapCol(0)._RSIndex=   0
         _Band(0)._MapCol(0)._Hidden=   -1  'True
         _Band(0)._MapCol(1)._Name=   "Cycle"
         _Band(0)._MapCol(1)._Caption=   "Цикл"
         _Band(0)._MapCol(1)._RSIndex=   1
         _Band(0)._MapCol(1)._Alignment=   7
         _Band(0)._MapCol(2)._Name=   "CycleLambKid"
         _Band(0)._MapCol(2)._RSIndex=   2
         _Band(0)._MapCol(2)._Alignment=   7
         _Band(0)._MapCol(2)._Hidden=   -1  'True
         _Band(0)._MapCol(3)._Name=   "IDSire"
         _Band(0)._MapCol(3)._Caption=   "№ Бар/козл"
         _Band(0)._MapCol(3)._RSIndex=   4
         _Band(0)._MapCol(4)._Name=   "DateMatFrom"
         _Band(0)._MapCol(4)._Caption=   "Дата случки"
         _Band(0)._MapCol(4)._RSIndex=   3
         _Band(1).BandIndent=   1
         _Band(1).Cols   =   2
         _Band(1).GridLinesBand=   1
         _Band(1).TextStyleBand=   0
         _Band(1).TextStyleHeader=   0
         _Band(1).ColHeader=   1
         _Band(1).BandExpandable=   0   'False
         _Band(1)._ParentBand=   0
         _Band(1)._NumMapCols=   7
         _Band(1)._MapCol(0)._Name=   "IDDam"
         _Band(1)._MapCol(0)._RSIndex=   0
         _Band(1)._MapCol(0)._Hidden=   -1  'True
         _Band(1)._MapCol(1)._Name=   "Cycle"
         _Band(1)._MapCol(1)._RSIndex=   1
         _Band(1)._MapCol(1)._Alignment=   7
         _Band(1)._MapCol(1)._Hidden=   -1  'True
         _Band(1)._MapCol(2)._Name=   "CycleLambKid"
         _Band(1)._MapCol(2)._RSIndex=   2
         _Band(1)._MapCol(2)._Alignment=   7
         _Band(1)._MapCol(2)._Hidden=   -1  'True
         _Band(1)._MapCol(3)._Name=   "DateLambKid"
         _Band(1)._MapCol(3)._Caption=   "Дата ягн/козл"
         _Band(1)._MapCol(3)._RSIndex=   3
         _Band(1)._MapCol(4)._Name=   "TypeBirth"
         _Band(1)._MapCol(4)._RSIndex=   4
         _Band(1)._MapCol(4)._Alignment=   7
         _Band(1)._MapCol(4)._Hidden=   -1  'True
         _Band(1)._MapCol(5)._Name=   "Abort"
         _Band(1)._MapCol(5)._RSIndex=   5
         _Band(1)._MapCol(5)._Hidden=   -1  'True
         _Band(1)._MapCol(6)._Name=   "AbortYN"
         _Band(1)._MapCol(6)._Caption=   "Аборт"
         _Band(1)._MapCol(6)._RSIndex=   6
         _Band(2).BandIndent=   2
         _Band(2).Cols   =   4
         _Band(2).GridLinesBand=   1
         _Band(2).TextStyleBand=   0
         _Band(2).TextStyleHeader=   0
         _Band(2).ColHeader=   1
         _Band(2)._ParentBand=   1
         _Band(2)._NumMapCols=   9
         _Band(2)._MapCol(0)._Name=   "IDDam"
         _Band(2)._MapCol(0)._RSIndex=   0
         _Band(2)._MapCol(0)._Hidden=   -1  'True
         _Band(2)._MapCol(1)._Name=   "Cycle"
         _Band(2)._MapCol(1)._RSIndex=   1
         _Band(2)._MapCol(1)._Alignment=   7
         _Band(2)._MapCol(1)._Hidden=   -1  'True
         _Band(2)._MapCol(2)._Name=   "NoLambKid"
         _Band(2)._MapCol(2)._RSIndex=   2
         _Band(2)._MapCol(2)._Alignment=   7
         _Band(2)._MapCol(2)._Hidden=   -1  'True
         _Band(2)._MapCol(3)._Name=   "IDLambKid"
         _Band(2)._MapCol(3)._Caption=   "№ Приплода"
         _Band(2)._MapCol(3)._RSIndex=   3
         _Band(2)._MapCol(4)._Name=   "IDSex"
         _Band(2)._MapCol(4)._RSIndex=   4
         _Band(2)._MapCol(4)._Hidden=   -1  'True
         _Band(2)._MapCol(5)._Name=   "Sex"
         _Band(2)._MapCol(5)._Caption=   "Пол"
         _Band(2)._MapCol(5)._RSIndex=   5
         _Band(2)._MapCol(6)._Name=   "WtBirth"
         _Band(2)._MapCol(6)._Caption=   "Жив мас, кг"
         _Band(2)._MapCol(6)._RSIndex=   6
         _Band(2)._MapCol(6)._Alignment=   7
         _Band(2)._MapCol(7)._Name=   "IDLiv"
         _Band(2)._MapCol(7)._RSIndex=   7
         _Band(2)._MapCol(7)._Hidden=   -1  'True
         _Band(2)._MapCol(8)._Name=   "Liv"
         _Band(2)._MapCol(8)._Caption=   "Состояние"
         _Band(2)._MapCol(8)._RSIndex=   8
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Приплод"
         Height          =   2175
         Index           =   10
         Left            =   3360
         TabIndex        =   66
         Top             =   240
         Width           =   6975
         Begin VB.CommandButton cmdID 
            Enabled         =   0   'False
            Height          =   375
            Index           =   10
            Left            =   2640
            Picture         =   "frmShG.frx":1925
            Style           =   1  'Graphical
            TabIndex        =   71
            TabStop         =   0   'False
            ToolTipText     =   "Найти приплод"
            Top             =   480
            Width           =   375
         End
         Begin VB.CommandButton cmdEdit 
            Caption         =   "&Изменить"
            Height          =   375
            Index           =   0
            Left            =   5760
            TabIndex        =   80
            TabStop         =   0   'False
            ToolTipText     =   "Изменить приплод"
            Top             =   1200
            Width           =   1065
         End
         Begin VB.CommandButton cmdDel 
            Caption         =   "&Удалить"
            Height          =   375
            Index           =   0
            Left            =   5760
            TabIndex        =   81
            TabStop         =   0   'False
            ToolTipText     =   "Удалить приплод"
            Top             =   1680
            Width           =   1065
         End
         Begin VB.CommandButton cmdAdd 
            Caption         =   "&Добавить"
            Height          =   375
            Index           =   0
            Left            =   5760
            TabIndex        =   79
            TabStop         =   0   'False
            ToolTipText     =   "Добавить приплод"
            Top             =   720
            Width           =   1065
         End
         Begin VB.OptionButton optFld 
            Caption         =   "&Живой"
            Height          =   315
            Index           =   4
            Left            =   240
            TabIndex        =   67
            TabStop         =   0   'False
            Top             =   240
            Width           =   1095
         End
         Begin VB.OptionButton optFld 
            Caption         =   "&Мёртвый"
            Height          =   315
            Index           =   5
            Left            =   240
            TabIndex        =   68
            TabStop         =   0   'False
            Top             =   600
            Width           =   1095
         End
         Begin VB.TextBox txtID 
            Height          =   315
            Index           =   10
            Left            =   1440
            MaxLength       =   6
            TabIndex        =   70
            TabStop         =   0   'False
            Top             =   480
            Width           =   1095
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   0
            Left            =   4680
            MaxLength       =   3
            TabIndex        =   75
            TabStop         =   0   'False
            Top             =   480
            Width           =   975
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   7
            Left            =   3300
            TabIndex        =   73
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   480
            Width           =   1095
            _ExtentX        =   1931
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSDataListLib.DataCombo dbcFld 
            Height          =   315
            Index           =   8
            Left            =   1440
            TabIndex        =   77
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть список"
            Top             =   480
            Visible         =   0   'False
            Width           =   2415
            _ExtentX        =   4260
            _ExtentY        =   556
            _Version        =   393216
            Style           =   2
            Text            =   ""
         End
         Begin MSComctlLib.ListView lvwList 
            Height          =   1095
            Index           =   0
            Left            =   120
            TabIndex        =   78
            TabStop         =   0   'False
            Top             =   960
            Width           =   5535
            _ExtentX        =   9763
            _ExtentY        =   1931
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
            NumItems        =   0
         End
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   8
            Left            =   1440
            Top             =   600
            Visible         =   0   'False
            Width           =   2415
            _ExtentX        =   4260
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
            RecordSource    =   "spSelect_Liveability"
            Caption         =   "adoFld"
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
         Begin MSAdodcLib.Adodc adoFld 
            Height          =   330
            Index           =   7
            Left            =   3840
            Top             =   600
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
            RecordSource    =   "spSelect_SexOffspring"
            Caption         =   "adoFld"
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
         Begin VB.Label lblID 
            Caption         =   "№ &Приплода:"
            Height          =   255
            Index           =   10
            Left            =   1440
            TabIndex        =   69
            Top             =   240
            Width           =   1095
         End
         Begin VB.Label lblFld 
            Caption         =   "По&л:"
            Height          =   255
            Index           =   7
            Left            =   3300
            TabIndex        =   72
            Top             =   240
            Width           =   495
         End
         Begin VB.Label lblNum 
            Caption         =   "Живая ма&сса, кг:"
            Height          =   255
            Index           =   0
            Left            =   4560
            TabIndex        =   74
            Top             =   240
            Width           =   1455
         End
         Begin VB.Label lblFld 
            Caption         =   "П&ричина:"
            Height          =   255
            Index           =   8
            Left            =   1440
            TabIndex        =   76
            Top             =   240
            Visible         =   0   'False
            Width           =   735
         End
      End
      Begin VB.CommandButton cmdID 
         Height          =   375
         Index           =   3
         Left            =   2760
         Picture         =   "frmShG.frx":1A27
         Style           =   1  'Graphical
         TabIndex        =   61
         TabStop         =   0   'False
         ToolTipText     =   "Выбрать овцематку/козоматку"
         Top             =   360
         Width           =   375
      End
      Begin VB.CheckBox chkFld 
         Caption         =   "&Аборт"
         Height          =   315
         Index           =   1
         Left            =   1560
         TabIndex        =   65
         TabStop         =   0   'False
         Top             =   1800
         Width           =   855
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   3
         Left            =   1560
         MaxLength       =   6
         TabIndex        =   60
         TabStop         =   0   'False
         ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
         Top             =   360
         Width           =   1095
      End
      Begin MSComCtl2.DTPicker dtpDate 
         Height          =   315
         Index           =   4
         Left            =   1560
         TabIndex        =   64
         TabStop         =   0   'False
         Top             =   1110
         Width           =   1335
         _ExtentX        =   2355
         _ExtentY        =   556
         _Version        =   393216
         CheckBox        =   -1  'True
         Format          =   50593793
         CurrentDate     =   37737.0048842593
      End
      Begin VB.Label lblGrid 
         Caption         =   "Для изменения или удаления ягнения/козления выберите его из списка и нажмите Enter (дважды щёлкните по нему):"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   82
         Top             =   2520
         Width           =   9135
      End
      Begin VB.Label lblID 
         Caption         =   "&Номер овцема- тки/козоматки:"
         Height          =   375
         Index           =   3
         Left            =   240
         TabIndex        =   59
         Top             =   330
         Width           =   1215
      End
      Begin VB.Label lblDate 
         Caption         =   "Да&та:"
         Height          =   255
         Index           =   4
         Left            =   240
         TabIndex        =   62
         Top             =   1080
         Width           =   495
      End
   End
   Begin VB.Frame fraFrame 
      Caption         =   "Взвешивание и стрижка"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5160
      Index           =   5
      Left            =   0
      TabIndex        =   100
      Top             =   15
      Visible         =   0   'False
      Width           =   10575
      Begin MSAdodcLib.Adodc adoGrid 
         Height          =   330
         Index           =   2
         Left            =   3240
         Top             =   4725
         Visible         =   0   'False
         Width           =   7095
         _ExtentX        =   12515
         _ExtentY        =   582
         ConnectMode     =   0
         CursorLocation  =   3
         IsolationLevel  =   -1
         ConnectionTimeout=   15
         CommandTimeout  =   30
         CursorType      =   3
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
         Caption         =   "adoGrid"
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
      Begin VB.Frame fraFrame 
         Caption         =   "Взвешивание"
         Height          =   1800
         Index           =   13
         Left            =   240
         TabIndex        =   104
         Top             =   960
         Width           =   4575
         Begin VB.TextBox txtDate 
            Height          =   315
            Index           =   7
            Left            =   2400
            MaxLength       =   10
            TabIndex        =   106
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть календарь"
            Top             =   480
            Width           =   1095
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   3
            Left            =   2400
            MaxLength       =   5
            TabIndex        =   109
            TabStop         =   0   'False
            Top             =   1200
            Width           =   1095
         End
         Begin MSComCtl2.DTPicker dtpDate 
            Height          =   315
            Index           =   7
            Left            =   2400
            TabIndex        =   107
            TabStop         =   0   'False
            Top             =   480
            Width           =   1335
            _ExtentX        =   2355
            _ExtentY        =   556
            _Version        =   393216
            CheckBox        =   -1  'True
            DateIsNull      =   -1  'True
            Format          =   50593793
            CurrentDate     =   37389
         End
         Begin VB.Label lblNum 
            Caption         =   "Живая ма&сса, кг:"
            Height          =   255
            Index           =   3
            Left            =   600
            TabIndex        =   108
            Top             =   1200
            Width           =   1455
         End
         Begin VB.Label lblDate 
            Caption         =   "Да&та:"
            Height          =   255
            Index           =   7
            Left            =   600
            TabIndex        =   105
            Top             =   480
            Width           =   495
         End
      End
      Begin VB.Frame fraFrame 
         Caption         =   "Стрижка"
         Height          =   1800
         Index           =   14
         Left            =   5760
         TabIndex        =   110
         Top             =   960
         Width           =   4575
         Begin VB.TextBox txtDate 
            Height          =   315
            Index           =   8
            Left            =   2400
            MaxLength       =   10
            TabIndex        =   112
            TabStop         =   0   'False
            ToolTipText     =   "F4 - Открыть календарь"
            Top             =   480
            Width           =   1095
         End
         Begin VB.TextBox txtNum 
            Height          =   315
            Index           =   4
            Left            =   2400
            MaxLength       =   4
            TabIndex        =   115
            TabStop         =   0   'False
            Top             =   1200
            Width           =   1095
         End
         Begin MSComCtl2.DTPicker dtpDate 
            Height          =   315
            Index           =   8
            Left            =   2400
            TabIndex        =   113
            TabStop         =   0   'False
            Top             =   480
            Width           =   1335
            _ExtentX        =   2355
            _ExtentY        =   556
            _Version        =   393216
            CheckBox        =   -1  'True
            DateIsNull      =   -1  'True
            Format          =   50593793
            CurrentDate     =   37389
         End
         Begin VB.Label lblDate 
            Caption         =   "Д&ата:"
            Height          =   255
            Index           =   8
            Left            =   600
            TabIndex        =   111
            Top             =   480
            Width           =   495
         End
         Begin VB.Label lblNum 
            Caption         =   "Наст&риг, кг:"
            Height          =   255
            Index           =   4
            Left            =   600
            TabIndex        =   114
            Top             =   1200
            Width           =   1095
         End
      End
      Begin VB.CommandButton cmdID 
         Height          =   375
         Index           =   5
         Left            =   2280
         Picture         =   "frmShG.frx":1B99
         Style           =   1  'Graphical
         TabIndex        =   103
         TabStop         =   0   'False
         ToolTipText     =   "Выбрать животное"
         Top             =   360
         Width           =   375
      End
      Begin VB.TextBox txtID 
         Height          =   315
         Index           =   5
         Left            =   1080
         MaxLength       =   6
         TabIndex        =   102
         TabStop         =   0   'False
         ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
         Top             =   360
         Width           =   1095
      End
      Begin MSHierarchicalFlexGridLib.MSHFlexGrid flexGrid 
         Height          =   1935
         Index           =   2
         Left            =   3240
         TabIndex        =   117
         TabStop         =   0   'False
         Top             =   3120
         Width           =   7095
         _ExtentX        =   12515
         _ExtentY        =   3413
         _Version        =   393216
         Cols            =   5
         FixedRows       =   0
         FixedCols       =   0
         WordWrap        =   -1  'True
         FocusRect       =   2
         AllowUserResizing=   3
         _NumberOfBands  =   1
         _Band(0).Cols   =   5
         _Band(0).GridLinesBand=   1
         _Band(0).TextStyleBand=   0
         _Band(0).TextStyleHeader=   0
         _Band(0).ColHeader=   1
         _Band(0)._NumMapCols=   6
         _Band(0)._MapCol(0)._Name=   "IDSheepGoat"
         _Band(0)._MapCol(0)._RSIndex=   0
         _Band(0)._MapCol(0)._Hidden=   -1  'True
         _Band(0)._MapCol(1)._Name=   "Age"
         _Band(0)._MapCol(1)._Caption=   "Цикл"
         _Band(0)._MapCol(1)._RSIndex=   1
         _Band(0)._MapCol(1)._Alignment=   7
         _Band(0)._MapCol(2)._Name=   "DateAnnl"
         _Band(0)._MapCol(2)._Caption=   "Дата взвешив"
         _Band(0)._MapCol(2)._RSIndex=   2
         _Band(0)._MapCol(3)._Name=   "WtAnnl"
         _Band(0)._MapCol(3)._Caption=   "Живая масса, кг"
         _Band(0)._MapCol(3)._RSIndex=   3
         _Band(0)._MapCol(3)._Alignment=   7
         _Band(0)._MapCol(4)._Name=   "DateShearAnnl"
         _Band(0)._MapCol(4)._Caption=   "Дата стрижки"
         _Band(0)._MapCol(4)._RSIndex=   4
         _Band(0)._MapCol(5)._Name=   "GreaseAnnl"
         _Band(0)._MapCol(5)._Caption=   "Настриг, кг"
         _Band(0)._MapCol(5)._RSIndex=   5
         _Band(0)._MapCol(5)._Alignment=   7
      End
      Begin VB.Label lblGrid 
         Caption         =   "Для изменения или удаления взвешивания и стрижки выберите их из списка и нажмите Enter (дважды щёлкните по ним): "
         Height          =   855
         Index           =   2
         Left            =   240
         TabIndex        =   116
         Top             =   3120
         Width           =   2775
      End
      Begin VB.Label lblID 
         Caption         =   "&Номер:"
         Height          =   255
         Index           =   5
         Left            =   240
         TabIndex        =   101
         Top             =   360
         Width           =   615
      End
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   9240
      TabIndex        =   173
      Top             =   5520
      Width           =   1215
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "&ОК"
      Height          =   375
      Left            =   7920
      TabIndex        =   172
      Top             =   5520
      Width           =   1215
   End
   Begin MSComctlLib.ImageList ilsShG 
      Left            =   0
      Top             =   5640
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
            Picture         =   "frmShG.frx":1D0B
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShG.frx":255D
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShG.frx":41BF
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShG.frx":4D75
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShG.frx":55C7
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmShG.frx":5E19
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.TabStrip tabShG 
      Height          =   5595
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   10665
      _ExtentX        =   18812
      _ExtentY        =   9869
      MultiRow        =   -1  'True
      Placement       =   1
      TabMinWidth     =   998
      TabStyle        =   1
      ImageList       =   "ilsShG"
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
End
Attribute VB_Name = "frmShG"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Implements MsgRecip
Implements DatFrm
Implements SetngFrm

Const miShGInven As Integer = 1 'The Inven form's controls' indexes.
Const miFarm As Integer = 0
Const miSexInven As Integer = 1
Const miOptBrdPure As Integer = 0
Const miBrdPure As Integer = 6
Const miOptBrdCrs As Integer = 1
Const miBrdCrsTxt As Integer = 1
Const miBrdCrsCmd As Integer = 0
Const miDateBirth As Integer = 0
Const miSireInven As Integer = 7
Const miDamInven As Integer = 8
Const miTypeBirth As Integer = 2
Const miFarmBirth As Integer = 3
Const miOptTransFarm As Integer = 2
Const miTransFarmCmd As Integer = 1
Const miOptDisp As Integer = 3
Const miDateDisp As Integer = 1
Const miDispReas As Integer = 4
Const miCompClass As Integer = 5
Const miTestSireChk As Integer = 0
Const miDateTestSire As Integer = 2
Const miRemark As Integer = 0
Const miDamMat As Integer = 2 'The Mate form's controls' indexes.
Const miSireMat As Integer = 9
Const miDateMat As Integer = 3
Const miFlexMat As Integer = 0
Const miDamLmK As Integer = 3 'The LmK form's controls' indexes.
Const miDateLmK As Integer = 4
Const miAbortChk As Integer = 1
Const miOptLmKAliv As Integer = 4
Const miLmKLmK As Integer = 10
Const miSexLmK As Integer = 7
Const miWtBirth As Integer = 0
Const miOptLmKDead As Integer = 5
Const miLiv As Integer = 8
Const miLvwOffsp As Integer = 0
Const miFlexLmK As Integer = 1
Const miLmKWtLmK As Integer = 4 'The WtLmK form's controls' indexes.
Const miDateWean As Integer = 5
Const miWtWean As Integer = 1
Const miDate7Mon As Integer = 6
Const miWt7Mon As Integer = 2
Const miShGWtWool As Integer = 5 'The WtWool form's controls' indexes.
Const miDateAnnl As Integer = 7
Const miWtAnnl As Integer = 3
Const miDateShearAnnl As Integer = 8
Const miGreaseAnnl As Integer = 4
Const miFlexWtWool As Integer = 2
Const miShGAppr As Integer = 6 'The Appr form's controls' indexes.
Const miDateAppr As Integer = 9
Const miLeng As Integer = 5
Const miDiam As Integer = 9
Const miDiamFromLbl As Integer = 3
Const miDiamToLbl As Integer = 5
Const miMass As Integer = 10
Const miCrimpins As Integer = 11
Const miEvens As Integer = 12
Const miDensity As Integer = 6
Const miStrength As Integer = 13
Const miColour As Integer = 14
Const miQuality As Integer = 15
Const miFluffColour As Integer = 16
Const miFluff As Integer = 7
Const miFibreYield As Integer = 8
Const miBodyType As Integer = 17
Const miConstitutn As Integer = 18
Const miBodySize As Integer = 19
Const miFatTail As Integer = 20
Const miDefct As Integer = 21
Const miLvwInhertDefct As Integer = 1
Const miFlexAppr As Integer = 3

Const miFraBirth As Integer = 8 'The frames.

Const mintBndMat As Integer = 0 'The Mate/LmK grids' bands.
Const mintBndLmK As Integer = 1
Const mintBndOffsp As Integer = 2
Const mintColCycle As Integer = 0 'The Mate/LmK grids' columns.
Const mintColDateMat As Integer = 2
Const mintColDateLmK As Integer = 0
Const mintColWtBirth As Integer = 2
Const mintBndWtWool As Integer = 0 'The WtWool band.
Const mintBndWoolExtr As Integer = 0 'The Appr grids' Wool/Exterior band.
Const mintColAge As Integer = 0 'The Appr grids' columns.
Const mintColDateAppr As Integer = 1
Const mintColLeng As Integer = 2
Const mintIndtEscShift As Integer = 75 'The indent from grids' right side to escape
                                       'shifting rows when the last column is clicked.
Const mintItemLiv As Integer = 3 'The Livability ListSubItems in the lvwList(miLvwOffsp)
                                 'list view.
Dim mcolMsgs As Collection
Dim mobUtilBrsMatLmK As UtilBrs
Dim mobUtilBrsWtWool As UtilBrs
Dim mobUtilBrsAppr As UtilBrs

Dim mobDatFrm As DatFrm
Dim mstrIDFrm As String
Dim mstrIDFrmLast As String
Dim mintMode() As Integer
Dim mstrFrmHostNam As String
Dim mstrFrmHostCapt As String
Dim mblnFrmFilld() As Boolean
Dim mintIsDirty() As Boolean

Dim mblnEscTabClick As Boolean

Dim mblnRefrshSusp As Boolean
Dim mblnRefrshResm As Boolean

' Implement the clicked check box's operation.
Private Sub chkFld_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miTestSireChk 'Test Sire contorls.
      Select Case chkFld(miTestSireChk)
      Case vbChecked
         Call SwchTestSireDate(True)
      Case vbUnchecked
         Call SwchTestSireDate(False)
      End Select
   Case miAbortChk
      Call SwchAbort 'Switch the offspring controls.
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected cmdDel button's operation.
Private Sub cmdAdd_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miLvwOffsp
      Call ClickAddLmK
   Case miLvwInhertDefct
      Call ClickAddAppr
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected cmdDel button's operation.
Private Sub cmdDel_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miLvwOffsp
      Call ClickDelLmK
   Case miLvwInhertDefct
      Call ClickDelAppr
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open the frmBrdCrs, frmTransFarm forms.
Private Sub cmdDlg_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miBrdCrsCmd 'Open frmBrdCrs.
      Load frmBrdCrs
      With mobDatFrm
         Call frmBrdCrs.InitFrm(gobShGs(.IDFrm), False, .Mode, optFld(miOptBrdPure), _
            dbcFld(miBrdPure), txtMisc(miBrdCrsTxt))
      End With
      frmBrdCrs.Show vbModal
   Case miTransFarmCmd 'Open the frmTransFarm form.
      Load frmTransFarm
      With frmTransFarm 'Set frmBrdCrs's parameters.
         Set .DatFrmCallFrm = mobDatFrm
         Set .FarmDbc = dbcFld(miFarm)
         .Show vbModal
      End With
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' - For miShGInven to miShGAppr:
' Open the frmBrsShG form.
' Set the frmBrsShG.DatFrmEntr parameter to True in the Edit/Del modes. Set it to False
'  in the Add one to prevent adding a duplicate IDShG.
' - For miSireInven:
' To miLmKLmK: Open the dam's frmShG form.
Private Sub cmdID_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miShGInven To miShGAppr
      With frmBrsShG 'frmBrsShG: pass this form's parameters.
          Set .FrmCall = Me
         .FrmCallNam = gobSetng.FrmNamByIdx(tabShG.SelectedItem.Index) 'Get the data form's name.
         Set .IDTxt = mobDatFrm.IDCtl
         Set .CmdButton = cmdID(tabShG.SelectedItem.Index)
         If tabShG.SelectedItem.Index = gobSetng.FrmInvenIdx Then 'Require Enter for:
            .DatFrmEntr = IIf(mobDatFrm.Mode = gobSetng.ModeAdd, False, True) 'Inven;
         Else
            .DatFrmEntr = True 'The rest data forms.
         End If
         .FrmCallNew = False
         .RefrshTreeDo 'Refresh the tree veiw, if necessary.
      End With
      frmBrsShGShow.cmdShG = True
   Case miSireInven To miLmKLmK
      With gobSetng 'Enable opening the Inven data form.
         .LastTabShG = .FrmInvenIdx
      End With
      Call SrDmLoad(txtID(Index))
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the lblMisc(miDiamFromLbl) & lblMisc(miDiamToLbl) controls.
Private Sub dbcFld_Change(Index As Integer)
On Error GoTo ErrHnd
   If Index = miDiam Then Call RefrshDiam
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del for the DropDownList type of comboboxes, except the Complex Class one.
' Enable Esc.
Private Sub dbcFld_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel 'Del.
         If dbcFld(Index).Style = dbcDropdownList Then
            If Index <> miCompClass Then dbcFld(Index).BoundText = "" 'Except ComplClas
         End If
      Case .CodeEsc 'Esc.
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Type farm in upper case.
Private Sub dbcFld_KeyPress(Index As Integer, KeyAscii As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miFarm, miFarmBirth
      KeyAscii = gobFormtCtl.UpCase(KeyAscii)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Verify that the farm exist in the DB.
' Verify the sheep/goat's sex change in the Edit mode.
' Validate changing the ShG's basic breed in the Edit mode.
Private Sub dbcFld_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   With mobDatFrm
      Select Case Index
      Case miFarm 'Validate the farm.
         Cancel = Not gobFormtCtl.VldFarm(dbcFld(Index), gobShGs(.IDFrm).TblShG _
            .IDFarmOrig)
      Case miFarmBirth 'Validate the birth farm.
         Cancel = Not gobFormtCtl.VldFarm(dbcFld(Index), gobShGs(.IDFrm).TblShG _
            .IDFarmBirthOrig)
      Case miSexInven 'Validate the sex.
         If .Mode = gobSetng.ModeEdit Then Cancel = Not VldSex
      Case miBrdPure 'Validate changing the basic breed.
         If .Mode = gobSetng.ModeEdit Then Cancel = Not gobFormtCtl.VldIDBrdSpcs( _
            dbcFld(miBrdPure), gobShGs(.IDFrm), False)
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Convert the selected date from the dtpDate control to the adjacent txtDate text box.
Private Sub dtpDate_CloseUp(Index As Integer)
On Error GoTo ErrHnd
   txtDate(Index) = DateValue(dtpDate(Index).Value)
   txtDate(Index).SetFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter.
Private Sub flexGrid_DblClick(Index As Integer)
On Error GoTo ErrHnd
   Call flexGrid_KeyPress(Index, gobFormtCtl.AscEnter)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing Enter, show the selected record from a grid in the respective data form.
Private Sub flexGrid_KeyPress(Index As Integer, KeyAscii As Integer)
On Error GoTo ErrHnd
   If KeyAscii = gobFormtCtl.AscEnter Then 'Proceed on Enter.
      Select Case Index
      Case miFlexMat, miFlexLmK
         Call ShowMatLmK(Index)
      Case miFlexWtWool
         Call ShowWtWool
      Case miFlexAppr
         Call ShowAppr
      End Select
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the form's parameters.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Const lngWdth As Long = 10815 '11070
   Const lngHght As Long = 6405 '6375
   ReDim mintMode(gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx) As Integer
   ReDim mblnFrmFilld(gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx) As Boolean
   ReDim mintIsDirty(gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx) As Boolean
   Set mcolMsgs = New Collection
   Set mobDatFrm = Me
   mobDatFrm.FrmHostCaptOrig = Me.Caption
   Set mobUtilBrsMatLmK = New UtilBrs 'Initialise the browse utility objects.
   mobUtilBrsMatLmK.CyclAgeCol = mintColCycle
   Set mobUtilBrsWtWool = New UtilBrs
   Set mobUtilBrsWtWool.Grid = flexGrid(miFlexWtWool)
   mobUtilBrsWtWool.CyclAgeCol = mintColAge
   Set mobUtilBrsAppr = New UtilBrs
   Set mobUtilBrsAppr.Grid = flexGrid(miFlexAppr)
   mobUtilBrsAppr.CyclAgeCol = mintColAge
   tabShG.Tabs(gobSetng.LastTabShG).Selected = True 'Show the last data form.
   Call InitTxt(True) 'Initialise text boxes.
   Call frmMDI.SwchMnuWin(True) 'Switch the menu & toolbar buttons.
   Call frmMDI.WinPosn(Me, lngWdth, lngHght) 'Place the the window & adjust its size.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resize the tabShG & linBtn lines.
Private Sub Form_Resize()
On Error GoTo ErrHnd
   Const intDistTabBtn As Integer = 120 'The distance between tabShG & cmdOk/cmdCancel.
   Dim lngLeftOk As Long
   Dim lngLeftCanc As Long
   Dim lngTopBtn As Long
   With Me
      gobSetng.FrmChldStat = .WindowState 'Save the state.
      lngLeftOk = .ScaleWidth - cmdOk.Width - cmdCancel.Width - gobSetng.IndtCtlOkCanc _
         - gobSetng.IndtCtlRght
      lngLeftOk = IIf(lngLeftOk > 0, lngLeftOk, 0) 'Must be positive.
      lngLeftCanc = .ScaleWidth - cmdCancel.Width - gobSetng.IndtCtlRght
      lngLeftCanc = IIf(lngLeftCanc > 0, lngLeftCanc, 0) 'Must be positive.
      lngTopBtn = .ScaleHeight - cmdOk.Height - intDistTabBtn
      lngTopBtn = IIf(lngTopBtn > 0, lngTopBtn, 0) 'Must be positive.
      cmdOk.Move lngLeftOk, lngTopBtn
      cmdCancel.Move lngLeftCanc, lngTopBtn
      tabShG.Move .ScaleLeft, .ScaleTop, .ScaleWidth, lngTopBtn + intDistTabBtn
   End With
   Call ReszFram 'Resize the edge frames.
   Call ReszGrid 'Resize the grids.
   cmdOk.ZOrder 0 'Keep on top.
   cmdCancel.ZOrder 0
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resize the edge frames along with the tabShG frame.
Private Sub ReszFram()
On Error GoTo ErrHnd
   Dim I As Integer
   For I = 1 To tabShG.Tabs.Count
      With tabShG
         fraFrame(I).Move .ClientLeft, .ClientTop, .ClientWidth, .ClientHeight
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display the File menu as a pop-up menu.
Private Sub fraFrame_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x _
   As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub optFld_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miOptBrdPure To miOptDisp
      Call BrdTransDisp(Index)
   Case miOptLmKAliv, miOptLmKDead
      Call LmKAlivDead(Index)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resume refreshing the ado's after the gcnnConn connection's active transaction.
Private Property Let SetngFrm_RefrshResm(ByVal blnRefrshResm As Boolean)
   mblnRefrshResm = blnRefrshResm
End Property

Private Property Get SetngFrm_RefrshResm() As Boolean
   SetngFrm_RefrshResm = mblnRefrshResm
End Property

' Suspend refreshing the ado's due to the gcnnConn connection's active transaction.
Private Property Let SetngFrm_RefrshSusp(ByVal blnRefrshSusp As Boolean)
   mblnRefrshSusp = blnRefrshSusp
End Property

Private Property Get SetngFrm_RefrshSusp() As Boolean
   SetngFrm_RefrshSusp = mblnRefrshSusp
End Property

' Initialise the text boxes of the selected data form, unless it's filled. If one of the
'  frmShG form data forms is filled but the selected one is empty fill the latter form.
' Switch on the active tab's controls' TabStop's & switch off the previous tab's.
' Bring to the front the selected tab's frame.
Private Sub tabShG_Click()
On Error GoTo ErrHnd
   Static intIdxPrev As Integer
   If Not mblnEscTabClick Then 'Proceed, unless escaped.
      With tabShG.SelectedItem
         gobSetng.LastTabShG = .Index 'Save the index.
         Call InitCtlSwch 'Initialise & switch the selected data form's controls.
         Call frmMDI.SwchMnuMode(mobDatFrm.Mode) 'Switch the menu.
         cmdOk.Enabled = mblnFrmFilld(.Index) 'Switch cmdOk.
         If Not mblnFrmFilld(.Index) Then Call InitTxt(False) 'Initialise.
         If intIdxPrev = 0 Then intIdxPrev = IIf(.Index = gobSetng.FrmInvenIdx, _
            gobSetng.FrmMatIdx, gobSetng.FrmInvenIdx) 'Initialise intIdxPrev 1st time.
         If intIdxPrev <> .Index Then
            Call SwchVisibleTabStop(.Index, True) 'The active TabStop's on.
            If intIdxPrev = 0 Then intIdxPrev = gobSetng.FrmInvenIdx 'Initialse the prev. index.
            Call SwchVisibleTabStop(intIdxPrev, False) 'The previous TabStop's off.
            intIdxPrev = .Index 'Remember for later use.
         End If
         fraFrame(.Index).ZOrder 0 'Bring the frame to front.
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resize the grids along with the form.
' Resize the grids' columns, if the respective forms are filled.
Private Sub ReszGrid()
On Error GoTo ErrHnd
   Const intHghtAdd As Integer = 120 'Additional height for the grids.
   Dim flexCtl As MSHFlexGrid
   Dim lngWdth As Long
   Dim lngHght As Long
   Dim intIdx As Integer
   For Each flexCtl In flexGrid
      With fraFrame(tabShG.SelectedItem.Index)
         lngWdth = .Width - flexCtl.Left - gobSetng.IndtCtlRght
         lngHght = .Height - flexCtl.Top - gobSetng.IndtCtlRght + intHghtAdd
         lngWdth = IIf(lngWdth > 0, lngWdth, 0) 'Must be positive.
         lngHght = IIf(lngHght > 0, lngHght, 0)
         flexCtl.Width = lngWdth
         flexCtl.Height = lngHght
         Select Case intIdx 'Resize the columns, if filled.
         Case miFlexMat
            If mblnFrmFilld(gobSetng.FrmMatIdx) Then Call ReszColMatLmK
         Case miFlexLmK
            If mblnFrmFilld(gobSetng.FrmLmKIdx) Then Call ReszColMatLmK
         Case miFlexWtWool
            If mblnFrmFilld(gobSetng.FrmWtWoolIdx) Then Call ReszColWtWool
         End Select
         intIdx = intIdx + 1 'Increase the grid index.
      End With
   Next
'   flexGrid(miFlexWtWool).Height = flexGrid(miFlexWtWool).Height - intHghtAdd 'Decrease the wt/wool grid's height.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the form, if it's clear.
' Cancel the changes.
' Clear the controls.
' Return the focus to the ID text box.
Public Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If mobDatFrm.IsDirty Then 'Cancel.
      mobDatFrm.Cancel True
      Call InitTxt(True) 'Initialise text boxes.
      cmdCancel.SetFocus 'Focus cmdCancel to invoke the txtShG_GotFocus proc.
      txtID(tabShG.SelectedItem.Index).SetFocus
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected data form's cmdCancel_Click operation.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   With gobSetng
      Select Case tabShG.SelectedItem.Index
      Case .FrmInvenIdx
         Call ClickOkInven
      Case .FrmMatIdx
         Call ClickOkMat
      Case .FrmLmKIdx
         Call ClickOkLmK
      Case .FrmWtLmKIdx
         Call ClickOkWtLmK
      Case .FrmWtWoolIdx
         Call ClickOkWtWool
      Case .FrmApprIdx
         Call ClickOkAppr
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected data form's DatFrm_CtlClear operation.
Private Sub DatFrm_CtlClear()
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      txtID(miShGInven) = ""
      Call CtlClearTxtDbc(txtID, miSireInven, miDamInven)
      Call CtlClearTxtDbc(dbcFld, miFarm, miBrdPure)
      Call CtlClearDate(miDateBirth, miDateTestSire)
      Call CtlClearTxtDbc(txtMisc, miRemark, miBrdCrsTxt)
      chkFld(miTestSireChk) = vbUnchecked
   Case gobSetng.FrmMatIdx
      txtID(miDamMat) = ""
      txtID(miSireMat) = ""
      Call CtlClearDate(miDateMat, miDateMat)
   Case gobSetng.FrmLmKIdx
      txtID(miDamLmK) = ""
      txtID(miLmKLmK) = ""
      Call CtlClearDate(miDateLmK, miDateLmK)
      chkFld(miAbortChk) = vbUnchecked
      Call CtlClearTxtDbc(dbcFld, miSexLmK, miLiv)
      txtNum(miWtBirth) = ""
      lvwList(miLvwOffsp).ListItems.Clear
   Case gobSetng.FrmWtLmKIdx
      txtID(miLmKWtLmK) = ""
      Call CtlClearDate(miDateWean, miDate7Mon)
      Call CtlClearTxtDbc(txtNum, miWtWean, miWt7Mon)
   Case gobSetng.FrmWtWoolIdx
      txtID(miShGWtWool) = ""
      Call CtlClearDate(miDateAnnl, miDateShearAnnl)
      Call CtlClearTxtDbc(txtNum, miWtAnnl, miGreaseAnnl)
   Case gobSetng.FrmApprIdx
      txtID(miShGAppr) = ""
      Call CtlClearDate(miDateAppr, miDateAppr)
      Call CtlClearTxtDbc(txtNum, miLeng, miFibreYield)
      Call CtlClearTxtDbc(dbcFld, miDiam, miDefct)
      Call RefrshDiam 'Reset lblMisc(miDiamFromLbl) & lblMisc(miDiamToLbl).
      lvwList(miLvwInhertDefct).ListItems.Clear
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub DatFrm_CtlWrite()
'If necessary modify the code to use this procedure in conjunction with DatFrm_DBtoFrm.
End Sub

' Implement the selected data form's DatFrm_CtlRead operation.
Private Sub DatFrm_CtlRead()
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      Call CtlReadInven
   Case gobSetng.FrmMatIdx
      Call CtlReadMat
   Case gobSetng.FrmLmKIdx
      Call CtlReadLmK
   Case gobSetng.FrmWtLmKIdx
      Call CtlReadWtLmK
   Case gobSetng.FrmWtWoolIdx
      Call CtlReadWtWool
   Case gobSetng.FrmApprIdx
      Call CtlReadAppr
   End Select
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

Private Property Get DatFrm_FrmHostNam() As String
    DatFrm_FrmHostNam = mstrFrmHostNam
End Property

' Get the IsDirty property for each data form of the 6 separately.
Private Property Get DatFrm_IDCtl() As TextBox
On Error GoTo ErrHnd
   Set DatFrm_IDCtl = txtID(tabShG.SelectedItem.Index)
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Let & get IDShG to identify this data form.
' Unless the new ID is blank save it for later use.
Private Property Let DatFrm_IDFrm(ByVal strIDFrm As String)
On Error GoTo ErrHnd
   mstrIDFrm = strIDFrm
    If strIDFrm <> "" Then
      mstrIDFrmLast = strIDFrm
      gobDatFrms.IDFrmLastSet strIDFrm, Me.Name
   End If
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get IDShG to identify this data form.
Private Property Get DatFrm_IDFrm() As String
On Error GoTo ErrHnd
   DatFrm_IDFrm = mstrIDFrm
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Implements or not the SetngFrm class.
Private Property Get DatFrm_IsSetngFrm() As Boolean
   DatFrm_IsSetngFrm = True
End Property

' Shwitch on/off the data form's controls based on the selected data form.
Private Sub DatFrm_SwchCtlFill(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   cmdOk.Enabled = blnEnable
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      Call SwchCtlFillInven(blnEnable, blnEnableID)
   Case gobSetng.FrmMatIdx
      Call SwchCtlFillMat(blnEnable)
   Case gobSetng.FrmLmKIdx
      Call SwchCtlFillLmK(blnEnable)
   Case gobSetng.FrmWtLmKIdx
      Call SwchCtlFillWtLmK(blnEnable)
   Case gobSetng.FrmWtWoolIdx
      Call SwchCtlFillWtWool(blnEnable)
   Case gobSetng.FrmApprIdx
      Call SwchCtlFillAppr(blnEnable)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected data form's DatFrm_SwchCtlMode operation.
Private Sub DatFrm_SwchCtlMode()
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      Call SwchCtlModeInven
   Case gobSetng.FrmMatIdx
      Call SwchCtlModeMat
   Case gobSetng.FrmLmKIdx
      Call SwchCtlModeLmK
   Case gobSetng.FrmWtLmKIdx
      Call SwchCtlModeWtLmK
   Case gobSetng.FrmWtWoolIdx
      Call SwchCtlModeWtWool
   Case gobSetng.FrmApprIdx
      Call SwchCtlModeAppr
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
' Switch the controls to save a new ID.
Private Sub SwchCtlModeInven()
On Error GoTo ErrHnd
   Select Case mintMode(gobSetng.FrmInvenIdx) 'Switch by mode.
   Case gobSetng.ModeAdd
      Call DatFrm_SwchCtlFill(True, False)
      dbcFld(miFarm).SetFocus
   Case gobSetng.ModeEdit
      Call DatFrm_SwchCtlFill(True, True)
      txtID(miShGInven).Enabled = True
      txtID(miShGInven).SetFocus
   Case gobSetng.ModeDel
      txtID(miShGInven).Enabled = False
      cmdID(miShGInven).Enabled = False
      If optFld(miOptBrdCrs) Then Call SwchBrdCrs(False) 'Disable Cross Breed after purebred ShG
      Call SwchTestSireDate(False) 'Disable the Test Sire controls.
      cmdOk.Enabled = True
      cmdOk.SetFocus
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected data form's DatFrm_Vld operation.
' Return True, if succeeds.
Private Function DatFrm_Vld() As Boolean
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      DatFrm_Vld = VldInven
   Case gobSetng.FrmMatIdx
      DatFrm_Vld = VldMat
   Case gobSetng.FrmLmKIdx
      DatFrm_Vld = VldLmK
   Case gobSetng.FrmWtLmKIdx
      DatFrm_Vld = VldWtLmK
   Case gobSetng.FrmWtWoolIdx
      DatFrm_Vld = VldWtWool
   Case gobSetng.FrmApprIdx
      DatFrm_Vld = VldAppr
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function VldInven() As Boolean
On Error GoTo ErrHnd
   If VldFillCtlInven Then 'Filling the controls.
      Call CtlReadBirthDisp 'Refresh the birth date & the date & reason of disp.
      With gobShGs(mobDatFrm.IDFrm)
         If VldAgeSrDm(txtID(miSireInven), miSireInven) Then 'The sire's age.
            If VldAgeSrDm(txtID(miDamInven), miDamInven) Then 'The dam's age.
               If VldDate(miDateDisp, .TblShG.DateDispOrig, optFld(miOptDisp).Caption) _
                  Then 'Disp.
                  If VldDate(miDateTestSire, .TblTestSire.DateTestSireOrig, _
                     LoadResString(573)) Then 'Test sire date.
                     If mobDatFrm.Mode <> gobSetng.ModeEdit Then
                        VldInven = True 'Succeeded.
                     Else 'Proceed, in the Edit mode.
                        If VldAgeMatLmK Then 'The age at matings & lamb/kiddings.
                           If VldAgeWean7Mon Then 'The age at wean/7-mon.
                              If VldAgeWtWool Then 'The age at wt/wool's.
                                 If VldAgeAppr Then VldInven = VldTrans 'The age at
                              End If                       'appraisals & transfers.
                           End If
                        End If
                     End If
                  End If
               End If
            End If
         End If
      End With
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Switch the Edit tool bar's buttons & the Edit menu.
' Focus the active data form's ID after loading the form.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   Call frmMDI.SwchMnuMode(mobDatFrm.Mode)
   If Not blnPassed Then 'Focus ID once.
      blnPassed = True
      With txtID(tabShG.SelectedItem.Index)
         If .Enabled And .Visible Then .SetFocus
      End With
   End If
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

' Display a pop-up File menu on the right-mouse click.
Private Sub Form_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cancel the current changes.
' Switch controls.
' Nullify this data form's marks.
' Re-register the data form under zero-length-string ID, uless any other data form is
'  registered.
' Switch the menu & toolbar.
' Reset the gobMsgInst object.
Private Sub DatFrm_Cancel(ByVal blnCtlClear As Boolean)
On Error GoTo ErrHnd
   Call Cancel1st(blnCtlClear) 'Implement the 1st part.
   If Not DatFrmFilldAny(tabShG.SelectedItem.Index) Then Call DatFrm_RegistFrm("", True) 'Important: Re-register after DatFrm_CtlClear!
   gobMsgInst.Rest Me 'Reset gobMsgInst.
   If Not DatFrmFilldAny(tabShG.SelectedItem.Index) Then Call Util.FrmCapt(mobDatFrm, _
      False) 'Reset the form's caption, unless another data form is filled.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected data form's DatFrm_FrmToDB operation.
Private Sub DatFrm_FrmToDB()
On Error GoTo ErrHnd
   Dim obSetngFrm As SetngFrm
   gobDatFrms.UnldEmpt mstrIDFrm, mstrFrmHostNam
   Set obSetngFrm = Me 'Suspend refreshing the ado's due to the gcnnConn connection's active transaction.
   obSetngFrm.RefrshSusp = True
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      Call FrmToDBInven
   Case gobSetng.FrmMatIdx
      Call FrmToDBMat
   Case gobSetng.FrmLmKIdx
      Call FrmToDBLmK
   Case gobSetng.FrmWtLmKIdx
      Call FrmToDBWtLmK
   Case gobSetng.FrmWtWoolIdx
      Call FrmToDBWtWool
   Case gobSetng.FrmApprIdx
      Call FrmToDBAppr
   End Select
   With obSetngFrm
      .RefrshSusp = False 'Resume refreshing the ado's
      Call frmMDI.RefrshSetng(False)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Write the controls' content to the the ShG object associated with the data form
'  to put it into the DB.
' Roll back operations on the SQL server's error.
Private Sub FrmToDBInven()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim blnConfmChanID As Boolean
   gcnnConn.BeginTrans 'Begin transaction.
   With gobShGs(mstrIDFrm)
      Set obDatTbl = .TblShG
      If mintMode(gobSetng.FrmInvenIdx) = gobSetng.ModeDel Then
         obDatTbl.Del 'Deletion.
      Else
         Call DatFrm_CtlRead 'Read the data.
         Select Case mintMode(gobSetng.FrmInvenIdx) 'Accomplish the mode's opertation.
         Case gobSetng.ModeAdd
            obDatTbl.Ins
            blnConfmChanID = True 'Default for later use.
            If Not gobMsgInst.SQLErr(Me) Then Call FrmToDBTestSire 'Update TblTestSire.
         Case gobSetng.ModeEdit
            blnConfmChanID = ConfmChanID 'Verify an IDShG change.
            If blnConfmChanID Then
               obDatTbl.Upd
               If Not gobMsgInst.SQLErr(Me) Then 'Update the complex class, if any.
                  If .TblSelIdxCC.Full Then
                     Set obDatTbl = .TblSelIdxCC
                     obDatTbl.Upd
                  End If
                  If Not gobMsgInst.SQLErr(Me) Then Call FrmToDBTestSire 'Update
               End If                                                   'TblTestSire.
            End If
         End Select
' REF. TO DO 1.
         If Not gobMsgInst.SQLErr(Me) And blnConfmChanID Then 'Insert the cross breeds
            With .TblShG                '& farm transfers, if no errors in ShGIns/ShGUpd.
               If .BrdCrsChand And .Crs Then
                  .BrdCrsDel    'This deletion duplicates that from the CtlReadInven
                  .BrdCrsInsNew 'procedure to prevent that strange PK violation in the
               End If           'BreedCross table. I couldn't find a beeter solution.
               If .TransFarmChand Then .TransFarmInsNew
            End With
         End If
      End If
   End With
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Get Mode of each data form separately.
Private Property Get DatFrm_Mode() As Integer
On Error GoTo ErrHnd
   DatFrm_Mode = mintMode(tabShG.SelectedItem.Index)
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Set the form's mode to the specified option unless there is unsaved data.
Private Sub DatFrm_ModeSet(ByVal intMode As Integer)
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   mintMode(tabShG.SelectedItem.Index) = intMode
   Call frmMDI.SwchMnuMode(intMode)
   If Not blnPassed Then 'Initialise all data forms' modes once.
      blnPassed = True
      Call InitMode(intMode)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable a clicked option's controls to input data.
Private Sub BrdTransDisp(ByVal intIdx As Integer)
On Error GoTo ErrHnd
   Select Case intIdx
   Case miOptBrdPure
      dbcFld(miBrdPure).Enabled = True
      Call SwchBrdCrs(False) 'Cross Breed controls off.
   Case miOptBrdCrs
      Call SwchBrdCrs(True) 'Cross Breed controls on.
      dbcFld(miBrdPure).Enabled = False
   Case miOptTransFarm
      cmdDlg(miTransFarmCmd).Enabled = True
      txtDate(miDateDisp).Enabled = False
      lblDate(miDateDisp).Enabled = False
      dtpDate(miDateDisp).Enabled = False
      lblFld(miDispReas).Enabled = False
      dbcFld(miDispReas).Enabled = False
   Case miOptDisp
      lblDate(miDateDisp).Enabled = True
      txtDate(miDateDisp).Enabled = True
      dtpDate(miDateDisp).Enabled = True
      lblFld(miDispReas).Enabled = True
      dbcFld(miDispReas).Enabled = True
      cmdDlg(miTransFarmCmd).Enabled = False
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh all settings-relevant Ado's.
' If this form invoked refreshing the ado's suspend it & resume after committing the
'  gcnnConn connection's active transaction.
Private Sub SetngFrm_RefrshAdo()
On Error GoTo ErrHnd
   Call RefrshInitAdo(adoFld(miFarm))
   Call RefrshInitAdo(adoFld(miBrdPure))
   Call RefrshInitAdo(adoFld(miDefct))
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the Ado control.
' Set its connection string first, if not yet.
Private Sub RefrshInitAdo(ByRef adoCtl As Adodc)
On Error GoTo ErrHnd
   With adoCtl
      If .ConnectionString <> gcnnConn.ConnectionString Then .ConnectionString = _
         gcnnConn.ConnectionString
      .Refresh
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub SetngFrm_SyncBrs()
'Empty.
End Sub

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub IDCtlPressInven(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm) 'Set the menu & IsDirty mark.
      If intKeyAscii <> gobFormtCtl.AscEnter Then
         intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
      Else
         intKeyAscii = 0 'Cancel Enter
         If Not mblnFrmFilld(gobSetng.FrmInvenIdx) Then 'Proceed, unless filled.
            If Len(Trim$(txtID(miShGInven))) = gobFormtCtl.LengIDShG Then 'Proceed corresponding to the mode.
               .RegistFrm Trim$(txtID(miShGInven)), True 'Register the form.
               If gobMsgInst.DuplFrm Then 'Avoid duplication by ivoking the LostFocus
                  cmdCancel.SetFocus      'procedure.
               Else
                  .DBtoFrm 'Fill the form in an Edit/Del mode.
                  Select Case mobDatFrm.Mode 'Check the operation's feedback by mode.
                  Case gobSetng.ModeEdit, gobSetng.ModeDel 'Edit/Del modes.
                     If Not gobShGs(.IDFrm).TblShG.Full Then blnFail = True 'Failed.
                  Case gobSetng.ModeAdd 'Add mode.
                     If gobShGs(.IDFrm).TblShG.Full Then 'Adding a duplicate IDShG.
                        blnFail = True 'Mark the error.
                        MsgBox LoadResString(73), vbExclamation, LoadResString(50)
                     End If
                  End Select
                  If Not blnFail Then
                     mblnFrmFilld(gobSetng.FrmInvenIdx) = True 'Mark filling the form.
                     .SwchCtlMode 'Switch controls by mode.
                  Else
                     .Cancel False 'Cancel the current changes, if any.
                     txtID(miShGInven).SetFocus
                  End If
               End If
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mcolMsgs collection to the gobMsgInst object to read/write messages to the form.
Private Property Get MsgRecip_Msgs() As Collection
   Set MsgRecip_Msgs = mcolMsgs
End Property

' Implement the selected data form's DatFrm_DBtoFrm operation.
Private Sub DatFrm_DBtoFrm()
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      Call DBtoFrmInven
   Case gobSetng.FrmMatIdx
      Call DBtoFrmMat
   Case gobSetng.FrmLmKIdx
      Call DBtoFrmLmK
   Case gobSetng.FrmWtLmKIdx
      Call DBtoFrmWtLmK
   Case gobSetng.FrmWtWoolIdx
      Call DBtoFrmWtWool
   Case gobSetng.FrmApprIdx
      Call DBtoFrmAppr
   End Select
   Call Util.FrmCapt(mobDatFrm, True) 'Set the form's caption.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the DB to the ShG object to fill out this form & its child, frmBrdCrs.
' Supply the data to this form's controls from the ShG object.
Private Sub DBtoFrmInven()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm)
      Select Case mintMode(gobSetng.FrmInvenIdx)
      Case gobSetng.ModeAdd 'Add mode.
         .TblShG.EscIDShGWrng = True 'Cancel the IDShGWrong message.
         .SelShG True 'Populate obTblShG'Populate obTblShG.
      Case gobSetng.ModeEdit, gobSetng.ModeDel 'Edit/Del mode
         .SelShG True 'Populate obTblShG'Populate obTblShG.
         If .TblShG.Full Then Call CtlWriteInven(gobShGs(mstrIDFrm)) 'Check if ShG exists & fill.
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the controls from the specified obTblAppr object.
Private Sub CtlWriteInven(ByVal obShG As ShG)
On Error GoTo ErrHnd
   Call DatFrm_CtlClear 'Clear & reinitialise the controls.
   Call InitTxt(True)
   With obShG
      With .TblShG
         dbcFld(miFarm).BoundText = .IDFarm
         dbcFld(miSexInven).BoundText = .IDSex
         If .Crs Then 'Purebred or crossbred.
            optFld(miOptBrdCrs) = True
            txtMisc(miBrdCrsTxt) = .BrdCrs
            dbcFld(miBrdPure).BoundText = ""
            If Not .PopltBrdCrs Then .BrdCrsSel 'Populate cross breeds, unless
         Else                                       'populated.
            optFld(miOptBrdPure) = True
            dbcFld(miBrdPure).BoundText = .IDBrdBas
             txtMisc(miBrdCrsTxt) = ""
         End If
         gobFormtCtl.WriteDate txtDate(miDateBirth), dtpDate(miDateBirth), .DateBirth
'         txtDate(miDateBirth) = .DateBirth
         txtID(miSireInven) = .IDSire
         txtID(miDamInven) = .IDDam
         dbcFld(miTypeBirth).BoundText = .TypeBirth
         dbcFld(miFarmBirth).BoundText = .IDFarmBirth
         .TransFarmSel 'Prepare data for frmTransFarm.
         If .DateDisp > 0 Then gobFormtCtl.WriteDate txtDate(miDateDisp), dtpDate( _
            miDateDisp), .DateDisp
         dbcFld(miDispReas).BoundText = .IDDispReas
         txtMisc(miRemark) = .Remark
      End With
      dbcFld(miCompClass).BoundText = .TblSelIdxCC.IDCompClass 'Fill/clear dbcFld(miCompClass)
      If .TblTestSire.Full Then 'Test sire.                   'based on if CC is present.
         chkFld(miTestSireChk) = vbChecked
         gobFormtCtl.WriteDate txtDate(miDateTestSire), dtpDate(miDateTestSire), _
            .TblTestSire.DateTestSire
      Else
         chkFld(miTestSireChk) = vbUnchecked
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' REF. TO DO 1.
' Adjust the breed options to make sure the user inputs cross breeds again each time
'  without the record-to-record data carring feature.
Private Sub BrdPureOption()
On Error GoTo ErrHnd
   If optFld(miOptBrdCrs) Then
      optFld(miOptBrdPure) = True
      dbcFld(miBrdPure).BoundText = Left$(txtMisc(miBrdCrsTxt), 2)
      txtMisc(miBrdCrsTxt) = ""
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the forms' ID controls & number text boxes.
' If the blnClearPrev argument is True clear the previous value, otherwise unless the
'  textbox is blank keep the previous value.
Private Sub InitTxt(ByVal blnClearPrev As Boolean)
On Error GoTo ErrHnd
   If mstrIDFrmLast = "" Then 'Set the last ID.
      txtID(tabShG.SelectedItem.Index) = gobDatFrms.IDFrmLast(Me.Name)
   Else
      txtID(tabShG.SelectedItem.Index) = mstrIDFrmLast
   End If
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmLmKIdx
      Call InitTxtLmK(blnClearPrev)
   Case gobSetng.FrmWtLmKIdx
      Call InitTxtWtLmK(blnClearPrev)
   Case gobSetng.FrmWtWoolIdx
      Call InitTxtWtWool(blnClearPrev)
   Case gobSetng.FrmApprIdx
      Call InitTxtAppr(blnClearPrev)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
                                
' Confirm changing IDShG.
' Return True, if either confirmed or no change took place.
' If the change is denied restore the previous ShGID in the txtID(miShGInven) just to
'  show it to the user.
' To bring about the change, unload all data forms of the specifiec ShG.
Private Function ConfmChanID() As Boolean
On Error GoTo ErrHnd
   Dim intResp As Integer
   If txtID(miShGInven) = mobDatFrm.IDFrm Then
      ConfmChanID = True 'The same ID - confirmation is unnecessary.
   Else
      Beep
      intResp = MsgBox(LoadResString(310) & mobDatFrm.IDFrm & LoadResString(311) & _
         txtID(miShGInven) & "'?", vbYesNo + vbQuestion, LoadResString(371))
      If intResp = vbYes Then 'Above: 'Confirm the change.
         If DatFrmUnld(gobSetng.FrmInvenIdx) Then 'Unload all tabs' data forms, except this one's.
            If DatFrmUnldDam Then 'Unload the dam's frmShG data form.
               mstrIDFrmLast = txtID(gobSetng.FrmInvenIdx) 'Save the new ID to refer to as the last.
               gobDatFrms.IDFrmLastSet txtID(gobSetng.FrmInvenIdx), Me.Name
               ConfmChanID = True 'Unload other data forms.
            End If
         End If
      Else 'Denied - restore.
         txtID(miShGInven) = mobDatFrm.IDFrm
         txtID(miShGInven).SetFocus
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Load the sire's/dam's Inven form or merely focus it, if it's already loaded.
' Use the explicit name of this form i.e. gobSetng.FrmShGNam vs. Me.Name to avoid an
'  error, if the procedure is ever moved from this form.
Private Sub SrDmLoad(ByVal strID As String)
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   With gobDatFrms
      If .Exists(strID, gobSetng.FrmShGNam) Then 'Exists?
         .FrmHostFoc strID, gobSetng.FrmShGNam 'Focus.
      Else 'Load new.
         Call frmMDI.LoadNewShG 'Load.
         Set obDatFrm = frmMDI.ActiveForm
         With obDatFrm
            .IDCtl = strID 'Write the sire/dam's ID.
            .IDCtl.SetFocus 'Focus to simulate the user's behavour to prevent the former
            .IDCtlPress gobFormtCtl.AscEnter 'Press Enter.                       'error.
         End With
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the selected data form's controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   With gobSetng
      Select Case tabShG.SelectedItem.Index
      Case .FrmInvenIdx
         Call InitCtlInven
      Case .FrmMatIdx
         Call BrsMatLmK("") 'Initialise the Mate/LmK grid.
      Case .FrmLmKIdx
         Call InitCtlLmK
      Case .FrmWtWoolIdx
         Call BrsWtWool("") 'Initialise the WtWool grid.
      Case .FrmApprIdx
         Call InitCtlAppr
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the Inven data form's controls.
Private Sub InitCtlInven()
On Error GoTo ErrHnd
   Dim I As Integer
   With gcnnConn
      adoFld(miFarm).ConnectionString = .ConnectionString
      Call Util.DbcSetRowSrc(dbcFld(miFarm), adoFld(miFarm), "IDFarm", "IDFarm")
      Call Util.DbcSetRowSrc(dbcFld(miFarmBirth), adoFld(miFarm), "IDFarm", "IDFarm")
      adoFld(miSexInven).ConnectionString = .ConnectionString
      Call Util.DbcSetRowSrc(dbcFld(miSexInven), adoFld(miSexInven), "IDSex", "Sex")
      adoFld(miTypeBirth).ConnectionString = .ConnectionString
      Call Util.DbcSetRowSrc(dbcFld(miTypeBirth), adoFld(miTypeBirth), "TypeBirth", _
         "TypeBirth")
      adoFld(miBrdPure).ConnectionString = .ConnectionString
      Call Util.DbcSetRowSrc(dbcFld(miBrdPure), adoFld(miBrdPure), "IDBreed", "Breed")
      adoFld(miDispReas).ConnectionString = .ConnectionString
      Call Util.DbcSetRowSrc(dbcFld(miDispReas), adoFld(miDispReas), "IDDispReas", "DispReas")
      adoFld(miCompClass).ConnectionString = .ConnectionString
      Call Util.DbcSetRowSrc(dbcFld(miCompClass), adoFld(miCompClass), "IDCompClass", _
         "CompClass")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

'Switch the Inven option controls.
Private Sub SwchOptCtl()
On Error GoTo ErrHnd
   If txtMisc(miBrdCrsTxt) = "" Then 'Breed controls.
      optFld(miOptBrdPure) = True
      dbcFld(miBrdPure).Enabled = True
      txtMisc(miBrdCrsTxt).Enabled = False
      cmdDlg(miBrdCrsCmd).Enabled = False
   Else
      optFld(miOptBrdCrs) = True
      txtMisc(miBrdCrsTxt).Enabled = True
      cmdDlg(miBrdCrsCmd).Enabled = True
      dbcFld(miBrdPure).Enabled = False
   End If
   If Trim$(txtDate(miDateDisp)) = "" Then 'Transfer/Disposition controls.
      optFld(miOptTransFarm) = True
      cmdDlg(miTransFarmCmd).Enabled = True
      txtDate(miDateDisp).Enabled = False
      lblDate(miDateDisp).Enabled = False
      dtpDate(miDateDisp).Enabled = False
      lblFld(miDispReas).Enabled = False
      dbcFld(miDispReas).Enabled = False
   Else
      optFld(miOptDisp) = True
      txtDate(miDateDisp).Enabled = True
      lblDate(miDateDisp).Enabled = True
      dtpDate(miDateDisp).Enabled = True
      lblFld(miDispReas).Enabled = True
      dbcFld(miDispReas).Enabled = True
      cmdDlg(miTransFarmCmd).Enabled = False
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the dbcComplClass control based on the mode & the complex classe's presence (in
'  the Edit mode).
' Only disable it & keep the content when the IDShG is being changed.
Public Sub SwchCompClass(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Dim blnEnableCC As Boolean
   If Not blnEnable Then
         Call DisabClearCompClass 'Clear & disable.
   Else 'Switch by mode.
      With gobSetng
         Select Case mintMode(gobSetng.FrmInvenIdx)
         Case .ModeAdd
            Call DisabClearCompClass 'Clear & disable.
         Case .ModeEdit
            blnEnableCC = IIf(dbcFld(miCompClass) = "", False, True) 'Switch depending on presen
            lblFld(miCompClass).Enabled = blnEnableCC
            dbcFld(miCompClass).Enabled = blnEnableCC
         End Select
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear & disable the dbcFld(miCompClass) control.
Private Sub DisabClearCompClass()
On Error GoTo ErrHnd
   dbcFld(miCompClass) = ""
   lblFld(miCompClass).Enabled = False
   dbcFld(miCompClass).Enabled = False
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert/delete the TblTestSire table for a male only in an Add/Edit mode.
Private Sub FrmToDBTestSire()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   With gobShGs(mstrIDFrm)
      If .TblShG.IDSex = gobSetng.IDSexMl Then 'For a male only.
         Select Case mintMode(gobSetng.FrmInvenIdx)
         Case gobSetng.ModeAdd 'Add mode.
            Call TestSireIns(.TblTestSire) 'Insert.
         Case gobSetng.ModeEdit 'Edit mode.
            Select Case .TblTestSire.Full
            Case True
               Select Case chkFld(miTestSireChk)
               Case vbChecked 'Update the date, if changed.
                  Set obDatTbl = .TblTestSire
                  obDatTbl.Upd
               Case vbUnchecked 'Delete.
                  Set obDatTbl = .TblTestSire
                  obDatTbl.Del
               End Select
            Case False 'Insert.
               Call TestSireIns(.TblTestSire)
            End Select
         End Select
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert the TblTestSire table in an Add/Edit mode.
Private Sub TestSireIns(ByRef obTblTestSire As TblTestSire)
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   If chkFld(miTestSireChk) = vbChecked Then 'Insert.
      Set obDatTbl = obTblTestSire
      obDatTbl.Ins
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable the Test Sire controls in the Add mode.
' In the Edit mode after filling the data form, disable:
'  - all Test Sire controls for a female or male younger than the minimal mating age;
'  - the Test Sire date controls only for a non-Test-Sire male.
Private Sub SwchTestSire()
On Error GoTo ErrHnd
   Select Case mintMode(gobSetng.FrmInvenIdx) 'Switch by mode.
'   Select Case mintMode(tabShG.SelectedItem.Index) 'Switch by mode.
   Case gobSetng.ModeAdd
      Call DisabTestSire 'Disable.
   Case gobSetng.ModeEdit
      If mstrIDFrm <> "" Then 'For filled data form only.
         With gobShGs(mstrIDFrm)
            Select Case .TblShG.IDSex 'Validate by sex.
            Case gobSetng.IDSexFm 'Female.
               Call DisabTestSire
            Case gobSetng.IDSexMl 'Male.
               If .Age(Date) < gobTblCtrlParam.AgeMatMinSr Then 'Validate by age.
                  Call DisabTestSire
               ElseIf Not .TblTestSire.Full Then 'Disable the date, if empty.
                  Call SwchTestSireDate(False)
               End If
            End Select
         End With
      End If
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable the TestSire controls.
Private Sub DisabTestSire()
On Error GoTo ErrHnd
   chkFld(miTestSireChk).Enabled = False
   Call SwchTestSireDate(False)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the Test Sire contorls.
Private Sub SwchTestSireDate(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   lblDate(miDateTestSire).Enabled = blnEnable
   txtDate(miDateTestSire).Enabled = blnEnable
   dtpDate(miDateTestSire).Enabled = blnEnable
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

' Get the deletion promt based on the deleted ShG sex.
Private Function PromtDel() As String
On Error GoTo ErrHnd
   Dim strAffx As String
   Select Case gobShGs(mobDatFrm.IDFrm).TblShG.IDSex 'Explanatory affix by sex.
   Case gobSetng.IDSexMl 'Male.
      strAffx = LoadResString(308)
   Case gobSetng.IDSexFm 'Female.
      strAffx = LoadResString(307)
   End Select
   PromtDel = LoadResString(304) & txtID(miShGInven) & "'?" & String(2, vbCrLf) & _
      LoadResString(305) & vbCrLf & LoadResString(306) & vbCrLf & strAffx 'Full prom
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Switch on/off the Cross Breed contorls.
Private Sub SwchBrdCrs(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   txtMisc(miBrdCrsTxt).Enabled = blnEnable
   cmdDlg(miBrdCrsCmd).Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate how the controls are filled.
' Return True, if succeeds.
Private Function VldFillCtlInven() As Boolean
On Error GoTo ErrHnd
   Const intFraBrd As Integer = 7 'The breed frame's index.
   If Trim$(txtID(miShGInven)) = "" Then 'Define IDShG.
      Call Util.MissParam(txtID(miShGInven), lblID(miShGInven)) 'Message & focus.
   ElseIf dbcFld(miFarm).BoundText = "" Then 'Define the farm.
      Call Util.MissParam(dbcFld(miFarm), lblFld(miFarm)) 'Message & focus.
   ElseIf dbcFld(miSexInven).BoundText = "" Then 'Define the sex.
Debug.Assert 0 = 1 'Verify
      Call Util.MissParam(dbcFld(miSexInven), lblFld(miSexInven)) 'Message & focus.
   ElseIf optFld(miOptBrdPure) And dbcFld(miBrdPure).BoundText = "" Then 'Define BreedPure, if optFld(miOptBrdPure) = True
      Call Util.MissParam(dbcFld(miBrdPure), fraFrame(intFraBrd) & Space$(1)) 'Message & focus.
   ElseIf optFld(miOptBrdCrs) And txtMisc(miBrdCrsTxt) = "" Then 'If optFld(miOptBrdCrs) = True define cross breeds.
      Call Util.MissParam(cmdDlg(miBrdCrsCmd), fraFrame(intFraBrd) & Space$(1)) 'Message & focus.
   ElseIf Trim$(txtDate(miDateBirth)) = "" Then 'Define the date of birth.
      Call Util.MissParam(txtDate(miDateBirth), lblDate(miDateBirth) & LoadResString(220)) 'Message & focus.
   ElseIf Not gobFormtCtl.VldIDShG(txtID(miSireInven), lblID(miSireInven)) Then 'Input a full ID or nothing.
'   ElseIf Not gobFormtCtl.ValidID(mebSire, lblSire, False) Then 'Input a full ID or
Debug.Assert 0 = 1 'Verify
      VldFillCtlInven = False
   ElseIf Not gobFormtCtl.VldIDShG(txtID(miDamInven), lblID(miDamInven)) Then 'Input a full ID or nothing
'   ElseIf Not gobFormtCtl.ValidID(mebDam, lblDam, False) Then 'Input a full ID or nothing
Debug.Assert 0 = 1 'Verify
      VldFillCtlInven = False
Debug.Assert 0 = 1 'Verify
   ElseIf (optFld(miOptDisp)) And ((Trim$(txtDate(miDateDisp)) <> "" And dbcFld(miDispReas).BoundText = "") Or _
      (Trim$(txtDate(miDateDisp)) = "" And dbcFld(miDispReas).BoundText <> "")) Then
      MsgBox LoadResString(221), vbExclamation, LoadResString(21)
      If txtDate(miDateDisp).Enabled Then txtDate(miDateDisp).SetFocus
   ElseIf chkFld(miTestSireChk) = vbChecked And Trim$(txtDate(miDateTestSire)) = "" Then 'Define the Test Sire date.
      Call Util.MissParam(txtDate(miDateTestSire), lblDate(miDateTestSire)) 'Message & focus.
   Else
      VldFillCtlInven = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Verify the sheep/goat's sex change.
' Query for its ID as a sire/dam in the SheepGoat table & as a sire/dam in the Mate table.
' Unload the ShG's dam's frmShG data form, if loaded, which shows this frmShG data form's
'  ShG as LmK in the LmK data form's tab (& in the Mat tab's grid).
' Return True, if succeeds.
Private Function VldSex() As Boolean
On Error GoTo ErrHnd
   Dim obDam As Dam
   Dim obTblSex As TblSex
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm)
      If dbcFld(miSexInven).BoundText <> .TblShG.IDSexOrig Then 'Proceed, if changed.
         Select Case .TblShG.IDSexOrig
         Case gobSetng.IDSexMl 'Originally male.
            If .TblShG.CountSrOffsp(mobDatFrm.IDFrm) <> 0 Then 'Query in .TblShG.
               blnFail = True 'Failed.
            Else 'No progeny - query in mboTblMat.
               If .Sire.CountMat <> 0 Then blnFail = True 'Failed.
            End If
         Case gobSetng.IDSexFm 'Originally female.
            If .TblShG.CountDmOffsp(mobDatFrm.IDFrm) <> 0 Then 'Query in .TblShG.
               blnFail = True 'Failed.
            Else 'No progeny - query in mboTblMat.
               Set obDam = New Dam
               With obDam
                  .IDDam = mobDatFrm.IDFrm
                  .MatSel False
                  If .Mats.Count <> 0 Then blnFail = True 'Failed.
               End With
            End If
         End Select
      End If
      If blnFail Then 'Message.
         Set obTblSex = New TblSex
Debug.Assert 0 = 1 'Verify dbcFld(miSexInven).BoundText
         strPromt = LoadResString(550) & obTblSex.Sex(.TblShG.IDSexOrig) & _
            LoadResString(551) & obTblSex.Sex(dbcFld(miSexInven).BoundText) & _
            LoadResString(552)
         MsgBox strPromt, vbExclamation, LoadResString(131)
Debug.Assert 0 = 1 'Verify dbcFld(miSexInven).BoundText
         dbcFld(miSexInven).BoundText = .TblShG.IDSexOrig 'Restore the original sex.
         dbcFld(miSexInven).SetFocus 'Focus after the message box.
      Else
         VldSex = DatFrmUnldDam 'Unload the dam's frmShG data form.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that the sire/dam ID have 6 characters inputted.
' Unless failed, switch the adjacent Sire/Dam button based on if there is a sire/dam.
' Validate the sire/dam's ID & sex.
' Return True, if succeeds.
Private Function VldSrDm(ByRef txtSrDm As TextBox, ByVal intIdx As Integer, ByVal _
   strLblCapt As String, ByRef cmdSrDm As CommandButton) As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   If gobFormtCtl.VldIDShG(txtSrDm, strLblCapt) Then 'Validate the ID format.
      If txtSrDm <> "" Then 'Validate ID & sex, if filled.
         If txtSrDm <> SrDmIDOrig(intIdx) Then blnFail = Not VldSrDmIDSex(txtSrDm, _
            intIdx) 'Validate, if ID changed.
      End If
   Else
      blnFail = True 'Failed.
   End If
   If Not blnFail Then
      Call SwchBtnID(intIdx) 'Switch the adjacent button.
      VldSrDm = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Switch Sire/Dam button based on if there is a sire/dam.
Private Sub SwchBtnID(ByVal intIdx As Integer)
On Error GoTo ErrHnd
   cmdID(intIdx).Enabled = IIf(Trim$(txtID(intIdx)) <> "", True, False)
'   cmdSrDm.Enabled = IIf(Trim$(strText) <> "", True, False)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the sire/dam's ID, sex that:
'  - IDSire/Dam not repeat IDShG;
'  - exists in the DB;
'  - sire is male & dam is female.
' Return True, if succeeds.
Private Function VldSrDmIDSex(ByVal txtSrDm As TextBox, ByVal intIdx As Integer) _
   As Boolean
On Error GoTo ErrHnd
   Dim obShGSrDm As ShG
   Dim lngSrDmAgeMin As Long
   Dim lngAgeSrDmMax As Long
   Dim strPromt As String
   If txtSrDm <> mobDatFrm.IDFrm Then 'IDSrDm must not repeat IDShG.
      Set obShGSrDm = New ShG 'Sire/dam.
      With obShGSrDm
         .IDShG = txtSrDm 'Verity the ID.
         If .Exists(False) Then 'Proceed, if exists.
            If .TblShG.IDSex = SrDmSex(intIdx) Then 'Verify the sex.
               VldSrDmIDSex = True 'Succeeded.
            Else 'Wrong sex promt.
               strPromt = SrDmMsgSex(intIdx) 'Wrong sex promt by sex.
            End If
         End If
      End With
   Else
      strPromt = SrDmMsgDupl(intIdx) 'Sire/dam's duplicate ID message.
   End If
   If strPromt <> "" Then MsgBox strPromt, vbExclamation, LoadResString(131) 'Message, if
Exit Function                                                                'reqiured.
ErrHnd:
MsgBox Err.Description
End Function

' Return the minimal required age the sire/dam must have.
Private Function SrDmAgeMin(ByVal intIdx As Integer) As Long
On Error GoTo ErrHnd
   With gobTblCtrlParam
      Select Case intIdx
      Case miSireInven 'Sire.
         SrDmAgeMin = .AgeMatMinSr + .PregnLengMin
      Case miDamInven 'Dam.
         SrDmAgeMin = .AgeMatMinDm + .PregnLengMin
      End Select
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Sire/dam's Wrong sex message for the VldSrDmIDSex procedure.
Private Property Get SrDmMsgSex(ByVal intIdx As Integer) As String
On Error GoTo ErrHnd
   Select Case intIdx  'Distinguish by sex.
   Case miSireInven 'Sire.
      SrDmMsgSex = LoadResString(554)
   Case miDamInven 'Dam.
      SrDmMsgSex = LoadResString(555)
   Case miSireMat
      SrDmMsgSex = LoadResString(578)
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Validate the sire/dam's age at the ShG's birth, if either the birth date or sire/dam
'  changed.
' Return True, if succeeds.
Private Function VldAgeSrDm(ByRef txtSrDm As TextBox, ByVal intIdx As Integer) As Boolean
On Error GoTo ErrHnd
   Dim obShGSrDm As ShG
   Dim lngAge As Long
   Dim sngAgeYr As Single
   Dim lngAgeMin As Long
   Dim blnFail As Boolean
   Dim strSrDm As String
   Dim strPromt As String
   If txtSrDm <> "" Then 'Proceed, if filled.
      If (txtSrDm <> SrDmIDOrig(intIdx)) Or (txtDate(miDateBirth) <> gobShGs(mobDatFrm _
         .IDFrm).TblShG.DateBirthOrig) Then 'Proceed, if either is changed.
         Set obShGSrDm = New ShG 'Sire/dam.
         With obShGSrDm
            .IDShG = txtSrDm
            .SelShG 'Populate the data.                        Below: 'Sire/dam title.
            strSrDm = IIf(intIdx = miSireInven, LoadResString(564), LoadResString(565))
            If Not WhoOlderWhom(obShGSrDm, strSrDm, mobDatFrm.IDFrm, txtDate(miDateBirth)) Then
               blnFail = True 'Verify that the sire/dam be older than the ShG.
            Else
               lngAge = .Age(txtDate(miDateBirth), False) 'Sire/dam's age.
               lngAgeMin = SrDmAgeMin(intIdx) 'Min required age for a sire/dam.
               If lngAge < lngAgeMin Then
                  blnFail = True 'Too young.
                  strSrDm = IIf(intIdx = miSireInven, LoadResString(558), _
                     LoadResString(566)) 'Sire/dam title.
Debug.Assert 0 = 1 'Verify txtDate(miDateBirth)
                  strPromt = strSrDm & txtSrDm & "' (" & lngAge & LoadResString(556) _
                     & txtDate(miDateBirth) & LoadResString(557) & lngAgeMin & LoadResString(231)
               Else
                  sngAgeYr = .Age(txtDate(miDateBirth), True) 'Sire/dam's age in years.
                  If sngAgeYr > gobTblCtrlParam.LifeTimeMax Then
                     blnFail = True 'Too old.
Debug.Assert 0 = 1 'Verify txtDate(miDateBirth)
                     strPromt = LoadResString(558) & txtSrDm & "' (" & sngAgeYr _
                        & LoadResString(559) & txtDate(miDateBirth) & LoadResString(560) & _
                        gobTblCtrlParam.LifeTimeMax & LoadResString(333)
                  End If
               End If
            End If
         End With
      End If
   End If
   If blnFail Then 'Succeeded/failed.
      If strPromt <> "" Then MsgBox strPromt, vbExclamation, LoadResString(131) 'Message,
      txtSrDm.SetFocus                                                      'if required.
   Else
      VldAgeSrDm = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the original sire/dam's ID.
Private Function SrDmIDOrig(ByVal intIdx As Integer) As String
On Error GoTo ErrHnd
   With mobDatFrm
      Select Case intIdx
      Case miSireInven 'Sire.
         SrDmIDOrig = gobShGs(.IDFrm).TblShG.IDSireOrig
      Case miDamInven 'Dam.
         SrDmIDOrig = gobShGs(.IDFrm).TblShG.IDDamOrig
      Case miSireMat
         Select Case .Mode
         Case gobSetng.ModeAdd
            SrDmIDOrig = ""
         Case gobSetng.ModeEdit
            SrDmIDOrig = gobShGs(.IDFrm).Dam.Mats.Act.IDSireOrig
         End Select
      End Select
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the sire/dam's sex by the its text box's name.
Private Property Get SrDmSex(ByVal intIdx As Integer) As String
On Error GoTo ErrHnd
   Select Case intIdx
   Case miSireInven, miSireMat 'Sire.
      SrDmSex = gobSetng.IDSexMl
   Case miDamInven 'Dam.
      SrDmSex = gobSetng.IDSexFm
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Validate that Who (father, mother, sire etc.) be born before Whom.
' Return True, if succeeds.
Private Function WhoOlderWhom(ByVal obShGWho As ShG, ByVal strWho As String, ByVal _
   strIDWhom As String, dtmDateBrthWhom As Date) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If obShGWho.TblShG.DateBirth < dtmDateBrthWhom Then
      WhoOlderWhom = True 'Succeeded.
   Else 'Failed.
      With obShGWho
         strPromt = strWho & "'" & .IDShG & LoadResString(561) & .TblShG.DateBirth & _
            LoadResString(562) & dtmDateBrthWhom & LoadResString(563) & strIDWhom & "'."
      End With
      MsgBox strPromt, vbExclamation, LoadResString(131)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that the ShG live at the specified date, if the date is filled & changed or
'  the birth date is changed.
'' If the disposition date is specified validate the age at the last record.
' Return True, if succeeds.
Private Function VldDate(ByVal intIdx As Integer, ByVal dtmDateOrig As Date, ByVal _
   strEvent As String) As Boolean
On Error GoTo ErrHnd
   Dim blnEscDisp As Boolean
   Dim blnFail As Boolean
   Dim strPromt As String
   blnEscDisp = IIf(intIdx = miDateDisp, True, False) 'Don't check disposal itself for
   If txtDate(intIdx) <> "" And txtDate(intIdx).Enabled Then 'Filled & enabled? 'its date
      With gobShGs(mobDatFrm.IDFrm)
         If (CDate(txtDate(miDateBirth)) <> .TblShG.DateBirthOrig) Or (CDate(txtDate( _
            intIdx)) <> dtmDateOrig) Then 'Proceed, if either is changed
            If .Lives(txtDate(intIdx), strEvent, blnEscDisp, strPromt) Then 'Lives?
               If intIdx = miDateTestSire Then blnFail = Not VldTestSireAge 'Validate test sire's age
            Else
               blnFail = True 'ShG doesn't live.
               MsgBox strPromt, vbExclamation, LoadResString(131)
               If txtDate(intIdx).Enabled Then txtDate(intIdx).SetFocus
            End If
         End If
      End With
   End If
   VldDate = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Read the birth date & the date & reason of disposition. These controls are picked out
'  from among the rest to enable refreshing the TblShG object from the VldInven
'  procecdure.
Private Sub CtlReadBirthDisp()
On Error GoTo ErrHnd
   With gobShGs(mobDatFrm.IDFrm).TblShG
      .DateBirth = txtDate(miDateBirth)
      Select Case optFld(miOptDisp) 'Disposition selected?
      Case True 'Read.
         .DateDisp = IIf(Trim$(txtDate(miDateDisp)) <> "", txtDate(miDateDisp), 0)
         .IDDispReas = Util.DbcReadBoundTxt(dbcFld(miDispReas), adoFld(miDispReas))
      Case False 'Nullify.
         .DateDisp = 0
         .IDDispReas = ""
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the ShG's age for a test sire.
' Return True, if succeeds.
Private Function VldTestSireAge() As Boolean
On Error GoTo ErrHnd
   Dim lngAge As Long
   Dim strPromt As String
   lngAge = gobShGs(mobDatFrm.IDFrm).Age(txtDate(miDateTestSire)) 'Test-sire-transfer age.
   If lngAge >= gobTblCtrlParam.AgeMatMinSr Then
      VldTestSireAge = True 'Succeeded.
   Else
      strPromt = LoadResString(573) & " (" & txtDate(miDateTestSire) & LoadResString(575) & _
         lngAge & LoadResString(576) & gobTblCtrlParam.AgeMatMinSr & LoadResString(231)
      MsgBox strPromt, vbExclamation, LoadResString(131)
      txtDate(miDateTestSire).SetFocus
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Let the IsDirty property for each data form of the 6 separately.
Private Property Let DatFrm_IsDirty(ByVal blnIsDirty As Boolean)
On Error GoTo ErrHnd
   mintIsDirty(tabShG.SelectedItem.Index) = blnIsDirty
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get the IsDirty property for each data form of the 6 separately.
Private Property Get DatFrm_IsDirty() As Boolean
On Error GoTo ErrHnd
   DatFrm_IsDirty = mintIsDirty(tabShG.SelectedItem.Index)
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Shwitch on/off the data form's controls depending on whether the txtID is filled.
' If the ID is filled switch the option related controls by their contents.
' Switch Sire/Dam buttons based on if there are sire & dam respectively.
Private Sub SwchCtlFillInven(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   txtID(miShGInven).Enabled = blnEnableID 'ID control.
   cmdID(miShGInven).Enabled = Not blnEnable 'ID button - opposite to other controls.
   Call SwchCtlObj(lblFld, miFarm, miCompClass, blnEnable) 'Switch other controls
   Call SwchCtlObj(dbcFld, miFarm, miBrdPure, blnEnable)
   Call SwchCtlObj(optFld, miOptBrdPure, miOptDisp, blnEnable)
   lblMisc(miRemark).Enabled = blnEnable
   Call SwchCtlObj(txtMisc, miRemark, miBrdCrsTxt, blnEnable)
   Call SwchCtlObj(cmdDlg, miBrdCrsCmd, miTransFarmCmd, blnEnable)
   Call SwchCtlFillDate(miDateBirth, miDateTestSire, blnEnable)
   Call SwchCtlObj(lblID, miSireInven, miDamInven, blnEnable)
   Call SwchCtlObj(txtID, miSireInven, miDamInven, blnEnable)
   Call SwchCtlObj(cmdID, miSireInven, miDamInven, blnEnable)
   chkFld(miTestSireChk).Enabled = blnEnable
   If blnEnable Then 'Switch other controls:
      Call SwchOptCtl '- option controls.
      Call SwchBtnID(miSireInven)  '- sire/dam buttons.
      Call SwchBtnID(miDamInven)
   End If
   Call SwchCompClass(blnEnable) '- complex class.
   Call SwchTestSire ' - test sire.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Shwitch on/off the data form's specified control arrays.
Private Sub SwchCtlObj(ByRef objCtl As Object, ByVal intFst As Integer, ByVal intLst _
   As Integer, ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = intFst To intLst
      objCtl(I).Enabled = blnEnable
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified ID lables, text boxes & their adjacent buttons.
Private Sub SwchID(ByVal intFst As Integer, ByVal intLst As Integer, ByVal _
   blnEscLbl As Boolean, ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = intFst To intLst
      If Not blnEscLbl Then lblID(I).Enabled = blnEnable
      txtID(I).Enabled = blnEnable
      cmdID(I).Enabled = blnEnable
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified date lables, text boxes & their adjacent date time pickers.
Private Sub SwchCtlFillDate(ByVal intFst As Integer, ByVal intLst As Integer, ByVal _
   blnEnable As Boolean)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = intFst To intLst
      lblDate(I).Enabled = blnEnable
      txtDate(I).Enabled = blnEnable
      dtpDate(I).Enabled = blnEnable
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified lable & its adjacent control.
Private Sub SwchCtlLbl(ByRef lblLbl As Label, ByRef ctlCtl As Control, ByVal _
   blnEnable As Boolean)
On Error GoTo ErrHnd
   lblLbl.Enabled = blnEnable
   ctlCtl.Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtID(miShGInven).
Private Sub ClickOkInven()
On Error GoTo ErrHnd
   Dim intResp As Integer
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit 'Validate data in an Add or Edit mode.
         If .Vld Then
            .FrmToDB
            .Cancel False
            txtID(miShGInven).SetFocus
         End If
      Case gobSetng.ModeDel 'The Del mode.
         Beep
         intResp = MsgBox(PromtDel, vbYesNoCancel + vbQuestion, LoadResString(372))
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            If DatFrmUnld(gobSetng.FrmInvenIdx) Then 'Unload other data forms.
               .FrmToDB
               .Cancel True
               Call InitTxt(True) 'Initialise text boxes.
               txtID(miShGInven).SetFocus
            End If
         Case vbNo
            cmdOk.SetFocus
         Case vbCancel
            .Cancel True
            txtID(miShGInven).SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the data from the form's controls to the ShG object.
' If changed update cross breeds &/or farm transfers from the ShG object to the data
'  base.
Private Sub CtlReadInven()
On Error GoTo ErrHnd
   Dim strBrd As String
   With gobShGs(mobDatFrm.IDFrm)
      With .TblShG
         .IDFarm = dbcFld(miFarm).BoundText
         .IDShG = Trim$(txtID(miShGInven))
         .IDSex = dbcFld(miSexInven).BoundText
         If optFld(miOptBrdPure) Then
            .BrdCrsDel
            strBrd = Util.DbcReadBoundTxt(dbcFld(miBrdPure), adoFld(miBrdPure)) 'Read the
            .IDBrdBas = strBrd                                      'basic & cross breed.
            .BrdCrs = strBrd
            .Crs = False
         Else
            If .BrdCrsChand Then 'Update the cross breed code on change.
               .BrdCrsDel
               .IDBrdBas = .IDBrdBasNew
               .BrdCrs = .BrdCrsNew
            End If
            .Crs = True
            Call BrdPureOption
' TO DO 1: PROGRAM READING THE WHOLE CROSS BREED CODE FROM txtMisc(miBrdCrsTxt)
'   IN ORDER FOR THE USER NOT TO MANUALLY RE-INPUT CROSS BREEDS, IF REPEATED.
         End If
         .IDFarmBirth = dbcFld(miFarmBirth).BoundText
         .TypeBirth = IIf(dbcFld(miTypeBirth).BoundText = "", 1, dbcFld(miTypeBirth) _
            .BoundText)
         .IDSire = Trim$(txtID(miSireInven))
         .IDDam = Trim$(txtID(miDamInven))
         If .TransFarmChand Then .TransFarmDel 'Delete the prev. farm transfers, if chang
         .Remark = txtMisc(miRemark)
      End With 'Below: Read the complex class in the Edit mode only.
      If mintMode(gobSetng.FrmInvenIdx) = gobSetng.ModeEdit Then .TblSelIdxCC _
         .IDCompClass = dbcFld(miCompClass).BoundText 'Read comp. cl. in Edit mode only.
      If chkFld(miTestSireChk) = vbChecked Then .TblTestSire.DateTestSire = txtDate _
         (miDateTestSire)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDate_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtDate(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing F4 open the adjacent dtpDate.
Private Sub txtDate_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.OpenDTPick KeyCode, dtpDate(Index), txtDate(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtDate_KeyPress(Index As Integer, KeyAscii As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.TypeDate KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted date.
Private Sub txtDate_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   gobFormtCtl.VldDate txtDate(Index), dtpDate(Index), Cancel
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter in the data form ID text box.
Private Sub txtID_DblClick(Index As Integer)
On Error GoTo ErrHnd
   Select Case Index
   Case miShGInven To miShGAppr
      mobDatFrm.IDCtlPress gobFormtCtl.AscEnter
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtID_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtID(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' To prevent beeping beyond the ID length, cancel the length restriction for Enter.
Private Sub txtID_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If KeyCode = gobFormtCtl.AscEnter Then txtID(Index).MaxLength = 0
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Type in upper case.
' Invoke the mobDatFrm.IDCtlPress procedure for the data form ID text boxes.
Private Sub txtID_KeyPress(Index As Integer, KeyAscii As Integer)
On Error GoTo ErrHnd
   KeyAscii = gobFormtCtl.UpCase(KeyAscii)
   Select Case Index
   Case miShGInven To miShGAppr
      mobDatFrm.IDCtlPress KeyAscii
   Case miSireInven To miLmKLmK
      KeyAscii = gobFormtCtl.UpCase(KeyAscii)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restore the length restriction, if it was canceled for Enter on the KeyDown event.
Private Sub txtID_KeyUp(Index As Integer, KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If txtID(Index).MaxLength = 0 Then txtID(Index).MaxLength = gobFormtCtl.LengIDShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Invoke the mobDatFrm.IDCtlLostFoc procedure for the data form ID text boxes.
Private Sub txtID_LostFocus(Index As Integer)
On Error GoTo ErrHnd
   mobDatFrm.IDCtlLostFoc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' For txtID(miShGInven): restrict the focus, if fewer than six characters are inputted
'  or if the field is left blank in the Edit mode after changing the ID.
' For the non-form ID text boxes: restrict the focus, if fewer than six characters are
'  inputted.
Private Sub txtID_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case Index
      Case miShGInven
         If mblnFrmFilld(gobSetng.FrmInvenIdx) And mobDatFrm.Mode = gobSetng.ModeEdit Then 'Must be
            .VldIDCtlShG txtID(Index), lblID(Index), Cancel         'full, if ID changed.
         Else
            Cancel = Not .VldIDShG(txtID(Index), lblID(Index))
         End If
      Case miDamMat To miShGAppr
         Cancel = Not .VldIDShG(txtID(Index), lblID(Index))
      Case miSireInven To miSireMat
'      Case miSireInven, miDamInven
         Cancel = Not VldSrDm(txtID(Index), Index, lblID(Index), cmdID(Index))
      Case miLmKLmK
         If .VldIDShG(txtID(Index), lblID(Index)) Then 'Validate.
            Call SwchBtnID(Index) 'Switch the adjacent button.
         Else
            Cancel = True 'Canceled.
         End If
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement the selected data form's DatFrm_IDCtlPress operation.
Private Sub DatFrm_IDCtlPress(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmInvenIdx
      Call IDCtlPressInven(intKeyAscii)
   Case gobSetng.FrmMatIdx
      Call IDCtlPressMat(intKeyAscii)
   Case gobSetng.FrmLmKIdx
      Call IDCtlPressLmK(intKeyAscii)
   Case gobSetng.FrmWtLmKIdx
      Call IDCtlPressWtLmK(intKeyAscii)
   Case gobSetng.FrmWtWoolIdx
      Call IDCtlPressWtWool(intKeyAscii)
   Case gobSetng.FrmApprIdx
      Call IDCtlPressAppr(intKeyAscii)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Prevent a duplication.
' Format the control.
' Reset the gobMsgInst object for later use.
' Unless the Util.DuplFrmtRest procedure unloads the form complete switching the
'  controls in the Edit mode after filling the form to restrict the access to the this
'  control until saving or canceling.
Private Sub DatFrm_IDCtlLostFoc()
On Error GoTo ErrHnd
   Call Util.DuplFrmtRest(Me, txtID(tabShG.SelectedItem.Index))
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtID(miDamMat).
Private Sub ClickOkMat()
On Error GoTo ErrHnd
   Dim intResp As Integer
   Dim strPromt As String
   Call UnldSyncMatLmK(gobSetng.FrmLmKIdx) 'Unload the LmK data form.
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit
         If .Vld Then 'Validate data in an Add or Edit mode.
            .FrmToDB
            .Cancel False
            txtID(miDamMat).SetFocus
         End If
      Case gobSetng.ModeDel
         Beep
         strPromt = LoadResString(303) & vbCrLf & LoadResString(309)
         intResp = MsgBox(strPromt, vbYesNoCancel + vbQuestion, LoadResString(372))
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            .FrmToDB
            .Cancel True
            Call InitTxt(True) 'Initialise text boxes.
            txtID(miDamMat).SetFocus
         Case vbNo
            cmdOk.SetFocus
         Case vbCancel
            .Cancel True
            txtID(miDamMat).SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the Mate contorls.
Private Sub CtlReadMat()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm).Dam.Mats.Act
      .IDSire = Trim$(txtID(miSireMat))
      .DateMat = txtDate(miDateMat)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Register the data form itself under a new ID. Delete it under the previous ID, if any,
'  & register under a new one.
' Along with the data form, register the ShG object shown in this data form.
' On duplication of the data form escape registering the ShG object.
Private Sub DatFrm_RegistFrm(ByVal strNewIDFrm As String, ByVal blnDelPrev As Boolean)
On Error GoTo ErrHnd
   Dim obShG As ShG 'Below: 'Re-register, for the 1st time or if the ID changes.
   If strNewIDFrm = "" Or strNewIDFrm <> mstrIDFrm Then
      If blnDelPrev Then
         If DatFrmUnld(tabShG.SelectedItem.Index) Then 'Unload filled data forms, if any.
            For Each obShG In gobShGs 'Check to delete the ShG object.
               If obShG.IDShG = mstrIDFrm Then
                  gobShGs.Del mstrIDFrm, Me.Name 'Delete ShG.
                  Exit For
               End If
            Next obShG
            gobDatFrms.Del mstrIDFrm, Me.Name 'Delete DatFrm object.
         End If
      End If
      gobDatFrms.Add strNewIDFrm, Me.Name 'Register the form under the new ID.
      If strNewIDFrm <> "" And gobMsgInst.DuplFrm = False Then 'Register ShG & Dam.
         gobShGs.Add strNewIDFrm, Me.Name 'Register ShG & dam.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Shwitch on/off the Mate data form's controls depending on whether the txtID(miDamMat)
'  is filled.
Private Sub SwchCtlFillMat(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Call SwchID(miDamMat, miDamMat, True, Not blnEnable)
   Call SwchID(miSireMat, miSireMat, False, blnEnable)
   Call SwchCtlFillDate(miDateMat, miDateMat, blnEnable)
   Call SwchCtlLbl(lblGrid(miFlexMat), flexGrid(miFlexMat), blnEnable)
   If blnEnable Then Call SwchBtnID(miSireMat) 'Switch the sire button.
'   If blnEnable Then Call SwchBtnID(txtID(miSireMat), cmdID(miSireMat)) 'Switch the sire button.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
Private Sub SwchCtlModeMat()
On Error GoTo ErrHnd
   With gobSetng
      Select Case mintMode(gobSetng.FrmMatIdx)
      Case .ModeAdd, .ModeEdit
         Call DatFrm_SwchCtlFill(True)
         txtID(miSireMat).SetFocus
      Case .ModeDel
         txtID(miDamMat).Enabled = False
         cmdID(miDamMat).Enabled = False
         Call SwchCtlLbl(lblGrid(miFlexMat), flexGrid(miFlexMat), True)
         cmdOk.Enabled = True
         cmdOk.SetFocus
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function VldMat() As Boolean
On Error GoTo ErrHnd
   Dim obShGSr As ShG
   If VldFillCtlMat Then 'Filling the controls.
      If VldAgeMat(gobShGs(mobDatFrm.IDFrm), gobTblCtrlParam.AgeMatMinDm, _
         LoadResString(230)) Then 'Validate the dam's age.
         Set obShGSr = New ShG 'Initialise the sire ShG.
         With obShGSr
            .IDShG = txtID(miSireMat)
            .SelShG
         End With 'Below: 'Validate the sire's age.
         If VldAgeMat(obShGSr, gobTblCtrlParam.AgeMatMinSr, LoadResString(232)) Then _
            VldMat = VldOvlpMat 'Validate overlapping Mat/LmK's
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Delete the ShG & Dam objects, if shown in the form.
' Delete the current data form from the DatFrms collection.
' Reset the relevant to windows & data form forms menu's & tool bar's items.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   With mobDatFrm
      If .IDFrm <> "" Then 'Delete the ShG & Dam objects.
         gobShGs.Del .IDFrm, Me.Name
      End If
      gobDatFrms.Del .IDFrm, .FrmHostNam 'Delete the data form.
   End With
   With frmMDI 'Switch the buttons.
      Call .SwchMnuWin(False)
      Call .SwchMnuMode(gobSetng.ModeOff)
   End With
   gobMsgInst.Rest Me 'Reset gobMsgInst.
 Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select matings from the DB to the Dam object object associated with the data form,
'  unless the data haven't populated yet.
' In an Edit of Del mode, fill out this form with the data from the last cycle of the Dam
Private Sub DBtoFrmMat()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm).Dam
      If Not .PopltMat Then .MatSel True 'Prepare data. 'Below: 'Check if the dam exist
      If .VldFail = False And gobMsgInst.NoMating(Me) = False Then '& has matings.
         Select Case mintMode(gobSetng.FrmMatIdx) 'Fill.
         Case gobSetng.ModeEdit, gobSetng.ModeDel
            Call CtlWriteMat(.Mats.Last(False)) 'Fill the text boxes.
'            Call CtlWriteMat(.Mats.Last(mstrIDFrm)) 'Fill the text boxes.
         End Select
         Call BrsMatLmK(mstrIDFrm) 'Fill the Mate/LmK grid.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the Mate object associated with the data form to put
'   it into the DB.
' Delete the active cycle in the Del mode.
' Unload the LmK data form to make the user syncronise it to this one.
' Roll back operations on the SQL server's error.
Private Sub FrmToDBMat()
On Error GoTo ErrHnd
   Dim intCycleNew As Integer
   Dim intCycleLmKNew As Integer
   gcnnConn.BeginTrans 'Begin transaction.
   With gobShGs(mstrIDFrm).Dam
      Select Case mintMode(gobSetng.FrmMatIdx) 'Accomplish the mode's opertation.
      Case gobSetng.ModeAdd
         intCycleNew = .Mats.CycleNew 'Define a new cycle number.
         If Not .PopltLmK Then .LmKSel False  'Define a new CycleLmK.
         intCycleLmKNew = .LmKs.CycleLmKNew 'Below: 'Add a new mating.
         .Mats.Add intCycleNew, intCycleLmKNew, txtDate(miDateMat), txtID(miSireMat)
         .MatIns
      Case gobSetng.ModeEdit
         Call DatFrm_CtlRead 'Read the contorls.
         .MatUpd
      Case gobSetng.ModeDel
         .MatDel 'Deletion.
      End Select
   End With
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub IDCtlPressMat(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Call frmMDI.SetIsDirtyMnu(mobDatFrm) 'Set the menu & IsDirty mark.
   If intKeyAscii <> gobFormtCtl.AscEnter Then
      intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
   Else
      intKeyAscii = 0 'Cancel Enter
      If Len(Trim$(txtID(miDamMat))) = gobFormtCtl.LengIDShG Then
         With mobDatFrm
            .RegistFrm Trim$(txtID(miDamMat)), True  'Process the command corresponding
            If gobMsgInst.DuplFrm Then               'to the mode. Register the form.
               cmdCancel.SetFocus 'Avoid duplication by ivoking the LostFocus procedure.
            Else
               .DBtoFrm 'Fill the form with the data from the Dam object in an Edit/Del
               If gobShGs(.IDFrm).Dam.VldFail Then                             'mode.
                  .Cancel False 'Cancel the current changes, if any.
                  txtID(miDamMat).SetFocus
               ElseIf (gobMsgInst.NoMating(Me)) And (.Mode = gobSetng.ModeEdit Or .Mode _
                  = gobSetng.ModeDel) Then
                  MsgBox LoadResString(170) & .IDFrm & LoadResString(184), _
                     vbExclamation, LoadResString(172) 'No mating to Edit/Del.
                  .Cancel False
                  txtID(miDamMat).SetFocus
               Else
                  mblnFrmFilld(gobSetng.FrmMatIdx) = True 'Mark filled.
                  .SwchCtlMode 'Switch controls by mode.
               End If
            End If
         End With
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear text/combo boxes.
Private Sub CtlClearTxtDbc(ByRef objTxtDbc As Object, ByVal intFst As Integer, ByVal _
   intLst As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = intFst To intLst
      objTxtDbc(I) = ""
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear the specified date text boxes & their adjacent date time pickers.
Private Sub CtlClearDate(ByVal intFst As Integer, ByVal intLst As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = intFst To intLst
      gobFormtCtl.WriteDate txtDate(I), dtpDate(I), 0
'      txtDate(I) = ""
'      dtpDate(I).Value = Null
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Access to the complex class combo box to be updated from within the TblSelIdxCC class.
Public Property Get CompClassDbc() As DataCombo
   Set CompClassDbc = dbcFld(miCompClass)
End Property

' Return True, if any of the data forms, except the specified one, is filled.
Private Function DatFrmFilldAny(ByVal intEscFrm As Integer) As Boolean
On Error GoTo ErrHnd
   Dim I As Integer
   For I = gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx 'Look up a filled data form.
      If mblnFrmFilld(I) Then
         If I <> intEscFrm Then 'Except the specified one.
            DatFrmFilldAny = True 'Filled.
            Exit For
         End If
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise all data forms' modes on form loading.
Private Sub InitMode(ByVal intMode As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx
      mintMode(I) = intMode
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload all data forms except the specified one, if required, in order to:
'  - delete the ShG or change its ID from the Inven data form;
'  - re-register the data form.
' Return True, if succeeds.
Private Function DatFrmUnld(ByVal intEscFrm As Integer) As Boolean
On Error GoTo ErrHnd
   Dim intTabOrig As Integer
   Dim I As Integer
   With tabShG
      For I = gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx
         If mblnFrmFilld(I) Then 'Select the respective tab, if filled.
            If I <> intEscFrm Then 'Escape, if necessary.
               If intTabOrig = 0 Then
                  intTabOrig = .SelectedItem.Index 'Save original.
                  mblnEscTabClick = True 'Prevent the tab click operation.
               End If
               .Tabs(I).Selected = True
               Call Cancel1st(True) 'Unload.
            End If
         End If
      Next
      If intTabOrig <> 0 Then
         .Tabs(intTabOrig).Selected = True 'Select the original, if deselected in For.
         mblnEscTabClick = False 'Reset.
      End If
   End With
   DatFrmUnld = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Implement the 1st part of the DatFrm_Cancel procedure. This part is separated from the
'  2nd one for the DatFrmUnld procedure.
Private Sub Cancel1st(ByVal blnCtlClear As Boolean)
On Error GoTo ErrHnd
   With tabShG.SelectedItem
      If blnCtlClear Then Call DatFrm_CtlClear 'Clear the controls, if required.
      mintIsDirty(.Index) = False
      Select Case .Index 'Distinguish this part by data form.
      Case gobSetng.FrmInvenIdx
         Call DatFrm_SwchCtlFill(False, True) 'Shwitch the controls.
      Case gobSetng.FrmMatIdx To gobSetng.FrmApprIdx
         Call DatFrm_SwchCtlFill(False) 'Shwitch the controls.
         Call CancelClearDat 'Drop the data.
         Select Case .Index 'Clear the grids.
         Case gobSetng.FrmMatIdx, gobSetng.FrmLmKIdx
            Call BrsMatLmK("")
         Case gobSetng.FrmWtWoolIdx
            Call BrsWtWool("")
         Case gobSetng.FrmApprIdx
            Call BrsAppr("")
         End Select
      End Select
      mblnFrmFilld(.Index) = False
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Drop the ShG's data on cancelling.
Private Sub CancelClearDat()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   With gobShGs
      If .Exists(mstrIDFrm) Then 'Exists?
         With .Item(mstrIDFrm)
            Select Case tabShG.SelectedItem.Index
            Case gobSetng.FrmMatIdx
               With .Dam
                  .Mats.DelAll 'Drop mates.
                  .PopltMat = False 'Keep explicit.
               End With
            Case gobSetng.FrmLmKIdx
               With .Dam
                  .LmKs.DelAll 'Drop lamb/kiddings.
                  .PopltLmK = False 'Keep explicit.
               End With
            Case gobSetng.FrmWtLmKIdx
               Set obDatTbl = .TblWtWean
               obDatTbl.Clear
               Set obDatTbl = .TblWt7Mon
               obDatTbl.Clear
            Case gobSetng.FrmWtWoolIdx
               .WtWools.DelAll
               .PopltWtWool = False 'Keep explicit.
            Case gobSetng.FrmApprIdx
               .Apprs.DelAll
               .PopltAppr = False 'Keep explicit.
            End Select
         End With
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Add an obTblOffsp object filled with the data from the controls to the obOffsps
'  collection. If an obTblOffsp is being edited only update it.
' Prior to addition, make sure the offspring's data have been inputted.
' Add the updated obTblOffsp object's data to lvwList(miLvwOffsp).
' Clear the offspring's comboboxes.
' Enable the cmdEdit, cmdDel, cmdBrowse, & cmdOk buttons, if disabled.
' Set the focus to either txtID(miLmKLmK) or dbcFld(miLiv) depending on their Enable property.
Private Sub ClickAddLmK()
On Error GoTo ErrHnd
    If VldAdd Then 'Validate the data.
      Call OffspAddEdit 'Add or update the offspring.
      Call OffspClear 'Clear the combo boxes' content.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the selected offspring from lvwList(miLvwOffsp).
' Prior to the deletion, make sure there are offsprings in lvwList(miLvwOffsp) to delete.
' Mark the deleted offspring as deleted in the obTblOffsp object to delete if later or
'  delete it immediately from the Offsps collection, if it has been added just at this
'  session. In the former case, disable the cmdAdd & cmdEdit buttons to prevent adding
'  new offspring until the change is saved.
' Enable the cmdOk button, if disabled.
Private Sub ClickDelLmK()
On Error GoTo ErrHnd
   Dim strIDDam As String
   Dim intCycle As Integer
   Dim intNoLmK As Integer
   If lvwList(miLvwOffsp).ListItems.Count > 0 Then
      strIDDam = mobDatFrm.IDFrm 'Define the dam's ID & its active cycle.
      intCycle = gobShGs(strIDDam).Dam.LmKs.Act.Cycle
      intNoLmK = NoLmK(lvwList(miLvwOffsp).SelectedItem.Key) 'Define the deleted offspring's No.
      With gobShGs(strIDDam).Dam.LmKs.Act.Offsps 'Mark the offspring deleted or
         If .Item(intNoLmK, False).Added Then    'delete it from Offsps.
            .Del intNoLmK 'Delete.
         Else
            With .Item(intNoLmK, False) 'Mark Deld & set off Edited.
               .Deld = True
               .Edited = False
            End With
         End If
      End With
      With lvwList(miLvwOffsp) 'Delete from lvwList(miLvwOffsp).
         .ListItems.Remove (.SelectedItem.Key)
         If .ListItems.Count > 0 Then .SelectedItem.Selected = True 'Mark out the
      End With                                           'remaining selected row, if any.
      If cmdOk.Enabled = False Then cmdOk.Enabled = True 'Enable cmdOk.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Move the offspring from lvwList(miLvwOffsp) & put it to the Offspring comboboxes to edit.
' Prior to the move, make sure there are offsprings in lvwList(miLvwOffsp) to edit.
' Mark the Offsps collection Edited.
' Mark the obTblOffsp object Edited in the Edit mode or specify the active edited
'  offspring in the Add mode.
' If the edited offspring has been previously added omit marking as edited.
' Switch cmdEdit, cmdDel, cmdBrowse, cmdOk, lvwList(miLvwOffsp) & ofsspring controls.
Private Sub cmdEdit_Click(Index As Integer)
On Error GoTo ErrHnd
   Dim intCycle As Integer
   Dim intNoLmK As Integer
   If lvwList(miLvwOffsp).ListItems.Count > 0 Then
      gobShGs(mobDatFrm.IDFrm).Dam.LmKs.Act.Offsps.Edited = True
      intNoLmK = NoLmK(lvwList(miLvwOffsp).SelectedItem.Key)  'Define the moved offspring's No.
      With gobShGs(mobDatFrm.IDFrm).Dam.LmKs.Act
         intCycle = .Cycle
         If mobDatFrm.Mode = gobSetng.ModeEdit Then
            With .Offsps(intNoLmK, False) 'Mark obTblOffsp Edited
               If Not .Added Then
                  .Edited = True 'Omit marking an added offsrping.
               End If
            End With
         Else
            .Offsps.NoLmKAct = intNoLmK 'Specify the active offspring.
         End If
         Call OffspMove 'Move the offspring.
         With .Offsps(intNoLmK, False)
            Call SwchBtnLmK(False, .Edited, .IDLiv) 'Switch controls.
         End With
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the active cycle's lambing/kidding date & calculate TypeBirth.
Private Sub CtlReadLmK()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm).Dam.LmKs.Act 'Get the active cycle's data.
      .DateLmK = txtDate(miDateLmK) 'Lambing/kidding date.
      .TypeBirth = .Offsps.Count
      .Abort = chkFld(miAbortChk)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the DB to the Dam object object associated with the data form.
' In an Edit of Del mode, fill out this form with the data from the last cycle of the Dam
' In the Add mode open a new empty cycle to fill data in it.
Private Sub DBtoFrmLmK()
On Error GoTo ErrHnd
   Dim strKey As String
   With gobShGs(mstrIDFrm).Dam
      If Not .PopltLmK Then .LmKSel True 'Prepare data.
      If Not .VldFail Then 'Check whether the specified dam exists.
         If mintMode(gobSetng.FrmLmKIdx) = gobSetng.ModeAdd Then
            .LmKNewOpen 'Open a new cycle.
         ElseIf Not gobMsgInst.NoLmKng(Me) Then
            Call CtlWriteLmK(.LmKs.Last(False)) 'Fill the form.
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the Dam object associated with the
'   data form to put it into the DB.
' First insert/update the active cycle in the LambKid table.
' Roll back operations on SQL server's error, if any.
' Then insert/update the offspring/s in the Offspring table.
Private Sub FrmToDBLmK()
On Error GoTo ErrHnd
   Dim intCycle As Integer
   gcnnConn.BeginTrans 'Begin transaction.
   With gobShGs(mstrIDFrm).Dam
      intCycle = .LmKs.Act.Cycle 'Define the active cycle.
      If mintMode(gobSetng.FrmLmKIdx) = gobSetng.ModeDel Then
         .LmKDel 'Deletion.
      Else
         DatFrm_CtlRead 'Read the controls.
         Select Case mintMode(gobSetng.FrmLmKIdx) 'Accomplish the mode's opertation.
         Case gobSetng.ModeAdd
            .LmKIns
         Case gobSetng.ModeEdit
            .LmKUpd
         End Select
      End If
   End With
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Shwitch on/off the LmK data form's controls depending on whether the txtID(miDamLmK) is
'  filled.
Private Sub SwchCtlFillLmK(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   Call SwchID(miDamLmK, miDamLmK, True, Not blnEnable)
   Call SwchCtlFillDate(miDateLmK, miDateLmK, blnEnable)
   chkFld(miAbortChk).Enabled = blnEnable
   Call SwchCtlObj(optFld, miOptLmKAliv, miOptLmKDead, blnEnable)
   Call SwchCtlLbl(lblID(miLmKLmK), txtID(miLmKLmK), blnEnable)
'   Call SwchID(miLmKLmK, miLmKLmK, False, blnEnable)
   Call SwchCtlObj(lblFld, miSexLmK, miLiv, blnEnable)
   Call SwchCtlObj(dbcFld, miSexLmK, miLiv, blnEnable)
   Call SwchCtlLbl(lblNum(miWtBirth), txtNum(miWtBirth), blnEnable)
   If Not blnEnable Then lvwList(miLvwOffsp).ListItems.Clear 'Clear lvwList(miLvwOffsp), when the rest controls are switched off.
   Call Util.SwchListView(lvwList(miLvwOffsp), blnEnable)
   Call SwchBtnLvw(miLvwOffsp, blnEnable)
   Call SwchCtlLbl(lblGrid(miFlexLmK), flexGrid(miFlexLmK), blnEnable)
   If blnEnable Then 'Switch the option controls.
      If Not optFld(miOptLmKAliv) Then
         optFld(miOptLmKAliv) = True 'Switching on the optFld(miOptLmKAliv)-related controls is invoked
      Else                  'implicitly by setting optFld(miOptLmKAliv).Value.
         Call LmKAlivDead(miOptLmKAliv) 'Invoke switchin on the optFld(miOptLmKAliv)-related
      End If                                 'controls explicitly.
   End If
   If blnEnable Then Call SwchAbort 'Switch the offspring controls.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
Private Sub SwchCtlModeLmK()
On Error GoTo ErrHnd
   Select Case mintMode(gobSetng.FrmLmKIdx) 'Switch by mode.
   Case gobSetng.ModeAdd, gobSetng.ModeEdit
      Call DatFrm_SwchCtlFill(True)
      txtDate(miDateLmK).SetFocus
   Case gobSetng.ModeDel
      txtID(miDamLmK).Enabled = False
      cmdID(miDamLmK).Enabled = False
      Call SwchCtlLbl(lblGrid(miFlexLmK), flexGrid(miFlexLmK), True)
      cmdOk.Enabled = True
      cmdOk.SetFocus
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function VldLmK() As Boolean
On Error GoTo ErrHnd
   If VldFillCtlLmK Then 'Filling the controls.
      If VldMinMaxAgeLmK Then 'Min/max age at lamb/kidding.
         If VldLmKOffsp Then 'Offsprings' dates consistency.
            If VldPregnLengLmK Then VldLmK = VldOvlpLmK 'Pregnancy length & overlapping.
         End If
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the dam's minimal & maximal age at lamb/kidding.
' Return True, if succeeds.
Private Function VldMinMaxAgeLmK() As Boolean
On Error GoTo ErrHnd
   Dim lngAge As Long
   Dim lngAgeMin As Long
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm)
      If Not .Lives(txtDate(miDateLmK), fraFrame(gobSetng.FrmLmKIdx).Caption, strPromt:= _
         strPromt) Then 'Validate the dam's age.
         blnFail = True 'The dam doesn't live.
      Else
         lngAge = .Age(txtDate(miDateLmK)) 'Validate the min age at lamb/kidding.
         lngAgeMin = gobTblCtrlParam.AgeMatMinDm + gobTblCtrlParam.PregnLengMin
         If lngAge < lngAgeMin Then
            blnFail = True 'Too young to lamb/kid.
            strPromt = LoadResString(542) & lngAge & LoadResString(233) & txtDate( _
               miDateLmK) & LoadResString(544) & lngAgeMin & LoadResString(234)
         End If
      End If
   End With
   If blnFail Then 'Message & focus.
      MsgBox strPromt, vbExclamation, LoadResString(131)
      txtDate(miDateLmK).SetFocus
   Else 'Succeeded.
      VldMinMaxAgeLmK = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the logical consistence of the inputted data in an Add or Edit mode. Make sure
'  there are the lambing/kidding date & offspring/s in lvwList(miLvwOffsp).
' Return True, if succeeds.
Private Function VldFillCtlLmK() As Boolean
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   Dim strLabel As String
   Dim blnEscMsg As Boolean
   If Trim$(txtDate(miDateLmK)) = "" Then 'Define the lambing/kidding date.
      Set ctlCtl = txtDate(miDateLmK)
      strLabel = lblDate(miDamLmK)
   ElseIf lvwList(miLvwOffsp).ListItems.Count = 0 And chkFld(miAbortChk) = 0 Then 'Define an offspring/s.
      blnEscMsg = True 'Escape messaging in Util.MissParam.
      MsgBox LoadResString(240), vbExclamation, LoadResString(21)
      chkFld(miAbortChk).SetFocus
   Else
      VldFillCtlLmK = True 'Validation passed.
   End If 'Below: 'Message & focus.
   If VldFillCtlLmK = False And blnEscMsg = False Then Call Util.MissParam(ctlCtl, _
      strLabel)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtid(miDamLmK).
Private Sub ClickOkLmK()
On Error GoTo ErrHnd
   Dim intResp As Integer
   Call UnldSyncMatLmK(gobSetng.FrmMatIdx) 'Unload the Mat data form.
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit
         If .Vld Then 'Validate data in an Add or Edit mode.
            .FrmToDB
            .Cancel False
            txtID(miDamLmK).SetFocus
         End If
      Case gobSetng.ModeDel
         Beep
         intResp = MsgBox("Вы уверены, что хотите удалить данное ягнение/козление?", _
            vbYesNoCancel + vbQuestion, LoadResString(372)) 'The Del mode.
         Select Case intResp 'Yes, No, or Cancel response.
         Case vbYes
            .FrmToDB
            .Cancel True
            Call InitTxt(True) 'Initialise text boxes.
            txtID(miDamLmK).SetFocus
         Case vbNo
            cmdOk.SetFocus
         Case vbCancel
            .Cancel True
            txtID(miDamLmK).SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' On pressing the Add button, check whether all controls except lvwList(miLvwOffsp) been
'  filled.
' Restrict the number of offsprings to 6.
' Return True, if succeeds.
Private Function VldAdd() As Boolean
On Error GoTo ErrHnd
   Const intMaxOffsp As Integer = 6 'The maximal number of ofsprings.
   If Trim$(txtDate(miDateLmK)) = "" Then 'Define the lambing/kidding date.
      Call Util.MissParam(txtDate(miDateLmK), lblDate(miDamLmK))
   ElseIf lvwList(miLvwOffsp).ListItems.Count >= intMaxOffsp Then 'Over 6 offsprings?
      MsgBox LoadResString(706) & intMaxOffsp & ".", vbExclamation, LoadResString(131)
      cmdAdd(miLvwOffsp).SetFocus
   Else
      Select Case optFld(miOptLmKAliv) 'Distinguish an alive & dead offspring.
      Case True
         If Trim$(txtID(miLmKLmK)) = "" Then 'Define the offspring's ID.
            MsgBox LoadResString(702), vbExclamation, LoadResString(131)
            txtID(miLmKLmK).SetFocus
         ElseIf dbcFld(miSexLmK).BoundText = "" Then 'Define the sex.
            MsgBox LoadResString(703), vbExclamation, LoadResString(131)
            dbcFld(miSexLmK).SetFocus
         ElseIf gobFormtCtl.BlankNum(txtNum(miWtBirth)) Then 'Define the weight.
            MsgBox LoadResString(704), vbExclamation, LoadResString(131)
            txtNum(miWtBirth).SetFocus
         Else
            VldAdd = True 'Suscceeded.
         End If
      Case False
         If dbcFld(miLiv).BoundText = "" Then 'Define the livability option.
            MsgBox LoadResString(705), vbExclamation, LoadResString(131)
            dbcFld(miLiv).SetFocus
         Else
            VldAdd = True 'Suscceeded.
         End If
      End Select
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub IDCtlPressLmK(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm) 'Set the menu & IsDirty mark.
      If intKeyAscii <> gobFormtCtl.AscEnter Then
         intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
      Else
         intKeyAscii = 0 'Cancel Enter
         If Len(Trim$(txtID(miDamLmK))) = gobFormtCtl.LengIDShG Then
            .RegistFrm Trim$(txtID(miDamLmK)), True 'Process the command corresponding to the
            If gobMsgInst.DuplFrm Then           'mode. Register the form.
               cmdCancel.SetFocus 'Avoid duplication by ivoking the LostFocus procedure.
            Else
               .DBtoFrm 'Fill the form in an Edit/Del mode.
               If gobShGs(.IDFrm).Dam.VldFail Or gobMsgInst.LmKed(Me) Then
                  .Cancel False 'Cancel the current changes, if any.
                  txtID(miDamLmK).SetFocus
               ElseIf (gobMsgInst.NoLmKng(Me)) And (.Mode = gobSetng.ModeEdit Or _
                  .Mode = gobSetng.ModeDel) Then
                  MsgBox LoadResString(170) & .IDFrm & LoadResString(171), _
                     vbExclamation, LoadResString(172) 'No lambing/kidding can be exposed in an Edit/Del
                  .Cancel False      'mode.
                  txtID(miDamLmK).SetFocus
               Else
                  Call BrsMatLmK(mstrIDFrm) 'Fill the Mate/LmK grid.
                  mblnFrmFilld(gobSetng.FrmLmKIdx) = True 'Mark filled.
                  .SwchCtlMode 'Switch controls by mode.
               End If
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form's controls.
Private Sub InitCtlLmK()
On Error GoTo ErrHnd
   Dim colIDLmK As ColumnHeader
   Dim colSex As ColumnHeader
   Dim colWtBirth As ColumnHeader
   Dim colLiv As ColumnHeader
   adoFld(miSexLmK).ConnectionString = gcnnConn.ConnectionString 'Set the data source for adoFld(miSexLmK) & dbcFld(miSexLmK).
   Call Util.DbcSetRowSrc(dbcFld(miSexLmK), adoFld(miSexLmK), "IDSex", "Sex")
   adoFld(miLiv).ConnectionString = gcnnConn.ConnectionString 'Set the data source for adoFld(miLiv) & dbcFld(miLiv).
   Call Util.DbcSetRowSrc(dbcFld(miLiv), adoFld(miLiv), "IDLiv", "Liv")
   Set colIDLmK = lvwList(miLvwOffsp).ColumnHeaders.Add() 'Set lvwList(miLvwOffsp)'s column headers.
   colIDLmK.Text = LoadResString(607)
   colIDLmK.Width = lvwList(miLvwOffsp).Width * 0.3
   Set colSex = lvwList(miLvwOffsp).ColumnHeaders.Add()
   colSex.Text = "Пол"
   colSex.Width = lvwList(miLvwOffsp).Width * 0.15
   Set colWtBirth = lvwList(miLvwOffsp).ColumnHeaders.Add()
   colWtBirth.Text = "Вес"
   colWtBirth.Width = lvwList(miLvwOffsp).Width * 0.15
   Set colLiv = lvwList(miLvwOffsp).ColumnHeaders.Add()
   colLiv.Text = "Cостояние"
   colLiv.Width = lvwList(miLvwOffsp).Width * 0.4
   Call BrsMatLmK("") 'Initialise the Mate/LmK grid.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable a clicked option's controls to input data.
Private Sub LmKAlivDead(ByVal intIdx As Integer)
On Error GoTo ErrHnd
   Dim blnAliv As Boolean
   Dim blnDead As Boolean
   blnAliv = IIf(intIdx = miOptLmKAliv, True, False)
   blnDead = IIf(intIdx = miOptLmKDead, True, False)
   Call SwchCtlLbl(lblID(miLmKLmK), txtID(miLmKLmK), blnAliv)
'   cmdID(miLmKLmK).Enabled = blnAliv
   Call SwchCtlLbl(lblFld(miSexLmK), dbcFld(miSexLmK), blnAliv)
   Call SwchCtlLbl(lblNum(miWtBirth), txtNum(miWtBirth), blnAliv)
   Call SwchCtlLbl(lblFld(miLiv), dbcFld(miLiv), blnDead)
   lblID(miLmKLmK).Visible = blnAliv
   txtID(miLmKLmK).Visible = blnAliv
   cmdID(miLmKLmK).Visible = blnAliv
   lblFld(miSexLmK).Visible = blnAliv
   dbcFld(miSexLmK).Visible = blnAliv
   lblNum(miWtBirth).Visible = blnAliv
   txtNum(miWtBirth).Visible = blnAliv
   lblFld(miLiv).Visible = blnDead
   dbcFld(miLiv).Visible = blnDead
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the data from the Offspring controls distinguishing an alive & dead offspring.
Private Function OffspRead() As TblOffsp
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim strIDDam As String
   Set obTblOffsp = New TblOffsp
   With obTblOffsp
      strIDDam = mobDatFrm.IDFrm 'Define the dam's ID & cycle.
      .IDDam = strIDDam
      .Cycle = gobShGs(strIDDam).Dam.LmKs.Act.Cycle
      If optFld(miOptLmKAliv) Then
         .IDLmK = txtID(miLmKLmK)
         .IDSex = dbcFld(miSexLmK).BoundText
         .Sex = dbcFld(miSexLmK).Text
         .WtBirth = CSng(txtNum(miWtBirth)) 'Convert WtBirth from a string to a single number.
         .IDLiv = gobSetng.Liv.IDLivAlive
         .Liv = gobSetng.Liv.LivAlive
      Else
         .IDLiv = dbcFld(miLiv).BoundText
         .Liv = dbcFld(miLiv).Text
      End If
   End With
   Set OffspRead = obTblOffsp
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Clear the Offspring combo boxes' content.
' Set the focus to txtID(miLmKLmK) or dbcFld(miLiv) based on the selected
'   offspring's status at birth.
Private Sub OffspClear()
On Error GoTo ErrHnd
   txtID(miLmKLmK) = ""
   cmdID(miLmKLmK).Enabled = False
   dbcFld(miSexLmK).Text = ""
   txtNum(miWtBirth) = ""
   dbcFld(miLiv).Text = ""
   ' Enable the buttons.
   Call SwchBtnLmK(True)
   ' Set the focus to txtID(miLmKLmK) or dbcFld(miLiv).
   If optFld(miOptLmKAliv) Then
       txtID(miLmKLmK).SetFocus
   Else
       dbcFld(miLiv).SetFocus
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill out the lvwList(miLvwOffsp) control with the data from the supplied
'   obTblOffsp object.
Private Sub OffspFillLst(ByVal obTblOffsp As TblOffsp)
On Error GoTo ErrHnd
   Dim strKey
   With obTblOffsp
      strKey = .IDDam & "-" & CStr(.Cycle) & "-" & .NoLmK 'Create a unique key.
      lvwList(miLvwOffsp).ListItems.Add , strKey, .IDLmK 'Add.
      lvwList(miLvwOffsp).ListItems(strKey).ListSubItems.Add 1, , .Sex
      lvwList(miLvwOffsp).ListItems(strKey).ListSubItems.Add 2, , gobFormtCtl _
         .NumFrac(.WtBirth)
      lvwList(miLvwOffsp).ListItems(strKey).ListSubItems.Add 3, , .Liv
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Add a new offpsring or update an editted one.
' Mark the offspring as added in the Offsps collection, if added but not edited.
Private Sub OffspAddEdit()
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim intNoLmKNew As Integer
   Set obTblOffsp = OffspRead 'Read the data.
   With gobShGs(obTblOffsp.IDDam).Dam.LmKs.Act.Offsps
      If .Edited Then 'Add or update.
         .Edited = False
         With .Act 'Update the edited offspring.
            .IDLmK = obTblOffsp.IDLmK
            .IDSex = obTblOffsp.IDSex
            .Sex = obTblOffsp.Sex
            .WtBirth = obTblOffsp.WtBirth
            .IDLiv = obTblOffsp.IDLiv
            .Liv = obTblOffsp.Liv
         End With
      Else
         intNoLmKNew = .NoLmKNew
         .Add intNoLmKNew, intNoLmKNew, obTblOffsp.IDLmK, obTblOffsp.IDSex, _
            obTblOffsp.Sex, obTblOffsp.WtBirth, obTblOffsp.IDLiv, obTblOffsp.Liv
         .Act.Added = True 'Mark the offspring added.
      End If
      Call OffspFillLst(.Act) 'Update lvwList(miLvwOffsp).
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Retrieve the selected offspring's NoLambKid from lvwList(miLvwOffsp)'s list's
'   key.
Private Function NoLmK(ByVal strKey As String) As Integer
On Error GoTo ErrHnd
    Dim strNoLmK As String
    ' Cut the first two-symbol sample.
    strNoLmK = Right$(strKey, 2)
    ' If there is "-" in front of the samle exclude it & define
    '   NoLmK.
    NoLmK = CInt(IIf(Left$(strNoLmK, 1) = "-", Right$(strNoLmK, 1), strNoLmK))
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Move the offspring from lvwList(miLvwOffsp) & to the Offspring controls to edit.
' Focus either txtNum(miWtBirth) or dbcFld(miLiv) depending on their Enable property.
Private Sub OffspMove()
On Error GoTo ErrHnd
   Const intItemSex As Integer = 1 'The Sex & WtBirth ListSubItems in the lvwList(miLvwOffsp) list
   Const intItemWtBirth As Integer = 2 'view.
   txtID(miLmKLmK) = "" 'Clear the Ofsspring controls.
   dbcFld(miSexLmK).Text = ""
   txtNum(miWtBirth) = ""
   dbcFld(miLiv).Text = ""
   With lvwList(miLvwOffsp) 'Move to the Ofsspring controls.
       If .SelectedItem.ListSubItems(mintItemLiv).Text = gobSetng.Liv.LivAlive Then
         optFld(miOptLmKAliv) = True 'Alive offspring.
         txtID(miLmKLmK) = .SelectedItem.Text
         cmdID(miLmKLmK).Enabled = True
         dbcFld(miSexLmK).Text = .SelectedItem.ListSubItems(intItemSex).Text
         txtNum(miWtBirth) = gobFormtCtl.NumFrac(CSng(.SelectedItem.ListSubItems _
            (intItemWtBirth).Text))
         txtNum(miWtBirth).SetFocus 'Focus.
      Else
         optFld(miOptLmKDead) = True 'Dead offspring.
         dbcFld(miLiv).Text = .SelectedItem.ListSubItems(mintItemLiv).Text
         dbcFld(miLiv).SetFocus 'Set focus.
      End If
      .ListItems.Remove (.SelectedItem.Key) 'Delete from lvwList(miLvwOffsp).
      If .ListItems.Count > 0 Then .SelectedItem.Selected = True 'Mark the remaining
   End With                                                      'selected row, if any.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable the cmdEdit, cmdDel, cmdBrowse & cmdOk buttons to make the user either
'  complete or cancel the edition altogether.
' In the Edit mode, unless an offspring is newly added at the current session (i.e. an
'  offsrpring from the DB being edited) disable the alive/dead offspring controls to
'  prevent changing an offspring' ID, sex & livability.
' If the blnEnable argument is True enable all controls regardlessly.
Private Sub SwchBtnLmK(ByVal blnEnable As Boolean, Optional ByVal blnEdited As Boolean, _
   Optional ByVal strIDLiv As String)
On Error GoTo ErrHnd
   cmdEdit(miLvwOffsp).Enabled = blnEnable 'Buttons & lvwList(miLvwOffsp).
   cmdDel(miLvwOffsp).Enabled = blnEnable
   cmdOk.Enabled = blnEnable
   Call Util.SwchListView(lvwList(miLvwOffsp), blnEnable) 'Switch lvwList(miLvwOffsp).
   If blnEnable Then 'Enable all ofsspring controls regardlessly.
      optFld(miOptLmKAliv).Enabled = True
      optFld(miOptLmKDead).Enabled = True
      txtID(miLmKLmK).Enabled = True
      dbcFld(miSexLmK).Enabled = True
   Else 'Disable only in the Edit mode & for an edited offspring.
      If mobDatFrm.Mode = gobSetng.ModeEdit And blnEdited Then
         optFld(miOptLmKAliv).Enabled = False 'Prevent changing livability.
         optFld(miOptLmKDead).Enabled = False
         If strIDLiv = gobSetng.Liv.IDLivAlive Then
            txtID(miLmKLmK).Enabled = False 'Alive - prevent changeing ID & sex.
            dbcFld(miSexLmK).Enabled = False
         End If
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the forms' ID controls & number text boxes.
' If the blnClearPrev argument is True clear the previous value, otherwise unless the
'  textbox is blank keep the previous value.
Private Sub InitTxtLmK(ByVal blnClearPrev As Boolean)
On Error GoTo ErrHnd
   If blnClearPrev Then
      txtNum(miWtBirth) = gobFormtCtl.NumFrac(0)
   Else
      If txtNum(miWtBirth) = "" Then txtNum(miWtBirth) = gobFormtCtl.NumFrac(0)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
' Disable the offspring controls, if selected, & vice versa.
Private Sub SwchAbort()
On Error GoTo ErrHnd
   Dim blnEnable As Boolean
   blnEnable = IIf(chkFld(miAbortChk) = vbUnchecked, True, False) 'Define the state.
   optFld(miOptLmKAliv).Enabled = blnEnable 'Switch.
   optFld(miOptLmKDead).Enabled = blnEnable
   Call Util.SwchListView(lvwList(miLvwOffsp), blnEnable) 'Switch lvwList(miLvwOffsp).
   cmdAdd(miLvwOffsp).Enabled = blnEnable
   cmdEdit(miLvwOffsp).Enabled = blnEnable
   cmdDel(miLvwOffsp).Enabled = blnEnable
   Select Case blnEnable 'Distinguish switching the alive-dead controls.
   Case False 'Disable regardlessly.
      Call SwchCtlLbl(lblID(miLmKLmK), txtID(miLmKLmK), blnEnable)
      Call SwchCtlLbl(lblFld(miSexLmK), dbcFld(miSexLmK), blnEnable)
      Call SwchCtlLbl(lblNum(miWtBirth), txtNum(miWtBirth), blnEnable)
      Call SwchCtlLbl(lblFld(miLiv), dbcFld(miLiv), blnEnable)
   Case True 'Enable the alive-dead controls based on the respective option.
      If optFld(miOptLmKAliv) Then 'Alive.
         Call LmKAlivDead(miOptLmKAliv)
      ElseIf optFld(miOptLmKDead) Then 'Dead.
         Call LmKAlivDead(miOptLmKDead)
      End If
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the controls with the data from the specified obTblLmK object.
Private Sub CtlWriteLmK(ByVal obTblLmK As TblLmK)
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Call DatFrm_CtlClear 'Clear & reinitialise the controls.
   Call InitTxt(True)
   With obTblLmK
      txtID(miDamLmK) = .IDDam 'Fill it for frmBrsMateLmK.
      gobFormtCtl.WriteDate txtDate(miDateLmK), dtpDate(miDateLmK), .DateLmK
      chkFld(miAbortChk) = .Abort
      For Each obTblOffsp In .Offsps 'Fill mobOffsps.
         Call OffspFillLst(obTblOffsp)
      Next obTblOffsp
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the buttons adjacent to the specified list view.
Private Sub SwchBtnLvw(ByVal intIdx As Integer, ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   cmdAdd(intIdx).Enabled = blnEnable
   cmdDel(intIdx).Enabled = blnEnable
   If intIdx = miLvwOffsp Then cmdEdit(intIdx).Enabled = blnEnable 'For the offspring
Exit Sub                                                           'list view only.
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtMisc_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   If Index = miBrdCrsTxt Then gobFormtCtl.SelTxt txtMisc(Index) 'Select cross breed.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtNum_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtNum(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the inputted number for formatting & minimum/maximum.
Private Sub txtNum_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   Const sngWtBirthMin As Single = 2 'The min/max.
   Const sngWtBirthMax As Single = 8
   Const sngWtWean7MonMin As Single = 20
   Const sngWtWean7MonMax As Single = 40
   Const intDensityMin As Integer = 2000
   Const intDensityMax As Integer = 7000
   Const intFluffMin As Integer = 60
   Const intFluffMax As Integer = 80
   Const intFibreYieldMin As Integer = 80
   Const intFibreYieldMax As Integer = 98
   With gobFormtCtl
      Select Case Index
      Case miWtBirth
         Cancel = Not .VldNum(txtNum(Index), sngWtBirthMin, sngWtBirthMax)
      Case miWtWean, miWt7Mon
         Cancel = Not .VldNum(txtNum(Index), sngWtWean7MonMin, sngWtWean7MonMax)
      Case miWtAnnl
         Cancel = Not .VldNum(txtNum(Index), .MinWt1Yr, .MaxWt1Yr)
      Case miGreaseAnnl
         Cancel = Not .VldNum(txtNum(Index), .MinGrease, .MaxGrease)
      Case miLeng
         Cancel = Not .VldNum(txtNum(Index), .MinLeng, .MaxLeng)
      Case miDensity
         Cancel = Not .VldNum(txtNum(Index), intDensityMin, intDensityMax, True)
      Case miFluff
         Cancel = Not .VldNum(txtNum(Index), intFluffMin, intFluffMax, True)
      Case miFibreYield
         Cancel = Not .VldNum(txtNum(Index), intFibreYieldMin, intFibreYieldMax, True)
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise & switch once the selected data form's controls.
Private Sub InitCtlSwch()
On Error GoTo ErrHnd
   Static blnPassed() As Boolean
   ReDim Preserve blnPassed(gobSetng.FrmInvenIdx To gobSetng.FrmApprIdx) As Boolean
   If Not blnPassed(tabShG.SelectedItem.Index) Then 'Execute once.
      blnPassed(tabShG.SelectedItem.Index) = True 'Passed.
      Call Util.SwchBtnMouse(Me, False, True) 'Switch the mouse.
      Call InitCtl 'Initialise.
      mobDatFrm.SwchCtlFill False, True 'Switch.
      Call Util.SwchBtnMouse(Me, True, True) 'Reset the mouse.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtID(miLmKWtLmK).
Private Sub ClickOkWtLmK()
On Error GoTo ErrHnd
   Dim intResp As Integer
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit
         If .Vld Then 'Validate data in an Add or Edit mode.
            .FrmToDB
            .Cancel False
            txtID(miLmKWtLmK).SetFocus
         End If
      Case gobSetng.ModeDel
         Beep
         intResp = MsgBox(LoadResString(314), vbYesNoCancel + vbQuestion, _
            LoadResString(372)) 'The Del mode.
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            .FrmToDB
            .Cancel True
            Call InitTxt(True) 'Initialise text boxes.
            txtID(miLmKWtLmK).SetFocus
         Case vbNo
            cmdOk.SetFocus
         Case vbCancel
            .Cancel True
            txtID(miLmKWtLmK).SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the controls.
Private Sub CtlReadWtLmK()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm)
      With .TblWtWean
         If Trim$(txtDate(miDateWean)) <> "" Then
            .IDLmK = mstrIDFrm
            .DateWean = Trim$(txtDate(miDateWean))
            .WtWean = Trim$(txtNum(miWtWean))
         Else
Debug.Assert 0 = 1 'Verify
            .IDLmK = ""
            .DateWean = 0
            .WtWean = 0
         End If
      End With
      With .TblWt7Mon
         If Not Trim$(txtDate(miDate7Mon)) = "" Then
            .IDLmK = mstrIDFrm
            .Date7Mon = Trim$(txtDate(miDate7Mon))
            .Wt7Mon = Trim$(txtNum(miWt7Mon))
         Else
            .IDLmK = ""
            .Date7Mon = 0
            .Wt7Mon = 0
         End If
      End With
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the WeightWean & Weight7Mon tables to the ShG object.
' In the Edit/Del mode, fill the controls from the ShG object.
' Prior to filling, clear & reinitialise the controls to drop the previous contents, if
'  any.
' In the Add mode, check whether there is a weighing already.
Private Sub DBtoFrmWtLmK()
On Error GoTo ErrHnd
   Dim obDatTblWean As DatTbl
   Dim obDatTbl7Mon As DatTbl
   With gobShGs(mstrIDFrm)
      .SelWtWean True 'Prepare data from the WeightWean table.
      If .TblShG.Full Then 'Check if the lamb/kid exists.
         .SelWt7Mon 'Prepare data from the Weight7Mon table.
         If mintMode(gobSetng.FrmWtLmKIdx) = gobSetng.ModeEdit Or mintMode(gobSetng _
            .FrmWtLmKIdx) = gobSetng.ModeDel Then 'Proceed in an Edit/Del mode.
            Call DatFrm_CtlClear 'Clear & reinitialise the controls.
            Call InitTxt(True)
            Set obDatTblWean = .TblWtWean
            If obDatTblWean.Full Then 'Check if there's a weighing to fill.
               With .TblWtWean
                  gobFormtCtl.WriteDate txtDate(miDateWean), dtpDate(miDateWean), _
                     .DateWean
                  txtNum(miWtWean) = gobFormtCtl.NumFrac(.WtWean)
               End With
            End If
            Set obDatTbl7Mon = .TblWt7Mon
            If obDatTbl7Mon.Full Then 'Check if there's a weighing to fill.
               With .TblWt7Mon
                  gobFormtCtl.WriteDate txtDate(miDate7Mon), dtpDate(miDate7Mon), _
                     .Date7Mon
                  txtNum(miWt7Mon) = gobFormtCtl.NumFrac(.Wt7Mon)
               End With
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the ShG object associated with the data form in an
'  Add or Edit mode.
' Accomplish the mode's corresponding operation.
Private Sub FrmToDBWtLmK()
On Error GoTo ErrHnd
   Dim obDatTblWean As DatTbl
   Dim obDatTbl7Mon As DatTbl
   gcnnConn.BeginTrans 'Begin the transaction.
   With gobShGs(mstrIDFrm)
      Set obDatTblWean = .TblWtWean 'Set the data tables for later use.
      Set obDatTbl7Mon = .TblWt7Mon
      If mintMode(gobSetng.FrmWtLmKIdx) = gobSetng.ModeDel Then 'Deletion.
Debug.Assert 0 = 1 'Verify obDatTblWean.Full
         If obDatTblWean.Full Then obDatTblWean.Del 'Weaning wt.
'         If .TblWtWean.Full Then obDatTblWean.Del 'Weaning wt.
Debug.Assert 0 = 1 'Verify obDatTbl7Mon.Full
         If obDatTbl7Mon.Full Then obDatTbl7Mon.Del '7-month wt.
'         If .TblWt7Mon.Full Then obDatTbl7Mon.Del '7-month wt.
      Else
         Call DatFrm_CtlRead 'Read the controls.
         Select Case mintMode(gobSetng.FrmWtLmKIdx)
         Case gobSetng.ModeAdd 'Addition.
            If Trim$(txtDate(miDateWean)) <> "" Then obDatTblWean.Ins
            If Trim$(txtDate(miDate7Mon)) <> "" Then obDatTbl7Mon.Ins
         Case gobSetng.ModeEdit 'Edition.
            Call FrmToDBEdit(txtDate(miDateWean), obDatTblWean, obDatTblWean.Full) 'Weaning wt.
            Call FrmToDBEdit(txtDate(miDate7Mon), obDatTbl7Mon, obDatTbl7Mon.Full) '7 month wt.
         End Select
      End If
   End With
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Shwitch on/off the data form's controls depending on whether the txtID(miLmKWtLmK) is filled.
Private Sub SwchCtlFillWtLmK(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Call SwchID(miLmKWtLmK, miLmKWtLmK, True, Not blnEnable)
   Call SwchCtlFillDate(miDateWean, miDate7Mon, blnEnable)
   Call SwchCtlObj(lblNum, miWtWean, miWt7Mon, blnEnable)
   Call SwchCtlObj(txtNum, miWtWean, miWt7Mon, blnEnable)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
Private Sub SwchCtlModeWtLmK()
On Error GoTo ErrHnd
   Select Case mintMode(gobSetng.FrmWtLmKIdx) 'Switch by mode.
   Case gobSetng.ModeAdd, gobSetng.ModeEdit
      Call DatFrm_SwchCtlFill(True)
      txtDate(miDateWean).SetFocus
   Case gobSetng.ModeDel
      txtID(miLmKWtLmK).Enabled = False
      cmdID(miLmKWtLmK).Enabled = False
      cmdOk.Enabled = True
      cmdOk.SetFocus
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate how the controls are filled & the dates according to the minimal & maximal
'  ages.
' Return True, if succeeds.
Private Function VldWtLmK() As Boolean
On Error GoTo ErrHnd
   If VldFillCtlWtLmK Then 'Filling.
      VldWtLmK = VldMinMaxAgeWtLmK 'The minimal & maximal ages.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub IDCtlPressWtLmK(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Dim obDatTblWean As DatTbl
   Dim obDatTbl7Mon As DatTbl
   Dim blnFail As Boolean
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm) 'Set the menu & IsDirty mark.
      If intKeyAscii <> gobFormtCtl.AscEnter Then
         intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
      Else
         intKeyAscii = 0 'Cancel Enter
         If Len(Trim$(txtID(miLmKWtLmK))) = gobFormtCtl.LengIDShG Then
            .RegistFrm Trim$(txtID(miLmKWtLmK)), True 'Process the command corresponding to
            If gobMsgInst.DuplFrm Then               'the mode. Register the form.
               cmdCancel.SetFocus 'Avoid duplication by ivoking the LostFocus procedure.
            Else
               .DBtoFrm 'Fill the ShG object & form in an Edit/Del mode.
               With gobShGs(.IDFrm)
                  Set obDatTblWean = .TblWtWean
                  Set obDatTbl7Mon = .TblWt7Mon
               End With
               If Not gobShGs(.IDFrm).TblShG.Full Then
                  blnFail = True 'Mark an error to cancel below.
               ElseIf (obDatTblWean.Full = False And obDatTbl7Mon.Full = False) And _
                  (.Mode = gobSetng.ModeEdit Or .Mode = gobSetng.ModeDel) Then
                  blnFail = True 'No weighing to edit or delete.
                  MsgBox LoadResString(180) & .IDFrm & LoadResString(181), _
                     vbExclamation, LoadResString(172)
               ElseIf (obDatTblWean.Full Or obDatTbl7Mon.Full) And gobMsgInst.ShGDispd _
                  (Me) = False And .Mode = gobSetng.ModeAdd Then
                  blnFail = True 'No more weighing can be added.
                  MsgBox LoadResString(180) & .IDFrm & LoadResString(75), _
                     vbExclamation, LoadResString(50)
               ElseIf gobMsgInst.ShGDispd(Me) And .Mode = gobSetng.ModeAdd Then
                  blnFail = True 'No more weighing can be added after disposition.
               Else
                  .SwchCtlMode 'Switch controls by mode.
               End If
               If blnFail Then 'On an error, cancel the current changes, if any.
                  .Cancel False
                  txtID(miLmKWtLmK).SetFocus
               Else
                  mblnFrmFilld(gobSetng.FrmWtLmKIdx) = True 'Mark filled.
               End If
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the forms' ID controls & number text boxes.
' If the blnClearPrev argument is True clear the previous value, otherwise unless the
'  textbox is blank keep the previous value.
Private Sub InitTxtWtLmK(ByVal blnClearPrev As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl
      If blnClearPrev Then
         txtNum(miWtWean) = .NumFrac(0)
         txtNum(miWt7Mon) = .NumFrac(0)
      Else
         If txtNum(miWtWean) = "" Then txtNum(miWtWean) = .NumFrac(0)
         If txtNum(miWt7Mon) = "" Then txtNum(miWt7Mon) = .NumFrac(0)
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate how the controls are filled.
' There are 3 inputting options:
'  - both weaning & 7-month weights (dates & weights);
'  - only weaning weight (date & weight);
'  - only 7-month weight (date & weight).
' Return True, if succeeds.
Private Function VldFillCtlWtLmK() As Boolean
On Error GoTo ErrHnd
   With gobFormtCtl 'Below: 'Check if the weaning &/or 7-month weight are inputted.
      If Trim$(txtDate(miDateWean)) = "" And Trim$(txtDate(miDate7Mon)) = "" Then
   '      If .BlankDate(txtDateWean.ClipText) And .BlankDate(mebDate7Mon.ClipText) Then
         Call Util.MissParam(txtDate(miDateWean), , , LoadResString(393)) 'Message & focus.
      Else
         If Trim$(txtDate(miDateWean)) <> "" And .BlankNum(txtNum(miWtWean)) Then 'Check the weaning weight.
   '         If .BlankDate(txtDateWean.ClipText) = False And .BlankNum(mebWtWean.ClipText) _
            Then 'Check the weaning weight.
            Call Util.MissParam(txtNum(miWtWean), , , LoadResString(394)) 'Message & focus.
         ElseIf .BlankNum(txtNum(miWtWean)) = False And Trim$(txtDate(miDateWean)) = "" Then 'Check the weaning date.
   '         ElseIf .BlankNum(mebWtWean.ClipText) = False And .BlankDate(txtDateWean _
            .ClipText) Then 'Check the weaning date.
   Debug.Assert 0 = 1 'Verify the above line
   Debug.Assert 0 = 1 'Verify the promt.
            Call Util.MissParam(txtNum(miWtWean), , , LoadResString(395)) 'Message & focus.
         ElseIf Trim$(txtDate(miDate7Mon)) <> "" And .BlankNum(txtNum(miWt7Mon)) Then 'Check the 7-month weight.
   '         ElseIf .BlankDate(txtDate7Mon.ClipText) = False And .BlankNum(mebWt7Mon _
            .ClipText) Then 'Check the 7-month weight.
   Debug.Assert 0 = 1 'Verify the above line
            Call Util.MissParam(txtNum(miWt7Mon), , , LoadResString(396)) 'Message & focus.
         ElseIf .BlankNum(txtNum(miWt7Mon)) = False And Trim$(txtDate(miDate7Mon)) = "" Then  'Check the 7-month date.
   '         ElseIf .BlankNum(mebWt7Mon.ClipText) = False And .BlankDate(txtDate7Mon _
            .ClipText) Then 'Check the 7-month date.
   Debug.Assert 0 = 1 'Verify the above line
            Call Util.MissParam(txtDate(miDate7Mon), , , LoadResString(397)) 'Message & focus.
         Else
            VldFillCtlWtLmK = True 'Succeeded.
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the minimal & maximal ages at the weaning & 7 months.
' Return True, if succeeds.
Private Function VldMinMaxAgeWtLmK() As Boolean
On Error GoTo ErrHnd
   Dim dtmDateBirth As Date
   Dim blnFail As Boolean
   dtmDateBirth = gobShGs(mstrIDFrm).TblShG.DateBirth 'The birth date.
   With gobTblCtrlParam
      If Trim$(txtDate(miDateWean)) <> "" Then 'The age at weaning.
'      If Not gobFormtCtl.BlankDate(txtDateWean.ClipText) Then 'The age at weaning.
         If CDate(txtDate(miDateWean)) - dtmDateBirth < .AgeWeanMin Then
            blnFail = True 'Failed.
            MsgBox LoadResString(398) & .AgeWeanMin & LoadResString(231), vbExclamation _
               , LoadResString(131)  'Too young.
            txtDate(miDateWean).SetFocus
         ElseIf CDate(txtDate(miDateWean)) - dtmDateBirth > .AgeWeanMax Then
            blnFail = True 'Failed.
            MsgBox LoadResString(399) & .AgeWeanMax & LoadResString(231), vbExclamation _
               , LoadResString(131) 'Too old.
            txtDate(miDateWean).SetFocus
         End If
      End If 'Below: 'The age at 7 months.
      If blnFail = False And Trim$(txtDate(miDate7Mon)) <> "" Then
'      If blnFail = False And gobFormtCtl.BlankDate(txtDate7Mon.ClipText) = False Then
         If CDate(txtDate(miDate7Mon)) - dtmDateBirth < .Age7MonMin Then
            blnFail = True 'Failed.
            MsgBox LoadResString(400) & .Age7MonMin & LoadResString(231), vbExclamation _
               , LoadResString(131)  'Too young.
            txtDate(miDate7Mon).SetFocus
         ElseIf CDate(txtDate(miDate7Mon)) - dtmDateBirth > .Age7MonMax Then
            blnFail = True 'Failed.
            MsgBox LoadResString(401) & .Age7MonMax & LoadResString(231), vbExclamation _
               , LoadResString(131) 'Too old.
            txtDate(miDate7Mon).SetFocus
         End If
      End If
   End With
   VldMinMaxAgeWtLmK = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Complete the DatFrm_FrmToDB procedure's operation on the weaning & 7-month weights in
'  the Edit mode as follows:
'  - insert, if the controls are filled & there were no records in the DB;
'  - update, if the controls are filled & there were records in the DB;
'  - delete, if the controls are empty but there were records in the DB.
Private Sub FrmToDBEdit(ByVal txtDate As TextBox, ByRef obDatTbl As DatTbl, ByVal _
   blnFull As Boolean)
On Error GoTo ErrHnd
   If Trim$(txtDate) <> "" Then
'   If Not gobFormtCtl.BlankDate(mebDate.ClipText) Then
      If blnFull Then 'Update the previous.
         obDatTbl.Upd
      Else 'Insert the new.
         obDatTbl.Ins
      End If
   Else
      If blnFull Then obDatTbl.Del 'Delete the previous.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtID(miShGAppr).
Private Sub ClickOkWtWool()
On Error GoTo ErrHnd
   Dim intResp As Integer
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit 'Validate data in the Add/Edit modes.
         If .Vld Then
            .FrmToDB
            .Cancel False
            txtID(miShGWtWool).SetFocus
         End If
      Case gobSetng.ModeDel
         Beep
         intResp = MsgBox(LoadResString(300), vbYesNoCancel + vbQuestion, _
            LoadResString(372))
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            .FrmToDB
            .Cancel True
            Call InitTxt(True) 'Initialise text boxes.
            txtID(miShGWtWool).SetFocus
         Case vbNo
            cmdOk.SetFocus
         Case vbCancel
            .Cancel True
            txtID(miShGWtWool).SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the controls.
Private Sub CtlReadWtWool()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm).WtWools.Act
      If Trim$(txtDate(miDateAnnl)) <> "" Then
         .DateAnnl = Trim$(txtDate(miDateAnnl))
         .WtAnnl = Trim$(txtNum(miWtAnnl))
      Else
         .DateAnnl = 0 'No weighing.
         .WtAnnl = 0
      End If
      If Trim$(txtDate(miDateShearAnnl)) <> "" Then
         .DateShearAnnl = Trim$(txtDate(miDateShearAnnl))
         .GreaseAnnl = Trim$(txtNum(miGreaseAnnl))
      Else
         .DateShearAnnl = 0 'No shearing.
         .GreaseAnnl = 0
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select weignings & shears from the DB to the ShG object object associated with
'  the data form.
' In an Edit of Del mode, fill out this form with the data from the last weigning's &
'  shear's of the sheep/goat.
Private Sub DBtoFrmWtWool()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm)
      If Not .PopltWtWool Then .SelWtWool True 'Prepare data from WtWool.
      If .TblShG.Full Then 'Check if the sheep/goat exists.
         Select Case mintMode(gobSetng.FrmWtWoolIdx)
         Case gobSetng.ModeAdd 'Open a new weighing & shearing to add.
            .WtWools.AgeNewOpen
            If Not gobMsgInst.NoWtWool(Me) Then Call BrsWtWool(mstrIDFrm) 'Fill the WtWool grid.
         Case gobSetng.ModeEdit, gobSetng.ModeDel 'Fill out the form to edit or delete.
            If Not gobMsgInst.NoWtWool(Me) Then 'Check whether there are weignings.
               Call CtlWriteWtWool(.WtWools.Last(False))
               Call BrsWtWool(mstrIDFrm) 'Fill the WtWool grid.
            End If
         End Select
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the ShG object associated with the data form
'  to put it into the DB.
' Accomplish the mode's operation.
' In an Add or Edit mode calculate the sheep/goat's selection index & complex class, if
'  this is a 1-year weighing & searing.
Private Sub FrmToDBWtWool()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim intCycle As Integer
   gcnnConn.BeginTrans 'Begin transaction.
   With gobShGs(mstrIDFrm)
      Set obDatTbl = .WtWools.Act
      If mintMode(gobSetng.FrmWtWoolIdx) = gobSetng.ModeDel Then
         obDatTbl.Del
         If Not gobMsgInst.SQLErr(Me) Then .TblSelIdxCC.DelWtAppr gobSetng.FrmWtWoolIdx 'Delete
      Else                                           'selection index & complex class.
         DatFrm_CtlRead 'Read the controls.
         Select Case mintMode(gobSetng.FrmWtWoolIdx) 'Accomplish the mode's opertation.
         Case gobSetng.ModeAdd
            obDatTbl.Ins
         Case gobSetng.ModeEdit
            obDatTbl.Upd
         End Select
         .TblSelIdxCC.GetRefrsh gobSetng.FrmWtWoolIdx 'Calculate the selection index & complex class.
      End If
   End With
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Shwitch on/off the data form's controls depending on whether the txtID(miShGWtWool) is filled
Private Sub SwchCtlFillWtWool(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   Call SwchID(miShGWtWool, miShGWtWool, True, Not blnEnable)
   Call SwchCtlFillDate(miDateAnnl, miDateShearAnnl, blnEnable)
   Call SwchCtlObj(lblNum, miWtAnnl, miGreaseAnnl, blnEnable)
   Call SwchCtlObj(txtNum, miWtAnnl, miGreaseAnnl, blnEnable)
   Call SwchCtlLbl(lblGrid(miFlexWtWool), flexGrid(miFlexWtWool), blnEnable)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
Private Sub SwchCtlModeWtWool()
On Error GoTo ErrHnd
   Select Case mintMode(gobSetng.FrmWtWoolIdx)
   Case gobSetng.ModeAdd, gobSetng.ModeEdit
      Call DatFrm_SwchCtlFill(True)
      txtDate(miDateAnnl).SetFocus
   Case gobSetng.ModeDel
      txtID(miShGWtWool).Enabled = False
      cmdID(miShGWtWool).Enabled = False
      Call SwchCtlLbl(lblGrid(miFlexWtWool), flexGrid(miFlexWtWool), True)
      cmdOk.Enabled = True
      cmdOk.SetFocus
End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function VldWtWool() As Boolean
On Error GoTo ErrHnd
   If VldFillCtlWtWool Then 'Validate how the controls are filled.
      If VldMinMaxAgeWtWool Then 'Validate the dates according to the minimal & maximal ages.
         Select Case mobDatFrm.Mode 'Validate overlapping wt/wool's intervals by mode.
         Case gobSetng.ModeAdd
            VldWtWool = VldOvlpWtAdd
         Case gobSetng.ModeEdit
            VldWtWool = VldOvlpWtWoolEdit
         End Select
         If VldWtWool Then VldWtWool = VldWtWoolInter 'Validate interval between wt/wool.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub IDCtlPressWtWool(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
    Dim blnFail As Boolean
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm)
      If intKeyAscii <> gobFormtCtl.AscEnter Then
         intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
      Else
         intKeyAscii = 0 'Cancel Enter
         If Len(Trim$(txtID(miShGWtWool))) = gobFormtCtl.LengIDShG Then 'Proceed by mode.
            .RegistFrm Trim$(txtID(miShGWtWool)), True 'Register the form.
            If gobMsgInst.DuplFrm Then 'Avoid duplication by ivoking the LostFocus proced.
               cmdCancel.SetFocus
            Else 'Fill the ShG object & form in an Edit or Del mode.
               .DBtoFrm
               If (gobShGs(.IDFrm).TblShG.Full = False) Or (gobMsgInst.ShGDispd(Me) And .Mode = _
                  gobSetng.ModeAdd) Then 'Check the operation's feedback.
                  blnFail = True 'Mark an error to cancel below.
               ElseIf (gobMsgInst.NoWtWool(Me)) And (.Mode = gobSetng.ModeEdit Or _
                  .Mode = gobSetng.ModeDel) Then
                  blnFail = True 'There are no weighing/s & shear/s to expose.
                  MsgBox LoadResString(174) & .IDFrm & "'.", vbExclamation, _
                     LoadResString(172)
               End If
               If blnFail Then 'On an error, cancel the current changes, if any.
                  .Cancel False
                  txtID(miShGWtWool).SetFocus
               Else
                  mblnFrmFilld(gobSetng.FrmWtWoolIdx) = True 'Mark filled.
                  .SwchCtlMode 'Switch controls by mode.
               End If
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate how the controls are filled.
' There are 3 inputting options:
'  - both weighing (date & value) & shearing (date & value);
'  - only weighing (date & value);
'  - only shearing (date & value).
' Return True, if succeeds.
Private Function VldFillCtlWtWool() As Boolean
On Error GoTo ErrHnd
   With gobFormtCtl
      If Trim$(txtDate(miDateAnnl)) = "" And Trim$(txtDate(miDateShearAnnl)) = "" Then 'Check whether weighing &/or shearing are inputted.
         Call Util.MissParam(txtDate(miDateAnnl), , , LoadResString(390)) 'Message & focus.
      Else
         If Trim$(txtDate(miDateAnnl)) <> "" And .BlankNum(txtNum(miWtAnnl)) Then 'Check the weighing value.
            Call Util.MissParam(txtNum(miWtAnnl), lblNum(miWtAnnl)) 'Message & focus.
         ElseIf .BlankNum(txtNum(miWtAnnl)) = False And Trim$(txtDate(miDateAnnl)) = "" Then  'Check the weighing date.
   '         ElseIf .BlankNum(mebWtAnnl.ClipText) = False And .BlankDate(txtDateAnnl _
            .ClipText) Then 'Check the weighing date.
   Debug.Assert 0 = 1 'Verify the above line
            Call Util.MissParam(txtDate(miDateAnnl), , , LoadResString(391)) 'Message & focus.
         ElseIf Trim$(txtDate(miDateShearAnnl)) <> "" And .BlankNum(txtNum(miGreaseAnnl)) Then  'Check the shearing value.
   '         ElseIf .BlankDate(txtDateShearAnnl.ClipText) = False And .BlankNum( _
            mebGreaseAnnl.ClipText) Then 'Check the shearing value.
   Debug.Assert 0 = 1 'Verify the above line
            Call Util.MissParam(txtNum(miGreaseAnnl), lblNum(miGreaseAnnl)) 'Message & focus.
         ElseIf .BlankNum(txtNum(miGreaseAnnl)) = False And Trim$(txtDate(miDateShearAnnl)) = "" Then 'Check the shearing date.
   '         ElseIf .BlankNum(mebGreaseAnnl.ClipText) = False And .BlankDate( _
            txtDateShearAnnl.ClipText) Then 'Check the shearing date.
   Debug.Assert 0 = 1 'Verify the above line
            Call Util.MissParam(txtDate(miDateShearAnnl), , , LoadResString(392)) 'Focus &
         Else                                                               'message.
            VldFillCtlWtWool = True 'Succeeded.
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the minimal & maximal age at a firt or annual weighing & shearing.
' Return True, if succeeds.
Private Function VldMinMaxAgeWtWool() As Boolean
On Error GoTo ErrHnd
   Const intFraWtAnnl As Integer = 13 'The wt/wool frames.
   Const intFraGreaseAnnl As Integer = 14
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm)
      If Trim$(txtDate(miDateAnnl)) <> "" Then 'Validate the age at weighing.
         If Not .Lives(txtDate(miDateAnnl), fraFrame(intFraWtAnnl).Caption, strPromt:= _
            strPromt) Then 'Lives?
            blnFail = True 'Doesn't live.
         ElseIf .Age(txtDate(miDateAnnl)) < gobTblCtrlParam.Age1YrWtMin Then
            blnFail = True 'Too young.                Above: Min 1-yr wt age.
            strPromt = LoadResString(322) & mstrIDFrm & LoadResString(330) & _
               gobTblCtrlParam.Age1YrWtMin & LoadResString(231)
         End If
      End If 'Below: Age at shearing, unless failed above.
      If blnFail Then 'Message & focus.
         MsgBox strPromt, vbExclamation, LoadResString(131)
         txtDate(miDateAnnl).SetFocus
      ElseIf Trim$(txtDate(miDateShearAnnl)) <> "" Then 'Filled & not failed above?
         If Not .Lives(txtDate(miDateShearAnnl), fraFrame(intFraGreaseAnnl).Caption, _
            strPromt:=strPromt) Then 'Lives at shearing?
            blnFail = True 'Doesn't live.
         ElseIf .Age(txtDate(miDateShearAnnl)) < gobTblCtrlParam.Age1YrShearMin Then 'Min 1-yr wool age.
            blnFail = True 'Too young.
            strPromt = LoadResString(322) & mstrIDFrm & LoadResString(334) & _
               gobTblCtrlParam.Age1YrShearMin & LoadResString(231)
         End If
         If blnFail Then 'Message & focus.
            MsgBox strPromt, vbExclamation, LoadResString(131)
            txtDate(miGreaseAnnl).SetFocus
         End If
      End If
   End With
   VldMinMaxAgeWtWool = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the first weighing for 1 year-age or a next one for the annual interval in the
'  Add mode.
' Return True, if succeeds.
Private Function VldOvlpWtAdd() As Boolean
On Error GoTo ErrHnd
   Dim blnIncrAge As Boolean
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm)
      If Trim$(txtDate(miDateAnnl)) <> "" Then
         With .WtWools
            If .Act.Age = 1 Then 'Differentiate the 1st & a next weighing.
               blnFail = Not VldWtFst(blnIncrAge) 'The 1st weighing.
            ElseIf .Count > 1 Then
               blnFail = Not VldOvlpPrevWt 'A next weighing.
            End If
         End With
      End If
      If blnFail Then 'Continue to validate the shearing date or interrupt to correct the
         VldOvlpWtAdd = False 'Interrupt.                                'weighing one.
         txtDate(miDateAnnl).SetFocus
      Else
         If Trim$(txtDate(miDateShearAnnl)) <> "" Then 'Continue.
            VldOvlpWtAdd = VldOvlpWoolAdd(blnIncrAge) 'Validate the shearing date.
         Else
            If blnIncrAge Then 'Check to increase the age.
               With .WtWools.Act
                  .Age = .Age + 1
               End With
            End If
            VldOvlpWtAdd = True 'Succeeded.
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the 1st shearing for 1 year-age or a next one for the annual interval in the
'  Add mode.
' Return True, if succeeds.
Private Function VldOvlpWoolAdd(ByVal blnIncrAge As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   With gobShGs(mstrIDFrm).WtWools
      If .Act.Age = 1 Then 'Differentiate the 1st & a next shearing.
         blnFail = Not VldWoolFst(blnIncrAge) 'The 1st shearing.
      ElseIf .Count > 1 Then
         blnFail = Not VldOvlpPrevWool
      End If
      If blnFail Then 'Correct an error or pass the validation.
         VldOvlpWoolAdd = False 'Correct.
         txtDate(miDateShearAnnl).SetFocus
      Else
         If blnIncrAge Then 'Check to increase the age.
            With .Act
               .Age = .Age + 1
            End With
         End If
         VldOvlpWoolAdd = True 'Succeeded.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise the forms' ID controls & number text boxes.
' If the blnClearPrev argument is True clear the previous value, otherwise unless the
'  textbox is blank keep the previous value.
Private Sub InitTxtWtWool(ByVal blnClearPrev As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl 'Simulate date masks.
      If blnClearPrev Then
         txtNum(miWtAnnl) = .NumFrac(0)
         txtNum(miGreaseAnnl) = .NumFrac(0)
      Else
         If txtNum(miWtAnnl) = "" Then txtNum(miWtAnnl) = .NumFrac(0)
         If txtNum(miGreaseAnnl) = "" Then txtNum(miGreaseAnnl) = .NumFrac(0)
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the referred-to frmWtWool form from the specified obTblWtWool object.
' Prior to filling, clear & reinitialise the controls to drop the previous contents, if
'  any.
Private Sub CtlWriteWtWool(ByVal obTblWtWool As TblWtWool)
On Error GoTo ErrHnd
   Call DatFrm_CtlClear 'Clear & reinitialise the controls.
   Call InitTxt(True)
   With obTblWtWool 'Fill.
      If .DateAnnl > 0 Then
         gobFormtCtl.WriteDate txtDate(miDateAnnl), dtpDate(miDateAnnl), .DateAnnl
         txtNum(miWtAnnl) = gobFormtCtl.NumFrac(.WtAnnl)
      End If
      If .DateShearAnnl > 0 Then
         gobFormtCtl.WriteDate txtDate(miDateShearAnnl), dtpDate(miDateShearAnnl), _
            .DateShearAnnl
         txtNum(miGreaseAnnl) = gobFormtCtl.NumFrac(.GreaseAnnl)
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the Mate data form from the specified obTblMat object.
' Prior to filling, clear & reinitialise the controls to drop the previous contents, if
'  any.
Private Sub CtlWriteMat(ByVal obTblMat As TblMat)
On Error GoTo ErrHnd
   With obTblMat 'Fill.
      txtID(miSireMat) = .IDSire
      gobFormtCtl.WriteDate txtDate(miDateMat), dtpDate(miDateMat), .DateMat
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the 1st weighing for the 1 year-age.
' Return True, if succeeds.
Private Function VldWtFst(ByRef blnIncrAge As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   Dim intResp As Integer
   With gobTblCtrlParam
      If gobShGs(mstrIDFrm).Age(txtDate(miDateAnnl)) > .Age1YrWtMax Then
         If .Age1YrChk Then 'Proceed, if the 1st-weighing check is required
            intResp = MsgBox(LoadResString(331) & mstrIDFrm & LoadResString(340) & _
               .Age1YrWtMax & LoadResString(341), vbYesNo + vbQuestion, _
               LoadResString(342)) 'Promt to correct.
            If intResp = vbYes Then
               blnFail = True
            Else
               blnIncrAge = True 'Increase the age count.
            End If
         Else
            blnIncrAge = True 'Increase the age count.
         End If
      End If
   End With
   VldWtFst = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the annual interval between the active weighing & the previous one.
' If the previous weighing is Null use the adjacent shearing instead.
' Return True, if succeeds.
Private Function VldOvlpPrevWt() As Boolean
On Error GoTo ErrHnd
   Dim dtmDatePrev As Date
   Dim blnFail As Boolean
   Dim strAffx As String
   Dim intResp As Integer
   With gobShGs(mstrIDFrm).WtWools
      dtmDatePrev = .Prev(True).DateAnnl 'The previous wt date.
      If dtmDatePrev = 0 Then 'Check if there's wt.
Debug.Assert 0 = 1 'Verify w/o IDShG
         dtmDatePrev = .Prev(True).DateShearAnnl 'No wt - use the shearing
'         dtmDatePrev = .Prev(mstrIDFrm, True).DateShearAnnl 'No wt - use the shearing
         strAffx = LoadResString(349) 'Wool promt affix.       'date instead.
      Else
         strAffx = LoadResString(343) 'Wt promt affix.
      End If
   End With
   With gobTblCtrlParam
      If CDate(txtDate(miDateAnnl)) - dtmDatePrev < .InterAnnlMin Then
         blnFail = True 'The interval is smaller than allowed.
         MsgBox strAffx & dtmDatePrev & LoadResString(344) & txtDate(miDateAnnl) & _
            LoadResString(345) & .InterAnnlMin & LoadResString(231), vbExclamation, _
            LoadResString(131)
      ElseIf CDate(txtDate(miDateAnnl)) - dtmDatePrev > .InterAnnlMax Then
         intResp = MsgBox(strAffx & dtmDatePrev & LoadResString(344) & txtDate( _
            miDateAnnl) & LoadResString(346) & .InterAnnlMax & LoadResString(590), _
            vbYesNo + vbQuestion, LoadResString(342)) 'Too big interval.
         If intResp = vbYes Then blnFail = True
      End If
   End With
   If blnFail Then
      txtDate(miDateAnnl).SetFocus
   Else
      VldOvlpPrevWt = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the 1st shearing for 1 year-age.
' Return True, if succeeds.
Private Function VldWoolFst(ByRef blnIncrAge As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   Dim intResp As Integer
   With gobTblCtrlParam
      If CDate(txtDate(miDateShearAnnl)) - gobShGs(mstrIDFrm).TblShG.DateBirth > _
         .Age1YrShearMax Then
         If blnIncrAge = False And .Age1YrChk Then 'The sheep/goat is too old.
Debug.Assert 0 = 1 'Verify the promt
            intResp = MsgBox(LoadResString(331) & mstrIDFrm & LoadResString(347) & _
               .Age1YrShearMax & LoadResString(341), vbYesNo + vbQuestion, _
               LoadResString(348))
            If intResp = vbYes Then
               blnFail = True
            Else
               blnIncrAge = True 'Increase the age count.
            End If
         Else
            blnIncrAge = True 'Increase the age count.
         End If
      End If
   End With
   VldWoolFst = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the annual interval between the active shearing & the previous one.
' If the previous shearing is Null use the adjacent weighing instead.
' Return True, if succeeds.
Private Function VldOvlpPrevWool() As Boolean
On Error GoTo ErrHnd
   Dim dtmPrevDate As Date
   Dim blnFail As Boolean
   Dim strAffx As String
   Dim intResp As Integer
   With gobShGs(mstrIDFrm).WtWools
      dtmPrevDate = .Prev(True).DateShearAnnl 'The previous shearing date.
      If dtmPrevDate = 0 Then 'Check if there's shearing.
         dtmPrevDate = .Prev(True).DateAnnl 'No shearing - use the wt date.
         strAffx = LoadResString(343) 'Wt promt affix.
      Else
         strAffx = LoadResString(349) 'Normal promt affix.
      End If
   End With
   With gobTblCtrlParam
      If CDate(txtDate(miDateShearAnnl)) - dtmPrevDate < .InterAnnlMin Then
         blnFail = True 'The interval is smaller than allowed.
         MsgBox strAffx & dtmPrevDate & LoadResString(350) & txtDate(miDateShearAnnl) & _
            LoadResString(345) & .InterAnnlMin & LoadResString(234), vbExclamation, _
            LoadResString(131)  'Below: 'Too big interval.
      ElseIf CDate(txtDate(miDateShearAnnl)) - dtmPrevDate > .InterAnnlMax Then
         intResp = MsgBox(strAffx & dtmPrevDate & LoadResString(350) & txtDate( _
            miDateShearAnnl) & LoadResString(346) & .InterAnnlMax & LoadResString(590), _
            vbYesNo + vbQuestion, LoadResString(348))
         If intResp = vbYes Then blnFail = True
      End If
   End With
   If blnFail Then
      txtDate(miDateShearAnnl).SetFocus
   Else
      VldOvlpPrevWool = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a defect to the lvwList(miLvwInhertDefct) control & to the InhertDefcts collection.
' Mark the new defect added, unless it's being edited or has been deleted. If it has been
'  deleted restore it by setting off the deleted mark.
' Update the edited defect, if it's being edited, by reseting it.
' Enable the cmdEdit, cmdDel, & cmdOk buttons, if disabled.
' Set focus to the mebDateTrans control.
Private Sub ClickAddAppr()
On Error GoTo ErrHnd
   Dim strErr As String
   Dim strIDShG As String
   Dim strKey As String
   Dim lngIDDefctOrigPrev As Long
   Dim lngIDDefctPrev As Long
   Dim blnAddedPrev As Boolean
   Dim blnEditedPrev As Boolean
   If VldDefct(dbcFld(miDefct)) Then 'Validate the defect.
      strIDShG = mobDatFrm.IDFrm
      With dbcFld(miDefct) 'Add to lvwList(miLvwInhertDefct).
         strKey = strIDShG & .BoundText
         lvwList(miLvwInhertDefct).ListItems.Add , strKey, .Text
      End With
      With gobShGs(strIDShG).Apprs.Act.InhertDefcts
         If .Edited Then 'Add or update.
            .Edited = False 'Updtate.
Debug.Assert 0 = 1 'Check IDShG within .Act.
            With .Act 'Remember the previous.
Debug.Assert 0 = 1 'Verify lngIDDefct* As Long
               lngIDDefctOrigPrev = .IDDefctOrig
               lngIDDefctPrev = .IDDefct
               blnAddedPrev = .Added
               blnEditedPrev = .Edited
            End With
 Debug.Assert 0 = 1 'Check IDShG within .Del.
            .Del lngIDDefctPrev 'Delete it.
'            .Del strIDShG, strIDDefctPrev 'Delete it.
Debug.Assert 0 = 1 'Check IDShG within .Add.
Debug.Assert 0 = 1 'Verify lngIDDefct* As Long
            .Add lngIDDefctOrigPrev, dbcFld(miDefct).BoundText, dbcFld(miDefct).Text 'Add a new one
'            .Add strIDShG, strIDDefctOrigPrev, dbcDefct.BoundText, dbcDefct.Text 'Add
 Debug.Assert 0 = 1 'Check IDShG within .Act.
            With .Act                            'with the previous parameters.
'            With .Act(strIDShG)                            'with the previous parameters.
               .Added = blnAddedPrev
               .Edited = blnEditedPrev
            End With
         Else
            If Not .Exists(dbcFld(miDefct).BoundText) Then 'Add a new defect.
               .Add dbcFld(miDefct).BoundText, dbcFld(miDefct).BoundText, dbcFld(miDefct).Text 'Add to
               .Act.Added = True                    'InhertDefcts & mark added.
            ElseIf .Item(dbcFld(miDefct).BoundText, False).Deld Then 'Restore, if deleted
               .Act.Deld = False
            End If
         End If
      End With
Continue:
      With dbcFld(miDefct) 'Clear dbcFld(miDefct) & focus it.
         .BoundText = ""
         .SetFocus
      End With
      Call SwchBtnAppr(True) 'Enable the buttons.
  End If
Exit Sub
ErrHnd:
   strErr = Err.Description
   If Err.Number = 35602 Then
      MsgBox LoadResString(74), vbExclamation, LoadResString(50) 'Duplicate defect.
   Else
      MsgBox strErr 'Some other error.
   End If
   Resume Continue
End Sub

' Delete the selected defect from lvwList(miLvwInhertDefct).
' Prior to the deletion, make sure there are defects in lvwList(miLvwInhertDefct) to
'  delete.
' Mark the deleted defect as deleted in the obTblInhertDefct object to delete if later or
'  delete it immediately from the InhertDefcts collection, if it has been added just at
'  this session.
' Enable the cmdOk button, if disabled.
Private Sub ClickDelAppr()
On Error GoTo ErrHnd
   Dim strIDShG As String
   Dim lngIDDefct As Long
   If lvwList(miLvwInhertDefct).ListItems.Count > 0 Then
      strIDShG = mobDatFrm.IDFrm 'Define the shee/goat.
      lngIDDefct = Mid$(lvwList(miLvwInhertDefct).SelectedItem.Key, gobFormtCtl.LengIDShG + 1) 'Define the deleted defect's ID.
      With gobShGs(strIDShG).Apprs.Act.InhertDefcts 'Mark the defect deleted or delete
         If .Item(lngIDDefct, False).Added Then           'it from InhertDefcts.
            .Del lngIDDefct
         Else
            With .Item(lngIDDefct, False) 'Mark Deld & set off Edited.
               .Deld = True
               .Edited = False
            End With
         End If
      End With
      With lvwList(miLvwInhertDefct) 'Delete from lvwList(miLvwInhertDefct).
         .ListItems.Remove (.SelectedItem.Key)
         If .ListItems.Count > 0 Then .SelectedItem.Selected = True 'Mark out the
      End With                                    'remaining selected row, if any.
      If cmdOk.Enabled = False Then cmdOk.Enabled = True 'Enable cmdOk.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtID(miShGAppr).
Private Sub ClickOkAppr()
On Error GoTo ErrHnd
   Dim intResp As Integer
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit
         If .Vld Then 'Validate data in an Add or Edit mode.
            .FrmToDB
            .Cancel False
            txtID(miShGAppr).SetFocus
         End If
      Case gobSetng.ModeDel
         Beep
         intResp = MsgBox(LoadResString(302), vbYesNoCancel + vbQuestion, _
            LoadResString(372))
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            .FrmToDB
            .Cancel True
            Call InitTxt(True) 'Initialise text boxes.
            txtID(miShGAppr).SetFocus
         Case vbNo
            cmdOk.SetFocus
         Case vbCancel
            .Cancel True
            txtID(miShGAppr).SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the appraisal's data except defects inputted before.
Private Sub CtlReadAppr()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm).Apprs.Act
      .DateAppr = Trim$(txtDate(miDateAppr))
      .Leng = Trim$(txtNum(miLeng))
      .Diam = dbcFld(miDiam)
      .Mass = dbcFld(miMass)
      .Crimpins = dbcFld(miCrimpins)
      .Evens = dbcFld(miEvens)
      .Density = Trim$(txtNum(miDensity))
      .Strength = dbcFld(miStrength)
      .IDColour = Util.DbcReadBoundTxt(dbcFld(miColour), adoFld(miColour))
      .Quality = dbcFld(miQuality)
      .IDFluffColour = Util.DbcReadBoundTxt(dbcFld(miFluffColour), adoFld(miFluffColour))
      .Fluff = Trim$(txtNum(miFluff))
      .FibreYield = Trim$(txtNum(miFibreYield))
      .BodyType = dbcFld(miBodyType)
      .Constitutn = dbcFld(miConstitutn)
      .BodySize = dbcFld(miBodySize)
      .FatTail = dbcFld(miFatTail)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the DB to the ShG object object associated with the data form.
' In an Edit of Del mode, fill out this form with the data from the ShG object.
Private Sub DBtoFrmAppr()
On Error GoTo ErrHnd
   With gobShGs(mstrIDFrm)
      If Not .PopltAppr Then .SelAppr True 'Prepare the data.
      If .TblShG.Full Then 'Check if the sheep/goat exists.
         Select Case mintMode(gobSetng.FrmApprIdx)
         Case gobSetng.ModeAdd 'Open a new appriasal to add.
            .Apprs.AgeNewOpen
            If Not gobMsgInst.NoAppr(Me) Then Call BrsAppr(mstrIDFrm) 'Fill the Appr grid
         Case gobSetng.ModeEdit, gobSetng.ModeDel 'Fill out the form to edit or delete.
            If Not gobMsgInst.NoAppr(Me) Then 'Check whether there are appraisals.
               Call DatFrm_CtlClear 'Clear & reinitialise the controls.
               Call InitTxt(True)
               Call CtlWriteAppr(.Apprs.Last(False))
               Call BrsAppr(mstrIDFrm) 'Fill the Appr grid.
            End If
         End Select
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the ShG object associated with the data form to put
'  it into the DB.
' First insert/update the Appraisal table.
' Roll back operations on SQL server's error, if any.
' Then insert/update the defect/s in the InhertDefect table.
Private Sub FrmToDBAppr()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   gcnnConn.BeginTrans 'Begin transaction.
   With gobShGs(mstrIDFrm)
      Set obDatTbl = .Apprs.Act
      If mintMode(gobSetng.FrmApprIdx) = gobSetng.ModeDel Then
         obDatTbl.Del 'Deletion.
         If Not gobMsgInst.SQLErr(Me) Then .TblSelIdxCC.DelWtAppr gobSetng.FrmApprIdx 'Delete
      Else                                              'selection index & complex class.
         DatFrm_CtlRead 'Read the controls.
         Select Case mintMode(gobSetng.FrmApprIdx) 'Accomplish the mode's opertation.
         Case gobSetng.ModeAdd
            obDatTbl.Ins
         Case gobSetng.ModeEdit
            obDatTbl.Upd
         End Select
         .TblSelIdxCC.GetRefrsh gobSetng.FrmApprIdx 'Calculate the selection index & complex class.
      End If
   End With
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Resume to close gcnnConn's transaction.
End Sub

' Shwitch on/off the data form's controls depending on whether the txtID(miShGAppr) is filled.
Private Sub SwchCtlFillAppr(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Call SwchID(miShGAppr, miShGAppr, True, Not blnEnable)
   Call SwchCtlFillDate(miDateAppr, miDateAppr, blnEnable)
   Call SwchCtlObj(lblNum, miLeng, miFibreYield, blnEnable)
   Call SwchCtlObj(txtNum, miLeng, miFibreYield, blnEnable)
   Call SwchCtlObj(lblFld, miDiam, miFatTail, blnEnable)
   Call SwchCtlObj(dbcFld, miDiam, miDefct, blnEnable)
   Call SwchCtlObj(lblMisc, miDiamFromLbl, miDiamToLbl, blnEnable)
   If Not blnEnable Then lvwList(miLvwInhertDefct).ListItems.Clear 'Clear lvwList(miLvwInhertDefct), if the rest controls are switched off.
   Call Util.SwchListView(lvwList(miLvwInhertDefct), blnEnable) 'Switch the list view preventing mixed colours.
   Call SwchBtnLvw(miLvwInhertDefct, blnEnable)
   Call SwchCtlLbl(lblGrid(miFlexAppr), flexGrid(miFlexAppr), blnEnable)
   Call SwchFluff 'Switch the Fluff controls.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
Private Sub SwchCtlModeAppr()
On Error GoTo ErrHnd
   Select Case mintMode(gobSetng.FrmApprIdx)
   Case gobSetng.ModeAdd, gobSetng.ModeEdit
      Call DatFrm_SwchCtlFill(True)
      txtDate(miDateAppr).SetFocus
   Case gobSetng.ModeDel
      txtID(miShGAppr).Enabled = False
      cmdID(miShGAppr).Enabled = False
      Call SwchCtlLbl(lblGrid(miFlexAppr), flexGrid(miFlexAppr), True)
      cmdOk.Enabled = True
      cmdOk.SetFocus
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function VldAppr() As Boolean
On Error GoTo ErrHnd
   If VldFillCtlAppr Then 'Validate how the controls are filled.
      If VldMinMaxAgeAppr() Then 'Validate the dates according to the minimal & maximal ages.
         Select Case mobDatFrm.Mode 'Validate overlapping appr's intervals by mode.
         Case gobSetng.ModeAdd
            VldAppr = VldOvlpApprAdd
         Case gobSetng.ModeEdit
            VldAppr = VldOvlpApprEdit
         End Select
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise the form's controls.
Private Sub InitCtlAppr()
On Error GoTo ErrHnd
   Dim colIDDefct As ColumnHeader
   Set colIDDefct = lvwList(miLvwInhertDefct).ColumnHeaders.Add()
   colIDDefct.Width = lvwList(miLvwInhertDefct).Width
   colIDDefct.Text = LoadResString(260)
   Call AdoCnnStr(miDiam, miDefct) ' Set the the Ados' ConnectionString.
   Call Util.DbcSetRowSrc(dbcFld(miDiam), adoFld(miDiam), "Diam", "Diam")
   Set lblMisc(miDiamFromLbl).DataSource = adoFld(miDiam)
   lblMisc(miDiamFromLbl).DataField = "DiamFrom"
   Set lblMisc(miDiamToLbl).DataSource = adoFld(miDiam)
   lblMisc(miDiamToLbl).DataField = "DiamTo"
   Call RefrshDiam(True) 'Clear lblMisc(miDiamFromLbl) & lblMisc(miDiamToLbl) until filled.
   Call Util.DbcSetRowSrc(dbcFld(miMass), adoFld(miMass), "Mass", "Mass") 'dbcFld(miMass).
   Call Util.DbcSetRowSrc(dbcFld(miCrimpins), adoFld(miCrimpins), "Crimpins", "Crimpins") 'dbcFld(miCrimpins)
   Call Util.DbcSetRowSrc(dbcFld(miEvens), adoFld(miEvens), "Evens", "Evens") 'dbcFld(miEvens)
   Call Util.DbcSetRowSrc(dbcFld(miStrength), adoFld(miStrength), "Strength", "Strength")
   Call Util.DbcSetRowSrc(dbcFld(miColour), adoFld(miColour), "IDColour", "Colour")
   Call Util.DbcSetRowSrc(dbcFld(miQuality), adoFld(miQuality), "Quality", "Quality")
   Call Util.DbcSetRowSrc(dbcFld(miFluffColour), adoFld(miFluffColour), "IDFluffColour", _
      "FluffColour")
   Call Util.DbcSetRowSrc(dbcFld(miBodyType), adoFld(miBodyType), "BodyType", "BodyType")
   Call Util.DbcSetRowSrc(dbcFld(miConstitutn), adoFld(miConstitutn), "Constitutn", _
      "Constitutn")
   Call Util.DbcSetRowSrc(dbcFld(miBodySize), adoFld(miBodySize), "BodySize", "BodySize")
   Call Util.DbcSetRowSrc(dbcFld(miFatTail), adoFld(miFatTail), "FatTail", "FatTail")
   Call Util.DbcSetRowSrc(dbcFld(miDefct), adoFld(miDefct), "IDDefect", "Defect")
   Call BrsAppr("") 'Initialise the Appr grid.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Fill the form & begin the mode's operation.
Private Sub IDCtlPressAppr(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm)
      If intKeyAscii <> gobFormtCtl.AscEnter Then
         intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
      Else
         intKeyAscii = 0 'Cancel Enter
         If Len(Trim$(txtID(miShGAppr))) = gobFormtCtl.LengIDShG Then 'Process the command corresponding to
            .RegistFrm Trim$(txtID(miShGAppr)), True     'the mode. Register the form.
            If gobMsgInst.DuplFrm Then 'Avoid duplication by ivoking the LostFocus proced.
               cmdCancel.SetFocus
            Else 'Fill the ShG object & form in an Edit or Del mode.
               .DBtoFrm
               If (gobShGs(.IDFrm).TblShG.Full = False) Or (gobMsgInst.ShGDispd(Me) And _
                  .Mode = gobSetng.ModeAdd) Then 'Check the operation's feedback.
                  blnFail = True 'Mark an error to cancel below.
               ElseIf (gobMsgInst.NoAppr(Me)) And (.Mode = gobSetng.ModeEdit Or .Mode = _
                  gobSetng.ModeDel) Then
                  blnFail = True 'There are no appriasal/s to expose.
                  MsgBox LoadResString(322) & .IDFrm & LoadResString(182), _
                     vbExclamation, LoadResString(172)
               End If
               If blnFail Then 'On an error, cancel the current changes, if any.
                  .Cancel False
                  txtID(miShGAppr).SetFocus
               Else
                  .SwchCtlMode 'Switch controls by mode.
                  mblnFrmFilld(gobSetng.FrmApprIdx) = True 'Mark filled.
               End If
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Check whether a defect has been selected.
' Return True, if succeeds.
Private Function VldDefct(ByVal dbcDefct As DataCombo) As Boolean
On Error GoTo ErrHnd
    ' Validate presence.
    If dbcDefct.BoundText = "" Then
        VldDefct = False
'        MsgBox "Выберите дефект.", vbExclamation, "Ошибка"
         MsgBox LoadResString(261), vbExclamation, LoadResString(131)
        dbcDefct.SetFocus
    Else
        ' The validaton passed.
        VldDefct = True
    End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Move the defect from lvwList(miLvwInhertDefct) & put it to the dbcFld(miDefct)
'   comboboxe to edit.
' Set the focus to dbcFld(miDefct).
Private Sub DefctMove()
On Error GoTo ErrHnd
   dbcFld(miDefct).Text = "" 'Clear dbcFld(miDefct).
   With lvwList(miLvwInhertDefct) 'Move to dbcFld(miDefct).
      dbcFld(miDefct).Text = .SelectedItem.Text
      dbcFld(miDefct).SetFocus 'Set focus.
      .ListItems.Remove (.SelectedItem.Index) 'Delete from lvwList(miLvwInhertDefct).
      If .ListItems.Count > 0 Then .SelectedItem.Selected = True 'Mark the remaining selected row, if any.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable or disable cmdEdit, cmdDel, & cmdOk buttons.
Private Sub SwchBtnAppr(ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
    cmdDel(miLvwInhertDefct).Enabled = blnEnable
    cmdOk.Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the forms' ID controls & number text boxes.
' If the blnClearPrev argument is True clear the previous value, otherwise unless the
'  textbox is blank keep the previous value.
Private Sub InitTxtAppr(ByVal blnClearPrev As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl
      If blnClearPrev Then
         txtNum(miLeng) = .NumFrac(0)
         txtNum(miDensity) = .NumFrac(0, True)
         txtNum(miFluff) = .NumFrac(0, True)
         txtNum(miFibreYield) = .NumFrac(0, True)
      Else
         If txtNum(miLeng) = "" Then txtNum(miLeng) = .NumFrac(0)
         If txtNum(miDensity) = "" Then txtNum(miDensity) = .NumFrac(0, True)
         If txtNum(miFluff) = "" Then txtNum(miFluff) = .NumFrac(0, True)
         If txtNum(miFibreYield) = "" Then txtNum(miFibreYield) = .NumFrac(0, True)
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the controls from the specified obTblAppr object.
Private Sub CtlWriteAppr(ByVal obTblAppr As TblAppr)
On Error GoTo ErrHnd
   Dim obTblInhertDefct As TblInhertDefct
   Dim strKey As String
   With obTblAppr
      txtID(miShGAppr) = .IDShG 'This is necessary to fill from the frmBrsAppr form.
      gobFormtCtl.WriteDate txtDate(miDateAppr), dtpDate(miDateAppr), .DateAppr
'      txtDate(miDateAppr) = .DateAppr
      txtNum(miLeng) = gobFormtCtl.NumFrac(.Leng)
      dbcFld(miDiam) = .Diam
      Call RefrshDiam(True) 'Refresh the lblMisc(miDiamFromLbl) & lblMisc(miDiamToLbl) controls
      dbcFld(miMass) = .Mass
      dbcFld(miCrimpins) = .Crimpins
      dbcFld(miEvens) = .Evens
      txtNum(miDensity) = gobFormtCtl.NumFrac(.Density, True)
      dbcFld(miStrength) = .Strength
      dbcFld(miColour).BoundText = .IDColour
      dbcFld(miQuality) = .Quality
      dbcFld(miFluffColour).BoundText = .IDFluffColour
      txtNum(miFluff) = gobFormtCtl.NumFrac(.Fluff, True)
      txtNum(miFibreYield) = gobFormtCtl.NumFrac(.FibreYield, True)
      dbcFld(miBodyType) = .BodyType
      dbcFld(miConstitutn) = .Constitutn
      dbcFld(miBodySize) = .BodySize
      dbcFld(miFatTail) = .FatTail
   End With
   For Each obTblInhertDefct In obTblAppr.InhertDefcts 'Fill lvwList(miLvwInhertDefct).
      With obTblInhertDefct
         strKey = .IDShG & CStr(.IDDefct)
         lvwList(miLvwInhertDefct).ListItems.Add , strKey, .Defct
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate whether the controls are filled: the date of appraisal & at least a single
'  triat/defect.
' Return True, if succeeeds.
Private Function VldFillCtlAppr() As Boolean
On Error GoTo ErrHnd
   With gobFormtCtl
      If Trim$(txtDate(miDateAppr)) = "" Then 'Define the appraisal date.
         Call Util.MissParam(txtDate(miDateAppr), lblDate(miDateAppr)) 'Message & focus.
      ElseIf Not .BlankNum(txtNum(miLeng)) Then 'Find a single filled controls.
         VldFillCtlAppr = True
      ElseIf dbcFld(miDiam).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miMass).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miCrimpins).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miEvens).BoundText <> "" Then
         VldFillCtlAppr = True
'      ElseIf Not Trim$(txtDensity) = "" Then
      ElseIf Not .BlankNum(txtNum(miDensity)) Then
Debug.Assert 0 = 1 'Verify the above line
         VldFillCtlAppr = True
      ElseIf dbcFld(miStrength).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miColour).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miQuality).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miFluffColour).BoundText <> "" Then
         VldFillCtlAppr = True
'      ElseIf Trim$(txtFluff) <> "" Then
      ElseIf Not .BlankNum(txtNum(miFluff)) Then
Debug.Assert 0 = 1 'Verify the above line
         VldFillCtlAppr = True
'      ElseIf Trim$(txtFibreYield) <> "" Then
      ElseIf Not .BlankNum(txtNum(miFibreYield)) Then
Debug.Assert 0 = 1 'Verify the above line
         VldFillCtlAppr = True
      ElseIf dbcFld(miBodyType).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miConstitutn).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miBodySize).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf dbcFld(miFatTail).BoundText <> "" Then
         VldFillCtlAppr = True
      ElseIf lvwList(miLvwInhertDefct).ListItems.Count <> 0 Then
         VldFillCtlAppr = True
      Else
         Call Util.MissParam(txtNum(miLeng), , , LoadResString(324)) 'Message & focus.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the minimal & maximal age at the 1-year/annual appraisal.
' Return True, if succeeds.
Private Function VldMinMaxAgeAppr() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm)
      If Not .Lives(txtDate(miDateAppr), fraFrame(gobSetng.FrmApprIdx).Caption, _
         strPromt:=strPromt) Then 'Lives?
         blnFail = True 'Doesn't live.
      ElseIf .Age(txtDate(miDateAppr)) < gobTblCtrlParam.Age1YrShearMin Then  'The mimimal age at 1-year.
         blnFail = True
         strPromt = LoadResString(322) & mstrIDFrm & LoadResString(360) & _
            gobTblCtrlParam.Age1YrShearMin & LoadResString(231)
      Else
         VldMinMaxAgeAppr = True 'Succeeded.
      End If
   End With
   If blnFail Then 'Message & focus.
      MsgBox strPromt, vbExclamation, LoadResString(131)
      txtDate(miDateAppr).SetFocus
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the 1st appriasal for 1 year-age or a next one for the annual interval in the
'  Add mode.
' Return True, if succeeds.
Private Function VldOvlpApprAdd() As Boolean
On Error GoTo ErrHnd
   Dim intAgeAct As Integer
   Dim dtmDateApprPrev As Date
   Dim intResp As Integer
   Dim blnIncrAge As Boolean
   Dim blnErr As Boolean
   With gobShGs(mstrIDFrm)
      If .Apprs.Act.Age = 1 Then 'Differentiate 1st/next appriasal.
         If .Age(txtDate(miDateAppr)) > gobTblCtrlParam.Age1YrWtMax Then
            If gobTblCtrlParam.Age1YrChk Then 'The 1st appriasal.
                intResp = MsgBox(LoadResString(331) & mstrIDFrm & LoadResString(361) _
                  & gobTblCtrlParam.Age1YrWtMax & LoadResString(341), vbYesNo + _
                  vbQuestion, LoadResString(362)) 'Promt to correct.
               If intResp = vbYes Then
                  blnErr = True
               Else
                  blnIncrAge = True 'Increase the age count.
               End If
            Else
               blnIncrAge = True 'Increase the age count.
            End If
         End If
      ElseIf .Apprs.Count > 1 Then
         intAgeAct = .Apprs.Act.Age 'Increase the age count.
         dtmDateApprPrev = .Apprs.Prev(False).DateAppr
         .Apprs.Item intAgeAct, False
         If CDate(txtDate(miDateAppr)) - dtmDateApprPrev < gobTblCtrlParam.InterAnnlMin _
            Then
            blnErr = True 'The interval is smaller than allowed.
             MsgBox LoadResString(363) & dtmDateApprPrev & LoadResString(364) & _
               txtDate(miDateAppr) & LoadResString(345) & gobTblCtrlParam.InterAnnlMin _
               & LoadResString(231), vbExclamation, LoadResString(131)
         ElseIf CDate(txtDate(miDateAppr)) - dtmDateApprPrev > gobTblCtrlParam _
            .InterAnnlMax Then
             intResp = MsgBox(LoadResString(363) & dtmDateApprPrev & LoadResString(364) _
               & txtDate(miDateAppr) & LoadResString(346) & gobTblCtrlParam.InterAnnlMax _
               & LoadResString(590), vbYesNo + vbQuestion, LoadResString(362))  'The interval is smaller than allowed.
            If intResp = vbYes Then blnErr = True
         End If
      End If
      If blnErr Then 'Continue or interrupt to correct the appriasal date.
         txtDate(miDateAppr).SetFocus 'Interrupt.
      Else 'Continue.
         If blnIncrAge Then 'Check to increase the age.
            With .Apprs.Act
               .Age = .Age + 1
            End With
         End If
         VldOvlpApprAdd = True 'Succeeded.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Disable & clear the Fluff controls for a sheep.
Private Sub SwchFluff()
On Error GoTo ErrHnd
   Dim obTblBrd As TblBrd
   Dim obDatTbl As DatTbl
   If mstrIDFrm <> "" Then 'For filled data form only.
      If gobShGs(mstrIDFrm).TblShG.Full Then 'For ShG with data only.
         Set obTblBrd = New TblBrd 'Get the animal's species.
         Set obDatTbl = obTblBrd
         obDatTbl.Sel gobShGs(mstrIDFrm).TblShG.IDBrdBas
         If obTblBrd.IDSpcs = gobSetng.IDSpcsSh Then 'Proceed for a sheep.
            lblFld(miFluffColour).Enabled = False 'Disable.
            dbcFld(miFluffColour).Enabled = False
            lblNum(miFluff).Enabled = False
            txtNum(miFluff) = gobFormtCtl.NumFrac(0, True)
            txtNum(miFluff).Enabled = False
            lblNum(miFibreYield).Enabled = False
            txtNum(miFibreYield) = gobFormtCtl.NumFrac(0, True)
            txtNum(miFibreYield).Enabled = False
            dbcFld(miFluffColour) = "" 'Clear.
         End If
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the lblMisc(miDiamFromLbl) & lblMisc(miDiamToLbl) controls by finding the selected diameter in the
'  adoFld(miDiam) recordset.
Private Sub RefrshDiam(Optional ByVal blnIgnorePrev As Boolean)
On Error GoTo ErrHnd
   Static strDiamPrev As String
   Call Util.RefrshDiamFrm(adoFld(miDiam), dbcFld(miDiam), strDiamPrev, blnIgnorePrev)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the data sorce for the specified Ado's.
Private Sub AdoCnnStr(ByVal intFst As Integer, ByVal intLst As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   With gcnnConn
      For I = intFst To intLst
         adoFld(I).ConnectionString = .ConnectionString
      Next
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide/unhide the specified frame to prevent confusing coinciding lable shortcuts in
'  different frames.
' Switch on/off the specified tab's controls' TabStop's.
Private Sub SwchVisibleTabStop(ByVal intIdx As Integer, ByVal blnVisibleTabStop _
   As Boolean)
On Error GoTo ErrHnd
   fraFrame(intIdx).Visible = blnVisibleTabStop 'Hide/uhide the frame.
   With gobSetng 'Switch TabStop's.
      Select Case intIdx 'Select the active tab.
      Case .FrmInvenIdx
         txtID(miShGInven).TabStop = blnVisibleTabStop
         cmdID(miShGInven).TabStop = blnVisibleTabStop
         Call Util.SwchTabStopCtl(txtID, miSireInven, miDamInven, blnVisibleTabStop)
         Call Util.SwchTabStopCtl(dbcFld, miFarm, miBrdPure, blnVisibleTabStop)
         Call Util.SwchTabStopCtl(txtDate, miDateBirth, miDateTestSire, blnVisibleTabStop)
         Call Util.SwchTabStopCtl(txtMisc, miRemark, miRemark, blnVisibleTabStop)
         chkFld(miTestSireChk).TabStop = blnVisibleTabStop
         Call Util.SwchTabStopCtl(cmdDlg, miBrdCrsCmd, miTransFarmCmd, blnVisibleTabStop)
      Case .FrmMatIdx
         txtID(miDamMat).TabStop = blnVisibleTabStop
         cmdID(miDamMat).TabStop = blnVisibleTabStop
         txtID(miSireMat).TabStop = blnVisibleTabStop
         txtDate(miDateMat).TabStop = blnVisibleTabStop
         flexGrid(miFlexMat).TabStop = blnVisibleTabStop
      Case .FrmLmKIdx
         txtID(miDamLmK).TabStop = blnVisibleTabStop
         cmdID(miDamLmK).TabStop = blnVisibleTabStop
         txtID(miLmKLmK).TabStop = blnVisibleTabStop
         txtDate(miDateLmK).TabStop = blnVisibleTabStop
         chkFld(miAbortChk).TabStop = blnVisibleTabStop
         Call Util.SwchTabStopCtl(dbcFld, miSexLmK, miLiv, blnVisibleTabStop)
         txtNum(miWtBirth).TabStop = blnVisibleTabStop
         Call SwchTabStopLvw(miLvwOffsp, blnVisibleTabStop) 'Switch the list view & its buttons.
         Call Util.SwchTabStopCtl(optFld, miOptLmKAliv, miOptLmKDead, blnVisibleTabStop)
         flexGrid(miFlexLmK).TabStop = blnVisibleTabStop
      Case .FrmWtLmKIdx
         txtID(miLmKWtLmK).TabStop = blnVisibleTabStop
         cmdID(miLmKWtLmK).TabStop = blnVisibleTabStop
         Call Util.SwchTabStopCtl(txtDate, miDateWean, miDate7Mon, blnVisibleTabStop)
         Call Util.SwchTabStopCtl(txtNum, miWtWean, miWt7Mon, blnVisibleTabStop)
      Case .FrmWtWoolIdx
         txtID(miShGWtWool).TabStop = blnVisibleTabStop
         cmdID(miShGWtWool).TabStop = blnVisibleTabStop
         Call Util.SwchTabStopCtl(txtDate, miDateAnnl, miDateShearAnnl, blnVisibleTabStop)
         Call Util.SwchTabStopCtl(txtNum, miWtAnnl, miGreaseAnnl, blnVisibleTabStop)
         flexGrid(miFlexWtWool).TabStop = blnVisibleTabStop
      Case .FrmApprIdx
         txtID(miShGAppr).TabStop = blnVisibleTabStop
         cmdID(miShGAppr).TabStop = blnVisibleTabStop
         txtDate(miDateAppr).TabStop = blnVisibleTabStop
         Call Util.SwchTabStopCtl(txtNum, miLeng, miFibreYield, blnVisibleTabStop)
         Call Util.SwchTabStopCtl(dbcFld, miDiam, miDefct, blnVisibleTabStop)
         Call SwchTabStopLvw(miLvwInhertDefct, blnVisibleTabStop) 'Switch the list view & its buttons.
         flexGrid(miFlexAppr).TabStop = blnVisibleTabStop
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the list view's & its adjacent buttons' TabStop's.
Private Sub SwchTabStopLvw(ByVal intIdx As Integer, ByVal blnTabStop As Boolean)
On Error GoTo ErrHnd
   lvwList(intIdx).TabStop = blnTabStop
   cmdAdd(intIdx).TabStop = blnTabStop
   cmdDel(intIdx).TabStop = blnTabStop
   If intIdx = miLvwOffsp Then cmdEdit(intIdx).TabStop = blnTabStop 'For the offspring
Exit Sub                                                           'list view only.
ErrHnd:
MsgBox Err.Description
End Sub

' Unless populated yet populate lambings/kiddings to show.
' Fill the Mat/LmK grid.
Private Sub BrsMatLmK(ByVal strIDDam As String)
On Error GoTo ErrHnd
   Const intDateLmK As Integer = 3
   Const intWtBirth As Integer = 7
   With adoGrid(MatLmKIdx)
      If .ConnectionString = "" Then .ConnectionString = gcnnConn.ConnectionString
      .RecordSource = "SHAPE {SELECT * FROM `Mate` WHERE IDDam = '" & strIDDam & "'}  AS spSelect_Mate_IDDam APPEND (( SHAPE {SELECT * FROM `LambKidV`}  AS LambKidV APPEND ({SELECT * FROM `OffspringV`}  AS OffspringV RELATE 'IDDam' TO 'IDDam','Cycle' TO 'Cycle') AS OffspringV) AS LambKidV RELATE 'IDDam' TO 'IDDam','Cycle' TO 'Cycle') AS LambKidV"
      .Refresh
   End With
   With flexGrid(MatLmKIdx) 'Set the grid's data source.
      Set .DataSource = adoGrid(MatLmKIdx)
      .Refresh
      If strIDDam <> "" Then 'Format the grid, if filled.
         Set mobUtilBrsMatLmK.Grid = flexGrid(MatLmKIdx) 'Set the grid.
         Call ReszColMatLmK 'Resize the columns.
         mobUtilBrsMatLmK.Formt mobUtilBrsMatLmK.FormtDate, mintColDateMat, _
            .ColHeaderCaption(mintBndMat, mintColDateMat) 'Format the mating & lambing/kidding dates.
         mobUtilBrsMatLmK.Formt mobUtilBrsMatLmK.FormtDate, intDateLmK, _
            .ColHeaderCaption(mintBndLmK, mintColDateLmK)
         mobUtilBrsMatLmK.Formt mobUtilBrsMatLmK.FormtNum, intWtBirth, _
            .ColHeaderCaption(mintBndOffsp, mintColWtBirth) 'Format WtBirth.
         mobUtilBrsMatLmK.CyclAgeActFoc MatLmKCycleAct, mintColCycle, _
            .ColHeaderCaption(mintBndMat, mintColCycle) 'Focus the active cycle.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the flexMateLmK grid.
Private Sub ReszColMatLmK()
On Error GoTo ErrHnd
   Const intColSire As Integer = 1 'The Mate band's local column constants.
   Const intColAbortYN As Integer = 1 'The LmK band's local column constants.
   Const intColLmK As Integer = 0 'The Offsp band's local column constants.
   Const intColSex As Integer = 1
   Const intColLiv As Integer = 3
   Const sngWdCycle As Single = 0.06 'The Mate band's columns' width coefficients.
   Const sngWdSire As Single = 0.11
   Const sngWdDateMat As Single = 0.11
   Const sngWdDateLmK As Single = 0.13 'The LmK band's columns' width coefficients.
   Const sngWdAbortYN As Single = 0.09
   Const sngWdLmK As Single = 0.11 'The Offsp band's columns' width coefficients.
   Const sngWdSex As Single = 0.08
   Const sngWdWtBirth As Single = 0.11
   Const sngWdLiv As Single = 0.2
   With flexGrid(MatLmKIdx) 'Get the grid.
      .ColWidth(mintColCycle) = .Width * sngWdCycle '500 'Cycle
      .ColWidth(intColSire) = .Width * sngWdSire '950 'Sire
      .ColWidth(mintColDateMat) = .Width * sngWdDateMat '750 'Mate date
      .ColWidth(mintColDateLmK, mintBndLmK) = .Width * sngWdDateLmK '1250 'DateLambKid
      .ColWidth(intColAbortYN, mintBndLmK) = .Width * sngWdAbortYN '800 'AbortYN
      .ColWidth(intColLmK, mintBndOffsp) = .Width * sngWdLmK '950 'LmK
      .ColWidth(intColSex, mintBndOffsp) = .Width * sngWdSex '650 'Sex
      .ColWidth(mintColWtBirth, mintBndOffsp) = .Width * sngWdWtBirth '850 'WtBirth
      .ColWidth(intColLiv, mintBndOffsp) = Util.PostvSize(.Width * sngWdLiv - _
         mintIndtEscShift) '1600 'Liv
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Define the active cycle shown in the Mate/LmK data form to highlight as active in the
'  flexGrid(miFlexMat/miFlexLmK) grids.
Private Function MatLmKCycleAct() As Integer
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmMatIdx
      With gobShGs(mobDatFrm.IDFrm).Dam.Mats
         If .Count > 0 Then MatLmKCycleAct = .Act.Cycle 'Get a cycle, if any.
      End With
   Case gobSetng.FrmLmKIdx
      With gobShGs(mobDatFrm.IDFrm).Dam.LmKs
          If .Count > 0 Then MatLmKCycleAct = .Act.Cycle 'Get a cycle, if any.
      End With
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the Mate/LmK grid's index based on the selected tab.
Private Property Get MatLmKIdx() As Integer
On Error GoTo ErrHnd
   Select Case tabShG.SelectedItem.Index
   Case gobSetng.FrmMatIdx
      MatLmKIdx = miFlexMat
   Case gobSetng.FrmLmKIdx
      MatLmKIdx = miFlexLmK
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property
' Show the selected cycle's mating or lambing/kidding in the Edit/Del modes.
' Prior to presenting the data in frmLmK make sure that there is lambing/kidding in the
'  selected cycle.
Private Sub ShowMatLmK(ByVal intIdx As Integer)
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim intCycle As Integer
   If mobDatFrm.Mode = gobSetng.ModeAdd Then 'No record selectiion in the Add mode.
      MsgBox LoadResString(185) & LoadResString(186), vbInformation, LoadResString(370)
   Else 'Proceed in the Edit/Del modes.
      With mobUtilBrsMatLmK
         Set .Grid = flexGrid(MatLmKIdx) 'Set the grid.
         intCycle = .CyclAgeGet(flexGrid(MatLmKIdx).ColHeaderCaption(mintBndMat, _
            mintColCycle)) 'Get the selected row's cycle.
      End With
      Select Case intIdx
      Case miFlexMat
         Call CtlWriteMat(gobShGs(mobDatFrm.IDFrm).Dam.Mats(intCycle, False)) 'Fill the form.
      Case miFlexLmK
         With gobShGs(mobDatFrm.IDFrm).Dam.LmKs
            If .CycleVld(intCycle) Then 'Validate the selected cycle.
               Call CtlWriteLmK(.Act) 'Fill the LmK data form.
            Else 'Cancel filling.
               MsgBox LoadResString(177) & mobDatFrm.IDFrm & LoadResString(178) & _
                  intCycle & LoadResString(179), vbInformation, LoadResString(172)
               flexGrid(MatLmKIdx).SetFocus
            End If
         End With
      End Select
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unless populated yet populate lambings/kiddings to show.
' Initialise mobDatFrm, controls & fill the form.
Private Sub BrsAppr(ByVal strIDShG As String)
On Error GoTo ErrHnd
   With adoGrid(miFlexAppr)
      If .ConnectionString = "" Then .ConnectionString = gcnnConn.ConnectionString
      .RecordSource = " SHAPE {SELECT * FROM `spSelect_Appraisal_IDShG` WHERE IDSheepGoat = '" & strIDShG & "'}  AS Temp_spSelect_Appraisal_IDShG APPEND ({SELECT * FROM `InhertDefectV`}  AS InhertDefectV RELATE 'IDSheepGoat' TO 'IDSheepGoat','Age' TO 'Age') AS InhertDefectV"
      .Refresh
   End With
   With flexGrid(miFlexAppr) 'Set the grid's data source.
      Set .DataSource = adoGrid(miFlexAppr)
      .Refresh
   End With
   If strIDShG <> "" Then 'Format the grid, if filled.
      Call ReszColAppr 'Resize the columns.
      With mobUtilBrsAppr
         .Formt .FormtDate, mintColDateAppr, flexGrid(miFlexAppr).ColHeaderCaption( _
            mintBndWoolExtr, mintColDateAppr) 'Format the appraisal dates.
         .Formt .FormtNum, mintColLeng, flexGrid(miFlexAppr).ColHeaderCaption( _
            mintBndWoolExtr, mintColLeng) 'Format WtBirth.
         .CyclAgeActFoc gobShGs(mobDatFrm.IDFrm).Apprs.Act.Age, mintColAge, flexGrid( _
            miFlexAppr).ColHeaderCaption(mintBndWoolExtr, mintColAge) 'Focus the active age row.
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the flexMateLmK grid.
Private Sub ReszColAppr()
On Error GoTo ErrHnd
   Const intBandInhertDefct As Integer = 1 'The InhertDefct band.
   Const intColDefct As Integer = 0 'The Defct column.
   With flexGrid(miFlexAppr)
      .ColWidth(mintColAge) = 500 'Age
      .ColWidth(mintColDateAppr) = 950 '800
      .ColWidth(mintColLeng) = 900 '1050 'Length.
      .ColWidth(3) = 700
      .ColWidth(4) = 600
      .ColWidth(5) = 600
      .ColWidth(6) = 600 '800
      .ColWidth(7) = 1200 '1000
      .ColWidth(8) = 600
      .ColWidth(9) = 1500
      .ColWidth(10) = 1150 '850
      .ColWidth(11) = 1650
      .ColWidth(12) = 1000 '800
      .ColWidth(13) = 1000 '900
      .ColWidth(14) = 600 '500
      .ColWidth(15) = 600 '700
      .ColWidth(16) = 600 '550
      .ColWidth(17) = 950 '800
      .ColWidth(intColDefct, intBandInhertDefct) = 2700
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the selected age in the frmAppr form in the Edit/Del modes.
Private Sub ShowAppr()
On Error GoTo ErrHnd
   If mobDatFrm.Mode = gobSetng.ModeAdd Then 'No record selectiion in the Add mode.
      MsgBox LoadResString(187) & LoadResString(186), vbInformation, LoadResString(370)
   Else 'Proceed in the Edit/Del modes.
      mobDatFrm.CtlClear 'Clear & show.
      Call CtlWriteAppr(gobShGs(mobDatFrm.IDFrm).Apprs(mobUtilBrsAppr.CyclAgeGet( _
         flexGrid(miFlexAppr).ColHeaderCaption(mintBndWoolExtr, mintColAge)), False))
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the WtWool grid.
Private Sub BrsWtWool(ByVal strIDShG As String)
On Error GoTo ErrHnd
   Const intColDateAnnl As Integer = 1 'The columns.
   Const intColWtAnnl As Integer = 2
   Const intColDateShearAnnl As Integer = 3
   Const intColGreaseAnnl As Integer = 4
   With adoGrid(miFlexWtWool)
      If .ConnectionString = "" Then .ConnectionString = gcnnConn.ConnectionString
      .RecordSource = "SELECT * FROM WeightWoolAnnl WHERE IDSheepGoat = '" & strIDShG & "'"
      .Refresh
   End With
   With flexGrid(miFlexWtWool) 'Set the grid's data source.
      Set .DataSource = adoGrid(miFlexWtWool)
      .Refresh
   End With
   If strIDShG <> "" Then 'Format the grid, if filled.
      Call ReszColWtWool 'Resize the columns.
      With mobUtilBrsWtWool
         .Formt .FormtDate, intColDateAnnl, flexGrid(miFlexWtWool).ColHeaderCaption( _
            mintBndWtWool, intColDateAnnl) 'Format the wt date.
         .Formt .FormtNum, intColWtAnnl, flexGrid(miFlexWtWool).ColHeaderCaption( _
            mintBndWtWool, intColWtAnnl) 'Format wt.
         .Formt .FormtDate, intColDateShearAnnl, flexGrid(miFlexWtWool) _
            .ColHeaderCaption(mintBndWtWool, intColDateShearAnnl) 'Format the wool date.
         .Formt .FormtNum, intColGreaseAnnl, flexGrid(miFlexWtWool).ColHeaderCaption( _
            mintBndWtWool, intColGreaseAnnl) 'Format wool.
         .CyclAgeActFoc gobShGs(mobDatFrm.IDFrm).WtWools.Act.Age, mintColAge, flexGrid( _
            miFlexWtWool).ColHeaderCaption(mintBndWtWool, mintColAge) 'Focus the active age row
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resize the WtWool grid's columns.
Private Sub ReszColWtWool()
On Error GoTo ErrHnd
   Dim lngWdth As Long
   Dim I As Integer
   With flexGrid(miFlexWtWool)
      lngWdth = .Width / .Cols - mintIndtEscShift / .Cols 'Column width.
      lngWdth = IIf(lngWdth > 0, lngWdth, 0) 'Must be positiive.
      For I = 0 To .Cols - 1 'All columns' width is even.
         .ColWidth(I) = lngWdth
      Next
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the selected age in the WtWool form in the Edit/Del modes.
Private Sub ShowWtWool()
On Error GoTo ErrHnd
   With mobDatFrm
      If .Mode = gobSetng.ModeAdd Then 'No record selectiion in the Add mode.
         MsgBox LoadResString(188) & LoadResString(186), vbInformation, LoadResString(370)
      Else 'Proceed in the Edit/Del modes.
         Call CtlWriteWtWool(gobShGs(.IDFrm).WtWools(mobUtilBrsWtWool _
            .CyclAgeGet(flexGrid(miFlexWtWool).ColHeaderCaption(mintBndWtWool, _
            mintColAge)), False))
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the Mat/LmK data forms to make the user syncronise them to each other by
'  reloading them. This is required after updating the dam's mating, lamb/kidding or
'  after changing one of the lamb/kid's ID or sex in the latter's own frmShG data form.
Public Sub UnldSyncMatLmK(ByVal intFrmUnld As Integer)
On Error GoTo ErrHnd
   Dim intFrmOrig As Integer
   If mblnFrmFilld(intFrmUnld) Then 'Proceed, if loaded.
      With tabShG
         intFrmOrig = .SelectedItem.Index 'Save the original index to restore later.
         mblnEscTabClick = True 'Prevent the tab click operation.
         .Tabs(intFrmUnld).Selected = True 'Select the unloaded data form.
         mobDatFrm.Cancel True
         .Tabs(intFrmOrig).Selected = True 'Reset.
      End With
      mblnEscTabClick = False
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sire/dam's duplicate ID message for the VldSrDmIDSex procedure.
Private Property Get SrDmMsgDupl(ByVal intIdx As Integer) As String
On Error GoTo ErrHnd
   Select Case intIdx
   Case miSireInven, miDamInven 'Sire/dam's promt.
Debug.Assert 0 = 1 'Verify
      SrDmMsgDupl = LoadResString(553)
   Case miSireMat 'Mating sire's promt.
      SrDmMsgDupl = LoadResString(577)
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property


' Validate how the controls are filled.
' Return True, if succeeds.
Private Function VldFillCtlMat() As Boolean
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   Dim strLabel As String
   Dim strExplain As String
   Dim blnEscMsg As Boolean
   If Trim$(txtID(miSireMat)) = "" Then 'Define the sire.
      Set ctlCtl = txtID(miSireMat)
      strLabel = lblID(miSireMat)
   ElseIf Trim$(txtDate(miDateMat)) = "" Then 'Define the mating-from date.
      Set ctlCtl = txtDate(miDateMat)
      strLabel = lblDate(miDateMat)
   Else
      VldFillCtlMat = True 'Validation passed.
   End If
   If VldFillCtlMat = False And blnEscMsg = False Then Call Util.MissParam(ctlCtl, strLabel, _
      strExplain) 'Message & focus.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the dam/sire's age at the mating.
' Return True, if succeeds.
Private Function VldAgeMat(ByVal obShG As ShG, ByVal intAgeMatMin As Integer, ByVal _
   strYngPromtAffx As String) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim blnFail As Boolean
   With obShG
      If Not .Lives(txtDate(miDateMat), fraFrame(gobSetng.FrmMatIdx).Caption, strPromt:= _
         strPromt) Then 'Lives?
         blnFail = True 'Failed.
      ElseIf .Age(txtDate(miDateMat)) < intAgeMatMin Then 'Mature?
         blnFail = True 'Too young.
         strPromt = strYngPromtAffx & intAgeMatMin & LoadResString(231)
      End If
   End With
   If blnFail Then
      MsgBox strPromt, vbExclamation, LoadResString(131) 'Message & focus.
      txtDate(miDateMat).SetFocus
   Else
      VldAgeMat = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the mating dates that they not overlap each other.
' In the Add mode check the previous date only, whereas in the Edit mode, validate the
'  next date, too.
' Return True, if succeeds.
Private Function VldOvlpMat() As Boolean
On Error GoTo ErrHnd
   Dim dtmDateNxt As Date
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm).Dam.Mats
      Select Case mobDatFrm.Mode
      Case gobSetng.ModeAdd
         If .Count > 0 Then blnFail = Not VldOvlpPrevMat(.Act.Cycle) 'Validate
      Case gobSetng.ModeEdit                            'the by the last recorded date.
         If .Count > 1 Then 'Are there other matings to overlap?
            If .Act.Cycle > .First(True).Cycle Then blnFail = Not VldOvlpPrevMat( _
               .Prev(True).Cycle) 'Ovelapping the prev. mating, unless it's the 1st
            If Not blnFail Then 'Overlapping the next mating, unless failed above.
               If .Act.Cycle < .Last(True).Cycle Then blnFail = Not VldOvlpNxtMat( _
                  .Nxt(True).DateMat) 'Ovelapping the next mating
               If Not blnFail Then blnFail = Not VldPregnLengMat 'Length of pregn., if
            End If                                               'any, unless failed above.
         End If
      End Select
   End With
   VldOvlpMat = Not blnFail 'Succeeded/failded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that the mating date not overlap:
'  - the previous mating date;
'  - the date of the previous lamb/kidding, if any.
' Return True, if succeeds. If the mating overlaps the previous lamb/kidding return False,
'  unless the wrong entry is canceled.
Private Function VldOvlpPrevMat(ByVal intCyclePrev As Integer) As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm).Dam 'Below: Validate the prev. mating.
      If CDate(txtDate(miDateMat)) <= .Mats(intCyclePrev, True).DateMat Then
         blnFail = True 'Overlapped mating.
         strPromt = LoadResString(579) & txtDate(miDateMat) & LoadResString(580) & _
            .Mats(intCyclePrev, True).DateMat & ")." 'Message & focus.
         MsgBox strPromt, vbExclamation, LoadResString(131)
      Else 'Validate the prev. lamb/kiddig.
         If .LmKedAfterMat(intCyclePrev) Then 'Proceed, if Lamb/kidded.
            If CDate(txtDate(miDateMat)) <= .LmKs(intCyclePrev, True).DateLmK Then
               strPromt = LoadResString(583) & txtDate(miDateMat) & LoadResString(591) _
                  & .LmKs(intCyclePrev, True).DateLmK & LoadResString(592) & _
                  intCyclePrev & LoadResString(593) 'Overlapped lamb/kidding.
               If MsgBox(strPromt, vbQuestion + vbYesNo, LoadResString(131)) = vbYes _
                  Then blnFail = True 'Promt to cancel the wrong entry.
            End If
         End If
      End If
   End With
   If blnFail Then
      txtDate(miDateMat).SetFocus 'Focus.
   Else
      VldOvlpPrevMat = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that the mating date not overlap the next one.
' Return True, if succeeds.
Private Function VldOvlpNxtMat(ByVal dtmDateNxt As Date) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If CDate(txtDate(miDateMat)) < dtmDateNxt Then 'Overlapped?
      VldOvlpNxtMat = True 'Succeeded.
   Else 'Failed.
      strPromt = LoadResString(579) & txtDate(miDateMat) & LoadResString(582) & _
         dtmDateNxt & ")." 'Message & focus.
      MsgBox strPromt, vbExclamation, LoadResString(131)
      txtDate(miDateMat).SetFocus
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the length of pregnancy, if lamb/kidded in the current cycle, after editing
'  the mating in the same cycle.
' Return True, if succeeds. If failes return False, if the entry is canceled.
Private Function VldPregnLengMat() As Boolean
On Error GoTo ErrHnd
   Dim intCycleAct As Integer
   Dim strPromt As String
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm).Dam
      intCycleAct = .Mats.Act.Cycle 'Active cycle for later use.
      If .LmKedAfterMat(intCycleAct) Then 'Proceed, if lamb/kidded.
         With .LmKs(intCycleAct, False)
            If Not VldPregnLengDo(intCycleAct, txtDate(miDateMat), .DateLmK, .Abort, _
               strPromt) Then
               strPromt = strPromt & LoadResString(594) 'Complete the promt.
               If MsgBox(strPromt, vbYesNo + vbQuestion, LoadResString(131)) = vbYes Then 'Promt to correct.
                  blnFail = True 'Failed.
                  txtDate(miDateMat).SetFocus 'Focus.
               End If
            End If
         End With
      End If
   End With
   VldPregnLengMat = Not blnFail 'Succeeded/fialed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the age at the 1st & last matings (lamb/kidding for a dam) for the Inven data
'  form.
' Return True, if succeeds.
Private Function VldAgeMatLmK() As Boolean
On Error GoTo ErrHnd
   Dim lngCountMat As Long
   Dim dtmDateLstMatLmK As Date
   Dim strAffxLstMatLmK As String
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm)
      Select Case .TblShG.IDSex 'Validate matings by sex.
      Case gobSetng.IDSexMl 'Sire's matings.
         With .Sire
            lngCountMat = .CountMat 'Count matings.         'Below: Validate, if mated.
            If lngCountMat > 0 Then blnFail = Not VldBirthDisp(.DatMatFirst, .DatMatLast, _
               gobTblCtrlParam.AgeMatMinSr, LoadResString(540), LoadResString(530))
         End With
      Case gobSetng.IDSexFm 'Dam's matings & lamb/kiddings.
         With .Dam
            If Not .PopltMat Then .MatSel False 'Populate Mat's.
            If .Mats.Count > 0 Then 'Validate, if mated.
               If Not .PopltLmK Then .LmKSel False 'Populate LmK's
               If .LmKs.Count > 0 Then If .LmKedAfterMat(.Mats.Last(True).Cycle) Then _
                  dtmDateLstMatLmK = .LmKs.Last(True).DateLmK 'Define dam's last event:
               If dtmDateLstMatLmK = 0 Then                   'Mat or LmK.
                  dtmDateLstMatLmK = .Mats.Last(True).DateMat 'The latest is Mat.
                  strAffxLstMatLmK = LoadResString(530) 'Mat promt affix.
               Else 'The latest is LmK.
                  strAffxLstMatLmK = LoadResString(531) 'LmK promt affix.
               End If
               blnFail = Not VldBirthDisp(.Mats.First(True).DateMat, dtmDateLstMatLmK, _
                  gobTblCtrlParam.AgeMatMinDm, LoadResString(540), strAffxLstMatLmK) 'Validate.
            End If
         End With
      End Select
   End With
   VldAgeMatLmK = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the lamb/kid's age at the wean/7-mon weighing for the Inven data form.
' Return True, if succeeds.
Private Function VldAgeWean7Mon() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm)
      Set obDatTbl = .TblWtWean 'Validate wean wt.
      If Not obDatTbl.Full Then .SelWtWean False 'Populate wean wt.
      If obDatTbl.Full Then blnFail = Not VldAgeWean7MonDo(.TblWtWean.DateWean, _
         gobTblCtrlParam.AgeWeanMin, gobTblCtrlParam.AgeWeanMax, LoadResString(533)) 'Validate, if full.
      If Not blnFail Then 'Validate 7-mon wt, unless failed above.
         Set obDatTbl = .TblWt7Mon
         If Not obDatTbl.Full Then .SelWt7Mon 'Populate 7-mon wt.
         If obDatTbl.Full Then blnFail = Not VldAgeWean7MonDo(.TblWt7Mon.Date7Mon, _
            gobTblCtrlParam.Age7MonMin, gobTblCtrlParam.Age7MonMax, LoadResString(534)) 'Validate, if full.
      End If
   End With
   VldAgeWean7Mon = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the lamb/kid's age at the wean/7-mon weighing for the Inven data form.
' Return True, if succeeds.
Private Function VldAgeWean7MonDo(ByVal dtmDateWean7Mon As Date, ByVal intAgeWean7MonMin _
   As Integer, ByVal intAgeWean7MonMax As Integer, ByVal strAffxWean7Mon As String) _
   As Boolean
On Error GoTo ErrHnd
   Dim sngAgeYr As Single
   Dim sngAgeDay As Single
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm)
      sngAgeDay = .Age(dtmDateWean7Mon) 'Age in days.
      If sngAgeDay <= 0 Then 'Overlapping the wean/7-mon date.
         blnFail = True 'Overlapped.
         strPromt = Util.CutColonAmpers(fraFrame(miFraBirth).Caption) & " (" & txtDate( _
            miDateBirth) & LoadResString(532) & strAffxWean7Mon & .TblWtWean.DateWean & _
            LoadResString(541) & LoadResString(593)
      ElseIf sngAgeDay < intAgeWean7MonMin Then 'Min wean/7-mon age.
         blnFail = True 'Min age violated.
         strPromt = LoadResString(542) & sngAgeDay & LoadResString(535) _
            & strAffxWean7Mon & dtmDateWean7Mon & LoadResString(544) & intAgeWean7MonMin _
            & LoadResString(590)
      End If
      If blnFail Then 'Promt to correct.
         If MsgBox(strPromt, vbQuestion + vbYesNo, LoadResString(131)) = vbNo Then _
            blnFail = False 'Correction rejected.
      End If
      If Not blnFail Then 'Proceed, unless failed above.
         If Not .Lives(dtmDateWean7Mon, blnEscDisp:=True) Then 'Life time.
            sngAgeYr = .Age(dtmDateWean7Mon, True) 'Age in yr's.
            If sngAgeYr > 0 Then 'Message, if the age is positive.
               blnFail = True 'Life time violated.
               strPromt = LoadResString(542) & sngAgeYr & LoadResString(545) _
                  & strAffxWean7Mon & dtmDateWean7Mon & LoadResString(546) & _
                  gobTblCtrlParam.LifeTimeMax & LoadResString(547) 'Violated the max age.
            End If
         ElseIf sngAgeDay > intAgeWean7MonMax Then 'Max wean/7-mon age.
            blnFail = True 'Max age violated.
            strPromt = LoadResString(542) & sngAgeDay & LoadResString(535) & _
               strAffxWean7Mon & dtmDateWean7Mon & LoadResString(546) & _
               intAgeWean7MonMax & LoadResString(590)
         End If
         If blnFail Then 'Promt to correct.
            If MsgBox(strPromt, vbQuestion + vbYesNo, LoadResString(131)) = vbNo Then _
               blnFail = False 'Correction rejected.
         End If
      End If
   End With
   If blnFail Then
      txtDate(miDateBirth).SetFocus 'Focus.
   Else
      VldAgeWean7MonDo = VldDisp(dtmDateWean7Mon, strAffxWean7Mon) 'Validate disp. date.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

'  update the despcription.
' Validate the ShG's age at the 1st & last records specified.
' Return True, if succeeds.
Private Function VldBirthDisp(ByVal dtmDateFst As Date, ByVal dtmDateLst As Date, _
   ByVal intAgeMinCtrlParam As Integer, ByVal strAffxFst As String, ByVal strAffxLst _
   As String) As Boolean
On Error GoTo ErrHnd
   Dim sngAgeLst As Single
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm)
      If .Age(dtmDateFst) <= 0 Then 'Overlapping the 1st record's date.
         blnFail = True 'Overlapped.
         strPromt = Util.CutColonAmpers(fraFrame(miFraBirth).Caption) & " (" & txtDate( _
            miDateBirth) & LoadResString(536) & strAffxFst & dtmDateFst & ")" & _
            LoadResString(593)
      ElseIf intAgeMinCtrlParam <> 0 And .Age(dtmDateFst) < intAgeMinCtrlParam Then 'Min age.
         blnFail = True 'Min age violated.
         strPromt = LoadResString(542) & .Age(dtmDateFst) & LoadResString(543) _
            & dtmDateFst & LoadResString(544) & intAgeMinCtrlParam & LoadResString(590)
      End If
      If blnFail Then 'Promt to correct.
         If MsgBox(strPromt, vbQuestion + vbYesNo, LoadResString(131)) = vbNo Then _
            blnFail = False 'Correction rejected.
      End If
      If Not blnFail Then 'Validate the last record's date, unless failed above.
         If Not .Lives(dtmDateLst, blnEscDisp:=True) Then 'Lives?
            sngAgeLst = .Age(dtmDateLst, True) 'Age at the last record.
            If sngAgeLst > 0 Then 'Message, if the age is positive.
               strPromt = LoadResString(542) & sngAgeLst & LoadResString(545) & _
                  strAffxLst & dtmDateLst & LoadResString(546) & gobTblCtrlParam _
                  .LifeTimeMax & LoadResString(547) 'Violated the max age.
               If MsgBox(strPromt, vbQuestion + vbYesNo, LoadResString(131)) = vbYes _
                  Then blnFail = True
            End If
         End If
      End If
   End With
   If blnFail Then
      txtDate(miDateBirth).SetFocus 'Focus.
   Else
      VldBirthDisp = VldDisp(dtmDateLst, strAffxLst) 'Validate the disposition date.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the age for the Inven data form at the 1st & last annual weiging/shearing's.
' Return True, if succeeds.
Private Function VldAgeWtWool() As Boolean
On Error GoTo ErrHnd
   Dim dtmDateFst As Date
   Dim dtmDateLst As Date
   Dim intAge1YrMin As Integer
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm)
      If Not .PopltWtWool Then .SelWtWool False 'Populate wt/wool's.
      With .WtWools
         If .Count > 0 Then 'Validate, if weighed. Below: Define the 1st date & min 1-yr
            dtmDateFst = .First(True).DateAnnl                      'age: wt's or wool's?
            intAge1YrMin = gobTblCtrlParam.Age1YrWtMin
            If dtmDateFst = 0 Then 'Wool's vs. wt's, if the 1st wt is missing.
Debug.Assert 0 = 1 'Verify If
               dtmDateFst = .First(True).DateShearAnnl
               intAge1YrMin = gobTblCtrlParam.Age1YrShearMin
            End If 'Below: 'Define the last date: wt's or wool's?
            dtmDateLst = .Last(True).DateAnnl 'Below: 'Wool's vs. wt's, if the last wt is
            If dtmDateLst = 0 Then dtmDateLst = .Last(True).DateShearAnnl 'missing.
            blnFail = Not VldBirthDisp(dtmDateFst, dtmDateLst, intAge1YrMin, _
               LoadResString(537), LoadResString(538))
'            blnFail = Not VldDisp(dtmDateLst, LoadResString(538)) 'Validate disp. date.
         End If
      End With
   End With
   VldAgeWtWool = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the age for the Inven data form at the 1st & last appraisals.
' Return True, if succeeds.
Private Function VldAgeAppr() As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm)
      If Not .PopltAppr Then .SelAppr False 'Populate appraisals.
      With .Apprs
         If .Count > 0 Then 'Validate, if appaised.
            blnFail = Not VldBirthDisp(.First(True).DateAppr, .Last(True).DateAppr, _
               gobTblCtrlParam.Age1YrShearMin, LoadResString(539), LoadResString(548))
         End If
      End With
   End With
   VldAgeAppr = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the age for the Inven data form at the 1st & last farm transfers.
' Validate the farm ID according to the last farm transfer so that the last tranfsfered-
'  to-farm be the residential one.
' Return True, if succeeds.
Private Function VldTrans() As Boolean
On Error GoTo ErrHnd
   Dim dtmDateTransFrs As Date
   Dim dtmDateTransLst As Date
   Dim strIDFarmTransLst As String
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm).TblShG 'Define the 1st & last transfers' data.
      If .TransFarmChand Then 'Use the new vs. old transfers, if changed & vice versa.
         With .TransFarmsNew
            If .Count > 0 Then 'Are there transfers?
               dtmDateTransFrs = .First.DateTrans
               With .Last
                  dtmDateTransLst = .DateTrans
                  strIDFarmTransLst = .IDFarm
               End With
            End If
         End With
      Else
         With .TransFarms
            If .Count > 0 Then 'Are there transfers?
               dtmDateTransFrs = .First.DateTrans
               With .Last
                  dtmDateTransLst = .DateTrans
                  strIDFarmTransLst = .IDFarm
               End With
            End If
         End With
      End If
      If dtmDateTransFrs <> 0 Then 'Validate the age.
         If Not VldBirthDisp(dtmDateTransFrs, dtmDateTransLst, 0, LoadResString(522), _
            LoadResString(523)) Then
            blnFail = True 'Failed.
         ElseIf dbcFld(miFarm) <> strIDFarmTransLst Then 'Validate the last farm ID.
            strPromt = LoadResString(213) & strIDFarmTransLst & LoadResString(214) & _
               LoadResString(593)
            If MsgBox(strPromt, vbQuestion + vbYesNo) = vbYes Then
               blnFail = True 'Promt to correct.
               dbcFld(miFarm).SetFocus 'Focus after the message.
            End If
         End If
      End If
   End With
   VldTrans = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the disposition date, if filled, that it not overlap any last record.
' Return True, if succeeds.
Private Function VldDisp(ByVal dtmDateLst As Date, ByVal strAffxLst As String) As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   Dim strPromt As String
   With txtDate(miDateDisp)
      If .Text <> "" And .Enabled Then 'Filled & enabled?
         If CDate(.Text) <= dtmDateLst Then 'Overlapped?
            strPromt = LoadResString(520) & .Text & LoadResString(521) & strAffxLst & _
               dtmDateLst & ")" & LoadResString(593)
            If MsgBox(strPromt, vbQuestion + vbYesNo, LoadResString(131)) = vbYes Then _
               blnFail = True  'Failes, unless correction rejected.
         End If
      End If
      If blnFail Then 'Focus.
         .SetFocus
      Else 'Succeeded.
         VldDisp = True
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the lamb/kidding dates that they not overlap each other.
' In the Add mode check the previous date only, whereas in the Edit mode, validate the
'  next date, too.
' Return True, if succeeds.
Private Function VldOvlpLmK() As Boolean
On Error GoTo ErrHnd
   Dim dtmDateNxt As Date
   Dim blnFail As Boolean
   Dim strPromt As String
   With gobShGs(mobDatFrm.IDFrm).Dam.LmKs
      If .Count > 1 Then 'Proceed, if ther're other records to be overlapped.
         Select Case mobDatFrm.Mode
         Case gobSetng.ModeAdd 'Validate the prev. recorord only.
            blnFail = Not VldOvlpPrevLmK(.Prev(True).DateLmK)
         Case gobSetng.ModeEdit 'Validate the prev. & next recorords.
            If .Act.Cycle > .First(True).Cycle Then blnFail = Not VldOvlpPrevLmK( _
               .Prev(True).DateLmK) 'The prev. LmK, unless it's the 1st.
            If Not blnFail Then 'The next LmK, unless failed above.
               If .Act.Cycle < .Last(True).Cycle Then 'The next LmK, unless it's the last.
                  dtmDateNxt = .Nxt(True).DateLmK 'The next date.
                  If CDate(txtDate(miDateLmK)) >= dtmDateNxt Then 'Overlapped?
                     blnFail = True 'Overlapped the next LmK.
                     strPromt = LoadResString(235) & txtDate(miDateLmK) & _
                        LoadResString(237) & dtmDateNxt & ")."
                     MsgBox strPromt, vbExclamation, LoadResString(131) 'Message & focus.
                     txtDate(miDateLmK).SetFocus
   End If: End If: End If: End Select: End If: End With
   VldOvlpLmK = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the pregnancy length.
' Return True, if succeeds.
Private Function VldPregnLengLmK() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim intCycleAct As Integer
   With gobShGs(mobDatFrm.IDFrm).Dam
      intCycleAct = .LmKs.Act.Cycle 'The active cycle for later use.
      If Not .PopltMat Then .MatSel False 'Populate matings.
      If VldPregnLengDo(intCycleAct, .Mats(intCycleAct, False).DateMat, (txtDate( _
         miDateLmK)), chkFld(miAbortChk), strPromt) Then
         VldPregnLengLmK = True 'Succeeded.
      Else 'Failed.
         MsgBox strPromt, vbExclamation, LoadResString(131)
         txtDate(miDateLmK).SetFocus
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the length of pregnancy in the specified cycle.
' Return True, if succeeds.
Private Function VldPregnLengDo(ByVal intCycle As Integer, ByVal dtmDateMat As Date, _
   ByVal dtmDateLmK As Date, ByVal intAbort As Integer, ByRef strPromt As String) _
   As Boolean
On Error GoTo ErrHnd
   Dim lngPregnLeng As Long
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm).Dam
      lngPregnLeng = dtmDateLmK - dtmDateMat 'Pregn. length.
      If lngPregnLeng <= 0 Then 'Lamb/kidded after mating?
         blnFail = True 'Can't lamb/kid before mating.
         strPromt = LoadResString(583) & dtmDateMat & LoadResString(584) & intCycle & _
            LoadResString(585) & dtmDateLmK & "). "
      Else
         If (lngPregnLeng < gobTblCtrlParam.PregnLengMin And intAbort = vbUnchecked) Or _
            (lngPregnLeng > gobTblCtrlParam.PregnLengMax) Then
            blnFail = True 'Min/max pregn. length violated.
            strPromt = LoadResString(586) & lngPregnLeng & LoadResString(587) & _
               dtmDateMat & LoadResString(588) & dtmDateLmK & LoadResString(584) & _
               intCycle & LoadResString(589) & gobTblCtrlParam.PregnLengMin & _
               LoadResString(26) & gobTblCtrlParam.PregnLengMax & LoadResString(234)
         End If
      End If
   End With
   VldPregnLengDo = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the lamb/kidding date that it not overlap the previous one.
' Return True, if succeeds.
Private Function VldOvlpPrevLmK(ByVal dtmDatePrev As Date) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If txtDate(miDateLmK) > dtmDatePrev Then
      VldOvlpPrevLmK = True 'Succeeded.
   Else 'Overlapped the prev. lamb/kidding.
      strPromt = LoadResString(235) & txtDate(miDateLmK) & LoadResString(236) & _
         dtmDatePrev & ")." 'Message & focus.
      MsgBox strPromt, vbExclamation, LoadResString(131)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the weighing & shearing that they not ovrlap the annual interval with the
'  previous & next records in the Edit mode.
' Return True, if succeeds.
Private Function VldOvlpWtWoolEdit() As Boolean
On Error GoTo ErrHnd
   Dim blnVldPrev As Boolean
   Dim blnVldNxt As Boolean
   Dim dtmDateNxt As Date
   Dim blnFail As Boolean
   Dim strPromt As String
   Dim strAffxNxt As String
   With gobShGs(mobDatFrm.IDFrm).WtWools
      If .Count > 1 Then 'Proceed, if ther're other records to be overlapped.
         If .Act.Age > .First(True).Age Then blnVldPrev = True 'Validate towards the prev., unless it's the 1st.
         If .Act.Age < .Last(True).Age Then blnVldNxt = True 'Validate towards the next, unless it's the last.
         If Trim$(txtDate(miDateAnnl)) <> "" Then 'Validate wt, if filled.
            If blnVldPrev Then blnFail = Not VldOvlpPrevWt 'Prev. wt.
            If blnFail = False And blnVldNxt Then 'Next wt, unless failed above.
               dtmDateNxt = .Nxt(True).DateAnnl 'The next date.
               If dtmDateNxt = 0 Then 'Check if there's wt.
                  dtmDateNxt = .Nxt(True).DateShearAnnl 'No wt - use wool date instead.
                  strAffxNxt = LoadResString(337) 'Wool promt affix.
               Else
                  strAffxNxt = LoadResString(336) 'Wt promt affixes.
               End If
               blnFail = Not VldOvlpNxtAnnl(miDateAnnl, dtmDateNxt, _
                  LoadResString(344), strAffxNxt)
            End If
         End If 'Below: 'Validate woll, if filled & not failed above.
         If blnFail = False And Trim$(txtDate(miDateShearAnnl)) <> "" Then
            If blnVldPrev Then blnFail = Not VldOvlpPrevWool 'Prev. wool.
            If blnFail = False And blnVldNxt Then 'Next wool, unless failed above.
               dtmDateNxt = .Nxt(True).DateShearAnnl 'The next date.
               If dtmDateNxt = 0 Then 'Check if there's wool.
                  dtmDateNxt = .Nxt(True).DateAnnl 'No wool - use wt date instead.
                  strAffxNxt = LoadResString(336)
               Else
                  strAffxNxt = LoadResString(337)
               End If
               blnFail = Not VldOvlpNxtAnnl(miDateShearAnnl, dtmDateNxt, _
                  LoadResString(350), strAffxNxt)
            End If
         End If
      End If
   End With
   VldOvlpWtWoolEdit = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the annual records (i.e. weighing, shearing, or appraisal) that they not
'  ovrlap the annual interval with the next records.
' Return True, if succeeds.
Private Function VldOvlpNxtAnnl(ByVal intIdx As Integer, ByVal dtmDateNxt As Date, _
   ByVal strAffxAct As String, ByVal strAffxNxt As String) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   With gobTblCtrlParam 'Below: Is the annl. interval overlapped?
      If dtmDateNxt - CDate(txtDate(intIdx)) < .InterAnnlMin Then
         strPromt = strAffxNxt & dtmDateNxt & strAffxAct & txtDate(intIdx) & _
            LoadResString(345) & .InterAnnlMin & LoadResString(234) 'Too small interval.
         MsgBox strPromt, vbExclamation, LoadResString(131) 'Message & focus.
         txtDate(intIdx).SetFocus
      ElseIf dtmDateNxt - CDate(txtDate(intIdx)) > .InterAnnlMax Then
         strPromt = strAffxNxt & dtmDateNxt & strAffxAct & txtDate(intIdx) & _
            LoadResString(346) & .InterAnnlMax & LoadResString(590) 'Too big interval.
         If MsgBox(strPromt, vbYesNo + vbQuestion, LoadResString(342)) = vbNo Then 'Promt to correct.
            VldOvlpNxtAnnl = True 'Correction rejected.
         Else
            txtDate(intIdx).SetFocus
         End If
      Else
         VldOvlpNxtAnnl = True 'Succeeded.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the interval between the adjacent weighing & shearing, if both are filled.
' Return True, if succeeds.
Private Function VldWtWoolInter() As Boolean
On Error GoTo ErrHnd
   Const intInterMax As Integer = 90 'The maximial wt/wool interval.
   Dim lngInter As Long
   Dim blnFail As Boolean
   Dim strPromt As String
   If txtDate(miDateAnnl) <> "" And txtDate(miDateShearAnnl) <> "" Then 'Both filled?
      lngInter = Abs(CDate(txtDate(miDateAnnl)) - CDate(txtDate(miDateShearAnnl)))
      If lngInter > intInterMax Then
         blnFail = True 'Too big interval.
         strPromt = LoadResString(586) & lngInter & LoadResString(338) & txtDate( _
            miDateAnnl) & LoadResString(339) & txtDate(miDateShearAnnl) & _
            LoadResString(546) & intInterMax & LoadResString(234)
         MsgBox strPromt, vbExclamation, LoadResString(131)
         txtDate(miDateAnnl).SetFocus
      End If
   End If
   VldWtWoolInter = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the apprasals that they not ovrlap the annual interval with the previous &
'  next records in the Edit mode.
' Return True, if succeeds.
Private Function VldOvlpApprEdit() As Boolean
On Error GoTo ErrHnd
   Dim blnFail As Boolean
   With gobShGs(mobDatFrm.IDFrm).Apprs
      If .Count > 1 Then 'Proceed, if ther're other records to be overlapped.
         If .Act.Age > .First(True).Age Then blnFail = Not VldOvlpPrevAppr 'Validate towards the prev., unless it's the 1st.
         If blnFail = False And .Act.Age < .Last(True).Age Then 'Proceed unless it's the last & failed above.
            blnFail = Not VldOvlpNxtAnnl(miDateAppr, .Nxt(True).DateAppr, _
               LoadResString(364), LoadResString(365)) 'Validate towards the next appr.
         End If
      End If
   End With
   VldOvlpApprEdit = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the annual interval between the active appaisal & previous one.
' Return True, if succeeds.
Private Function VldOvlpPrevAppr() As Boolean
On Error GoTo ErrHnd
   Dim dtmDatePrev As Date
   Dim blnFail As Boolean
   Dim strPromt As String
   dtmDatePrev = gobShGs(mobDatFrm.IDFrm).Apprs.Prev(True).DateAppr 'The prev. date.
   With gobTblCtrlParam
      If CDate(txtDate(miDateAppr)) - dtmDatePrev < .InterAnnlMin Then
         blnFail = True 'Too small interval.
         strPromt = LoadResString(363) & dtmDatePrev & LoadResString(364) & txtDate( _
            miDateAppr) & LoadResString(345) & .InterAnnlMin & LoadResString(234)
         MsgBox strPromt, vbExclamation, LoadResString(131)
      ElseIf CDate(txtDate(miDateAppr)) - dtmDatePrev > .InterAnnlMax Then
         strPromt = LoadResString(363) & dtmDatePrev & LoadResString(364) & txtDate( _
            miDateAppr) & LoadResString(346) & .InterAnnlMax & LoadResString(590) 'Too big interval.
         If MsgBox(strPromt, vbYesNo + vbQuestion, LoadResString(342)) = vbYes Then _
            blnFail = True 'Promt to correct.
      End If
   End With
   If blnFail Then 'Focus.
      txtDate(miDateAppr).SetFocus
   Else 'Succeeded.
      VldOvlpPrevAppr = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the date of lambing/kidding in the Edit mode if the date changes that the
'  latter be consistent with the offsprings' dates of birth in the SheepGoat table.
' Return True, if all alive offsprings' dates are equal to the lamb/kidding date.
'  Ohterwise reject the change to make the user adjust the offspring's date of birth from
'  the Inven data form.
Private Function VldLmKOffsp() As Boolean
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim obShG As ShG
   Dim blnFail As Boolean
   Dim strPromt As String
   If mobDatFrm.Mode = gobSetng.ModeEdit Then 'Validate in the Edit mode.
      With gobShGs(mobDatFrm.IDFrm).Dam.LmKs.Act
         If CDate(txtDate(miDateLmK)) <> .DateLmKOrig Then 'Changed?
            If .Abort = vbUnchecked And .TypeBirth > 0 Then 'Proceed, unless zero (unnecessary but check).
               For Each obTblOffsp In .Offsps 'Loop through all ofssp's.
                  If obTblOffsp.IDLiv = gobSetng.Liv.IDLivAlive Then 'Alive?
                     Set obShG = New ShG
                     With obShG
                        .IDShG = obTblOffsp.IDLmK
                        If .Exists(True) Then 'Exists?
                           If .TblShG.DateBirth <> CDate(txtDate(miDateLmK)) Then 'Same birth date?
                              blnFail = True
                              strPromt = LoadResString(238) & .TblShG.DateBirth & _
                                 LoadResString(239) & obTblOffsp.IDLmK & _
                                 LoadResString(241) & txtDate(miDateLmK) & _
                                 LoadResString(242) & txtID(miDamLmK) & "'. " & String$ _
                                 (2, vbCrLf) & LoadResString(243)
                              MsgBox strPromt, vbExclamation, LoadResString(131)
                              txtDate(miDateLmK).SetFocus
                              Exit For 'Exit.
                           End If
                        End If
                     End With
                     Set obShG = Nothing 'Destroy.
                  End If
               Next
            End If
         End If
      End With
   End If
   VldLmKOffsp = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Unload the ShG's dam's frmShG data form, if loaded, which shows this frmShG data form's
'  ShG as LmK in the LmK data form's tab (& in the Mat tab's grid). Unloading is required
'  in order to delete the ShG or change its ID & sex.
' Return True, if succeeds.
Private Function DatFrmUnldDam() As Boolean
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   With gobShGs(mobDatFrm.IDFrm).TblShG
      If .IDDam <> "" Then 'Has dam?
         For Each obDatFrm In gobDatFrms
            If obDatFrm.IDFrm = .IDDam Then 'Look for the dam's data form.
               With obDatFrm.FrmHost
                  Call .UnldSyncMatLmK(gobSetng.FrmMatIdx) 'Unload matings.
                  Call .UnldSyncMatLmK(gobSetng.FrmLmKIdx) 'Unload lamb/kiddings.
               End With
            End If
         Next
      End If
   End With
   DatFrmUnldDam = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' The form's caption.
Private Property Get DatFrm_FrmHostCaptOrig() As String
   DatFrm_FrmHostCaptOrig = mstrFrmHostCapt
End Property

' The form's caption.
Private Property Let DatFrm_FrmHostCaptOrig(ByVal strFrmHostCapt As String)
   mstrFrmHostCapt = strFrmHostCapt
End Property

' Return True, if 1-yr weighing/shearing is being currentrly added. The procedure is
'  necessary for the TblSelIdxCC.VldPoplt procedure to encapsulate refrencing the tabShG tab
'  indexes.
Public Function Add1YrWtWool() As Boolean
On Error GoTo ErrHnd
   If mobDatFrm.Mode = gobSetng.ModeAdd Then
      If tabShG.SelectedItem.Index = gobSetng.FrmWtWoolIdx Then Add1YrWtWool = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if 1-yr appraisal is being currentrly added. The procedure is necessary for
'  the TblSelIdxCC.VldPoplt procedure to encapsulate refrencing the tabShG tab indexes.
Public Function Add1YrAppr() As Boolean
On Error GoTo ErrHnd
   If mobDatFrm.Mode = gobSetng.ModeAdd Then
      If tabShG.SelectedItem.Index = gobSetng.FrmApprIdx Then Add1YrAppr = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
