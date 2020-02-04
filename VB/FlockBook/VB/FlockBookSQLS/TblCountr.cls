VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblCountr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

'Public Event RefrshCountr() 'Refresh the Countries list in the host form.

Private Type TblCountrTp
   IDCountr As Long
   Countr As String
   Remark As String
End Type

Dim mudtTblCountr As TblCountrTp
Dim mudtTblCountrOrig As TblCountrTp

'Dim mblnCancCountrWrong As Boolean
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

' Get IDCountr.
Public Property Get IDCountr() As Long
Debug.Assert 0 = 1 'Verify As Long
   IDCountr = mudtTblCountr.IDCountr
End Property

' Country
Public Property Let Countr(ByVal strCountr As String)
    mudtTblCountr.Countr = strCountr
End Property

' Country
Public Property Get Countr() As String
    Countr = mudtTblCountr.Countr
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblCountr.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblCountr.Remark = "-", "", mudtTblCountr.Remark)
End Property

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Add a new sheep/goat to the ShG table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblCountr
      strCmdTxt = "spInsert_Countries('" & .Countr & "', '" & .Remark & "')"
   End With
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = True 'Mark full.
   Call Util.RefrshSetng(True) 'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Delete the current record from the ShG table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spDelete_Countries_IDCountr(" & mudtTblCountr.IDCountr & ")"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   Call Util.RefrshSetng(True)   'Refresh settings forms.
Exit Sub
ErrHnd: 'Message about a Foreign constraint violation error.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(150), LoadResString(372)
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

' Get the TblCountr object's data from SheepGoat.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstCountr As ADODB.Recordset
   Dim strCountr As String
   Dim strCmdTxt As String
   Set rstCountr = New ADODB.Recordset
   strCountr = vntKeys(0)
   strCmdTxt = "spSelect_Countries_Countr('" & strCountr & "')" 'Open the specified
   With rstCountr                                             'country's recordset.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .EOF And .BOF Then 'Give feedback on if Countr found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(190) & strCountr & _
            LoadResString(191), vbExclamation, LoadResString(172) 'Message, unless cancel
'         If Not mblnCancCountrWrong Then MsgBox LoadResString(190) & strCountr & _
            LoadResString(191), vbExclamation, LoadResString(172) 'Message, unless cancel
      Else
         With .Fields 'Get the data from the recordset.
            mudtTblCountr.IDCountr = .Item("IDCountry")
            mudtTblCountr.Countr = .Item("Country")
            mudtTblCountr.Remark = .Item("Remark")
         End With
         Call OrigSave 'Save original data.
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
   mblnEscSelFail = blnEscSelFail
End Property

' Update the form's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If Not OrigCompr Then
      With mudtTblCountr
         strCmdTxt = "spUpdate_Countries_IDCountr(" & .IDCountr & ", '" & .Countr & _
            "', '" & .Remark & "')"
      End With
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      Call Util.RefrshSetng(True)   'Refresh settings forms.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblCountrOrig
      If .Countr = mudtTblCountr.Countr Then
         If .Remark = mudtTblCountr.Remark Then OrigCompr = True 'Equal.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Save the original data after selecting.
Private Sub OrigSave()
On Error GoTo ErrHnd
   With mudtTblCountrOrig
      .IDCountr = mudtTblCountr.IDCountr
      .Countr = mudtTblCountr.Countr
      .Remark = mudtTblCountr.Remark
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
