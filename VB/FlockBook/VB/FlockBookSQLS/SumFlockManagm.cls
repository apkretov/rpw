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
   Dim strCmdTxt As String
   Dim strIDFarm As String
   Dim strDateBeg As String
   Dim strDateEnd As String
   strIDFarm = vntKeys(0)
   strDateBeg = Util.DateStrDB(vntKeys(1)) 'Convert dates to strings.
   strDateEnd = Util.DateStrDB(vntKeys(2))
   With gcnnConnServ
      .BeginTrans
      strCmdTxt = "spExec_SumFlockManagm_SelectInto('" & strIDFarm & "','" & strDateBeg _
         & "','" & strDateEnd & "')"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spExec_SumFlockManagm_Reprod"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spSelectInto_SumFlockManagm_BearDistr" 'Approved
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spExec_SumFlockManagm_PerfAge"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spSelectInto_SumFlockManagm_Disp" 'Approved
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spExec_SumFlockManagm_PerfSexAge('" & strIDFarm & "','" & strDateBeg _
         & "','" & strDateEnd & "')"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      .CommitTrans
   End With
   DatTblSel_Sel = True 'The operation succeeded
Exit Function
ErrHnd:
   MsgBox Err.Description
   gcnnConnServ.RollbackTrans 'Roll back the transaction & mark an error.
   DatTblSel_Sel = False
End Function

