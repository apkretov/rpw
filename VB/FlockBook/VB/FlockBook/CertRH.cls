VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CertRH"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTblSel

Dim mobCert As Cert

' Initialise the module-level variables.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobCert = New Cert
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Query the data.
' Return True, if succeeds.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim obTblShG As TblShG
   Dim obDatTbl As DatTbl
   Dim strIDShG As String
   Dim strDate As String
   Call DropTable 'Drop tables.
   strIDShG = vntKeys(0)
   Set obTblShG = New TblShG 'Get the animal's farm ID.
   Set obDatTbl = obTblShG
   obDatTbl.Sel strIDShG
   strDate = Util.DateStrRpt(Date)
   DatTblSel_Sel = spExec_CertRamHegoat(obTblShG.IDFarm, strIDShG, strDate)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Drop the creatable tables.
Private Sub DropTable()
On Error Resume Next
   mobCert.DropTable 'Drop sex-irrelevant certificate tables.
   With gdbDB
      .Execute "DROP TABLE CertRamHegoat_SireOffspring"
      .Execute "DROP TABLE CertRamHegoat_Mate"
      .Execute "DROP TABLE CertRamHegoat_BV_WtBirth"
      .Execute "DROP TABLE CertRamHegoat_BV_WtWean"
      .Execute "DROP TABLE CertRamHegoat_BV_Wt7Mon"
      .Execute "DROP TABLE CertRamHegoat_BV_Weight"
      .Execute "DROP TABLE CertRamHegoat_BV_Wool"
      .Execute "DROP TABLE CertRamHegoat_BV_Appr"
   End With
End Sub

' Execute the spExec_CertRamHegoat SP.
' Return True, if succeeds.
Private Function spExec_CertRamHegoat(ByVal strIDFarm As String, ByVal strIDShG _
   As String, strDate As String) As Boolean
On Error GoTo ErrHnd
   Dim obSumGenEval As SumGenEval
   Dim obDatTblSel As DatTblSel
   With mobCert
      .IDShG = strIDShG
      .spSelectInto_Cert_SheepGoat
   '   Call spSelectInto_Cert_SheepGoat(strIDShG)
      gdbDB.Execute "spSelectInto_Cert_SheepGoatSire"
      gdbDB.Execute "spSelectInto_Cert_SheepGoatDam"
      Call spUpdate_Cert(strIDShG)
      .spSelectInto_Cert_WeightWoolAnnl
      .spSelectInto_Cert_PerfAge_YrAllExec
      .spSelectInto_Cert_Appraisal
      .spSelectInto_Cert_ApprAge_YrAllExec
   End With
   Call spSelectInto_CertRamHegoat_SireOffspring(strIDShG)
   Call spSelectInto_CertRamHegoat_Mate(strIDShG)
   Set obSumGenEval = New SumGenEval
   Set obDatTblSel = obSumGenEval
   obDatTblSel.Sel strIDFarm, strDate
   Call spSelectInto_CertRamHegoat_BV_WtBirth(strIDShG)
   Call spSelectInto_CertRamHegoat_BV_WtWean(strIDShG)
   Call spSelectInto_CertRamHegoat_BV_Wt7Mon(strIDShG)
   Call spSelectInto_CertRamHegoat_BV_Weight(strIDShG)
   Call spSelectInto_CertRamHegoat_BV_Wool(strIDShG)
   Call spSelectInto_CertRamHegoat_BV_Appr(strIDShG)
   spExec_CertRamHegoat = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the spUpdate_Cert SP.
Private Sub spUpdate_Cert(ByVal strIDShG As String)
On Error GoTo ErrHnd
Dim strCmdTxt As String
   With gdbDB 'Delete hyphens from the pedigree tables: Cert_SheepGoatSire, Cert_SheepGoatSire, Cert_SheepGoatDam, Cert_SheepGoatDam.
      strCmdTxt = "UPDATE Cert_SheepGoatSire SET IDSiresSire = """" WHERE IDSiresSire = ""-"""
      .Execute strCmdTxt
      strCmdTxt = "UPDATE Cert_SheepGoatSire SET IDSiresDam = """" WHERE IDSiresDam = ""-"""
      .Execute strCmdTxt
      strCmdTxt = "UPDATE Cert_SheepGoatDam SET IDDamsSire = """" WHERE IDDamsSire = ""-"""
      .Execute strCmdTxt
      strCmdTxt = "UPDATE Cert_SheepGoatDam SET IDDamsDam = """" WHERE IDDamsDam = ""-"""
      .Execute strCmdTxt
      strCmdTxt = "UPDATE Cert_WeightWoolAnnlAge SET IDSheepGoat = """ & strIDShG & """" 'Insert
      .Execute strCmdTxt 'the sheep/goat's ID into the Cert_WeightWoolAnnlAge table next to the ages.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_SireOffspring SP.
Private Sub spSelectInto_CertRamHegoat_SireOffspring(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT Mate.IDSire, Mate.DateMatFrom, Offspring.IDLambKid, Offspring.WtBirth, WeightWean.WtWean, Weight7Mon.Wt7Mon INTO CertRamHegoat_SireOffspring FROM (((Mate LEFT JOIN LambKid ON (Mate.Cycle = LambKid.Cycle) AND (Mate.IDDam = LambKid.IDDam)) LEFT JOIN Offspring ON (LambKid.Cycle = Offspring.Cycle) AND (LambKid.IDDam = Offspring.IDDam)) LEFT JOIN Weight7Mon ON Offspring.IDLambKid = Weight7Mon.IDLambKid) LEFT JOIN WeightWean ON Offspring.IDLambKid = WeightWean.IDLambKid " & _
      "WHERE (Mate.IDSire = """ & strIDSire & """)"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_Mate SP.
Private Sub spSelectInto_CertRamHegoat_Mate(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT IDSire, YEAR(DateMatFrom) AS YearMat, COUNT(IDDam) AS CountIDDam  INTO CertRamHegoat_Mate FROM Mate GROUP BY IDSire, YEAR(DateMatFrom) " & _
      "HAVING (IDSire = """ & strIDSire & """)"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_BV_WtBirth SP.
Private Sub spSelectInto_CertRamHegoat_BV_WtBirth(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT DISTINCT SumGenEval_WtBirthSire.IDSire, SumGenEval_WtBirthSire.AvgWtBirth - SumGenEvalV_WtBirthFarm.AvgWtBirth AS BVWtBirth, SumGenEval_WtBirthSire.CountWtBirth INTO CertRamHegoat_BV_WtBirth FROM SumGenEval_WtBirthSire INNER JOIN SumGenEvalV_WtBirthFarm ON SumGenEval_WtBirthSire.IDFarm = SumGenEvalV_WtBirthFarm.IDFarm AND SumGenEval_WtBirthSire.BreedCross = SumGenEvalV_WtBirthFarm.BreedCross " & _
      "WHERE IDSire = """ & strIDSire & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_BV_WtWean SP.
Private Sub spSelectInto_CertRamHegoat_BV_WtWean(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT DISTINCT SumGenEval_WtWeanSire.IDSire, SumGenEval_WtWeanSire.AvgWtWean - SumGenEvalV_WtWeanFarm.AvgWtWean AS BVWtWean, SumGenEval_WtWeanSire.CountWtWean INTO CertRamHegoat_BV_WtWean FROM SumGenEval_WtWeanSire INNER JOIN SumGenEvalV_WtWeanFarm ON SumGenEval_WtWeanSire.IDFarm = SumGenEvalV_WtWeanFarm.IDFarm AND SumGenEval_WtWeanSire.BreedCross = SumGenEvalV_WtWeanFarm.BreedCross " & _
      "WHERE IDSire = """ & strIDSire & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_BV_Wt7Mon SP.
Private Sub spSelectInto_CertRamHegoat_BV_Wt7Mon(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT DISTINCT SumGenEval_Wt7MonSire.IDSire, SumGenEval_Wt7MonSire.AvgWt7Mon - SumGenEvalV_Wt7MonFarm.AvgWt7Mon AS BVWt7Mon, SumGenEval_Wt7MonSire.CountWt7Mon INTO CertRamHegoat_BV_Wt7Mon FROM SumGenEval_Wt7MonSire INNER JOIN SumGenEvalV_Wt7MonFarm ON SumGenEval_Wt7MonSire.IDFarm = SumGenEvalV_Wt7MonFarm.IDFarm AND SumGenEval_Wt7MonSire.BreedCross = SumGenEvalV_Wt7MonFarm.BreedCross " & _
      "WHERE IDSire = """ & strIDSire & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_BV_Weight SP.
Private Sub spSelectInto_CertRamHegoat_BV_Weight(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT DISTINCT SumGenEval_WeightSire.IDSire, SumGenEval_WeightSire.AvgWt1Yr - SumGenEvalV_WeightFarm.AvgWt1Yr AS BVWt1Yr, SumGenEval_WeightSire.CountWt1Yr INTO CertRamHegoat_BV_Weight FROM SumGenEvalV_WeightFarm INNER JOIN SumGenEval_WeightSire ON SumGenEvalV_WeightFarm.IDFarm = SumGenEval_WeightSire.IDFarm AND SumGenEvalV_WeightFarm.BreedCross = SumGenEval_WeightSire.BreedCross " & _
      "WHERE IDSire = """ & strIDSire & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_BV_Wool SP.
Private Sub spSelectInto_CertRamHegoat_BV_Wool(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT DISTINCT SumGenEval_WoolSire.IDSire, SumGenEval_WoolSire.AvgGrease1Yr - SumGenEvalV_WoolFarm.AvgGrease1Yr AS BVGrease1Yr, SumGenEval_WoolSire.CountGrease1Yr INTO CertRamHegoat_BV_Wool FROM SumGenEvalV_WoolFarm INNER JOIN SumGenEval_WoolSire ON SumGenEvalV_WoolFarm.IDFarm = SumGenEval_WoolSire.IDFarm AND SumGenEvalV_WoolFarm.BreedCross = SumGenEval_WoolSire.BreedCross " & _
      "WHERE IDSire = """ & strIDSire & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertRamHegoat_BV_Appr SP.
Private Sub spSelectInto_CertRamHegoat_BV_Appr(ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT DISTINCT SumGenEval_ApprSire.IDSire, SumGenEval_ApprSire.AvgLeng - SumGenEvalV_ApprFarm.AvgLeng AS BVLeng, SumGenEval_ApprSire.CountLeng, SumGenEval_ApprSire.AvgDiam - SumGenEvalV_ApprFarm.AvgDiam AS BVDiam, SumGenEval_ApprSire.CountDiam INTO CertRamHegoat_BV_Appr FROM SumGenEval_ApprSire INNER JOIN SumGenEvalV_ApprFarm ON SumGenEval_ApprSire.IDFarm = SumGenEvalV_ApprFarm.IDFarm AND SumGenEval_ApprSire.BreedCross = SumGenEvalV_ApprFarm.BreedCross " & _
      "WHERE IDSire = """ & strIDSire & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

