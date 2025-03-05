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

' Query the data.
' Return True, if succeeds.
Private Function DatTblSel_Sel(ParamArray vntKeys() As Variant) As Boolean
On Error GoTo ErrHnd
   Dim obTblShG As TblShG
   Dim obDatTbl As DatTbl
   Dim strIDShG As String
   Dim strDate As String
   Dim strCmdTxt As String
   strIDShG = vntKeys(0)
   Set obTblShG = New TblShG 'Get the animal's farm ID.
   Set obDatTbl = obTblShG
   obDatTbl.Sel strIDShG
   strDate = Util.DateStrDB(Date)
   strCmdTxt = "spExec_CertRamHegoat('" & obTblShG.IDFarm & "', '" & strIDShG & "', '" _
      & strDate & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   DatTblSel_Sel = True 'The operation succeeded
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
