VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrsLmK"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements TblBrs

Dim mrstBrsShG_LmK As ADODB.Recordset

' Populate the mrstBrsShG_LmK recordset filtered based on the frmBrsShG form's
'   filtering criteria.
Private Sub TblBrs_Sel(ByVal strIDFarm As String, ByVal lngDateDispMin As Long, ByVal _
   lngDateDispMax As Long, ByRef adoCtl As Adodc, ByVal strSortFld As String, ParamArray _
   vntFilt() As Variant)
On Error GoTo ErrHnd
   Const strIDSexDead As String = "-"
   Const strIDLiv0 As String = "0"
   Const strIDLiv1 As String = "1"
   Const strIDLiv2 As String = "2"
   Dim strAbortNo As String
   Dim strAbortYes As String
   Dim strIDSexOffspMl As String
   Dim strIDSexOffspFm As String
   Dim strIDLivAliv As String
   Dim strIDLivDead As String
   Dim strIDLivDead1 As String
   Dim strIDLivDead2 As String
   With gobSetng 'Define the filtering criteria.
      strAbortNo = CStr(IIf(vntFilt(0) = vbChecked, vbUnchecked, vbChecked)) 'Not aborted, i.e. lambed
      strAbortYes = CStr(IIf(vntFilt(1) = vbChecked, vbChecked, vbUnchecked)) 'Aaborted.
      strIDSexOffspMl = CStr(IIf(vntFilt(4) = vbChecked, .IDSexMl, .IDSexFm)) 'Male offsp.
      strIDSexOffspFm = CStr(IIf(vntFilt(5) = vbChecked, .IDSexFm, .IDSexMl)) 'Female offsp.
      strIDLivAliv = CStr(IIf(vntFilt(6) = vbChecked, vbUnchecked, vbChecked)) 'Alive offsprings.
      strIDLivDead = CStr(IIf(vntFilt(7) = vbChecked, vbChecked, vbUnchecked)) 'Dead offsprings.
   End With
   If strIDLivDead = strIDLiv0 Then 'Define the dead variables.
      strIDLivDead1 = strIDLiv0 'Nullify the dead codes.
      strIDLivDead2 = strIDLiv0
   Else 'Distinguish 2 different dead codes.
      strIDLivDead1 = strIDLiv1
      strIDLivDead2 = strIDLiv2
   End If
   Set mrstBrsShG_LmK = New ADODB.Recordset 'Populate.
   adoCtl.RecordSource = "SELECT SheepGoat.IDFarm, LambKid.IDDam, LambKid.Cycle, LambKid.DateLambKid, AbortYN.AbortYN, OffspringV.IDLambKid, OffspringV.Sex, OffspringV.WtBirth, OffspringV.Liv FROM AbortYN INNER JOIN ((SheepGoat INNER JOIN LambKid ON SheepGoat.IDSheepGoat = LambKid.IDDam) LEFT JOIN OffspringV ON (LambKid.Cycle = OffspringV.Cycle) AND (LambKid.IDDam = OffspringV.IDDam)) ON AbortYN.Abort = LambKid.Abort " & _
      "WHERE ( (SheepGoat.IDFarm = """ & strIDFarm & """) AND " & _
         "((LambKid.Abort = """ & strAbortNo & """) OR (LambKid.Abort = """ & strAbortYes & """)) AND " & _
         "(SheepGoat.DateDisp >= " & lngDateDispMin & ") AND " & _
         "(SheepGoat.DateDisp <= " & lngDateDispMax & ") AND " & _
         "((IIF(ISNULL(Offspring.IDSex),""" & strIDSexOffspMl & """, Offspring.IDSex) = """ & strIDSexOffspMl & """) OR " & _
         "(IIF(ISNULL(Offspring.IDSex), """ & strIDSexOffspFm & """, Offspring.IDSex) = """ & strIDSexOffspFm & """) OR " & _
         "(IIF(ISNULL(Offspring.IDSex), """ & strIDSexDead & """, Offspring.IDSex) = """ & strIDSexDead & """)) AND " & _
         "((IIF(ISNULL(Offspring.IDLiv), """ & strIDLivAliv & """, Offspring.IDLiv) = """ & strIDLivAliv & """) OR " & _
         "(IIF(ISNULL(Offspring.IDLiv), """ & strIDLivDead1 & """, Offspring.IDLiv) = """ & strIDLivDead1 & """) OR " & _
         "(IIF(ISNULL(Offspring.IDLiv), """ & strIDLivDead2 & """, Offspring.IDLiv) = """ & strIDLivDead2 & """)) ) " & _
      "ORDER BY " & strSortFld
   adoCtl.Refresh
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
