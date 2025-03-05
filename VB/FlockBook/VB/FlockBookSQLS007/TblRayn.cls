VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblRayn"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblRaynTp
   IDRayn As Long
   IDObl As Long
   Rayn As String
   Remark As String
End Type

Dim mudtTblRayn As TblRaynTp
Dim mudtTblRaynOrig As TblRaynTp

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

' Get IDRayn.
Public Property Get IDRayn() As Long
Debug.Assert 0 = 1 ' Verify As Long
   IDRayn = mudtTblRayn.IDRayn
End Property

' Let IDObl
Public Property Let IDObl(ByVal lngIDObl As Long)
   mudtTblRayn.IDObl = lngIDObl
End Property

' Get IDObl.
Public Property Get IDObl() As Long
   IDObl = mudtTblRayn.IDObl
End Property

' Rayn
Public Property Let Rayn(ByVal strRayn As String)
    mudtTblRayn.Rayn = strRayn
End Property

' Rayn
Public Property Get Rayn() As String
    Rayn = mudtTblRayn.Rayn
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblRayn.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblRayn.Remark = "-", "", mudtTblRayn.Remark)
End Property

' Delete the current record from the Oblasts table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spDelete_Rayons_IDRayn(" & mudtTblRayn.IDRayn & ")"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = False 'Mark empty.
      Call Util.RefrshSetng(True) 'Refresh settings forms.
Exit Sub
ErrHnd: 'Message about a Foreign constraint violation error.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(152), LoadResString(372)
End Sub

' Add a new sheep/goat to the Oblasts table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblRayn
      strCmdTxt = "spInsert_Rayons(" & .IDObl & ", '" & .Rayn & "', '" & .Remark & "')"
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
   Dim rstRayn As ADODB.Recordset
   Dim strRayn As String
   Dim strCmdTxt As String
   Set rstRayn = New ADODB.Recordset
   strRayn = vntKeys(0)
   strCmdTxt = "spSelect_Rayons_Rayn('" & strRayn & "')" 'Open the specified rayon's
   With rstRayn                                               'recordset.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .EOF And .BOF Then 'Give feedback on if Rayn found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(193) & strRayn & _
            LoadResString(194), vbExclamation, LoadResString(172) 'Message, unless cancel
      Else
         With .Fields 'Get the data from the recordset.
            mudtTblRayn.IDRayn = .Item("IDRayon")
            mudtTblRayn.IDObl = .Item("IDOblast")
            mudtTblRayn.Rayn = .Item("Rayon")
            mudtTblRayn.Remark = .Item("Remark")
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
      With mudtTblRayn
         strCmdTxt = "spUpdate_Rayons_IDRayn(" & .IDRayn & ", " & .IDObl & ", '" & _
            .Rayn & "', '" & .Remark & "')"
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
   With mudtTblRaynOrig
      If .IDRayn = mudtTblRayn.IDRayn Then
         If .IDObl = mudtTblRayn.IDObl Then
            If .Rayn = mudtTblRayn.Rayn Then
               If .Remark = mudtTblRayn.Remark Then OrigCompr = True 'Equal.
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
   With mudtTblRaynOrig
      .IDRayn = mudtTblRayn.IDRayn
      .IDObl = mudtTblRayn.IDObl
      .Rayn = mudtTblRayn.Rayn
      .Remark = mudtTblRayn.Remark
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

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

