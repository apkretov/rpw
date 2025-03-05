VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBusy"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

'Dim mblnFull As Boolean

Public Busy As Boolean 'Mark the server busy.

' Delete all records, if accidentially more than 1, from the Busy table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   gcnnConn.Execute "DELETE FROM Busy", , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' The Busy table's full mark.
Private Property Get DatTbl_Full() As Boolean
'Debug.Assert 0 = 1 'Verify
'   DatTbl_Full = mblnFull
End Property

' Insert the Busy mark into the Busy table. The procedure is needed to re-initialise the
'  table, if it accedentially got emtpy.
Private Sub DatTbl_Ins()
   Dim strCmdTxt As String
   strCmdTxt = "INSERT INTO Busy (Busy) VALUES (" & IIf(Busy, gobSetng.Checked, vbUnchecked) & ")"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

' Get the server's busy mark from the Busy table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstBusy As ADODB.Recordset
   Set rstBusy = New ADODB.Recordset
   With rstBusy
      .Open "Busy", gcnnConn, adOpenDynamic, adLockOptimistic, adCmdTable
      If .BOF = False And .EOF = False Then 'Any records?
         Busy = .Fields("Busy")
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Mark the server busy/not busy.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "UPDATE Busy SET Busy = " & IIf(Busy, gobSetng.Checked, vbUnchecked)
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub
