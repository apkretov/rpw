VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblWtWool"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl
 
Dim mobSQLErrHnd As SQLErrHnd

'Dim mintAgeOrig As Integer
Dim mdtmDateAnnl As Date
Dim mdtmDateShearAnnl As Date

Public IDShG As String
Public AgeOrig As Integer
Public Age As Integer
Public WtAnnl As Single
Public GreaseAnnl As Single

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Let & get DateAnnl.
Public Property Let DateAnnl(ByVal dtmDateAnnl As Date)
    mdtmDateAnnl = dtmDateAnnl
End Property

Public Property Get DateAnnl() As Date
    DateAnnl = IIf(mdtmDateAnnl = gobSetng.SQLDateZero, 0, mdtmDateAnnl)
End Property

' Let & get DateShearAnnl.
Public Property Let DateShearAnnl(ByVal dtmDateShearAnnl As Date)
   mdtmDateShearAnnl = dtmDateShearAnnl
End Property

Public Property Get DateShearAnnl() As Date
   DateShearAnnl = IIf(mdtmDateShearAnnl = gobSetng.SQLDateZero, 0, mdtmDateShearAnnl)
End Property

' Delete the current record from the WeightWoolAnnl table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spDelete_WeightWoolAnnl_IDSheepGoatAge('" & IDShG & "', " & Age & ")"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new weighing to the WeightWoolAnnl table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateAnnl As String
   Dim strDateShearAnnl As String
   strDateAnnl = Util.DateStrDB(mdtmDateAnnl) 'Convert DateAnnl & DateShearAnnl.
   strDateShearAnnl = Util.DateStrDB(mdtmDateShearAnnl)
   strCmdTxt = "spInsert_WeightWoolAnnl('" & IDShG & "', " & Age & ", '" & _
      strDateAnnl & "', " & WtAnnl * gobSetng.Decm10 & ", '" & strDateShearAnnl & "', " _
      & GreaseAnnl * gobSetng.Decm10 & ")"
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

' Select data from the WeightWoolAnnl table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
    Dim rstWtWool As ADODB.Recordset
    Dim strCmdTxt As String
    Dim strIDShG As String
    Dim intAge As Integer
    Set rstWtWool = New ADODB.Recordset
    strIDShG = vntKeys(0)
    intAge = vntKeys(2)
    ' Set the specified animal's WtWool recordset.
    strCmdTxt = "spSelect_WeightWoolAnnl_IDSheepGoatAge('" & strIDShG & "', " & intAge _
        & ")"
    With rstWtWool
        .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
            adCmdStoredProc
        If .EOF And .BOF Then
            ' Give feedback on whether there is a weighing.
            gobMsgInst.NoWtWoolSnd frmMDI.ActiveForm
        Else
            ' Define the animal's data from the WtWool recordset.
            With .Fields
                IDShG = .Item("IDSheepGoat")
                AgeOrig = .Item("Age")
                Age = .Item("Age")
                mdtmDateAnnl = .Item("DateAnnl")
                WtAnnl = .Item("WtAnnl")
                mdtmDateShearAnnl = .Item("DateShearAnnl")
                GreaseAnnl = .Item("GreaseAnnl")
            End With
        End If
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the WeightWoolAnnl table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateAnnl As String
   Dim strDateShearAnnl As String
   strDateAnnl = Util.DateStrDB(mdtmDateAnnl) 'Convert DateAnnl & DateShearAnnl to strings.
   strDateShearAnnl = Util.DateStrDB(mdtmDateShearAnnl)
   strCmdTxt = "spUpdate_WeightWoolAnnl_IDSheepGoatAge('" & IDShG & "', " & _
      Age & ", '" & strDateAnnl & "', " & WtAnnl * gobSetng.Decm10 & ", '" & strDateShearAnnl & _
      "', " & GreaseAnnl * gobSetng.Decm10 & ")"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Compose the collection of the WeightWoolAnnl table's primary keys.
Public Function GetKeys(ByVal strIDShG As String) As Keys
On Error GoTo ErrHnd
   Dim obKeys As Keys
   Dim rstWtWool As ADODB.Recordset
   Dim strCmdTxt As String
   Set obKeys = New Keys
   Set rstWtWool = New ADODB.Recordset 'Open the record set with the specified sheep/
   strCmdTxt = "spSelect_WeightWoolAnnl_IDSheepGoat_Keys('" & strIDShG & "')" 'goat's
   rstWtWool.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic 'weighings/
   With rstWtWool 'Compose the colleciton.                                'shearings.
      If .EOF = False And .BOF = False Then
         Do Until .EOF
            obKeys.Add .Fields("IDSheepGoat"), , .Fields("Age")
            .MoveNext
         Loop
      End If
   End With
   Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

