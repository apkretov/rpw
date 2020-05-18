VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblInhertDefct"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Public IDShG As String
Public Age As Integer
Public IDDefctOrig As Long
Public IDDefct As Long
Public Defct As String
Public Added As Boolean
Public Edited As Boolean
Public Deld As Boolean

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the InhertDefect table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM InhertDefect WHERE IDSheepGoat = '" & IDShG & "' AND Age = " _
      & Age & " AND IDDefect = " & IDDefct
'   strCmdTxt = "spDelete_InhertDefect_IDShGAgeIDDefect('" & IDShG & "', " & Age & ", " _
      & IDDefct & ")"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   Call frmMDI.RefrshSetng(False) 'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new sheep/goat to the ShG table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "INSERT INTO InhertDefect (IDSheepGoat, Age, IDDefect) " & _
      "VALUES ('" & IDShG & "', " & Age & ", " & IDDefct & ")"
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   Call frmMDI.RefrshSetng(False) 'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

' Define the TblInhertDefct object's data from InhertDefect.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim strIDShG As String
   Dim intAge As Integer
   Dim lngIDDefct As Long
   Dim rstInhertDefct As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstInhertDefct = New ADODB.Recordset
   strIDShG = vntKeys(0)
   intAge = vntKeys(2)
   lngIDDefct = vntKeys(3)
   strCmdTxt = "SELECT * FROM InhertDefectV WHERE IDSheepGoat = '" & strIDShG & _
      "' AND Age = " & intAge & " AND IDDefect = " & lngIDDefct       'Set the recordset for the specified animal's defect.
   rstInhertDefct.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, _
      adCmdText
   With rstInhertDefct.Fields 'Define the data from the recordset.
      IDShG = .Item("IDSheepGoat")
      Age = .Item("Age")
      IDDefctOrig = .Item("IDDefect")
      IDDefct = .Item("IDDefect")
      Defct = .Item("Defect")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the InhertDefect table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
Debug.Assert 0 = 1 'Verify IDDefct As Long
    strCmdTxt = "UPDATE InhertDefect SET IDDefect = " & IDDefct & _
      " WHERE IDSheepGoat = '" & IDShG & "' AND Age = " & Age & " AND IDDefect = " & _
         IDDefctOrig
'    strCmdTxt = "spUpdate_InhertDefect_IDShGAgeIDDefect('" & IDShG & "', " & Age & _
      ", " & IDDefctOrig & ", " & IDDefct & ")"
 Debug.Assert 0 = 1
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Debug.Assert 0 = 1 'Verify
   Call frmMDI.RefrshSetng(False)   'Refresh settings forms.
Exit Sub
ErrHnd:
    mobSQLErrHnd.Genrl Err.Description
End Sub

' Compose the collection of the InhertDefect table's primary keys.
Public Function GetKeys(ByVal strIDShG As String, ByVal intAge As Integer) As Keys
On Error GoTo ErrHnd
   Dim obKeys As Keys
   Dim rstInhertDefct As ADODB.Recordset
   Dim strCmdTxt As String
   Set obKeys = New Keys
   Set rstInhertDefct = New ADODB.Recordset 'Open the record set with the defects.
   strCmdTxt = "SELECT * FROM InhertDefect WHERE IDSheepGoat = '" & strIDShG & "' AND " _
      & "Age = " & intAge
   With rstInhertDefct
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF = False And .BOF = False Then 'Compose the colleciton.
         Do Until .EOF
            obKeys.Add .Fields("IDSheepGoat"), , .Fields("Age"), .Fields("IDDefect")
            .MoveNext
         Loop
      End If
   End With
   Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

