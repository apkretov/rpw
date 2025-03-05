VERSION 5.00
Begin VB.Form frmWorldTime 
   Caption         =   "World Time"
   ClientHeight    =   2265
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4995
   Icon            =   "frmWorldTime.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   2265
   ScaleWidth      =   4995
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer tmrTimer 
      Interval        =   1000
      Left            =   0
      Top             =   240
   End
   Begin VB.Label lblTimerLbl 
      Caption         =   "Timer:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3480
      TabIndex        =   12
      Top             =   240
      Width           =   615
   End
   Begin VB.Label lblTimer 
      Caption         =   "00:00:00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4080
      TabIndex        =   11
      Top             =   240
      Width           =   840
   End
   Begin VB.Label lblTime 
      Caption         =   "00:00:00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   2
      Left            =   3480
      TabIndex        =   10
      Top             =   1680
      Width           =   1125
   End
   Begin VB.Label lblTime 
      Caption         =   "00:00:00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   1
      Left            =   1800
      TabIndex        =   9
      Top             =   1680
      Width           =   1125
   End
   Begin VB.Label lblTime 
      Caption         =   "00:00:00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   0
      Left            =   120
      TabIndex        =   8
      Top             =   1680
      Width           =   1125
   End
   Begin VB.Label lblTime 
      Alignment       =   2  'Center
      Caption         =   "00:00:00"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   3
      Left            =   1875
      TabIndex        =   7
      Top             =   480
      Width           =   1125
   End
   Begin VB.Label lblWokTime 
      Caption         =   "8:30 - 15:00"
      Height          =   255
      Index           =   2
      Left            =   3480
      TabIndex        =   6
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Label lblWokTime 
      Caption         =   "9:00 - 16:00"
      Height          =   255
      Index           =   1
      Left            =   1830
      TabIndex        =   5
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Label lblWokTime 
      Caption         =   "10:00 - 17:00"
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   4
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label lblCity 
      Alignment       =   2  'Center
      Caption         =   "Local Time"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   3
      Left            =   1695
      TabIndex        =   3
      Top             =   120
      Width           =   1605
   End
   Begin VB.Label lblCity 
      Caption         =   "New York"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   2
      Left            =   3480
      TabIndex        =   2
      Top             =   1080
      Width           =   1455
   End
   Begin VB.Label lblCity 
      Caption         =   "London"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   1
      Left            =   1830
      TabIndex        =   1
      Top             =   1080
      Width           =   1095
   End
   Begin VB.Label lblCity 
      Caption         =   "Tokyo"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   1080
      Width           =   975
   End
End
Attribute VB_Name = "frmWorldTime"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mstrSettings As String = "Settings"

Dim msngStart As Single

' Unload the form on Esc.
Private Sub Form_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   Const intEsc As Integer = 27 'The Esc key's code.
   If KeyAscii = intEsc Then Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the world time immediately on loading.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Me.Left = GetSetting(App.Title, mstrSettings, "Lft", 1000)
   Me.Top = GetSetting(App.Title, mstrSettings, "Top", 1000)
   msngStart = Timer
   Call tmrTimer_Timer
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the form's settings to apply at a next loading.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   If Me.WindowState <> vbMinimized Then 'MDI's settings.
      SaveSetting App.Title, mstrSettings, "Lft", Me.Left
      SaveSetting App.Title, mstrSettings, "Top", Me.Top
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the world time.
Private Sub tmrTimer_Timer()
On Error GoTo ErrHnd
   Const intCtTyo As Integer = 0 'The cities' constants.
   Const intCtLnd As Integer = 1
   Const intCtNY As Integer = 2
   Const intCtLoc As Integer = 3
   Const intDffrTyo As Integer = 5 'The local time to cities'time differences.
   Const intDffrLnd As Integer = -5
   Const intDffrNY As Integer = -11
   lblTime(intCtLoc) = DffrTime(0)
   lblTime(intCtTyo) = DffrTime(intDffrTyo)
   lblTime(intCtLnd) = DffrTime(intDffrLnd)
   lblTime(intCtNY) = DffrTime(intDffrNY)
   lblTimer = StopTime
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the world time.
Private Sub PREV_tmrTimer_Timer()
On Error GoTo ErrHnd
'   Const intCtTyo As Integer = 0 'The cities' constants.
'   Const intCtLnd As Integer = 1
'   Const intCtNY As Integer = 2
'   Const intCtLoc As Integer = 3
'   Const intDffrTyo As Integer = 4 'The local time to cities'time differences.
'   Const intDffrLnd As Integer = -5
'   Const intDffrNY As Integer = -10
'   lblTime(intCtLoc) = DffrTime(0)
'   lblTime(intCtTyo) = DffrTime(intDffrTyo)
'   lblTime(intCtLnd) = DffrTime(intDffrLnd)
'   lblTime(intCtNY) = DffrTime(intDffrNY)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the time with the specified time difference.
Private Function DffrTime(ByVal intDffr As Integer) As String
On Error GoTo ErrHnd
   DffrTime = TimeSerial(DffrHour(intDffr), Minute(Time), Second(Time))
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the hour based on the specified time difference.
Private Function DffrHour(ByVal intDffr As Integer) As Integer
On Error GoTo ErrHnd
   Const intDayBeg As Integer = 0 'The beginning & ending hours of the day.
   Const intDayEnd As Integer = 24
   Dim intDffrHour As Integer
   intDffrHour = Hour(Time) + intDffr
   If intDffrHour < intDayBeg Then 'Before the beginning?
      DffrHour = intDffrHour + intDayEnd
   ElseIf intDffrHour >= intDayEnd Then
      DffrHour = intDffrHour - intDayEnd
   Else
      DffrHour = intDffrHour
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Stop the time.
Private Function StopTime() As String
On Error GoTo ErrHnd
   Const intSecToMin As Integer = 60 'The seconds in a minutes.
   Const intSecToHr As Integer = 3600 'The seconds in an hour.
   Const intHrMax As Integer = 24 'The maximal ours in the day.
   Dim intSec As Integer
   Dim intMin As Integer
   Dim lngHr As Long
   Dim sngTime As Single
   sngTime = Timer - msngStart 'Get the unformatted time.
   lngHr = sngTime \ intSecToHr 'Hours.
   intMin = (sngTime - lngHr * intSecToHr) \ intSecToMin 'Minutes.
   intSec = sngTime - lngHr * intSecToHr - intMin * intSecToMin
   If lngHr >= intHrMax Then lngHr = lngHr Mod intHrMax 'More hours than in day?
   StopTime = TimeSerial(lngHr, intMin, intSec) 'Format the time.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
