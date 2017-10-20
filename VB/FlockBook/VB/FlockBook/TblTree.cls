VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblTree"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblTreeTp
   IDClnt As String
   Refrsh As Boolean
End Type
Dim mudtTblTree As TblTreeTp
Dim mudtTblTreeOrig As TblTreeTp

Dim mblnFull As Boolean

'Public IDClnt As String
'Public Refrsh As Boolean 'Mark to refresh the frmBrsShG.treFarms control.

' Get & let IDClnt this application/workstation's client ID.
Public Property Get IDClnt() As String
   IDClnt = mudtTblTree.IDClnt
End Property

Public Property Let IDClnt(ByVal strIDClnt As String)
   mudtTblTree.IDClnt = strIDClnt
End Property

' Get & let the mark to refresh the frmBrsShG.treFarms control.
Public Property Get Refrsh() As Boolean
   Refrsh = mudtTblTree.Refrsh
End Property

Public Property Let Refrsh(ByVal blnRefrsh As Boolean)
   mudtTblTree.Refrsh = blnRefrsh
End Property

' Delete the records.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM Tree WHERE IDClnt = '" & mudtTblTree.IDClnt & "'"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Insert a new record.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblTree
      strCmdTxt = "INSERT INTO Tree (IDClnt, Refrsh) " & _
         "VALUES ('" & .IDClnt & "', " & IIf(.Refrsh, gobSetng.Checked, vbUnchecked) & ")"
   End With
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark full.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

' Save the original data.
Private Sub DatTbl_OrigSave()
On Error GoTo ErrHnd
   With mudtTblTreeOrig
      .IDClnt = mudtTblTree.IDClnt
      .Refrsh = mudtTblTree.Refrsh
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select a reocrd.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstTree As ADODB.Recordset
   Dim strCmdTxt As String
   Dim strIDClnt As String
   Set rstTree = New ADODB.Recordset
   strIDClnt = vntKeys(0)
   strCmdTxt = "SELECT * FROM Tree WHERE IDClnt = '" & strIDClnt & "'"
   With rstTree
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .BOF = False And .EOF = False Then 'Any records?
         mudtTblTree.IDClnt = .Fields("IDClnt")
         mudtTblTree.Refrsh = .Fields("Refrsh")
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Update the record.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "UPDATE Tree SET Refrsh = " & IIf(mudtTblTree.Refrsh, gobSetng.Checked, _
      vbUnchecked) & " WHERE IDClnt = '" & mudtTblTree.IDClnt & "'"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear the table's data.
Private Sub DatTbl_Clear()
On Error GoTo ErrHnd
   mudtTblTree.IDClnt = ""
   mudtTblTree.Refrsh = False
   mblnFull = False 'Mark empty.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update all clients' marks to make them refresh their trees.
Public Sub RefrshAll()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "UPDATE Tree SET Refrsh = " & gobSetng.Checked
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Generate a new unique client ID.
Public Function IDClntNew() As String
On Error GoTo ErrHnd
   Dim strIDClnt As String
   Dim blnFullOrig As Boolean
   Call DatTbl_OrigSave 'Save the original data to restore later.
   blnFullOrig = mblnFull
   Do
      Call DatTbl_Clear 'Clear before re-populating.
      strIDClnt = CStr(CLng(Rnd * 1000000000#)) 'New random 9-digit ID.
      Call DatTbl_Sel(strIDClnt) 'Populate with a new ID.
   Loop While mblnFull 'Loop, if full i.e. not unique.
   With mudtTblTreeOrig 'Restore the original data.
      mudtTblTree.IDClnt = .IDClnt
      mudtTblTree.Refrsh = .Refrsh
   End With
   mblnFull = blnFullOrig
   IDClntNew = strIDClnt
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

