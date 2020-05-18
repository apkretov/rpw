VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblTwnVll"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblTwnVllTp
   IDTwnVll As Long
   IDRayn As Long
   TwnVll As String
   Remark As String
End Type

Dim mudtTblTwnVll As TblTwnVllTp
Dim mudtTblTwnVllOrig As TblTwnVllTp

Dim mblnEscSelFail As Boolean
Dim mblnFull As Boolean

Dim mobSQLErrHnd As SQLErrHnd

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get IDTwnVll.
Public Property Get IDTwnVll() As Long
Debug.Assert 0 = 1 ' Verify As Long
   IDTwnVll = mudtTblTwnVll.IDTwnVll
End Property

' Let IDRayn
Public Property Let IDRayn(ByVal lngIDRayn As Long)
   mudtTblTwnVll.IDRayn = lngIDRayn
End Property

' Get IDRayn.
Public Property Get IDRayn() As Long
   IDRayn = mudtTblTwnVll.IDRayn
End Property

' TwnVll
Public Property Let TwnVll(ByVal strRayn As String)
    mudtTblTwnVll.TwnVll = strRayn
End Property

' TwnVll
Public Property Get TwnVll() As String
    TwnVll = mudtTblTwnVll.TwnVll
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblTwnVll.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblTwnVll.Remark = "-", "", mudtTblTwnVll.Remark)
End Property

' Delete the current record from the TownVill table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spDelete_TownVill_IDTwnVll(" & mudtTblTwnVll.IDTwnVll & ")"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   Call Util.RefrshSetng(True) 'Refresh settings forms.
Exit Sub
ErrHnd: 'Foreign constraint violation message.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(153), LoadResString(372)
End Sub

' Add a new record to the TownVill table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblTwnVll
      strCmdTxt = "spInsert_TownVill(" & .IDRayn & ", '" & .TwnVll & "', '" & .Remark & _
         "')"
   End With
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = True 'Mark full.
   Call Util.RefrshSetng(True) 'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Get the TblCountr object's data from SheepGoat.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstTwnVll As ADODB.Recordset
   Dim strTwnVll As String
   Dim strCmdTxt As String
   Set rstTwnVll = New ADODB.Recordset
   strTwnVll = vntKeys(0)
   strCmdTxt = "spSelect_TownVill_TwnVll('" & strTwnVll & "')" 'Open the specified town/
   With rstTwnVll                                              'village's recordset.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .EOF And .BOF Then 'Give feedback on if TwnVll found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(195) & strTwnVll & _
            LoadResString(194), vbExclamation, LoadResString(172)  'Message, uless cancel
      Else
         With .Fields 'Get the data from the recordset.
            mudtTblTwnVll.IDTwnVll = .Item("IDTownVill")
            mudtTblTwnVll.IDRayn = .Item("IDRayon")
            mudtTblTwnVll.TwnVll = .Item("TownVill")
            mudtTblTwnVll.Remark = .Item("Remark")
         End With
         Call OrigSave 'Save original data.
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the form's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If Not OrigCompr Then 'Update, if changed.
      With mudtTblTwnVll
         strCmdTxt = "spUpdate_TownVill_IDTwnVll(" & .IDTwnVll & ", " & .IDRayn & ", '" _
            & .TwnVll & "', '" & .Remark & "')"
      End With
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      Call Util.RefrshSetng(True) 'Refresh settings forms.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblTwnVllOrig
      If .IDTwnVll = mudtTblTwnVll.IDTwnVll Then
         If .IDRayn = mudtTblTwnVll.IDRayn Then
            If .TwnVll = mudtTblTwnVll.TwnVll Then
               If .Remark = mudtTblTwnVll.Remark Then OrigCompr = True 'Equal.
            End If
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Save the original data after selecting.
Private Sub OrigSave()
On Error GoTo ErrHnd
   With mudtTblTwnVllOrig
      .IDTwnVll = mudtTblTwnVll.IDTwnVll
      .IDRayn = mudtTblTwnVll.IDRayn
      .TwnVll = mudtTblTwnVll.TwnVll
      .Remark = mudtTblTwnVll.Remark
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Cancel the Selection Failed message.
Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
   mblnEscSelFail = blnEscSelFail
End Property

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

