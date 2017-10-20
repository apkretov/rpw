VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UtilDB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim WithEvents mfrmPath As frmPath
Attribute mfrmPath.VB_VarHelpID = -1

Const mstrStngLogin As String = "Login" 'The Windows registry seting section & keys.
Const mstrStngServer As String = "Server"
Const mstrStngDB As String = "DB"
Const mstrStngUser As String = "User"
Const mstrStngPwd As String = "Pwd"

Const mintOprnBackup As Integer = 1
Const mintOprnRestr As Integer = 2
Const mintOprnExp As Integer = 4

Const mstrDBMaster = "master"
Const mstrBackupFldrNam As String = "Backup" 'The Backup folder's name.
Const mstrBackupFlExt As String = ".bak" 'The DB backup file name's extention.

Const mintTbls As Integer = 6 'Number of tables/files.
Const mintArrTbl As Integer = 0 'Array index for tables.
Const mintArrFl As Integer = 1 'Array index for files.

Dim mstrTblFl(mintTbls - 1, 1) As String

Dim mstrFldrPath As String
Dim mstrFlBackup As String

Public Server As String 'SQL Server.
Public DB As String 'SQL Server DB.
Public User As String 'User name.
Public Pwd As String 'User's password.

' Get the server, DB, user & password last saved in the windows registry.
Private Sub PREV_Class_Initialize()
On Error GoTo ErrHnd
'   Const strServerLocal As String = "(local)" 'The local default server.
'   Const strUserSA As String = "sa" 'The system administator's login.
'   With App
'      Server = GetSetting(.ProductName, mstrStngLogin, mstrStngServer, strServerLocal)
'      DB = GetSetting(.ProductName, mstrStngLogin, mstrStngDB, .ProductName)
'      User = GetSetting(.ProductName, mstrStngLogin, mstrStngUser, strUserSA)
'      Pwd = GetSetting(.ProductName, mstrStngLogin, mstrStngPwd)
'   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the server, DB, user & password last saved in the windows registry.
Private Sub PREV_Class_Terminate()
On Error GoTo ErrHnd
'   With App
'      SaveSetting .ProductName, mstrStngLogin, mstrStngServer, Server
'      SaveSetting .ProductName, mstrStngLogin, mstrStngDB, DB
'      SaveSetting .ProductName, mstrStngLogin, mstrStngUser, User
'      SaveSetting .ProductName, mstrStngLogin, mstrStngPwd, Pwd
'   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Remember the selected folder's path for the Import procedure.
Private Sub mfrmPath_PathDefnd(ByVal FldrPath As String, ByVal FlPath As String, ByVal _
   FreeMB As Single)
On Error GoTo ErrHnd
   mstrFldrPath = FldrPath
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fill the mstrTblFl array with the tables' & respective files' names.
' Return True, if succeeds.
Private Function FillTblFl() As Boolean
On Error GoTo ErrHnd
   mstrTblFl(0, mintArrTbl) = "BrsShG_ShG"
   mstrTblFl(0, mintArrFl) = "ShG.txt"
   mstrTblFl(1, mintArrTbl) = "BrsShG_Mate"
   mstrTblFl(1, mintArrFl) = "Mate.txt"
   mstrTblFl(2, mintArrTbl) = "BrsShG_LmK"
   mstrTblFl(2, mintArrFl) = "LmK.txt"
   mstrTblFl(3, mintArrTbl) = "BrsShG_WtLmK"
   mstrTblFl(3, mintArrFl) = "WtLmK.txt"
   mstrTblFl(4, mintArrTbl) = "BrsShG_WtWool"
   mstrTblFl(4, mintArrFl) = "WtWool.txt"
   mstrTblFl(5, mintArrTbl) = "BrsShG_Appr"
   mstrTblFl(5, mintArrFl) = "Appr.txt"
   FillTblFl = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

'Add a back slash before the file name, if missing.
Public Function AddPathSlash(ByVal strFldrPath As String) As String
On Error GoTo ErrHnd
   If Right$(strFldrPath, 1) = "\" Then
      AddPathSlash = strFldrPath
   Else
      AddPathSlash = strFldrPath & "\"
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Setup operation's mark.
Public Property Get OprnRestr() As Integer
   OprnRestr = mintOprnRestr
End Property

' Get the Backup folder name.
Public Property Get BackupFldrNam() As String
   BackupFldrNam = mstrBackupFldrNam
End Property

' Get the DB backup file name's extention.
Public Property Get BackupFlExt() As String
   BackupFlExt = mstrBackupFlExt
End Property

' Confirm restore, backup or export operation.
' Return True, if confirmed.
Public Function OprnConf(ByVal intOprn As Integer) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim strTitle As String
   Select Case intOprn
   Case mintOprnRestr
      strPromt = LoadResString(730) & LoadResString(733)
      strTitle = LoadResString(732)
   Case mintOprnExp
      strPromt = LoadResString(734)
      strTitle = LoadResString(740)
   End Select
   If MsgBox(strPromt, vbOKCancel + vbInformation, strTitle) = vbOK Then OprnConf = True
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate if a new DB is unique to prevent overtyping an existing DB. Query the Master
'  DB's sysdatabases table to search the new DB's name.
' Return True to allow creating a new DB.
Public Function Exists(ByVal strDB As String) As Boolean
On Error GoTo ErrHnd
   Dim rstSysDB As ADODB.Recordset
   Dim strDBOrig As String
   Dim strCmdTxt As String
   Set rstSysDB = New ADODB.Recordset
   strDBOrig = DB 'Remember the original DB.
   strCmdTxt = "SELECT name FROM sysdatabases WHERE name = '" & strDB & "'"
   With rstSysDB
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockBatchOptimistic, adCmdText
      If .BOF = False And .EOF = False Then Exists = True 'Eists.
   End With
   If strDBOrig <> "" Then Call Connect(False, strDBOrig) 'Connect to orig. DB, if any
Exit Function
ErrHnd:
   MsgBox Err.Description
End Function

' Validate if a new DB is unique to prevent overtyping an existing DB. Query the Master
'  DB's sysdatabases table to search the new DB's name.
' Return True to allow creating a new DB.
Private Function KTB_Exists(ByVal strDB As String) As Boolean
'On Error GoTo ErrHnd
'   Dim rstSysDB As ADODB.Recordset
'   Dim strDBOrig As String
'   Dim strCmdTxt As String
'   Set rstSysDB = New ADODB.Recordset
'   strDBOrig = DB 'Remember the original DB.
'   If Connect(False, mstrDBMaster) Then 'Connect to the master DB.
'      strCmdTxt = "SELECT name FROM sysdatabases WHERE name = '" & strDB & "'"
'      With rstSysDB
'         .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockBatchOptimistic, adCmdText
'         If .BOF = False And .EOF = False Then Exists = True 'Eists.
'      End With
'      If strDBOrig <> "" Then Call Connect(False, strDBOrig) 'Connect to orig. DB, if any
'   End If
'Exit Function
'ErrHnd:
'Debug.Assert 0 = 1 'Verify
'   Call ConnectOrig(False, strDBOrig) ''Connect to the original DB, if disconnected.
'   MsgBox Err.Description
End Function

' Execute a strPathName BCP export operation.
' Return True, if succeeds.
Private Function ExecBCP(ByVal intOprn As Integer, ByVal strFldrPath As String, ByVal _
   intIdx As Integer) As Boolean
On Error GoTo ErrHnd
   Const strBCP As String = "bcp "
   Const strDbo As String = ".dbo."
   Const strOut As String = " out "
   Const strTxtWU As String = " -w -U "
   Const strP As String = " -P "
   Dim strPathName As String
   Dim dblRetVal As Double
   strFldrPath = AddPathSlash(strFldrPath) 'Add a back slash.
   strPathName = strBCP & DB & strDbo & mstrTblFl(intIdx, mintArrTbl) & strOut & _
      strFldrPath & mstrTblFl(intIdx, mintArrFl) & strTxtWU & User & strP & Pwd 'Compose the path name for 'the BCP.
   dblRetVal = Shell(strPathName, vbMinimizedFocus)
   If dblRetVal = 0 Then 'Verify the result.
      MsgBox LoadResString(735), vbCritical, LoadResString(131)
   Else
      ExecBCP = True 'Succeeded.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Drop reports' temporary tables in the DB.
Public Sub DropTblRpt()
On Error GoTo ErrHnd
   gcnnConnServ.Execute "spDropTable_SumFlockManagm", , adCmdStoredProc + _
      adExecuteNoRecords
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Convert bytes to megabytes.
Public Function ConvByteToMB(ByVal sngByte As Single) As Single
On Error GoTo ErrHnd
   Const lngByteToMB As Long = 1048576 'The byte to MB convertion coefficient.
   ConvByteToMB = sngByte / lngByteToMB
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Compose a clicked file's path distinguishing Root/sub- directory to avoid double "\".
Public Function FlPathComps(ByVal strFldrPath As String, ByVal strFlNam As String) _
   As String
On Error GoTo ErrHnd
   Dim strFlPath As String
   If Right$(strFldrPath, 1) = "\" Then
      strFlPath = strFldrPath & strFlNam
   Else
      strFlPath = strFldrPath & "\" & strFlNam
   End If
   FlPathComps = strFlPath 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the master DB's name.
Public Property Get DBMaster() As Variant
   DBMaster = mstrDBMaster
End Property

' Connect to original DB, if any.
Private Sub KTB_ConnectOrig(ByVal blnDoAllCnn As Boolean, ByVal strDBOrig As String)
On Error GoTo ErrHnd
'   If strDBOrig <> "" Then Call Connect(blnDoAllCnn, strDBOrig)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return True, if the existing drive is ready, i.e. a floppy or compact disk is inserted.
Public Function IsDrvReady(ByVal strDrv As String) As Boolean
On Error GoTo ErrHnd
   Dim fsoFSO As FileSystemObject
   Dim fsoDrive As Drive
   Dim strPromt As String
   Set fsoFSO = New FileSystemObject
   Set fsoDrive = fsoFSO.GetDrive(strDrv)
   If fsoDrive.IsReady Then 'Ready?
      IsDrvReady = True
   Else 'No disk in the drive.
      strPromt = LoadResString(751) & fsoDrive.Path & "\" & LoadResString(752)
      MsgBox strPromt, vbCritical, LoadResString(131)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the destination disk's free space that it be sufficient.
' Return True, if succeeds.
Public Function VldFreeMB(ByVal strPathWithDisk As String, ByVal sngFreeMBMin _
   As Single) As Boolean
On Error GoTo ErrHnd
   Dim fsoFSO As FileSystemObject
   Dim fsoDrive As Drive
   Dim sngFreeMB As Single
   Dim strPromt As String
   Set fsoFSO = New FileSystemObject
   With fsoFSO 'Free space.
      Set fsoDrive = .GetDrive(.GetDriveName(strPathWithDisk))
   End With
   sngFreeMB = ConvByteToMB(fsoDrive.FreeSpace) 'Free disk space.
   If sngFreeMB >= sngFreeMBMin Then 'Sufficient free space?
      VldFreeMB = True 'Succeeded.
   Else 'Space insufficient.
      With gobFormtCtl
         strPromt = LoadResString(764) & fsoDrive.Path & "\" & LoadResString(765) & _
            .NumMB(sngFreeMB) & LoadResString(766) & .NumMB(sngFreeMBMin) & _
            LoadResString(767)
      End With
      MsgBox strPromt, vbCritical, LoadResString(131)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the active DB's size in MB's by executing the sp_helpdb system SP.
Private Function DBSize() As Single
On Error GoTo ErrHnd
   Const intLengMB As Integer = 2 'The length of the MB string in the db_size feild of
   Dim rstHelpdb As ADODB.Recordset 'the sp_helpdb SP's recordset's.
   Dim strDBSizeFld As String
   Dim intLengDBSizeFld As Integer
   Set rstHelpdb = New ADODB.Recordset
   With rstHelpdb
      .Open "sp_helpdb", gcnnConnServ, adOpenDynamic, adLockOptimistic, _
         adCmdStoredProc
      .Find ("name = '" & DB & "'") 'Find the DB's record.
      If Not .BOF Then 'Found?
         strDBSizeFld = .Fields("db_size") 'Read the size field.
         intLengDBSizeFld = Len(strDBSizeFld) 'The size field's length.
         DBSize = CSng(Val(Trim$(Left$(strDBSizeFld, intLengDBSizeFld - intLengMB))))
      End If 'Above: Cut off the MB affix & read the size.
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Message about the backing up success, if the created file exists.
Public Sub BackupSucc(ByVal strFlPath As String, ByVal strDB As String, ByVal _
   strBackupRestr As String)
On Error GoTo ErrHnd
   Dim fsoFSO As FileSystemObject
   Dim strPromt As String
   Set fsoFSO = New FileSystemObject
   If fsoFSO.FileExists(strFlPath) Then
      strPromt = strBackupRestr & " '" & strDB & "'" & LoadResString(739)
      MsgBox strPromt, vbInformation, strBackupRestr
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the Backup procedure's part 1 before backing up the DB.
' Return True, if succeeds.
Public Function Backup1() As Boolean
On Error GoTo ErrHnd
   Dim strFldrBackup As String
   strFldrBackup = AddPathSlash(App.Path) & mstrBackupFldrNam 'Backup folder.
   Call FldrCreate(strFldrBackup) 'Create the backup folder, if missing.
Debug.Assert 0 = 1 'Verify frmDBRestr.dlgFile
   With frmDBRestr.dlgFile 'Promt to specify the backup file.
      .DialogTitle = LoadResString(754)
      .Filter = LoadResString(755) & mstrBackupFlExt & ")|*" & mstrBackupFlExt & "|" & _
         LoadResString(757)
      .InitDir = strFldrBackup
      .DefaultExt = mstrBackupFlExt 'Default backup extention.
      .Flags = cdlOFNHideReadOnly
      .FileName = "" 'Reset, unless used before.
      .ShowSave
      mstrFlBackup = .FileName 'Read the backup file name.
   End With
   If mstrFlBackup <> "" Then Backup1 = True 'Succeeds, if the backup file is selected.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Create the specified folder, if missing.
Public Sub FldrCreate(ByVal strFldrPath As String)
On Error GoTo ErrHnd
   Dim fsoFSO As FileSystemObject
   Set fsoFSO = New FileSystemObject
   If Not fsoFSO.FolderExists(strFldrPath) Then fsoFSO.CreateFolder strFldrPath
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open the frmPath form to let the user select a path.
' Show the specified default folder in the application's folder. Create the folder, if
'  missing.
Public Sub PathFrmOpen(ByRef frmPath As frmPath, ByVal strFldrDefltNam As String, ByVal _
   strCapt As String, ByRef frmOwnerForm As Form)
On Error GoTo ErrHnd
   Dim strFldrPathDeflt As String
   strFldrPathDeflt = AddPathSlash(App.Path) & strFldrDefltNam 'Default folder path.
   Call FldrCreate(strFldrPathDeflt) 'Create the folder path, if missing.
   With frmPath
      .Caption = strCapt
      .FldrPathDeflt = strFldrPathDeflt 'Show the default folder.
      .Show vbModal, frmOwnerForm
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Connect the gcnnConnServ connection to a DB & also, if all connections are
'  required to be connected, gcnnConnClnt & deFlockBook.
' Compose the connection string based on the module level variables: Server, DB ,User &
'  Pwd. The optional argument strDB shortens the code to connect to another DB given the
'  rest parameters unchanged.
' Return True, if succeeds.
Public Function Connect(ByVal blnDoAllCnn As Boolean, Optional ByVal strDB As String) _
   As Boolean
On Error GoTo ErrHnd
   Const lngCnnTimeout As Long = 30
   Dim strCnnStr As String
   If strDB <> "" Then DB = strDB 'Change the DB.
   strCnnStr = "driver={SQL Server};server=" & Server & ";uid=" & User & ";pwd=" & Pwd _
      & ";database=" & DB
   With gcnnConnServ 'Server-side connection.
     If .State = adStateOpen Then .Close 'Close to open again.
     .ConnectionTimeout = lngCnnTimeout
     .CursorLocation = adUseClient ' adUseServer
     .Open strCnnStr
   End With
   Connect = True 'Succeeded.
Exit Function
ErrHnd:
   MsgBox Err.Description
   Connect = False 'Failed.
End Function

' Start the specified SQL Server by means of the StartServ.dll library.
' Return True, if succeeds.
Private Function KTB_StartServ() As Boolean
On Error GoTo ErrHnd
'   Dim obStartServ As StartServ.UtilDB
'   Set obStartServ = New StartServ.UtilDB
'   With obStartServ
'      .Server = Server 'Iniitalase the library.
'      .DB = DB
'      .User = User
'      .Pwd = Pwd
'      StartServ = .StartServ 'Srart.
'   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the sa user's name.
Public Property Get UserSA() As Variant
   Const strUserSA As String = "sa" 'The system administator's login.
   UserSA = strUserSA
End Property

