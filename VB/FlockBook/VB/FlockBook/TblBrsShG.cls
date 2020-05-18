VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsShG"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

' Populate the mrstBrsSheepGoatV_ShG recordset filtered based on the
'   frmBrsShG form's strIDFarm control array's filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ByRef adoCtl As Adodc, ByVal strSortFld As String, ParamArray _
   vntFilt() As Variant)
On Error GoTo ErrHnd
   Dim strIDSexMl As String
   Dim strIDSexFm As String
   Dim intCrossedPure As Integer
   Dim intCrossedCross As Integer
   Dim lngAgeMin As Long
   Dim lngAgeMax As Long
   With gobSetng
      strIDSexMl = IIf(vntFilt(0) = vbChecked, .IDSexMl, .IDSexFm) 'Define the filtering
      strIDSexFm = IIf(vntFilt(1) = vbChecked, .IDSexFm, .IDSexMl) 'criteria.
      intCrossedPure = IIf(vntFilt(2) = vbChecked, vbUnchecked, gobSetng.Checked)
      intCrossedCross = IIf(vntFilt(3) = vbChecked, gobSetng.Checked, vbUnchecked)
      lngAgeMin = IIf(vntFilt(4) = vbChecked, 0, Int(.YearDays))
      lngAgeMax = IIf(vntFilt(5) = vbChecked, .SQLDaysMax, Int(.YearDays))
   End With
   adoCtl.RecordSource = "SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat, Sex.Sex, " & _
      "SheepGoat.BreedCross, SheepGoat.DateBirth, SheepGoat.IDSire, SheepGoat.IDDam, " & _
         "SheepGoat.TypeBirth, SheepGoat.IDFarmBirth, BrsShG_ShG_Disp.DateDisp, " _
         & "Disposition.DispReas, CopmClass.CompClass, TestSire.DateTestSire, " & _
         "SheepGoat.Remark " & _
      "FROM Disposition INNER JOIN ((((SheepGoat INNER JOIN Sex ON SheepGoat.IDSex = " _
         & "Sex.IDSex) LEFT JOIN BrsShG_ShG_Disp ON SheepGoat.IDSheepGoat = " & _
         "BrsShG_ShG_Disp.IDSheepGoat) LEFT JOIN TestSire ON SheepGoat.IDSheepGoat = " _
         & "TestSire.IDSire) LEFT JOIN SelIndxCompClassV ON SheepGoat.IDSheepGoat = " & _
         "SelIndxCompClassV.IDSheepGoat) ON Disposition.IDDispReas = " & _
         "SheepGoat.IDDispReas " & _
      "WHERE ((SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "((SheepGoat.IDSex = """ & strIDSexMl & """) OR " & _
         "(SheepGoat.IDSex = """ & strIDSexFm & """)) AND " & _
         "((SheepGoat.Crossed = " & intCrossedPure & ") OR " & _
         "(SheepGoat.Crossed = " & intCrossedCross & ")) AND" _
         & "(Date() - SheepGoat.DateBirth >= " & lngAgeMin & ") AND " & _
         "(Date() - SheepGoat.DateBirth < " & lngAgeMax & ") AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ")) " & _
      "ORDER BY " & strSortFld
   adoCtl.Refresh
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
