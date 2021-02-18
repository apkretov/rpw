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

Const mstrStngLogin As String = "Login" 'The Windows registry seting section & keys.
Const mstrStngDB As String = "DB"
Const mstrStngPwd As String = "Pwd"

Const mintOprnBackup As Integer = 1
Const mintOprnExp As Integer = 2

'Const mstrFldrNamData As String = "Data" 'The Data folder's name.
Const mstrFldrNamBackup As String = "Backup" 'The Backup folder's name.
Const mstrDBFlExt As String = ".mdb" 'The Access DB file name's extention.

Const mintTbls As Integer = 6 'Number of tables/files.
Const mintArrTbl As Integer = 0 'Array index for tables.
Const mintArrFl As Integer = 1 'Array index for files.

Dim mstrTblFl(mintTbls - 1, 1) As String

Dim mstrFldrPath As String
Dim mstrFlBackup As String

Public DB As String 'SQL Server DB.
Public Pwd As String 'User's password.

' Get the server, DB, user & password last saved in the windows registry.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Dim strDBFlPath As String
   With App
      strDBFlPath = AddPathSlash(.Path) & .ProductName & mstrDBFlExt
      DB = GetSetting(.ProductName, mstrStngLogin, mstrStngDB, .Path & "\" & _
         .ProductName & mstrDBFlExt)
      Pwd = GetSetting(.ProductName, mstrStngLogin, mstrStngPwd)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the server, DB, user & password last saved in the windows registry.
Private Sub KTB_Class_Initialize()
On Error GoTo ErrHnd
'   Dim strDBFlPath As String
'   With App
'      strDBFlPath = AddPathSlash(.Path) & AddPathSlash(mstrFldrNamData) & .ProductName & _
'         mstrDBFlExt
'      DB = GetSetting(.ProductName, mstrStngLogin, mstrStngDB, .Path & "\" & _
'         .ProductName & mstrDBFlExt)
'      Pwd = GetSetting(.ProductName, mstrStngLogin, mstrStngPwd)
'   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the server, DB, user & password last saved in the windows registry.
Private Sub Class_Terminate()
On Error GoTo ErrHnd
   With App
      SaveSetting .ProductName, mstrStngLogin, mstrStngDB, DB
      SaveSetting .ProductName, mstrStngLogin, mstrStngPwd, Pwd
   End With
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

' Connect the gcnnConn connection to a DB & also, if all connections are
'  required to be connected, gcnnConnClnt & deFlockBook.
' Compose the connection string based on the module level variables: Server, DB ,User &
'  Pwd. The optional argument strDB shortens the code to connect to another DB given the
'  rest parameters unchanged.
' Return True, if succeeds.
Public Function Connect(ByVal blnDoAllCnn As Boolean, Optional ByVal strDB As String) _
   As Boolean
On Error GoTo ErrHnd
   Const lngCnnTimeout As Long = 30
   If strDB <> "" Then DB = strDB 'Change the DB.
   With deFlockBook.FlockBook 'Data environment's DB.
     If .State = adStateOpen Then .Close 'Close to open again.
     .CommandTimeout = lngCnnTimeout
     .CursorLocation = adUseClient
     .Open DB
   End With
   With gcnnConn 'Server-side connection.
     If .State = adStateOpen Then .Close 'Close to open again.
     .ConnectionTimeout = lngCnnTimeout
     .CursorLocation = adUseClient
     .Open deFlockBook.FlockBook.ConnectionString
   End With
   If blnDoAllCnn Then 'Connect, if required.
      Set gdbDB = OpenDatabase(DB)
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

' Confirm restore, backup or export operation.
' Return True, if confirmed.
Public Function OprnConf(ByVal intOprn As Integer) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim strTitle As String
   Select Case intOprn
   Case mintOprnExp
      strPromt = LoadResString(734)
      strTitle = LoadResString(740)
   End Select
   If MsgBox(strPromt, vbOKCancel + vbInformation, strTitle) = vbOK Then OprnConf = True
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
On Error Resume Next
   With gcnnConn
      .Execute "drop table [SumGenEval_Appraisal]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_ApprSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_FarmBrdSrOffsp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_Farms]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_Weight]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_WeightSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_Wool]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_WoolSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_Wt7Mon]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_Wt7MonSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_WtBirth]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_WtBirthSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_WtWean]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumGenEval_WtWeanSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_Appraisal]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_Farms]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_MaxAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_SheepGoat]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_Weight7Mon]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_WeightWean]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumPerform_WeightWoolAnnl]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Appraisal]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_BearDistr1]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_BearDistr2]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_BearDistr3]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_BearDistr4]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_BearDistr_AllAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female2All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female4All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female6All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male1All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male3All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male5All]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male1TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male1Total]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female2TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female2Total]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male3TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male3Total]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female4TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female4Total]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male5TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Male5Total]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female6TotalDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Disp_Female6Total]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Farms]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_LambKid]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_LambKidCount]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_LambKidWeaned]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Mate]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Offspring]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfAge_GreaseAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfAge_GreaseGroup]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfAge_WeightAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfAge_WeightGroup]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge_FarmSexAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge_WoolAnnl]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge_WoolMaxAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge_WtAnnl]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge_WtBirth]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_PerfSexAge_WtMaxAge]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Reprod]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Reprod_AbortCount]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Reprod_OffspBornCount]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_SheepGoat]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_SheepGoatDisp]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_Weight7Mon]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_WeightAnnl]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_WeightWean]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [SumFlockManagm_WoolAnnl]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_ApprAge_YrAll]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_Appraisal]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_PerfAge_YrAll]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_SheepGoat]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_SheepGoatDam]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_SheepGoatSire]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [Cert_WeightWoolAnnl]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertEweShegoat_LambKid]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertEweShegoat_Offspring]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_BV_Appr]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_BV_Weight]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_BV_Wool]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_BV_Wt7Mon]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_BV_WtBirth]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_BV_WtWean]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_Mate]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [CertRamHegoat_SireOffspring]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [FrmAppr]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [FrmInvMat]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [FrmLmK_LambKid]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [FrmLmK_Mate]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [FrmWtLmK]", , adCmdText + adExecuteNoRecords
      .Execute "drop table [FrmWtWool]", , adCmdText + adExecuteNoRecords
   End With
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
   strFldrBackup = AddPathSlash(App.Path) & mstrFldrNamBackup 'Backup folder.
   Call FldrCreate(strFldrBackup) 'Create the backup folder, if missing.
   With frmMDI.dlgFile 'Promt to specify the backup file.
      .DialogTitle = LoadResString(754)
      .Filter = LoadResString(755) & mstrDBFlExt & ")|*" & mstrDBFlExt
      .InitDir = strFldrBackup
      .DefaultExt = mstrDBFlExt 'Default backup extention.
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
   Dim fsoFSO As FileSystemObject
   Set fsoFSO = New FileSystemObject
   Dim strCmdTxtBackup As String
   Call frmMDI.StatusMsg(True, LoadResString(756) & ". ") 'Message about backing up.
'   Call CompctDB 'Compact the DB.
   fsoFSO.CopyFile DB, mstrFlBackup
   Call frmMDI.StatusMsg(False) 'Remove message.
   Call BackupSucc(mstrFlBackup, DB, LoadResString(756))
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

' Change the password.
Public Sub PwdSet(ByVal strPwdNew As String)
On Error GoTo ErrHnd
   Pwd = strPwdNew 'Save the new password in the Win registry, if it's the current user's.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Verify that the specified file exists.
' Return True, if succeeds.
Public Function FlExist(ByVal strFlPath As String) As Boolean
On Error GoTo ErrHnd
   Dim fsoFSO As FileSystemObject
   Dim strPromt As String
   Set fsoFSO = New FileSystemObject
   If fsoFSO.FileExists(strFlPath) Then
      FlExist = True 'Succeeded.
   Else
      strPromt = LoadResString(742) & strFlPath & LoadResString(183)
      MsgBox strPromt, vbCritical, LoadResString(131)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the spSelectInto_RptFarm SP.
Public Sub spSelectInto_RptFarm(ByVal strIDFarm As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Farms.IDFarm, Persons.Nam INTO RptFarm FROM Farms INNER JOIN Persons ON Farms.IDPersFarmer = Persons.IDPers " & _
      "WHERE Farms.IDFarm = """ & strIDFarm & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the Data folder name.
Private Property Get KTB_FldrNamData() As String
'   FldrNamData = mstrFldrNamData
End Property

' Get the Backup folder name.
Public Property Get FldrNamBackup() As String
Debug.Assert 0 = 1 'Verify
   FldrNamBackup = mstrFldrNamBackup
End Property

' Get the Access DB file name's extention.
Public Property Get DBFlExt() As String
   DBFlExt = mstrDBFlExt
End Property


