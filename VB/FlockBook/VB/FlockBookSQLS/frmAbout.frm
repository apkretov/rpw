VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   3  'Fixed Dialog
   ClientHeight    =   3690
   ClientLeft      =   2340
   ClientTop       =   1935
   ClientWidth     =   5730
   ClipControls    =   0   'False
   Icon            =   "frmAbout.frx":0000
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3690
   ScaleWidth      =   5730
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox picIcon 
      AutoSize        =   -1  'True
      ClipControls    =   0   'False
      Height          =   540
      Left            =   240
      Picture         =   "frmAbout.frx":1042
      ScaleHeight     =   480
      ScaleMode       =   0  'User
      ScaleWidth      =   480
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   240
      Width           =   540
   End
   Begin VB.CommandButton cmdOK 
      Cancel          =   -1  'True
      Caption         =   "&Œ "
      Default         =   -1  'True
      Height          =   375
      Left            =   4365
      TabIndex        =   6
      Top             =   3120
      Width           =   1215
   End
   Begin VB.Label lblCompany 
      Caption         =   "Company"
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
      Left            =   960
      TabIndex        =   3
      Top             =   960
      Width           =   3105
   End
   Begin VB.Line linButton 
      BorderColor     =   &H00808080&
      BorderStyle     =   6  'Inside Solid
      Index           =   1
      X1              =   90
      X2              =   5654
      Y1              =   2445
      Y2              =   2445
   End
   Begin VB.Label lblDescription 
      Caption         =   "App Description"
      ForeColor       =   &H00000000&
      Height          =   810
      Left            =   960
      TabIndex        =   4
      Top             =   1440
      Width           =   4485
   End
   Begin VB.Label lblTitle 
      Caption         =   "Application Title"
      ForeColor       =   &H00000000&
      Height          =   240
      Left            =   930
      TabIndex        =   1
      Top             =   240
      Width           =   3885
   End
   Begin VB.Line linButton 
      BorderColor     =   &H00FFFFFF&
      BorderWidth     =   2
      Index           =   0
      X1              =   105
      X2              =   5654
      Y1              =   2460
      Y2              =   2460
   End
   Begin VB.Label lblVersion 
      Caption         =   "Version"
      Height          =   225
      Left            =   930
      TabIndex        =   2
      Top             =   600
      Width           =   3885
   End
   Begin VB.Label lblDisclaimer 
      Caption         =   "Warning..."
      ForeColor       =   &H00000000&
      Height          =   825
      Left            =   240
      TabIndex        =   5
      Top             =   2760
      Width           =   3990
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdOk_Click()
  Unload Me
End Sub

' Show information about the FlockBook.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Me.Caption = frmMDI.mnuHelpAbout.Caption
   With App
      lblTitle.Caption = .Title
      lblVersion.Caption = LoadResString(1) & .Major & "." & .Minor '& "." & .Revision
      lblCompany.Caption = .CompanyName
      lblDescription.Caption = .FileDescription
   End With
   lblDisclaimer.Caption = LoadResString(3) & ". " & LoadResString(2) & "."
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
