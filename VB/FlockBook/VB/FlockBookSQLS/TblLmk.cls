VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblLmK"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Dim mobOffsps As Offsps

Dim mstrIDDam As String
Dim mintCycle As Integer
Dim mstrAbort As String

Public CycleLmK As Integer
Public DateLmKOrig As Date
Public DateLmK As Date
Public TypeBirth As Integer

' Get IDDam.
Public Property Get IDDam() As String
   IDDam = mstrIDDam
End Property

' Let IDDam in this class & in its inbuilt ones.
Public Property Let IDDam(ByVal strIDDam As String)
On Error GoTo ErrHnd
   mstrIDDam = strIDDam
   mobOffsps.IDDam = strIDDam
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get Cycle.
Public Property Get Cycle() As Integer
   Cycle = mintCycle
End Property

' Let Cycle in this class & in its inbuilt ones.
Public Property Let Cycle(ByVal intCycle As Integer)
On Error GoTo ErrHnd
   mintCycle = intCycle
   mobOffsps.Cycle = intCycle
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

'Public Abort As Integer
' Get & let Abort converted from Strig to Integer to bring about a minimal change in the
'  rest of the application after changing the Abort type from bit to char(1) in the DB.
Public Property Get Abort() As Integer
   Abort = CInt(mstrAbort)
End Property

Public Property Let Abort(ByVal intAbort As Integer)
   mstrAbort = CStr(intAbort)
End Property

' Initialise new module level objects.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mobOffsps = New Offsps
    Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the LambKid table.
' Prior to the deletion, delete the dependent offsprings from the
'   Offspring tablle.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    Call OffspDel
    strCmdTxt = "spDelete_LambKid_IDDamCycle('" & mstrIDDam & "', " & mintCycle & ")"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Insert the new lambinging/kidding to the LambKid table.
' First enroll the new offsprings, if any, into the flock book by inserting them into the
'  ShG &, if necessary, BreedCross tables; if succeeded, proceed inserting the them
'  into the Offspring tablle.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateLmK As String
   strDateLmK = Util.DateStrDB(DateLmK) 'Convert dates to strings.
   strCmdTxt = "spInsert_LambKid('" & mstrIDDam & "', " & mintCycle & ", " & CycleLmK & ", '" _
      & strDateLmK & "', " & TypeBirth & ", '" & mstrAbort & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords 'Insert the lambing/kidding.
   Call OffspIns 'Insert the offsprings, inless aborted.
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
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

' Select data from the LambKid table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstLmK As ADODB.Recordset
   Dim strCmdTxt As String
   Dim strIDDam As String
   Dim intCycle As Integer
   Set rstLmK = New ADODB.Recordset
   strIDDam = vntKeys(0)
   intCycle = vntKeys(2)
   strCmdTxt = "spSelect_LambKid_IDDamCycle('" & strIDDam & "', " & intCycle & ")" 'Set the specified animal's LambKid recordset.
   rstLmK.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
   With rstLmK.Fields 'Define the animal's data from the LambKid recordset.
      mstrIDDam = .Item("IDDam")
      mintCycle = .Item("Cycle")
      CycleLmK = .Item("CycleLambKid")
      DateLmKOrig = .Item("DateLambKid")
      DateLmK = .Item("DateLambKid")
      TypeBirth = .Item("TypeBirth")
      mstrAbort = .Item("Abort")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Update the form's content to the DB.
' Prior to updating, insert, update, or delete dependent offsprings in the Offspring
'  tablle.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateLmK As String
   Call OffspUpd 'Update offspringns.
   strDateLmK = Util.DateStrDB(DateLmK) 'Convert dates to strings.
   strCmdTxt = "spUpdate_LambKid_IDDamCycle('" & mstrIDDam & "', " & mintCycle & ", " & _
      CycleLmK & ", '" & strDateLmK & "', " & TypeBirth & ", '" & mstrAbort & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Compose the collection of the LambKid table's primary keys.
Public Function GetKeys(ByVal strIDDam As String) As Keys
On Error GoTo ErrHnd
    Dim obKeys As Keys
    Dim rstLmK As ADODB.Recordset
    Dim strCmdTxt As String
    Set obKeys = New Keys
    ' Open the record set with the specified dam's matings.
    Set rstLmK = New ADODB.Recordset
    strCmdTxt = "spSelect_LambKid_IDDam('" & strIDDam & "')"
    rstLmK.Open strCmdTxt, gcnnConnServ, adOpenDynamic, _
            adLockOptimistic
    ' Compose the colleciton.
    With rstLmK
        If .EOF = False And .BOF = False Then
            Do Until .EOF
                obKeys.Add .Fields.Item("IDDam"), , _
                    .Fields.Item("Cycle")
                .MoveNext
            Loop
        End If
    End With
    Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Build in & link to the Offsps collection object into the Dam
'   object.
Public Property Get Offsps() As Offsps
   Set Offsps = mobOffsps
End Property

' Insert all obTblOffsp objects from the mobOffsps collection into the Offspring table.
Public Sub OffspIns()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim obTblOffsp As TblOffsp
   If Abort = vbUnchecked Then 'Escape if aborted.
      For Each obTblOffsp In mobOffsps 'Insert each obTblOffsp.
         Set obDatTbl = obTblOffsp
         obDatTbl.Ins
      Next obTblOffsp
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert, update, or delete the dependent offsprings in the Offspring table.
' Update the TypeBirth counter if offsprings are inserted/deleted to update it both in
'  the LambKid & SheepGoat tables.
Private Sub OffspUpd()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim obTblOffsp As TblOffsp
   Dim blnInsDel As Boolean
   For Each obTblOffsp In mobOffsps 'Go through each obTblOffsp.
      Set obDatTbl = obTblOffsp
      If obTblOffsp.Added And Abort = vbUnchecked Then
         blnInsDel = True 'Mark insertion.
         obDatTbl.Ins 'Insert.
      ElseIf obTblOffsp.Edited And Abort = vbUnchecked Then
         obDatTbl.Upd 'Update.
      ElseIf obTblOffsp.Deld Or Abort = vbChecked Then
         blnInsDel = True 'Mark deletion.
         obDatTbl.Del 'Delete.
         With obTblOffsp ' Delete from the mobOffsps collection.
            mobOffsps.Del .NoLmK
         End With
      End If
   Next
   If blnInsDel Then Call UpdTypeBirth 'Update TypeBirth's.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' This (other similar procedures, too) is unnecessary because the relational cascade
'  deletion automaically deletes all dependent records from the Offspring table.
'  Nevetherless keep the procedure.
' Delete all obTblOffsp objects from the mobOffsps collection.
Public Sub OffspDel()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Dim obTblOffsp As TblOffsp
    ' Delete each obTblOffsp.
    For Each obTblOffsp In mobOffsps
        Set obDatTbl = obTblOffsp
        obDatTbl.Del
    Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mobOffsps collection for the frmOffspring form.
' Validate the dam first.
Public Sub OffspSel()
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim obDatTbl As DatTbl
   Dim obKeys As Keys
   Dim obKey As Key
   Set obTblOffsp = New TblOffsp
   Set obKeys = obTblOffsp.GetKeys(mstrIDDam, mintCycle) 'Get the primary keys values for the
   For Each obKey In obKeys        'Offspring table to fill the mobOffsps collection.
      Set obDatTbl = obTblOffsp
      With obKey
         obDatTbl.Sel .Key0, , .Key2, .Key3
      End With
      With obTblOffsp
         mobOffsps.Add .NoLmK, .NoLmK, .IDLmK, .IDSex, .Sex, .WtBirth, .IDLiv, .Liv
      End With
   Next obKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Recount the TypeBirth counter.
' Update the TypeBirth variable of offsprings born within the current lambing/kidding, if an
'  offspring is inserted/deleted. Update it in both the LambKid & SheepGoat tables.
Private Sub UpdTypeBirth()
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim obShG As ShG
   Dim obDatTbl As DatTbl
   If TypeBirth <> mobOffsps.Count Then TypeBirth = mobOffsps.Count 'Recount TypeBirth.
   For Each obTblOffsp In mobOffsps 'Go through each obTblOffsp.
      If obTblOffsp.IDLiv = gobSetng.Liv.IDLivAlive Then 'Proceed for alive only.
         Set obShG = New ShG
         With obShG
            .IDShG = obTblOffsp.IDLmK
            .TblShG.EscIDShGWrng = True 'Cancel the IDShGWrong message.
            .SelShG 'Populate.
            If .TblShG.TypeBirth <> TypeBirth Then 'Update the SheepGoat table.
               .TblShG.TypeBirth = TypeBirth
               Set obDatTbl = .TblShG
               obDatTbl.Upd
            End If
         End With
         Set obShG = Nothing 'Reset for later use.
      End If
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub


Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

