VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "FrmWtLmKRpt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTblSel

' Query data.
' Return True, if succeeds.
' Don't create an additional Exec SP just to encapsulate only 2 SP's in order to avoid
'  unnecessary object repletion in the DB.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Dim strIDFarm As String
   Dim strDate As String
   Call DropTable 'Drop tables.
   strIDFarm = vntKeys(0)
   strDate = Util.DateStrRpt(vntKeys(1))
   Set obUtilDB = New UtilDB
   obUtilDB.spSelectInto_RptFarm strIDFarm
   Call spSelectInto_FrmWtLmK(strIDFarm, strDate)
   DatTblSel_Sel = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Drop the creatable tables.
Private Sub DropTable()
On Error Resume Next
   With gdbDB
      .Execute "DROP TABLE RptFarm"
      .Execute "DROP TABLE FrmWtLmK"
   End With
End Sub

' Execute the spSelectInto_FrmWtLmK SP.
Private Sub spSelectInto_FrmWtLmK(ByVal strIDFarm As String, ByVal strDate _
   As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT SheepGoat.IDFarm, SexOffspring.Sex, Offspring.IDLambKid INTO FrmWtLmK FROM SheepGoat INNER JOIN (SexOffspring INNER JOIN Offspring ON SexOffspring.IDSex = Offspring.IDSex) ON SheepGoat.IDSheepGoat = Offspring.IDLambKid " & _
      "WHERE (Offspring.IDLambKid <> ""-"") AND " & _
         "(SheepGoat.IDDispReas = ""-"") AND " & _
         "(SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "(#" & strDate & "# >= SheepGoat.DateBirth) AND " & _
         "((#" & strDate & "# - SheepGoat.DateBirth) < " & gobTblCtrlParam.Age1YrWtMin _
            & ") " & _
      "ORDER BY SexOffspring.Sex, Offspring.IDLambKid"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

