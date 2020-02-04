VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SQL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' Create a recordset with oblasts within the specified country based on the corresponding
'   stored procedure.
Public Function Oblasts(ByVal lngIDCountry As Long) As ADODB.Recordset
On Error GoTo ErrHnd
    Dim rstOblasts As ADODB.Recordset
    Dim strCmdTxt As String
    Set rstOblasts = New ADODB.Recordset
    strCmdTxt = "spSelect_BrsShG_Oblasts(" & lngIDCountry & ")"
    rstOblasts.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
            adCmdStoredProc
    Set Oblasts = rstOblasts
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Create a recordset with rayons within the specified oblast based on the corresponding
'   stored procedure.
Public Function Rayons(ByVal lngIDOblast As Long) As ADODB.Recordset
On Error GoTo ErrHnd
    Dim rstRayons As ADODB.Recordset
    Dim strCmdTxt As String
    Set rstRayons = New ADODB.Recordset
    strCmdTxt = "spSelect_BrsShG_Rayons(" & lngIDOblast & ")"
    rstRayons.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
            adCmdStoredProc
    Set Rayons = rstRayons
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Create a recordset with towns/villages within the specified rayon based on the
'   corresponding stored procedure.
Public Function TwnVll(ByVal lngIDRayon As Long) As ADODB.Recordset
On Error GoTo ErrHnd
    Dim rstTwnVll As ADODB.Recordset
    Dim strCmdTxt As String
    Set rstTwnVll = New ADODB.Recordset
    strCmdTxt = "spSelect_BrsShG_TownVill(" & lngIDRayon & ")"
    rstTwnVll.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
            adCmdStoredProc
    Set TwnVll = rstTwnVll
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Create a recordset with farms within the specified town/village based on the
'   corresponding stored procedure.
Public Function Farms(ByVal lngIDTwnVll As Long) As ADODB.Recordset
On Error GoTo ErrHnd
    Dim rstFarms As ADODB.Recordset
    Dim strCmdTxt As String
    Set rstFarms = New ADODB.Recordset
    strCmdTxt = "spSelect_BrsShG_Farms(" & lngIDTwnVll & ")"
    rstFarms.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
            adCmdStoredProc
    Set Farms = rstFarms
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
