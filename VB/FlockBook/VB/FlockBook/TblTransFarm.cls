VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblTransFarm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mstrIDShG As String
Dim mdtmDateTrans As Date
Dim mstrIDFarm As String

Dim mobSQLErrHnd As SQLErrHnd

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

' DateTrans.
Public Property Let DateTrans(ByVal dtmDateTrans As Date)
    mdtmDateTrans = dtmDateTrans
End Property

Public Property Get DateTrans() As Date
    DateTrans = mdtmDateTrans
End Property

' IDFarm.
Public Property Let IDFarm(ByVal strIDFarm As String)
    mstrIDFarm = strIDFarm
End Property

Public Property Get IDFarm() As String
    IDFarm = mstrIDFarm
End Property

' Delete the current record from the BreedCross table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    Dim strDateTrans As String
    strDateTrans = Util.DateStrRpt(mdtmDateTrans) 'Convert the date to a string.
    strCmdTxt = "delete from TransFarm where IDSheepGoat = """ & mstrIDShG & """ and " & _
      "DateTrans = #" & strDateTrans & "#"
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
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
    Dim strDateTrans As String
    strDateTrans = Util.DateStrDB(mdtmDateTrans) 'Convert the date to a string.
    strCmdTxt = "INSERT INTO TransFarm(IDSheepGoat, DateTrans, IDFarm) " & _
      "VALUES ('" & mstrIDShG & "', '" & strDateTrans & "', '" & mstrIDFarm & "')"
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
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

' Define the TblTransFarm object's data from TransFarm.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim strIDShG As String
   Dim strDateTrans As String
   Dim rstTransFarm As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstTransFarm = New ADODB.Recordset
   strIDShG = vntKeys(0)
   strDateTrans = Util.DateStrRpt(vntKeys(4)) 'Convert the date to a string.
   strCmdTxt = "select * from TransFarm where IDSheepGoat = """ & strIDShG & """ and " _
     & "DateTrans = #" & strDateTrans & "#"
   rstTransFarm.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
   With rstTransFarm.Fields
       mstrIDShG = .Item("IDSheepGoat")
       mdtmDateTrans = .Item("DateTrans")
       mstrIDFarm = .Item("IDFarm")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Sub DatTbl_Upd()
' Empty
End Sub

' Compose the collection of the TransFarm table's primary keys.
Public Function GetKeys(ByVal strIDShG As String) As Keys
On Error GoTo ErrHnd
    Dim obKeys As Keys
    Dim rstTransFarm As ADODB.Recordset
    Dim strCmdTxt As String
    Set obKeys = New Keys
    Set rstTransFarm = New ADODB.Recordset
    strCmdTxt = "select * from TransFarm where IDSheepGoat = '" & strIDShG & "'"
    rstTransFarm.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic
    With rstTransFarm 'Compose the colleciton.
        If .EOF = False And .BOF = False Then
            Do Until .EOF
                obKeys.Add .Fields.Item("IDSheepGoat"), , , , .Fields.Item("DateTrans")
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

