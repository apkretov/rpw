VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsWtLmK"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

' Populate the mrstBrsShG_WtLmK recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ByRef adoCtl As Adodc, ByVal strSortFld As String, ParamArray _
   vntFilt() As Variant)
On Error GoTo ErrHnd
   With adoCtl
      If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Both Wean & 7-Mon wt.
         .RecordSource = spSelect_BrsShG_WtLmKAll(strIDFarm, lngDateDispMin, lngDateDispMax, _
            strSortFld)
      ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Wean wt only.
         .RecordSource = spSelect_BrsShG_WtLmKWean(strIDFarm, lngDateDispMin, lngDateDispMax, _
            strSortFld)
      ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then '7-Mon wt only.
         .RecordSource = spSelect_BrsShG_WtLmK7Mon(strIDFarm, lngDateDispMin, lngDateDispMax, _
            strSortFld)
      End If
      .Refresh
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the spSelect_BrsShG_WtLmKAll SP.
Private Property Get spSelect_BrsShG_WtLmKAll(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_WtLmKAll = "SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat AS IDLambKid, WeightWean.DateWean, WeightWean.WtWean, Weight7Mon.Date7Mon, Weight7Mon.Wt7Mon FROM (SheepGoat LEFT JOIN Weight7Mon ON SheepGoat.IDSheepGoat = Weight7Mon.IDLambKid) LEFT JOIN WeightWean ON SheepGoat.IDSheepGoat = WeightWean.IDLambKid " & _
      "WHERE ( (WeightWean.IDLambKid IS NOT NULL) OR " & _
         "(Weight7Mon.IDLambKid IS NOT NULL) ) AND " & _
         "(SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_WtLmKWean SP.
Private Property Get spSelect_BrsShG_WtLmKWean(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_WtLmKWean = "SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat AS IDLambKid, WeightWean.DateWean, WeightWean.WtWean, Weight7Mon.Date7Mon, Weight7Mon.Wt7Mon FROM (SheepGoat LEFT JOIN Weight7Mon ON SheepGoat.IDSheepGoat = Weight7Mon.IDLambKid) LEFT JOIN WeightWean ON SheepGoat.IDSheepGoat = WeightWean.IDLambKid " & _
      "WHERE (WeightWean.IDLambKid IS NOT NULL) AND " & _
         "(Weight7Mon.IDLambKid IS NULL) AND " & _
         "(SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_WtLmK7Mon SP.
Private Property Get spSelect_BrsShG_WtLmK7Mon(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_WtLmK7Mon = "SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat AS IDLambKid, WeightWean.DateWean, WeightWean.WtWean, Weight7Mon.Date7Mon, Weight7Mon.Wt7Mon FROM (SheepGoat LEFT JOIN Weight7Mon ON SheepGoat.IDSheepGoat = Weight7Mon.IDLambKid) LEFT JOIN WeightWean ON SheepGoat.IDSheepGoat = WeightWean.IDLambKid " & _
         "WHERE (WeightWean.IDLambKid IS NULL) AND " & _
         "(Weight7Mon.IDLambKid IS NOT NULL) AND " & _
         "(SheepGoat.IDFarm =  '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

