VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Dam"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mobMats As Mats
Dim mobLmKs As LmKs

Dim mstrIDDam As String
Dim mblnVldFail As Boolean

'Public IDDam As String
Public PopltMat As Boolean 'Mark whether matings are populated.
Public PopltLmK As Boolean 'Mark whether lambings/kiddings are populated.

' Get IDDam.
Public Property Get IDDam() As String
   IDDam = mstrIDDam
End Property

' Let IDDam in this class & in its inbuilt ones.
Public Property Let IDDam(ByVal strIDDam As String)
On Error GoTo ErrHnd
   mstrIDDam = strIDDam
   mobMats.IDDam = strIDDam
   mobLmKs.IDDam = strIDDam
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Initialise new module level objects.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mobMats = New Mats
    Set mobLmKs = New LmKs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the Mats collection object into the Dam object.
Public Property Get Mats() As Mats
   Set Mats = mobMats
End Property

' Get the mobMats collection for the frmMat form.
' Validate the dam first, if required.
' Mark that the matings are populated.
Public Sub MatSel(ByVal blnDoValid As Boolean)
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim obDatTbl As DatTbl
   Dim obKeys As Keys
   Dim obKey As Key
   Dim blnValidDam As Boolean
   If blnDoValid Then 'Validate the dam.
      blnValidDam = VldDam 'Validate.
   Else
      blnValidDam = True 'Skip validation.
   End If
   If blnValidDam Then
      Set obTblMat = New TblMat
      Set obKeys = obTblMat.GetKeys(IDDam) 'Get the primary keys.
      If obKeys.Count = 0 Then 'Check how many matings there are in the collection.
         gobMsgInst.NoMatingSnd frmMDI.ActiveForm
      Else
         For Each obKey In obKeys
            Set obDatTbl = obTblMat
            With obKey
               obDatTbl.Sel .Key0, , .Key2
            End With
            With obTblMat
               mobMats.Add .Cycle, .CycleLmK, .DateMat, .IDSire
            End With
         Next obKey
         PopltMat = True 'Mark matings populated.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert a new record into the TblMat table.
Public Sub MatIns()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobMats.Act
    obDatTbl.Ins
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the active record in the TblMat table.
Public Sub MatUpd()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobMats.Act
    obDatTbl.Upd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the active record from the TblMat table.
Public Sub MatDel()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobMats.Act
    obDatTbl.Del
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the given animal for whether it is:
'   existent;
'   female;
'   not disposed;
'   exposed (frmLmK specific)
' Return True, if succeeds.
Private Function VldDam(Optional blnLmK As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   VldDam = True 'Set to True by default.
   Set obDatFrm = frmMDI.ActiveForm
   gobShGs(IDDam).SelShG True
   If Not gobShGs(IDDam).TblShG.Full Then
      VldDam = False 'The animal doesn't exist.
   ElseIf gobShGs(IDDam).TblShG.IDDispReas <> "" And obDatFrm.Mode = gobSetng.ModeAdd _
      Then
      VldDam = False 'Restirct addition for a disposed animal.
      MsgBox "∆ивотное '" & IDDam & "' выбыло из учЄта. ¬вод новых данных не " _
         & "возможен.", vbExclamation, LoadResString(131)
   ElseIf gobShGs(IDDam).TblShG.IDSex = gobSetng.IDSexMl Then
      VldDam = False 'The animal is a male.
      MsgBox "∆ивотное '" & IDDam & "' - самец. ¬вод случки или €гнени€/козлени€ не " & _
         "допустим.", vbExclamation, LoadResString(131)
   ElseIf blnLmK And obDatFrm.Mode = gobSetng.ModeAdd Then
      If Not PopltMat Then Call MatSel(False) 'Populate matings, unless done.
      If mobMats.Count = 0 Then
         VldDam = False 'No matings to lamb/kid.
         MsgBox "ќвцематка/козоматка '" & IDDam & "' не осеменена. ¬вод €гнени€/козлени€" _
            & " не возможен.", vbExclamation, LoadResString(131)
      End If
   End If
   mblnVldFail = Not VldDam 'Mark the validation failure, if so.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the mobLmKs collection for the frmLmK form.
' Validate the dam first, if required.
' Fill each TblLmk object in the mobLmKs collection with obTblOffsp objects.
' Mark lambings/kiddings populated.
Public Sub LmKSel(ByVal blnDoValid As Boolean)
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   Dim obDatTbl As DatTbl
   Dim obDatFrm As DatFrm
   Dim obKeys As Keys
   Dim obKey As Key
   Dim blnValidDam As Boolean
   If blnDoValid Then 'Validate the dam.
      blnValidDam = VldDam(True) 'Validate.
   Else
      blnValidDam = True 'Skip validation.
   End If
   If blnValidDam Then
      Set obTblLmK = New TblLmK
      Set obKeys = obTblLmK.GetKeys(IDDam) 'Get the primary keys values for the LambKid table to fill the mobLmKs collection.
      If obKeys.Count = 0 Then 'Check how many lambings/kiddings there are in the collection.
          gobMsgInst.NoLmKngSnd frmMDI.ActiveForm
      Else
         For Each obKey In obKeys
            Set obDatTbl = obTblLmK
            With obKey
               obDatTbl.Sel .Key0, , .Key2
            End With
            With obTblLmK
               mobLmKs.Add .Cycle, .CycleLmK, .DateLmKOrig, .DateLmK, .TypeBirth, _
                  .Abort 'Add obTblLmk to the collection.
               mobLmKs(.Cycle, False).OffspSel 'Fill obTblLmk with obTblOffsps.
            End With
         Next obKey
         PopltLmK = True 'Mark lambings/kiddings populated.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the active record from the TblLmk table.
Public Sub LmKDel()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobLmKs.Act
    obDatTbl.Del
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert a new record into the TblLmk table.
Public Sub LmKIns()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobLmKs.Act
    obDatTbl.Ins
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the active record in the TblLmk table.
Public Sub LmKUpd()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobLmKs.Act
    obDatTbl.Upd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open a new blank cycle to input data in it, if the the dam is inseminated & hasn't
'   yet lambed/kidded.
' Set the new cycle's number equal to the last mating' one.
' Increment the CycleLmK counter by one from the last lambing/kidding.
Public Sub LmKNewOpen()
On Error GoTo ErrHnd
   Dim intCycleLmKLast As Integer
   Dim intCycleNew As Integer
   Dim intCycleLmKNew As Integer
   If mobLmKs.Count > 0 Then 'Validate the last mating.
      intCycleLmKLast = mobLmKs.Last(False).Cycle
   Else
      intCycleLmKLast = 0
   End If
   If Not PopltMat Then Call MatSel(False) 'Populate matings.
   If mobMats.Last(False).Cycle > intCycleLmKLast Then
      intCycleNew = mobMats.Last(False).Cycle 'Define a new cycle.
      intCycleLmKNew = mobLmKs.CycleLmKNew 'New CycleLmK.
      mobLmKs.Add intCycleNew, intCycleLmKNew, 0, 0, 0, False 'Open the new
   Else                                                                'cycle.
      gobMsgInst.LmKedSnd frmMDI.ActiveForm 'Lamed/kidded after the last mating.
      MsgBox LoadResString(170) & IDDam & LoadResString(189), vbExclamation, _
         LoadResString(131)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the LmKs collection object into the Dam object.
Public Property Get LmKs() As LmKs
   Set LmKs = mobLmKs
End Property

' Get the validation failure mark.
Public Property Get VldFail() As Boolean
   VldFail = mblnVldFail
End Property

' Return True, if the dam has lamb/kidded after mating in the specified cycle.
Public Function LmKedAfterMat(ByVal intCycleMat As Integer) As Boolean
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   If Not PopltLmK Then Call LmKSel(False) 'Populate LmK's, unless populated.
   If mobLmKs.Count > 0 Then 'Ever lamb/kidded?
      For Each obTblLmK In mobLmKs 'Look for the matching lamb/kidding cycle.
         If obTblLmK.Cycle = intCycleMat Then
            LmKedAfterMat = True 'Lamb/kidded.
            Exit For 'Exit.
         End If
      Next
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
