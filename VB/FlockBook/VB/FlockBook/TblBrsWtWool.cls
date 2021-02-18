VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
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

' Populate the mrstBrsShG_WtWool recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ByRef adoCtl As Adodc, ByVal strSortFld As String, ParamArray _
   vntFilt() As Variant)
On Error GoTo ErrHnd
   With adoCtl
      If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Both wt & grease.
         .RecordSource = spSelect_BrsShG_WtWoolAll(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Wean wt.
         .RecordSource = spSelect_BrsShG_WtWoolWt(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then 'Grease only.
         .RecordSource = spSelect_BrsShG_WtWoolGrease(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      End If
      .Refresh
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the spSelect_BrsShG_WtWoolAll SP.
Private Property Get spSelect_BrsShG_WtWoolAll(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_WtWoolAll = "SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl, WeightWoolAnnl.DateShearAnnl, WeightWoolAnnl.GreaseAnnl FROM WeightWoolAnnl INNER JOIN SheepGoat ON WeightWoolAnnl.IDSheepGoat = SheepGoat.IDSheepGoat " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
          "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
          "(SheepGoat.DateDisp <= " & lngDateDispMax & ") " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_WtWoolWt SP.
Private Property Get spSelect_BrsShG_WtWoolWt(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_WtWoolWt = "SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl, WeightWoolAnnl.DateShearAnnl, WeightWoolAnnl.GreaseAnnl FROM WeightWoolAnnl INNER JOIN SheepGoat ON WeightWoolAnnl.IDSheepGoat = SheepGoat.IDSheepGoat " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") AND " & _
         "(WeightWoolAnnl.DateAnnl IS NOT NULL) AND " & _
         "(WeightWoolAnnl.DateShearAnnl IS NULL) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_WtWoolGrease SP.
Private Property Get spSelect_BrsShG_WtWoolGrease(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_WtWoolGrease = "SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl, WeightWoolAnnl.DateShearAnnl, WeightWoolAnnl.GreaseAnnl FROM WeightWoolAnnl INNER JOIN SheepGoat ON WeightWoolAnnl.IDSheepGoat = SheepGoat.IDSheepGoat " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & " ) AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") AND " & _
         "(WeightWoolAnnl.DateAnnl IS NULL) AND " & _
         "(WeightWoolAnnl.DateShearAnnl IS NOT NULL) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

