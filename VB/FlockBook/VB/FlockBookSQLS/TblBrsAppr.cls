VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsAppr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_Appr As ADODB.Recordset

' The GetDataMember procedure sets the source of the data for the class.
Private Sub Class_GetDataMember(DataMember As String, Data As Object)
On Error GoTo ErrHnd
    Set Data = mrstBrsShG_Appr
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Populate the mrstBrsShG_Appr recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ParamArray vntFilt() As Variant)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strSP As String
   If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Ages with & w/o defects.
      strSP = "spSelect_BrsShG_ApprAllDefect"
   ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Ages only w/o defects.
Debug.Assert 0 = 1 'Verify
      strSP = "spSelect_BrsShG_ApprNoDefect"
   ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then 'Ages only with defects.
Debug.Assert 0 = 1 'Verify
      strSP = "spSelect_BrsShG_ApprDefect"
   End If
   Set mrstBrsShG_Appr = New ADODB.Recordset 'Populate.
   strCmdTxt = strSP & "('" & strIDFarm & "', " & lngDateDispMin & ", " & _
      lngDateDispMax & ")"
   mrstBrsShG_Appr.Open strCmdTxt, gcnnConnClnt, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sort the mrstBrsShG_Appr record set's field values ascendinly.
Private Sub TblBrs_Sort(ByVal strField As String)
On Error GoTo ErrHnd
    With mrstBrsShG_Appr
        .Fields(strField).Properties("Optimize") = True 'Create an index.
        .Sort = strField 'Sort the recordset.
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

