VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "FrmLmKRpt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTblSel

' Query data.
' Return True, if succeeds.
' Don't create an additional Exec SP just to encapsulate only 3 SP's in order to avoid
'  unnecessary object repletion in the DB.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Dim strIDFarm As String
   Dim strDate As String
   Dim dtmDate As Date
   Call DropTable 'Drop tables.
   strIDFarm = vntKeys(0)
   strDate = Util.DateStrRpt(vntKeys(1))
   dtmDate = vntKeys(1)
   Set obUtilDB = New UtilDB
   obUtilDB.spSelectInto_RptFarm strIDFarm
   Call spSelectInto_FrmLmK_Mate(strIDFarm, strDate, dtmDate)
   Call spSelectInto_FrmLmK_LambKid(strIDFarm, strDate)
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
      .Execute "DROP TABLE FrmLmK_Mate"
      .Execute "DROP TABLE FrmLmK_LambKid"
   End With
End Sub

' Execute the spSelectInto_FrmLmK_Mate SP.
Private Sub spSelectInto_FrmLmK_Mate(ByVal strIDFarm As String, ByVal strDate _
   As String, ByVal dtmDate As Date)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateMateBeg As String 'Below: The mating date to begin filtering from.
   strDateMateBeg = Util.DateStrRpt(dtmDate - gobTblCtrlParam.PregnLengMax)
   strCmdTxt = "SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.DateMatFrom, Mate.IDSire INTO FrmLmK_Mate FROM SheepGoat INNER JOIN Mate ON SheepGoat.IDSheepGoat = Mate.IDDam " & _
      "WHERE (((SheepGoat.IDFarm) = """ & strIDFarm & """) AND  " & _
         "((Mate.DateMatFrom) <= #" & strDate & "# AND " & _
         "(Mate.DateMatFrom) >= #" & strDateMateBeg & "#) AND " & _
         "((SheepGoat.IDDispReas) = ""-"")) " & _
      "ORDER BY Mate.IDDam, Mate.Cycle"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the spSelectInto_FrmLmK_LambKid SP.
Private Sub spSelectInto_FrmLmK_LambKid(ByVal strIDFarm As String, ByVal strDate _
   As String)
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "SELECT LambKid.IDDam, LambKid.Cycle INTO FrmLmK_LambKid FROM SheepGoat INNER JOIN LambKid ON SheepGoat.IDSheepGoat = LambKid.IDDam " & _
      "WHERE (((SheepGoat.IDFarm) = """ & strIDFarm & """) AND " & _
         "((SheepGoat.IDDispReas) = ""-"") AND " & _
         "((LambKid.DateLambKid) <= #" & strDate & "#))"
   gdbDB.Execute strCmdTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

