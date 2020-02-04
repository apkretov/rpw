VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Public Event RefrshBrd() 'Refresh the list of breed ID's in the frmBrdStd.dbcIDBrd combob

Private Type TblBrdTp
   IDBrd As String
   Brd As String
   IDSpcs As String
   WtWt As Integer
   WtGrease As Integer
   WtLeng As Integer
   WtDiam As Integer
   WtFatTail As Integer
End Type
Dim mudtTblBrd As TblBrdTp
Dim mudtTblBrdOrig As TblBrdTp

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

' Delete the current record from the Breeds table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM Breeds WHERE IDBreed = '" & mudtTblBrd.IDBrd & "'"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   RaiseEvent RefrshBrd 'Refresh the list of breed ID's.
Exit Sub
ErrHnd: 'Foreign constraint violation message.
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(156) & LoadResString(157), _
      LoadResString(372)
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Add a new record to the Breeds table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   With mudtTblBrd
      strCmdTxt = "INSERT INTO Breeds (IDBreed, Breed, IDSpecies, WtWt, WtGrease, " & _
         "WtLeng, WtDiam, WtFatTail) " & _
         "VALUES ('" & .IDBrd & "', '" & .Brd & "', '" & .IDSpcs & "', " & .WtWt & ", " _
            & .WtGrease & ", " & .WtLeng & ", " & .WtDiam & ", " & .WtFatTail & ")"
   End With
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = True 'Mark full.
   RaiseEvent RefrshBrd 'Refresh the list of breed ID's.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function DatTbl_OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblBrdOrig
      If .IDBrd = mudtTblBrd.IDBrd Then
         If .Brd = mudtTblBrd.Brd Then
            If .IDSpcs = mudtTblBrd.IDSpcs Then
               If .WtWt = mudtTblBrd.WtWt Then
                  If .WtGrease = mudtTblBrd.WtGrease Then
                     If .WtLeng = mudtTblBrd.WtLeng Then
                        If .WtDiam = mudtTblBrd.WtDiam Then
                           If .WtFatTail = mudtTblBrd.WtFatTail Then DatTbl_OrigCompr = _
                              True 'Equal.
                        End If
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
Private Sub DatTbl_OrigSave()
On Error GoTo ErrHnd
   With mudtTblBrdOrig
      .IDBrd = mudtTblBrd.IDBrd
      .Brd = mudtTblBrd.Brd
      .IDSpcs = mudtTblBrd.IDSpcs
      .WtWt = mudtTblBrd.WtWt
      .WtGrease = mudtTblBrd.WtGrease
      .WtLeng = mudtTblBrd.WtLeng
      .WtDiam = mudtTblBrd.WtDiam
      .WtFatTail = mudtTblBrd.WtFatTail
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the TblBrd object's data from Breeds.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim strIDBrd As String
   Dim rstBrd As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstBrd = New ADODB.Recordset
   strIDBrd = vntKeys(0)
   strCmdTxt = "select * from Breeds where IDBreed = '" & strIDBrd & "'" 'Set the specified
   With rstBrd                                            'animal's the ShG recordset.
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF And .BOF Then 'Give feedback on if breed found.
         mblnFull = False 'Mark empty.
         If Not mblnEscSelFail Then MsgBox LoadResString(198) & strIDBrd & _
            LoadResString(191), vbExclamation, LoadResString(172)  'Message, uless cancel
      Else
         With .Fields 'Define the data from the recordset.
            mudtTblBrd.IDBrd = .Item("IDBreed")
            mudtTblBrd.Brd = .Item("Breed")
            mudtTblBrd.IDSpcs = .Item("IDSpecies")
            mudtTblBrd.WtWt = .Item("WtWt")
            mudtTblBrd.WtGrease = .Item("WtGrease")
            mudtTblBrd.WtLeng = .Item("WtLeng")
            mudtTblBrd.WtDiam = .Item("WtDiam")
            mudtTblBrd.WtFatTail = .Item("WtFatTail")
         End With
         Call DatTbl_OrigSave 'Save original data.
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cancel the Selection Failed message.
Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
   mblnEscSelFail = blnEscSelFail
End Property

' Update the form's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If Not DatTbl_OrigCompr Then 'Update, if changed.
      With mudtTblBrd
         strCmdTxt = "UPDATE Breeds SET IDBreed = '" & .IDBrd & "', Breed = '" & .Brd & _
            "', IDSpecies = '" & .IDSpcs & "', WtWt = " & .WtWt & ", WtGrease = " & _
            .WtGrease & ", WtLeng = " & .WtLeng & ", WtDiam = " & .WtDiam & _
            ", WtFatTail = " & .WtFatTail & _
            " WHERE IDBreed = '" & mudtTblBrdOrig.IDBrd & "'"
      End With
      gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
      RaiseEvent RefrshBrd 'Refresh the list of breed ID's.
   End If
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify LoadResString
   mobSQLErrHnd.KeyPrimForgn Err.Description, LoadResString(156) & LoadResString(158), _
      LoadResString(371)
'   Call Util.SQLErrHndPK(Err.Description)
End Sub

Public Property Get IDBrd() As String
   IDBrd = mudtTblBrd.IDBrd
End Property

Public Property Let IDBrd(ByVal strIDBrd As String)
   mudtTblBrd.IDBrd = strIDBrd
End Property

Public Property Get Brd() As String
   Brd = mudtTblBrd.Brd
End Property

Public Property Let Brd(ByVal strBrd As String)
   mudtTblBrd.Brd = strBrd
End Property

Public Property Get IDSpcs() As String
   IDSpcs = mudtTblBrd.IDSpcs
End Property

Public Property Let IDSpcs(ByVal strIDSpcs As String)
   mudtTblBrd.IDSpcs = strIDSpcs
End Property

Public Property Get WtWt() As Integer
   WtWt = mudtTblBrd.WtWt
End Property

Public Property Let WtWt(ByVal intWtWt As Integer)
   mudtTblBrd.WtWt = intWtWt
End Property

Public Property Get WtGrease() As Integer
   WtGrease = mudtTblBrd.WtGrease
End Property

Public Property Let WtGrease(ByVal intWtGrease As Integer)
   mudtTblBrd.WtGrease = intWtGrease
End Property

Public Property Get WtLeng() As Integer
   WtLeng = mudtTblBrd.WtLeng
End Property

Public Property Let WtLeng(ByVal intWtLeng As Integer)
   mudtTblBrd.WtLeng = intWtLeng
End Property

Public Property Get WtDiam() As Integer
   WtDiam = mudtTblBrd.WtDiam
End Property

Public Property Let WtDiam(ByVal intWtDiam As Integer)
   mudtTblBrd.WtDiam = intWtDiam
End Property

Public Property Get WtFatTail() As Integer
   WtFatTail = mudtTblBrd.WtFatTail
End Property

Public Property Let WtFatTail(ByVal intWtFatTail As Integer)
   mudtTblBrd.WtFatTail = intWtFatTail
End Property

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub
