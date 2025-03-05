VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Box"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintDistnc As Integer = 0 'The distance between the boxes.

Private Type BoxTp
   CentrYTop As Single
   CentrYBttm As Single
End Type
Dim mudtBox As BoxTp

Public CentrX As Single 'The horizontal & vertical coordinates of the centre
Public CentrY As Single
Public SideSize As Single

' Get the top CentrY.
Public Property Get CentrYTop() As Single
   CentrYTop = mudtBox.CentrYTop
End Property

' Get the bottom CentrY.
Public Property Get CentrYBttm() As Single
   CentrYBttm = mudtBox.CentrYBttm
End Property

' Change the box's centre's coordinates to move up.
Public Sub MoveUp()
On Error GoTo ErrHnd
   CentrY = CentrY - SideSize - mintDistnc
   If mudtBox.CentrYTop > CentrY Then mudtBox.CentrYTop = CentrY 'Remember the top position.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the box's centre's coordinates to move down.
Public Sub MoveDown()
On Error GoTo ErrHnd
   CentrY = CentrY + SideSize + mintDistnc
   If mudtBox.CentrYBttm < CentrY Then mudtBox.CentrYBttm = CentrY
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the box's centre's coordinates to move right.
Public Sub MoveRight()
On Error GoTo ErrHnd
   CentrX = CentrX + SideSize + mintDistnc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the top CentrY.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Const sngCentrYTopBeg As Single = 1000000 'The beginning top CentrY to assign smaller values.
   mudtBox.CentrYTop = sngCentrYTopBeg
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
