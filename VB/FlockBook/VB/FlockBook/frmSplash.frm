VERSION 5.00
Begin VB.Form frmSplash 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   4245
   ClientLeft      =   255
   ClientTop       =   1410
   ClientWidth     =   7380
   ClipControls    =   0   'False
   ControlBox      =   0   'False
   Icon            =   "frmSplash.frx":0000
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4245
   ScaleWidth      =   7380
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.Timer tmrTimer 
      Interval        =   500
      Left            =   240
      Top             =   3600
   End
   Begin VB.Frame fraSplash 
      Height          =   4050
      Left            =   150
      TabIndex        =   0
      Top             =   60
      Width           =   7080
      Begin VB.Frame fraLogo 
         BackColor       =   &H80000005&
         BorderStyle     =   0  'None
         Height          =   3135
         Left            =   120
         TabIndex        =   8
         Top             =   480
         Width           =   1935
         Begin VB.Image imgLogo 
            Height          =   1695
            Left            =   120
            Picture         =   "frmSplash.frx":000C
            Stretch         =   -1  'True
            Top             =   1200
            Width           =   1695
         End
         Begin VB.Image imgLogoCABS 
            Height          =   750
            Left            =   210
            Picture         =   "frmSplash.frx":104E
            Top             =   240
            Width           =   1500
         End
      End
      Begin VB.Label lblCopyright 
         Caption         =   "Copyright"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2400
         TabIndex        =   3
         Top             =   3240
         Visible         =   0   'False
         Width           =   1785
      End
      Begin VB.Label lblWarning 
         Alignment       =   2  'Center
         Caption         =   "Warning"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   195
         Left            =   240
         TabIndex        =   2
         Top             =   3660
         Width           =   6705
      End
      Begin VB.Label lblVersion 
         AutoSize        =   -1  'True
         Caption         =   "Version"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12.75
            Charset         =   204
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   4400
         TabIndex        =   4
         Top             =   2880
         Width           =   900
      End
      Begin VB.Label lblPlatform 
         AutoSize        =   -1  'True
         Caption         =   "Platform"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   4400
         TabIndex        =   5
         Top             =   3180
         Width           =   720
      End
      Begin VB.Label lblProductName 
         AutoSize        =   -1  'True
         Caption         =   "Product"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   26.25
            Charset         =   204
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   615
         Left            =   2400
         TabIndex        =   7
         Top             =   1440
         Width           =   2220
         WordWrap        =   -1  'True
      End
      Begin VB.Label lblLicenseTo 
         Alignment       =   2  'Center
         Caption         =   "License to"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   204
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   240
         Width           =   6705
      End
      Begin VB.Label lblCompanyProduct 
         AutoSize        =   -1  'True
         Caption         =   "CompanyProduct"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   204
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   2400
         TabIndex        =   6
         Top             =   600
         Width           =   3360
         WordWrap        =   -1  'True
      End
   End
End
Attribute VB_Name = "frmSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_KeyPress(KeyAscii As Integer)
On Error GoTo ErrHnd
   Call StartApp
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the splash form.
' Load the frmMDI form.
Private Sub Form_Load()
On Error GoTo ErrHnd
   lblLicenseTo.Caption = LoadResString(3)
   lblPlatform.Caption = LoadResString(4)
   lblWarning.Caption = LoadResString(2)
   With App
      lblCompanyProduct.Caption = .CompanyName
      lblProductName.Caption = .Title
      lblVersion.Caption = LoadResString(1) & .Major & "." & .Minor
      lblCopyright.Caption = .LegalCopyright
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub fraSplash_Click()
On Error GoTo ErrHnd
   Call StartApp
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the form, unless a key is pressed/the mouse is clicked.
Private Sub tmrTimer_Timer()
On Error GoTo ErrHnd
   Call StartApp
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Start the application by loading the frmMDI form.
' Unload this form.
Private Sub StartApp()
On Error GoTo ErrHnd
   Load frmMDI 'Start.
   Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
