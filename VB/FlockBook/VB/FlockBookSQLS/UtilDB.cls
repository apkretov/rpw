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

Const mstrUserSA As String = "sa" 'The system administator's login.
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

' Export the current DB tables to *.txt files to the main directory's Export
'  subdirectory. Apply the BCP utility to export the data.
' Skip hidden tables.
Public Sub Export()
On Error GoTo ErrHnd
   Const strFldrExpNam As String = "Export"
   Dim strPromt As String
   Dim I As Integer
   Dim blnFail As Boolean
   If OprnConf(mintOprnExp) Then 'Confirm.
      Set mfrmPath = New frmPath 'Promt to choose a folder to export to.
      Call PathFrmOpen(mfrmPath, strFldrExpNam, LoadResString(736), frmMDI)
      Set mfrmPath = Nothing 'Explicitly destroy after the export folder is selected.
      If mstrFldrPath <> "" Then 'Path defined?
         Call frmMDI.StatusMsg(True, LoadResString(103)) 'Status bar message.
         If FillTblFl Then 'Compose the file list.
            For I = 0 To mintTbls - 1 'Cycle through all tables.
               If Not ExecBCP(mintOprnExp, mstrFldrPath, I) Then 'Export
                  blnFail = True 'Exit on ExportDo failure.
                  Exit For
               End If
            Next
            Call frmMDI.StatusMsg(False) 'Remove the status bar message.
            If Not blnFail Then 'Message, if succeeded.
               strPromt = LoadResString(737) & mstrFldrPath & LoadResString(738) & _
                  LoadResString(733)
               MsgBox strPromt, vbInformation, LoadResString(740)
            End If
         End If
      End If
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Call frmMDI.StatusMsg(False) 'Remove the status bar message.
End Sub

' Get the server, DB, user & password last saved in the windows registry.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Const strServerLocal As String = "(local)" 'The local default server.
   With App
      Server = GetSetting(.ProductName, mstrStngLogin, mstrStngServer, strServerLocal)
      DB = GetSetting(.ProductName, mstrStngLogin, mstrStngDB, .ProductName)
      User = GetSetting(.ProductName, mstrStngLogin, mstrStngUser, mstrUserSA)
      Pwd = GetSetting(.ProductName, mstrStngLogin, mstrStngPwd)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the server, DB, user & password last saved in the windows registry.
Private Sub Class_Terminate()
On Error GoTo ErrHnd
   With App
      SaveSetting .ProductName, mstrStngLogin, mstrStngServer, Server
      SaveSetting .ProductName, mstrStngLogin, mstrStngDB, DB
      SaveSetting .ProductName, mstrStngLogin, mstrStngUser, User
      SaveSetting .ProductName, mstrStngLogin, mstrStngPwd, Pwd
   End With
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
   mstrTblFl(0, mintArrFl) = "ShG.txt"""
   mstrTblFl(1, mintArrTbl) = "BrsShG_Mate"
   mstrTblFl(1, mintArrFl) = "Mate.txt"""
   mstrTblFl(2, mintArrTbl) = "BrsShG_LmK"
   mstrTblFl(2, mintArrFl) = "LmK.txt"""
   mstrTblFl(3, mintArrTbl) = "BrsShG_WtLmK"
   mstrTblFl(3, mintArrFl) = "WtLmK.txt"""
   mstrTblFl(4, mintArrTbl) = "BrsShG_WtWool"
   mstrTblFl(4, mintArrFl) = "WtWool.txt"""
   mstrTblFl(5, mintArrTbl) = "BrsShG_Appr"
   mstrTblFl(5, mintArrFl) = "Appr.txt"""
   FillTblFl = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

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
Rem 1: Watch this & deFlockBook.FlockBook .CursorLocation as adUseClient: why did they
'  need adUseServer? Rename the gcnnConnServ & gcnnConnClnt connections, if works. In the
'  latter positive case unite the two connections on one & test again how the only one
'  will work beacause I deliberately created the gcnnConnClnt connection for necessary
'  features.
     .CursorLocation = adUseClient ' adUseServer
     .Open strCnnStr
   End With
   If blnDoAllCnn Then 'Connect, if required.
      With gcnnConnClnt 'Client-side connection.
        If .State = adStateOpen Then .Close 'Close to open again.
        .ConnectionTimeout = lngCnnTimeout
        .CursorLocation = adUseClient
        .Open strCnnStr
      End With
      With deFlockBook.FlockBook 'Data environment's DB.
        If .State = adStateOpen Then .Close 'Close to open again.
        .CommandTimeout = lngCnnTimeout
        .CursorLocation = adUseClient 'adUseServer
        .ConnectionString = strCnnStr
        .Open 'Verify this later again.
      End With
   End If
   Connect = True 'Succeeded.
Exit Function
ErrHnd:
   MsgBox Err.Description
   Connect = False 'Failed.
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
   If Connect(False, mstrDBMaster) Then 'Connect to the master DB.
      strCmdTxt = "SELECT name FROM sysdatabases WHERE name = '" & strDB & "'"
      With rstSysDB
         .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockBatchOptimistic, adCmdText
         If .BOF = False And .EOF = False Then Exists = True 'Eists.
      End With
      If strDBOrig <> "" Then Call Connect(False, strDBOrig) 'Connect to orig. DB, if any
   End If
Exit Function
ErrHnd:
Debug.Assert 0 = 1 'Verify
   Call ConnectOrig(False, strDBOrig) ''Connect to the original DB, if disconnected.
   MsgBox Err.Description
End Function

' Execute a strPathName BCP export operation.
' Return True, if succeeds.
Private Function ExecBCP(ByVal intOprn As Integer, ByVal strFldrPath As String, ByVal _
   intIdx As Integer) As Boolean
On Error GoTo ErrHnd
   Const strBCP As String = "bcp """
   Const strDbo As String = ".dbo."
   Const strOut As String = """ out """
   Const strTxtWU As String = " -w -U "
   Const strP As String = " -P """
   Dim strPathName As String
   Dim dblRetVal As Double
   strFldrPath = AddPathSlash(strFldrPath) 'Add a back slash.
   strPathName = strBCP & DB & strDbo & mstrTblFl(intIdx, mintArrTbl) & strOut & _
      strFldrPath & mstrTblFl(intIdx, mintArrFl) & strTxtWU & User & strP & Pwd & "" 'Compose the path name for 'the BCP."
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

' Set the SQL Server busy/not busy.
' For the busy state: if busy promt to retry.
' Return True, if succeeds.
Public Function BusySet(ByVal blnBusy As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim obTblBusy As TblBusy
   Dim obDatTbl As DatTbl
   Dim strPromt As String
   Dim intResp As Integer
   Set obTblBusy = New TblBusy
   Set obDatTbl = obTblBusy
   If Not blnBusy Then
      obTblBusy.Busy = False 'Set not busy.
      obDatTbl.Upd
   Else
      Do 'Set busy.
         If Busy Then
            strPromt = LoadResString(82) & String$(2, vbCrLf) & LoadResString(84)
            intResp = MsgBox(strPromt, vbInformation + vbAbortRetryIgnore + _
               vbDefaultButton2, LoadResString(81)) 'Promt to retry.
            If intResp = vbIgnore Then BusySet = BusyRest 'Reset the busy mark.
         Else
            intResp = vbCancel
            obTblBusy.Busy = True 'Mark busy.
            obDatTbl.Upd
            BusySet = True 'Succeeded.
         End If
      Loop While intResp = vbRetry 'Loop, if retried.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if the SQL Server is busy with preparing a report.
Public Function Busy() As Boolean
On Error GoTo ErrHnd
   Dim obTblBusy As TblBusy
   Dim obDatTbl As DatTbl
   Set obTblBusy = New TblBusy
   Set obDatTbl = obTblBusy
   obDatTbl.Sel
   Busy = obTblBusy.Busy
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Reset the SQL Sever's busy state to allow making reports.
' This is an emergency administrative task. It's required in the following cases:
'  - the Busy table's busy mark is permanantly left busy;
'  - another client's report takes too long;
'  - the Busy table is corrupted.
' Empty the Busy table altogether & insert a new record with a False value.
' Return True, if succeeds.
Private Function BusyRest() As Boolean
On Error GoTo ErrHnd
   Dim obTblBusy As TblBusy
   Dim obDatTbl As DatTbl
   Beep
   If MsgBox(LoadResString(83), vbQuestion + vbYesNo, LoadResString(81)) = vbYes Then 'Proceed?
      Set obTblBusy = New TblBusy
      Set obDatTbl = obTblBusy
      obDatTbl.Del 'Empty the table.
      obTblBusy.Busy = False 'Insert Not-busy record.
      obDatTbl.Ins
      BusyRest = True 'Succeeded.
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

' Get the sa user's name.
Public Property Get UserSA() As Variant
   UserSA = mstrUserSA
End Property

' Get the master DB's name.
Public Property Get DBMaster() As Variant
   DBMaster = mstrDBMaster
End Property

' Connect to original DB, if any.
Public Sub ConnectOrig(ByVal blnDoAllCnn As Boolean, ByVal strDBOrig As String)
On Error GoTo ErrHnd
   If strDBOrig <> "" Then Call Connect(blnDoAllCnn, strDBOrig)
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
   With frmMDI.dlgFile 'Promt to specify the backup file.
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

' Execute the Backup procedure's part 2 after backing up the DB.
Public Sub Backup2()
On Error GoTo ErrHnd
   Dim strCmdTxtBackup As String
   If VldFreeMB(mstrFlBackup, DBSize) Then 'Enough free disk space?
      Call frmMDI.StatusMsg(True, LoadResString(756) & ". ") 'Message about backing up.
      strCmdTxtBackup = _
         "BACKUP DATABASE [" & DB & "] " & _
            "TO DISK = '" & mstrFlBackup & "' " & _
               "WITH INIT"
      gcnnConnServ.Execute strCmdTxtBackup, , adCmdText + adExecuteNoRecords
      Call frmMDI.StatusMsg(False) 'Remove message.
      Call BackupSucc(mstrFlBackup, DB, LoadResString(756))
   End If
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   Call frmMDI.StatusMsg(False) 'Remove message.
   MsgBox Err.Description
End Sub

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

' Change the password.
Public Sub PwdSet(ByVal strUser As String, ByVal strPwdNew As String)
On Error GoTo ErrHnd
   Const strSP As String = "sp_password "
   Const strNull As String = "NULL, "
   Dim strDBOrig As String
   Dim strCmdTxt As String
   strDBOrig = DB 'Save the original DB.
   If Connect(False, mstrDBMaster) Then 'Connected to the master DB?
      strCmdTxt = strSP & IIf(Pwd = "", strNull, "'" & Pwd & "', ") & IIf(strPwdNew = _
         "", strNull, "'" & strPwdNew & "', ") & strUser 'Substiture zero strings by Null
      gcnnConnServ.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
      If strUser = User Then Pwd = strPwdNew 'Save the new password in the Win registry, if it's the current user's.
      Call ConnectOrig(False, strDBOrig) 'Connect to the original DB.
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
   If strDBOrig <> "" Then Call ConnectOrig(False, strDBOrig) 'Connect to the original DB, if disconnected.
End Sub
