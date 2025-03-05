VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SumGenEval"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTblSel
   
'Dim mstrIDFarm As String
'Dim mstrDate As String

' Query data.
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
   DatTblSel_Sel = spExec_SumGenEval(strIDFarm, strDate, dtmDate) 'Succeeded.
Exit Function
ErrHnd:
   MsgBox Err.Description
   DatTblSel_Sel = False 'Failed.
End Function

' Drop the creatable tables.
Private Sub DropTable()
On Error Resume Next
   With gdbDB
      .Execute "DROP TABLE SumGenEval_Farms"
      .Execute "DROP TABLE SumGenEval_FarmBrdSrOffsp"
      .Execute "DROP TABLE SumGenEval_WtBirth"
      .Execute "DROP TABLE SumGenEval_WtBirthSire"
      .Execute "DROP TABLE SumGenEval_WtWean"
      .Execute "DROP TABLE SumGenEval_WtWeanSire"
      .Execute "DROP TABLE SumGenEval_Wt7Mon"
      .Execute "DROP TABLE SumGenEval_Wt7MonSire"
      .Execute "DROP TABLE SumGenEval_Weight"
      .Execute "DROP TABLE SumGenEval_Wool"
      .Execute "DROP TABLE SumGenEval_Appraisal"
      .Execute "DROP TABLE SumGenEval_WeightSire"
      .Execute "DROP TABLE SumGenEval_WoolSire"
      .Execute "DROP TABLE SumGenEval_ApprSire"
   End With
End Sub

' Execute the spExec_SumGenEval SP.
' Return True, if succeeds.
Private Function spExec_SumGenEval(ByVal strIDFarm As String, ByVal strDate As String, _
   ByVal dtmDate As Date) As Boolean
On Error GoTo ErrHnd
   Call spSelectInto_SumGenEval_Farms(strIDFarm)
   Call spSelectInto_SumGenEval_FarmBrdSrOffsp(strIDFarm, strDate, dtmDate)
   Call spSelectInto_SumGenEval_WtBirth(strDate, dtmDate)
   With gdbDB
      .Execute "spSelectInto_SumGenEval_WtBirthSire"
      Call spSelectInto_SumGenEval_WtWean(strDate, dtmDate)
      .Execute "spSelectInto_SumGenEval_WtWeanSire"
      Call spSelectInto_SumGenEval_Wt7Mon(strDate, dtmDate)
      .Execute "spSelectInto_SumGenEval_Wt7MonSire"
      Call spSelectInto_SumGenEval_Weight(strDate, dtmDate)
      Call spSelectInto_SumGenEval_Wool(strDate, dtmDate)
      Call spSelectInto_SumGenEval_Appraisal(strDate, dtmDate)
      .Execute "spSelectInto_SumGenEval_WeightSire"
      .Execute "spSelectInto_SumGenEval_WoolSire"
      .Execute "spSelectInto_SumGenEval_ApprSire"
   End With
   spExec_SumGenEval = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the spSelectInto_SumGenEval_Farms SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_Farms(ByVal strIDFarm As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Farms.IDFarm, Persons.Nam INTO SumGenEval_Farms FROM Farms " & _
      "INNER JOIN Persons ON Farms.IDPersFarmer = Persons.IDPers WHERE Farms.IDFarm = """ _
      & strIDFarm & """"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_FarmBrdSrOffsp SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_FarmBrdSrOffsp(ByVal strIDFarm As String, ByVal _
   strDateEnd As String, ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateMinAge As String
   strDateMinAge = Util.DateStrRpt(dtmDateEnd - gobTblCtrlParam.AgeMatMinSr - _
      gobTblCtrlParam.PregnLengMin)
   strCmdTxt = _
   "SELECT SheepGoat.IDFarm, SheepGoat.BreedCross, Mate.IDSire, Offspring.IDLambKid INTO SumGenEval_FarmBrdSrOffsp FROM SheepGoat INNER JOIN (Mate INNER JOIN (LambKid INNER JOIN Offspring ON (LambKid.IDDam = Offspring.IDDam) AND (LambKid.Cycle = Offspring.Cycle)) ON (Mate.IDDam = LambKid.IDDam) AND (Mate.Cycle = LambKid.Cycle)) ON SheepGoat.IDSheepGoat = Mate.IDSire " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
             "(SheepGoat.DateBirth <= #" & strDateMinAge & "#) AND " & _
             "((SheepGoat.IDDispReas = ""-"") OR " & _
             "((SheepGoat.IDDispReas <> ""-"" AND " & _
             "SheepGoat.DateDisp > #" & strDateEnd & "#))) AND " & _
             "(Offspring.IDLambKid <> ""-"")"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_WtBirth SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_WtBirth(ByVal strDateEnd As String, ByVal _
   dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String 'The beginning date for the BV calculation.
   strDateBegin = Util.DateStrRpt(dtmDateEnd - spSelectInto_SumGenEval_BVSpan)
   strCmdTxt = "SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, SumGenEval_FarmBrdSrOffsp.IDSire, Offspring.WtBirth INTO SumGenEval_WtBirth FROM SumGenEval_FarmBrdSrOffsp INNER JOIN (LambKid INNER JOIN Offspring ON (LambKid.Cycle = Offspring.Cycle) AND (LambKid.IDDam = Offspring.IDDam)) ON SumGenEval_FarmBrdSrOffsp.IDLambKid = Offspring.IDLambKid " & _
      "WHERE (LambKid.DateLambKid >= #" & strDateBegin & "#) AND " & _
          "(LambKid.DateLambKid <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_BVSpan SP: define the BV calculation span:
'  life time vs. years by the control parameters.
' Trap an error in the calling proc.
Private Function spSelectInto_SumGenEval_BVSpan() As Long
   With gobTblCtrlParam
      If .BVTestLifeTime Then 'During life time?
         spSelectInto_SumGenEval_BVSpan = CLng(gobSetng.YearDays * .LifeTimeMax)
      Else
         spSelectInto_SumGenEval_BVSpan = CLng(gobSetng.YearDays * .BVTestYr)
      End If
   End With
End Function

' Execute the spSelectInto_SumGenEval_WtWean SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_WtWean(ByVal strDateEnd As String, ByVal dtmDateEnd _
   As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String 'The beginning date for the BV calculation.
   strDateBegin = Util.DateStrRpt(dtmDateEnd - spSelectInto_SumGenEval_BVSpan)
   strCmdTxt = "SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, SumGenEval_FarmBrdSrOffsp.IDSire, WeightWean.WtWean INTO SumGenEval_WtWean FROM SumGenEval_FarmBrdSrOffsp INNER JOIN WeightWean ON SumGenEval_FarmBrdSrOffsp.IDLambKid = WeightWean.IDLambKid " & _
      "WHERE (WeightWean.DateWean >= #" & strDateBegin & "#) AND " & _
          "(WeightWean.DateWean <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_Wt7Mon SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_Wt7Mon(ByVal strDateEnd As String, ByVal dtmDateEnd _
   As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String 'The beginning date for the BV calculation.
   strDateBegin = Util.DateStrRpt(dtmDateEnd - spSelectInto_SumGenEval_BVSpan)
   strCmdTxt = "SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, SumGenEval_FarmBrdSrOffsp.IDSire, Weight7Mon.Wt7Mon INTO SumGenEval_Wt7Mon FROM SumGenEval_FarmBrdSrOffsp INNER JOIN Weight7Mon ON SumGenEval_FarmBrdSrOffsp.IDLambKid = Weight7Mon.IDLambKid " & _
      "WHERE (Weight7Mon.Date7Mon >= #" & strDateBegin & "#) AND " & _
          "(Weight7Mon.Date7Mon <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_Weight SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_Weight(ByVal strDateEnd As String, ByVal dtmDateEnd _
   As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String 'The beginning date for the BV calculation.
   strDateBegin = Util.DateStrRpt(dtmDateEnd - spSelectInto_SumGenEval_BVSpan)
   strCmdTxt = "SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, SumGenEval_FarmBrdSrOffsp.IDSire , WeightWoolAnnl.WtAnnl INTO SumGenEval_Weight FROM SumGenEval_FarmBrdSrOffsp INNER JOIN WeightWoolAnnl ON SumGenEval_FarmBrdSrOffsp.IDLambKid = WeightWoolAnnl.IDSheepGoat " & _
      "WHERE (WeightWoolAnnl.DateAnnl >= #" & strDateBegin & "#) AND " & _
         "(WeightWoolAnnl.DateAnnl <= #" & strDateEnd & "#) AND " & _
         "(WeightWoolAnnl.Age = 1)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_Wool SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_Wool(ByVal strDateEnd As String, ByVal dtmDateEnd _
   As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String 'The beginning date for the BV calculation.
   strDateBegin = Util.DateStrRpt(dtmDateEnd - spSelectInto_SumGenEval_BVSpan)
   strCmdTxt = "SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, SumGenEval_FarmBrdSrOffsp.IDSire , WeightWoolAnnl.GreaseAnnl INTO SumGenEval_Wool FROM SumGenEval_FarmBrdSrOffsp INNER JOIN WeightWoolAnnl ON SumGenEval_FarmBrdSrOffsp.IDLambKid = WeightWoolAnnl.IDSheepGoat " & _
      "WHERE (WeightWoolAnnl.DateShearAnnl >= #" & strDateBegin & "#) AND " & _
         "(WeightWoolAnnl.DateShearAnnl <= #" & strDateEnd & "#) AND " & _
         "(WeightWoolAnnl.Age = 1)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumGenEval_Appraisal SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumGenEval_Appraisal(ByVal strDateEnd As String, ByVal _
   dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBegin As String 'The beginning date for the BV calculation.
   strDateBegin = Util.DateStrRpt(dtmDateEnd - spSelectInto_SumGenEval_BVSpan)
   strCmdTxt = "SELECT SumGenEval_FarmBrdSrOffsp.IDFarm, SumGenEval_FarmBrdSrOffsp.BreedCross, SumGenEval_FarmBrdSrOffsp.IDSire, Appraisal.Leng, ([Diameter].[DiamFrom]+[Diameter].[DiamTo])/2 AS Diam INTO SumGenEval_Appraisal FROM SumGenEval_FarmBrdSrOffsp INNER JOIN (Diameter INNER JOIN Appraisal ON Diameter.Diam = Appraisal.Diam) ON SumGenEval_FarmBrdSrOffsp.IDLambKid = Appraisal.IDSheepGoat " & _
      "WHERE (Appraisal.DateAppr >= #" & strDateBegin & "#) AND " & _
         "(Appraisal.DateAppr <= #" & strDateEnd & "#) AND " & _
         "(Appraisal.Age = 1)"
   gdbDB.Execute strCmdTxt
End Sub
