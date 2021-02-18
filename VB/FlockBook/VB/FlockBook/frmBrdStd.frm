VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "msadodc.ocx"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDatLst.ocx"
Object = "{86CF1D34-0C5F-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSComCt2.ocx"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TabCtl32.ocx"
Begin VB.Form frmBrdStd 
   Caption         =   "Породы и стандарты пород"
   ClientHeight    =   6240
   ClientLeft      =   2580
   ClientTop       =   1515
   ClientWidth     =   11460
   Icon            =   "frmBrdStd.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   6240
   ScaleWidth      =   11460
   Begin VB.TextBox txtIDBrd 
      Height          =   315
      Left            =   1200
      MaxLength       =   2
      TabIndex        =   3
      ToolTipText     =   "Заполните поле и нажмите Enter (дважды щёлкните по полю)"
      Top             =   720
      Width           =   855
   End
   Begin VB.Frame fraSpecies 
      Caption         =   "Вид животных"
      Height          =   735
      Left            =   240
      TabIndex        =   6
      Top             =   1740
      Width           =   3855
      Begin VB.OptionButton optSpecies 
         Caption         =   "Ко&зы"
         Height          =   255
         Index           =   1
         Left            =   2160
         TabIndex        =   8
         Top             =   360
         Width           =   855
      End
      Begin VB.OptionButton optSpecies 
         Caption         =   "Ов&цы"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Width           =   855
      End
   End
   Begin VB.TextBox txtBrd 
      Height          =   315
      Left            =   1200
      TabIndex        =   5
      Top             =   1200
      Width           =   2895
   End
   Begin VB.Frame fraWt 
      Caption         =   "Признаки, удельное влияние на селекц индекс"
      Height          =   2775
      Left            =   240
      TabIndex        =   9
      Top             =   2640
      Width           =   3855
      Begin MSComCtl2.UpDown updWtTrait 
         Height          =   315
         Index           =   4
         Left            =   3375
         TabIndex        =   24
         TabStop         =   0   'False
         Top             =   2280
         Width           =   240
         _ExtentX        =   423
         _ExtentY        =   556
         _Version        =   393216
         AutoBuddy       =   -1  'True
         BuddyControl    =   "txtWtTrait(4)"
         BuddyDispid     =   196614
         BuddyIndex      =   4
         OrigLeft        =   3480
         OrigTop         =   2280
         OrigRight       =   3720
         OrigBottom      =   2655
         Increment       =   5
         Max             =   100
         SyncBuddy       =   -1  'True
         BuddyProperty   =   0
         Enabled         =   -1  'True
      End
      Begin VB.TextBox txtWtTrait 
         Height          =   315
         Index           =   4
         Left            =   2520
         MaxLength       =   3
         TabIndex        =   23
         Top             =   2280
         Width           =   855
      End
      Begin MSComCtl2.UpDown updWtTrait 
         Height          =   315
         Index           =   3
         Left            =   3375
         TabIndex        =   21
         TabStop         =   0   'False
         Top             =   1800
         Width           =   240
         _ExtentX        =   423
         _ExtentY        =   556
         _Version        =   393216
         AutoBuddy       =   -1  'True
         BuddyControl    =   "txtWtTrait(3)"
         BuddyDispid     =   196614
         BuddyIndex      =   3
         OrigLeft        =   3480
         OrigTop         =   1800
         OrigRight       =   3720
         OrigBottom      =   2175
         Increment       =   5
         Max             =   100
         SyncBuddy       =   -1  'True
         BuddyProperty   =   0
         Enabled         =   -1  'True
      End
      Begin VB.TextBox txtWtTrait 
         Height          =   315
         Index           =   3
         Left            =   2520
         MaxLength       =   3
         TabIndex        =   20
         Top             =   1800
         Width           =   855
      End
      Begin MSComCtl2.UpDown updWtTrait 
         Height          =   315
         Index           =   2
         Left            =   3375
         TabIndex        =   18
         TabStop         =   0   'False
         Top             =   1320
         Width           =   240
         _ExtentX        =   423
         _ExtentY        =   556
         _Version        =   393216
         AutoBuddy       =   -1  'True
         BuddyControl    =   "txtWtTrait(2)"
         BuddyDispid     =   196614
         BuddyIndex      =   2
         OrigLeft        =   3480
         OrigTop         =   1320
         OrigRight       =   3720
         OrigBottom      =   1695
         Increment       =   5
         Max             =   100
         SyncBuddy       =   -1  'True
         BuddyProperty   =   0
         Enabled         =   -1  'True
      End
      Begin VB.TextBox txtWtTrait 
         Height          =   315
         Index           =   2
         Left            =   2520
         MaxLength       =   3
         TabIndex        =   17
         Top             =   1320
         Width           =   855
      End
      Begin MSComCtl2.UpDown updWtTrait 
         Height          =   315
         Index           =   1
         Left            =   3375
         TabIndex        =   15
         TabStop         =   0   'False
         Top             =   840
         Width           =   240
         _ExtentX        =   423
         _ExtentY        =   556
         _Version        =   393216
         AutoBuddy       =   -1  'True
         BuddyControl    =   "txtWtTrait(1)"
         BuddyDispid     =   196614
         BuddyIndex      =   1
         OrigLeft        =   3480
         OrigTop         =   840
         OrigRight       =   3720
         OrigBottom      =   1215
         Increment       =   5
         Max             =   100
         SyncBuddy       =   -1  'True
         BuddyProperty   =   0
         Enabled         =   -1  'True
      End
      Begin VB.TextBox txtWtTrait 
         Height          =   315
         Index           =   1
         Left            =   2520
         MaxLength       =   3
         TabIndex        =   14
         Top             =   840
         Width           =   855
      End
      Begin VB.TextBox txtWtTrait 
         Height          =   315
         Index           =   0
         Left            =   2520
         MaxLength       =   3
         TabIndex        =   11
         Top             =   360
         Width           =   855
      End
      Begin VB.CheckBox chkWtTrait 
         Caption         =   "Живая ма&сса, %:"
         Height          =   285
         Index           =   0
         Left            =   240
         TabIndex        =   10
         Top             =   360
         Width           =   1695
      End
      Begin VB.CheckBox chkWtTrait 
         Caption         =   "Наст&риг шерсти/пуха, %:"
         Height          =   285
         Index           =   1
         Left            =   240
         TabIndex        =   13
         Top             =   840
         Width           =   2295
      End
      Begin VB.CheckBox chkWtTrait 
         Caption         =   "Д&лина шерсти/пуха, %:"
         Height          =   285
         Index           =   2
         Left            =   240
         TabIndex        =   16
         Top             =   1320
         Width           =   2175
      End
      Begin VB.CheckBox chkWtTrait 
         Caption         =   "Тонин&а шерсти/пуха, %:"
         Height          =   285
         Index           =   3
         Left            =   240
         TabIndex        =   19
         Top             =   1800
         Width           =   2175
      End
      Begin VB.CheckBox chkWtTrait 
         Caption         =   "Оценка курд&юка, %:"
         Height          =   285
         Index           =   4
         Left            =   240
         TabIndex        =   22
         Top             =   2280
         Width           =   1935
      End
      Begin MSComCtl2.UpDown updWtTrait 
         Height          =   315
         Index           =   0
         Left            =   3375
         TabIndex        =   12
         TabStop         =   0   'False
         Top             =   360
         Width           =   240
         _ExtentX        =   423
         _ExtentY        =   556
         _Version        =   393216
         AutoBuddy       =   -1  'True
         BuddyControl    =   "txtWtTrait(0)"
         BuddyDispid     =   196614
         BuddyIndex      =   0
         OrigLeft        =   3480
         OrigTop         =   720
         OrigRight       =   3720
         OrigBottom      =   1035
         Increment       =   5
         Max             =   100
         SyncBuddy       =   -1  'True
         BuddyProperty   =   0
         Enabled         =   -1  'True
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
      ScaleWidth      =   11460
      TabIndex        =   168
      TabStop         =   0   'False
      Top             =   5505
      Width           =   11460
      Begin VB.CommandButton cmdOk 
         Caption         =   "&ОК"
         Height          =   375
         Left            =   8700
         TabIndex        =   169
         Top             =   240
         Width           =   1215
      End
      Begin VB.CommandButton cmdCancel 
         Cancel          =   -1  'True
         Caption         =   "Отмена"
         Height          =   375
         Left            =   10020
         TabIndex        =   170
         Top             =   240
         Width           =   1215
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000005&
         Index           =   1
         X1              =   0
         X2              =   11340
         Y1              =   15
         Y2              =   15
      End
      Begin VB.Line linBtn 
         BorderColor     =   &H80000010&
         Index           =   0
         X1              =   0
         X2              =   11340
         Y1              =   0
         Y2              =   0
      End
   End
   Begin TabDlg.SSTab tabBrdStd 
      Height          =   5235
      Left            =   4320
      TabIndex        =   25
      Top             =   180
      Width           =   6930
      _ExtentX        =   12224
      _ExtentY        =   9234
      _Version        =   393216
      Style           =   1
      Tabs            =   5
      Tab             =   3
      TabHeight       =   520
      TabCaption(0)   =   "Живая масса"
      TabPicture(0)   =   "frmBrdStd.frx":1042
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "fraCompClass(0)"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "fraSelIndx(0)"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "Настриг шерсти/пуха"
      TabPicture(1)   =   "frmBrdStd.frx":105E
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "fraSelIndx(1)"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "fraCompClass(1)"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).ControlCount=   2
      TabCaption(2)   =   "Длина шерсти/пуха"
      TabPicture(2)   =   "frmBrdStd.frx":107A
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "fraSelIndx(2)"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).Control(1)=   "fraCompClass(2)"
      Tab(2).Control(1).Enabled=   0   'False
      Tab(2).ControlCount=   2
      TabCaption(3)   =   "Тонина шерсти/пуха"
      TabPicture(3)   =   "frmBrdStd.frx":1096
      Tab(3).ControlEnabled=   -1  'True
      Tab(3).Control(0)=   "fraSelIndx(3)"
      Tab(3).Control(0).Enabled=   0   'False
      Tab(3).Control(1)=   "fraCompClass(3)"
      Tab(3).Control(1).Enabled=   0   'False
      Tab(3).ControlCount=   2
      TabCaption(4)   =   "Оценка курдюка"
      TabPicture(4)   =   "frmBrdStd.frx":10B2
      Tab(4).ControlEnabled=   0   'False
      Tab(4).Control(0)=   "fraSelIndx(4)"
      Tab(4).Control(0).Enabled=   0   'False
      Tab(4).Control(1)=   "fraCompClass(4)"
      Tab(4).Control(1).Enabled=   0   'False
      Tab(4).ControlCount=   2
      Begin VB.Frame fraCompClass 
         Caption         =   "Нижние пороги комплексной оценки"
         Height          =   1935
         Index           =   4
         Left            =   -74880
         TabIndex        =   157
         Top             =   3120
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraCompClassMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   4
            Left            =   120
            TabIndex        =   158
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   4
               Left            =   1920
               TabIndex        =   160
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   4
               Left            =   1920
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
               Caption         =   "adoFatTail"
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
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   5
               Left            =   1920
               TabIndex        =   162
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   5
               Left            =   1920
               Top             =   1200
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
               Caption         =   "adoFatTail"
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
            Begin VB.Label lblFatTail 
               Caption         =   "&1 Класс:"
               Height          =   255
               Index           =   5
               Left            =   240
               TabIndex        =   161
               Top             =   960
               Width           =   1095
            End
            Begin VB.Label lblFatTail 
               Caption         =   "&Элита:"
               Height          =   255
               Index           =   4
               Left            =   240
               TabIndex        =   159
               Top             =   480
               Width           =   855
            End
         End
         Begin VB.Frame fraCompClassFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   4
            Left            =   3360
            TabIndex        =   163
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   6
               Left            =   1920
               TabIndex        =   165
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   6
               Left            =   1920
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
               Caption         =   "adoFatTail"
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
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   7
               Left            =   1920
               TabIndex        =   167
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   7
               Left            =   1920
               Top             =   1200
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
               Caption         =   "adoFatTail"
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
            Begin VB.Label lblFatTail 
               Caption         =   "1 &Класс:"
               Height          =   255
               Index           =   7
               Left            =   240
               TabIndex        =   166
               Top             =   960
               Width           =   1095
            End
            Begin VB.Label lblFatTail 
               Caption         =   "Эли&та:"
               Height          =   255
               Index           =   6
               Left            =   240
               TabIndex        =   164
               Top             =   480
               Width           =   855
            End
         End
      End
      Begin VB.Frame fraSelIndx 
         Caption         =   "Верхний и нижний пороги селекционного индекса"
         Height          =   1935
         Index           =   4
         Left            =   -74880
         TabIndex        =   146
         Top             =   840
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraSelIndxMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   4
            Left            =   120
            TabIndex        =   147
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   0
               Left            =   1920
               TabIndex        =   149
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   0
               Left            =   1920
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
               Caption         =   "adoFatTail"
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
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   1
               Left            =   1920
               TabIndex        =   151
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   1
               Left            =   1920
               Top             =   1200
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
               Caption         =   "adoFatTail"
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
            Begin VB.Label lblFatTail 
               Caption         =   "&Верхний порог:"
               Height          =   255
               Index           =   0
               Left            =   240
               TabIndex        =   148
               Top             =   480
               Width           =   1455
            End
            Begin VB.Label lblFatTail 
               Caption         =   "Н&ижний порог:"
               Height          =   255
               Index           =   1
               Left            =   240
               TabIndex        =   150
               Top             =   960
               Width           =   1575
            End
         End
         Begin VB.Frame fraSelIndxFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   4
            Left            =   3360
            TabIndex        =   152
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   2
               Left            =   1920
               TabIndex        =   154
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   2
               Left            =   1920
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
               Caption         =   "adoFatTail"
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
            Begin MSDataListLib.DataCombo dbcFatTail 
               Height          =   315
               Index           =   3
               Left            =   1920
               TabIndex        =   156
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   975
               _ExtentX        =   1720
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoFatTail 
               Height          =   330
               Index           =   3
               Left            =   1920
               Top             =   1200
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
               Caption         =   "adoFatTail"
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
            Begin VB.Label lblFatTail 
               Caption         =   "В&ерхний порог:"
               Height          =   255
               Index           =   2
               Left            =   240
               TabIndex        =   153
               Top             =   480
               Width           =   1455
            End
            Begin VB.Label lblFatTail 
               Caption         =   "Ни&жний порог:"
               Height          =   255
               Index           =   3
               Left            =   240
               TabIndex        =   155
               Top             =   960
               Width           =   1575
            End
         End
      End
      Begin VB.Frame fraCompClass 
         Caption         =   "Нижние пороги комплексной оценки"
         Height          =   1935
         Index           =   3
         Left            =   120
         TabIndex        =   119
         Top             =   3120
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraCompClassFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   3
            Left            =   3360
            TabIndex        =   133
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   6
               Left            =   840
               TabIndex        =   135
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   6
               Left            =   840
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
               Caption         =   "adoDiam"
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
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   7
               Left            =   840
               TabIndex        =   141
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   7
               Left            =   840
               Top             =   1200
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
               Caption         =   "adoDiam"
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
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   7
               Left            =   1560
               TabIndex        =   142
               Top             =   960
               Width           =   375
            End
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   6
               Left            =   1560
               TabIndex        =   136
               Top             =   480
               Width           =   375
            End
            Begin VB.Label lblDiam 
               Caption         =   "1 &Класс:"
               Height          =   255
               Index           =   7
               Left            =   120
               TabIndex        =   140
               Top             =   975
               Width           =   855
            End
            Begin VB.Label lblDiam 
               Caption         =   "Эли&та:"
               Height          =   255
               Index           =   6
               Left            =   120
               TabIndex        =   134
               Top             =   480
               Width           =   615
            End
            Begin VB.Label lblDiamFrom 
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
               Index           =   7
               Left            =   1920
               TabIndex        =   143
               Top             =   960
               Width           =   405
            End
            Begin VB.Label lblDiamTo 
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
               Index           =   7
               Left            =   2520
               TabIndex        =   145
               Top             =   960
               Width           =   405
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   7
               Left            =   2340
               TabIndex        =   144
               Top             =   960
               Width           =   135
            End
            Begin VB.Label lblDiamFrom 
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
               Index           =   6
               Left            =   1920
               TabIndex        =   137
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamTo 
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
               Index           =   6
               Left            =   2520
               TabIndex        =   139
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   6
               Left            =   2340
               TabIndex        =   138
               Top             =   480
               Width           =   135
            End
         End
         Begin VB.Frame fraCompClassMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   3
            Left            =   120
            TabIndex        =   120
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   4
               Left            =   840
               TabIndex        =   122
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   4
               Left            =   840
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
               Caption         =   "adoDiam"
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
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   5
               Left            =   840
               TabIndex        =   128
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   5
               Left            =   840
               Top             =   1200
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
               Caption         =   "adoDiam"
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
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   5
               Left            =   1560
               TabIndex        =   129
               Top             =   960
               Width           =   375
            End
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   4
               Left            =   1560
               TabIndex        =   123
               Top             =   480
               Width           =   375
            End
            Begin VB.Label lblDiam 
               Caption         =   "&1 Класс:"
               Height          =   255
               Index           =   5
               Left            =   120
               TabIndex        =   127
               Top             =   960
               Width           =   855
            End
            Begin VB.Label lblDiam 
               Caption         =   "&Элита:"
               Height          =   255
               Index           =   4
               Left            =   120
               TabIndex        =   121
               Top             =   465
               Width           =   615
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   4
               Left            =   2340
               TabIndex        =   125
               Top             =   480
               Width           =   135
            End
            Begin VB.Label lblDiamTo 
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
               Index           =   4
               Left            =   2520
               TabIndex        =   126
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamFrom 
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
               Index           =   4
               Left            =   1920
               TabIndex        =   124
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   5
               Left            =   2340
               TabIndex        =   131
               Top             =   960
               Width           =   135
            End
            Begin VB.Label lblDiamTo 
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
               Left            =   2520
               TabIndex        =   132
               Top             =   960
               Width           =   405
            End
            Begin VB.Label lblDiamFrom 
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
               Left            =   1920
               TabIndex        =   130
               Top             =   960
               Width           =   405
            End
         End
      End
      Begin VB.Frame fraSelIndx 
         Caption         =   "Верхний и нижний пороги селекционного индекса"
         Height          =   1935
         Index           =   3
         Left            =   120
         TabIndex        =   92
         Top             =   840
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraSelIndxFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   3
            Left            =   3360
            TabIndex        =   106
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   2
               Left            =   840
               TabIndex        =   108
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   2
               Left            =   840
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
               Caption         =   "adoDiam"
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
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   3
               Left            =   840
               TabIndex        =   114
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   3
               Left            =   840
               Top             =   1200
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
               Caption         =   "adoDiam"
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
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   3
               Left            =   1560
               TabIndex        =   115
               Top             =   960
               Width           =   375
            End
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   2
               Left            =   1560
               TabIndex        =   109
               Top             =   480
               Width           =   375
            End
            Begin VB.Label lblDiam 
               Caption         =   "Ни&жний порог:"
               Height          =   375
               Index           =   3
               Left            =   120
               TabIndex        =   113
               Top             =   945
               Width           =   735
            End
            Begin VB.Label lblDiam 
               Caption         =   "В&ерхний порог:"
               Height          =   375
               Index           =   2
               Left            =   120
               TabIndex        =   107
               Top             =   465
               Width           =   855
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   2
               Left            =   2340
               TabIndex        =   111
               Top             =   480
               Width           =   135
            End
            Begin VB.Label lblDiamTo 
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
               Index           =   2
               Left            =   2520
               TabIndex        =   112
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamFrom 
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
               Index           =   2
               Left            =   1920
               TabIndex        =   110
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   3
               Left            =   2340
               TabIndex        =   117
               Top             =   960
               Width           =   135
            End
            Begin VB.Label lblDiamTo 
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
               Left            =   2520
               TabIndex        =   118
               Top             =   960
               Width           =   405
            End
            Begin VB.Label lblDiamFrom 
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
               Left            =   1920
               TabIndex        =   116
               Top             =   960
               Width           =   405
            End
         End
         Begin VB.Frame fraSelIndxMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   3
            Left            =   120
            TabIndex        =   93
            Top             =   360
            Width           =   3075
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   0
               Left            =   840
               TabIndex        =   95
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   480
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   0
               Left            =   840
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
               Caption         =   "adoDiam"
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
            Begin MSDataListLib.DataCombo dbcDiam 
               Height          =   315
               Index           =   1
               Left            =   840
               TabIndex        =   101
               TabStop         =   0   'False
               ToolTipText     =   "F4 - Открыть список"
               Top             =   960
               Width           =   675
               _ExtentX        =   1191
               _ExtentY        =   556
               _Version        =   393216
               Style           =   2
               ListField       =   ""
               BoundColumn     =   ""
               Text            =   ""
            End
            Begin MSAdodcLib.Adodc adoDiam 
               Height          =   330
               Index           =   1
               Left            =   840
               Top             =   1200
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
               Caption         =   "adoDiam"
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
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   1
               Left            =   1560
               TabIndex        =   102
               Top             =   960
               Width           =   375
            End
            Begin VB.Label lblDiamMcm 
               Caption         =   "мкн:"
               Height          =   255
               Index           =   0
               Left            =   1560
               TabIndex        =   96
               Top             =   480
               Width           =   375
            End
            Begin VB.Label lblDiamFrom 
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
               Index           =   1
               Left            =   1920
               TabIndex        =   103
               Top             =   960
               Width           =   405
            End
            Begin VB.Label lblDiamTo 
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
               Index           =   1
               Left            =   2520
               TabIndex        =   105
               Top             =   960
               Width           =   405
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   1
               Left            =   2340
               TabIndex        =   104
               Top             =   960
               Width           =   135
            End
            Begin VB.Label lblDiamFrom 
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
               Index           =   0
               Left            =   1920
               TabIndex        =   97
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamTo 
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
               Index           =   0
               Left            =   2520
               TabIndex        =   99
               Top             =   480
               Width           =   405
            End
            Begin VB.Label lblDiamHyph 
               Alignment       =   2  'Center
               Caption         =   "-"
               Height          =   255
               Index           =   0
               Left            =   2340
               TabIndex        =   98
               Top             =   480
               Width           =   135
            End
            Begin VB.Label lblDiam 
               Caption         =   "&Верхний порог:"
               Height          =   375
               Index           =   0
               Left            =   120
               TabIndex        =   94
               Top             =   465
               Width           =   855
            End
            Begin VB.Label lblDiam 
               Caption         =   "Н&ижний порог:"
               Height          =   375
               Index           =   1
               Left            =   120
               TabIndex        =   100
               Top             =   945
               Width           =   735
            End
         End
      End
      Begin VB.Frame fraCompClass 
         Caption         =   "Нижние пороги комплексной оценки"
         Height          =   1935
         Index           =   2
         Left            =   -74880
         TabIndex        =   81
         Top             =   3120
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraCompClassMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   2
            Left            =   120
            TabIndex        =   82
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   5
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   86
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   4
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   84
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblLeng 
               Caption         =   "&1 Класс, см:"
               Height          =   255
               Index           =   5
               Left            =   240
               TabIndex        =   85
               Top             =   960
               Width           =   1095
            End
            Begin VB.Label lblLeng 
               Caption         =   "&Элита, см:"
               Height          =   255
               Index           =   4
               Left            =   240
               TabIndex        =   83
               Top             =   480
               Width           =   855
            End
         End
         Begin VB.Frame fraCompClassFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   2
            Left            =   3360
            TabIndex        =   87
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   7
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   91
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   6
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   89
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblLeng 
               Caption         =   "1 &Класс, см:"
               Height          =   255
               Index           =   7
               Left            =   240
               TabIndex        =   90
               Top             =   960
               Width           =   1095
            End
            Begin VB.Label lblLeng 
               Caption         =   "Эли&та, см:"
               Height          =   255
               Index           =   6
               Left            =   240
               TabIndex        =   88
               Top             =   480
               Width           =   855
            End
         End
      End
      Begin VB.Frame fraSelIndx 
         Caption         =   "Верхний и нижний пороги селекционного индекса"
         Height          =   1935
         Index           =   2
         Left            =   -74880
         TabIndex        =   70
         Top             =   840
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraSelIndxMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   2
            Left            =   120
            TabIndex        =   71
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   1
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   75
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   0
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   73
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblLeng 
               Caption         =   "&Верхний порог, см:"
               Height          =   255
               Index           =   0
               Left            =   240
               TabIndex        =   72
               Top             =   480
               Width           =   1455
            End
            Begin VB.Label lblLeng 
               Caption         =   "Н&ижний порог, см:"
               Height          =   255
               Index           =   1
               Left            =   240
               TabIndex        =   74
               Top             =   960
               Width           =   1575
            End
         End
         Begin VB.Frame fraSelIndxFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   2
            Left            =   3360
            TabIndex        =   76
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   3
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   80
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtLeng 
               Height          =   315
               Index           =   2
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   78
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblLeng 
               Caption         =   "В&ерхний порог, см:"
               Height          =   255
               Index           =   2
               Left            =   240
               TabIndex        =   77
               Top             =   480
               Width           =   1455
            End
            Begin VB.Label lblLeng 
               Caption         =   "Ни&жний порог, см:"
               Height          =   255
               Index           =   3
               Left            =   240
               TabIndex        =   79
               Top             =   960
               Width           =   1575
            End
         End
      End
      Begin VB.Frame fraCompClass 
         Caption         =   "Нижние пороги комплексной оценки"
         Height          =   1935
         Index           =   1
         Left            =   -74880
         TabIndex        =   59
         Top             =   3120
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraCompClassMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   1
            Left            =   120
            TabIndex        =   60
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   5
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   64
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   4
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   62
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblGrease 
               Caption         =   "&1 Класс, кг:"
               Height          =   255
               Index           =   5
               Left            =   240
               TabIndex        =   63
               Top             =   960
               Width           =   1095
            End
            Begin VB.Label lblGrease 
               Caption         =   "&Элита, кг:"
               Height          =   255
               Index           =   4
               Left            =   240
               TabIndex        =   61
               Top             =   480
               Width           =   855
            End
         End
         Begin VB.Frame fraCompClassFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   1
            Left            =   3360
            TabIndex        =   65
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   7
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   69
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   6
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   67
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblGrease 
               Caption         =   "1 &Класс, кг:"
               Height          =   255
               Index           =   7
               Left            =   240
               TabIndex        =   68
               Top             =   960
               Width           =   1095
            End
            Begin VB.Label lblGrease 
               Caption         =   "Эли&та, кг:"
               Height          =   255
               Index           =   6
               Left            =   240
               TabIndex        =   66
               Top             =   480
               Width           =   855
            End
         End
      End
      Begin VB.Frame fraSelIndx 
         Caption         =   "Верхний и нижний пороги селекционного индекса"
         Height          =   1935
         Index           =   1
         Left            =   -74880
         TabIndex        =   48
         Top             =   840
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraSelIndxMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   1
            Left            =   120
            TabIndex        =   49
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   1
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   53
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   0
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   51
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblGrease 
               Caption         =   "&Верхний порог, кг:"
               Height          =   255
               Index           =   0
               Left            =   240
               TabIndex        =   50
               Top             =   480
               Width           =   1455
            End
            Begin VB.Label lblGrease 
               Caption         =   "Н&ижний порог, кг:"
               Height          =   255
               Index           =   1
               Left            =   240
               TabIndex        =   52
               Top             =   960
               Width           =   1575
            End
         End
         Begin VB.Frame fraSelIndxFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   1
            Left            =   3360
            TabIndex        =   54
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   3
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   58
               TabStop         =   0   'False
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtGrease 
               Height          =   315
               Index           =   2
               Left            =   1920
               MaxLength       =   4
               TabIndex        =   56
               TabStop         =   0   'False
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblGrease 
               Caption         =   "В&ерхний порог, кг:"
               Height          =   255
               Index           =   2
               Left            =   240
               TabIndex        =   55
               Top             =   480
               Width           =   1455
            End
            Begin VB.Label lblGrease 
               Caption         =   "Ни&жний порог, кг:"
               Height          =   255
               Index           =   3
               Left            =   240
               TabIndex        =   57
               Top             =   960
               Width           =   1575
            End
         End
      End
      Begin VB.Frame fraCompClass 
         Caption         =   "Нижние пороги комплексной оценки"
         Height          =   1935
         Index           =   0
         Left            =   -74880
         TabIndex        =   37
         Top             =   3120
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraCompClassFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   0
            Left            =   3360
            TabIndex        =   43
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   7
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   47
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   6
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   45
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblWt 
               Caption         =   "Эли&та, кг:"
               Height          =   255
               Index           =   6
               Left            =   240
               TabIndex        =   44
               Top             =   480
               Width           =   855
            End
            Begin VB.Label lblWt 
               Caption         =   "1 &Класс, кг:"
               Height          =   255
               Index           =   7
               Left            =   240
               TabIndex        =   46
               Top             =   960
               Width           =   1095
            End
         End
         Begin VB.Frame fraCompClassMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   0
            Left            =   120
            TabIndex        =   38
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   5
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   42
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   4
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   40
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblWt 
               Caption         =   "&Элита, кг:"
               Height          =   255
               Index           =   4
               Left            =   240
               TabIndex        =   39
               Top             =   480
               Width           =   855
            End
            Begin VB.Label lblWt 
               Caption         =   "&1 Класс, кг:"
               Height          =   255
               Index           =   5
               Left            =   240
               TabIndex        =   41
               Top             =   960
               Width           =   1095
            End
         End
      End
      Begin VB.Frame fraSelIndx 
         Caption         =   "Верхний и нижний пороги селекционного индекса"
         Height          =   1935
         Index           =   0
         Left            =   -74880
         TabIndex        =   26
         Top             =   840
         Visible         =   0   'False
         Width           =   6555
         Begin VB.Frame fraSelIndxFm 
            Caption         =   "Самки"
            Height          =   1455
            Index           =   0
            Left            =   3360
            TabIndex        =   32
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   3
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   36
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   2
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   34
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblWt 
               Caption         =   "Ни&жний порог, кг:"
               Height          =   255
               Index           =   3
               Left            =   240
               TabIndex        =   35
               Top             =   960
               Width           =   1575
            End
            Begin VB.Label lblWt 
               Caption         =   "В&ерхний порог, кг:"
               Height          =   255
               Index           =   2
               Left            =   240
               TabIndex        =   33
               Top             =   480
               Width           =   1455
            End
         End
         Begin VB.Frame fraSelIndxMl 
            Caption         =   "Самцы"
            Height          =   1455
            Index           =   0
            Left            =   120
            TabIndex        =   27
            Top             =   360
            Width           =   3075
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   1
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   31
               Top             =   960
               Width           =   975
            End
            Begin VB.TextBox txtWt 
               Height          =   315
               Index           =   0
               Left            =   1920
               MaxLength       =   5
               TabIndex        =   29
               Top             =   480
               Width           =   975
            End
            Begin VB.Label lblWt 
               Caption         =   "Н&ижний порог, кг:"
               Height          =   255
               Index           =   1
               Left            =   240
               TabIndex        =   30
               Top             =   960
               Width           =   1575
            End
            Begin VB.Label lblWt 
               Caption         =   "&Верхний порог, кг:"
               Height          =   255
               Index           =   0
               Left            =   240
               TabIndex        =   28
               Top             =   480
               Width           =   1455
            End
         End
      End
   End
   Begin MSDataListLib.DataCombo dbcBrdBrs 
      Height          =   315
      Left            =   1200
      TabIndex        =   1
      ToolTipText     =   "F4 - Открыть список"
      Top             =   240
      Width           =   2895
      _ExtentX        =   5106
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
   End
   Begin MSAdodcLib.Adodc adoBrdBrs 
      Height          =   330
      Left            =   1200
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
      RecordSource    =   "spSelect_Breeds_ID_B"
      Caption         =   "adoBrd"
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
   Begin VB.Label lblBrdBrs 
      Caption         =   "В&ыберите породу:"
      Height          =   405
      Left            =   240
      TabIndex        =   0
      Top             =   195
      Width           =   855
   End
   Begin VB.Label lblIDBrd 
      Caption         =   "Код &породы:"
      Height          =   405
      Left            =   240
      TabIndex        =   2
      Top             =   675
      Width           =   615
   End
   Begin VB.Label lblBrd 
      Caption         =   "&Название породы:"
      Height          =   375
      Left            =   240
      TabIndex        =   4
      Top             =   1170
      Width           =   855
   End
End
Attribute VB_Name = "frmBrdStd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Implements MsgRecip
Implements DatFrm
Implements SetngFrm

Const mintCtlCount As Integer = 8 'Count of the adoDiam, dbcDiam, lblDiamFrom, lblDiamTo,
                               'adoFatTail & dbcFatTail control collections.
Const mintCtlLbl As Integer = 0 'Lable mark.
Const mintCtlMebDbc As Integer = 1 'Mask edit box/combo box's mark.

Const mintTrtWt As Integer = 0 'Wt trait index.
Const mintTrtGrease As Integer = 1 'Grease trait index.
Const mintTrtLeng As Integer = 2 'Leng trait index.
Const mintTrtDiam As Integer = 3 'Diam trait index.
Const mintTrtFatTail As Integer = 4 'FatTail trait index.

Const mintFldIDBrd As Integer = 9 'IDBrd field index - not zero not to be consistent with
Const mintFldMlMax As Integer = 0 'MaleMax field index.        'the controls collections.
Const mintFldMlMin As Integer = 1 'MaleMin field index.
Const mintFldMlEl As Integer = 4 'MaleElite field index.
Const mintFldMlCl1 As Integer = 5 'MaleClass1 field index.
Const mintFldFmMax As Integer = 2 'FemaleMax field index.
Const mintFldFmMin As Integer = 3 'FemaleMin field index.
Const mintFldFmEl As Integer = 6 'FemaleElite field index.
Const mintFldFmCl1 As Integer = 7 'FemaleClass1 field index.

Dim WithEvents mobTblBrd As TblBrd
Attribute mobTblBrd.VB_VarHelpID = -1

Dim mcolMsgs As Collection
Dim mobDatFrm As DatFrm
Dim mudtDatFrm As DatFrmTp

Dim mobTblStdWt As TblStd
Dim mobTblStdGrease As TblStd
Dim mobTblStdLeng As TblStd
Dim mobTblStdDiam As TblStd
Dim mobTblStdFatTail As TblStd

Dim mblnRefrshBrd As Boolean

' Switch on/off the respective txtWtTrait, updWtTrait contorls & the respective tabBrdStd
'  tab's controls.
Private Sub chkWtTrait_Click(Index As Integer)
On Error GoTo ErrHnd
   Select Case chkWtTrait(Index)
   Case vbChecked
      Call SwchTraitCtl(Index, True) 'On.
   Case vbUnchecked
      Call SwchTraitCtl(Index, False) 'Off.
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the form, if it's clear.
' Cancel the changes.
' Clear the controls.
' Return the focus to txtIDBrd
Public Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If mobDatFrm.IsDirty Then 'Cancel.
      mobDatFrm.Cancel True
      Call InitTxt 'Initialise text boxes.
      txtIDBrd = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID.
      cmdCancel.SetFocus 'Focus cmdCancel to invoke the txtIDBrd's GotFocus proc.
      dbcBrdBrs.SetFocus
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the mode's operation.
' Clear contols in the Del mode.
' Return the focus to txtIDBrd.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   Dim intResp As Integer
   Dim strPromt As String
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit 'Validate 'data in an Add or Edit mode.
         If .Vld Then
            .FrmToDB
            .Cancel False
            dbcBrdBrs.SetFocus
         End If
      Case gobSetng.ModeDel 'The Del mode.
         strPromt = LoadResString(282) & txtIDBrd & "'?"
         Beep
         intResp = MsgBox(strPromt, vbYesNoCancel + vbQuestion, LoadResString(372))
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            .FrmToDB
            .Cancel True
            txtIDBrd = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID.
            dbcBrdBrs.SetFocus
         Case vbNo
            cmdOK.SetFocus
         Case vbCancel
            .Cancel True
            Call InitTxt 'Initialise text boxes.
Debug.Assert 0 = 1 'Verify dbcBrdBrs vs. txtIDBrd
            dbcBrdBrs.SetFocus
'            txtIDBrd.SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear the controls.
Private Sub DatFrm_CtlClear()
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   For Each ctlCtl In Me.Controls
      If TypeOf ctlCtl Is TextBox Then
         ctlCtl.Text = ""
      ElseIf TypeOf ctlCtl Is DataCombo Then
         ctlCtl.Text = ""
      ElseIf TypeOf ctlCtl Is CheckBox Then
         ctlCtl.Value = vbUnchecked
      ElseIf TypeOf ctlCtl Is OptionButton Then
         ctlCtl.Value = False
      End If
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the form's controls.
Private Sub DatFrm_CtlWrite()
On Error GoTo ErrHnd
   With mobTblBrd
      txtBrd = .Brd
      Select Case .IDSpcs 'Speices option control.
      Case gobSetng.IDSpcsSh 'Sheep.
         optSpecies(CInt(gobSetng.IDSpcsSh)) = True
      Case gobSetng.IDSpcsG 'Goat.
         optSpecies(CInt(gobSetng.IDSpcsG)) = True
      End Select
      If .WtWt > 0 Then 'Trait controls.
         chkWtTrait(mintTrtWt) = vbChecked
         txtWtTrait(mintTrtWt) = gobFormtCtl.NumFrac(.WtWt, True)
         Call StdWrite(txtWt, mobTblStdWt)
      End If
      If .WtGrease > 0 Then
         chkWtTrait(mintTrtGrease) = vbChecked
         txtWtTrait(mintTrtGrease) = gobFormtCtl.NumFrac(.WtGrease, True)
         Call StdWrite(txtGrease, mobTblStdGrease)
      End If
      If .WtLeng > 0 Then
         chkWtTrait(mintTrtLeng) = vbChecked
         txtWtTrait(mintTrtLeng) = gobFormtCtl.NumFrac(.WtLeng, True)
         Call StdWrite(txtLeng, mobTblStdLeng)
      End If
      If .WtDiam > 0 Then
         chkWtTrait(mintTrtDiam) = vbChecked
         txtWtTrait(mintTrtDiam) = gobFormtCtl.NumFrac(.WtDiam, True)
         Call StdWrite(dbcDiam, mobTblStdDiam)
      End If
      If .WtFatTail > 0 Then
         chkWtTrait(mintTrtFatTail) = vbChecked
         txtWtTrait(mintTrtFatTail) = gobFormtCtl.NumFrac(.WtFatTail, True)
         Call StdWrite(dbcFatTail, mobTblStdFatTail)
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the data from the form's controls.
Private Sub DatFrm_CtlRead()
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   Dim ctlCtl As Control
   Dim intTrt As Integer
   Dim intFld As Integer
   With mobTblBrd
      .IDBrd = Trim$(txtIDBrd) 'Breed ID.
      .Brd = Trim$(txtBrd) 'Breed name.
      .IDSpcs = IIf(optSpecies(CInt(gobSetng.IDSpcsSh)), gobSetng.IDSpcsSh, gobSetng _
         .IDSpcsG) 'Speices ID.
      For Each chkCtl In chkWtTrait 'Read the breed standards.
         Call StdReadTrtWt(chkCtl, intTrt) 'Read the trait weights.
         If chkCtl = vbChecked Then 'Proceed, if the trait is selected.
            With TblStdTrt(intTrt)
               .IDBrd = Trim$(txtIDBrd)
               For Each ctlCtl In ColCtl(intTrt, mintCtlMebDbc) 'Read the standard's fields.
                  Select Case intFld
                  Case mintFldMlMax
                     .MaleMax = ctlCtl
                  Case mintFldMlMin
                     .MaleMin = ctlCtl
                  Case mintFldMlEl
                     .MaleElite = ctlCtl
                  Case mintFldMlCl1
                     .MaleClass1 = ctlCtl
                  Case mintFldFmMax
                     .FemaleMax = ctlCtl
                  Case mintFldFmMin
                     .FemaleMin = ctlCtl
                  Case mintFldFmEl
                     .FemaleElite = ctlCtl
                  Case mintFldFmCl1
                     .FemaleClass1 = ctlCtl
                  End Select
                  intFld = intFld + 1 'Increase field index.
               Next
            End With
            intFld = 0 'Reset.
         End If
         intTrt = intTrt + 1 'Increase trait index.
      Next
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
    mudtDatFrm.FrmHostNam = strFrmHostNam
End Property

' Get the host form's name.
Private Property Get DatFrm_FrmHostNam() As String
    DatFrm_FrmHostNam = mudtDatFrm.FrmHostNam
End Property

' Get the ID control.
Private Property Get DatFrm_IDCtl() As TextBox
   Set DatFrm_IDCtl = txtIDBrd
End Property

' Let & IDShG to identify this data form.
' Remember the last ID.
Private Property Let DatFrm_IDFrm(ByVal strIDFrm As String)
    mudtDatFrm.IDFrm = strIDFrm
End Property

' Get IDFrm to identify this data form.
Private Property Get DatFrm_IDFrm() As String
    DatFrm_IDFrm = mudtDatFrm.IDFrm
End Property

' Implements or not the SetngFrm class.
Private Property Get DatFrm_IsSetngFrm() As Boolean
   DatFrm_IsSetngFrm = True
End Property

' Register the data form itself under a new ID. Delete it under the previous ID, if any,
'  & register under a new one.
Private Sub DatFrm_RegistFrm(ByVal strNewIDFrm As String, ByVal blnDelPrev As Boolean)
On Error GoTo ErrHnd
   If blnDelPrev Then gobDatFrms.Del mudtDatFrm.IDFrm, Me.Name 'Delete the DatFrm object.
   gobDatFrms.Add strNewIDFrm, Me.Name 'Register the form under the new ID.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Shwitch on/off the data form's controls depending on whether the txtIDBrd is filled.
Private Sub DatFrm_SwchCtlFill(ByVal blnEnable As Boolean, Optional ByVal blnEnableID _
   As Boolean)
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   For Each ctlCtl In Me.Controls 'Cycle through all controls to switch.
      If TypeOf ctlCtl Is Label And ctlCtl.Name = lblIDBrd.Name Then
         GoTo NextCtl 'Skip labels except ID one.
      ElseIf TypeOf ctlCtl Is Frame Then
         GoTo NextCtl 'Skip the frames.
      ElseIf TypeOf ctlCtl Is PictureBox Then
         GoTo NextCtl 'Skip the picture box.
      ElseIf TypeOf ctlCtl Is Line Then
         GoTo NextCtl 'Skip the line.
      Else
         Select Case ctlCtl.Name 'Switch on/off the ID control explicitly.
         Case txtIDBrd.Name
            ctlCtl.Enabled = blnEnableID 'ID control.
         Case dbcBrdBrs.Name, lblBrdBrs.Name
            ctlCtl.Enabled = Not blnEnable 'ID button - opposite to other controls.
         Case cmdCancel.Name
            GoTo NextCtl 'Skip cmdCancel.
         Case Else
            ctlCtl.Enabled = blnEnable 'Other controls.
         End Select
      End If
NextCtl:
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch controls by mode.
' Switch the controls to save a new ID.
Private Sub DatFrm_SwchCtlMode()
On Error GoTo ErrHnd
'   If mudtDatFrm.Swch Then
'      mudtDatFrm.Swch = False 'Reset.
'      mudtDatFrm.IDFrmChan = True 'Mark a change.
'      Call DatFrm_SwchCtlFill(False, True) 'Switch to save IDFrm.
'      txtIDBrd.SetFocus
'      lblBrdBrs.Enabled = False
'      dbcBrdBrs.Enabled = False
'      cmdOk.Enabled = True
'   Else
      Select Case mobDatFrm.Mode 'Switch by mode.
      Case gobSetng.ModeAdd
         Call DatFrm_SwchCtlFill(True, False)
         Call SwchTraitChk 'Switch the trait controls.
         txtBrd.SetFocus 'Focus the control next to IDCtl.
      Case gobSetng.ModeEdit
         Call DatFrm_SwchCtlFill(True, True)
         Call SwchTraitChk 'Switch the trait controls.
         txtIDBrd.SetFocus
      Case gobSetng.ModeDel
         txtIDBrd.Enabled = False
         dbcBrdBrs.Enabled = False
         cmdOK.Enabled = True
         cmdOK.SetFocus
      End Select
'   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the logical consistence of the inputted data.
' Return True, if succeeds.
Private Function DatFrm_Vld() As Boolean
On Error GoTo ErrHnd
   Dim intIdx As Integer
   If Trim$(txtIDBrd) = "" Then 'Define IDBrd.
      Call Util.MissParam(txtIDBrd, lblIDBrd) 'Message & focus.
   ElseIf txtBrd = "" Then 'Define Brd.
      Call Util.MissParam(txtBrd, lblBrd) 'Message & focus.
   ElseIf optSpecies(CInt(gobSetng.IDSpcsSh)) = False And optSpecies(CInt(gobSetng _
      .IDSpcsG)) = False Then 'Define the speces.
      MsgBox LoadResString(680), vbExclamation, LoadResString(21) 'Message w/o focusing.
   ElseIf Not VldTrait Then 'Select at least a single trait.
      Call Util.MissParam(chkWtTrait(mintTrtWt), , , LoadResString(681))
   ElseIf Not VldTraitPerc(intIdx) Then 'Assign non-zero percent to each selected trait.
      Call Util.MissParam(chkWtTrait(intIdx), chkWtTrait(intIdx).Caption) 'Focus & mesg
      intIdx = 0 'Reset.
   ElseIf Not VldTrait100(intIdx) Then 'Validate 100 per cent total.
      MsgBox LoadResString(682), vbExclamation, LoadResString(131) 'Message & focus.
      txtWtTrait(intIdx).SetFocus
      intIdx = 0 'Reset.
   Else
      DatFrm_Vld = VldStdCtl 'Define each selected standard.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Refresh the lblDiamFrom & lblDiamTo controls.
Private Sub dbcDiam_Change(Index As Integer)
On Error GoTo ErrHnd
   Call RefrshDiam(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del.
' Enable Esc.
Private Sub dbcDiam_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
         dbcDiam(Index).BoundText = ""
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
Private Sub dbcFatTail_KeyDown(Index As Integer, KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
         dbcFatTail(Index).BoundText = ""
      Case .CodeEsc
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Syncronise the txtIDBrd to this control.
Private Sub dbcBrdBrs_Change()
On Error GoTo ErrHnd
   txtIDBrd = dbcBrdBrs.BoundText
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Call the txtIDBrd_KeyPress procedure in the Edit/Del mode, if Enter is pressed.
Private Sub dbcBrdBrs_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   Call Util.IDCtlEnter(mobDatFrm, KeyAscii)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Del.
' Enable Esc.
Private Sub dbcBrdBrs_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   With gobFormtCtl
      Select Case KeyCode
      Case .CodeDel
         dbcBrdBrs.BoundText = ""
      Case .CodeEsc
         Call cmdCancel_Click
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the Edit tool bar's buttons & the Edit menu.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   Call frmMDI.SwchMnuMode(mobDatFrm.Mode)
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
   Const lngWdth As Long = 11580 '11460
   Const lngHght As Long = 6645 '6765
   Set mcolMsgs = New Collection 'Create module-level objects.
   Set mobTblBrd = New TblBrd
   Set mobTblStdWt = New TblStd
   mobTblStdWt.Std = mobTblStdWt.StdWt
   Set mobTblStdGrease = New TblStd
   mobTblStdGrease.Std = mobTblStdGrease.StdGrease
   Set mobTblStdLeng = New TblStd
   mobTblStdLeng.Std = mobTblStdLeng.StdLeng
   Set mobTblStdDiam = New TblStd
   mobTblStdDiam.Std = mobTblStdDiam.StdDiam
   Set mobTblStdFatTail = New TblStd
   mobTblStdFatTail.Std = mobTblStdFatTail.StdFatTail
   Set mobDatFrm = Me
   mobDatFrm.FrmHostCaptOrig = Me.Caption
   mobDatFrm.SwchCtlFill False, True
   Call InitCtl 'Initialise controls.
   Call InitTxt 'Initialise text boxes.
   txtIDBrd = gobDatFrms.IDFrmLast(Me.Name) 'Set the last ID.
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

' Save the window state, if changed & resize the linBtn lines.
Private Sub Form_Resize()
On Error GoTo ErrHnd
   gobSetng.FrmChldStat = Me.WindowState
   gobFormtCtl.ResizeLin Me, linBtn(0), linBtn(1)
   picBtn.ZOrder 0 'Keep picBtn on top.
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
   Call DatFrm_SwchCtlFill(False, True) 'Shwitch the controls.
   mobDatFrm.IsDirty = False
   mudtDatFrm.FrmFilld = False
   Call DatFrm_RegistFrm("", True) 'Re-register the data form.
   mudtDatFrm.IDFrm = "" 'THIS OPERATION LOOKS UNNECESSARY BUT KEEP IT EXPLICIT.
   If blnCtlClear Then Call DatFrm_CtlClear 'Clear the controls, if required.
   Call Util.FrmCapt(mobDatFrm, False) 'Reset the form's caption
   Call frmMDI.SwchMnuMode(mudtDatFrm.Mode) 'Switch the menu/tool bar buttons.
   gobMsgInst.Rest Me 'Reset gobMsgInst.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the controls' content to the the mobTblBrd & mobTblStd* objects.
' Roll back operations on the SQL server's error.
Private Sub DatFrm_FrmToDB()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim blnConfmChanID As Boolean
   gobDatFrms.UnldEmpt mudtDatFrm.IDFrm, mudtDatFrm.FrmHostNam
   Set obDatTbl = mobTblBrd
   gcnnConn.BeginTrans 'Begin transaction.
   If mudtDatFrm.Mode = gobSetng.ModeDel Then
      obDatTbl.Del 'Deletion.
   Else
      Call DatFrm_CtlRead 'Read the data.
      Select Case mudtDatFrm.Mode 'Accomplish the mode's opertation.
      Case gobSetng.ModeAdd 'Addition.
         obDatTbl.Ins
         If Not gobMsgInst.SQLErr(frmMDI.ActiveForm) Then Call FrmToDBAdd
      Case gobSetng.ModeEdit 'Edition.
         If ConfmChanID Then ' Confirm changing IDBrd, if so.
            obDatTbl.Upd
            If Not gobMsgInst.SQLErr(frmMDI.ActiveForm) Then Call FrmToDBEdit
         End If
      End Select
   End If
   If Not gobMsgInst.SQLErr(Me) Then 'Commint/rollback the transaction.
      gcnnConn.CommitTrans
   Else
      gcnnConn.RollbackTrans
   End If
   If mblnRefrshBrd Then
      mblnRefrshBrd = False 'Reset
      Call frmMDI.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Resume to close gcnnConn's transaction.
End Sub

Private Property Get DatFrm_Mode() As Integer
   DatFrm_Mode = mudtDatFrm.Mode
End Property

' Set the form's mode to the specified option unless there is unsaved data.
Private Sub DatFrm_ModeSet(ByVal intMode As Integer)
On Error GoTo ErrHnd
   mudtDatFrm.Mode = intMode
   Call frmMDI.SwchMnuMode(intMode)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub


' Display a pop-up File menu on the right-mouse click.
Private Sub fraCompClass_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraCompClassFm_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraCompClassMl_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraSelIndx_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraSelIndxFm_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraSelIndxMl_MouseUp(Index As Integer, Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraSpecies_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a pop-up File menu on the right-mouse click.
Private Sub fraWt_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh all settings-relevant Ado's.
Private Sub SetngFrm_RefrshAdo()
On Error GoTo ErrHnd
   adoBrdBrs.Refresh
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
   dbcBrdBrs = txtBrd
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

' Display the File menu as a pop-up menu.
Private Sub tabBrdStd_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   Call Util.FileMnu(Button)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtGrease_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtGrease(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtGrease_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl
      Cancel = Not .VldNum(txtGrease(Index), .MinGrease, .MaxGrease)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Press Enter.
Private Sub txtIDBrd_DblClick()
On Error GoTo ErrHnd
   Call txtIDBrd_KeyPress(gobFormtCtl.AscEnter)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtIDBrd_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtIDBrd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' To prevent beeping beyond the ID length, cancel the length restriction for Enter.
' On pressing F4 open the dbcBrdBrs.
Private Sub txtIDBrd_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If KeyCode = gobFormtCtl.AscEnter Then txtIDBrd.MaxLength = 0
'   gobFormtCtl.OpenAdjacnt KeyCode, dbcBrdBrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restore the length restriction, if it was canceled for Enter on the KeyDown event.
Private Sub txtIDBrd_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   If txtIDBrd.MaxLength = 0 Then txtIDBrd.MaxLength = gobFormtCtl.LengIDShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Call the mobDatFrm.IDCtlLostFoc procedure.
Private Sub txtIDBrd_LostFocus()
On Error GoTo ErrHnd
   mobDatFrm.IDCtlLostFoc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus, if fewer than 2 characters are inputted or if the field is left
'  blank in the Edit mode after changing the ID.
Private Sub txtIDBrd_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   If mudtDatFrm.FrmFilld And mobDatFrm.Mode = gobSetng.ModeEdit Then 'Must be full, if ID changed.
      gobFormtCtl.VldIDCtlBrd txtIDBrd, lblIDBrd, Cancel
   Else
      Cancel = Not gobFormtCtl.VldIDBrd(txtIDBrd, lblIDBrd)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtLeng_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtLeng(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtLeng_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl
      Cancel = Not gobFormtCtl.VldNum(txtLeng(Index), .MinLeng, .MaxLeng)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtWt_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtWt(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtWt_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   With gobFormtCtl
      Cancel = Not gobFormtCtl.VldNum(txtWt(Index), .MinWt1Yr, .MaxWt1Yr)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtWtTrait_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtWtTrait(Index)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtWtTrait_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   Cancel = Not gobFormtCtl.VldNum(txtWtTrait(Index), 0, gobSetng.Perc100, True)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Mark to refresh the list of breed ID's in the dbcBrdBrs combo box.
Private Sub mobTblBrd_RefrshBrd()
On Error GoTo ErrHnd
   mblnRefrshBrd = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mcolMsgs collection to the gobMsgInst object to read/write messages to the form
Private Property Get MsgRecip_Msgs() As Collection
   Set MsgRecip_Msgs = mcolMsgs
End Property

' Call the mobDatFrm.IDCtlPress procedure.
Private Sub txtIDBrd_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   mobDatFrm.IDCtlPress KeyAscii
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the DB to fill this form.
Private Sub DatFrm_DBtoFrm()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set obDatTbl = mobTblBrd
   With obDatTbl
      Select Case mudtDatFrm.Mode
      Case gobSetng.ModeAdd 'Add mode.
         .EscSelFail = True 'Cancel the Selection Failed message.
         .Sel mudtDatFrm.IDFrm 'Select the data.
         .EscSelFail = False 'Reset.
      Case gobSetng.ModeEdit, gobSetng.ModeDel 'Edit/Del mode
         Call DatFrm_CtlClear 'Clear & reinitialise the controls.
         Call InitTxt
         .Sel mudtDatFrm.IDFrm 'Select the data.
         If .Full Then 'Proceed, if full.
            Call StdSel 'Select the Breed Standards data.
            Call DatFrm_CtlWrite 'Fill the form.
         End If
      End Select
   End With
   Call Util.FrmCapt(mobDatFrm, True) 'Set the form's caption.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the form's controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   adoBrdBrs.ConnectionString = gcnnConn.ConnectionString 'ado's ConnectionString's.
   Call AdoCnnStr(adoDiam)
   Call AdoCnnStr(adoFatTail)
   Call Util.DbcSetRowSrc(dbcBrdBrs, adoBrdBrs, "IDBreed", "Breed") 'dbcBrdBrs data source.
   Call SrcColDbc
   Call RefrshDiam(, True, True) 'Clear lblDiamFrom & lblDiamTo until filled.
   tabBrdStd.Tab = mintTrtWt 'Show the 1st tab.
   Call SwchVisibleTabStop(mintTrtWt, True) 'Unhide the 1st tab's frames & switch TabStop's.
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

' Set the data sorce for the specified ado collection.
Private Sub AdoCnnStr(ByRef obColAdo As Object)
On Error GoTo ErrHnd
   Dim adoCtl As Adodc
   For Each adoCtl In obColAdo
      adoCtl.ConnectionString = gcnnConn.ConnectionString
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the data sorce for the data bound combos & diameter lables.
Private Sub SrcColDbc()
On Error GoTo ErrHnd
   Const strBoundColDiam As String = "Diam"
   Const strLstFldDiam As String = "Diam"
   Const strBoundColFatTail As String = "FatTail"
   Const strLstFldFatTail As String = "FatTail"
   Const strDatFldDiamFrom As String = "DiamFrom"
   Const strDatFldDiamTo As String = "DiamTo"
   Dim I As Integer
   For I = 0 To mintCtlCount - 1
      Call Util.DbcSetRowSrc(dbcDiam(I), adoDiam(I), strBoundColDiam, strLstFldDiam) 'dbcDiam.
      Call SrcLbl(lblDiamFrom(I), adoDiam(I), strDatFldDiamFrom) 'lblDiamFrom.
      Call SrcLbl(lblDiamTo(I), adoDiam(I), strDatFldDiamTo) 'lblDiamTo.
      Call Util.DbcSetRowSrc(dbcFatTail(I), adoFatTail(I), strBoundColFatTail, strLstFldFatTail)
   Next 'Above: 'dbcFatTail.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the data sorce for the specified data bound combo.
Private Sub SrcLbl(ByRef lblCtl As Label, ByRef adoCtl As Adodc, ByVal strDatFld _
   As String)
On Error GoTo ErrHnd
   Set lblCtl.DataSource = adoCtl
   lblCtl.DataField = strDatFld
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the lblDiamFrom & lblDiamTo controls by finding the selected diameter in the
'  adoDiam recordset.
' Look up either in a single Ado or in all together.
Private Sub RefrshDiam(Optional ByVal intIdx As Integer, Optional ByVal blnAll _
   As Boolean, Optional ByVal blnIgnorePrev As Boolean)
On Error GoTo ErrHnd
   Static strDiamPrev(mintCtlCount) As String
   Dim I As Integer
   If Not blnAll Then 'Single Ado.
      Call Util.RefrshDiamFrm(adoDiam(intIdx), dbcDiam(intIdx), strDiamPrev(intIdx), _
         blnIgnorePrev)
   Else 'All Ados.
      For I = 0 To mintCtlCount - 1
         Call Util.RefrshDiamFrm(adoDiam(I), dbcDiam(I), strDiamPrev(I), blnIgnorePrev)
      Next
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the respective txtWtTrait, updWtTrait contorls & the respective tabBrdStd tab's
'  controls.
Private Sub SwchTraitCtl(ByVal intIdx As Integer, ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   txtWtTrait(intIdx).Enabled = blnEnable
   updWtTrait(intIdx).Enabled = blnEnable
   Call SwchTraitCtlDo(ColCtl(intIdx, mintCtlLbl), blnEnable) 'Switch the tab lables &
   Call SwchTraitCtlDo(ColCtl(intIdx, mintCtlMebDbc), blnEnable) 'mask edit/combo boxes.
   If intIdx = mintTrtDiam Then 'Switch the diameter lables.
      Call SwchTraitCtlDo(lblDiamMcm, blnEnable)
      Call SwchTraitCtlDo(lblDiamFrom, blnEnable)
      Call SwchTraitCtlDo(lblDiamHyph, blnEnable)
      Call SwchTraitCtlDo(lblDiamTo, blnEnable)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified tab's collections of text boxes.
Private Sub SwchTraitCtlDo(ByRef obColCtl As Object, ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   For Each ctlCtl In obColCtl
      ctlCtl.Enabled = blnEnable
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select the Breed Standards data.
Private Sub StdSel()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   With mobTblBrd
      If .WtWt > 0 Then 'Wt.
         Set obDatTbl = mobTblStdWt
         obDatTbl.Sel mudtDatFrm.IDFrm
      End If
      If .WtGrease > 0 Then 'Grease.
         Set obDatTbl = mobTblStdGrease
         obDatTbl.Sel mudtDatFrm.IDFrm
      End If
      If .WtLeng > 0 Then 'Leng.
         Set obDatTbl = mobTblStdLeng
         obDatTbl.Sel mudtDatFrm.IDFrm
      End If
      If .WtDiam > 0 Then 'Diam.
         Set obDatTbl = mobTblStdDiam
         obDatTbl.Sel mudtDatFrm.IDFrm
      End If
      If .WtFatTail > 0 Then 'FatTail.
         Set obDatTbl = mobTblStdFatTail
         obDatTbl.Sel mudtDatFrm.IDFrm
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the forms' ID controls & number text boxes.
Private Sub InitTxt()
On Error GoTo ErrHnd
   txtIDBrd = gobDatFrms.IDFrmLast(Me.Name)
   Call InitTxtNum(txtWtTrait, True)
   Call InitTxtNum(txtWt, False)
   Call InitTxtNum(txtGrease, False)
   Call InitTxtNum(txtLeng, False)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the number text box collections.
Private Sub InitTxtNum(ByRef obColMaskEB As Object, ByVal blnNoFrac As Boolean)
On Error GoTo ErrHnd
   Dim txtCtl As TextBox
   For Each txtCtl In obColMaskEB
      txtCtl = gobFormtCtl.NumFrac(0, blnNoFrac)
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fiil the Breed Standards control collection.
Private Sub StdWrite(ByRef obColCtl As Object, ByVal obTblStdTrt As TblStd)
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   Dim intFld As Integer
   For Each ctlCtl In obColCtl 'Fill the control collection.
      With obTblStdTrt
         Select Case intFld 'Distinguish by field.
         Case mintFldMlMax
            Call StdWriteFld(ctlCtl, .MaleMax)
         Case mintFldMlMin
            Call StdWriteFld(ctlCtl, .MaleMin)
         Case mintFldMlEl
            Call StdWriteFld(ctlCtl, .MaleElite)
         Case mintFldMlCl1
            Call StdWriteFld(ctlCtl, .MaleClass1)
         Case mintFldFmMax
            Call StdWriteFld(ctlCtl, .FemaleMax)
         Case mintFldFmMin
            Call StdWriteFld(ctlCtl, .FemaleMin)
         Case mintFldFmEl
            Call StdWriteFld(ctlCtl, .FemaleElite)
         Case mintFldFmCl1
            Call StdWriteFld(ctlCtl, .FemaleClass1)
         End Select
      End With
      intFld = intFld + 1 'Increase.
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the specified control with the specified field's value. Format the control as
'  Single/String distingushing by trait.
Private Sub StdWriteFld(ByRef ctlCtl As Control, ByVal vntFldVal As Variant)
On Error GoTo ErrHnd
   If TypeOf ctlCtl Is TextBox Then
      ctlCtl = gobFormtCtl.NumFrac(CSng(vntFldVal))
   ElseIf TypeOf ctlCtl Is DataCombo Then
      ctlCtl = CStr(vntFldVal)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unhide the active tab's fraSelIndx & fraCompClass frames & unhide the previous tab's to
'  prevent confusing coinciding lable shortcuts in different tabs.
' Switch on the active tab's controls' TabStop's & switch off the previous tab's.
Private Sub tabBrdStd_Click(PreviousTab As Integer)
On Error GoTo ErrHnd
   Call SwchVisibleTabStop(tabBrdStd.Tab, True) 'Active.
   Call SwchVisibleTabStop(PreviousTab, False) 'Previous.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide/unhide the specified fraSelIndx & fraCompClass frames.
' Switch on/off the specified controls' TabStop's.
Private Sub SwchVisibleTabStop(ByVal intIdx As Integer, ByVal blnVisibleTabStop _
   As Boolean)
On Error GoTo ErrHnd
   fraSelIndx(intIdx).Visible = blnVisibleTabStop
   fraCompClass(intIdx).Visible = blnVisibleTabStop
   Dim ctlCtl As Control
   For Each ctlCtl In ColCtl(intIdx, mintCtlMebDbc)
      ctlCtl.TabStop = blnVisibleTabStop
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the specified by index lable/control collection in the tab control.
Private Property Get ColCtl(ByVal intTrt As Integer, ByVal intCtlTyp As Integer) _
   As Object
On Error GoTo ErrHnd
   Select Case intTrt 'Select the trait controls.
   Case mintTrtWt
      Set ColCtl = IIf(intCtlTyp = mintCtlLbl, lblWt, txtWt) 'Lable/text box.
   Case mintTrtGrease
      Set ColCtl = IIf(intCtlTyp = mintCtlLbl, lblGrease, txtGrease) 'Lable/text box.
   Case mintTrtLeng
      Set ColCtl = IIf(intCtlTyp = mintCtlLbl, lblLeng, txtLeng) 'Lable/text box.
   Case mintTrtDiam
      Set ColCtl = IIf(intCtlTyp = mintCtlLbl, lblDiam, dbcDiam) 'Lable/combo box.
   Case mintTrtFatTail
      Set ColCtl = IIf(intCtlTyp = mintCtlLbl, lblFatTail, dbcFatTail) 'Lable/combo box.
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Switch the trait controls depending on the chkWtTrait check boxes' values.
Private Sub SwchTraitChk()
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   Dim intIdx As Integer
   Dim blnEnable As Boolean
   For Each chkCtl In chkWtTrait
      blnEnable = IIf(chkCtl = vbChecked, True, False) 'Define the Enabled property.
      Call SwchTraitCtl(intIdx, blnEnable) 'Switch.
      intIdx = intIdx + 1 'Increase the index.
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtBrd_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtBrd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate that at least a single chkWtTrait check box be selected.
' Return True, if succeeds.
Private Function VldTrait() As Boolean
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   For Each chkCtl In chkWtTrait
      If chkCtl = vbChecked Then
         VldTrait = True 'Succeeded.
         Exit For
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that each selected trait be assigned non-zero percent.
' Return True, if succeeds, otherwise return the index of the blank text box to
'  focus in the DatFrm_Vld procedure.
Private Function VldTraitPerc(ByRef intIdx As Integer) As Boolean
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   Dim blnFail As Boolean
   For Each chkCtl In chkWtTrait
      If chkCtl = vbChecked Then 'Check the selected trait wt.
'         If Trim$(txtWtTrait(intIdx)) = "" Then
         If gobFormtCtl.BlankNum(txtWtTrait(intIdx)) Then
            blnFail = True 'Failed.
            Exit For
         End If
      End If
      intIdx = intIdx + 1 'Increase.
   Next
   VldTraitPerc = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate 100 per cent sum of the selected traits' weights.
' Return True, if succeeds, otherwise return the index of the 1st full text box to
'  focus in the DatFrm_Vld procedure.
Private Function VldTrait100(ByRef intIdx As Integer) As Boolean
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   Dim intTotal As Integer
   Dim blnPassed As Boolean
   Dim I As Integer
   For Each chkCtl In chkWtTrait
      If chkCtl = vbChecked Then 'Preceed, if selected.
         If Not blnPassed Then
            blnPassed = True
            intIdx = I 'Remember the 1st selected check box's index.
         End If
         intTotal = intTotal + CInt(txtWtTrait(I)) 'Total.
      End If
      I = I + 1 'Increase.
   Next
   VldTrait100 = IIf(intTotal = gobSetng.Perc100, True, False) 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that each selected trait's standard control in the tab control be filled.
' Return True, if succeeds.
Private Function VldStdCtl() As Boolean
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   Dim ctlCtl As Control
   Dim intTrt As Integer
   Dim intFld As Integer
   Dim blnFail As Boolean
   For Each chkCtl In chkWtTrait
      If chkCtl = vbChecked Then 'Preceed, if selected.
         For Each ctlCtl In ColCtl(intTrt, mintCtlMebDbc) 'Loop through collection.
            If TypeOf ctlCtl Is TextBox Then
'               If Trim$(ctlCtl.Text) Then
               If gobFormtCtl.BlankNum(ctlCtl.Text) Then
                  Call FocTabMsg(ctlCtl, intTrt, intFld) 'Message & focus.
                  blnFail = True 'Failed.
                  Exit For 'Exit.
               End If
            ElseIf TypeOf ctlCtl Is DataCombo Then
               If ctlCtl.BoundText = "" Then
                  Call FocTabMsg(ctlCtl, intTrt, intFld) 'Message & focus.
                  blnFail = True 'Failed.
                  Exit For 'Exit.
               End If
            End If
         intFld = intFld + 1 'Increase field index.
         Next
         intFld = 0 'Reset
      End If
      If blnFail Then Exit For 'Exit, if failed above.
      intTrt = intTrt + 1 'Increase trait index.
   Next
   VldStdCtl = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the specified trait's standard table by index.
Private Property Get TblStdTrt(ByVal intTrt As Integer) As TblStd
On Error GoTo ErrHnd
   Select Case intTrt 'Select the table.
   Case mintTrtWt
      Set TblStdTrt = mobTblStdWt
   Case mintTrtGrease
      Set TblStdTrt = mobTblStdGrease
   Case mintTrtLeng
      Set TblStdTrt = mobTblStdLeng
   Case mintTrtDiam
      Set TblStdTrt = mobTblStdDiam
   Case mintTrtFatTail
      Set TblStdTrt = mobTblStdFatTail
   End Select
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Read from the specified control. Format the control as Single/String by trait.
Private Sub StdRead(ByRef ctlCtl As Control, ByRef vntFld As Variant)
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify the missing MaskEdBox
   If TypeOf ctlCtl Is TextBox Then
      vntFld = CSng(ctlCtl.Text)
   ElseIf TypeOf ctlCtl Is DataCombo Then
      vntFld = CStr(ctlCtl.BoundText)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert selected traits' breed standards to the DB.
Private Sub FrmToDBAdd()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim chkCtl As CheckBox
   Dim intTrt As Integer
   For Each chkCtl In chkWtTrait
      If chkCtl = vbChecked Then 'Proceed, if selected.
         Set obDatTbl = TblStdTrt(intTrt) 'Insert.
         obDatTbl.Ins
      End If
      intTrt = intTrt + 1 'Increase trait index.
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Complete the DatFrm_FrmToDB procedure's operation in the Edit mode as follows:
'  - insert, if a trait is selected & there was no record in the DB;
'  - update, if a trait is selected & there was a record in the DB;
'  - delete, if a trait is deselected & there was a record in the DB.
Private Sub FrmToDBEdit()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim chkCtl As CheckBox
   Dim intTrt As Integer
   For Each chkCtl In chkWtTrait
      Set obDatTbl = TblStdTrt(intTrt) 'Get the data table.
      With obDatTbl
         Select Case chkCtl 'Update/insert.
         Case vbChecked
            Select Case .Full
            Case True 'Update the previous record.
               .Upd
            Case False 'Insert the new record.
               .Ins
            End Select
         Case vbUnchecked 'Delete the previous record, if any.
            If .Full Then .Del
         End Select
      End With
      intTrt = intTrt + 1 'Increase trait index.
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select the specified tab, focus the validation-failed control & message the error
'  occurred in the VldStdCtl procedure.
Private Sub FocTabMsg(ByRef ctlCtl As Control, ByVal intTrt As Integer, ByVal intFld _
   As Integer)
On Error GoTo ErrHnd
   tabBrdStd.Tab = intTrt
   Call Util.MissParam(ctlCtl, ColCtl(intTrt, mintCtlLbl)(intFld).Caption)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the trait weights from the chkWtTrait check boxes & write to the mobTblBrd object.
Private Sub StdReadTrtWt(ByVal chkCtl As CheckBox, ByVal intTrt As Integer)
On Error GoTo ErrHnd
   With mobTblBrd
      Select Case intTrt 'Select the trait.
      Case mintTrtWt
         .WtWt = CInt(IIf(chkCtl = vbChecked, txtWtTrait(intTrt), 0))
      Case mintTrtGrease
         .WtGrease = CInt(IIf(chkCtl = vbChecked, txtWtTrait(intTrt), 0))
      Case mintTrtLeng
         .WtLeng = CInt(IIf(chkCtl = vbChecked, txtWtTrait(intTrt), 0))
      Case mintTrtDiam
         .WtDiam = CInt(IIf(chkCtl = vbChecked, txtWtTrait(intTrt), 0))
      Case mintTrtFatTail
         .WtFatTail = CInt(IIf(chkCtl = vbChecked, txtWtTrait(intTrt), 0))
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Confirm changing IDBrd.
' Return True, if either confirmed or no change took place.
' If the change is denied restore the previous IDFrm in the DatFrm_IDCtl control just to
'  show it to the user.
Private Function ConfmChanID() As Boolean
On Error GoTo ErrHnd
   Dim intResp As Integer
   If Trim$(txtIDBrd) = mobDatFrm.IDFrm Then
      ConfmChanID = True 'The same ID - confirmation is unnecessary.
   Else
      Beep
      intResp = MsgBox(LoadResString(283) & mobDatFrm.IDFrm & LoadResString(311) & _
         txtIDBrd & "'?", vbYesNo + vbQuestion, LoadResString(371)) 'Confirm.
      If intResp = vbYes Then
            ConfmChanID = True
      Else 'Denied - restore.
         txtIDBrd = mobDatFrm.IDFrm
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Let & get IsDirty.
Private Property Let DatFrm_IsDirty(ByVal blnIsDirty As Boolean)
   mudtDatFrm.IsDirty = blnIsDirty
End Property

Private Property Get DatFrm_IsDirty() As Boolean
   DatFrm_IsDirty = mudtDatFrm.IsDirty
End Property

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the control.
' Switch the controls to save a new ID, if it's being changed.
' Fill the form & begin the mode's operation.
Private Sub DatFrm_IDCtlPress(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim intLeng As Integer
   Dim blnFail As Boolean
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm) 'Set the menu & IsDirty mark.
      If intKeyAscii <> gobFormtCtl.AscEnter Then
         intKeyAscii = gobFormtCtl.UpCase(intKeyAscii) ' Type in upper case.
         dbcBrdBrs = "" 'Clear dbcBrdBrs.
      Else
         intKeyAscii = 0 'Cancel Enter
         If Not mudtDatFrm.FrmFilld Then 'Proceed, unless filled.
            intLeng = Len(Trim$(txtIDBrd))
            If intLeng = 0 Then
               .Cancel False 'Cancel the changes.
               txtIDBrd.SetFocus
            ElseIf intLeng = gobFormtCtl.LengIDBrd Then 'Proceed corresponding to the mode.
               .RegistFrm Trim$(txtIDBrd), True  'Register the form.
               If gobMsgInst.DuplFrm Then 'Avoid duplication by ivoking the LostFocus
                  cmdCancel.SetFocus      'procedure.
               Else
                  .DBtoFrm 'Fill the form in an Edit/Del mode.
                  Set obDatTbl = mobTblBrd
                  Select Case mobDatFrm.Mode 'Check the operation's feedback by mode.
                  Case gobSetng.ModeEdit, gobSetng.ModeDel 'Edit/Del modes.
                     If obDatTbl.Full Then
                        mudtDatFrm.FrmFilld = True 'Mark filling the form.
                     Else
                        blnFail = True 'Mark the error.
                     End If
                  Case gobSetng.ModeAdd 'Add mode.
                     If obDatTbl.Full Then 'Adding a duplicate IDBrd.
                        blnFail = True 'Mark the error.
                        MsgBox LoadResString(73), vbExclamation, LoadResString(50)
                     End If
                  End Select
                  If Not blnFail Then
                     Call Util.SyncBrs(mobDatFrm) 'Syncronise the settings form's browsing list.
                     .SwchCtlMode 'Switch controls by mode.
                  Else
                     .Cancel False 'Cancel the current changes, if any.
                     txtIDBrd.SetFocus
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

' Prevent a duplication.
' Reset the gobMsgInst object for later use.
' Unless the Util.DuplFrmtRest procedure unloads the form complete switching the
'  controls in the Edit mode after filling the form to restrict the access to the this
'  control until saving or canceling.
Private Sub DatFrm_IDCtlLostFoc()
On Error GoTo ErrHnd
   Call Util.DuplFrmtRest(Me, txtIDBrd)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' The form's caption.
Private Property Get DatFrm_FrmHostCaptOrig() As String
   DatFrm_FrmHostCaptOrig = mudtDatFrm.FrmHostCaptOrig
End Property

' The form's caption.
Private Property Let DatFrm_FrmHostCaptOrig(ByVal strFrmHostCapt As String)
   mudtDatFrm.FrmHostCaptOrig = strFrmHostCapt
End Property

