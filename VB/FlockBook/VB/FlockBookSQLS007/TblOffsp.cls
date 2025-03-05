VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblOffsp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

'Private WithEvents mfrmBrdCrs As frmBrdCrs
'Dim mblnBrdCrsDefnd As Boolean

Private Type PedigrBasCrs
   IDBrdBasSire As String
   CrsSire As Boolean
   IDBrdBasDam As String
   CrsDam As Boolean
End Type

Dim mobShGOffsp As ShG
Dim mobShGOffspTest As ShG
Dim mobShGSire As ShG

Dim mobSQLErrHnd As SQLErrHnd

Dim mstrIDLmK As String
Dim mstrIDSex As String
Dim mstrSex As String

Dim mblnAdded As Boolean
Dim mblnEdited As Boolean
Dim mblnDeld As Boolean

Public IDDam As String
Public Cycle As Integer
Public NoLmKOrig As Integer
Public NoLmK As Integer
Public WtBirth As Single
Public IDLiv As String
Public Liv As String

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Let & get IDLmK.
Public Property Let IDLmK(ByVal strIDLmK As String)
    mstrIDLmK = IIf(strIDLmK = "", "-     ", strIDLmK)
End Property

Public Property Get IDLmK() As String
    IDLmK = IIf(mstrIDLmK = "-     ", "", mstrIDLmK)
End Property

' Let & get IDSex.
Public Property Let IDSex(ByVal strIDSex As String)
    mstrIDSex = IIf(strIDSex = "", "-", strIDSex)
End Property

Public Property Get IDSex() As String
    IDSex = IIf(mstrIDSex = "-", "", mstrIDSex)
End Property

' Let & get Sex.
Public Property Let Sex(ByVal strSex As String)
    mstrSex = IIf(strSex = "", "-", strSex)
End Property

Public Property Get Sex() As String
    Sex = IIf(mstrSex = "-", "", mstrSex)
End Property

' Delete the current record from the Offspring table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "spDelete_Offspring_IDDamCycleNoLK('" & IDDam & "', " & Cycle & ", " & _
      NoLmK & ")"
    gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

' Add a new offspring to the Offspring table.
' First enroll the new offspring into the flock book.
' If succeeded, proceed inserting into the Offspring table. Otherwise rollback the
'  transaction in the frmLmK\DatFrm_FrmToDB procedure.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If Not Enroll Then
      gobMsgInst.SQLErrSnd frmMDI.ActiveForm 'Rollaback.
   Else
      strCmdTxt = "spInsert_Offspring('" & IDDam & "', " & Cycle & ", " & NoLmK & ", '" _
      & mstrIDLmK & "', '" & mstrIDSex & "', " & WtBirth * gobSetng.Decm10 & ", '" & IDLiv & "')"       'Enrollment succeeded.
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   End If
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

' Select data from the Offspring table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstOffsp As ADODB.Recordset
   Dim strCmdTxt As String
   Dim strIDDam As String
   Dim intCycle As Integer
   Dim intNoLmK  As Integer
   Set rstOffsp = New ADODB.Recordset
   strIDDam = vntKeys(0)
   intCycle = vntKeys(2)
   intNoLmK = vntKeys(3)
   strCmdTxt = "spSelect_OffspringV_IDDamCycleNoLK('" & strIDDam & "', " & intCycle & _
      ", " & intNoLmK & ")" 'Set the specified animal's Offspring recordset.
   rstOffsp.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
   With rstOffsp.Fields 'Define the animal's data from the Offspring recordset.
      IDDam = .Item("IDDam")
      Cycle = .Item("Cycle")
      NoLmKOrig = .Item("NoLambKid")
      NoLmK = .Item("NoLambKid")
      mstrIDLmK = .Item("IDLambKid")
      mstrIDSex = .Item("IDSex")
      mstrSex = .Item("Sex")
      WtBirth = .Item("WtBirth")
      IDLiv = .Item("IDLiv")
      Liv = .Item("Liv")
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
   
Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

' Update the object's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spUpdate_Offspring_IDDamCycleNoLK('" & IDDam & "', " & Cycle & ", " & _
      NoLmKOrig & ", " & NoLmK & ", '" & mstrIDLmK & "', '" & mstrIDSex & _
      "', " & WtBirth * gobSetng.Decm10 & ", '" & IDLiv & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub
   
' Compose the collection of the Offspring table's primary keys.
Public Function GetKeys(ByVal strIDDam As String, intCycle As Integer) As Keys
On Error GoTo ErrHnd
    Dim obKeys As Keys
    Dim rstOffsp As ADODB.Recordset
    Dim strCmdTxt As String
    Set obKeys = New Keys
    ' Open the record set with the specified dam's matings.
    Set rstOffsp = New ADODB.Recordset
    strCmdTxt = "spSelect_Offspring_IDDamCycle_Kyes('" & strIDDam _
        & "', " & intCycle & ")"
    rstOffsp.Open strCmdTxt, gcnnConnServ, adOpenDynamic, _
            adLockOptimistic
    ' Compose the colleciton.
    With rstOffsp
        If .EOF = False And .BOF = False Then
            Do Until .EOF
                obKeys.Add .Fields.Item("IDDam"), , _
                    .Fields.Item("Cycle"), .Fields.Item("NoLambKid")
                .MoveNext
            Loop
        End If
    End With
    Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

'' Mark the offspring added, edited, or deleted in a data form's Edit
''   mode.
'Public Sub Operation(Optional ByVal blnAdded As Boolean, Optional _
'    ByVal blnEdited As Boolean, Optional ByVal blnDeld As Boolean)
'On Error GoTo ErrHnd
'    ' Set the specified mark & set off its contradictionary ones.
'    If blnAdded Then
'        ' Added.
'        mblnAdded = True
'    ElseIf blnEdited Then
'        ' Edited.
'        mblnEdited = True
'    ElseIf blnDeld Then
'        ' Deld - set off the others.
'        mblnDeld = True
'        mblnAdded = False
'        mblnEdited = False
'    End If
'Exit Sub
'ErrHnd:
'MsgBox Err.Description
'End Sub

' Get & let the offspring's Added mark.
Public Property Get Added() As Boolean
    Added = mblnAdded
End Property

Public Property Let Added(ByVal blnAdded As Boolean)
    mblnAdded = blnAdded
End Property

' Get & let the offspring's Edited mark.
Public Property Get Edited() As Boolean
    Edited = mblnEdited
End Property

Public Property Let Edited(ByVal blnEdited As Boolean)
    mblnEdited = blnEdited
End Property

' Get & let the offspring's Deld mark.
Public Property Get Deld() As Boolean
    Deld = mblnDeld
End Property

Public Property Let Deld(ByVal blnDeld As Boolean)
    mblnDeld = blnDeld
End Property

' Unless the offspring is dead, enroll it into the flock book by inserting it into the
'  SheepGoat & if necessary BreedCross tables. Escape inserting, if the offspring is
'  registered & just registered as a lamb/kid within the current lambing/kidding.
' Prevent duplication of an existent sheep/goat.
Private Function Enroll() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim blnEscIns As Boolean
   If IDLiv <> gobSetng.Liv.IDLivAlive Then 'Alive or dead.
      Enroll = True 'Dead offspring.
   Else
      If InitOffspPedgr Then 'Initialise the new offspting & its sire.
         If FillOffsp Then 'Fill the new obShG object.
            If Vld(blnEscIns) Then
               If blnEscIns Then 'Escape inserting.
                  Enroll = True
               Else
                  With mobShGOffsp 'Insert the offsprings into the ShG table.
                     Set obDatTbl = .TblShG
                     obDatTbl.Ins
                     If Not gobMsgInst.SQLErr(frmMDI.ActiveForm) Then .TblShG _
                        .BrdCrsInsNew 'Proceed, if the inserting succeeded.
                  End With
                  Enroll = Not gobMsgInst.SQLErr(frmMDI.ActiveForm) 'Succeeded, if no
               End If                                      'error during obShG inserting.
            End If
         End If
      End If
      Set mobShGSire = Nothing
      Set mobShGOffsp = Nothing
      Set mobShGOffspTest = Nothing
   End If
Exit Function
ErrHnd:
   MsgBox Err.Description
   Enroll = False 'Failed.
   Resume Next 'Remove the offspring's sire & itself from gobShGs.
End Function

' Initialise the new offspting & its pedigree.
' Return True, unless an error encounters.
Private Function InitOffspPedgr() As Boolean
On Error GoTo ErrHnd
   Const strTestAfx As String = "Test"
   Dim strIDLmKTest As String
   Dim strIDSire As String
   Set mobShGOffsp = New ShG 'Offspting.
   mobShGOffsp.IDShG = mstrIDLmK
   strIDLmKTest = mstrIDLmK & strTestAfx 'Create test ID for later reference.
   Set mobShGOffspTest = New ShG 'Testing offspring for validation.
   mobShGOffspTest.IDShG = strIDLmKTest
   With gobShGs(IDDam) 'Dam - populate the cross breeds, if crossbred, & mates.
      With .TblShG
         If .Crs Then
            If Not .PopltBrdCrs Then .BrdCrsSel 'Populate cross breeds, unless populated.
         End If
      End With
      With .Dam
         If Not .PopltMat Then .MatSel False
         strIDSire = .Mats(Cycle, False).IDSire
      End With
   End With
   With mobShGOffsp.TblShG
      .IDShG = mstrIDLmK
      .IDSire = strIDSire
   End With
   Set mobShGSire = New ShG 'Sire - populate obTblShG, unless populated, & its cross
   mobShGSire.IDShG = strIDSire                               'breeds, if crossbred.
   With mobShGSire
      .SelShG
      With .TblShG
         If .Crs Then
            If Not .PopltBrdCrs Then .BrdCrsSel 'Populate cross breeds, unless populated.
         End If
      End With
   End With
   InitOffspPedgr = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Fill the new obShG object.
' Return True, if succeeds.
Private Function FillOffsp() As Boolean
On Error GoTo ErrHnd
   With mobShGOffsp.TblShG
      .IDFarm = gobShGs(IDDam).TblShG.IDFarm
      .IDSex = mstrIDSex
      .DateBirth = gobShGs(IDDam).Dam.LmKs(Cycle, False).DateLmK
      .IDDam = IDDam
      .TypeBirth = gobShGs(IDDam).Dam.LmKs.Act.TypeBirth
      .IDFarmBirth = gobShGs(IDDam).TblShG.IDFarm
      .IDDispReas = ""
   End With
   FillOffsp = FillBrd 'Fill the breed parameters.
Exit Function
ErrHnd:
   MsgBox Err.Description
   FillOffsp = False 'Failed.
End Function

' Fill the breed parameters based on those of the dam & sire.
' Return True, if succeeds.
Private Function FillBrd() As Boolean
On Error GoTo ErrHnd
   Dim udtPedigrBasCrs As PedigrBasCrs
   Dim blnFail As Boolean
   If PedgrBrdParam(udtPedigrBasCrs) Then 'Get the dam's & sire's breed parameters.
      With mobShGOffsp.TblShG 'Set the offspring's breed.   Below: Sire/dam's same
         If udtPedigrBasCrs.IDBrdBasSire = udtPedigrBasCrs.IDBrdBasDam Then 'basic breeds
            If udtPedigrBasCrs.CrsSire = False And udtPedigrBasCrs.CrsDam = False Then
               blnFail = Not BasSamePure(udtPedigrBasCrs.IDBrdBasDam) 'Purebred.
            Else
               If Not gobTblCtrlParam.ConvCrsToPure Then 'Keep the cross breeds' shares.
                  blnFail = Not BasSameCrs(udtPedigrBasCrs.IDBrdBasDam) 'Crossbred.
                  .BrdCrsesNew.Remv32nd False 'Remove the 1/32 cross breed share.
                  blnFail = Not Limit6Share64th 'Validate the number of shares & the denominator.
               Else 'Wipe out the cross breeds' shares.
Debug.Assert 0 = 1 'Verify
                  blnFail = Not CrsToPureSrDm(udtPedigrBasCrs.IDBrdBasSire, _
                     udtPedigrBasCrs.IDBrdBasDam)
'                  FillBrd = CrsToPureSrDm(udtPedigrBasCrs.IDBrdBasSire, udtPedigrBasCrs _
                     .IDBrdBasDam)
               End If
            End If
         Else 'Sire's & dam's basic breeds are different.            Below: 'Purebred.
            If udtPedigrBasCrs.CrsSire = False And udtPedigrBasCrs.CrsDam = False Then
               If Not gobTblCtrlParam.ConvCrsToPure Then 'Keep the cross breeds' shares.
                  blnFail = Not BasDiffrPure(udtPedigrBasCrs.IDBrdBasSire, _
                     udtPedigrBasCrs.IDBrdBasDam)
               Else 'Wipe out the cross breeds' shares.
Debug.Assert 0 = 1 'Verify
                  blnFail = Not CrsToPureSrDm(udtPedigrBasCrs.IDBrdBasSire, _
                     udtPedigrBasCrs.IDBrdBasDam)
'                  FillBrd = CrsToPureSrDm(udtPedigrBasCrs.IDBrdBasSire, udtPedigrBasCrs _
                     .IDBrdBasDam)
               End If
            Else 'Crossbred.
               If Not BasDiffrCrs Then
Debug.Assert 0 = 1 'Verify
                  blnFail = True
               Else
                  If Not gobTblCtrlParam.ConvCrsToPure Then 'Keep the cross breeds' shares.
                     .BrdCrsesNew.Remv32nd False 'Remove the 1/32 cross breed share (unused but keep).
                     blnFail = Not Limit6Share64th 'Validate the number of shares & the denominator.
                  Else 'Wipe out the cross breeds' shares.
Debug.Assert 0 = 1 'Verify
                     blnFail = Not CrsToPureBas
'                     FillBrd = CrsToPureBas
                  End If
               End If
            End If
         End If
      End With
   End If
   FillBrd = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
   MsgBox Err.Description 'Failed.
   FillBrd = False
End Function

' Fill the offspring's cross breed's data for the case when sire's & dam's base breeds
'  are the same but the breeds are crossed.
' Return True, if succeeds.
Private Function BasSameCrs(strIDBrdBas As String) As Boolean
On Error GoTo ErrHnd
   With mobShGOffsp.TblShG 'Fill TblShG.
      .Crs = True
      .IDBrdBas = strIDBrdBas
      .IDBrdBasNew = strIDBrdBas
      BasSameCrs = FillCrsBrd 'Fill cross breeds.
      If BasSameCrs Then .BrdCrs = .BrdCrsNew 'Create the BreedCross code.
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
   BasSameCrs = False 'Failed.
End Function

' Fill the offspring's cross breed's data for the case when both sire's & dam's breeds
'   are pure.
' According to the cotnrol parameters' settings, set the basic breed equivalent to that
'   of the dam or sire.
Private Function BasDiffrPure(ByVal strIDBrdBasSire As String, ByVal strIDBrdBasDam _
   As String) As Boolean
On Error GoTo ErrHnd
    With mobShGOffsp.TblShG 'Fill TblShG.
'    With gobShGs(mstrIDLmK).TblShG 'Fill TblShG.
        .Crs = True
        If gobTblCtrlParam.BrdBasDam Then
            .IDBrdBas = strIDBrdBasDam 'Dam's base breed
            .IDBrdBasNew = strIDBrdBasDam
             With .BrdCrsesNew 'Fill BrdCrsesNew.
                .Add strIDBrdBasDam, 1, 2
                .Add strIDBrdBasSire, 1, 2
            End With
        Else
            .IDBrdBas = strIDBrdBasSire 'Sire's base breed.
            .IDBrdBasNew = strIDBrdBasSire
             With .BrdCrsesNew 'Fill BrdCrsesNew.
                .Add strIDBrdBasSire, 1, 2
                .Add strIDBrdBasDam, 1, 2
            End With
        End If
        .BrdCrs = .BrdCrsNew 'Create the BreedCross code.
    End With
    BasDiffrPure = True 'Succeeded.
Exit Function
ErrHnd:
    MsgBox Err.Description 'Failed.
    BasDiffrPure = False
End Function

' Fill the offspring's cross breeds in case the sire's & dam's base breeds are different
'  & the breeds are crossed.
' Return True, if succeeds.
Private Function BasDiffrCrs() As Boolean
On Error GoTo ErrHnd
   Dim strIDBrdBas As String
   If FillCrsBrd Then 'Fill cross breeds.
      With mobShGOffsp.TblShG
         strIDBrdBas = .BrdCrsesNew.DefineBas(mobShGSire.TblShG.IDBrdBas, gobShGs(IDDam) _
            .TblShG.IDBrdBas) 'Define the basic breed.
         .IDBrdBas = strIDBrdBas
         .IDBrdBasNew = strIDBrdBas
         .Crs = True 'Fill TblShG.
         .BrdCrs = .BrdCrsNew 'Create the BreedCross code.
         BasDiffrCrs = True 'Succeeded.
      End With
   End If
Exit Function
ErrHnd:
   MsgBox Err.Description
   BasDiffrCrs = False 'Failed.
End Function

' To fill the offpsring's cross breeds' shares, add sire's & dam's cross breeds' halves.
' If either sire or dam is purebred add a half of its basic breed.
' Return True, if succeeds.
Private Function FillCrsBrd() As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrsSire As TblBrdCrs
   Dim obTblBrdCrsDam As TblBrdCrs
   Dim obTblBrdCrs As TblBrdCrs
   Dim blnCrsSire As Boolean
   Dim blnCrsDam As Boolean
   Dim strIDBrdBas As String
   With mobShGOffsp.TblShG.BrdCrsesNew
      For Each obTblBrdCrsSire In mobShGSire.TblShG.BrdCrses 'Add sire's cross breeds.
         .AddHalf obTblBrdCrsSire
      Next
      For Each obTblBrdCrsDam In gobShGs(IDDam).TblShG.BrdCrses 'Add dam's cross breeds.
         .AddHalf obTblBrdCrsDam
      Next
   End With
   With gobShGs 'Check for a purebred sire or dam.
      blnCrsSire = mobShGSire.TblShG.Crs
      blnCrsDam = .Item(IDDam).TblShG.Crs
      If (blnCrsSire And blnCrsDam) = False Then 'Get sire's or dam's pure basic breed.
         If blnCrsSire Then
            strIDBrdBas = .Item(IDDam).TblShG.IDBrdBas 'Dams's.
         Else
            strIDBrdBas = mobShGSire.TblShG.IDBrdBas 'Sire's.
         End If
         Set obTblBrdCrs = New TblBrdCrs
         With obTblBrdCrs
            .IDBrd = strIDBrdBas
            .BrdNum = 1
            .BrdDen = 1
         End With
         mobShGOffsp.TblShG.BrdCrsesNew.AddHalf obTblBrdCrs
      End If
      With mobShGOffsp.TblShG.BrdCrsesNew
         .ReducToComnDen 'Reduce all cross breeds to the common denominator.
         .ReducDenNum 'Reduce the denomimator & numerators.
      End With
   End With
   FillCrsBrd = True 'Succeeded.
Exit Function
ErrHnd:
   MsgBox Err.Description
   FillCrsBrd = False 'Failed.
End Function

' Validate an added offspring to prevent duplication by verifying that:
'  - it must not duplicate its dam's ID.
'  - it must not duplicate a sheep/goat from the SheepGoat table;
'  - if a duplication in the SheepGoat table occures the offspring must not be registered
'     twice in the Offspring table & its address data must fit the current lambing/
'     kidding.
' In the last positive case, escape inserting a new sheep/goat in the SheepGoat table.
' Return True, if succeeds.
Private Function Vld(blnEscIns As Boolean) As Boolean
On Error GoTo ErrHnd
   If IDDam = mstrIDLmK Then
      Vld = False 'Offpring's ID duplicates its dam's.
      MsgBox LoadResString(76) & mstrIDLmK & LoadResString(77), vbExclamation, _
         LoadResString(50)
   Else
      If Not mobShGOffspTest.Exists(True) Then 'Prevent duplication in the
         Vld = True                                   'SheepGoat table.
      Else 'Prevent duplication in the Offspring table.
         If VldTblOffsp Then
            If VldFit Then 'Validate how the offspring fits the lambing/kidding.
               Vld = True
               blnEscIns = True 'Escape inserting.
            End If
         End If
      End If
   End If
Exit Function
ErrHnd:
   MsgBox Err.Description
   Vld = False 'Failed.
End Function

' Prevent duplication in the Offspring table.
' Return True, if succeeds.
Private Function VldTblOffsp() As Boolean
On Error GoTo ErrHnd
   Dim rstOffsp As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstOffsp = New ADODB.Recordset
   strCmdTxt = "spSelect_Offspring_IDLmK ('" & mstrIDLmK & "')"
   With rstOffsp
   rstOffsp.Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, _
      adCmdStoredProc
      If .BOF And .BOF Then
         VldTblOffsp = True 'There is no offspring with this ID.
      Else
         VldTblOffsp = False 'Duplication.
         MsgBox LoadResString(78) & mstrIDLmK & LoadResString(79), vbExclamation, _
            LoadResString(50)
      End If
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
   VldTblOffsp = False 'Failed.
End Function

' Verify if the tested offspring's pedigree, sex, breed, birth date, farm & type fit the
'  current lambing/kidding.
' To do so compare the offspring's data populated in the gobShGs object under two ID's:
'  mstrIDLmK & mstrIDLmKTest.
' Return True, if all data are identical.
Private Function VldFit() As Boolean
On Error GoTo ErrHnd
'   Dim obTblShGTest As TblShG
'   Set obTblShGTest = gobShGs(mstrIDLmKTest).TblShG 'Shorten the access to the tested obShG object.
   With mobShGOffsp.TblShG
'   With gobShGs(mstrIDLmK).TblShG
      If mobShGOffspTest.TblShG.IDFarm = .IDFarm Then 'Compare the obShG's.
         If mobShGOffspTest.TblShG.IDSex = .IDSex Then
            If (mobShGOffspTest.TblShG.IDBrdBas = .IDBrdBas) And (mobShGOffspTest.TblShG.Crs = _
               .Crs) And (mobShGOffspTest.TblShG.BrdCrs = .BrdCrs) Then
               If mobShGOffspTest.TblShG.IDFarmBirth = .IDFarmBirth Then
                  If mobShGOffspTest.TblShG.DateBirth = .DateBirth Then
                     If mobShGOffspTest.TblShG.TypeBirth = .TypeBirth Then
                        If mobShGOffspTest.TblShG.IDSire = .IDSire Then
                           If mobShGOffspTest.TblShG.IDDam = .IDDam Then
                              VldFit = True 'Succeded.
                           Else
                              Call MsgDam(mobShGOffspTest.TblShG.IDDam, .IDDam) 'Explanatory
                           End If                                        'message.
                        Else
                           Call MsgSire(mobShGOffspTest.TblShG.IDSire, .IDSire) 'Explanatory
                        End If                                        'message.
                     Else
                        Call MsgTypeBirth(mobShGOffspTest.TblShG.TypeBirth, .TypeBirth) 'Explanait.
                     End If                                                   ''message.
                  Else
                     Call MsgDateBirth(mobShGOffspTest.TblShG.DateBirth, .DateBirth) 'Explanatory
                  End If                                                   'message.
               Else
                  Call MsgFarmBirth(mobShGOffspTest.TblShG.IDFarmBirth, .IDFarmBirth) 'Explanatory
               End If                                                       'message.
            Else
               Call MsgBrdCrs(mobShGOffspTest.TblShG.IDBrdBas, mobShGOffspTest.TblShG.Crs, _
                  mobShGOffspTest.TblShG.BrdCrs, .IDBrdBas, .Crs, .BrdCrs) 'Explanatory
            End If                                                      'message.
         Else
            Call MsgSex(.IDSex, mobShGOffspTest.TblShG.IDSex) 'Explanatory message.
         End If
      Else
         Call MsgFarm(mobShGOffspTest.TblShG.IDFarm, .IDFarm) 'Explanatory message.
      End If
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
   VldFit = False 'Failed.
End Function

' Farm error message from the VldFit procedure.
Private Sub MsgFarm(ByVal strIDFarmErr As String, ByVal strIDFarm As String)
On Error GoTo ErrHnd
   Dim strPromt As String
   strPromt = RscBeg & LoadResString(54) & strIDFarmErr & LoadResString(55) & _
      strIDFarm & RscEnd
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sex error message from the VldFit procedure.
Private Sub MsgSex(ByVal strIDSexErr As String, ByVal strIDSex As String)
On Error GoTo ErrHnd
   Dim obTblSex As TblSex
   Dim strPromt As String
   Set obTblSex = New TblSex
'   strPromt = RscBeg & "- измените его пол '" & _
      obTblSex.Sex(strIDSexErr) & "' на '" & obTblSex.Sex(strIDSex) & "';" & _
      vbCrLf & LoadResString(56)
   strPromt = RscBeg & LoadResString(57) & obTblSex.Sex(strIDSexErr) & _
      LoadResString(58) & obTblSex.Sex(strIDSex) & RscEnd
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Breed error message from the VldFit procedure.
' Prior to messaging, prepare the breed strings to show in the message: full breed names
'  or cross breed codes.
'IDBrdBas Crossed BrdCrs
Private Sub MsgBrdCrs(ByVal strIDBrdBasErr As String, ByVal blnCrsErr _
   As Boolean, ByVal strBrdCrsErr As String, ByVal strIDBrdBas As String, ByVal _
   blnCrs As Boolean, ByVal strBrdCrs As String)
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim strBrdErr As String
   Dim strBrd As String
   If blnCrsErr Then 'Error breed string.
      strBrdErr = strBrdCrsErr 'Code.
   Else
Debug.Assert 0 = 1 'Verify
      strBrdErr = Util.BrdCodeToNam(strIDBrdBasErr) 'Full name.
   End If
   If blnCrs Then 'Correct breed string.
      strBrd = strBrdCrs 'Code.
   Else
Debug.Assert 0 = 1 'Verify
      strBrd = Util.BrdCodeToNam(strIDBrdBas) 'Full name.
   End If
   strPromt = RscBeg & LoadResString(59) & strBrdErr & LoadResString(58) & strBrd _
      & RscEnd
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Birth farm error message from the VldFit procedure.
Private Sub MsgFarmBirth(ByVal strIDFarmBirthErr As String, ByVal strIDFarmBirth _
   As String)
On Error GoTo ErrHnd
   Dim strPromt As String
'   strPromt = RscBeg & "- измените его ферму рождения '" & _
      strIDFarmBirthErr & "' на ферму матки/козы '" & strIDFarmBirth & RscEnd
   strPromt = RscBeg & LoadResString(65) & strIDFarmBirthErr & LoadResString(66) & _
      strIDFarmBirth & RscEnd
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Birth date error message from the VldFit procedure.
Private Sub MsgDateBirth(ByVal dtmIDDateBirthErr As Date, ByVal dtmIDDateBirth As Date)
On Error GoTo ErrHnd
   Dim strPromt As String
'   strPromt = RscBeg & "- измените его дату рождения '" & _
      CStr(dtmIDDateBirthErr) & "' на дату данного ягнения/козления '" & CStr( _
      dtmIDDateBirth) & RscEnd
   strPromt = RscBeg & LoadResString(63) & CStr(dtmIDDateBirthErr) & LoadResString(64) _
      & CStr(dtmIDDateBirth) & RscEnd
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' TypeBirth error message from the VldFit procedure.
Private Sub MsgTypeBirth(ByVal intTypeBirthErr As Integer, ByVal intTypeBirth As Integer)
On Error GoTo ErrHnd
   Dim strPromt As String
Debug.Assert 0 = 1 'Verify the promt
   strPromt = RscBeg & LoadResString(72) & CStr(intTypeBirthErr) & LoadResString(58) & _
      CStr(intTypeBirth) & RscEnd
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Sire error message from the VldFit procedure.
' Distinguish messages for available vs. missing sire.
Private Sub MsgSire(ByVal strIDSireErr As String, ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim strPromt As String
   If strIDSireErr = "" Then 'Missing sire.
      strPromt = RscBeg & LoadResString(67) & strIDSire & LoadResString(68) & vbCrLf & _
         LoadResString(56)
   Else 'Available sire.
      strPromt = RscBeg & LoadResString(69) & strIDSireErr & LoadResString(70) & _
         strIDSire & LoadResString(71) & vbCrLf & LoadResString(56)
   End If
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Dam error message from the VldFit procedure.
' Distinguish messages for available vs. missing dam.
Private Sub MsgDam(ByVal strIDDamErr As String, ByVal strIDDam As String)
On Error GoTo ErrHnd
   Dim strPromt As String
Debug.Assert 0 = 1 'Verify "" vs. former gobFormtCtl.BlankIDText
   If strIDDamErr = "" Then 'Missing dam.
'   If strIDDamErr = gobFormtCtl.BlankIDText Then 'Missing dam.
      strPromt = RscBeg & LoadResString(60) & strIDDam & RscEnd
   Else 'Available dam.
      strPromt = RscBeg & LoadResString(61) & strIDDamErr & LoadResString(62) & strIDDam _
         & RscEnd
   End If
   MsgBox strPromt, vbExclamation, LoadResString(50)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Compose the beginning of a message from the resource file.
Private Function RscBeg() As String
On Error GoTo ErrHnd
   RscBeg = LoadResString(51) & mstrIDLmK & LoadResString(52) & vbCrLf & vbCrLf & _
      LoadResString(53) & vbCrLf
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Compose the ending of a message from the resource file.
Private Function RscEnd() As String
On Error GoTo ErrHnd
   RscEnd = "';" & vbCrLf & LoadResString(56)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the dam's & sire's breed parameters to the procecdure's by-reference arguments.
' Return True, if succeeds.
Private Function PedgrBrdParam(ByRef udtPedigrBasCrs As PedigrBasCrs) As Boolean
On Error GoTo ErrHnd
   With mobShGSire.TblShG
      udtPedigrBasCrs.IDBrdBasSire = .IDBrdBas
      udtPedigrBasCrs.CrsSire = .Crs
   End With
   With gobShGs(IDDam).TblShG
      udtPedigrBasCrs.IDBrdBasDam = .IDBrdBas
      udtPedigrBasCrs.CrsDam = .Crs
   End With
   PedgrBrdParam = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Fill the offspring's cross breed's data for the case when sire's & dam's base breeds
'  are the same & the breeds are pure.
' Return True, if succeeds.
Private Function BasSamePure(ByVal strIDBrdBas As String) As Boolean
On Error GoTo ErrHnd
   With mobShGOffsp.TblShG 'Fill TblShG.
      .IDBrdBas = strIDBrdBas
      .Crs = False
      .BrdCrs = strIDBrdBas
   End With
   BasSamePure = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Convert the cross breed to pure & take the sire/dam's basic breed as the offsprings
'  breed, in case the gobTblCtrlParam.ConvCrsToPure setting is True.
' Return True, if succeeds.
Private Function CrsToPureSrDm(ByVal strIDBrdBasSire As String, ByVal strIDBrdBasDam _
   As String) As Boolean
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify
   With mobShGOffsp.TblShG 'Fill TblShG.
'   With gobShGs(mstrIDLmK).TblShG 'Fill TblShG.
      .Crs = False
      If gobTblCtrlParam.BrdBasDam Then 'Sire's or dam's basic breed.
         .IDBrdBas = strIDBrdBasDam
         .BrdCrs = strIDBrdBasDam
      Else
         .IDBrdBas = strIDBrdBasSire
         .BrdCrs = strIDBrdBasSire
      End If
   End With
   CrsToPureSrDm = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Convert the cross breed to pure & leave the basic breed as the breed after defining the
'  breed in the BasDiffrCrs procedure, in case the gobTblCtrlParam.ConvCrsToPure setting
'  is True.
' Return True, if succeeds.
Private Function CrsToPureBas() As Boolean
On Error GoTo ErrHnd
   With mobShGOffsp.TblShG
'   With gobShGs(mstrIDLmK).TblShG
      .Crs = False
      .BrdCrs = .IDBrdBas
      .BrdCrsesNew.DelAll 'Delete all cross breed shares.
   End With
   CrsToPureBas = True 'Succeeded.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

' Limit the number of shares (up to 6) & the size of the denominator (up to 64).
' Return True, if nether limit fired. Otherwise promt to manually adjust the breed.
Private Function Limit6Share64th() As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim blnBrdDenMore64 As Boolean
   Dim intBrdDen As Integer
   Dim blnFail As Boolean
   Dim strPromt As String
   With mobShGOffsp.TblShG
      If .BrdCrsesNew.Count > 0 Then 'Any cross breed shares?
         For Each obTblBrdCrs In .BrdCrsesNew 'Look for a denominator > 64.
            If obTblBrdCrs.BrdDen > gobSetng.BrdCrsMaxDen Then
               blnBrdDenMore64 = True
               intBrdDen = obTblBrdCrs.BrdDen 'Remember the denominator for later use.
            End If
            Exit For
         Next 'Below: 'Denominator > 64 or shares > 6?
         If blnBrdDenMore64 Or .BrdCrsesNew.Count > gobSetng.BrdCrsMaxShare Then
            If blnBrdDenMore64 Then 'Promt about denominator > 64.
               strPromt = LoadResString(427) & BrdPureCrs( _
                  mobShGSire.TblShG) & LoadResString(428) & mobShGSire.IDShG & _
                  LoadResString(429) & BrdPureCrs(gobShGs(IDDam).TblShG) & _
                  LoadResString(430) & IDDam & LoadResString(431) & .BrdCrs & _
                  LoadResString(432) & IDLmK & LoadResString(433) & intBrdDen & ") " & _
                  LoadResString(434) & gobSetng.BrdCrsMaxDen & ". " & String$(2, vbCrLf) _
                  & LoadResString(435) & LoadResString(436)
            ElseIf .BrdCrsesNew.Count > gobSetng.BrdCrsMaxShare Then 'Promt about shares > 6.
               strPromt = LoadResString(438) & .BrdCrsesNew.Count & LoadResString(439) & _
                  .BrdCrs & LoadResString(432) & IDLmK & "' " & LoadResString(434) & _
                  gobSetng.BrdCrsMaxShare & ". " & String$(2, vbCrLf) & _
                  LoadResString(440) & LoadResString(436)
            End If
            If MsgBox(strPromt, vbInformation + vbOKCancel, LoadResString(437)) = _
               vbCancel Then 'Promt to correct.
               blnFail = True 'Correction rejected.
            Else
               Load frmBrdCrs 'Load & initialise mfrmBrdCrs.
               Call frmBrdCrs.InitFrm(mobShGOffsp, True)
               frmBrdCrs.Show vbModal
               With mobShGOffsp.TblShG
                  If .BrdCrsChand Then 'A new cross breed inputted?
                     .BrdCrs = .BrdCrsNew 'Create the BreedCross code.
                  Else
                     blnFail = True 'No new cross breed inputted.
                  End If
               End With
            End If
         End If
      End If
   End With
   Limit6Share64th = Not blnFail 'Succeeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return pure breed's name or crossbred breed's code based on whether the ShG's breed is
'  pure or crossbred.
Private Function BrdPureCrs(ByVal obTblShG As TblShG) As String
On Error GoTo ErrHnd
   With obTblShG
      If .Crs Then
         BrdPureCrs = .BrdCrs 'Crossbred.
      Else
Debug.Assert 0 = 1 'Verify
         BrdPureCrs = Util.BrdCodeToNam(.IDBrdBas) 'Purebred.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
