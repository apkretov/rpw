VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblSex"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mstrSexMl As String
Dim mstrSexFm As String

' Get an offspring sex name by the specified sex ID.
Public Function Sex(ByVal strIDSex As String) As String
On Error GoTo ErrHnd
   With gobSetng
      Select Case strIDSex
      Case .IDSexMl 'Male.
         Sex = mstrSexMl
      Case .IDSexFm 'Female.
         Sex = mstrSexFm
      End Select
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

'' Male offspring sex name.
'Public Property Get SexMl() As String
'   SexMl = mstrSexMl
'End Property
'
'' Female offspring sex name.
'Public Property Get SexFm() As String
'   SexFm = mstrSexFm
'End Property

' Get the TblSex object's data from the Offspring table.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Dim rstSexOffsp As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstSexOffsp = New ADODB.Recordset
   With rstSexOffsp
      strCmdTxt = "spSelect_SexOffspring_IDSex('" & gobSetng.IDSexMl & "')" 'Male sex.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      mstrSexMl = .Fields("Sex")
      .Close
      strCmdTxt = "spSelect_SexOffspring_IDSex('" & gobSetng.IDSexFm & "')" 'Female sex.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      mstrSexFm = .Fields("Sex")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
