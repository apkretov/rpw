VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SumPerform"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTblSel

' Query the data.
' Return True, if succeeds.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim strIDFarm As String
   Dim strDate As String
   Dim dtmDate As Date
   Call DropTable 'Drop tables.
   strIDFarm = vntKeys(0)
   strDate = Util.DateStrRpt(vntKeys(1))
   dtmDate = vntKeys(1)
   DatTblSel_Sel = spExec_SumPerform(strIDFarm, strDate, dtmDate)
Exit Function
ErrHnd:
   MsgBox Err.Description
   DatTblSel_Sel = False 'Failed.
End Function

' Drop the creatable tables.
Private Sub DropTable()
On Error Resume Next
   With gdbDB
      .Execute "DROP TABLE SumPerform_Farms"
      .Execute "DROP TABLE SumPerform_SheepGoat"
      .Execute "DROP TABLE SumPerform_WeightWean"
      .Execute "DROP TABLE SumPerform_Weight7Mon"
      .Execute "DROP TABLE SumPerform_WeightWoolAnnl"
      .Execute "DROP TABLE SumPerform_Appraisal"
      .Execute "DROP TABLE SumPerform_MaxAge"
   End With
End Sub

' Execute the spExec_SumPerform SP.
' Return True, if succeeds.
Private Function spExec_SumPerform(ByVal strIDFarm As String, ByVal strDate As String, _
   ByVal dtmDate As Date) As Boolean
On Error GoTo ErrHnd
   Call spSelectInto_SumPerform_Farms(strIDFarm)
   Call spSelectInto_SumPerform_SheepGoat(strIDFarm, strDate)
   Call spAlter_SumPerform_SheepGoat
   Call spUpdate_SumPerform_SheepGoat(strDate)
   Call spSelectInto_SumPerform_WeightWean(strDate)
   Call spSelectInto_SumPerform_Weight7Mon(strDate)
   Call spSelectInto_SumPerform_WeightWoolAnnl(strDate)
   Call spSelectInto_SumPerform_Appraisal(strDate)
   Call spSelectInto_SumPerform_MaxAge(strDate, dtmDate)
   spExec_SumPerform = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the spSelectInto_SumGenEval_Farms SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_Farms(ByVal strIDFarm As String)
   Dim strCmdTxt As String
   strCmdTxt = "select IDFarm, IDPersFarmer into SumPerform_Farms from Farms where " & _
      "IDFarm = """ & strIDFarm & """"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumPerform_SheepGoat SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_SheepGoat(ByVal strIDFarm As String, ByVal _
   strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = _
      "SELECT IDFarm, IDSheepGoat, IDSex, BreedCross, DateBirth, TypeBirth " & _
         "INTO SumPerform_SheepGoat " & _
         "FROM SheepGoat " & _
         "WHERE IDFarm = """ & strIDFarm & """ AND " & _
            "(DateBirth <= #" & strDateEnd & "#) AND " _
            & "((IDDispReas = ""-"") OR " & _
            "((IDDispReas <> ""-"" AND DateDisp > #" & strDateEnd & "#))) " & _
         "ORDER BY IDSheepGoat"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spAlter_SumPerform_SheepGoat SP.
' Trap an error in the calling proc.
Private Sub spAlter_SumPerform_SheepGoat()
   Dim strCmdTxt As String
   strCmdTxt = "ALTER TABLE SumPerform_SheepGoat ADD IDAgeSex Text(1)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spAlter_SumPerform_SheepGoat SP.
' Trap an error in the calling proc.
Private Sub spUpdate_SumPerform_SheepGoat(ByVal strDate As String)
   Const strIDAgeSex1 As String = "1"
   Const strIDAgeSex2 As String = "2"
   Const strIDAgeSex3 As String = "3"
   Const strIDAgeSex4 As String = "4"
   Const strIDAgeSex5 As String = "5"
   Const strIDAgeSex6 As String = "6"
   Const strIDSexMale As String = "0"
   Const strIDSexFemale As String = "1"
   Dim strCmdTxt As String
   With gdbDB
      strCmdTxt = _
      "UPDATE SumPerform_SheepGoat SET IDAgeSex = '" & strIDAgeSex1 & "' " & _
         "WHERE #" & strDate & "# - DateBirth >= (SELECT Age FROM AgeSex WHERE " & _
            "IDAgeSex = '" & strIDAgeSex1 & "') AND " & _
            "IDSex = '" & strIDSexMale & "'" 'Mark mature males.
      .Execute strCmdTxt
      strCmdTxt = _
      "UPDATE SumPerform_SheepGoat SET IDAgeSex = '" & strIDAgeSex2 & "' " & _
         "WHERE #" & strDate & "# - DateBirth >= (SELECT Age FROM AgeSex WHERE " & _
            "IDAgeSex = '" & strIDAgeSex2 & "') AND " & _
            "IDSex = '" & strIDSexFemale & "'" 'Mark mature females.
      .Execute strCmdTxt
      strCmdTxt = _
      "UPDATE SumPerform_SheepGoat SET IDAgeSex = '" & strIDAgeSex3 & "' " & _
         "WHERE #" & strDate & "# - DateBirth >= (SELECT Age FROM AgeSex WHERE " _
            & "IDAgeSex = '" & strIDAgeSex3 & "') AND #" & _
            strDate & "# - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = '" _
               & strIDAgeSex1 & "') AND " & _
            "IDSex = '" & strIDSexMale & "'" 'Mark males > 1 year.
      .Execute strCmdTxt
      strCmdTxt = _
      "UPDATE SumPerform_SheepGoat SET IDAgeSex = '" & strIDAgeSex4 & "'" & _
         "WHERE #" & strDate & "# - DateBirth >= (SELECT Age FROM AgeSex WHERE " & _
            "IDAgeSex = '" & strIDAgeSex4 & "') AND #" & _
            strDate & "# - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = '" _
               & strIDAgeSex2 & "') AND " & _
            "IDSex = '" & strIDSexFemale & "'" 'Mark females > 1 year.
      .Execute strCmdTxt
      strCmdTxt = _
      "UPDATE SumPerform_SheepGoat SET IDAgeSex = '" & strIDAgeSex5 & "'" & _
         "WHERE #" & strDate & "# - DateBirth < (SELECT Age FROM AgeSex WHERE " & _
            "IDAgeSex = '" & strIDAgeSex3 & "') AND " & _
            "IDSex = '" & strIDSexMale & "'" 'Mark males < 1 year.
      .Execute strCmdTxt
      strCmdTxt = "UPDATE SumPerform_SheepGoat Set IDAgeSex = '" & strIDAgeSex6 & "' WHERE #" & strDate & "# - DateBirth < (SELECT Age FROM AgeSex WHERE IDAgeSex = '" & strIDAgeSex4 & "') AND IDSex = '" & strIDSexFemale & "'" 'Mark females < 1 year.
      .Execute strCmdTxt
   End With
End Sub

' Execute the spSelectInto_SumPerform_WeightWean SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_WeightWean(ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT WeightWean.IDLambKid, WeightWean.WtWean INTO SumPerform_WeightWean FROM WeightWean INNER JOIN SumPerform_SheepGoat ON WeightWean.IDLambKid = SumPerform_SheepGoat.IDSheepGoat WHERE (WeightWean.DateWean <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumPerform_Weight7Mon SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_Weight7Mon(ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Weight7Mon.IDLambKid, Weight7Mon.Wt7Mon INTO SumPerform_Weight7Mon FROM Weight7Mon INNER JOIN SumPerform_SheepGoat ON Weight7Mon.IDLambKid = SumPerform_SheepGoat.IDSheepGoat WHERE (Weight7Mon.Date7Mon <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumPerform_WeightWoolAnnl SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_WeightWoolAnnl(ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl , WeightWoolAnnl.GreaseAnnl INTO SumPerform_WeightWoolAnnl FROM SumPerform_SheepGoat INNER JOIN WeightWoolAnnl ON SumPerform_SheepGoat.IDSheepGoat = WeightWoolAnnl.IDSheepGoat WHERE (WeightWoolAnnl.DateAnnl <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumPerform_Appraisal SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_Appraisal(ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.Leng, ([Diameter].[DiamFrom]+[Diameter].[DiamTo])/2 AS Diam INTO SumPerform_Appraisal FROM SumPerform_SheepGoat INNER JOIN (Diameter INNER JOIN Appraisal ON Diameter.Diam = Appraisal.Diam) ON SumPerform_SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat WHERE (Appraisal.DateAppr <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumPerform_MaxAge SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumPerform_MaxAge(ByVal strDateEnd As String, ByVal dtmDateEnd _
   As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String
   strDateBegin = Util.DateStrRpt(dtmDateEnd - Int(gobSetng.YearDays))
   strCmdTxt = "SELECT IDSheepGoat, MAX(Age) AS MaxAge INTO SumPerform_MaxAge FROM SumPerform_WeightWoolAnnl WHERE (DateAnnl >= #" & strDateBegin & "# AND DateAnnl <= #" & strDateEnd & "#) GROUP BY IDSheepGoat HAVING (MAX(Age) > 1)"
   gdbDB.Execute strCmdTxt
End Sub

