VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblPers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblPersTp
   IDPers As Long
   Nam As String
   IDTwnVll As Long
   Address As String
   Phone As String
   Email As String
   Remark As String
End Type

Dim mudtTblPers As TblPersTp
Dim mudtTblPersOrig As TblPersTp

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

' Get IDPers.
Public Property Get IDPers() As String
   IDPers = mudtTblPers.IDPers
End Property

' Nam
Public Property Let Nam(ByVal strNam As String)
    mudtTblPers.Nam = IIf(strNam = "", "-", strNam)
End Property

' Nam
Public Property Get Nam() As String
    Nam = IIf(mudtTblPers.Nam = "-", "", mudtTblPers.Nam)
End Property

'' NamFirst
'Public Property Let NamFirst(ByVal strNamFirst As String)
'    mudtTblPers.NamFirst = IIf(strNamFirst = "", "-", strNamFirst)
'End Property

'' NamFirst
'Public Property Get NamFirst() As String
'    NamFirst = IIf(mudtTblPers.NamFirst = "-", "", mudtTblPers.NamFirst)
'End Property

'' NamPatr
'Public Property Let NamPatr(ByVal strNamPatr As String)
'    mudtTblPers.NamPatr = IIf(strNamPatr = "", "-", strNamPatr)
'End Property

'' NamPatr
'Public Property Get NamPatr() As String
'    NamPatr = IIf(mudtTblPers.NamPatr = "-", "", mudtTblPers.NamPatr)
'End Property

' Let IDTwnVll
Public Property Let IDTwnVll(ByVal lngIDTwnVll As Long)
   mudtTblPers.IDTwnVll = lngIDTwnVll
End Property

' Get IDTwnVll.
Public Property Get IDTwnVll() As Long
   IDTwnVll = mudtTblPers.IDTwnVll
End Property

' Address
Public Property Let Address(ByVal strAddress As String)
    mudtTblPers.Address = IIf(strAddress = "", "-", strAddress)
End Property

' Address
Public Property Get Address() As String
    Address = IIf(mudtTblPers.Address = "-", "", mudtTblPers.Address)
End Property

' Phone
Public Property Let Phone(ByVal strPhone As String)
   mudtTblPers.Phone = IIf(strPhone = "", "-", strPhone)
End Property

' Phone
Public Property Get Phone() As String
   Phone = IIf(mudtTblPers.Phone = "-", "", mudtTblPers.Phone)
End Property

' Email
Public Property Let Email(ByVal strEmail As String)
   mudtTblPers.Email = IIf(strEmail = "", "-", strEmail)
End Property

' Email
Public Property Get Email() As String
    Email = IIf(mudtTblPers.Email = "-", "", mudtTblPers.Email)
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblPers.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblPers.Remark = "-", "", mudtTblPers.Remark)
End Property

' Delete the current record from the Oblasts table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spDelete_Persons_IDPers(" & mudtTblPers.IDPers & ")"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
Exit Sub
ErrHnd: 'Message about a Foreign constraint violation error.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(154), LoadResString(372)
End Sub

' Add a new sheep/goat to the Oblasts table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblPers
      strCmdTxt = "spInsert_Persons('" & .Nam & "', " & .IDTwnVll & ", '" & .Address & _
         "', '" & .Phone & "', '" & .Email & "', '" & .Remark & "')"
   End With
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = True 'Mark full.
Debug.Assert 0 = 1 'Verify
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Get the TblCountr object's data from SheepGoat.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstPers As ADODB.Recordset
   Dim strNam As String
   Dim strCmdTxt As String
   Set rstPers = New ADODB.Recordset
   strNam = vntKeys(0)
   strCmdTxt = "spSelect_Persons_Nam('" & strNam & "')" 'Open the specified person's rst.
   With rstPers
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .EOF And .BOF Then 'Give feedback on if TwnVll found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then
            MsgBox strNam & LoadResString(196), vbExclamation, LoadResString(172)
         End If
      Else 'Above 'Message, uless canceled.
         With .Fields 'Get the data from the recordset.
            mudtTblPers.IDPers = .Item("IDPers")
            mudtTblPers.Nam = .Item("Nam")
            mudtTblPers.IDTwnVll = .Item("IDTownVill")
            mudtTblPers.Address = .Item("Address")
            mudtTblPers.Phone = .Item("Phone")
            mudtTblPers.Email = .Item("Email")
            mudtTblPers.Remark = .Item("Remark")
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
      With mudtTblPers
         strCmdTxt = "spUpdate_Persons_IDPers(" & .IDPers & ", '" & .Nam & "', " & _
            .IDTwnVll & ", '" & .Address & "', '" & .Phone & "', '" & .Email & "', '" & _
            .Remark & "')"
      End With
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblPersOrig
      If .IDPers = mudtTblPers.IDPers Then
         If .Nam = mudtTblPers.Nam Then
            If .IDTwnVll = mudtTblPers.IDTwnVll Then
               If .Address = mudtTblPers.Address Then
                  If .Phone = mudtTblPers.Phone Then
                     If .Email = mudtTblPers.Email Then
                        If .Remark = mudtTblPers.Remark Then OrigCompr = True 'Equl
                     End If
                  End If
               End If
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
   With mudtTblPersOrig
      .IDPers = mudtTblPers.IDPers
      .Nam = mudtTblPers.Nam
      .IDTwnVll = mudtTblPers.IDTwnVll
      .Address = mudtTblPers.Address
      .Phone = mudtTblPers.Phone
      .Email = mudtTblPers.Email
      .Remark = mudtTblPers.Remark
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

' Return a space vs. zero-length string to be put between the last & first names, first &
'  patrtynomic ones based on if the 1st part in either pair is full/blank.
Private Function NamSpace(ByVal strNam As String) As String
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify
   NamSpace = IIf(strNam <> "", Space$(1), "")
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

