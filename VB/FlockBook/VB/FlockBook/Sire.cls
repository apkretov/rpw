VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Sire"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public IDSire As String

' Count the sire's matings in the Mate table:
'  No Matings = No of IDSire's encountered.
Public Function CountMat() As Long
On Error GoTo ErrHnd
   Dim rstMat As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstMat = New ADODB.Recordset
   strCmdTxt = "SELECT COUNT(IDSire) AS CountIDSire FROM Mate GROUP BY IDSire HAVING " _
      & "(IDSire = '" & IDSire & "')"
   With rstMat
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .BOF = False And .EOF = False Then CountMat = .Fields("CountIDSire")
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the sire's 1st mating's date.
Public Function DatMatFirst() As Date
On Error GoTo ErrHnd
   Dim rstMat As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstMat = New ADODB.Recordset
   strCmdTxt = "SELECT IDSire, MIN(DateMatFrom) AS MinDateMatFrom FROM Mate GROUP BY " _
      & "IDSire HAVING (IDSire = '" & IDSire & "')"
   With rstMat
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .BOF = False And .EOF = False Then DatMatFirst = .Fields("MinDateMatFrom")
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the sire's last mating's date.
Public Function DatMatLast() As Date
On Error GoTo ErrHnd
   Dim rstMat As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstMat = New ADODB.Recordset
   strCmdTxt = "SELECT IDSire, MAX(DateMatFrom) AS MaxDateMatFrom FROM Mate GROUP BY " _
      & "IDSire HAVING (IDSire = '" & IDSire & "')"
   With rstMat
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .BOF = False And .EOF = False Then DatMatLast = .Fields("MaxDateMatFrom")
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

