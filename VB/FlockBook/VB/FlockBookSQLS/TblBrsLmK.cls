VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsLmK"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_LmK As ADODB.Recordset

' The GetDataMember procedure sets the source of the data for the class.
Private Sub Class_GetDataMember(DataMember As String, Data As Object)
On Error GoTo ErrHnd
    Set Data = mrstBrsShG_LmK
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Populate the mrstBrsShG_LmK recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ParamArray vntFilt() As Variant)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strAbortNo As String
   Dim strAbortYes As String
   Dim strIDSexOffspMl As String
   Dim strIDSexOffspFm As String
   Dim strIDLivAliv As String
   Dim strIDLivDead As String
   With gobSetng 'Define the filtering criteria.
      strAbortNo = CStr(IIf(vntFilt(0) = vbChecked, vbUnchecked, vbChecked)) 'Not aborted, i.e. lambed
      strAbortYes = CStr(IIf(vntFilt(1) = vbChecked, vbChecked, vbUnchecked)) 'Aaborted.
      strIDSexOffspMl = CStr(IIf(vntFilt(4) = vbChecked, .IDSexMl, .IDSexFm)) 'Male offsp.
      strIDSexOffspFm = CStr(IIf(vntFilt(5) = vbChecked, .IDSexFm, .IDSexMl)) 'Female offsp.
      strIDLivAliv = CStr(IIf(vntFilt(6) = vbChecked, vbUnchecked, vbChecked)) 'Alive offsprings.
      strIDLivDead = CStr(IIf(vntFilt(7) = vbChecked, vbChecked, vbUnchecked)) 'Dead offsprings.
   End With
   Set mrstBrsShG_LmK = New ADODB.Recordset 'Populate.
   strCmdTxt = "spSelect_BrsShG_LmK('" & strIDFarm & "', '" & strAbortNo & "', '" & _
      strAbortYes & "', " & lngDateDispMin & ", " & lngDateDispMax & ", '" & _
      strIDSexOffspMl & "', '" & strIDSexOffspFm & "', '" & strIDLivAliv & "', '" & _
      strIDLivDead & "')"
   mrstBrsShG_LmK.Open strCmdTxt, gcnnConnClnt, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sort the mrstBrsShG_LmK record set's field values ascendinly.
Private Sub TblBrs_Sort(ByVal strField As String)
On Error GoTo ErrHnd
    With mrstBrsShG_LmK
        .Fields(strField).Properties("Optimize") = True 'Create an index.
        .Sort = strField 'Sort the recordset.
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

