VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsWtWool"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_WtWool As ADODB.Recordset

' The GetDataMember procedure sets the source of the data for the class.
Private Sub Class_GetDataMember(DataMember As String, Data As Object)
On Error GoTo ErrHnd
    Set Data = mrstBrsShG_WtWool
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Populate the mrstBrsShG_WtWool recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ParamArray vntFilt() As Variant)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strSP As String
   If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Both wt & grease.
      strSP = "spSelect_BrsShG_WtWoolAll"
   ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Wean wt.
      strSP = "spSelect_BrsShG_WtWoolWt"
   ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then 'Grease only.
      strSP = "spSelect_BrsShG_WtWoolGrease"
   End If
   Set mrstBrsShG_WtWool = New ADODB.Recordset 'Populate.
   strCmdTxt = strSP & "('" & strIDFarm & "', " & lngDateDispMin & ", " & _
      lngDateDispMax & ")"
   mrstBrsShG_WtWool.Open strCmdTxt, gcnnConnClnt, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sort the mrstBrsShG_WtWool record set's field values ascendinly.
Private Sub TblBrs_Sort(ByVal strField As String)
On Error GoTo ErrHnd
    With mrstBrsShG_WtWool
        .Fields(strField).Properties("Optimize") = True 'Create an index.
        .Sort = strField 'Sort the recordset.
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub



