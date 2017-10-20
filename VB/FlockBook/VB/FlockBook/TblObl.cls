VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblObl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblOblTp
   IDObl As Long
   IDCountr As Long
   Obl As String
   Remark As String
End Type

Dim mudtTblObl As TblOblTp
Dim mudtTblOblOrig As TblOblTp

'Dim mblnCancOblWrong As Boolean
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

' Get IDObl.
Public Property Get IDObl() As Long
Debug.Assert 0 = 1 ' Verify As Long
   IDObl = mudtTblObl.IDObl
End Property

' Let IDCountr
Public Property Let IDCountr(ByVal lngIDCountr As Long)
   mudtTblObl.IDCountr = lngIDCountr
End Property

' Get IDCountr.
Public Property Get IDCountr() As Long
   IDCountr = mudtTblObl.IDCountr
End Property

' Obl
Public Property Let Obl(ByVal strObl As String)
    mudtTblObl.Obl = strObl
End Property

' Obl
Public Property Get Obl() As String
    Obl = mudtTblObl.Obl
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblObl.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblObl.Remark = "-", "", mudtTblObl.Remark)
End Property

' Delete the current record from the Oblasts table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM Oblasts WHERE IDOblast = " & mudtTblObl.IDObl
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
      Call frmMDI.RefrshSetng(True) 'Refresh settings forms.
Exit Sub
ErrHnd: 'Message about a Foreign constraint violation error.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(151), LoadResString(372)
End Sub

' Add a new sheep/goat to the Oblasts table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblObl
      strCmdTxt = "INSERT INTO Oblasts (IDCountry, Oblast, Remark) " & _
         "VALUES (" & .IDCountr & ", '" & .Obl & "', '" & .Remark & "')"
   End With
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = True 'Mark full.
      Call frmMDI.RefrshSetng(True) 'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Get the TblCountr object's data from SheepGoat.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstObl As ADODB.Recordset
   Dim strObl As String
   Dim strCmdTxt As String
   Set rstObl = New ADODB.Recordset
   strObl = vntKeys(0)
   strCmdTxt = "SELECT * FROM Oblasts WHERE Oblast = '" & strObl & "'"
   With rstObl                                               'recordset.
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF And .BOF Then 'Give feedback on if Obl found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(192) & strObl & _
            LoadResString(191), vbExclamation, LoadResString(172) 'Message, unless cancel
      Else
         With .Fields 'Get the data from the recordset.
            mudtTblObl.IDObl = .Item("IDOblast")
            mudtTblObl.IDCountr = .Item("IDCountry")
            mudtTblObl.Obl = .Item("Oblast")
            mudtTblObl.Remark = .Item("Remark")
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
      With mudtTblObl
Debug.Assert 0 = 1 'Verify
         strCmdTxt = "UPDATE Oblasts SET IDCountry = " & .IDCountr & ", Oblast = '" & _
            .Obl & "', Remark = '" & .Remark & "' WHERE IDOblast = " & .IDObl
'         strCmdTxt = "spUpdate_Oblasts_IDObl(" & .IDObl & ", " & .IDCountr & ", '" & _
            .Obl & "', '" & .Remark & "')"
      End With
      gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Debug.Assert 0 = 1 'Verify
      Call frmMDI.RefrshSetng(True) 'Refresh settings forms.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblOblOrig
      If .IDObl = mudtTblObl.IDObl Then
         If .IDCountr = mudtTblObl.IDCountr Then
            If .Obl = mudtTblObl.Obl Then
               If .Remark = mudtTblObl.Remark Then OrigCompr = True 'Equal.
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
   With mudtTblOblOrig
      .IDObl = mudtTblObl.IDObl
      .IDCountr = mudtTblObl.IDCountr
      .Obl = mudtTblObl.Obl
      .Remark = mudtTblObl.Remark
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

