VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.MDIForm frmMDI 
   BackColor       =   &H8000000C&
   ClientHeight    =   6645
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   10815
   Icon            =   "frmMDI.frx":0000
   LinkTopic       =   "MDIForm1"
   LockControls    =   -1  'True
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.Timer tmrTimer 
      Enabled         =   0   'False
      Interval        =   125
      Left            =   120
      Top             =   2040
   End
   Begin MSComctlLib.StatusBar staStatusBar 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   0
      Top             =   6270
      Width           =   10815
      _ExtentX        =   19076
      _ExtentY        =   661
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   5
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   12039
            Text            =   "Готово"
            TextSave        =   "Готово"
            Key             =   "pnlText"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   2
            Text            =   "База данных: "
            TextSave        =   "База данных: "
            Key             =   "pnlDB"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   1
            Enabled         =   0   'False
            Object.Width           =   1058
            MinWidth        =   1058
            Text            =   "Caps Lock"
            TextSave        =   "CAPS"
            Key             =   "pnlCabs"
         EndProperty
         BeginProperty Panel4 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   2
            Object.Width           =   1058
            MinWidth        =   1058
            Text            =   "Num Lock"
            TextSave        =   "NUM"
            Key             =   "pnlNum"
         EndProperty
         BeginProperty Panel5 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            Object.Width           =   1764
            MinWidth        =   1764
            TextSave        =   "10.08.2003"
            Key             =   "pnlDate"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar tlbToolBar 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   10815
      _ExtentX        =   19076
      _ExtentY        =   741
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "ilsImageList"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   23
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   4
            Object.Width           =   75
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "BrsShG"
            Object.ToolTipText     =   "Обзор овец/коз (Ctrl+O)"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "ShG"
            Object.ToolTipText     =   "Обработка данных овец/коз (Ctrl+I)"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Add"
            Object.ToolTipText     =   "Ввод записи (Ctrl+A)"
            ImageIndex      =   3
            Style           =   2
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Edit"
            Object.ToolTipText     =   "Изменение записи (Ctrl+S)"
            ImageIndex      =   4
            Style           =   2
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Del"
            Object.ToolTipText     =   "Удаление записи (Ctrl+D)"
            ImageIndex      =   5
            Style           =   2
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cut"
            Object.ToolTipText     =   "Вырезать (Ctrl+X)"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Copy"
            Object.ToolTipText     =   "Скопировать (Ctrl+C)"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Paste"
            Object.ToolTipText     =   "Вставить (Ctrl+V)"
            ImageIndex      =   8
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Undo"
            Object.ToolTipText     =   "Восстановить текст (Ctrl+Z)"
            ImageIndex      =   9
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "SumGenEval"
            Object.ToolTipText     =   "Оценка баранов/козлов по качеству потомства Ctrl+Q"
            ImageIndex      =   10
         EndProperty
         BeginProperty Button17 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "SumPerform"
            Object.ToolTipText     =   "Продуктивность животных (Ctrl+W)"
            ImageIndex      =   11
         EndProperty
         BeginProperty Button18 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "SumFlockManagm"
            Object.ToolTipText     =   "Управление стадом (Ctrl+E)"
            ImageIndex      =   12
         EndProperty
         BeginProperty Button19 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Cert"
            Object.ToolTipText     =   "Карточка племенного животного (Ctrl+R)"
            ImageIndex      =   13
         EndProperty
         BeginProperty Button20 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button21 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "FrmBlk"
            Object.ToolTipText     =   "Бланк инвентаризации и случки (пустой) (F5)"
            ImageIndex      =   14
            Style           =   5
            BeginProperty ButtonMenus {66833FEC-8583-11D1-B16A-00C0F0283628} 
               NumButtonMenus  =   7
               BeginProperty ButtonMenu1 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "InvenMatBlk"
                  Text            =   "Бланк инвентаризации и случки (пустой) (F5)"
               EndProperty
               BeginProperty ButtonMenu2 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "InvenMat"
                  Text            =   "Бланк инвентаризации и случки (F6)"
               EndProperty
               BeginProperty ButtonMenu3 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "LmK"
                  Text            =   "Бланк ягнения/козления (F7)"
               EndProperty
               BeginProperty ButtonMenu4 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "WtLmK"
                  Text            =   "Бланк взвешивания ягнят/козлят (F8)"
               EndProperty
               BeginProperty ButtonMenu5 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "WtWool"
                  Text            =   "Бланк взвешивания и стрижки (F9)"
               EndProperty
               BeginProperty ButtonMenu6 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "Appr"
                  Text            =   "Бланк бонитировки (F11)"
               EndProperty
               BeginProperty ButtonMenu7 {66833FEE-8583-11D1-B16A-00C0F0283628} 
                  Key             =   "Disp"
                  Text            =   "Бланк выбытия (F12)"
               EndProperty
            EndProperty
         EndProperty
         BeginProperty Button22 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button23 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Close"
            Object.ToolTipText     =   "Закрыть (Ctrl+F)"
            ImageIndex      =   15
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ilsImageList 
      Left            =   120
      Top             =   600
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   15
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":1042
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":11C4
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":14DE
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":15E0
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":173A
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":1844
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":1EBE
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":2538
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":264A
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":275C
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":346E
            Key             =   ""
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":3F00
            Key             =   ""
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":4752
            Key             =   ""
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":55A4
            Key             =   ""
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMDI.frx":56AE
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgFile 
      Left            =   120
      Top             =   1320
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Menu mnuFile 
      Caption         =   "Файл"
      Begin VB.Menu mnuFileFrmBrsShG 
         Caption         =   "Обзор овец/коз"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileFrmShG 
         Caption         =   "Обработка данных овец/коз"
         Shortcut        =   ^I
      End
      Begin VB.Menu Separator8 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileRpt 
         Caption         =   "Отчёты"
         Begin VB.Menu mnuFileRptSumGenEval 
            Caption         =   "Оценка баранов/козлов по качеству потомства..."
            Shortcut        =   ^Q
         End
         Begin VB.Menu mnuFileRptSumPerform 
            Caption         =   "Продуктивность животных..."
            Shortcut        =   ^W
         End
         Begin VB.Menu mnuFileRptSumFlockManagm 
            Caption         =   "Управление стадом..."
            Shortcut        =   ^E
         End
         Begin VB.Menu mnuFileRptCert 
            Caption         =   "Карточка племенного животного..."
            Shortcut        =   ^R
         End
      End
      Begin VB.Menu mnuFrmBlk 
         Caption         =   "Бланки"
         Begin VB.Menu mnuFrmblkInvenMatBlk 
            Caption         =   "Бланк инвентаризации и случки (пустой)"
            Shortcut        =   {F5}
         End
         Begin VB.Menu mnuFrmblkInvenMat 
            Caption         =   "Бланк инвентаризации и случки..."
            Shortcut        =   {F6}
         End
         Begin VB.Menu mnuFrmblkLmK 
            Caption         =   "Бланк ягнения/козления..."
            Shortcut        =   {F7}
         End
         Begin VB.Menu mnuFrmblkWtLmK 
            Caption         =   "Бланк взвешивания ягнят/козлят..."
            Shortcut        =   {F8}
         End
         Begin VB.Menu mnuFrmblkWtWool 
            Caption         =   "Бланк взвешивания и стрижки..."
            Shortcut        =   {F9}
         End
         Begin VB.Menu mnuFrmblkAppr 
            Caption         =   "Бланк бонитировки..."
            Shortcut        =   {F11}
         End
         Begin VB.Menu mnuFrmblkDisp 
            Caption         =   "Бланк выбытия"
            Shortcut        =   {F12}
         End
      End
      Begin VB.Menu Separator1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileAdd 
         Caption         =   "Ввод записи"
         Enabled         =   0   'False
         Shortcut        =   ^A
      End
      Begin VB.Menu mnuFileEdit 
         Caption         =   "Изменение записи"
         Enabled         =   0   'False
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileDel 
         Caption         =   "Удаление записи"
         Enabled         =   0   'False
         Shortcut        =   ^D
      End
      Begin VB.Menu Separator11 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "Закрыть"
         Enabled         =   0   'False
         Shortcut        =   ^F
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "Выйти"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "Правка"
      Begin VB.Menu mnuEditUndo 
         Caption         =   "Восстановить Ctrl+Z"
         Enabled         =   0   'False
      End
      Begin VB.Menu Separator10 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditCut 
         Caption         =   "Вырезать        Ctrl+X"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuEditCopy 
         Caption         =   "Скопировать   Ctrl+C"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuEditPaste 
         Caption         =   "Вставить         Ctrl+V"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "Вид"
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "Панель инструментов"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar 
         Caption         =   "Строка состояния"
         Checked         =   -1  'True
      End
   End
   Begin VB.Menu mnuSetng 
      Caption         =   "Сервис"
      Begin VB.Menu mnuSetngCountr 
         Caption         =   "Страны"
         Shortcut        =   +{F1}
      End
      Begin VB.Menu mnuSetngObl 
         Caption         =   "Области"
         Shortcut        =   +{F2}
      End
      Begin VB.Menu mnuSetngRayn 
         Caption         =   "Районы"
         Shortcut        =   +{F3}
      End
      Begin VB.Menu mnuSetngTwnVll 
         Caption         =   "Населённые пункты"
         Shortcut        =   +{F4}
      End
      Begin VB.Menu Separator2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSetngPers 
         Caption         =   "Участники"
         Shortcut        =   +{F5}
      End
      Begin VB.Menu mnuSetngFarm 
         Caption         =   "Фермы"
         Shortcut        =   +{F6}
      End
      Begin VB.Menu Separator3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSetngBrdStd 
         Caption         =   "Породы и стандарты пород"
         Shortcut        =   +{F7}
      End
      Begin VB.Menu mnuSetngDefct 
         Caption         =   "Пороки"
         Shortcut        =   +{F8}
      End
      Begin VB.Menu Separator4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSetngCtrlParam 
         Caption         =   "Контрольные параметры"
         Shortcut        =   +{F9}
      End
      Begin VB.Menu Separator6 
         Caption         =   "-"
      End
      Begin VB.Menu mnuSetngDBBackup 
         Caption         =   "Резервное копирование базы данных..."
      End
      Begin VB.Menu mnuSetngPwdSet 
         Caption         =   "Изменение пароля..."
      End
   End
   Begin VB.Menu mnuWnd 
      Caption         =   "Окно"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWndTitleHorizontal 
         Caption         =   "Расположить горизонтально"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuWndTitleVertical 
         Caption         =   "Расположить вертикально"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuWndCascade 
         Caption         =   "Расположить каскадом"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "Помощь"
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "О Племкниге"
      End
   End
End
Attribute VB_Name = "frmMDI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim WithEvents mfrmRptFarmDate As frmRptFarmDate
Attribute mfrmRptFarmDate.VB_VarHelpID = -1
Dim mintIdxRpt As Integer

Const mstrKeyInvenMatBlk As String = "InvenMatBlk"
Const mstrKeyInvenMat As String = "InvenMat"
Const mstrKeyLmK As String = "LmK"
Const mstrKeyWtLmK As String = "WtLmK"
Const mstrKeyWtWool As String = "WtWool"
Const mstrKeyAppr As String = "Appr"
Const mstrKeyDisp As String = "Disp"
Const mstrKeyFrmBlk As String = "FrmBlk"

Dim mstrKeyBtnMnu As String
Dim mblnRefrshTree As Boolean

Public TimerObj As Object
Public TimerProc As String

' Create new global objects.
Private Sub MDIForm_Load()
On Error GoTo ErrHnd
   With App
      Me.Caption = .Title 'Form caption.
      mnuHelpAbout.Caption = LoadResString(5) & Space$(1) & .Title 'About menu caption.
   End With
   Set gcnnConn = New ADODB.Connection
'   Set gcnnConnClnt = New ADODB.Connection
   Set gobDatFrms = New DatFrms
   Set gobShGs = New ShGs
   Set gobMsgInst = New MsgInst
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Public Sub MDIForm_MouseUp(Button As Integer, Shift As Integer, x As Single, Y As Single)
On Error GoTo ErrHnd
   If Button = 2 Then 'Check if right mouse button was clicked.
      PopupMenu mnuFile 'Display the File menu as a pop-up menu.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

'' Save the window state, if changed.
'Private Sub MDIForm_Resize()
'On Error GoTo ErrHnd
'   Dim intWindowState As Integer
'   intWindowState = CInt(GetSetting(App.Title, "WindowSate", "Child", 0)) 'Compare.
'   If Me.WindowState <> intWindowState Then SaveSetting App.Title, "WindowSate", _
'      "MDI", Me.WindowState 'Save.
'Exit Sub
'ErrHnd:
'MsgBox Err.Description
'End Sub

' Destroy all global objects.
' Unload the hidden frmBrsShG & frmBrsShGShow forms.
' Drop reports' temporary tables in the DB, unless the SQL Server is currently busy.
Private Sub MDIForm_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB 'Drop tables, if server is connected & isn't busy .
   Dim obDatTbl As DatTbl
   frmBrsShG.AllowUnload = True 'Mark to unload frmBrsShG.
   Unload frmBrsShG 'Unload frmBrsShG & frmBrsShGShow.
   Unload frmBrsShGShow
   Set obUtilDB = New UtilDB
   If gcnnConn.State = adStateOpen Then If Not obUtilDB.Busy Then obUtilDB.DropTblRpt
   Set gcnnConn = Nothing 'Destroy globals.
   Set gdbDB = Nothing
'   Set gcnnConnClnt = Nothing
   Set gobDatFrms = Nothing
   Set gobShGs = Nothing
   Set gobTblCtrlParam = Nothing
   Set gobMsgInst = Nothing
   Set gobSetng = Nothing
   Set gobFormtCtl = Nothing
   Set gobMsgInst = Nothing
   Debug.Print "The global objects set to Nothing in frmMDI\Form_Unload." & vbCr & _
      "Current time: "; Time() & vbCr 'Inform.
'   frmBrsShG.AllowUnload = True 'Mark to unload frmBrsShG.
'   Unload frmBrsShG 'Unload frmBrsShG & frmBrsShGShow.
'   Unload frmBrsShGShow
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Supply the specified report index for the report mfrmRptFarmDate form.
Private Sub mfrmRptFarmDate_GetIdx(intIdx As Integer)
On Error GoTo ErrHnd
   intIdx = mintIdxRpt
   mintIdxRpt = 0 'Reset.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open the frmBrsShG form.
' Load a new ShG form to fill it from the frmBrsShG one. Unless filled, unload it again.
Private Sub mnuFileFrmBrsShG_Click()
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   frmBrsShG.RefrshTreeDo 'Refresh the tree veiw, if necessary. Must implement before
   Call LoadNewShG 'Load new frmShG.            'LoadNewShG to prevent a mixed screen.
   Set obDatFrm = Me.ActiveForm
   With frmBrsShG 'Pass frmShG's parameters.
      Set .FrmCall = obDatFrm.FrmHost
      .FrmCallNam = gobSetng.FrmNamByIdx(gobSetng.LastTabShG)
      Set .IDTxt = obDatFrm.IDCtl
      Set .CmdButton = obDatFrm.FrmHost.cmdID(gobSetng.FrmInvenIdx)
      .DatFrmEntr = True 'The rest data forms.
      .FrmCallNew = True 'New frmShG.
   End With
   frmBrsShGShow.cmdShG = True 'Show frmBrsShG.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open ShG form first make sure its ID is properly set.
' Load a new ShG form.
' Register it in the DatFrms collection.
Private Sub mnuFileFrmShG_Click()
On Error GoTo ErrHnd
   Call LoadNewShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new rptFrmAppr report.
Private Sub mnuFrmBlkAppr_Click()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxFrmAppr 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the rptFrmDisp report.
Private Sub mnuFrmBlkDisp_Click()
On Error GoTo ErrHnd
   Dim rptNewFrmDisp As rptFrmDisp
   Set rptNewFrmDisp = New rptFrmDisp
   rptNewFrmDisp.Show , frmMDI
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new rptFrmWtWool report.
Private Sub mnuFrmBlkWtWool_Click()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxFrmWtWool 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Copy the text & put it to the clipboard.
Private Sub mnuEditCopy_Click()
On Error GoTo ErrHnd
   If gobFormtCtl.IsTxtDbcDropdown(Screen.ActiveControl) Then 'Proceed if cut/copy/paste allowed.
      Clipboard.Clear
      Clipboard.SetText Screen.ActiveControl.SelText
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cut the text & put it to the clipboard.
Private Sub mnuEditCut_Click()
On Error GoTo ErrHnd
   If gobFormtCtl.IsTxtDbcDropdown(Screen.ActiveControl) Then 'Proceed if cut/copy/paste allowed.
      Clipboard.Clear
      Clipboard.SetText Screen.ActiveControl.SelText
      Screen.ActiveControl.SelText = ""
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Paste the text from the clipboard.
Private Sub mnuEditPaste_Click()
On Error GoTo ErrHnd
   If gobFormtCtl.IsTxtDbcDropdown(Screen.ActiveControl) Then 'Proceed if cut/copy/paste allowed.
      Screen.ActiveControl.SelText = Clipboard.GetText()
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Undo the last change by pressing Ctrl+Z.
Private Sub mnuEditUndo_Click()
On Error GoTo ErrHnd
   Call APIKeyBoad.PressCtrlZ
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the form, menu, & tool bar to the Add mode.
Private Sub mnuFileAdd_Click()
On Error GoTo ErrHnd
   Call ModeSetAct(gobSetng.ModeAdd)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new rptFrmInvMat report.
Private Sub mnuFrmBlkInvenMat_Click()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxFrmInvMat 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the rptFrmInvMatBlk report.
Private Sub mnuFrmBlkInvenMatBlk_Click()
On Error GoTo ErrHnd
   Dim rptNewFrmInvMatBlk As rptFrmInvMatBlk
   Set rptNewFrmInvMatBlk = New rptFrmInvMatBlk
   rptNewFrmInvMatBlk.Show , frmMDI
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new rptFrmLmK report.
Private Sub mnuFrmBlkLmK_Click()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxFrmLmK 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new rptFrmWtLmK report.
Private Sub mnuFrmBlkWtLmK_Click()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxFrmWtLmK 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Close the active form, unless it's the frmBrsShG one.
Public Sub mnuFileClose_Click()
On Error GoTo ErrHnd
    Unload Me.ActiveForm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub mnuFileDel_Click()
On Error GoTo ErrHnd
   Call ModeSetAct(gobSetng.ModeDel)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub mnuFileEdit_Click()
On Error GoTo ErrHnd
   Call ModeSetAct(gobSetng.ModeEdit)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Exit the application.
Public Sub mnuFileExit_Click()
On Error GoTo ErrHnd
    Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub mnuFileFrmWtWool_Click()
On Error GoTo ErrHnd
'    Call LoadNewWtWool
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the frmAbout window.
Private Sub mnuHelpAbout_Click()
On Error GoTo ErrHnd
   Load frmAbout
   frmAbout.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub mnuFileRptCert_Click()
On Error GoTo ErrHnd
    Call LoadNewCert
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

'Private Sub mnuFileRptCertRamHegoat_Click()
'On Error GoTo ErrHnd
'    Call LoadNewCertRamHegoat
'Exit Sub
'ErrHnd:
'MsgBox Err.Description
'End Sub

Private Sub mnuFileRptSumFlockManagm_Click()
On Error GoTo ErrHnd
    Call LoadNewSumFlockManagm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub mnuFileRptSumGenEval_Click()
On Error GoTo ErrHnd
    Call LoadNewSumGenEval
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub mnuFileRptSumPerform_Click()
On Error GoTo ErrHnd
    Call LoadNewSumPerform
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open BrdStd form first make sure its ID is properly set.
' Load a new BrdStd form.
' Register it in the DatFrms collection.
Private Sub mnuSetngBrdStd_Click()
On Error GoTo ErrHnd
   Dim frmNewBrdStd As frmBrdStd
   If BlankVld(gobSetng.FrmBrdStdNam) Then 'Check another BrdStd form & its ID.
      Set frmNewBrdStd = New frmBrdStd 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewBrdStd) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open Countr form first make sure its ID is properly set.
' Load a new Countr form.
' Register it in the DatFrms collection.
Private Sub mnuSetngCountr_Click()
On Error GoTo ErrHnd
   Dim frmNewCountr As frmCountr
   If BlankVld(gobSetng.FrmCountrNam) Then 'Check another Countr form & its ID.
      Set frmNewCountr = New frmCountr 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewCountr) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show the frmCtrlParam form.
Public Sub mnuSetngCtrlParam_Click()
On Error GoTo ErrHnd
   Load frmCtrlParam
   frmCtrlParam.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Backup the DB.
' Verify the reqired free disk space for the backup.
' Save the backup file in the application Backup directory. Unless the latter exists
'  create a new one.
' To get rid of mixed forms when the dlgFile dialog form unloads & backing up starts this
'  operation is splited up to two procedures (Backup1 & Backup2) with a break between
'  the two. Call the 1st procedure from this one. Enable the tmrTimer timer to invoke
'  the 2nd procedure.
Private Sub mnuSetngDBBackup_Click()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Set obUtilDB = New UtilDB
   If obUtilDB.Backup1 Then 'The 1st procedure.
      Set TimerObj = obUtilDB 'Specify the arguments for the timer.
      TimerProc = "Backup2"
      tmrTimer.Enabled = True 'Inovke the 2nd procedure.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open Defct form first make sure its ID is properly set.
' Load a new Defct form.
' Register it in the DatFrms collection.
Private Sub mnuSetngDefct_Click()
On Error GoTo ErrHnd
   Dim frmNewDefct As frmDefct
   If BlankVld(gobSetng.FrmDefctNam) Then 'Check another Defct form & its ID.
      Set frmNewDefct = New frmDefct 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewDefct) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open Farm form first make sure its ID is properly set.
' Load a new Farm form.
' Register it in the DatFrms collection.
Private Sub mnuSetngFarm_Click()
On Error GoTo ErrHnd
   Dim frmNewFarm As frmFarm
   If BlankVld(gobSetng.FrmFarmNam) Then 'Check another Farm form & its ID.
      Set frmNewFarm = New frmFarm 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewFarm) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open Obl form first make sure its ID is properly set.
' Load a new Obl form.
' Register it in the DatFrms collection.
Private Sub mnuSetngObl_Click()
On Error GoTo ErrHnd
   Dim frmNewObl As frmObl
   If BlankVld(gobSetng.FrmOblNam) Then 'Check another Obl form & its ID.
      Set frmNewObl = New frmObl 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewObl) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open frmPers form first make sure its ID is properly set.
' Load a new frmPers form.
' Register it in the DatFrms collection.
Private Sub mnuSetngPers_Click()
On Error GoTo ErrHnd
   Dim frmNewPers As frmPers
   If BlankVld(gobSetng.FrmPersNam) Then 'Check another frmPers & its ID.
      Set frmNewPers = New frmPers 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewPers) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the user's currern password.
Private Sub mnuSetngPwdSet_Click()
On Error GoTo ErrHnd
   frmPwdSet.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open frmRayn form first make sure its ID is properly set.
' Load a new frmRayn form.
' Register it in the DatFrms collection.
Private Sub mnuSetngRayn_Click()
On Error GoTo ErrHnd
   Dim frmNewRayn As frmRayn
   If BlankVld(gobSetng.FrmRaynNam) Then 'Check another frmRayn & its ID.
      Set frmNewRayn = New frmRayn 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewRayn) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open frmTwnVll form first make sure its ID is properly set.
' Load a new frmTwnVll form.
' Register it in the DatFrms collection.
Private Sub mnuSetngTwnVll_Click()
On Error GoTo ErrHnd
   Dim frmNewTwnVll As frmTwnVll
   If BlankVld(gobSetng.FrmTwnVllNam) Then 'Check another frmTwnVll & its ID.
      Set frmNewTwnVll = New frmTwnVll 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewTwnVll) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide/unhide the status bar.
Private Sub mnuViewStatusBar_Click()
On Error GoTo ErrHnd
   If mnuViewStatusBar.Checked Then
      staStatusBar.Visible = False
      mnuViewStatusBar.Checked = False
   Else
      staStatusBar.Visible = True
      mnuViewStatusBar.Checked = True
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide/unhide the tool bar.
Private Sub mnuViewToolbar_Click()
On Error GoTo ErrHnd
   If mnuViewToolbar.Checked Then
      tlbToolBar.Visible = False
      mnuViewToolbar.Checked = False
   Else
      tlbToolBar.Visible = True
      mnuViewToolbar.Checked = True
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cascade the active windows.
Private Sub mnuWndCascade_Click()
On Error GoTo ErrHnd
    Arrange vbCascade
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Title the active windows horizontal.
Private Sub mnuWndTitleHorizontal_Click()
On Error GoTo ErrHnd
    Arrange vbTileHorizontal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Title the active windows vertical.
Private Sub mnuWndTitleVertical_Click()
On Error GoTo ErrHnd
    Arrange vbTileVertical
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Close the active form or exit the application.
Private Sub CloseExit()
On Error GoTo ErrHnd
    Unload ActiveForm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement a button's assinged action.
Private Sub tlbToolBar_ButtonClick(ByVal Button As MSComctlLib.Button)
On Error GoTo ErrHnd
   Call ToolBarDo(Button.Key)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on windows-relevant menus & the Exit button on the tool bar, if a form is
'   being opened.
' Otherwise, determine & set a proper state for the menus.
' If a report window, which is the only open one, invokes the procedure disable the
'   window menu items.
Public Sub SwchMnuWin(ByVal blnOpen As Boolean, Optional ByVal blnReport As Boolean)
On Error GoTo ErrHnd
   Dim blnSwitch As Boolean
   Dim blnEnable As Boolean
   With gobSetng
      If blnOpen Then 'A form is being opened.
          blnSwitch = True
          blnEnable = True
      ElseIf blnReport Then
         If CountFrm = 0 Then 'And .Reports = 0 Then
            blnSwitch = True 'The last report is being closed.
            blnEnable = False
         End If
      ElseIf Not blnReport Then
         If CountFrm = 1 Then 'And .Reports = 0 Then
            blnSwitch = True 'The last form is being closed.
            blnEnable = False
         End If
      End If
   End With
   If blnSwitch Then 'Enable/disable, if necessary.
      mnuFileClose.Enabled = blnEnable
      mnuEditUndo.Enabled = blnEnable
      mnuEditCut.Enabled = blnEnable
      mnuEditCopy.Enabled = blnEnable
      mnuEditPaste.Enabled = blnEnable
      mnuWndCascade.Enabled = blnEnable
      mnuWndTitleHorizontal.Enabled = blnEnable
      mnuWndTitleVertical.Enabled = blnEnable
      With tlbToolBar.Buttons
         .Item("Close").Enabled = blnEnable
         .Item("Undo").Enabled = blnEnable
         .Item("Cut").Enabled = blnEnable
         .Item("Copy").Enabled = blnEnable
         .Item("Paste").Enabled = blnEnable
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the Edit menu & its corresponding buttons on the tool bar based on a data
'   form's mode.
' Disable all buttons when no data form is open.
Public Sub SwchMnuMode(ByVal intMode As Integer)
On Error GoTo ErrHnd
   With gobSetng
      Select Case intMode
      Case .ModeAdd
         Call SwchMnuModeAdd
      Case .ModeEdit
         Call SwchMnuModeEdit
      Case .ModeDel
         Call SwchMnuModeDel
      Case .ModeOff
         Call SwchMnuModeOff
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If there is another open ShG form first make sure its ID is properly set.
' Load a new ShG form.
' Register it in the DatFrms collection.
Public Sub LoadNewShG()
On Error GoTo ErrHnd
   Dim frmNewShG As frmShG
   If BlankVld(gobSetng.FrmShGNam) Then 'Check another ShG form & its ID.
      Set frmNewShG = New frmShG 'Create a new data form & register it in the collctn
      Call RegistFrm(frmNewShG) 'Register & show the new form.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new SumGenEval report.
Public Sub LoadNewSumGenEval()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxSumGenEval 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new SumPerform report.
Public Sub LoadNewSumPerform()
On Error GoTo ErrHnd
   Set mfrmRptFarmDate = New frmRptFarmDate
   mintIdxRpt = mfrmRptFarmDate.IdxSumPerform 'The report index.
   mfrmRptFarmDate.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new SumFlockManagm form.
Public Sub LoadNewSumFlockManagm()
On Error GoTo ErrHnd
   Load frmSumFlockManagm
   frmSumFlockManagm.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new Cert form.
Public Sub LoadNewCert()
On Error GoTo ErrHnd
   Load frmCert
   frmCert.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Check to make sure there is no more same blank form.
' Return True, if succeeds. Otherwise focus the found form.
Private Function BlankVld(ByVal strFrmNam As String) As Boolean
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   Dim blnFail As Boolean
   If gobDatFrms.Count > 0 Then 'Proceed, if there forms.
      For Each obDatFrm In gobDatFrms
         With obDatFrm
            If .FrmHostNam = strFrmNam Then
               If .IDFrm = "" Then
                  blnFail = True
                  Call BlankFoc(strFrmNam) 'Focus the other blank form.
                  Exit For
                End If
            End If
         End With
      Next
   End If
   BlankVld = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' If there is already a blank form the same as the newly loaded one focus the former.
' Test if a form is blank by scanning the data form's IDSheepGoat property.
' If there are more than one similar blank forms unload them.
Private Sub BlankFoc(ByVal strFrmNam As String)
On Error GoTo ErrHnd
   Dim frmForm As Form
   Dim obDatFrm As DatFrm
   Dim blnFound As Boolean
   For Each frmForm In Forms 'Loop through all forms.
      If frmForm.Name = strFrmNam Then 'Scan the same forms only.
         Set obDatFrm = frmForm 'View the data form's ID.
         If obDatFrm.IDFrm = "" Then 'Focus the first one or unload the rest.
            If blnFound = False Then
               frmForm.SetFocus
               blnFound = True
            Else
               gobMsgInst.DuplFrm = True 'Mark this duplicate form to ecape the
               Unload frmForm        'DatFrms.Del method.
            End If
         End If
      End If
   Next frmForm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the active data form's specified mode.
' If the form is dirty cancel the current changes & set the new mode.
Private Sub ModeSetAct(ByVal intMode As Integer)
On Error GoTo ErrHnd
   Dim obDatFrm  As DatFrm 'Below: 'Cancel the current changes.
   Set obDatFrm = frmMDI.ActiveForm
   With obDatFrm
      If .IsDirty Then 'Set the new mode.
         Call frmMDI.ActiveForm.cmdCancel_Click
         .ModeSet intMode
      Else
         .ModeSet intMode 'Set the mode.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Display a message, if specified, in the staStatusBar status bar. Change the mouse
'  pointer.
' Otherwise set the status bar & mouse pointer to a normal mode.
Public Sub StatusMsg(ByVal blnDispMsg As Boolean, Optional ByVal strMsg As String)
On Error GoTo ErrHnd
   With staStatusBar
      If blnDispMsg Then
         .SimpleText = strMsg & LoadResString(100) 'Display a message.
         .Style = sbrSimple
         .Refresh
         Screen.MousePointer = vbHourglass 'Hourglass mouse pointer.
      Else
         .Style = sbrNormal 'Remove the status bar message.
         .Refresh
         Screen.MousePointer = vbDefault
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count MDI-child forms.
Public Function CountFrm() As Integer
On Error GoTo ErrHnd
   Dim frmForm As Form
   For Each frmForm In Forms
      If frmForm.Name <> Me.Name Then 'Skip this non MDI-child form itself.
         If frmForm.MDIChild = True Then CountFrm = CountFrm + 1 'MDI-child form.
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Place the specified window to a windows-default position.
' Move to the left top, if the right bottom locates outside the frmMDI form.
' Escape the operation, if the window is maximised.
Public Sub WinPosn(ByRef frmForm As Form, ByVal lngWdth As Long, ByVal lngHght As Long)
On Error GoTo ErrHnd
   Dim lngWdthFrm As Long
   Dim lngWdthMDI As Long
   Dim lngHghtFrm As Long
   Dim lngHghtMDI As Long
   With gobSetng
      Select Case .FrmChldStat 'Set the state.
      Case vbMaximized, vbNormal 'Previous, if max/normal.
         frmForm.WindowState = .FrmChldStat
      Case vbMinimized 'Normal, if a previous window was minimized.
         frmForm.WindowState = vbNormal
      End Select
      If frmForm.WindowState = vbNormal Then 'Proceed, unless maximised/minimised.
         frmForm.Height = IIf(lngHght > 0, lngHght, 0) 'Resize the window.
         frmForm.Width = IIf(lngWdth > 0, lngWdth, 0) 'Must be positive.
         If CountFrm = 1 Then 'And .Reports = 0 Then
            .ChldLft = 0 'Place the 1st window to the left top.
            .ChldTop = 0
         Else
            .ChldLft = .ChldLft + .IndtFrmCscd
            .ChldTop = .ChldTop + .IndtFrmCscd
         End If
         frmForm.Left = .ChldLft 'Place the window.
         frmForm.Top = .ChldTop
         lngHghtFrm = frmForm.Top + frmForm.Height 'The form's & frmMDI's sizes.
         lngHghtMDI = Me.Top + Me.Height - .IndtFrmBtm
         lngWdthFrm = frmForm.Left + frmForm.Width
         lngWdthMDI = Me.Left + Me.Width - .IndtFrmRght
         If (lngHghtFrm > lngHghtMDI) Or (lngWdthFrm > lngWdthMDI) Then 'Compare
            frmForm.Left = 0                             'the right bottom with frmMDI.
            frmForm.Top = 0
         End If
         .ChldLft = frmForm.Left 'Remember the last position.
         .ChldTop = frmForm.Top
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the Edit menu & its corresponding buttons on the tool bar for the Add mode.
Private Sub SwchMnuModeAdd()
On Error GoTo ErrHnd
   staStatusBar.Panels.Item("pnlText").Text = LoadResString(370) '"Ввод записи"
   staStatusBar.Refresh
'   If blnDataChand Then
'      mnuFileAdd.Enabled = False 'Menu.
'      mnuFileEdit.Enabled = False
'      mnuFileAdd.Checked = True
'      mnuFileEdit.Checked = False
'      mnuFileDel.Enabled = False
'      mnuFileDel.Checked = False
'      With tlbToolBar.Buttons 'Tool bar.
'         .Item("Add").Enabled = False
'         .Item("Edit").Enabled = False
'         .Item("Add").Value = tbrPressed
'         .Item("Del").Enabled = False
'      End With
'   Else
      mnuFileAdd.Enabled = True 'Menu.
      mnuFileEdit.Enabled = True
      mnuFileAdd.Checked = True
      mnuFileEdit.Checked = False
      mnuFileDel.Enabled = True
      mnuFileDel.Checked = False
      With tlbToolBar.Buttons 'Tool bar.
         .Item("Add").Enabled = True
         .Item("Edit").Enabled = True
         .Item("Add").Value = tbrPressed
         .Item("Del").Enabled = True
      End With
'   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the Edit menu & its corresponding buttons on the tool bar for the Edit mode.
Private Sub SwchMnuModeEdit()
On Error GoTo ErrHnd
   staStatusBar.Panels.Item("pnlText").Text = LoadResString(371) '"Исправление записи"
   staStatusBar.Refresh
'   If blnDataChand Then
'      mnuFileAdd.Enabled = False 'Menu.
'      mnuFileEdit.Enabled = False
'      mnuFileAdd.Checked = False
'      mnuFileEdit.Checked = True
'      mnuFileDel.Enabled = False
'      mnuFileDel.Checked = False
'      With tlbToolBar.Buttons 'Tool bar.
'         .Item("Add").Enabled = False
'         .Item("Edit").Enabled = False
'         .Item("Edit").Value = tbrPressed
'         .Item("Del").Enabled = False
'      End With
'   Else
      mnuFileAdd.Enabled = True 'Menu.
      mnuFileEdit.Enabled = True
      mnuFileAdd.Checked = False
      mnuFileEdit.Checked = True
      mnuFileDel.Enabled = True
      mnuFileDel.Checked = False
      With tlbToolBar.Buttons 'Tool bar.
         .Item("Add").Enabled = True
         .Item("Edit").Enabled = True
         .Item("Edit").Value = tbrPressed
         .Item("Del").Enabled = True
      End With
      staStatusBar.Panels.Item("pnlText").Text = LoadResString(371) '"Исправление записи"
      staStatusBar.Refresh
'   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the Edit menu & its corresponding buttons on the tool bar for the Del mode.
Private Sub SwchMnuModeDel()
On Error GoTo ErrHnd
   staStatusBar.Panels.Item("pnlText").Text = LoadResString(372) '"Удаление записи"
   staStatusBar.Refresh
'   If blnDataChand Then
'      mnuFileAdd.Enabled = False 'Menu.
'      mnuFileEdit.Enabled = False
'      mnuFileAdd.Checked = False
'      mnuFileEdit.Checked = False
'      mnuFileDel.Enabled = False
'      mnuFileDel.Checked = True
'      With tlbToolBar.Buttons 'Tool bar.
'         .Item("Add").Enabled = False
'         .Item("Edit").Enabled = False
'         .Item("Del").Value = tbrPressed
'         .Item("Del").Enabled = False
'      End With
'   Else
      mnuFileAdd.Enabled = True 'Menu.
      mnuFileEdit.Enabled = True
      mnuFileAdd.Checked = False
      mnuFileEdit.Checked = False
      mnuFileDel.Enabled = True
      mnuFileDel.Checked = True
      With tlbToolBar.Buttons 'Tool bar.
         .Item("Add").Enabled = True
         .Item("Edit").Enabled = True
         .Item("Del").Value = tbrPressed
         .Item("Del").Enabled = True
      End With
'   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable all buttons, if no data form is open.
Private Sub SwchMnuModeOff()
On Error GoTo ErrHnd
   If CountFrm = 1 Then 'Check open data forms.
      staStatusBar.Panels.Item("pnlText").Text = LoadResString(373) '"Готово"
      staStatusBar.Refresh
      mnuFileAdd.Enabled = False 'Menu.
      mnuFileEdit.Enabled = False
      mnuFileAdd.Checked = False
      mnuFileEdit.Checked = False
      mnuFileDel.Enabled = False
      mnuFileDel.Checked = False
      With tlbToolBar.Buttons 'Tool bar.
         .Item("Add").Value = tbrUnpressed
         .Item("Edit").Value = tbrUnpressed
         .Item("Del").Value = tbrUnpressed
         .Item("Add").Enabled = False
         .Item("Edit").Enabled = False
         .Item("Del").Enabled = False
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the mstrKeyBtnMnu variable to the clicked menu button's key to invoke the
'  respective procedure on the tlbToolBar ButtonClick event, if it's ivoked later.
' Set the FrmBlk button's tool tip text to the last clicked menu button's text.
Private Sub tlbToolBar_ButtonMenuClick(ByVal ButtonMenu As MSComctlLib.ButtonMenu)
On Error GoTo ErrHnd
   Select Case ButtonMenu.Key 'Select the button menu item.
   Case mstrKeyInvenMatBlk 'InvenMatBlk.
      mstrKeyBtnMnu = mstrKeyInvenMatBlk
   Case mstrKeyInvenMat 'InvenMat.
      mstrKeyBtnMnu = mstrKeyInvenMat
   Case mstrKeyLmK 'LmK.
      mstrKeyBtnMnu = mstrKeyLmK
   Case mstrKeyWtLmK 'WtLmK.
      mstrKeyBtnMnu = mstrKeyWtLmK
   Case mstrKeyWtWool 'WtWool.
      mstrKeyBtnMnu = mstrKeyWtWool
   Case mstrKeyAppr 'Appr.
      mstrKeyBtnMnu = mstrKeyAppr
   Case mstrKeyDisp 'Disp.
      mstrKeyBtnMnu = mstrKeyDisp
   End Select
   tlbToolBar.Buttons.Item("FrmBlk").ToolTipText = ButtonMenu.Text
   Call ToolBarDo(mstrKeyFrmBlk) 'Execute the tool bar button's operation.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Invoke the specified TimerFrm form's procedure after the tmrTimer timer's delay.
Private Sub tmrTimer_Timer()
On Error GoTo ErrHnd
   tmrTimer.Enabled = False 'Disable.
   CallByName TimerObj, TimerProc, VbMethod
   Set TimerObj = Nothing 'Reset.
   TimerProc = ""
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the relevant to the specified data form's mode menu & tool bar till the current
'  change is saved/canceled.
' Set the form's IsDirty mark to True.
Public Sub SetIsDirtyMnu(ByRef obDatFrm As DatFrm)
On Error GoTo ErrHnd
   With obDatFrm
      If Not .IsDirty Then
         .IsDirty = True
         Call SwchMnuMode(.Mode)
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Register a new data form in the collection, set it to the Edit mode & show it.
Private Sub RegistFrm(ByRef frmNew As Form)
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   Set obDatFrm = frmNew
   With obDatFrm 'Initialise.
      .IDFrm = ""
      .RegistFrm "", False 'Register.
      .ModeSet gobSetng.ModeEdit 'Set the Edit mode.
   End With
   frmNew.Show 'Show.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Implement a button's assinged action.
Private Sub ToolBarDo(ByVal strKey As String)
On Error GoTo ErrHnd
   Const strKeyBrsShG As String = "BrsShG"
   Const strKeyAdd As String = "Add"
   Const strKeyEdit As String = "Edit"
   Const strKeyDel As String = "Del"
   Const strKeyUndo As String = "Undo"
   Const strKeyCut As String = "Cut"
   Const strKeyCopy As String = "Copy"
   Const strKeyPaste As String = "Paste"
   Const strKeyClose As String = "Close"
   Dim obDatFrm As DatFrm
   Dim strProc As String
   Select Case strKey
   Case strKeyBrsShG
      Call mnuFileFrmBrsShG_Click 'Browse ShG's.
   Case strKeyAdd 'Set an Add, Edit & Del mode.
      Call ModeSetAct(gobSetng.ModeAdd)
   Case strKeyEdit
      Call ModeSetAct(gobSetng.ModeEdit)
   Case strKeyDel
      Call ModeSetAct(gobSetng.ModeDel)
   Case strKeyUndo 'Undo.
       Call mnuEditUndo_Click
   Case strKeyCut 'Cut.
       Call mnuEditCut_Click
   Case strKeyCopy 'Copy.
       Call mnuEditCopy_Click
   Case strKeyPaste 'Paste.
       Call mnuEditPaste_Click
   Case mstrKeyFrmBlk 'FrmBlk.
      Select Case mstrKeyBtnMnu 'Select the button menu item.
      Case mstrKeyInvenMatBlk, ""  'InvenMatBlk.
         Call mnuFrmBlkInvenMatBlk_Click
      Case mstrKeyInvenMat 'InvenMat.
         Call mnuFrmBlkInvenMat_Click
      Case mstrKeyLmK 'LmK.
         Call mnuFrmBlkLmK_Click
      Case mstrKeyWtLmK 'WtLmK.
         Call mnuFrmBlkWtLmK_Click
      Case mstrKeyWtWool 'WtWool.
         Call mnuFrmBlkWtWool_Click
      Case mstrKeyAppr 'Appr.
         Call mnuFrmBlkAppr_Click
      Case mstrKeyDisp 'Disp.
         Call mnuFrmBlkDisp_Click
      End Select
   Case strKeyClose 'Close.
       Call CloseExit
   Case Else 'Load a new form.
      strProc = "LoadNew" & strKey
      CallByName Me, strProc, VbMethod
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the SetngForm Ado constorls in all open settings forms. Make delay to let Access
'  refresh the new data & refresh them in the RefrshSetng1 procedure.
Public Sub RefrshSetng(ByVal blnRefrshTree As Boolean)
On Error GoTo ErrHnd
   Const lntTimeIntrv As Long = 500 'The timer's interval.
   Const strTimerProc As String = "RefrshSetng1"
   mblnRefrshTree = blnRefrshTree 'Set the variable to use in the RefrshSetng1 proc.
   Set TimerObj = Me 'Specify the arguments for the timer
   tmrTimer.Interval = lntTimeIntrv 'Set the interval.
   TimerProc = strTimerProc
   tmrTimer.Enabled = True 'Inovke the RefrshSetng1 procedure.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the SetngForm Ado constorls in all open settings forms.
Public Sub RefrshSetng1()
On Error GoTo ErrHnd
   Dim obSetngFrm As SetngFrm
   Dim obDatFrm As DatFrm
   If Not RefrshSusp Then 'Check if refreshing is suspended.
      For Each obDatFrm In gobDatFrms 'Look for SetngFrm-type DatFrm's.
         If obDatFrm.IsSetngFrm Then
            Set obSetngFrm = obDatFrm.FrmHost 'Link to the host form.
            obSetngFrm.RefrshAdo 'Refresh the Ados.
         End If
      Next
   End If
   If mblnRefrshTree Then
      mblnRefrshTree = False 'Reset.
      frmBrsShG.TblTree.RefrshAll 'Mark to refresh frmBrsShG's tree, unless canceled.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return True, if refreshing setting forms' ado's has been suspended from a ShG form for
'  the period of the open transaction.
' Unless refreshing has been already suspended (& consiquently marked to resume) mark to
'  resume refreshing after the transaction. Ohterwise return False to let resume
'  refreshing.
Private Function RefrshSusp() As Boolean
On Error GoTo ErrHnd
   Dim obSetngFrm As SetngFrm
   Dim obDatFrm As DatFrm
   For Each obDatFrm In gobDatFrms 'Look for SetngFrm-type DatFrm's.
      If obDatFrm.IsSetngFrm Then
         Set obSetngFrm = obDatFrm.FrmHost 'Link to the host form.
         With obSetngFrm
            If .RefrshSusp Then
               RefrshSusp = True 'Suspended.
               Exit For
            End If
         End With
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

