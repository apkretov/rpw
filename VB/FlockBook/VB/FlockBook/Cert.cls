VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Cert"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public IDShG As String

' Drop the creatable tables.
Public Sub DropTable()
On Error Resume Next
   With gdbDB
      .Execute "DROP TABLE Cert_SheepGoat"
      .Execute "DROP TABLE Cert_SheepGoatSire"
      .Execute "DROP TABLE Cert_SheepGoat"
      .Execute "DROP TABLE Cert_SheepGoatSire"
      .Execute "DROP TABLE Cert_SheepGoatDam"
      .Execute "DROP TABLE Cert_WeightWoolAnnl"
      .Execute "DROP TABLE Cert_PerfAge_YrAll"
      .Execute "DROP TABLE Cert_Appraisal"
      .Execute "DROP TABLE Cert_ApprAge_YrAll"
   End With
End Sub

' Execute the spSelectInto_Cert_SheepGoat SP.
Public Sub spSelectInto_Cert_SheepGoat()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT IDFarm, IDSheepGoat, IDSex, BreedCross, DateBirth, IDFarmBirth, TypeBirth, IDSire, IDDam INTO Cert_SheepGoat FROM SheepGoat " & _
      "WHERE IDSheepGoat = """ & IDShG & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spUpdate_Cert SP.
Public Sub spUpdate_Cert()
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
      strCmdTxt = "UPDATE Cert_WeightWoolAnnlAge SET IDSheepGoat = """ & IDShG & """" 'Insert
      .Execute strCmdTxt 'the sheep/goat's ID into the Cert_WeightWoolAnnlAge table next to the ages.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_WeightWoolAnnl SP.
Public Sub spSelectInto_Cert_WeightWoolAnnl()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT * INTO Cert_WeightWoolAnnl FROM WeightWoolAnnl " & _
      "WHERE IDSheepGoat = """ & IDShG & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_PerfAge_YrAllExec SP.
Public Sub spSelectInto_Cert_PerfAge_YrAllExec()
On Error GoTo ErrHnd
   Const intCount7 As Integer = 7
   Dim rstCert_WeightWoolAnnlCount As Recordset
   Dim strCmdTxt As String
   Dim intCount As Integer 'Below: Count records in the Cert_WeightWoolAnnl table.
   strCmdTxt = "SELECT COUNT(IDSheepGoat) AS CountIDSheepGoat FROM Cert_WeightWoolAnnl " _
      & "WHERE IDSheepGoat = '" & IDShG & "'"
   Set rstCert_WeightWoolAnnlCount = gdbDB.OpenRecordset(strCmdTxt)
   With rstCert_WeightWoolAnnlCount
      If .BOF = False And .EOF = False Then intCount = .Fields("CountIDSheepGoat")
   End With
   If intCount = 0 Then
      gdbDB.Execute "spSelectInto_Cert_PerfAge_YrAllEmpty" 'Create an empty table.
   Else
      Call spSelectInto_Cert_PerfAge_YrAllFull(intCount) 'Create a table with avaialable records
      If intCount < intCount7 Then Call spSelectInto_Cert_PerfAge_YrAllIns(IDShG, _
         intCount) 'Insert up to 7 records.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_PerfAge_YrAllFull SP.
Private Sub spSelectInto_Cert_PerfAge_YrAllFull(ByVal intCount As Integer)
On Error GoTo ErrHnd
   Const intCount7 As Integer = 7
   Dim rstCert_PerfAge_YrAll As Recordset
   Dim strCmdTxt As String
   Dim strIDShG As String
   Dim I As Integer
   Dim J As Integer
   strCmdTxt = "SELECT * INTO Cert_PerfAge_YrAll FROM Cert_WeightWoolAnnl"
   gdbDB.Execute strCmdTxt
   For I = 1 To intCount 'Loop as many as the number of records.
      For J = 1 To intCount7 'Loop to look for records to shift.'Below: Shift.
         strCmdTxt = "SELECT IDSheepGoat FROM Cert_PerfAge_YrAll WHERE Age = " & I
         Set rstCert_PerfAge_YrAll = gdbDB.OpenRecordset(strCmdTxt)
         With rstCert_PerfAge_YrAll
            If .BOF = False And .EOF = False Then
               Exit For 'Exit the loop.
            Else
               strCmdTxt = "UPDATE Cert_PerfAge_YrAll Set Age = Age - 1 WHERE Age > " & I
               gdbDB.Execute strCmdTxt
            End If
            .Close
         End With
         Set rstCert_PerfAge_YrAll = Nothing
      Next
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_PerfAge_YrAllIns SP.
Public Sub spSelectInto_Cert_PerfAge_YrAllIns(ByVal strIDShG As String, ByVal intCount _
   As Integer)
On Error GoTo ErrHnd
   Const intCount7 As Integer = 7
   Dim strCmdTxt As String
   Dim I As Integer
   For I = 1 To intCount7 - intCount 'Insert up to 7 records.
      strCmdTxt = "INSERT INTO Cert_PerfAge_YrAll (IDSheepGoat, Age) " & _
         "VALUES ('" & strIDShG & "', " & intCount + I & ")"
      gdbDB.Execute strCmdTxt
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_Appraisal SP.
Public Sub spSelectInto_Cert_Appraisal()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT * INTO Cert_Appraisal FROM Appraisal " & _
      "WHERE IDSheepGoat = """ & IDShG & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_ApprAge_YrAllExec SP.
Public Sub spSelectInto_Cert_ApprAge_YrAllExec()
On Error GoTo ErrHnd
   Const intCountMl As Integer = 5 'Count of records for a male.
   Const intCountFm As Integer = 2 'Count of records for a female.
   Dim strCmdTxt As String
   Dim rstCert_AppraisalCount As Recordset
   Dim rstCert_SheepGoat As Recordset
   Dim intCount As Integer
   Dim intCountSex As Integer
   Dim strIDSex As String
   strCmdTxt = "SELECT COUNT(IDSheepGoat) AS CountIDSheepGoat FROM Cert_Appraisal"
   Set rstCert_AppraisalCount = gdbDB.OpenRecordset(strCmdTxt)
   With rstCert_AppraisalCount 'Count records in the Cert_Appraisal table.
      If .BOF = False And .EOF = False Then intCount = .Fields("CountIDSheepGoat")
   End With
   If intCount = 0 Then
      gdbDB.Execute "spSelectInto_Cert_ApprAge_YrAllEmpty" 'Create an empty table.
   Else
      strCmdTxt = "SELECT IDSex FROM Cert_SheepGoat WHERE IDSheepGoat = '" & IDShG & _
         "'"
      Set rstCert_SheepGoat = gdbDB.OpenRecordset(strCmdTxt)
      With rstCert_SheepGoat
         If .BOF = False And .EOF = False Then strIDSex = .Fields("IDSex")
      End With
      Select Case strIDSex 'Define the sex record count (2 or 5).
      Case gobSetng.IDSexMl
          intCountSex = intCountMl 'Male.
      Case gobSetng.IDSexFm
          intCountSex = intCountFm 'Female.
      End Select
      Call spSelectInto_Cert_ApprAge_YrAllFull(intCount, intCountSex) 'Create with avaialable rec.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_Cert_ApprAge_YrAllFull SP.
Private Sub spSelectInto_Cert_ApprAge_YrAllFull(ByVal intCount As Integer, ByVal _
   intCountSex As Integer)
On Error GoTo ErrHnd
   Dim rstCert_ApprAge_YrAll As Recordset
   Dim strCmdTxt As String
   Dim strIDShG As String
   Dim I As Integer
   Dim J As Integer
   gdbDB.Execute "spSelectInto_Cert_ApprAge_YrAllEmpty" 'Create a table & update it below.
   For I = 1 To intCount 'Loop as many as the number of records.
      For J = 1 To intCountSex 'Loop to look for records to shift.
         strCmdTxt = "SELECT IDSheepGoat FROM Cert_ApprAge_YrAll WHERE Age = " & I
         Set rstCert_ApprAge_YrAll = gdbDB.OpenRecordset(strCmdTxt)
         With rstCert_ApprAge_YrAll
            If .BOF And .EOF Then 'Shift.
Debug.Assert 0 = 1 'Verify If
               strCmdTxt = "UPDATE Cert_ApprAge_YrAll SET Age = Age - 1 WHERE Age > " & I
               gdbDB.Execute strCmdTxt
            Else
               Exit For 'Exit the loop.
            End If
Debug.Assert 0 = 1 'Verify
            .Close 'Close & destroy to reopen it later.
         End With
         Set rstCert_ApprAge_YrAll = Nothing
      Next
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

