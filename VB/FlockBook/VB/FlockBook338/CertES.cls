VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CertES"
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
' Return True, if succeeds, False, if failed.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim strIDShG As String
   Call DropTable 'Drop tables.
   strIDShG = vntKeys(0)
   DatTblSel_Sel = spExec_CertEweShegoat(strIDShG)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Drop the creatable tables.
Private Sub DropTable()
On Error Resume Next
   mobCert.DropTable 'Drop sex-irrelevant certificate tables.
   With gdbDB
      .Execute "DROP TABLE CertEweShegoat_LambKid"
      .Execute "DROP TABLE CertEweShegoat_Offspring"
   End With
End Sub

' Execute the spExec_CertEweShegoat SP.
' Return True, if succeeds.
Private Function spExec_CertEweShegoat(ByVal strIDShG) As Boolean
On Error GoTo ErrHnd
   With mobCert
      .IDShG = strIDShG
      .spSelectInto_Cert_SheepGoat
      gdbDB.Execute "spSelectInto_Cert_SheepGoatSire"
      gdbDB.Execute "spSelectInto_Cert_SheepGoatDam"
      .spUpdate_Cert
      Call spSelectInto_CertEweShegoat_LambKid(strIDShG)
      Call spSelectInto_CertEweShegoat_Offspring(strIDShG)
      .spSelectInto_Cert_WeightWoolAnnl
      .spSelectInto_Cert_PerfAge_YrAllExec
      .spSelectInto_Cert_Appraisal
      .spSelectInto_Cert_ApprAge_YrAllExec
   End With
   spExec_CertEweShegoat = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Execute the spSelectInto_CertEweShegoat_LambKid SP.
Private Sub spSelectInto_CertEweShegoat_LambKid(ByVal strIDDam As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT IDDam, Cycle, CycleLambKid, DateLambKid  INTO CertEweShegoat_LambKid FROM LambKid " & _
      "WHERE IDDam = """ & strIDDam & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_CertEweShegoat_Offspring SP.
Private Sub spSelectInto_CertEweShegoat_Offspring(ByVal strIDDam As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT * INTO CertEweShegoat_Offspring FROM Offspring " & _
      "WHERE IDDam = """ & strIDDam & """"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

