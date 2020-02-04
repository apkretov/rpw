VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblDefct"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblDefctTp
   IDDefct As Long
   Defct As String
   Remark As String
End Type

Dim mudtTblDefct As TblDefctTp
Dim mudtTblDefctOrig As TblDefctTp

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

' Get IDDefct.
Public Property Get IDDefct() As Long
Debug.Assert 0 = 1 'Verify
   IDDefct = mudtTblDefct.IDDefct
End Property

' Defect
Public Property Let Defct(ByVal strDefct As String)
    mudtTblDefct.Defct = strDefct
End Property

' Defect
Public Property Get Defct() As String
Debug.Assert 0 = 1 'Verify
    Defct = mudtTblDefct.Defct
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblDefct.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblDefct.Remark = "-", "", mudtTblDefct.Remark)
End Property

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Add a new defect to the Defects table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblDefct
      strCmdTxt = "INSERT INTO Defects (Defect, Remark) " & _
         "VALUES ('" & .Defct & "', '" & .Remark & "')"
   End With
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = True 'Mark full.
   Call frmMDI.RefrshSetng(False) 'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

'  related oblasts within the country.
' Delete the current record from the ShG table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM Defects WHERE IDDefect = " & mudtTblDefct.IDDefct
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   Call frmMDI.RefrshSetng(False) 'Refresh settings forms.
Exit Sub
ErrHnd: 'Message about a Foreign constraint violation error.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(162), LoadResString(372)
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function DatTbl_OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblDefctOrig
      If .Defct = mudtTblDefct.Defct Then
         If .Remark = mudtTblDefct.Remark Then DatTbl_OrigCompr = True 'Equal.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Save the original data after selecting.
Private Sub DatTbl_OrigSave()
On Error GoTo ErrHnd
   With mudtTblDefctOrig
      .IDDefct = mudtTblDefct.IDDefct
      .Defct = mudtTblDefct.Defct
      .Remark = mudtTblDefct.Remark
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the TblDefct object's data from the Defects table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstDefct As ADODB.Recordset
   Dim strDefct As String
   Dim strCmdTxt As String
   Set rstDefct = New ADODB.Recordset
   strDefct = vntKeys(0)
   strCmdTxt = "SELECT * FROM Defects WHERE Defect = '" & strDefct & "'"
'   strCmdTxt = "spSelect_Defects_Defct('" & strDefct & "')" 'Open the specified
   With rstDefct                                             'defect's recordset.
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF And .BOF Then 'Give feedback on if Defct found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(260) & " '" & strDefct & _
            LoadResString(194), vbExclamation, LoadResString(172) 'Message, unless cancel
      Else
         With .Fields 'Get the data from the recordset.
            mudtTblDefct.IDDefct = .Item("IDDefect")
            mudtTblDefct.Defct = .Item("Defect")
            mudtTblDefct.Remark = .Item("Remark")
         End With
         Call DatTbl_OrigSave 'Save original data.
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

' Update the Defects table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If Not DatTbl_OrigCompr Then
      With mudtTblDefct
         strCmdTxt = "UPDATE Defects SET Defect = '" & .Defct & "', Remark = '" & _
            .Remark & "' WHERE IDDefect = " & .IDDefct
      End With
      gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
      Call frmMDI.RefrshSetng(False)   'Refresh settings forms.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

