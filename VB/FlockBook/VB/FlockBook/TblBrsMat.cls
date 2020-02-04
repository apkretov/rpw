VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsMat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_Mat As ADODB.Recordset

' Populate the mrstBrsShG_Mat recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ByRef adoCtl As Adodc, ByVal strSortFld As String, ParamArray _
   vntFilt() As Variant)
On Error GoTo ErrHnd
   With adoCtl
      If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Matings with & w/o lambings/kiddings.
         .RecordSource = spSelect_BrsShG_MateAllLmK(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Matings only w/o lambings/kiddings.
         .RecordSource = spSelect_BrsShG_MateNoLmK(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then 'Matings only with lambings/kiddings.
         .RecordSource = spSelect_BrsShG_MateLmK(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      End If
      .Refresh
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the spSelect_BrsShG_MateAllLmK SP.
Private Property Get spSelect_BrsShG_MateAllLmK(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_MateAllLmK = "SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.IDSire, Mate.DateMatFrom, LambKid.DateLambKid FROM SheepGoat INNER JOIN (Mate LEFT JOIN LambKid ON (Mate.Cycle = LambKid.Cycle) AND (Mate.IDDam = LambKid.IDDam)) ON SheepGoat.IDSheepGoat = Mate.IDDam " & _
      "WHERE ((SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ")) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_MateNoLmK SP.
Private Property Get spSelect_BrsShG_MateNoLmK(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_MateNoLmK = "SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.IDSire, Mate.DateMatFrom, LambKid.DateLambKid FROM SheepGoat INNER JOIN (Mate LEFT JOIN LambKid ON (Mate.Cycle = LambKid.Cycle) AND (Mate.IDDam = LambKid.IDDam)) ON SheepGoat.IDSheepGoat = Mate.IDDam " & _
      "WHERE (SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
          "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
          "(SheepGoat.DateDisp <= " & lngDateDispMax & ") AND " & _
          "(LambKid.IDDam IS NULL) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_MateLmK SP.
Private Property Get spSelect_BrsShG_MateLmK(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_MateLmK = "SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.IDSire, Mate.DateMatFrom, LambKid.DateLambKid FROM SheepGoat INNER JOIN (Mate LEFT JOIN LambKid ON (Mate.Cycle = LambKid.Cycle) AND (Mate.IDDam = LambKid.IDDam)) ON SheepGoat.IDSheepGoat = Mate.IDDam " & _
      "WHERE (SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") AND " & _
         "(LambKid.IDDam IS NOT NULL) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

