VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblFarm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblFarmTp
   IDFarm As String
   IDTwnVll As Long
   IDPersFarm As Long
   IDPersCont As Long
   Remark As String
End Type

Dim mudtTblFarm As TblFarmTp
Dim mudtTblFarmOrig As TblFarmTp

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

' Let IDFarm
Public Property Let IDFarm(ByVal strIDFarm As String)
    mudtTblFarm.IDFarm = IIf(strIDFarm = "", "-", strIDFarm)
End Property

' Get IDFarm.
Public Property Get IDFarm() As String
   IDFarm = mudtTblFarm.IDFarm
End Property

' Let IDTwnVll
Public Property Let IDTwnVll(ByVal lngIDTwnVll As Long)
   mudtTblFarm.IDTwnVll = lngIDTwnVll
End Property

' Get IDTwnVll.
Public Property Get IDTwnVll() As Long
   IDTwnVll = mudtTblFarm.IDTwnVll
End Property

' Let IDPersFarm
Public Property Let IDPersFarm(ByVal lngIDPersFarm As Long)
   mudtTblFarm.IDPersFarm = lngIDPersFarm
End Property

' Get IDPersFarm.
Public Property Get IDPersFarm() As Long
   IDPersFarm = mudtTblFarm.IDPersFarm
End Property

' Let IDPersCont
Public Property Let IDPersCont(ByVal lngIDPersCont As Long)
   mudtTblFarm.IDPersCont = lngIDPersCont
End Property

' Get IDPersCont.
Public Property Get IDPersCont() As Long
   IDPersCont = mudtTblFarm.IDPersCont
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblFarm.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblFarm.Remark = "-", "", mudtTblFarm.Remark)
End Property

' Delete the current record from the Oblasts table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM Farms WHERE IDFarm = '" & mudtTblFarm.IDFarm & "'"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   Call frmMDI.RefrshSetng(True)   'Refresh settings forms.
Exit Sub
ErrHnd: 'Foreign constraint violation message.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(155) & PromtKeyForgn, _
      LoadResString(372)
End Sub

' Add a new sheep/goat to the Oblasts table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblFarm
      strCmdTxt = "INSERT INTO Farms (IDFarm, IDTownVill, IDPersFarmer, IDPersCont, " & _
         "Remark) " & _
         "VALUES ('" & .IDFarm & "', " & .IDTwnVll & ", " & .IDPersFarm & ", " & _
            .IDPersCont & ", '" & .Remark & "')"
   End With
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = True 'Mark full.
   Call frmMDI.RefrshSetng(True)   'Refresh settings forms.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Get the TblCountr object's data from SheepGoat.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstFarm As ADODB.Recordset
   Dim strIDFarm As String
   Dim strCmdTxt As String
   Set rstFarm = New ADODB.Recordset
   strIDFarm = vntKeys(0)
   strCmdTxt = "SELECT * FROM Farms WHERE IDFarm = '" & strIDFarm & "'" 'Open the specified farm's
   With rstFarm                                             'recordset.
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF And .BOF Then 'Give feedback on if Farm found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(197) & strIDFarm & _
            LoadResString(183), vbExclamation, LoadResString(172)   'Message, uless cancel
      Else
         With .Fields 'Get the data from the recordset.
            mudtTblFarm.IDFarm = .Item("IDFarm")
            mudtTblFarm.IDTwnVll = .Item("IDTownVill")
            mudtTblFarm.IDPersFarm = .Item("IDPersFarmer")
            mudtTblFarm.IDPersCont = .Item("IDPersCont")
            mudtTblFarm.Remark = .Item("Remark")
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
      With mudtTblFarm
Debug.Assert 0 = 1 'Verify
         strCmdTxt = "UPDATE Farms SET IDFarm = '" & .IDFarm & "', IDTownVill = " & _
            .IDTwnVll & ", IDPersFarmer = " & .IDPersFarm & ", IDPersCont = " & _
            .IDPersCont & ", Remark = '" & .Remark & "' WHERE IDFarm = '" & _
            mudtTblFarmOrig.IDFarm & "'"
'         strCmdTxt = "spUpdate_Farms_IDFarm('" & mudtTblFarmOrig.IDFarm & "', '" & _
            .IDFarm & "', " & .IDTwnVll & ", " & .IDPersFarm & ", " & .IDPersCont & _
            ", '" & .Remark & "')"
      End With
      gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
      Call frmMDI.RefrshSetng(True)   'Refresh settings forms.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(161) & PromtKeyForgn, _
      LoadResString(371)
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblFarmOrig
      If .IDFarm = mudtTblFarm.IDFarm Then
         If .IDTwnVll = mudtTblFarm.IDTwnVll Then
            If .IDPersFarm = mudtTblFarm.IDPersFarm Then
               If .IDPersCont = mudtTblFarm.IDPersCont Then
                  If .Remark = mudtTblFarm.Remark Then OrigCompr = True 'Equal.
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
   With mudtTblFarmOrig
      .IDFarm = mudtTblFarm.IDFarm
      .IDTwnVll = mudtTblFarm.IDTwnVll
      .IDPersFarm = mudtTblFarm.IDPersFarm
      .IDPersCont = mudtTblFarm.IDPersCont
      .Remark = mudtTblFarm.Remark
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

' Return the Upd/Del promt affix about the foreign constraint violation.
Private Function PromtKeyForgn() As String
On Error GoTo ErrHnd
   PromtKeyForgn = vbCrLf & LoadResString(159) & vbCrLf & LoadResString(160)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

' Return True, if the farm exists.
Public Function Exists(ByVal strIDFarm As String) As Boolean
On Error GoTo ErrHnd
   Call DatTbl_Sel(strIDFarm) 'Select the farm from the DB.
   Exists = mblnFull 'Exists, if full.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function


