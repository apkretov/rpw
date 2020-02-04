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

' Query the data.
' Return True, if succeeds, False, if failed.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    Dim strIDShG As String
    strIDShG = vntKeys(0)
    strCmdTxt = "spExec_CertEweShegoat('" & strIDShG & "')"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
    DatTblSel_Sel = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
