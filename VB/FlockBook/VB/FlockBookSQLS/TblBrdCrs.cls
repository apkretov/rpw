VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblBrdCrs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Dim mstrIDShG As String
Dim mstrIDBrdOrig As String
Dim mstrIDBrd As String
Dim mintBrdNum As Integer
Dim mintBrdDen As Integer

' Mark whether a dam's cross breed's share is matched to that of the mating sire.
Public Occupied As Boolean

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' IDShG.
Public Property Let IDShG(ByVal strIDShG As String)
    mstrIDShG = strIDShG
End Property

Public Property Get IDShG() As String
    IDShG = mstrIDShG
End Property

' Original IDBrd.
Public Property Get IDBrdOrig() As String
    IDBrdOrig = mstrIDBrdOrig
End Property

' IDBrd.
Public Property Let IDBrd(ByVal strIDBrd As String)
    mstrIDBrd = strIDBrd
End Property

' IDBrd.
Public Property Get IDBrd() As String
    IDBrd = mstrIDBrd
End Property

' BreedNum.
Public Property Let BrdNum(ByVal intBrdNum As Integer)
    mintBrdNum = intBrdNum
End Property

' BreedNum.
Public Property Get BrdNum() As Integer
    BrdNum = mintBrdNum
End Property

' BreedDen.
Public Property Let BrdDen(ByVal intBrdDen As Integer)
    mintBrdDen = intBrdDen
End Property

' BreedDen.
Public Property Get BrdDen() As Integer
    BrdDen = mintBrdDen
End Property

' Delete the current record from the BreedCross table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "spDelete_BreedCross_IDShGIDBreed('" & _
        mstrIDShG & "', '" & mstrIDBrd & "')"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

' Add a new sheep/goat to the ShG table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spInsert_BreedCross('" & mstrIDShG & "', '" & mstrIDBrd & "', '" & _
      mintBrdNum & "', '" & mintBrdDen & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

' Define the TblBrdCrs object's data from BreedCross.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
    Dim strIDShG As String
    Dim strIDBrd As String
    Dim rstBrdCrs As ADODB.Recordset
    Dim strCmdTxt As String
    Set rstBrdCrs = New ADODB.Recordset
    strIDShG = vntKeys(0)
    strIDBrd = vntKeys(1)
    ' Set the BreedCross recordset for the specified animal & its
    '   cross breed component.
    strCmdTxt = "spSelect_BreedCross_IDShGIDBreed('" & strIDShG & _
        "', '" & strIDBrd & "')"
    rstBrdCrs.Open strCmdTxt, gcnnConnServ, adOpenDynamic, _
        adLockOptimistic, adCmdStoredProc
    ' Define the data from the recordset.
    With rstBrdCrs.Fields
        mstrIDShG = .Item("IDSheepGoat")
        mstrIDBrdOrig = .Item("IDBreed")
        mstrIDBrd = .Item("IDBreed")
        mintBrdNum = .Item("BreedNum")
        mintBrdDen = .Item("BreedDen")
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Update the TblBrdCrs object's content to the BreedCross table.
' Find the updatable record in the table by its original breed code
'   stored as mstrIDBrdOrig.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "spUpdate_BreedCross_IDShGIDBreed('" & _
        mstrIDShG & "', '" & mstrIDBrdOrig & "', '" & _
        mstrIDBrd & "', " & mintBrdNum & ", " & _
        mintBrdDen & ")"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Compose the collection of the BreedCross table's primary key data.
Public Function GetKeys(ByVal strIDShG As String) As Keys
On Error GoTo ErrHnd
    Dim obKeys As Keys
    Dim rstBrdCrs As ADODB.Recordset
    Dim strCmdTxt As String
    Set obKeys = New Keys
    ' Open the record set with the specified sheep/goat's cross breeds.
    Set rstBrdCrs = New ADODB.Recordset
    strCmdTxt = "spSelect_BreedCross_IDShG('" & strIDShG & _
        "')"
    rstBrdCrs.Open strCmdTxt, gcnnConnServ, adOpenDynamic, _
            adLockOptimistic
    ' Compose the colleciton..
    With rstBrdCrs
        If .EOF = False And .BOF = False Then
            Do Until .EOF
                obKeys.Add .Fields.Item("IDSheepGoat"), .Fields.Item _
                    ("IDBreed")
                .MoveNext
            Loop
        End If
    End With
    Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

