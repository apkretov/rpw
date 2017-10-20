VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ShG"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mobTblShG As TblShG
Dim mobTblWtWean As TblWtWean
Dim mobTblWt7Mon As TblWt7Mon
Dim mobWtWools As WtWools
Dim mobApprs As Apprs
Dim mobSire As Sire
Dim mobDam As Dam

Dim mstrIDShG As String

Public HostCount As Integer
Public HostShG As Boolean
Public HostLmK As Boolean
Public PopltWtWool As Boolean
Public PopltAppr As Boolean

' Initialise new module level objects.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobTblShG = New TblShG
   Set mobTblWtWean = New TblWtWean
   Set mobTblWt7Mon = New TblWt7Mon
   Set mobWtWools = New WtWools
   Set mobApprs = New Apprs
   Set mobSire = New Sire
   Set mobDam = New Dam
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the mobTblShG object into the ShG object.
Public Property Get TblShG() As TblShG
    Set TblShG = mobTblShG
End Property

' Get the mobTblShG object's data.
' Execute only once to escape unnecessary operation.
Public Sub SelShG(Optional ByVal blnDoSel As Boolean = False)
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   Dim obDatTbl As DatTbl
   If blnPassed = False Or blnDoSel Then
      blnPassed = True
      Set obDatTbl = mobTblShG
      obDatTbl.Sel mstrIDShG
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the mobTblWtWean object into the WtWean object.
Public Property Get TblWtWean() As TblWtWean
   Set TblWtWean = mobTblWtWean
End Property

' Select a weighing from the WeightWean table.
' Validate the lamb/kid for existence & disposition, if required.
Public Sub SelWtWean(ByVal blnDoValid As Boolean)
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim blnValidShG As Boolean
   If blnDoValid Then 'Validate the sheep/goat.
      blnValidShG = VldShG 'Validate.
   Else
      blnValidShG = True 'Skip validation.
   End If
   If blnValidShG Then 'Validate
      Set obDatTbl = mobTblWtWean 'Select.
      obDatTbl.Sel mstrIDShG
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the mobTblWt7Mon object into the Weight7Mon object.
Public Property Get TblWt7Mon() As TblWt7Mon
    Set TblWt7Mon = mobTblWt7Mon
End Property

' Select a weighing from the Weight7Mon table.
Public Sub SelWt7Mon()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Set obDatTbl = mobTblWt7Mon
    obDatTbl.Sel mstrIDShG
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the WtWools collection object into the Dam object.
Public Property Get WtWools() As WtWools
    Set WtWools = mobWtWools
End Property

' Get the mobApprs collection for the frmAppr form.
' Remember the original count of all defects to redefine the complex class (since a
'  single defect degrades the class down to Defct class), if the former changes.
' Validate the sheep/goat first, if required.
Public Sub SelAppr(ByVal blnDoValid As Boolean)
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim obDatTbl As DatTbl
   Dim obKeys As Keys
   Dim obKey As Key
   Dim blnValidShG As Boolean
   If blnDoValid Then 'Validate the sheep/goat.
      blnValidShG = VldShG 'Validate.
   Else
      blnValidShG = True 'Skip validation.
   End If
   If blnValidShG Then
      Set obTblAppr = New TblAppr
      obTblAppr.IDShG = mstrIDShG
      Set obKeys = obTblAppr.GetKeys() 'Get the primary keys values for the Appr table to fill the mobApprs collection.
      If obKeys.Count = 0 Then 'Check how many weighings there are in the collection.
         gobMsgInst.NoApprSnd frmMDI.ActiveForm
      Else
         For Each obKey In obKeys
            Set obDatTbl = obTblAppr
            With obKey
               obDatTbl.Sel .Key0, , .Key2
            End With
            With obTblAppr
               mobApprs.Add .AgeOrig, .Age, .DateAppr, .Leng, .Diam, .Mass, .Crimpins, _
                  .Evens, .Density, .Strength, .IDColour, .Colour, .Quality, _
                  .IDFluffColour, .FluffColour, .Fluff, .FibreYield, .BodyType, _
                  .Constitutn, .BodySize, .FatTail
               mobApprs(.Age, False).InhertDefctSel 'Fill the current age defects.
            End With
         Next
         mobApprs.AllDefctOrig 'Original defect count.
         PopltAppr = True 'Mark appraisal populated.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the given animal for whether it is existent & kept.
' Return True, if succeeds.
Private Function VldShG() As Boolean
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   Call SelShG
   If Not mobTblShG.Full Then
      VldShG = False 'The animal doesn't exist.
   ElseIf mobTblShG.IDDispReas <> "" Then 'The animal is disposed.
      Set obDatFrm = frmMDI.ActiveForm
      If obDatFrm.Mode = gobSetng.ModeAdd Then 'Restirct only addition.
         VldShG = False
         gobMsgInst.ShGDispdSnd frmMDI.ActiveForm
         MsgBox "∆ивотное '" & mstrIDShG & "' выбыло из учЄта. ¬вод новых данных не " & _
            "возможен.", vbExclamation, LoadResString(131)
      Else
         VldShG = True 'Sucseeded
      End If
   Else
      VldShG = True 'Sucseeded
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Build in & link to the Apprs collection object into the ShG object.
Public Property Get Apprs() As Apprs
   Set Apprs = mobApprs
End Property

' Get the mobWtWools collection for the frmWtWool form.
' Validate the sheep/goat first, if required.
Public Sub SelWtWool(ByVal blnDoValid As Boolean)
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim obDatTbl As DatTbl
   Dim obKeys As Keys
   Dim obKey As Key
   Dim blnValidShG As Boolean
   If blnDoValid Then 'Validate the sheep/goat.
      blnValidShG = VldShG 'Validate.
   Else
      blnValidShG = True 'Skip validation.
   End If
   If blnValidShG Then
      Set obTblWtWool = New TblWtWool
      Set obKeys = obTblWtWool.GetKeys(mstrIDShG) 'Get the primary keys values for the WtWool table to fill the mobWtWools collection.
      If obKeys.Count = 0 Then 'Check how many weighings there are in the collection.
         gobMsgInst.NoWtWoolSnd frmMDI.ActiveForm
      Else
         For Each obKey In obKeys
            Set obDatTbl = obTblWtWool
            With obKey
               obDatTbl.Sel .Key0, , .Key2
            End With
            With obTblWtWool
               mobWtWools.Add .AgeOrig, .Age, .DateAnnl, .WtAnnl, .DateShearAnnl, _
                  .GreaseAnnl
            End With
         Next
         PopltWtWool = True 'Mark weighings populated.
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get IDShG.
Public Property Get IDShG() As String
   IDShG = mstrIDShG
End Property

' Let IDShG in this class & in its inbuilt ones.
Public Property Let IDShG(ByVal strIDShG As String)
On Error GoTo ErrHnd
   mstrIDShG = strIDShG
   mobTblShG.IDShG = strIDShG
   mobWtWools.IDShG = strIDShG
   mobApprs.IDShG = strIDShG
   mobSire.IDSire = strIDShG
   mobDam.IDDam = strIDShG
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Link the mobSelIdxCC object to the ShG one.
' Initialise the mobSelIdxCC object only on demand.
Public Property Get TblSelIdxCC() As TblSelIdxCC
On Error GoTo ErrHnd
   Static obTblSelIdxCC As TblSelIdxCC
   Static blnPassed As Boolean
   If Not blnPassed Then 'Execute once.
      blnPassed = True
      Set obTblSelIdxCC = New TblSelIdxCC
      obTblSelIdxCC.ClassInitialize Me
   End If
   Set TblSelIdxCC = obTblSelIdxCC
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Link the mobTestSire object to the ShG one.
' Initialise the mobTestSire object only on demand.
Public Property Get TblTestSire() As TblTestSire
On Error GoTo ErrHnd
   Static obTblTestSire As TblTestSire
   Static blnPassed As Boolean
   If Not blnPassed Then 'Execute once.
      blnPassed = True
      Set obTblTestSire = New TblTestSire
      obTblTestSire.ClassInitialize mstrIDShG
   End If
   Set TblTestSire = obTblTestSire
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return True, if the ShG exists.
' Pupulate the ShG's data, unless done yet.
Public Function Exists(ByVal blnEscIDShGWrng As Boolean) As Boolean
On Error GoTo ErrHnd
   With mobTblShG
      .EscIDShGWrng = blnEscIDShGWrng 'Escape the IDShGWrong message, unless required.
      Call SelShG 'Populate.
      Exists = .Full 'Succeeded, if full.
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Compute the ShG's age at the specified event.
' Rerurn the age in years or days.
Public Function Age(ByVal dtmEvent As Date, Optional ByVal blnYearVsDay As Boolean = _
   False) As Single
On Error GoTo ErrHnd
   Age = dtmEvent - mobTblShG.DateBirth 'Days.
   If blnYearVsDay Then Age = Round(Age / gobSetng.YearDays, 1) 'Years.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if the ShG lives at the specified event i.e. the event happens after the
'  birth & before the maximal life time ends or before the disposition date (if required).
' If fails, return the failure message to the by-ref strPromt argument.
Public Function Lives(ByVal dtmEvent As Date, Optional ByVal strEvent As String, _
   Optional ByVal blnEscDisp As Boolean = False, Optional ByRef strPromt As String _
   ) As Boolean
On Error GoTo ErrHnd
   Dim sngAgeYr As Single
   sngAgeYr = Age(dtmEvent, True) 'Age in years for later use.
   With mobTblShG
      If dtmEvent <= .DateBirth Then 'The birth.
         strPromt = Util.CutColonAmpers(strEvent) & " (" & dtmEvent & LoadResString(568) & _
            .DateBirth & LoadResString(569) & IDShG & "'."
      ElseIf (blnEscDisp = False) And (.IDDispReas <> "" And dtmEvent >= _
         .DateDisp) Then 'The disposition, if required.
         strPromt = Util.CutColonAmpers(strEvent) & " (" & dtmEvent & _
            LoadResString(574) & .DateDisp & LoadResString(569) & IDShG & "'."
      ElseIf sngAgeYr > gobTblCtrlParam.LifeTimeMax Then 'The max life time.
         strPromt = Util.CutColonAmpers(strEvent) & " (" & dtmEvent & LoadResString(570) _
            & sngAgeYr & LoadResString(571) & IDShG & LoadResString(572) & _
            gobTblCtrlParam.LifeTimeMax & LoadResString(333)
      Else
         Lives = True 'Succeeded.
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Link to the mobSire object.
Public Property Get Sire() As Sire
   Set Sire = mobSire
End Property

' Link to the mobDam object.
Public Property Get Dam() As Dam
   Set Dam = mobDam
End Property

' Varify if the ShG's species can change. The species can change uless the ShG has goat-
'  specific trait records i.e. fluff colour, fluff, fibre yield.
' Return True, if succeeds.
Public Function CanChngBrd(ByVal strIDBrdBasTest As String) As Boolean
On Error GoTo ErrHnd
   Dim obTblBrd As TblBrd
   Dim obTblBrdTest As TblBrd
   Dim obTblAppr As TblAppr
   Dim strPromt As String
   Dim blnFail As Boolean
   Set obTblBrd = SelTblBrd(mobTblShG.IDBrdBas) 'Populate the ShG's breed table.
   If obTblBrd.IDSpcs = gobSetng.IDSpcsG Then 'Is the ShG a goat?
      Set obTblBrdTest = SelTblBrd(strIDBrdBasTest) 'Populate the test ShG's breed table.
      If obTblBrdTest.IDSpcs = gobSetng.IDSpcsSh Then 'Changed from goat to sheep?
         If Not PopltAppr Then Call SelAppr(False) 'Populate appraisals.
         If mobApprs.Count > 0 Then 'Ever appraised?
            For Each obTblAppr In mobApprs 'Look for goat-specific traits measured.
               With obTblAppr
                  If .FluffColour <> "" Or .Fluff <> 0 Or .FibreYield <> 0 Then
                     blnFail = True 'Sheep can't have goat traits.
                     Exit For 'Exit the loop.
                  End If
               End With
            Next
         End If
      End If
   End If
   If blnFail Then 'Message.
      strPromt = LoadResString(215) & obTblBrd.Brd & LoadResString(216) & obTblBrdTest _
         .Brd & LoadResString(217)
      MsgBox strPromt, vbExclamation, LoadResString(131)
   Else 'Succeeded.
      CanChngBrd = True
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the ShG's species ID.
Private Function SelTblBrd(ByVal strIDBrd As String) As TblBrd
On Error GoTo ErrHnd
   Dim obTblBrd As TblBrd
   Dim obDatTbl As DatTbl
   Set obTblBrd = New TblBrd 'Populate the breed.
   Set obDatTbl = obTblBrd
   obDatTbl.Sel strIDBrd
   Set SelTblBrd = obTblBrd
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
