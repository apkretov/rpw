VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblWtWean"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Dim mdtmDateWean As Date
Dim mblnFull As Boolean

Public IDLmK As String
Public WtWean As Single

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the WeightWean table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
Debug.Assert 0 = 1 'Verify
    strCmdTxt = "delete from WeightWean where IDLambKid = '" & IDLmK & "'"
'    strCmdTxt = "spDelete_WeightWean_IDLambKid('" & IDLmK & "')"
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
    mblnFull = False 'Mark empty.
Debug.Assert 0 = 1 'Verify uselessness
'   frmBrsShG.RefrshFarm = True 'Mark to refresh frmBrsShG.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new weighing to the WeightWean table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateWean As String
   strDateWean = Util.DateStrDB(mdtmDateWean) 'Convert mdtmDateWean to a string.
   strCmdTxt = "INSERT INTO WeightWean (IDLambKid, DateWean, WtWean) " & _
      "VALUES ('" & IDLmK & "', '" & strDateWean & "', " & Util.NumStrDB(WtWean) & ")"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
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

' Select data from the WeightWean table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstWtWean As ADODB.Recordset
   Dim strCmdTxt As String
   Dim strIDLmK As String
   Set rstWtWean = New ADODB.Recordset
   strIDLmK = vntKeys(0)
   strCmdTxt = "select * from WeightWean where IDLambKid = '" & strIDLmK & "'" 'Set the specified
   With rstWtWean                                             'animal's WtWean recordset.
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF And .BOF Then
         mblnFull = False 'Mark empty.
'         gobMsgInst.NoWtWeanSnd frmMDI.ActiveForm 'Give feedback that there is no weighing.
      Else
         With .Fields 'Define the animal's data from the WeightWean recordset.
            IDLmK = .Item("IDLambKid")
            mdtmDateWean = .Item("DateWean")
            WtWean = .Item("WtWean")
         End With
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the WeightWean table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateWean As String
   strDateWean = Util.DateStrDB(mdtmDateWean)
Debug.Assert 0 = 1 'Verify
   strCmdTxt = "update WeightWean set DateWean = '" & strDateWean & "', WtWean = " & _
      Util.NumStrDB(WtWean) & " where IDLambKid = '" & IDLmK & "'"
'    strCmdTxt = "spUpdate_WeightWean_IDLambKid('" & IDLmK & "', '" & strDateWean & _
     "', " & WtWean * gobSetng.Decm10 & ")"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
    mobSQLErrHnd.Genrl Err.Description
End Sub

' Let & get DateWean.
Public Property Let DateWean(ByVal dtmDateWean As Date)
   mdtmDateWean = dtmDateWean
End Property

Public Property Get DateWean() As Date
   DateWean = IIf(mdtmDateWean = gobSetng.SQLDateZero, 0, mdtmDateWean)
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
   mdtmDateWean = 0
   WtWean = 0
   mblnFull = False
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

