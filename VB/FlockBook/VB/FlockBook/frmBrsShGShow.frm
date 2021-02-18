VERSION 5.00
Begin VB.Form frmBrsShGShow 
   BorderStyle     =   4  'Fixed ToolWindow
   Caption         =   "frmBrsShGShow"
   ClientHeight    =   3195
   ClientLeft      =   45
   ClientTop       =   285
   ClientWidth     =   4680
   Icon            =   "frmBrsShGShow.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   ShowInTaskbar   =   0   'False
   Visible         =   0   'False
   WindowState     =   1  'Minimized
   Begin VB.CommandButton cmdShG 
      Height          =   375
      Left            =   1920
      Picture         =   "frmBrsShGShow.frx":1042
      Style           =   1  'Graphical
      TabIndex        =   0
      ToolTipText     =   "Найти номер животного"
      Top             =   1200
      Width           =   375
   End
End
Attribute VB_Name = "frmBrsShGShow"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Open the frmBrsShG form & hide itself.
Private Sub cmdShG_Click()
On Error GoTo ErrHnd
    Me.Hide
    frmBrsShG.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

