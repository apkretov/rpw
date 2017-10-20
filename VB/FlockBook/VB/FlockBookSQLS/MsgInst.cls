VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MsgInst"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' Messages' ID's.
Const mintShGDispd As Integer = 1
Const mintLmKed As Integer = 2
Const mintSQLErr As Integer = 3
'Const mintCancSel As Integer = 4

'Const mintNoContrParam As Integer = 5
Const mintNoMating As Integer = 6
Const mintNoLmKng As Integer = 7
Const mintNoWtWool As Integer = 8
Const mintNoAppr As Integer = 9

Public DuplFrm As Boolean 'Duplicate Form message; belongs to no message recipient form.

' Send the Sheep/Goat Disposed message to the specified message recipient form.
Public Sub ShGDispdSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintShGDispd, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the Sheep/Goat Disposed message from the specified message recipient form.
Public Property Get ShGDispd(frmRecip As Form) As Boolean
   ShGDispd = Receive(mintShGDispd, frmRecip)
End Property

' Send the Dam Lambe/Kidded message to the specified message recipient form.
Public Sub LmKedSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintLmKed, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the Dam Lambe/Kidded message from the specified message recipient form.
Public Property Get LmKed(frmRecip As Form) As Boolean
   LmKed = Receive(mintLmKed, frmRecip)
End Property

' Send the SQL Error message to the specified message recipient form.
Public Sub SQLErrSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintSQLErr, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the SQL Error message from the specified message recipient form.
Public Property Get SQLErr(frmRecip As Form) As Boolean
   SQLErr = Receive(mintSQLErr, frmRecip)
End Property

' Receive the No Control Parameters message from the specified message recipient form.
Private Property Get NoContrParam(frmRecip As Form) As Boolean
'   NoContrParam = Receive(mintNoContrParam, frmRecip)
End Property

' Send the No Mating message to the specified message recipient form.
Public Sub NoMatingSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintNoMating, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the No Mating message from the specified message recipient form.
Public Property Get NoMating(frmRecip As Form) As Boolean
   NoMating = Receive(mintNoMating, frmRecip)
End Property

' Send the No Lambing/Kidding message to the specified message recipient form.
Public Sub NoLmKngSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintNoLmKng, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the No Lambing/Kidding message from the specified message recipient form.
Public Property Get NoLmKng(frmRecip As Form) As Boolean
   NoLmKng = Receive(mintNoLmKng, frmRecip)
End Property

' Send the No Annual Weight/Wool message to the specified message recipient form.
Public Sub NoWtWoolSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintNoWtWool, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the No Annual Weight/Wool message from the specified message recipient form.
Public Property Get NoWtWool(frmRecip As Form) As Boolean
   NoWtWool = Receive(mintNoWtWool, frmRecip)
End Property

' Send the No Appraisal message to the specified message recipient form.
Public Sub NoApprSnd(frmRecip As Form)
On Error GoTo ErrHnd
   Call Snd(mintNoAppr, frmRecip)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Receive the No Appraisal message from the specified message recipient form.
Public Property Get NoAppr(frmRecip As Form) As Boolean
   NoAppr = Receive(mintNoAppr, frmRecip)
End Property

' Send a message to a frmRecip recipient form.
' Prevent sending a duplicate message.
Private Sub Snd(ByVal intMsg As Integer, frmRecip As Form)
On Error GoTo ErrHnd
   Dim obMsgRecip As MsgRecip
   Dim vntMsg As Variant
   Dim blnExit As Boolean
   Set obMsgRecip = frmRecip 'Get the form's message collection.
   With obMsgRecip
      For Each vntMsg In .Msgs 'Prevent duplicates.
         If intMsg = vntMsg Then
            blnExit = True
            Exit For
         End If
      Next
      If Not blnExit Then .Msgs.Add intMsg, CStr(intMsg) 'Add a message.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return True if there is the specified message in the specified recipient form's messages
'  collection.
Private Function Receive(ByVal intMsg As Integer, frmRecip As Form) As Boolean
On Error GoTo ErrHnd
   Dim obMsgRecip As MsgRecip
   Dim vntMsg As Variant
   Set obMsgRecip = frmRecip 'Get the form's message collection.
   With obMsgRecip
      For Each vntMsg In .Msgs 'Loop through the collection.
         If intMsg = vntMsg Then
            Receive = True 'Message found.
            Exit Function
         End If
      Next
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Reset a recipient form's messages collection.
Public Sub Rest(frmRecip As Form)
On Error GoTo ErrHnd
   Dim obMsgRecip As MsgRecip
   Dim vntMsg As Variant
   Dim strIdx As String
   DuplFrm = False 'Reset the Duplicate Form mark.
   Set obMsgRecip = frmRecip 'Get the form's message collection.
   With obMsgRecip
      For Each vntMsg In .Msgs 'Loop through the collection.
         strIdx = CStr(vntMsg) 'Remember the index to remove.
         .Msgs.Remove strIdx
      Next
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
