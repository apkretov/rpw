VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblWt7Mon"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Dim mdtmDate7Mon As Date
Dim mblnFull As Boolean

Public IDLmK As String
Public Wt7Mon As Single

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the Weight7Mon table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "spDelete_Weight7Mon_IDLambKid('" & IDLmK & "')"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
    mblnFull = False 'Mark empty.
Debug.Assert 0 = 1 'Verify uselessness
'   frmBrsShG.RefrshFarm = True 'Mark to refresh frmBrsShG.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new weighing to the Weight7Mon table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    Dim strDate7Mon As String
    ' Convert mdtmDate7Mon to a string.
    strDate7Mon = Util.DateStrDB(mdtmDate7Mon)
    strCmdTxt = "spInsert_Weight7Mon('" & IDLmK & "', '" & strDate7Mon & "', " & Wt7Mon _
      * gobSetng.Decm10 & ")"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
    mblnFull = True 'Mark full.
Debug.Assert 0 = 1 'Verify uselessness
'   frmBrsShG.RefrshFarm = True 'Mark to refresh frmBrsShG.
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

' Select data from the Weight7Mon table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstWt7Mon As ADODB.Recordset
   Dim strCmdTxt As String
   Dim strIDLmK As String
   Set rstWt7Mon = New ADODB.Recordset
   strIDLmK = vntKeys(0)
   strCmdTxt = "spSelect_Weight7Mon_IDLambKid('" & strIDLmK & "')" 'Set the specified
   With rstWt7Mon                                             'animal's Wt7Mon recordset.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .EOF And .BOF Then
         mblnFull = False 'Mark empty.
      Else
         With .Fields 'Define the animal's data from the Wt7Mon recordset.
            IDLmK = .Item("IDLambKid")
            mdtmDate7Mon = .Item("Date7Mon")
            Wt7Mon = .Item("Wt7Mon")
         End With
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the Weight7Mon table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    Dim strDate7Mon As String
    ' Convert mdtmDate7Mon to a string.
    strDate7Mon = Util.DateStrDB(mdtmDate7Mon)
    strCmdTxt = "spUpdate_Weight7Mon_IDLambKid('" & IDLmK & "', '" & strDate7Mon & _
      "', " & Wt7Mon * gobSetng.Decm10 & ")"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Debug.Assert 0 = 1 'Verify uselessness
'   frmBrsShG.RefrshFarm = True 'Mark to refresh frmBrsShG.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Let & get Date7Mon.
Public Property Let Date7Mon(ByVal dtmDate7Mon As Date)
   mdtmDate7Mon = dtmDate7Mon
End Property

Public Property Get Date7Mon() As Date
   Date7Mon = IIf(mdtmDate7Mon = gobSetng.SQLDateZero, 0, mdtmDate7Mon)
End Property

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Clear the tables data.
Private Sub DatTbl_Clear()
On Error GoTo ErrHnd
   IDLmK = ""
   mdtmDate7Mon = 0
   Wt7Mon = 0
   mblnFull = False
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
