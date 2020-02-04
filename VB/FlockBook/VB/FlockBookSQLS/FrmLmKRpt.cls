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
   Dim strCmdTxt As String
   Dim lngLevel As Long
   Dim strIDFarm As String
   Dim strDate As String
   strIDFarm = vntKeys(0)
   strDate = Util.DateStrDB(vntKeys(1))
   With gcnnConnServ
      lngLevel = .BeginTrans 'Remember the transaction level to be rollbacked, if failes.
      strCmdTxt = "spSelectInto_RptFarm('" & strIDFarm & "')"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spSelectInto_FrmLmK_Mate('" & strIDFarm & "', '" & strDate & "')"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      strCmdTxt = "spSelectInto_FrmLmK_LambKid('" & strIDFarm & "', '" & strDate & "')"
      .Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      .CommitTrans
   End With
   DatTblSel_Sel = True 'Succeeded.
Exit Function
ErrHnd:
   MsgBox Err.Description
Debug.Assert 0 = 1 'Verify If
   If lngLevel <> 0 Then gcnnConnServ.RollbackTrans 'Rollback the transaction, if began.
   DatTblSel_Sel = False 'Failed.
End Function


