VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblLiv"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mstrIDLivAlive As String
Dim mstrLivAlive As String

' Livability Alive ID for alive offspring.
Public Property Get IDLivAlive() As String
   IDLivAlive = mstrIDLivAlive
End Property

' Livability Alive code name for alive offspring.
Public Property Get LivAlive() As String
   LivAlive = mstrLivAlive
End Property

' Select data from the Liveability table.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Dim rstLiv As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstLiv = New ADODB.Recordset
   strCmdTxt = "spSelect_LiveabilityAlive" 'Set the Liveability recordset.
   rstLiv.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
   With rstLiv.Fields 'Get data from the recordset.
      mstrIDLivAlive = .Item("IDLiv")
      mstrLivAlive = .Item("Liv")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
