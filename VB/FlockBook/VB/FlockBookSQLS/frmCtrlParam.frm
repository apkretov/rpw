VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmCtrlParam 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Контрольные параметры"
   ClientHeight    =   7050
   ClientLeft      =   1095
   ClientTop       =   330
   ClientWidth     =   6720
   Icon            =   "frmCtrlParam.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7050
   ScaleWidth      =   6720
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox picBtn 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   510
      Left            =   0
      ScaleHeight     =   510
      ScaleWidth      =   6720
      TabIndex        =   53
      TabStop         =   0   'False
      Top             =   6540
      Width           =   6720
      Begin VB.CommandButton cmdApply 
         Caption         =   "&Применить"
         Height          =   375
         Left            =   4080
         TabIndex        =   55
         Top             =   0
         Width           =   1215
      End
      Begin VB.CommandButton cmdCancel 
         Cancel          =   -1  'True
         Caption         =   "Отмена"
         Height          =   375
         Left            =   5400
         TabIndex        =   56
         Top             =   0
         Width           =   1215
      End
      Begin VB.CommandButton cmdOk 
         Caption         =   "&ОК"
         Height          =   375
         Left            =   2760
         TabIndex        =   54
         Top             =   0
         Width           =   1215
      End
   End
   Begin TabDlg.SSTab tabCtrlParam 
      Height          =   6315
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6510
      _ExtentX        =   11483
      _ExtentY        =   11139
      _Version        =   393216
      Style           =   1
      TabsPerRow      =   5
      TabHeight       =   520
      TabCaption(0)   =   "Возраста"
      TabPicture(0)   =   "frmCtrlParam.frx":1042
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "lblFields(10)"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "fraFrames(0)"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "fraFrames(1)"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "fraFrames(2)"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "fraFrames(5)"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "txtFields(10)"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).ControlCount=   6
      TabCaption(1)   =   "Интервалы"
      TabPicture(1)   =   "frmCtrlParam.frx":105E
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "fraFrames(6)"
      Tab(1).Control(1)=   "fraFrames(7)"
      Tab(1).ControlCount=   2
      TabCaption(2)   =   "Общие"
      TabPicture(2)   =   "frmCtrlParam.frx":107A
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "lblFields(16)"
      Tab(2).Control(1)=   "txtFields(16)"
      Tab(2).Control(1).Enabled=   0   'False
      Tab(2).Control(2)=   "fraFrames(8)"
      Tab(2).Control(3)=   "fraFrames(10)"
      Tab(2).ControlCount=   4
      Begin VB.Frame fraFrames 
         Caption         =   "Период расчёта оценки баранов/козлов по качеству потомства"
         Height          =   1575
         Index           =   10
         Left            =   -74880
         TabIndex        =   47
         Top             =   3600
         Visible         =   0   'False
         Width           =   6255
         Begin VB.OptionButton optFields 
            Caption         =   "Вся &жизнь"
            Height          =   255
            Index           =   2
            Left            =   360
            TabIndex        =   48
            TabStop         =   0   'False
            Top             =   480
            Width           =   1215
         End
         Begin VB.OptionButton optFields 
            Caption         =   "Последние &годы:"
            Height          =   255
            Index           =   3
            Left            =   360
            TabIndex        =   49
            TabStop         =   0   'False
            Top             =   960
            Width           =   1695
         End
         Begin VB.TextBox txtFields 
            Enabled         =   0   'False
            Height          =   315
            Index           =   17
            Left            =   3000
            MaxLength       =   3
            TabIndex        =   50
            TabStop         =   0   'False
            Top             =   960
            Width           =   975
         End
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Составление кода помесной породы приплода при ягнении/козлении"
         Height          =   2775
         Index           =   8
         Left            =   -74880
         TabIndex        =   42
         Top             =   480
         Visible         =   0   'False
         Width           =   6255
         Begin VB.CheckBox chkFields 
            Caption         =   "Преобразовывать помесную породу в &чистопородную"
            Height          =   285
            Index           =   1
            Left            =   360
            TabIndex        =   46
            TabStop         =   0   'False
            Top             =   2160
            Value           =   2  'Grayed
            Width           =   4455
         End
         Begin VB.Frame fraFrames 
            Caption         =   "Принимать в качестве базовой породы"
            Height          =   1455
            Index           =   9
            Left            =   120
            TabIndex        =   43
            Top             =   480
            Width           =   4215
            Begin VB.OptionButton optFields 
               Caption         =   "Базовую породу &матери"
               Height          =   255
               Index           =   1
               Left            =   360
               TabIndex        =   45
               TabStop         =   0   'False
               Top             =   960
               Width           =   2175
            End
            Begin VB.OptionButton optFields 
               Caption         =   "Базовую породу от&ца"
               Height          =   255
               Index           =   0
               Left            =   360
               TabIndex        =   44
               TabStop         =   0   'False
               Top             =   480
               Width           =   2175
            End
         End
      End
      Begin VB.TextBox txtFields 
         Height          =   315
         Index           =   16
         Left            =   -70920
         MaxLength       =   3
         TabIndex        =   52
         TabStop         =   0   'False
         Top             =   5640
         Visible         =   0   'False
         Width           =   975
      End
      Begin VB.TextBox txtFields 
         Height          =   315
         Index           =   10
         Left            =   3480
         MaxLength       =   3
         TabIndex        =   29
         Top             =   5640
         Visible         =   0   'False
         Width           =   975
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Интервал между ежегодными замерами"
         Height          =   1335
         Index           =   7
         Left            =   -74880
         TabIndex        =   37
         Top             =   3480
         Visible         =   0   'False
         Width           =   6255
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   15
            Left            =   5040
            MaxLength       =   3
            TabIndex        =   41
            TabStop         =   0   'False
            Top             =   600
            Width           =   975
         End
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   14
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   39
            TabStop         =   0   'False
            Top             =   600
            Width           =   975
         End
         Begin VB.Label lblFields 
            Caption         =   "Н&аименьший, дни:"
            Height          =   255
            Index           =   14
            Left            =   240
            TabIndex        =   38
            Top             =   600
            Width           =   1455
         End
         Begin VB.Label lblFields 
            Caption         =   "На&ибольший, дни:"
            Height          =   255
            Index           =   15
            Left            =   3360
            TabIndex        =   40
            Top             =   600
            Width           =   1455
         End
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Интервал между случкой и ягнением/козлением"
         Height          =   2415
         Index           =   6
         Left            =   -74880
         TabIndex        =   30
         Top             =   480
         Visible         =   0   'False
         Width           =   6255
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   13
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   36
            TabStop         =   0   'False
            Top             =   1800
            Width           =   975
         End
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   12
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   34
            TabStop         =   0   'False
            Top             =   1200
            Width           =   975
         End
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   11
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   32
            TabStop         =   0   'False
            Top             =   600
            Width           =   975
         End
         Begin VB.Label lblFields 
            Caption         =   "Наи&меньший, дни:"
            Height          =   255
            Index           =   11
            Left            =   240
            TabIndex        =   31
            Top             =   600
            Width           =   1575
         End
         Begin VB.Label lblFields 
            Caption         =   "Наи&больший, дни:"
            Height          =   255
            Index           =   13
            Left            =   240
            TabIndex        =   35
            Top             =   1800
            Width           =   1455
         End
         Begin VB.Label lblFields 
            Caption         =   "&Нормальный, дни:"
            Height          =   255
            Index           =   12
            Left            =   240
            TabIndex        =   33
            Top             =   1200
            Width           =   1455
         End
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Наименьший возраст для случки"
         Height          =   855
         Index           =   5
         Left            =   120
         TabIndex        =   23
         Top             =   4440
         Visible         =   0   'False
         Width           =   6255
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   9
            Left            =   5040
            MaxLength       =   3
            TabIndex        =   27
            Top             =   360
            Width           =   975
         End
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   8
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   25
            Top             =   360
            Width           =   975
         End
         Begin VB.Label lblFields 
            Caption         =   "Ов&цематки/ козоматки, дни:"
            Height          =   375
            Index           =   9
            Left            =   3360
            TabIndex        =   26
            Top             =   300
            Width           =   1335
         End
         Begin VB.Label lblFields 
            Caption         =   "&Барана/козла, дни:"
            Height          =   255
            Index           =   8
            Left            =   240
            TabIndex        =   24
            Top             =   390
            Width           =   1575
         End
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Возраст в 1 год"
         Height          =   2175
         Index           =   2
         Left            =   120
         TabIndex        =   11
         Top             =   2040
         Visible         =   0   'False
         Width           =   6255
         Begin VB.Frame fraFrames 
            Caption         =   "При взвешивании"
            Height          =   1335
            Index           =   3
            Left            =   240
            TabIndex        =   13
            Top             =   720
            Width           =   2775
            Begin VB.TextBox txtFields 
               Enabled         =   0   'False
               Height          =   315
               Index           =   5
               Left            =   1680
               MaxLength       =   3
               TabIndex        =   17
               Top             =   840
               Width           =   975
            End
            Begin VB.TextBox txtFields 
               Enabled         =   0   'False
               Height          =   315
               Index           =   4
               Left            =   1680
               MaxLength       =   3
               TabIndex        =   15
               Top             =   360
               Width           =   975
            End
            Begin VB.Label lblFields 
               Caption         =   "Наи&меньший, дни:"
               Height          =   255
               Index           =   4
               Left            =   120
               TabIndex        =   14
               Top             =   390
               Width           =   1455
            End
            Begin VB.Label lblFields 
               Caption         =   "Наибол&ьший, дни:"
               Height          =   255
               Index           =   5
               Left            =   120
               TabIndex        =   16
               Top             =   870
               Width           =   1455
            End
         End
         Begin VB.Frame fraFrames 
            Caption         =   "Во время стрижки"
            Height          =   1335
            Index           =   4
            Left            =   3240
            TabIndex        =   18
            Top             =   720
            Width           =   2895
            Begin VB.TextBox txtFields 
               Enabled         =   0   'False
               Height          =   315
               Index           =   7
               Left            =   1800
               MaxLength       =   3
               TabIndex        =   22
               Top             =   840
               Width           =   975
            End
            Begin VB.TextBox txtFields 
               Enabled         =   0   'False
               Height          =   315
               Index           =   6
               Left            =   1800
               MaxLength       =   3
               TabIndex        =   20
               Top             =   360
               Width           =   975
            End
            Begin VB.Label lblFields 
               Caption         =   "Наим&еньший, дни:"
               Height          =   255
               Index           =   6
               Left            =   120
               TabIndex        =   19
               Top             =   390
               Width           =   1455
            End
            Begin VB.Label lblFields 
               Caption         =   "Наиболь&ший, дни:"
               Height          =   255
               Index           =   7
               Left            =   120
               TabIndex        =   21
               Top             =   870
               Width           =   1455
            End
         End
         Begin VB.CheckBox chkFields 
            Caption         =   "Проверять &возраст"
            Height          =   285
            Index           =   0
            Left            =   120
            TabIndex        =   12
            Top             =   360
            Value           =   2  'Grayed
            Width           =   1815
         End
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Возраст в 7 месяцев"
         Height          =   1335
         Index           =   1
         Left            =   3360
         TabIndex        =   6
         Top             =   480
         Visible         =   0   'False
         Width           =   3015
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   3
            Left            =   1800
            MaxLength       =   3
            TabIndex        =   10
            Top             =   840
            Width           =   975
         End
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   2
            Left            =   1800
            MaxLength       =   3
            TabIndex        =   8
            Top             =   360
            Width           =   975
         End
         Begin VB.Label lblFields 
            Caption         =   "Наибо&льший, дни:"
            Height          =   255
            Index           =   3
            Left            =   120
            TabIndex        =   9
            Top             =   885
            Width           =   1455
         End
         Begin VB.Label lblFields 
            Caption         =   "Н&аименьший, дни:"
            Height          =   255
            Index           =   2
            Left            =   120
            TabIndex        =   7
            Top             =   405
            Width           =   1455
         End
      End
      Begin VB.Frame fraFrames 
         Caption         =   "Возраст при отбивке"
         Height          =   1335
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   480
         Visible         =   0   'False
         Width           =   3015
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   1
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   5
            Top             =   840
            Width           =   975
         End
         Begin VB.TextBox txtFields 
            Height          =   315
            Index           =   0
            Left            =   1920
            MaxLength       =   3
            TabIndex        =   3
            Top             =   360
            Width           =   975
         End
         Begin VB.Label lblFields 
            Caption         =   "&Наименьший, дни:"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   2
            Top             =   390
            Width           =   1455
         End
         Begin VB.Label lblFields 
            Caption         =   "На&ибольший, дни:"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   4
            Top             =   870
            Width           =   1455
         End
      End
      Begin VB.Label lblFields 
         Caption         =   "Число баллов в &шкале селекционного индекса:"
         Height          =   255
         Index           =   16
         Left            =   -74760
         TabIndex        =   51
         Top             =   5640
         Visible         =   0   'False
         Width           =   3735
      End
      Begin VB.Label lblFields 
         Caption         =   "Наибольший возраст &животных, годы:"
         Height          =   255
         Index           =   10
         Left            =   240
         TabIndex        =   28
         Top             =   5670
         Visible         =   0   'False
         Width           =   3015
      End
   End
End
Attribute VB_Name = "frmCtrlParam"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Implements DatFrm
Implements MsgRecip

Const mintTab0 As Integer = 0 'Tab indexes.
Const mintTab1 As Integer = 1
Const mintTab2 As Integer = 2
Const mintCtl0Fst As Integer = 0 'The 1st & last lables/text boxes' indexs on tabs 0 to 1
Const mintCtl0Lst As Integer = 10
Const mintCtl1Fst As Integer = 11
Const mintCtl1Lst As Integer = 15
Const mintFraAgeWean As Integer = 0 'The frames' module-level indexes.
Const mintFraAge7Mon As Integer = 1
Const mintFraAge1Yr As Integer = 2
Const mintFraAgeMatMin As Integer = 5
Const mintFraPregnLeng As Integer = 6
Const mintFraInterAnnl As Integer = 7
Const mintFraBVTest As Integer = 10

Const mintAgeWeanMin As Integer = 0
Const mintAgeWeanMax As Integer = 1
Const mintAge7MonMin As Integer = 2
Const mintAge7MonMax As Integer = 3
Const mintAge1YrChk As Integer = 0
Const mintAge1YrWtMin As Integer = 4
Const mintAge1YrWtMax As Integer = 5
Const mintAge1YrShearMin As Integer = 6
Const mintAge1YrShearMax As Integer = 7
Const mintAgeMatMinSr As Integer = 8
Const mintAgeMatMinDm As Integer = 9
Const mintLifeTimeMax As Integer = 10
Const mintPregnLengMin As Integer = 11
Const mintPregnLengNorm As Integer = 12
Const mintPregnLengMax As Integer = 13
Const mintInterAnnlMin As Integer = 14
Const mintInterAnnlMax As Integer = 15
Const mintBrdBasDamFls As Integer = 0
Const mintBrdBasDamTr As Integer = 1
Const mintConvCrsToPure As Integer = 1
Const mintBVTestLifeTimeTr As Integer = 2
Const mintBVTestLifeTimeFls As Integer = 3
Const mintBVTestYr As Integer = 17
Const mintSelIndxScale As Integer = 16

Dim mobDatFrm As DatFrm
Dim mcolMsgs As Collection

Dim mblnIsDirty As Boolean
Dim mblnOk As Boolean

' Switch the Age1YrChk check box's dependent Age1Yr text boxes, if the Age1YrChk check
'  box is clicked.
' Mark a change.
Private Sub chkFields_Click(Index As Integer)
On Error GoTo ErrHnd
   Dim blnEnable As Boolean
   Dim I As Integer
   mblnIsDirty = True 'Mark a change.
   If Index = mintAge1YrChk Then 'Proceed for the Age1YrChk check box only.
      If chkFields(mintAge1YrChk) = vbChecked Then blnEnable = True 'Enable, if checked.
      For I = mintAge1YrWtMin To mintAge1YrShearMax 'Swhitch.
         lblFields(I).Enabled = blnEnable
         txtFields(I).Enabled = blnEnable
      Next
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub chkFields_GotFocus(Index As Integer)
Debug.Print "chkFields("; Index; ")"
End Sub

' Update the gobTblCtrlParam object.
' Save the updated data in the DB.
Private Sub cmdApply_Click()
On Error GoTo ErrHnd
   mobDatFrm.FrmToDB
   mblnIsDirty = False 'Reset.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cancel the changes or unload the form.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If mblnIsDirty Then
      mobDatFrm.Cancel False 'Cancel.
   Else
      Unload Me 'Unload.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the gobTblCtrlParam object.
' Save the updated data in the DB.
' Unload the form.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   mblnOk = True 'Mark cmdOk click.
   mobDatFrm.FrmToDB
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cancel the current changes. Restore the data as on form loading.
' Reset the gobMsgInst object.
' The blnCtlClear argument is unused.
Private Sub DatFrm_Cancel(ByVal blnCtlClear As Boolean)
On Error GoTo ErrHnd
   mblnIsDirty = False 'Reset.
   Call DatFrm_DBtoFrm 'Restore the data.
   gobMsgInst.Rest Me 'Reset messages.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear the form's controls.
Private Sub DatFrm_CtlClear()
On Error GoTo ErrHnd
   Call ClearTxt 'Initialise text boxes.
   chkFields(mintAge1YrChk).Value = vbGrayed
   chkFields(mintConvCrsToPure).Value = vbGrayed
   Call ClearOpt 'Initialise the option buttons.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the data from the form's controls.
Private Sub DatFrm_CtlRead()
On Error GoTo ErrHnd
   With gobTblCtrlParam
      .AgeWeanMin = Trim$(txtFields(mintAgeWeanMin))
      .AgeWeanMax = Trim$(txtFields(mintAgeWeanMax))
      .Age7MonMin = Trim$(txtFields(mintAge7MonMin))
      .Age7MonMax = Trim$(txtFields(mintAge7MonMax))
      Call ReadAge1Yr 'Read the Age1Yr parameters.
      .AgeMatMinSr = Trim$(txtFields(mintAgeMatMinSr))
      .AgeMatMinDm = Trim$(txtFields(mintAgeMatMinDm))
      .LifeTimeMax = Trim$(txtFields(mintLifeTimeMax))
      .PregnLengMin = Trim$(txtFields(mintPregnLengMin))
      .PregnLengNorm = Trim$(txtFields(mintPregnLengNorm))
      .PregnLengMax = Trim$(txtFields(mintPregnLengMax))
      .InterAnnlMin = Trim$(txtFields(mintInterAnnlMin))
      .InterAnnlMax = Trim$(txtFields(mintInterAnnlMax))
      .BrdBasDam = optFields(mintBrdBasDamTr)
      .ConvCrsToPure = IIf(chkFields(mintConvCrsToPure) = vbChecked, True, False)
      .BVTestLifeTime = optFields(mintBVTestLifeTimeTr)
      .BVTestYr = IIf(optFields(mintBVTestLifeTimeFls), txtFields(mintBVTestYr), 0)
      .SelIndxScale = Trim$(txtFields(mintSelIndxScale))
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the form's controls.
Private Sub DatFrm_CtlWrite()
On Error GoTo ErrHnd
   With gobTblCtrlParam
      txtFields(mintAgeWeanMin) = .AgeWeanMin
      txtFields(mintAgeWeanMax) = .AgeWeanMax
      txtFields(mintAge7MonMin) = .Age7MonMin
      txtFields(mintAge7MonMax) = .Age7MonMax
      chkFields(mintAge1YrChk) = IIf(.Age1YrChk, vbChecked, vbUnchecked)
      txtFields(mintAge1YrWtMin) = .Age1YrWtMin
      txtFields(mintAge1YrWtMax) = .Age1YrWtMax
      txtFields(mintAge1YrShearMin) = .Age1YrShearMin
      txtFields(mintAge1YrShearMax) = .Age1YrShearMax
      txtFields(mintAgeMatMinSr) = .AgeMatMinSr
      txtFields(mintAgeMatMinDm) = .AgeMatMinDm
      txtFields(mintLifeTimeMax) = .LifeTimeMax
      txtFields(mintPregnLengMin) = .PregnLengMin
      txtFields(mintPregnLengNorm) = .PregnLengNorm
      txtFields(mintPregnLengMax) = .PregnLengMax
      txtFields(mintInterAnnlMin) = .InterAnnlMin
      txtFields(mintInterAnnlMax) = .InterAnnlMax
      optFields(mintBrdBasDamFls) = Not .BrdBasDam
      optFields(mintBrdBasDamTr) = .BrdBasDam
      chkFields(mintConvCrsToPure) = IIf(.ConvCrsToPure, vbChecked, vbUnchecked)
      optFields(mintBVTestLifeTimeTr) = .BVTestLifeTime
      optFields(mintBVTestLifeTimeFls) = Not .BVTestLifeTime
      txtFields(mintBVTestYr) = IIf(.BVTestLifeTime, 0, .BVTestYr) 'Fill BV period,
      txtFields(mintSelIndxScale) = .SelIndxScale                  'unless life time.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the ContrlParam table.
' Fill the form, if the table is full, otherwise initialise the controls to intput data.
Private Sub DatFrm_DBtoFrm()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set obDatTbl = gobTblCtrlParam
   If obDatTbl.Full Then 'Check if the ContrlParam table is full.
      Call DatFrm_CtlWrite 'Fill the form.
   Else
      Call DatFrm_CtlClear 'Clear the controls.
   End If
   mblnIsDirty = False 'Reset after filling the check boxes/option buttons.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Link to Me.
Private Property Get DatFrm_FrmHost() As Form
Debug.Assert 0 = 1 'Verify
   Set DatFrm_FrmHost = Me
End Property

Private Property Let DatFrm_FrmHostNam(ByVal RHS As String)
'Empty.
End Property

Private Property Get DatFrm_FrmHostNam() As String
'Empty.
End Property

' Validate the data in the form.
' Update the gobTblCtrlParam object.
' Updated the ContrlParam table. If the table was empty insert the new record.
' Unload the form, unless the validation failes.
Private Sub DatFrm_FrmToDB()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   If DatFrm_Vld Then 'Proceed, if valid.
      gobTblCtrlParam.AllowWrite = True 'Allow to write the data to TblCtrlParam.
      Call DatFrm_CtlRead 'Read the controls.
      Set obDatTbl = gobTblCtrlParam
      With obDatTbl
         Select Case .Full 'Update/insert the ContrlParam table.
         Case True 'Update.
            .Upd
         Case False 'Insert.
            .Ins
         End Select
      End With
      gobTblCtrlParam.AllowWrite = False 'Don't allow to write the data to TblCtrlParam.
      If Not gobMsgInst.SQLErr(Me) Then 'Proceed, unless SQL error occurred.
         If mblnOk Then
            mblnOk = False 'Explicitly reset because the value is saved till next form
            Unload Me 'Unload, if cmdOk clicked.          loading even after unloading.
         End If
      End If
      gobMsgInst.Rest Me 'Reset.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Get DatFrm_IDCtl() As TextBox
'Empty.
End Property

Private Property Let DatFrm_IDFrm(ByVal RHS As String)
'Empty.
End Property

Private Property Get DatFrm_IDFrm() As String
'Empty.
End Property

' Implements or not the SetngFrm class.
Private Property Get DatFrm_IsSetngFrm() As Boolean
Debug.Assert 0 = 1 'Verify
   DatFrm_IsSetngFrm = False
End Property

Private Property Get DatFrm_Mode() As Integer
'Empty.
End Property

Private Sub DatFrm_ModeSet(ByVal intMode As Integer)
'Empty.
End Sub

Private Sub DatFrm_RegistFrm(ByVal strNewIDFrm As String, ByVal blnDelPrev As Boolean)
'Empty.
End Sub

Private Sub DatFrm_SwchCtlFill(ByVal blnEnable As Boolean, Optional ByVal blnEnableID As Boolean)
'Empty.
End Sub

Private Sub DatFrm_SwchCtlMode()
'Empty.
End Sub

' Verify that all required control parameters are inputted.
' Return True, if succeeds.
Private Function DatFrm_Vld() As Boolean
On Error GoTo ErrHnd
   If VldChkOpt Then DatFrm_Vld = VldTxt 'Validate the check boxes, option buttons
Exit Function                                  '& text boxes.
ErrHnd:
MsgBox Err.Description
End Function

' Mark a change.
Private Sub Form_KeyPress(KeyAscii As Integer)
   mblnIsDirty = True
End Sub

' Initialise the module level objects, variables & the form's controls.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set mobDatFrm = Me
   Set mcolMsgs = New Collection
   mobDatFrm.DBtoFrm 'Fill the form.
   tabCtrlParam.Tab = mintTab0 'Select the 1st tab.
   Call SwchVisibleTabStop(mintTab0, True) 'Unhide the 1st tab's frames & switch TabStop's.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If the ContrlParam table is empty promt to fill it. If the promt is rejected quit the
'  application.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set obDatTbl = gobTblCtrlParam
   If Not obDatTbl.Full Then 'Proceed, if empty.
      If MsgBox(LoadResString(199), vbCritical + vbOKCancel, LoadResString(172)) = vbOK _
         Then
         Cancel = True 'Cancel unloading.
      Else
         Call frmMDI.mnuFileExit_Click 'Quit.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mcolMsgs collection to the gobMsgInst object to read/write messages to the form
Private Property Get MsgRecip_Msgs() As Collection
   Set MsgRecip_Msgs = mcolMsgs
End Property

' Switch the BVTestYr text box, if either of the BVTestLifeTime option buttons is clicked
' Mark a change.
Private Sub optFields_Click(Index As Integer)
On Error GoTo ErrHnd
   mblnIsDirty = True
   If Index = mintBVTestLifeTimeTr Or Index = mintBVTestLifeTimeFls Then
      txtFields(mintBVTestYr).Enabled = IIf(optFields(mintBVTestLifeTimeFls), True, False)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub optFields_GotFocus(Index As Integer)
Debug.Print "optFields("; Index; ")"
End Sub

Private Sub picBtn_GotFocus()
Debug.Print "picBtn"
End Sub

' Unhide the active tab's frames & unhide the previous tab's to prevent confusing
'  coinciding lable shortcuts in different tabs.
' Switch on the active tab's controls' TabStop's & switch off the previous tab's.
Private Sub tabCtrlParam_Click(PreviousTab As Integer)
On Error GoTo ErrHnd
   Call SwchVisibleTabStop(tabCtrlParam.Tab, True) 'The active tab's on.
   Call SwchVisibleTabStop(PreviousTab, False) 'The previous tab's off.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide/unhide the specified tab's frames & controls.
' Switch on/off the specified tab's controls' TabStop's.
Private Sub SwchVisibleTabStop(ByVal intIdx As Integer, ByVal blnVisibleTabStop _
   As Boolean)
On Error GoTo ErrHnd
   Const intFraBrdCrs As Integer = 8 'The cross breed frame.
   Select Case intIdx 'Select the active tab.
   Case mintTab0
      fraFrames(mintFraAgeWean).Visible = blnVisibleTabStop
      fraFrames(mintFraAge7Mon).Visible = blnVisibleTabStop
      fraFrames(mintFraAge1Yr).Visible = blnVisibleTabStop
      fraFrames(mintFraAgeMatMin).Visible = blnVisibleTabStop
      lblFields(mintLifeTimeMax).Visible = blnVisibleTabStop
      txtFields(mintLifeTimeMax).Visible = blnVisibleTabStop
      Call Util.SwchTabStopCtl(txtFields, mintCtl0Fst, mintCtl0Lst, blnVisibleTabStop) 'Text boxes.
      chkFields(mintAge1YrChk).TabStop = blnVisibleTabStop
   Case mintTab1
      fraFrames(mintFraPregnLeng).Visible = blnVisibleTabStop
      fraFrames(mintFraInterAnnl).Visible = blnVisibleTabStop
      Call Util.SwchTabStopCtl(txtFields, mintCtl1Fst, mintCtl1Lst, blnVisibleTabStop) 'Text boxes.
   Case mintTab2
      fraFrames(intFraBrdCrs).Visible = blnVisibleTabStop
      fraFrames(mintFraBVTest).Visible = blnVisibleTabStop
      lblFields(mintSelIndxScale).Visible = blnVisibleTabStop
      txtFields(mintSelIndxScale).Visible = blnVisibleTabStop
      Call SwchTabStopOpt(blnVisibleTabStop) 'Option buttons.
      chkFields(mintConvCrsToPure).TabStop = blnVisibleTabStop
      txtFields(mintBVTestYr).TabStop = blnVisibleTabStop
      txtFields(mintSelIndxScale).TabStop = blnVisibleTabStop
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the option collection's TabStop's.
Private Sub SwchTabStopOpt(ByVal blnTabStop As Boolean)
On Error GoTo ErrHnd
   Dim optCtl As OptionButton
   For Each optCtl In optFields
      optCtl.TabStop = blnTabStop
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the text boxes.
Private Sub ClearTxt()
On Error GoTo ErrHnd
   Dim txtCtl As TextBox
   For Each txtCtl In txtFields
      txtCtl = 0
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the option buttons.
Private Sub ClearOpt()
On Error GoTo ErrHnd
   Dim optCtl As OptionButton
   For Each optCtl In optFields
      optCtl = False
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Verify that all text boxes be filled except for:
'  - the Age1Yr text boxes that depend on the Age1YrChk parameter;
'  - the BVTestYr text box that depends on the BVTestLifeTime parameter.
' Return True, if succeeds.
Private Function VldTxt() As Boolean
On Error GoTo ErrHnd
   Dim blnCheck As Boolean
   Dim blnFail As Boolean
   Dim I As Integer
   For I = 0 To txtFields.Count - 1
      Select Case I 'Define whether/not to check the text boxes.      Below: 'Age1Yr text
      Case mintAge1YrWtMin, mintAge1YrWtMax, mintAge1YrShearMin, mintAge1YrShearMax 'boxs
         If chkFields(mintAge1YrChk) = vbChecked Then blnCheck = True 'Check, if reqired.
      Case mintBVTestYr 'BVTestYr text box.
         If optFields(mintBVTestLifeTimeFls) Then blnCheck = True 'Check, unless life tim
      Case Else 'Other text boxes.
         blnCheck = True 'Mark to check below.
      End Select
      If blnCheck Then 'Check, if allowed.
         blnCheck = False 'Reset.
         If gobFormtCtl.BlankNum(txtFields(I)) Then
            blnFail = True 'Failed.
            Call FocTab(txtFields(I))
            Call Util.MissParam(txtFields(I), LblCapt(I))
            Exit For
         End If
      End If
   Next
   VldTxt = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Compose the captions to the specified text box for the Util.MissParam procedure to
'  message about a missing parameter.
Private Function LblCapt(ByVal intIdx As Integer) As String
On Error GoTo ErrHnd
   Const intFraAge1YrWt As Integer = 3 'The frames' local indexes.
   Const intFraAge1YrShear As Integer = 4
   Select Case intIdx 'Select the text box's caption/s.
   Case mintAgeWeanMin
      LblCapt = LoadResString(200) & LCase$(fraFrames(mintFraAgeWean).Caption)
   Case mintAgeWeanMax
      LblCapt = LoadResString(201) & LCase$(fraFrames(mintFraAgeWean).Caption)
   Case mintAge7MonMin
      LblCapt = LoadResString(200) & LCase$(fraFrames(mintFraAge7Mon).Caption)
   Case mintAge7MonMax
      LblCapt = LoadResString(201) & LCase$(fraFrames(mintFraAge7Mon).Caption)
   Case mintAge1YrWtMin
      LblCapt = LoadResString(200) & LCase$(fraFrames(mintFraAge1Yr).Caption) & Space$(1) _
         & LCase$(fraFrames(intFraAge1YrWt).Caption)
   Case mintAge1YrWtMax
      LblCapt = LoadResString(201) & LCase$(fraFrames(mintFraAge1Yr).Caption) & Space$(1) _
         & LCase$(fraFrames(intFraAge1YrWt).Caption)
   Case mintAge1YrShearMin
      LblCapt = LoadResString(200) & LCase$(fraFrames(mintFraAge1Yr).Caption) & Space$(1) _
         & LCase$(fraFrames(intFraAge1YrShear).Caption)
   Case mintAge1YrShearMax
      LblCapt = LoadResString(201) & LCase$(fraFrames(mintFraAge1Yr).Caption) & Space$(1) _
         & LCase$(fraFrames(intFraAge1YrShear).Caption)
   Case mintAgeMatMinSr
      LblCapt = fraFrames(mintFraAgeMatMin).Caption & LoadResString(202)
   Case mintAgeMatMinDm
      LblCapt = fraFrames(mintFraAgeMatMin).Caption & LoadResString(203)
   Case mintLifeTimeMax
      LblCapt = lblFields(mintLifeTimeMax).Caption
   Case mintPregnLengMin
      LblCapt = LoadResString(200) & LCase$(fraFrames(mintFraPregnLeng).Caption)
   Case mintPregnLengNorm
      LblCapt = LoadResString(204) & LCase$(fraFrames(mintFraPregnLeng).Caption)
   Case mintPregnLengMax
      LblCapt = LoadResString(201) & LCase$(fraFrames(mintFraPregnLeng).Caption)
   Case mintInterAnnlMin
      LblCapt = LoadResString(200) & LCase$(fraFrames(mintFraInterAnnl).Caption)
   Case mintInterAnnlMax
      LblCapt = LoadResString(201) & LCase$(fraFrames(mintFraInterAnnl).Caption)
   Case mintBVTestYr
      LblCapt = fraFrames(mintFraBVTest).Caption & Space$(1) & LCase$(optFields( _
         mintBVTestLifeTimeFls).Caption)
   Case mintSelIndxScale
      LblCapt = lblFields(mintSelIndxScale)
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Verify that all check boxes & option buttons be explicitely set.
' Return True, if succeeds.
Private Function VldChkOpt() As Boolean
On Error GoTo ErrHnd
   Dim chkCtl As CheckBox
   Dim strPromt As String
   If chkFields(mintAge1YrChk) = vbGrayed Then 'Define the Age1YrChk parameter.
      Call FocTab(chkFields(mintAge1YrChk)) 'Select the tab.
      strPromt = LoadResString(205) & chkFields(mintAge1YrChk).Caption & "'."
      Call Util.MissParam(chkFields(mintAge1YrChk), , , strPromt) 'Message & focus.
   ElseIf chkFields(mintConvCrsToPure) = vbGrayed Then 'Define the mintConvCrsToPure para
      Call FocTab(chkFields(mintConvCrsToPure)) 'Select the tab.
      strPromt = LoadResString(205) & chkFields(mintConvCrsToPure).Caption & "'."
      Call Util.MissParam(chkFields(mintConvCrsToPure), , , strPromt) 'Message & focus.
   ElseIf optFields(mintBrdBasDamFls) = False And optFields(mintBrdBasDamTr) = False _
      Then 'Define the BrdBasDam parameter.
      Call FocTab(optFields(mintBrdBasDamFls)) 'Select the tab.
      MsgBox LoadResString(206), vbExclamation, LoadResString(21) 'Message w/o focusing.
   ElseIf optFields(mintBVTestLifeTimeTr) = False And optFields(mintBVTestLifeTimeFls) _
      = False Then 'Define the BVTest parameter.
      Call FocTab(optFields(mintBVTestLifeTimeTr)) 'Select the tab.
      strPromt = LoadResString(205) & fraFrames(mintFraBVTest).Caption & "'."
      MsgBox strPromt, vbExclamation, LoadResString(21) 'Message w/o focusing.
   Else
      VldChkOpt = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Format the control.
Private Sub txtFields_GotFocus(Index As Integer)
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtFields(Index)
Debug.Print "txtFields("; Index; ")"
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtFields_Validate(Index As Integer, Cancel As Boolean)
On Error GoTo ErrHnd
   Const intMinAgeWean As Integer = 90 'The minimum/maximums.
   Const intMaxAgeWean As Integer = 180
   Const intMinAge7Mon As Integer = 180
   Const intMaxAge7Mon As Integer = 270
   Const intMinAge1YrWt As Integer = 305
   Const intMaxAge1YrWt As Integer = 515
   Const intMinAgeMatMin As Integer = 120
   Const intMaxAgeMatMin As Integer = 365
   Const intMinLifeTimeMax As Integer = 5
   Const intMaxLifeTimeMax As Integer = 15
   Const intMinPregnLeng As Integer = 135
   Const intMaxPregnLeng As Integer = 165
   Const intMinInterAnnl As Integer = 305
   Const intMaxInterAnnl As Integer = 425
   Const intMinSelIndxScale As Integer = 5
   Const intMaxSelIndxScale As Integer = 100
   Dim intMin As Single
   Dim intMax As Single
   Select Case Index 'Define the min/max by index.
   Case mintAgeWeanMin, mintAgeWeanMax
      intMin = intMinAgeWean
      intMax = intMaxAgeWean
   Case mintAge7MonMin, mintAge7MonMax
      intMin = intMinAge7Mon
      intMax = intMaxAge7Mon
   Case mintAge1YrWtMin, mintAge1YrWtMax, mintAge1YrShearMin, mintAge1YrShearMax
      intMin = intMinAge1YrWt
      intMax = intMaxAge1YrWt
   Case mintAgeMatMinSr, mintAgeMatMinDm
      intMin = intMinAgeMatMin
      intMax = intMaxAgeMatMin
   Case mintLifeTimeMax
      intMin = intMinLifeTimeMax
      intMax = intMaxLifeTimeMax
   Case mintPregnLengMin, mintPregnLengNorm, mintPregnLengMax
      intMin = intMinPregnLeng
      intMax = intMaxPregnLeng
   Case mintInterAnnlMin, mintInterAnnlMax
      intMin = intMinInterAnnl
      intMax = intMaxInterAnnl
   Case mintBVTestYr
      intMax = intMaxLifeTimeMax
   Case mintSelIndxScale
      intMin = intMinSelIndxScale
      intMax = intMaxSelIndxScale
   End Select
   Cancel = Not gobFormtCtl.VldNum(txtFields(Index), intMin, intMax, True)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select the tab a missing parameters resides on to focus that field.
Private Sub FocTab(ByVal ctlCtl As Control)
On Error GoTo ErrHnd
   If TypeOf ctlCtl Is TextBox Then 'Look up among the text boxes.
      Select Case ctlCtl.Index 'Match the index to the tabs' text boxes' indexes.
      Case mintCtl0Fst To mintCtl0Lst 'Tab 0.
         tabCtrlParam.Tab = mintTab0
      Case mintCtl1Fst To mintCtl1Lst 'Tab 1.
         tabCtrlParam.Tab = mintTab1
      Case mintBVTestYr, mintSelIndxScale 'Tab 2.
         tabCtrlParam.Tab = mintTab2
      End Select
   ElseIf TypeOf ctlCtl Is CheckBox Then 'Look up among the check boxes.
      Select Case ctlCtl.Index 'Match the index to the tabs' check boxes' indexes.
      Case mintAge1YrChk 'Tab 0.
         tabCtrlParam.Tab = mintTab0
      Case mintConvCrsToPure 'Tab 2.
         tabCtrlParam.Tab = mintTab2
      End Select
   ElseIf TypeOf ctlCtl Is OptionButton Then 'All option buttons reside on tab 2.
      tabCtrlParam.Tab = mintTab2
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Read the Age1Yr parameters based on the chkFields(mintAge1YrChk) check box's value.
Private Sub ReadAge1Yr()
On Error GoTo ErrHnd
   Dim I As Integer
   With gobTblCtrlParam
      .Age1YrChk = IIf(chkFields(mintAge1YrChk) = vbChecked, True, False)
      Select Case chkFields(mintAge1YrChk)
      Case vbChecked 'Read the inputted values.
         .Age1YrWtMin = Trim$(txtFields(mintAge1YrWtMin))
         .Age1YrWtMax = Trim$(txtFields(mintAge1YrWtMax))
         .Age1YrShearMin = Trim$(txtFields(mintAge1YrShearMin))
         .Age1YrShearMax = Trim$(txtFields(mintAge1YrShearMax))
      Case vbUnchecked 'Nullify the values.
         For I = mintAge1YrWtMin To mintAge1YrShearMax
            txtFields(I) = 0
         Next
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatFrm_IsDirty(ByVal blnIsDirty As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Property Get DatFrm_IsDirty() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Sub DatFrm_IDCtlPress(ByRef intKeyAscii As Integer)
'If necessary modify the code to use this procedure.
End Sub

Private Sub DatFrm_IDCtlLostFoc()
'If necessary modify the code to use this procedure.
End Sub

' The form's caption.
Private Property Get DatFrm_FrmHostCaptOrig() As String
'If necessary modify the code to use this procedure.
End Property

' The form's caption.
Private Property Let DatFrm_FrmHostCaptOrig(ByVal strFrmHostCapt As String)
'If necessary modify the code to use this procedure.
End Property

