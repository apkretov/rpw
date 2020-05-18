VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsWtLmK"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_WtLmK As ADODB.Recordset

' The GetDataMember procedure sets the source of the data for the class.
Private Sub Class_GetDataMember(DataMember As String, Data As Object)
On Error GoTo ErrHnd
    Set Data = mrstBrsShG_WtLmK
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Populate the mrstBrsShG_WtLmK recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ParamArray vntFilt() As Variant)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strSP As String
   If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Both Wean & 7-Mon wt.
      strSP = "spSelect_BrsShG_WtLmKAll"
   ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Wean wt only.
Debug.Assert 0 = 1 'Verify
      strSP = "spSelect_BrsShG_WtLmKWean"
   ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then '7-Mon wt only.
Debug.Assert 0 = 1 'Verify
      strSP = "spSelect_BrsShG_WtLmK7Mon"
   End If
   Set mrstBrsShG_WtLmK = New ADODB.Recordset 'Populate.
   strCmdTxt = strSP & "('" & strIDFarm & "', " & lngDateDispMin & ", " & _
      lngDateDispMax & ")"
   mrstBrsShG_WtLmK.Open strCmdTxt, gcnnConnClnt, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sort the mrstBrsShG_WtLmK record set's field values ascendinly.
Private Sub TblBrs_Sort(ByVal strField As String)
On Error GoTo ErrHnd
    With mrstBrsShG_WtLmK
        .Fields(strField).Properties("Optimize") = True 'Create an index.
        .Sort = strField 'Sort the recordset.
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

