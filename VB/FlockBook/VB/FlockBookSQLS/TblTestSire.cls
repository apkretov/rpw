VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblTestSire"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mstrIDSire As String
Dim mdtmDateTestSire As Date
Dim mdtmDateTestSireOrig As Date
Dim mblnFull As Boolean

'Public DateTestSire As Date

Dim mobSQLErrHnd As SQLErrHnd

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the TblTestSire table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "spDelete_TestSire_IDSire('" & mstrIDSire & "')"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
    mblnFull = False 'Mark empty.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new selection indext / complex class to the TblTestSire table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateTestSire As String
   strDateTestSire = Util.DateStrDB(mdtmDateTestSire) 'Convert the date to a string.
   strCmdTxt = "spInsert_TestSire('" & mstrIDSire & "', '" & strDateTestSire & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = True 'Mark full.
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

' Select data from the TblTestSire table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
    Dim rstTblTestSire As ADODB.Recordset
    Dim strCmdTxt As String
    Dim strIDSire As String
    Set rstTblTestSire = New ADODB.Recordset 'Set the specified animal's recordset.
    strIDSire = vntKeys(0)
    strCmdTxt = "spSelect_TestSire_IDSire('" & strIDSire & "')"
    With rstTblTestSire
        .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
        If .EOF = False And .BOF = False Then
            mblnFull = True 'Mark full.
            mstrIDSire = .Fields("IDSire") 'Get the data from the recordset.
            mdtmDateTestSireOrig = .Fields("DateTestSire")
            DateTestSire = .Fields("DateTestSire")
        Else
            mblnFull = False 'Mark empty.
        End If
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the TestSire table, if the date changed.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateTestSire As String
   If mdtmDateTestSire <> mdtmDateTestSireOrig Then 'Compare the date.
      strDateTestSire = Util.DateStrDB(mdtmDateTestSire) 'Convert the date to a string.
      strCmdTxt = "spUpdate_TestSire_IDSire('" & mstrIDSire & "', '" & strDateTestSire _
         & "')"
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Debug.Assert 0 = 1 'Verify uselessness
'      frmBrsShG.RefrshFarm = True 'Mark to refresh frmBrsShG.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Full record mark.
Public Property Get Full() As Boolean
   Full = mblnFull
End Property

' Get IDSire
Public Property Get IDSire() As String
   IDSire = mstrIDSire
End Property

' Initialise the class in a non-standard fashion.
' Execute only once to prevent confusion.
Public Sub ClassInitialize(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   If Not blnPassed Then 'Execute once.
      blnPassed = True
      mstrIDSire = strIDSire
      Call DatTbl_Sel(strIDSire) 'Select.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' DateTestSire
Public Property Let DateTestSire(ByVal dtmDateTestSire As Date)
    mdtmDateTestSire = dtmDateTestSire
End Property

' DateTestSire
Public Property Get DateTestSire() As Date
   DateTestSire = IIf(mdtmDateTestSire = 0, 0, DateValue(mdtmDateTestSire))
End Property

' DateTestSireOrig
Public Property Get DateTestSireOrig() As Date
   DateTestSireOrig = IIf(mdtmDateTestSireOrig = 0, 0, DateValue(mdtmDateTestSireOrig))
End Property

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

