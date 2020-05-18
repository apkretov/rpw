VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
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

' Populate the mrstBrsShG_Appr recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ByRef adoCtl As Adodc, ByVal strSortFld As String, ParamArray _
   vntFilt() As Variant)
On Error GoTo ErrHnd
   With adoCtl
      If vntFilt(0) = vbChecked And vntFilt(1) = vbChecked Then 'Ages with & w/o defects.
         .RecordSource = spSelect_BrsShG_ApprAllDefect(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      ElseIf vntFilt(0) = vbChecked And vntFilt(1) = vbUnchecked Then 'Ages only w/o defects.
         .RecordSource = spSelect_BrsShG_ApprNoDefect(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      ElseIf vntFilt(0) = vbUnchecked And vntFilt(1) = vbChecked Then 'Ages only with defects.
         .RecordSource = spSelect_BrsShG_ApprDefect(strIDFarm, lngDateDispMin, _
            lngDateDispMax, strSortFld)
      End If
      .Refresh
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the spSelect_BrsShG_ApprAllDefect SP.
Private Property Get spSelect_BrsShG_ApprAllDefect(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_ApprAllDefect = "SELECT SheepGoat.IDFarm, Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, Appraisal.Density, Appraisal.Strength, WlGrsColour.Colour, Appraisal.Quality, FluffColour.FluffColour, Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail, InhertDefectV.Defect FROM WlGrsColour INNER JOIN (SheepGoat INNER JOIN (FluffColour INNER JOIN (Appraisal LEFT JOIN InhertDefectV ON (Appraisal.IDSheepGoat = InhertDefectV.IDSheepGoat) AND (Appraisal.Age = InhertDefectV.Age)) ON FluffColour.IDFluffColour = Appraisal.IDFluffColour) ON SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat) ON WlGrsColour.IDColour = Appraisal.IDColour " & _
      "WHERE (SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_ApprNoDefect SP.
Private Property Get spSelect_BrsShG_ApprNoDefect(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_ApprNoDefect = "SELECT SheepGoat.IDFarm, Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, Appraisal.Density, Appraisal.Strength, WlGrsColour.Colour, Appraisal.Quality, FluffColour.FluffColour, Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail, InhertDefectV.Defect FROM (WlGrsColour INNER JOIN (SheepGoat INNER JOIN (FluffColour INNER JOIN Appraisal ON FluffColour.IDFluffColour = Appraisal.IDFluffColour) ON SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat) ON WlGrsColour.IDColour = Appraisal.IDColour) LEFT JOIN InhertDefectV ON (Appraisal.Age = InhertDefectV.Age) AND (Appraisal.IDSheepGoat = InhertDefectV.IDSheepGoat) " & _
      "WHERE (SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ")  AND " & _
         "(InhertDefect.IDDefect IS NULL) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the spSelect_BrsShG_ApprDefect SP.
Private Property Get spSelect_BrsShG_ApprDefect(ByVal strIDFarm As String, ByVal _
   lngDateDispMin As Long, ByVal lngDateDispMax As Long, ByVal strSortFld As String) _
   As String
On Error GoTo ErrHnd
   spSelect_BrsShG_ApprDefect = "SELECT SheepGoat.IDFarm, Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, Appraisal.Density, Appraisal.Strength, WlGrsColour.Colour, Appraisal.Quality, FluffColour.FluffColour, Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail, InhertDefectV.Defect FROM (WlGrsColour INNER JOIN (SheepGoat INNER JOIN (FluffColour INNER JOIN Appraisal ON FluffColour.IDFluffColour = Appraisal.IDFluffColour) ON SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat) ON WlGrsColour.IDColour = Appraisal.IDColour) LEFT JOIN InhertDefectV ON (Appraisal.Age = InhertDefectV.Age) AND (Appraisal.IDSheepGoat = InhertDefectV.IDSheepGoat) " & _
      "WHERE (SheepGoat.IDFarm = '" & strIDFarm & "') AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ")  AND " & _
         "(InhertDefect.IDDefect IS NOT NULL) " & _
      "ORDER BY " & strSortFld
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

