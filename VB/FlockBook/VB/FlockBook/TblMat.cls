VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblMat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Public IDDam As String
Public Cycle As Integer
Public CycleLmK As Integer
Public DateMat As Date
Public IDSire As String

Private Type TblMatTp
   IDDam As String
   Cycle As Integer
   CycleLmK As Integer
   DateMat As Date
   IDSire As String
End Type
Dim mudtTblMatTpOrig As TblMatTp

' Get original IDSire.
Public Property Get IDSireOrig() As String
   IDSireOrig = mudtTblMatTpOrig.IDSire
End Property

' Get original IDSire.
Public Property Get DateMatOrig() As Date
Debug.Assert 0 = 1 'Verify DateMat w/o From
   DateMatOrig = mudtTblMatTpOrig.DateMat
End Property

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the Mate table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "delete from Mate where IDDam = '" & IDDam & "' and Cycle = " & Cycle
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

' Add a new mating to the Mate table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateMat As String
   strDateMat = Util.DateStrDB(DateMat)
   strCmdTxt = "INSERT INTO Mate(IDDam, Cycle, CycleLambKid, DateMatFrom, IDSire) " & _
      "VALUES ('" & IDDam & "', " & Cycle & ", " & CycleLmK & ", '" & strDateMat & _
      "', '" & IDSire & "')"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

' Save the original data after selecting.
Private Sub DatTbl_OrigSave()
On Error GoTo ErrHnd
   With mudtTblMatTpOrig
      .IDDam = IDDam
      .Cycle = Cycle
      .CycleLmK = CycleLmK
      .DateMat = DateMat
      .IDSire = IDSire
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Define the TblShG object's data from the Mate table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
    Dim rstMat As ADODB.Recordset
    Dim strCmdTxt As String
    Dim strIDDam As String
    Dim intCycle As Integer
    Set rstMat = New ADODB.Recordset
    strIDDam = vntKeys(0)
    intCycle = vntKeys(2)
    strCmdTxt = "select * from Mate where IDDam = '" & strIDDam & "' and Cycle = " & intCycle
    rstMat.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
    With rstMat.Fields 'Define the animal's data from the Mate recordset.
        IDDam = .Item("IDDam")
        Cycle = .Item("Cycle")
        CycleLmK = .Item("CycleLambKid")
        DateMat = .Item("DateMatFrom")
        IDSire = .Item("IDSire")
    End With
    Call DatTbl_OrigSave 'Save original data.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Update the form's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    Dim strDateMat As String
    ' Convert dates to strings.
    strDateMat = Util.DateStrDB(DateMat)
    strCmdTxt = "UPDATE Mate SET IDDam = '" & IDDam & "', Cycle = " & Cycle & _
      ", CycleLambKid = " & CycleLmK & ", DateMatFrom = '" & strDateMat & _
      "', IDSire = '" & IDSire & "' WHERE IDDam = '" & IDDam & "' AND Cycle = " & Cycle
'    strCmdTxt = "spUpdate_Mate_IDDamCycle('" & IDDam & "', " & Cycle & ", " & _
        CycleLmK & ", '" & strDateMat & "', '" & IDSire & "')"
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Compose the collection of the Mate table's primary keys.
Public Function GetKeys(ByVal strIDDam As String) As Keys
On Error GoTo ErrHnd
   Dim obKeys As Keys
   Dim rstMat As ADODB.Recordset
   Dim strCmdTxt As String
   Set obKeys = New Keys
   Set rstMat = New ADODB.Recordset 'Open the record set with the dam's matings.
   strCmdTxt = "SELECT * FROM Mate WHERE IDDam = '" & strIDDam & "'"
   rstMat.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic
   With rstMat 'Compose the colleciton.
      If .EOF = False And .BOF = False Then
         Do Until .EOF
            obKeys.Add .Fields.Item("IDDam"), , .Fields.Item("Cycle")
            .MoveNext
         Loop
      End If
   End With
   Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

