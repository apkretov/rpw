VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 1  'vbDataSource
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsShG"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_ShG As ADODB.Recordset

' The GetDataMember procedure sets the source of the data for the class.
Private Sub Class_GetDataMember(DataMember As String, Data As Object)
On Error GoTo ErrHnd
   Set Data = mrstBrsShG_ShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Populate the mrstBrsSheepGoatV_ShG recordset filtered based on the
'   frmBrsShG form's strIDFarm control array's filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ParamArray vntFilt() As Variant)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strIDSexMl As String
   Dim strIDSexFm As String
   Dim intCrossedPure As Integer
   Dim intCrossedCross As Integer
   Dim lngAgeMin As Long
   Dim lngAgeMax As Long
   With gobSetng
      strIDSexMl = IIf(vntFilt(0) = 1, .IDSexMl, .IDSexFm) 'Define the filtering
      strIDSexFm = IIf(vntFilt(1) = 1, .IDSexFm, .IDSexMl) 'criteria.
      intCrossedPure = IIf(vntFilt(2) = 1, 0, 1)
      intCrossedCross = IIf(vntFilt(3) = 1, 1, 0)
      lngAgeMin = IIf(vntFilt(4) = 1, 0, Int(.YearDays))
      lngAgeMax = IIf(vntFilt(5) = 1, .SQLDaysMax, Int(.YearDays))
   End With
   Set mrstBrsShG_ShG = New ADODB.Recordset 'Populate.
   strCmdTxt = "spSelect_BrsShG_ShG('" & strIDFarm & "', '" & strIDSexMl & "', '" & _
      strIDSexFm & "', " & intCrossedPure & ", " & intCrossedCross & ", " & lngAgeMin & _
      ", " & lngAgeMax & ", " & lngDateDispMin & ", " & lngDateDispMax & ")"
   mrstBrsShG_ShG.Open strCmdTxt, gcnnConnClnt, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sort the mrstBrsShG_ShG record set's field values ascendinly.
Private Sub TblBrs_Sort(ByVal strField As String)
On Error GoTo ErrHnd
    With mrstBrsShG_ShG
        .Fields(strField).Properties("Optimize") = True 'Create an index.
        .Sort = strField 'Sort the recordset.
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
