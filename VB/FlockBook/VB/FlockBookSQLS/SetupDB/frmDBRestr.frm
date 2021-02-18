VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form frmDBRestr 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Установка базы данных"
   ClientHeight    =   4950
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7320
   Icon            =   "frmDBRestr.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4950
   ScaleWidth      =   7320
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin MSDataListLib.DataList dblDBServ 
      Height          =   450
      Left            =   5340
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   1800
      Width           =   1755
      _ExtentX        =   3096
      _ExtentY        =   794
      _Version        =   393216
   End
   Begin VB.CommandButton cmdPathSrc 
      Height          =   375
      Left            =   6720
      Picture         =   "frmDBRestr.frx":0442
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   2520
      Width           =   375
   End
   Begin VB.TextBox txtPathSrc 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   2400
      TabIndex        =   6
      Top             =   2520
      Width           =   4245
   End
   Begin VB.TextBox txtPathDest 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   2400
      TabIndex        =   9
      Top             =   3120
      Width           =   4245
   End
   Begin VB.CommandButton cmdPathDest 
      Caption         =   "..."
      Height          =   375
      Left            =   6720
      TabIndex        =   10
      Top             =   3120
      Width           =   375
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Height          =   360
      Left            =   4560
      TabIndex        =   11
      Tag             =   "OK"
      Top             =   4440
      Width           =   1215
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   360
      Left            =   5880
      TabIndex        =   12
      Tag             =   "Cancel"
      Top             =   4440
      Width           =   1215
   End
   Begin VB.TextBox txtDB 
      Height          =   315
      IMEMode         =   3  'DISABLE
      Left            =   2400
      TabIndex        =   2
      Top             =   1800
      Width           =   1605
   End
   Begin MSAdodcLib.Adodc adoDBServ 
      Height          =   330
      Left            =   5340
      Top             =   2160
      Visible         =   0   'False
      Width           =   1755
      _ExtentX        =   3096
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
      Caption         =   "adoDBServ"
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
   Begin MSComDlg.CommonDialog dlgFile 
      Left            =   0
      Top             =   4440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label lblDBServ 
      Caption         =   "Базы данных на сервере:"
      Height          =   375
      Left            =   4200
      TabIndex        =   3
      Top             =   1800
      Width           =   1095
   End
   Begin VB.Label lblPathSrc 
      Caption         =   "&Создать из резервной копии:"
      Height          =   495
      Left            =   360
      TabIndex        =   5
      Top             =   2430
      Width           =   1935
   End
   Begin VB.Label lblNote 
      BackColor       =   &H8000000E&
      BorderStyle     =   1  'Fixed Single
      Height          =   975
      Left            =   0
      TabIndex        =   0
      Top             =   -50
      Width           =   7335
   End
   Begin VB.Line linButton 
      BorderColor     =   &H80000005&
      Index           =   1
      X1              =   0
      X2              =   7350
      Y1              =   4215
      Y2              =   4215
   End
   Begin VB.Line linButton 
      BorderColor     =   &H80000011&
      Index           =   0
      X1              =   0
      X2              =   7350
      Y1              =   4200
      Y2              =   4200
   End
   Begin VB.Label lblPathDest 
      Caption         =   "&Поместить базу данных в директорий:"
      Height          =   375
      Left            =   360
      TabIndex        =   8
      Top             =   3090
      Width           =   1935
   End
   Begin VB.Label lblDB 
      Caption         =   "&Название базы данных:"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   1800
      Width           =   1935
   End
End
Attribute VB_Name = "frmDBRestr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private WithEvents mfrmPath As frmPath
Attribute mfrmPath.VB_VarHelpID = -1
Dim mobUtilDB As UtilDB

Const mintFreeMBMin As Integer = 100 'The min disk free space required.

Const mstrFlPhys1Affx As String = "_root.mdf" 'FlockBook DB physical files names'
Const mstrFlPhys2Affx As String = "_data1.ndf" 'affixes with file extentions.
Const mstrFlPhys3Affx As String = "_logdata1.ldf"

Dim mblnIsDirty As Boolean

' Unload the form, if it's clear.
' Clear the controls.
' Return the focus to the txtDB textbox.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   If mblnIsDirty Then 'Cancel.
      Call CtlClear
      txtDB.SetFocus
      mblnIsDirty = False 'Mark clear.
   Else 'Unload.
      Unload Me
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Create a new DB.
' Validate the input parameters.
' Confirm new DB creation.
' Unload the form, if succeeds.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   If VldFillCtl Then 'Control filled?
      If VldUniqueDB Then 'Unique DB name?
         If VldUniqueFl Then 'Wiil DB files be unique?
            If mobUtilDB.VldFreeMB(txtPathDest, mintFreeMBMin) Then 'Enough disk space?
               With mobUtilDB
                  If .OprnConf(.OprnRestr) Then 'Confirm the operation.
                     Call Util.SwchBtnMouse(Me, False) 'Switch buttons & mouse.
                     If RestoreDB Then 'Restored?
                        Unload Me
                     Else
                        Call Util.SwchBtnMouse(Me, True) 'Leave form to correct an error.
                     End If
                  End If
               End With
            End If
         End If
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
Resume Next 'Switch buttons & mouse.
End Sub

' Open the frmPath form to get a path for a new DB.
' Show the application's Data folder by default. Create the folder, if missing.
Private Sub cmdPathDest_Click()
On Error GoTo ErrHnd
   Const strFldrDataNam As String = "Data" 'The Data folder's name.
   mobUtilDB.PathFrmOpen mfrmPath, strFldrDataNam, LoadResString(741), Me
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open the Common Dialog box to let the user select a DB backup to write its path in the
'  txtPathSrc text box.
Private Sub cmdPathSrc_Click()
On Error GoTo ErrHnd
   Dim strFldrBackup As String
   With mobUtilDB
      strFldrBackup = .AddPathSlash(App.Path) & .BackupFldrNam
      .FldrCreate strFldrBackup 'Create the backup folder, if missing.
   End With
   With dlgFile
      .DialogTitle = LoadResString(745)
      .Filter = LoadResString(755) & mobUtilDB.BackupFlExt & ")|*" & mobUtilDB _
         .BackupFlExt & "|" & LoadResString(757)
      .InitDir = strFldrBackup
      .FileName = "" 'Delete, if any.
      .Flags = cdlOFNHideReadOnly
      .ShowOpen
      If .FileName <> "" Then txtPathSrc = .FileName
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Make sure SQL Server is running. Quit the application, if canceled.
' Load frmLogon to connect to the server's master DB.
Private Sub KTB_Form_Activate()
On Error GoTo ErrHnd
'   Static blnPassed As Boolean
'   If Not blnPassed Then 'Execute once.
'      blnPassed = True
'      frmLogon.Show vbModal, Me
'   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Make sure SQL Server is running. Quit the application, if canceled.
' Load frmLogon to connect to the server's master DB.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   If Not blnPassed Then 'Execute once.
      blnPassed = True
      If MsgBox(LoadResString(768), vbInformation + vbOKCancel) = vbCancel Then
         Unload Me
      Else
         frmLogon.Show vbModal, Me
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Mark a change.
Private Sub Form_KeyPress(KeyAscii As Integer)
   mblnIsDirty = True
End Sub

' Switch the menu.
' Set the msngFreeMB variable to the active drive's free space.
' Load the mfrmPath object.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set gcnnConnServ = New ADODB.Connection
   Set gobFormtCtl = New FormtCtl
   Set mobUtilDB = New UtilDB
   Set mfrmPath = New frmPath
   Call InitCtl 'Initilase controls.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Destroy the gloabal objects.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   Set gcnnConnServ = Nothing
   Set gobFormtCtl = Nothing
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the Path argument's value to the txtPathDest control.
' Get a selected disk's free space.
' Mark a change.
Private Sub mfrmPath_PathDefnd(ByVal FldrPath As String, ByVal FlPath As String, ByVal _
   FreeMB As Single)
On Error GoTo ErrHnd
   txtPathDest = FldrPath
   mblnIsDirty = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear controls.
Private Sub CtlClear()
On Error GoTo ErrHnd
   txtDB = ""
   txtPathSrc = ""
   txtPathDest = ""
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Show an error message & focus the respective control.
Private Sub MsgErr(ByVal strPromt As String, ctlCtl As Control)
On Error GoTo ErrHnd
   MsgBox strPromt, vbCritical, LoadResString(131)
   ctlCtl.SetFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub PREV_txtDB_GotFocus()
On Error GoTo ErrHnd
'   gobFormtCtl.SelTxt txtDB
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the DB name's symbols so that
'  - the 1st symbol be a letter;
'  - no invalid-file-name symbol be contained i.e. \ / : * ? " < > | & a blank space.
Private Sub txtDB_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   Const intAscDblQuotn As Integer = 34 'The double quotation mark's ASC code.
   Dim intAsc1st As Integer
   Dim blnSuccess As Boolean
   If txtDB <> "" Then 'Full?
      txtDB = Trim$(txtDB)
      intAsc1st = Asc(Left$(txtDB, 1))
      With gobFormtCtl
         Select Case intAsc1st
         Case .AscEngUpA To .AscEngUpZ, .AscEngLowA To .AscEngLowZ, .AscRusUpA To _
            .AscRusUpZ, .AscRusLowA To .AscRusLowZ 'Vld characters.
            If InStr(txtDB, "\") = 0 Then If InStr(txtDB, "/") = 0 Then If InStr(txtDB, _
               ":") = 0 Then If InStr(txtDB, "*") = 0 Then If InStr(txtDB, "?") = 0 Then _
               If InStr(txtDB, Chr(intAscDblQuotn)) = 0 Then If InStr(txtDB, "<") = 0 _
               Then If InStr(txtDB, ">") = 0 Then If InStr(txtDB, "|") = 0 Then If _
               InStr(txtDB, Space(1)) = 0 Then blnSuccess = True 'Succeeded.
         End Select
      End With
      If Not blnSuccess Then 'Failed.
         Cancel = True 'Restrict the focus.
         Call MsgErr(LoadResString(744), txtDB)
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the control.
Private Sub txtPathDest_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtPathDest
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Connect to a newly created DB.
' Return if the user chooses to connect to.
Private Function ConnectNew() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   strPromt = "Создание/восстановление базы данных '" & txtDB & "' завершено успешно. Зайти в " & _
      "новую базу данных сейчас?"
Debug.Assert 0 = 1 'Verify the promt & title
   If MsgBox(strPromt, vbQuestion + vbYesNo, Me.Caption) = vbYes Then
      ConnectNew = True 'Connect.
      mobUtilDB.Connect True, txtDB
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise the form's controls.
Private Sub InitCtl()
On Error GoTo ErrHnd
   lblNote = vbCrLf & Space$(5) & LoadResString(760) & vbCrLf & Space$(10) & _
      LoadResString(761) & mintFreeMBMin & LoadResString(762) & vbCrLf & Space$(10) & _
      LoadResString(763)
   cmdPathSrc.ToolTipText = LoadResString(745)
   cmdPathDest.ToolTipText = LoadResString(741)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Verify that the specified directory exists.
Private Sub txtPathDest_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   Const intLengDrvMax As Integer = 3 'The maximal length of a drive's name.
   Const intLengDrv1 As Integer = 1 'The options of drive name length.
   Const intLengDrv2 As Integer = 2
   Dim fsoFSO As FileSystemObject
   Dim intLengPath As Integer
   Dim intAscFst As String
   Dim blnDrv As Boolean
   If txtPathDest <> "" Then 'Full?
      intLengPath = Len(txtPathDest) 'The the path's length.
      If intLengPath <= intLengDrvMax Then 'Drive vs. folder?
         intAscFst = Asc(UCase(Left$(txtPathDest, 1))) 'The 1st symbol's ASC.
         If intAscFst >= gobFormtCtl.AscEngUpA And intAscFst <= gobFormtCtl.AscEngUpZ _
            Then 'Is the 1st symbol an English letter to represent a drive?
            Select Case intLengPath
            Case intLengDrv1 'One letter - treat as a drive.
               blnDrv = True
            Case intLengDrv2 'Is a back slash after the drive letter?
               If Right(txtPathDest, 1) = ":" Then blnDrv = True
            Case intLengDrvMax 'Are a colon & back slash after the drive letter?
               If Mid(txtPathDest, 2, 1) = ":" And Right(txtPathDest, 1) = "\" Then blnDrv _
                  = True
            End Select
         End If
      End If
      Set fsoFSO = New FileSystemObject
      With fsoFSO
         If blnDrv Then 'Validate as a drive.
            If Not .DriveExists(txtPathDest) Then 'Exists?
               Cancel = True 'Desn't exist.
               Call MsgErr(LoadResString(751) & txtPathDest & LoadResString(183), _
                  txtPathDest)
            ElseIf Not mobUtilDB.IsDrvReady(txtPathDest) Then 'Ready?
               Cancel = True 'Isn't ready.
            End If
         Else 'Validate as a directory.
            If Not .FolderExists(txtPathDest) Then 'Exists?
               Cancel = True 'Desn't exist.
               Call MsgErr(LoadResString(743) & txtPathDest & LoadResString(183), _
                  txtPathDest)
            End If
         End If
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select the text.
Private Sub txtPathSrc_GotFocus()
On Error GoTo ErrHnd
   gobFormtCtl.SelTxt txtPathSrc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Verify that the specified file exists.
Private Sub txtPathSrc_Validate(Cancel As Boolean)
On Error GoTo ErrHnd
   Dim fsoFSO As FileSystemObject
   If txtPathSrc <> "" Then 'Full?
      Set fsoFSO = New FileSystemObject
      If Not fsoFSO.FileExists(txtPathSrc) Then
         Cancel = True 'Restrict the focus.
         Call MsgErr(LoadResString(742) & txtPathSrc & LoadResString(183), txtPathSrc)
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate how the controls are filled.
' Return True, if succeeds.
Private Function VldFillCtl() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If txtDB = "" Then
      Call Util.MissParam(txtDB, lblDB)
   ElseIf txtPathSrc = "" Then
      Call Util.MissParam(txtPathSrc, lblPathSrc)
   ElseIf txtPathDest = "" Then
      Call Util.MissParam(txtPathDest, lblPathDest)
   Else
      VldFillCtl = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Restore a DB from the specified backup.
' Return True, if succeeds.
Private Function RestoreDB() As Boolean
On Error GoTo ErrHnd
   Dim strCmdTxtRestr As String
   Dim strCmdTxtOpt As String
   Dim strDBOrig As String
   With mobUtilDB
      strDBOrig = .DB 'Remember the original DB.
      If .Connect(False, .DBMaster) Then 'Connect to the master DB.
         strCmdTxtRestr = CmdTxtRestr 'Create a Restore command text.
         If strCmdTxtRestr <> "" Then 'Created?
            gcnnConnServ.Execute strCmdTxtRestr, , adCmdText + adExecuteNoRecords 'Create a DB.
            strCmdTxtOpt = CmdTxtOpt 'Set DB's options.
            If strCmdTxtOpt <> "" Then gcnnConnServ.Execute strCmdTxtOpt, , adCmdText _
               + adExecuteNoRecords
         End If
      End If
      Call AddDefltUser 'Add default users.
      If .Exists(txtDB) Then MsgBox LoadResString(732) & LoadResString(739), _
         vbInformation, LoadResString(732)
   End With
   RestoreDB = True 'Succeeded.
Exit Function
ErrHnd:
   With gcnnConnServ.Errors
      If .Count > 0 Then
         MsgBox .Item(0) 'Show the 1st error only.
         .Clear
      Else
         MsgBox Err.Description
      End If
   End With
End Function

' Restore a DB from the specified backup.
' Return True, if succeeds.
Private Function PREV_RestoreDB() As Boolean
'On Error GoTo ErrHnd
'   Dim strCmdTxtRestr As String
'   Dim strCmdTxtOpt As String
'   Dim strDBOrig As String
'   With mobUtilDB
'      strDBOrig = .DB 'Remember the original DB.
'      If .Connect(False, .DBMaster) Then 'Connect to the master DB.
'         strCmdTxtRestr = CmdTxtRestr 'Create a Restore command text.
'         If strCmdTxtRestr <> "" Then 'Created?
'            gcnnConnServ.Execute strCmdTxtRestr, , adCmdText + adExecuteNoRecords 'Create a DB.
'            strCmdTxtOpt = CmdTxtOpt 'Set DB's options.
'            If strCmdTxtOpt <> "" Then gcnnConnServ.Execute strCmdTxtOpt, , adCmdText _
'               + adExecuteNoRecords
'         End If
'      End If
'      .ConnectOrig False, strDBOrig 'Connect to original DB, if any.
'Debug.Assert 0 = 1 'Verify AddDefltUser
'   Call AddDefltUser 'Add default users.
'      If .Exists(txtDB) Then MsgBox LoadResString(732) & LoadResString(739), _
'         vbInformation, LoadResString(732)
'   End With
'   RestoreDB = True 'Succeeded.
'Exit Function
'ErrHnd:
'   With gcnnConnServ.Errors
'      If .Count > 0 Then
'         MsgBox .Item(0) 'Show the 1st error only.
'         .Clear
'      Else
'         MsgBox Err.Description
'      End If
'   End With
'   mobUtilDB.ConnectOrig False, strDBOrig 'Connect to original DB, if any.
End Function

' Validate that a new DB be unique to prevent overtyping an existing DB. Query the Master
'  DB's sysdatabases table to search the new DB's name.
' Return True to allow creating a new DB.
Private Function VldUniqueDB() As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   If mobUtilDB.Exists(txtDB) Then 'Exists already?
      strPromt = LoadResString(746) & txtDB & LoadResString(747)
      Call MsgErr(strPromt, txtDB)
   Else
      VldUniqueDB = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Create the command to restore a DB.
' Return True, if succeeds.
Private Function CmdTxtRestr() As String
On Error GoTo ErrHnd
   Const strFlLogic1 As String = "FlockBook_root" 'FlockBook DB logical file names.
   Const strFlLogic2 As String = "FlockBook_data1"
   Const strFlLogic3 As String = "FlockBookLog_data1"
   CmdTxtRestr = _
      "RESTORE DATABASE [" & txtDB & "] " & _
         "FROM DISK = '" & txtPathSrc & "' " & _
            "WITH MOVE '" & strFlLogic1 & "' TO '" & FlPhys(mstrFlPhys1Affx) & "', " & _
               "MOVE '" & strFlLogic2 & "' TO '" & FlPhys(mstrFlPhys2Affx) & "', " & _
               "MOVE '" & strFlLogic3 & "' TO '" & FlPhys(mstrFlPhys3Affx) & "'"
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that none of a new DB files exist in the selected folder.
' Return True, if none exists.
Private Function VldUniqueFl() As Boolean
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Dim fsoFSO As FileSystemObject
   Dim strPromt As String
   Set obUtilDB = New UtilDB
   Set fsoFSO = New FileSystemObject
   With fsoFSO
      If .FileExists(FlPhys(mstrFlPhys1Affx)) = False And .FileExists(FlPhys( _
         mstrFlPhys2Affx)) = False And .FileExists(FlPhys(mstrFlPhys3Affx)) = False Then
         VldUniqueFl = True 'Succeeded.
      Else
Debug.Assert 0 = 1 'Verify LoadResString(749)
         strPromt = LoadResString(743) & txtPathDest & LoadResString(748) & txtDB & _
            mstrFlPhys1Affx & "', '" & txtDB & mstrFlPhys2Affx & "', '" & txtDB & _
            mstrFlPhys3Affx & LoadResString(749)
         Call MsgErr(strPromt, txtPathDest)
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Create a command to set the restored DB's options.
Private Function CmdTxtOpt() As String
On Error GoTo ErrHnd
   CmdTxtOpt = _
      "EXEC sp_dboption '" & txtDB & "', 'autoshrink', 'TRUE'" & vbLf & _
      "EXEC sp_dboption '" & txtDB & "', 'select into', 'TRUE'" & vbLf & _
      "EXEC sp_dboption '" & txtDB & "', 'trunc. log on chkpt.', 'TRUE'"
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the restored DB's physical file name based on the specified file affix.
Private Function FlPhys(ByVal strFlPhysAffx As String) As String
On Error GoTo ErrHnd
   FlPhys = mobUtilDB.AddPathSlash(txtPathDest) & txtDB & strFlPhysAffx
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add 9 default users: user1 to user9.
Private Sub AddDefltUser()
On Error Resume Next 'Resume to complete adding the users.
   Const strSPAddLogin As String = "sp_addlogin " 'Add login SP.
   Const strSPRole As String = "sp_addsrvrolemember " 'The SP to add a login as a member of a fixed server role.
   Const strSysadmin As String = ", 'sysadmin'" 'The System Administrator fixed server role.
   Const strUserAffx As String = "user" 'User affix.
   Const intCountUser As Integer = 9 'Count of users.
   Dim strCmdTxt As String
   Dim strUser
   Dim I As Integer
   For I = 1 To intCountUser
      strUser = strUserAffx & CStr(I)
      strCmdTxt = strSPAddLogin & strUser
      gcnnConnServ.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
      strCmdTxt = strSPRole & strUser & strSysadmin
      gcnnConnServ.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   Next
End Sub

' Add 9 default users: user1 to user9.
Private Sub PREV_AddDefltUser()
On Error Resume Next 'Resume to complete adding the users.
'   Const strSP As String = "sp_addlogin "
'   Const strUser As String = "user" 'User affix.
'   Const intCountUser As Integer = 9 'Count of users.
'   Dim strCmdTxt As String
'   Dim I As Integer
'   For I = 1 To intCountUser
'      strCmdTxt = strSP & strUser & CStr(I)
'      gcnnConnServ.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
''      sp_addsrvrolemember 'user1', 'sysadmin'
'   Next
End Sub
