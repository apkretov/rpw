VERSION 5.00
Begin VB.Form frmPath 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   6090
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7515
   Icon            =   "frmPath.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6090
   ScaleWidth      =   7515
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.FileListBox filFile 
      Height          =   3990
      Left            =   3780
      TabIndex        =   11
      Top             =   2000
      Width           =   3705
   End
   Begin VB.Frame fraDrive 
      Caption         =   "&Диск"
      Height          =   1575
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   5895
      Begin VB.DriveListBox drvDrive 
         Height          =   315
         Left            =   120
         TabIndex        =   1
         ToolTipText     =   "F4 - Открыть список"
         Top             =   360
         Width           =   2535
      End
      Begin VB.Label lblFreeMBLbl 
         Caption         =   "Сводобно, МБ:"
         Height          =   255
         Index           =   2
         Left            =   3120
         TabIndex        =   4
         Top             =   720
         Width           =   1155
      End
      Begin VB.Label lblTotalMBLbl 
         Caption         =   "Размер, МБ:"
         Height          =   255
         Index           =   1
         Left            =   3120
         TabIndex        =   2
         Top             =   360
         Width           =   1155
      End
      Begin VB.Label lblFreeMB 
         Alignment       =   1  'Right Justify
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   4560
         TabIndex        =   5
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label lblTotalMB 
         Alignment       =   1  'Right Justify
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   4560
         TabIndex        =   3
         Top             =   360
         Width           =   1215
      End
      Begin VB.Label lblPercentLbl 
         Caption         =   "Сводобно:"
         Height          =   255
         Index           =   0
         Left            =   3120
         TabIndex        =   6
         Top             =   1080
         Width           =   1035
      End
      Begin VB.Label lblPercent 
         Alignment       =   1  'Right Justify
         BorderStyle     =   1  'Fixed Single
         Height          =   315
         Left            =   4560
         TabIndex        =   7
         Top             =   1080
         Width           =   1215
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "&ОК"
      Height          =   375
      Left            =   6240
      TabIndex        =   12
      Tag             =   "OK"
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   375
      Left            =   6240
      TabIndex        =   13
      Tag             =   "Cancel"
      Top             =   720
      Width           =   1215
   End
   Begin VB.DirListBox dirDirect 
      Height          =   3915
      Left            =   60
      TabIndex        =   9
      Top             =   2040
      Width           =   3705
   End
   Begin VB.Label lblFile 
      Caption         =   "&Файл:"
      Height          =   255
      Left            =   3840
      TabIndex        =   10
      Top             =   1800
      Width           =   615
   End
   Begin VB.Label lblDrive 
      Caption         =   "Ди&ректорий:"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1800
      Width           =   1095
   End
End
Attribute VB_Name = "frmPath"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mstrFldrPath As String
Dim mstrFlPath As String
Dim FreeMB As Single
Dim mstrDriveOrig As String

Public Event PathDefnd(ByVal FldrPath As String, ByVal FlPath As String, ByVal FreeMB _
   As Single) 'The path defined event.

' Deafualt folder to be shown.
Public Property Let FldrPathDeflt(ByVal strFldrPathDeflt As String)
   mstrFldrPath = strFldrPathDeflt
End Property

' Reset & hide.
Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
   Call ResetHide
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Raise the Path event to send the path to an ouside consumer.
' Reset & hide.
Private Sub cmdOk_Click()
On Error GoTo ErrHnd
   Call ResetHide
   RaiseEvent PathDefnd(mstrFldrPath, mstrFlPath, FreeMB)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the mstrFldrPath variable.
Private Sub dirDirect_Change()
On Error GoTo ErrHnd
   mstrFldrPath = dirDirect.Path
   filFile.Path = dirDirect.Path
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Enable Enter to change a directory.
Private Sub dirDirect_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   If KeyAscii = gobFormtCtl.AscEnter Then dirDirect.Path = dirDirect.List(dirDirect _
      .ListIndex)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Syncronise the dirDirect directory list box with the drvDrive drive list box.
Private Sub drvDrive_Change()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Set obUtilDB = New UtilDB
   With drvDrive
      If obUtilDB.IsDrvReady(drvDrive) Then 'Regarding floppy disk & CD mainly: is a disk inserted?
         dirDirect.Path = .Drive
         mstrDriveOrig = .Drive
      Else 'No disk - restore the original drive.
         .SetFocus
         .Drive = mstrDriveOrig
      End If
   End With
   mstrFldrPath = dirDirect.Path
   Call DiskSpace
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the original drive to restore it in the drvDrive_Change procedure, if necessary.
Private Sub drvDrive_GotFocus()
On Error GoTo ErrHnd
   mstrDriveOrig = drvDrive.Drive
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Compose a clicked file's path.
Private Sub filFile_Click()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Set obUtilDB = New UtilDB
   With filFile
      mstrFlPath = obUtilDB.FlPathComps(.Path, .FileName)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the dirDirect control's path to the early specified default path or, unless
'  otherwise stated, to the application's path.
' Get the disk's statistics
' Focus the dirDirect directroy list by default.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   If mstrFldrPath = "" Then mstrFldrPath = App.Path 'Set to the app.'s path, if empty.
   drvDrive.Drive = mstrFldrPath
   dirDirect.Path = mstrFldrPath
   Call DiskSpace
   dirDirect.SetFocus
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the disk's statistics: free, total & free percent space.
Private Sub DiskSpace()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Dim fsoFSO As FileSystemObject
   Dim fsoDrive As Drive
   Dim sngTotalSize As Single
   Dim sngPercent As Single
   Set fsoFSO = New FileSystemObject
   Set fsoDrive = fsoFSO.GetDrive(drvDrive.Drive)
   With fsoDrive
      If .IsReady Then 'Regarding floppy disk & CD mainly: is a disk inserted?
         Set obUtilDB = New UtilDB
         sngTotalSize = obUtilDB.ConvByteToMB(.TotalSize)
         FreeMB = obUtilDB.ConvByteToMB(.FreeSpace)
         sngPercent = .FreeSpace / .TotalSize
      Else 'No disk.
         FreeMB = 0
      End If
   End With
   lblTotalMB = gobFormtCtl.NumMB(sngTotalSize) 'Show the statistics.
   lblFreeMB = gobFormtCtl.NumMB(FreeMB)
   lblPercent = Format$(sngPercent, "Percent")
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset caption, file pattern. Focus the drvDrive control.
' Hide the form.
Private Sub ResetHide()
On Error GoTo ErrHnd
   Me.Caption = ""
   filFile.Pattern = ""
   drvDrive.SetFocus
   Me.Hide
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
