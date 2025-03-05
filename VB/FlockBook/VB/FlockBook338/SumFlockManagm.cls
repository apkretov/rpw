VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "SumFlockManagm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTblSel

' Query the data.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim strIDFarm As String
   Dim strDateBeg As String
   Dim strDateEnd As String
   Dim dtmDateBeg As Date
   Dim dtmDateEnd As Date
   Call DropTable 'Drop tables.
   strIDFarm = vntKeys(0)
   strDateBeg = Util.DateStrRpt(vntKeys(1)) 'Convert dates to strings.
   strDateEnd = Util.DateStrRpt(vntKeys(2))
   dtmDateBeg = vntKeys(1)
   dtmDateEnd = vntKeys(2)
   If spExec_SumFlockManagm_SelectInto(strIDFarm, strDateBeg, dtmDateBeg, strDateEnd, _
      dtmDateEnd) Then If spExec_SumFlockManagm_Reprod Then If _
      spSelectInto_SumFlockManagm_BearDistr Then If spExec_SumFlockManagm_PerfAge Then _
      If spSelectInto_SumFlockManagm_Disp Then DatTblSel_Sel = _
      spExec_SumFlockManagm_PerfSexAge(strIDFarm, strDateBeg, strDateEnd, dtmDateEnd)
   DatTblSel_Sel = True 'The operation succeeded
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Drop the creatable tables.
Private Sub DropTable()
On Error Resume Next
   With gdbDB
      .Execute "DROP TABLE SumFlockManagm_Farms"
      .Execute "DROP TABLE SumFlockManagm_Mate"
      .Execute "DROP TABLE SumFlockManagm_LambKid"
      .Execute "DROP TABLE SumFlockManagm_Offspring"
      .Execute "DROP TABLE SumFlockManagm_LambKidWeaned"
      .Execute "DROP TABLE SumFlockManagm_WoolAnnl"
      .Execute "DROP TABLE SumFlockManagm_Appraisal"
      .Execute "DROP TABLE SumFlockManagm_WeightWean"
      .Execute "DROP TABLE SumFlockManagm_Weight7Mon"
      .Execute "DROP TABLE SumFlockManagm_WeightAnnl"
      .Execute "DROP TABLE SumFlockManagm_SheepGoat"
      .Execute "DROP TABLE SumFlockManagm_SheepGoatDisp"
      .Execute "DROP TABLE SumFlockManagm_LambKidCount"
      .Execute "DROP TABLE SumFlockManagm_Disp_TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Reprod_AbortCount"
      .Execute "DROP TABLE SumFlockManagm_Reprod_OffspBornCount"
      .Execute "DROP TABLE SumFlockManagm_Reprod"
      .Execute "DROP TABLE SumFlockManagm_BearDistr_AllAge"
      .Execute "DROP TABLE SumFlockManagm_BearDistr1"
      .Execute "DROP TABLE SumFlockManagm_BearDistr2"
      .Execute "DROP TABLE SumFlockManagm_BearDistr3"
      .Execute "DROP TABLE SumFlockManagm_BearDistr4"
      .Execute "DROP TABLE SumFlockManagm_PerfAge_WeightAge"
      .Execute "DROP TABLE SumFlockManagm_PerfAge_GreaseAge"
      .Execute "DROP TABLE SumFlockManagm_PerfAge_WeightGroup"
      .Execute "DROP TABLE SumFlockManagm_PerfAge_GreaseGroup"
      .Execute "DROP TABLE SumFlockManagm_PerfAge"
      .Execute "DROP TABLE SumFlockManagm_Disp_All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male1All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female2All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male3All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female4All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male5All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female6All"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male1TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male1Total"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female2TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female2Total"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male3TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male3Total"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female4TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female4Total"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male5TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Disp_Male5Total"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female6TotalDisp"
      .Execute "DROP TABLE SumFlockManagm_Disp_Female6Total"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge_FarmSexAge"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge_WtBirth"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge_WtMaxAge"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge_WoolMaxAge"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge_WtAnnl"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge_WoolAnnl"
      .Execute "DROP TABLE SumFlockManagm_PerfSexAge"
   End With
End Sub

' Execute the spExec_SumFlockManagm_SelectInto SP.
' Trap an error in the calling proc.
' Return True, if succeeds.
Private Function spExec_SumFlockManagm_SelectInto(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal dtmDateBeg As Date, ByVal strDateEnd As String, ByVal _
   dtmDateEnd As Date) As Boolean
   Call spSelectInto_SumFlockManagm_Farms(strIDFarm)
   Call spSelectInto_SumFlockManagm_Mate(strIDFarm, dtmDateBeg, dtmDateEnd)
   With gdbDB
      .Execute "spSelectInto_SumFlockManagm_LambKid"
      .Execute "spSelectInto_SumFlockManagm_Offspring"
      Call spSelectInto_SumFlockManagm_LambKidWeaned(strIDFarm, dtmDateBeg, dtmDateEnd)
      Call spSelectInto_SumFlockManagm_WoolAnnl(strIDFarm, strDateBeg, strDateEnd)
      Call spSelectInto_SumFlockManagm_Appraisal(strIDFarm, strDateBeg, strDateEnd)
      Call spSelectInto_SumFlockManagm_WeightWean(strIDFarm, strDateBeg, strDateEnd)
      Call spSelectInto_SumFlockManagm_Weight7Mon(strIDFarm, strDateBeg, strDateEnd)
      Call spSelectInto_SumFlockManagm_WeightAnnl(strIDFarm, strDateBeg, strDateEnd)
      Call spSelectInto_SumFlockManagm_SheepGoat(strIDFarm, strDateEnd)
      Call spAlter_SumFlockManagm_SheepGoat
      Call spUpdate_SumFlockManagm_SheepGoat(strDateEnd)
      Call spSelectInto_SumFlockManagm_SheepGoatDisp(strIDFarm, strDateBeg, strDateEnd)
      Call spAlter_SumFlockManagm_SheepGoatDisp
      Call spUpdate_SumFlockManagm_SheepGoatDisp
      .Execute "spSelectInto_SumFlockManagm_LambKidCount"
      .Execute "spSelectInto_SumFlockManagm_Disp_TotalDisp"
   End With
   spExec_SumFlockManagm_SelectInto = True 'Succeeded.
End Function

' Execute the spSelectInto_SumFlockManagm_Farms SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_Farms(ByVal strIDFarm As String)
   Dim strCmdTxt As String
   strCmdTxt = "select IDFarm, IDPersFarmer into SumFlockManagm_Farms from Farms " & _
      "where IDFarm = """ & strIDFarm & """"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spSelectInto_SumFlockManagm_Mate SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_Mate(ByVal strIDFarm As String, ByVal _
   dtmDateBeg As Date, ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBeginShift As String
   Dim strDateEndShift As String
   strDateBeginShift = Util.DateStrRpt(dtmDateBeg - gobTblCtrlParam.PregnLengNorm)
   strDateEndShift = Util.DateStrRpt(dtmDateEnd - gobTblCtrlParam.PregnLengNorm)
   strCmdTxt = "SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle INTO SumFlockManagm_Mate FROM SheepGoat INNER JOIN Mate ON SheepGoat.IDSheepGoat = Mate.IDDam " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(SheepGoat.IDDispReas = ""-"") AND " & _
         "(Mate.DateMatFrom >= #" & strDateBeginShift & "#) AND " & _
         "(Mate.DateMatFrom <= #" & strDateEndShift & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumFlockManagm_LambKidWeaned SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_LambKidWeaned(ByVal strIDFarm As String, ByVal _
   dtmDateBeg As Date, ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBeginShift As String
   Dim strDateEndShift As String
   strDateBeginShift = Util.DateStrRpt(dtmDateBeg - gobTblCtrlParam.AgeWeanMax)
   strDateEndShift = Util.DateStrRpt(dtmDateEnd - gobTblCtrlParam.AgeWeanMax)
   strCmdTxt = "SELECT SheepGoat.IDFarm, LambKid.IDDam, LambKid.Cycle, LambKid.CycleLambKid INTO SumFlockManagm_LambKidWeaned FROM SheepGoat INNER JOIN LambKid ON SheepGoat.IDSheepGoat = LambKid.IDDam " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(LambKid.DateLambKid >= #" & strDateBeginShift & "#) AND " & _
         "(LambKid.DateLambKid <= #" & strDateEndShift & "#)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumFlockManagm_WoolAnnl SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_WoolAnnl(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateShearAnnl, WeightWoolAnnl.GreaseAnnl, SheepGoat.DateBirth INTO SumFlockManagm_WoolAnnl FROM SheepGoat INNER JOIN WeightWoolAnnl ON SheepGoat.IDSheepGoat = WeightWoolAnnl.IDSheepGoat " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(WeightWoolAnnl.DateShearAnnl >= #" & strDateBeg & "#) AND " & _
         "(WeightWoolAnnl.DateShearAnnl <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spSelectInto_SumFlockManagm_Appraisal SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_Appraisal(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT SheepGoat.IDFarm, Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, ([Diameter].[DiamFrom]+[Diameter].[DiamTo])/2 AS Diam INTO SumFlockManagm_Appraisal FROM Diameter INNER JOIN (SheepGoat INNER JOIN Appraisal ON SheepGoat.IDSheepGoat = Appraisal.IDSheepGoat) ON Diameter.Diam = Appraisal.Diam " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(Appraisal.DateAppr >= #" & strDateBeg & "#) AND " & _
         "(Appraisal.DateAppr <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spSelectInto_SumFlockManagm_WeightWean SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_WeightWean(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT WeightWean.IDLambKid, WeightWean.WtWean INTO SumFlockManagm_WeightWean FROM SheepGoat INNER JOIN WeightWean ON SheepGoat.IDSheepGoat = WeightWean.IDLambKid " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(WeightWean.DateWean >= #" & strDateBeg & "#) AND " & _
         "(WeightWean.DateWean <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spSelectInto_SumFlockManagm_Weight7Mon SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_Weight7Mon(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Weight7Mon.IDLambKid, Weight7Mon.Wt7Mon INTO SumFlockManagm_Weight7Mon FROM SheepGoat INNER JOIN Weight7Mon ON SheepGoat.IDSheepGoat = Weight7Mon.IDLambKid " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(Weight7Mon.Date7Mon >= #" & strDateBeg & "#) AND " & _
         "(Weight7Mon.Date7Mon <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spSelectInto_SumFlockManagm_WeightAnnl SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_WeightAnnl(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl , SheepGoat.DateBirth INTO SumFlockManagm_WeightAnnl FROM SheepGoat INNER JOIN WeightWoolAnnl ON SheepGoat.IDSheepGoat = WeightWoolAnnl.IDSheepGoat " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(WeightWoolAnnl.DateAnnl >= #" & strDateBeg & "#) AND " & _
         "(WeightWoolAnnl.DateAnnl <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spSelectInto_SumFlockManagm_SheepGoat SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_SheepGoat(ByVal strIDFarm As String, ByVal _
   strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT IDFarm, IDSheepGoat, IDSex, DateBirth INTO SumFlockManagm_SheepGoat FROM SheepGoat " & _
      "WHERE (IDFarm = """ & strIDFarm & """) AND " & _
         "(DateBirth <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spAlter_SumFlockManagm_SheepGoat SP.
' Trap an error in the calling proc.
Private Sub spAlter_SumFlockManagm_SheepGoat()
   Dim strCmdTxt As String
   strCmdTxt = "ALTER TABLE SumFlockManagm_SheepGoat ADD IDAgeSex char(1)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spUpdate_SumFlockManagm_SheepGoat SP.
' Trap an error in the calling proc.
Private Sub spUpdate_SumFlockManagm_SheepGoat(ByVal strDateEnd As String)
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
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoat SET IDAgeSex = """ & strIDAgeSex1 & """ " & _
         "WHERE #" & strDateEnd & "# - DateBirth >= " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex1 & """) AND " & _
            "IDSex = """ & strIDSexMale & """"
      .Execute strCmdTxt
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoat SET IDAgeSex = """ & strIDAgeSex2 & """ " & _
         "WHERE #" & strDateEnd & "# - DateBirth >= " & _
         "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex2 & """) AND " & _
         "IDSex = """ & strIDSexFemale & """"
      .Execute strCmdTxt
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoat SET IDAgeSex = """ & strIDAgeSex3 & """ " & _
         "WHERE #" & strDateEnd & "# - DateBirth >= " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex3 & """) AND " & _
            "#" & strDateEnd & "# - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex1 & """) AND " & _
            "IDSex = """ & strIDSexMale & """"
      .Execute strCmdTxt
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoat SET IDAgeSex = """ & strIDAgeSex4 & """ " & _
         "WHERE #" & strDateEnd & "# - DateBirth >= " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex4 & """) AND " & _
            "#" & strDateEnd & "# - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex2 & """) AND " & _
            "IDSex = """ & strIDSexFemale & """"
      .Execute strCmdTxt
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoat SET IDAgeSex = """ & strIDAgeSex5 & """ " & _
         "WHERE #" & strDateEnd & "# - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex3 & """) AND " & _
            "IDSex = """ & strIDSexMale & """"
      .Execute strCmdTxt
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoat SET IDAgeSex = """ & strIDAgeSex6 & """ " & _
         "WHERE #" & strDateEnd & "# - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex4 & """) AND " & _
            "IDSex = """ & strIDSexFemale & """"
      .Execute strCmdTxt
   End With
End Sub

' Execute the spSelectInto_SumFlockManagm_SheepGoatDisp SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_SheepGoatDisp(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT IDFarm, IDSheepGoat, IDSex, DateBirth, DateDisp, IDDispReas INTO SumFlockManagm_SheepGoatDisp FROM SheepGoat " & _
      "WHERE (IDFarm = """ & strIDFarm & """) AND " & _
         "(IDDispReas <> ""-"") AND " & _
         "(DateDisp >= #" & strDateBeg & "# ) AND " & _
         "(DateDisp <= #" & strDateEnd & "#)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spAlter_SumFlockManagm_SheepGoatDisp SP.
' Trap an error in the calling proc.
Private Sub spAlter_SumFlockManagm_SheepGoatDisp()
   Dim strCmdTxt As String
   strCmdTxt = "ALTER TABLE SumFlockManagm_SheepGoatDisp ADD IDAgeSex char(1)"
   gdbDB.Execute strCmdTxt
'   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
End Sub

' Execute the spUpdate_SumFlockManagm_SheepGoatDisp SP.
' Trap an error in the calling proc.
Private Sub spUpdate_SumFlockManagm_SheepGoatDisp()
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
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoatDisp SET IDAgeSex = """ & strIDAgeSex1 & """ " & _
         "WHERE DateDisp - DateBirth >= " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex1 & """) AND " & _
            "IDSex = """ & strIDSexMale & """"
      .Execute strCmdTxt ', , adCmdText + adExecuteNoRecords 'Mark mature males.
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoatDisp SET IDAgeSex = """ & strIDAgeSex2 & """ " & _
         "WHERE DateDisp - DateBirth >= " & _
         "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex2 & """) AND " & _
         "IDSex = """ & strIDSexFemale & """"
      .Execute strCmdTxt ', , adCmdText + adExecuteNoRecords 'Mark mature females.
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoatDisp SET IDAgeSex = """ & strIDAgeSex3 & """ " & _
         "WHERE DateDisp - DateBirth >= " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex3 & """) AND " & _
            "DateDisp - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex1 & """) AND " & _
            "IDSex = """ & strIDSexMale & """"
      .Execute strCmdTxt ', , adCmdText + adExecuteNoRecords 'Mark males > 1 year.
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoatDisp SET IDAgeSex = """ & strIDAgeSex4 & """ " & _
         "WHERE DateDisp - DateBirth >= " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex4 & """) AND " & _
            "DateDisp - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex2 & """) AND " & _
            "IDSex = """ & strIDSexFemale & """"
      .Execute strCmdTxt ', , adCmdText + adExecuteNoRecords 'Mark females > 1 year.
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoatDisp SET IDAgeSex = """ & strIDAgeSex5 & """ " & _
         "WHERE DateDisp - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex3 & """) AND " & _
            "IDSex = """ & strIDSexMale & """"
      .Execute strCmdTxt ', , adCmdText + adExecuteNoRecords 'Mark males < 1 year.
      strCmdTxt = "UPDATE SumFlockManagm_SheepGoatDisp SET IDAgeSex = """ & strIDAgeSex6 & """ " & _
         "WHERE DateDisp - DateBirth < " & _
            "(SELECT Age FROM AgeSex WHERE IDAgeSex = """ & strIDAgeSex4 & """) AND " & _
            "IDSex = """ & strIDSexFemale & """"
      .Execute strCmdTxt ', , adCmdText + adExecuteNoRecords 'Mark females < 1 year.
   End With
End Sub

' Execute the spExec_SumFlockManagm_Reprod SP.
' Trap an error in the calling proc.
' Return True, if succeeds.
Private Function spExec_SumFlockManagm_Reprod() As Boolean
   With gdbDB
      .Execute "spSelectInto_SumFlockManagm_Reprod_AbortCount"
      .Execute "spSelectInto_SumFlockManagm_Reprod_OffspBornCount"
      .Execute "spSelectInto_SumFlockManagm_Reprod"
   End With
   spExec_SumFlockManagm_Reprod = True 'Succeeded.
End Function

' Execute the spSelectInto_SumFlockManagm_BearDistr SP.
' Trap an error in the calling proc.
' Return True, if succeeds.
Private Function spSelectInto_SumFlockManagm_BearDistr() As Boolean
   With gdbDB
      .Execute "spSelectInto_SumFlockManagm_BearDistr_AllAge"
      .Execute "spSelectInto_SumFlockManagm_BearDistr1"
      .Execute "spSelectInto_SumFlockManagm_BearDistr2"
      .Execute "spSelectInto_SumFlockManagm_BearDistr3"
      .Execute "spSelectInto_SumFlockManagm_BearDistr4"
   End With
   spSelectInto_SumFlockManagm_BearDistr = True 'Succeeded.
End Function

' Execute the spExec_SumFlockManagm_PerfAge SP.
' Trap an error in the calling proc.
' Return True, if succeeds.
Private Function spExec_SumFlockManagm_PerfAge() As Boolean
   With gdbDB
      .Execute "spSelectInto_SumFlockManagm_PerfAge_WeightAge"
      .Execute "spSelectInto_SumFlockManagm_PerfAge_GreaseAge"
      .Execute "spSelectInto_SumFlockManagm_PerfAge_WeightGroup"
      .Execute "spSelectInto_SumFlockManagm_PerfAge_GreaseGroup"
      .Execute "spSelectInto_SumFlockManagm_PerfAge"
   End With
   spExec_SumFlockManagm_PerfAge = True 'Succeeded.
End Function

' Execute the spSelectInto_SumFlockManagm_Disp SP.
' Trap an error in the calling proc.
' Return True, if succeeds.
Private Function spSelectInto_SumFlockManagm_Disp() As Boolean
   With gdbDB
      .Execute "spSelectInto_SumFlockManagm_Disp_All"
      .Execute "spSelectInto_SumFlockManagm_Disp_Male1All"
      .Execute "spSelectInto_SumFlockManagm_Disp_Female2All"
      .Execute "spSelectInto_SumFlockManagm_Disp_Male3All"
      .Execute "spSelectInto_SumFlockManagm_Disp_Female4All"
      .Execute "spSelectInto_SumFlockManagm_Disp_Male5All"
      .Execute "spSelectInto_SumFlockManagm_Disp_Female6All"
      .Execute "SumFlockManagmV_Disp_Male1TotalDisp"
      .Execute "SumFlockManagmV_Disp_Male1Total"
      .Execute "SumFlockManagmV_Disp_Female2TotalDisp"
      .Execute "SumFlockManagmV_Disp_Female2Total"
      .Execute "SumFlockManagmV_Disp_Male3TotalDisp"
      .Execute "SumFlockManagmV_Disp_Male3Total"
      .Execute "SumFlockManagmV_Disp_Female4TotalDisp"
      .Execute "SumFlockManagmV_Disp_Female4Total"
      .Execute "SumFlockManagmV_Disp_Male5TotalDisp"
      .Execute "SumFlockManagmV_Disp_Male5Total"
      .Execute "SumFlockManagmV_Disp_Female6TotalDisp"
      .Execute "SumFlockManagmV_Disp_Female6Total"
   End With
   spSelectInto_SumFlockManagm_Disp = True 'Succeeded.
End Function

' Execute the spExec_SumFlockManagm_PerfSexAge SP.
' Trap an error in the calling proc.
' Return True, if succeeds.
Private Function spExec_SumFlockManagm_PerfSexAge(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String, ByVal dtmDateEnd As Date) As Boolean
   gdbDB.Execute "spSelectInto_SumFlockManagm_PerfSexAge_FarmSexAge"
   Call spSelectInto_SumFlockManagm_PerfSexAge_WtBirth(strIDFarm, strDateBeg, _
      strDateEnd)
   Call spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge(strDateBeg, strDateEnd, _
      dtmDateEnd)
   Call spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge(strDateBeg, strDateEnd, _
      dtmDateEnd)
   Call spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl(strDateEnd, dtmDateEnd)
   Call spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl(strDateEnd, dtmDateEnd)
   gdbDB.Execute "spSelectInto_SumFlockManagm_PerfSexAge"
   spExec_SumFlockManagm_PerfSexAge = True 'Succeeded.
End Function

' Execute the spSelectInto_SumFlockManagm_PerfSexAge_WtBirth SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_PerfSexAge_WtBirth(ByVal strIDFarm As String, ByVal _
   strDateBeg As String, ByVal strDateEnd As String)
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Offspring.IDLambKid, Offspring.WtBirth INTO SumFlockManagm_PerfSexAge_WtBirth FROM LambKid INNER JOIN (SheepGoat INNER JOIN Offspring ON SheepGoat.IDSheepGoat = Offspring.IDLambKid) ON (LambKid.Cycle = Offspring.Cycle) AND (LambKid.IDDam = Offspring.IDDam) " & _
      "WHERE (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(LambKid.DateLambKid >= #" & strDateBeg & "#) AND " & _
         "(LambKid.DateLambKid <= #" & strDateEnd & "#) AND " & _
         "(Offspring.IDLambKid <> '-')"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_PerfSexAge_WtMaxAge(ByVal strDateBeg As String, _
   ByVal strDateEnd As String, ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBeginCurYr As String 'Current year's beginning.
   strDateBeginCurYr = Util.DateStrRpt(dtmDateEnd - Int(gobSetng.YearDays))
   strCmdTxt = "SELECT IDSheepGoat, MAX(Age) AS MaxAge INTO SumFlockManagm_PerfSexAge_WtMaxAge FROM SumFlockManagm_WeightAnnl " & _
      "WHERE (DateAnnl >= #" & strDateBeg & "# AND " & _
         "DateAnnl >= #" & strDateBeginCurYr & "# AND " & _
         "DateAnnl <= #" & strDateEnd & "#) " & _
      "GROUP BY IDSheepGoat " & _
      "HAVING (Max(Age) > 1)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_PerfSexAge_WoolMaxAge(ByVal strDateBeg As String, _
   ByVal strDateEnd As String, ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBeginCurYr As String 'Current year's beginning.
   strDateBeginCurYr = Util.DateStrRpt(dtmDateEnd - Int(gobSetng.YearDays))
   strCmdTxt = "SELECT IDSheepGoat, MAX(Age) AS MaxAge INTO SumFlockManagm_PerfSexAge_WoolMaxAge FROM SumFlockManagm_WoolAnnl " & _
      "WHERE (DateShearAnnl >= #" & strDateBeg & "# AND " & _
         "DateShearAnnl >= #" & strDateBeginCurYr & "# AND " & _
         "DateShearAnnl <= #" & strDateEnd & "#) " & _
      "GROUP BY IDSheepGoat " & _
      "HAVING (Max(Age) > 1)"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_PerfSexAge_WtAnnl(ByVal strDateEnd As String, _
   ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBeg As String
   strDateBeg = Util.DateStrRpt(dtmDateEnd - Int(gobSetng.YearDays))
   strCmdTxt = "SELECT SumFlockManagm_PerfSexAge_WtMaxAge.IDSheepGoat, SumFlockManagm_WeightAnnl.WtAnnl INTO SumFlockManagm_PerfSexAge_WtAnnl FROM SumFlockManagm_PerfSexAge_WtMaxAge INNER JOIN SumFlockManagm_WeightAnnl ON SumFlockManagm_PerfSexAge_WtMaxAge.IDSheepGoat = SumFlockManagm_WeightAnnl.IDSheepGoat AND SumFlockManagm_PerfSexAge_WtMaxAge.MaxAge = SumFlockManagm_WeightAnnl.Age " & _
      "WHERE SumFlockManagm_WeightAnnl.DateAnnl >= #" & strDateBeg & "# AND " & _
      "SumFlockManagm_WeightAnnl.DateAnnl <= #" & strDateEnd & "#"
   gdbDB.Execute strCmdTxt
End Sub

' Execute the spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl SP.
' Trap an error in the calling proc.
Private Sub spSelectInto_SumFlockManagm_PerfSexAge_WoolAnnl(ByVal strDateEnd As String, _
   ByVal dtmDateEnd As Date)
   Dim strCmdTxt As String
   Dim strDateBeg As String
   strDateBeg = Util.DateStrRpt(dtmDateEnd - Int(gobSetng.YearDays))
   strCmdTxt = "SELECT SumFlockManagm_PerfSexAge_WoolMaxAge.IDSheepGoat, SumFlockManagm_WoolAnnl.GreaseAnnl INTO SumFlockManagm_PerfSexAge_WoolAnnl FROM SumFlockManagm_PerfSexAge_WoolMaxAge INNER JOIN SumFlockManagm_WoolAnnl ON (SumFlockManagm_PerfSexAge_WoolMaxAge.MaxAge = SumFlockManagm_WoolAnnl.Age) AND (SumFlockManagm_PerfSexAge_WoolMaxAge.IDSheepGoat = SumFlockManagm_WoolAnnl.IDSheepGoat) " & _
      "WHERE SumFlockManagm_WoolAnnl.DateShearAnnl >= #" & strDateBeg & "# AND " & _
      "SumFlockManagm_WoolAnnl.DateShearAnnl <= #" & strDateEnd & "#"
   gdbDB.Execute strCmdTxt
End Sub
