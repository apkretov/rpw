VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblSelIdxCC"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Const mintAge1Yr As Integer = 1
Const mstrClEl As String = "3"

Dim mobShG As ShG
Dim mobTblBrd As TblBrd

Dim mobTblStdWt As TblStd
Dim mobTblStdGrease As TblStd
Dim mobTblStdLeng As TblStd
Dim mobTblStdDiam As TblStd
Dim mobTblStdFatTail As TblStd

Dim mobSQLErrHnd As SQLErrHnd

Dim mstrIDShG As String
Dim msngSelIndx As Single
Dim mstrIDCompClass As String
Dim mblnFull As Boolean

Dim mintParms As Integer
Dim mblnDelWtWool As Boolean
Dim mblnDelAppr As Boolean
Dim mintFrmCallIdx As Integer

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the SelIndxCompClass table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "DELETE FROM SelIndxCompClass WHERE IDSheepGoat = '" & mstrIDShG & "'"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   mstrIDCompClass = "" 'Nullify the loaded in the ShG object.
   msngSelIndx = 0
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new selection indext / complex class to the SelIndxCompClass table.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "INSERT INTO SelIndxCompClass (IDSheepGoat, SelIndx, IDCompClass) " & _
      "VALUES ('" & mstrIDShG & "', " & Util.NumStrDB(msngSelIndx) & ", '" & _
         mstrIDCompClass & "')"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = True 'Mark full.
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

' Select data from the SelIndxCompClass table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
    Dim rstSelIndxCompClass As ADODB.Recordset
    Dim strCmdTxt As String
    Dim strIDShG As String
    Set rstSelIndxCompClass = New ADODB.Recordset
    strIDShG = vntKeys(0)
    strCmdTxt = "SELECT * FROM SelIndxCompClass WHERE IDSheepGoat = '" & strIDShG & "'"
    With rstSelIndxCompClass
        .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
        If .EOF And .BOF Then
            mblnFull = False 'Mark empty.
        Else
            With .Fields 'Define the animal's data from the SelIndxCompClass recordset.
                mstrIDShG = .Item("IDSheepGoat")
                msngSelIndx = .Item("SelIndx")
                mstrIDCompClass = .Item("IDCompClass")
            End With
            mblnFull = True 'Mark full.
        End If
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the SelIndxCompClass table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "UPDATE SelIndxCompClass SET SelIndx = " & Util.NumStrDB(msngSelIndx) & _
      ", IDCompClass = '" & mstrIDCompClass & "' WHERE IDSheepGoat = '" & mstrIDShG & "'"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Rem Substitute likewise the majority of messages from gobMsgInst.
' Full record mark.
Public Property Get Full() As Boolean
   Full = mblnFull
End Property

' Calculate the sheep/goat's selection index & complex class.
' Unless the selection index & complex class are available insert new otherwise update
'  the available.
' First validate the data for their fool composition to calculate selection index &
'  complex class.
Public Sub GetRefrsh(ByVal intFrmCallIdx As Integer)
On Error GoTo ErrHnd
   mintFrmCallIdx = intFrmCallIdx 'Set the calling form's index.
   If Vld() Then 'Get & validate required parameters.
      Call Calc 'Calculate the selection index & complex class.
      Select Case Full
      Case False 'Insert new selection index & complex class.
         Call DatTbl_Ins
      Case True 'Update the available selection index & complex class.
         Call DatTbl_Upd
      End Select
   End If
   Call RefrshInven 'Refresh the frmInven.dbcCompClass control.
   Call UnloadWtAppr 'Unload weighings/appraisals
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Varify whether the data have been populated, i.e. the frmWtWool form invoked the
'  method, & the active age is 1 year. Unless otherwise populated i.e. the frmAppr
'  invokes the method & the frmWtWool form doesn't show the sheep/goat populate the
'  data & varify the presense of the 1-year data.
' Verify likewise the Appraisal data; populate them, if necassary.
' Define whether the sheep/goat has all data required according to its breed's standard
'  to calculate selection index/comlex class.
' The required parameters are 1-year-measurements of:
'   weight, grease wool, staple length, fibre diameter & fat tail content.
Private Function Vld() As Boolean
On Error GoTo ErrHnd
   Dim obDatTblSel As DatTblSel
   Vld = False 'Reset, if ever used.
   If VldPoplt Then 'Populate weighings/apprasals & verify 1-yr data's availab.
      Call PopltBrd 'Populate the mobTblBrd object.
      mintParms = 0 'Reset the parameter counter.
      With mobTblBrd
         If .WtWt > 0 Then 'Weight.
            If Not VldWt Then Exit Function
         End If
         If .WtGrease > 0 Then 'Grease wool.
            If Not VldGrease Then Exit Function
         End If
         If .WtLeng > 0 Then 'Staple length.
            If Not VldLeng Then Exit Function
         End If
         If .WtDiam > 0 Then 'Fibre diameter.
            If Not VldDiam Then Exit Function
         End If
         If .WtFatTail > 0 Then 'FatTail content.
            If Not VldFatTail Then Exit Function
         End If
      End With
      If mintParms <> 0 Then Vld = True 'Verify the number of breed's defined
   End If                                 'parameters.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Varify whether the data have been populated, i.e. the frmWtWool form calls the
'  method & the active age is 1 year. Unless populated i.e. the frmAppr calls the method
'  & the frmWtWool form doesn't show, populate the data & varify the presence of
'  1-year data.
' Return True, if succeeds.
Private Function VldPoplt() As Boolean
On Error GoTo ErrHnd
   Dim blnExit As Boolean
   Select Case mintFrmCallIdx
   Case gobSetng.FrmWtWoolIdx 'frmWtWool - populate appraisal data.
      If mobShG.WtWools.Act.Age = mintAge1Yr Then 'For 1-year weighing only.
         If Not mobShG.PopltAppr Then 'Appraisals' presence.
               mobShG.SelAppr False
            If gobMsgInst.NoAppr(frmMDI.ActiveForm) Then
               blnExit = True 'No appraisals.
            Else
               mblnDelAppr = True 'Mark to release appraisals afterwards.
            End If
         End If
         If Not blnExit Then '1-year appraisal's presence.
            If mobShG.Apprs.First(True).Age = mintAge1Yr Then 'Is 1-yr appraisal
               If mobShG.PopltAppr Then            'being added or has been added before?
                  If gobDatFrms(mstrIDShG, gobSetng.FrmShGNam).FrmHost.Add1YrAppr Then
Debug.Assert 0 = 1 'Verify If
                     If mobShG.Apprs.Last(True).Age <> mintAge1Yr Then VldPoplt = True
                  Else
                     VldPoplt = True
                  End If
               Else
                  VldPoplt = True
               End If
            End If
         End If
      End If
   Case gobSetng.FrmApprIdx 'frmAppr - populate weighings.
      If (mobShG.Apprs.Act.Age = mintAge1Yr) Or (mobShG.Apprs.AllDefct <> mobShG.Apprs _
         .AllDefctOrig) Then 'Only for 1-yr appraisal or changed defect count.
         If Not mobShG.PopltWtWool Then 'Weighings' presence.
            mobShG.SelWtWool False
            If gobMsgInst.NoWtWool(frmMDI.ActiveForm) Then
               blnExit = True 'No weighings.
            Else
               mblnDelWtWool = True 'Mark to release weighings afterwards.
            End If
         End If
         If Not blnExit Then '1-year weighing's presence.
            If mobShG.WtWools.First(True).Age = mintAge1Yr Then 'Is 1-yr weighing being
               If mobShG.PopltWtWool Then               'added or have been added before?
                  If gobDatFrms(mstrIDShG, gobSetng.FrmShGNam).FrmHost.Add1YrWtWool Then
Debug.Assert 0 = 1 'Verify If
'                  If gobDatFrms(mstrIDShG, gobSetng.FrmShGNam).Mode = gobSetng.ModeAdd _
                     Then
                     If mobShG.WtWools.Last(True).Age <> mintAge1Yr Then VldPoplt = True
                  Else
                     VldPoplt = True
                  End If
               Else
                  VldPoplt = True
               End If
            End If
         End If
      End If
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Calculate the selection index by summing up the items taken into account according to a
'  breed's standard.
' Calculate the complex class.
' Determine the complex class by the independeng-culling method; the lowest trait's class
'  determines the complex class.
' If there is no selection index & complex class yet, prior to setting the rest
'  properties, set the sheep/goat's ID in the mobTblSelIdxCC object
' Prior to the calculations, reset the selection index & complex class. Set the former
'  to the minimum to add its items. Set the latter to the maximum to lower it down to the
'  smallest item.
' First scan defects; should a single one encounter grade down to the lowest complex
'  class.
Private Sub Calc()
On Error GoTo ErrHnd
   Const strClDefct As String = "0"
   Dim blnDefct As Boolean
   msngSelIndx = 0 'Reset.
   mstrIDCompClass = mstrClEl '"3"
   If Defct Then 'Scan defects for complex class.
      blnDefct = True 'Defective.
      mstrIDCompClass = strClDefct
   End If
   With mobTblBrd 'Calculate the selection index's items & determine classes, unless defective.
      If .WtWt > 0 Then Call Wt(blnDefct) 'Process each item, if its weight is more than zero. Weight.
      If .WtGrease > 0 Then Call Grease(blnDefct) 'Grease.
      If .WtLeng > 0 Then Call Leng(blnDefct) 'Length.
      If .WtDiam > 0 Then Call Diam(blnDefct) 'Diameter.
      If .WtFatTail > 0 Then Call FatTail(blnDefct) 'FatTail.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Calculate a score for a trait based on the range between its maximum & minimum.
' Treat a value above or below the range as the maximum or minimum correspondingly.
' The maximal score is equal to the scale's maximum; the mimimal score is zero.
Private Function Index(ByVal sngVal As Single, ByVal sngMax As Single, ByVal sngMin _
   As Single) As Single
On Error GoTo ErrHnd
   If sngVal < sngMin Then 'Below.
      Index = 0
   ElseIf sngVal >= sngMin And sngVal <= sngMax Then 'In-between.
      Index = (sngVal - sngMin) / (sngMax - sngMin) * gobTblCtrlParam.SelIndxScale
   ElseIf sngVal > sngMax Then 'Above.
      Index = gobTblCtrlParam.SelIndxScale
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Determine a trait's class based on its independent culling levels.
' Treat a value above or equal to the Elite level as Elite, in-between Elite & Class 1
'  as Class 1, & below Class 1 - as Class 2.
Private Function Class(ByVal sngVal As Single, ByVal sngElite As Single, ByVal _
   sngClass1 As Single) As String
On Error GoTo ErrHnd
   Const strCl2 As String = "1"
   Const strCl1 As String = "2"
   If sngVal >= sngElite Then 'Elite.
      Class = mstrClEl
   ElseIf sngVal >= sngClass1 Then 'Class 1.
      Class = strCl1
   ElseIf sngVal < sngClass1 Then 'Class 2.
      Class = strCl2
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Calculate the Weight item of the selection index's & complex class.
' Escape the comlex class's calculation, if the sheep/goat has a defect.
' Let the complex class equal to that of Weight, if the latter is lower than the former.
Private Sub Wt(ByVal blnDefct As Boolean)
On Error GoTo ErrHnd
   Dim sngWt As Single
   Dim strIDCC As String
   With mobTblStdWt
      If mobShG.TblShG.IDSex = gobSetng.IDSexMl Then 'Male of female.
         sngWt = Index(mobShG.WtWools(mintAge1Yr, True).WtAnnl, .MaleMax, _
            .MaleMin) 'Index.
         If Not blnDefct Then strIDCC = Class(mobShG.WtWools(mintAge1Yr, True).WtAnnl, _
            .MaleElite, .MaleClass1) 'Class.
      Else
         sngWt = Index(mobShG.WtWools(mintAge1Yr, True).WtAnnl, .FemaleMax, .FemaleMin) 'Index.
         If Not blnDefct Then strIDCC = Class(mobShG.WtWools(mintAge1Yr, True).WtAnnl, _
            .FemaleElite, .FemaleClass1) 'Class.
      End If
   End With
   msngSelIndx = msngSelIndx + sngWt * mobTblBrd.WtWt / gobSetng.Perc100 'Calculate the index.
   If blnDefct = False And strIDCC < mstrIDCompClass Then mstrIDCompClass = strIDCC 'Remember a lower class.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Calculate the Grease item of the selection index's & complex class.
' Escape the comlex class's calculation, if the sheep/goat has a defect.
' Let the complex class equal to that of Grease, if the latter is lower
'   than the former.
Private Sub Grease(ByVal blnDefct As Boolean)
On Error GoTo ErrHnd
   Dim sngGrease As Single
   Dim strIDCC As String
   With mobTblStdGrease
      If mobShG.TblShG.IDSex = gobSetng.IDSexMl Then 'Male of female.
         sngGrease = Index(mobShG.WtWools(mintAge1Yr, True).GreaseAnnl, .MaleMax, _
            .MaleMin) 'Index.
         If blnDefct = False Then strIDCC = Class(mobShG.WtWools(mintAge1Yr, True) _
            .GreaseAnnl, .MaleElite, .MaleClass1) 'Class.
      Else
         sngGrease = Index(mobShG.WtWools(mintAge1Yr, True).GreaseAnnl, .FemaleMax, _
            .FemaleMin) 'Index.
         If blnDefct = False Then strIDCC = Class(mobShG.WtWools(mintAge1Yr, True) _
            .GreaseAnnl, .FemaleElite, .FemaleClass1) 'Class.
      End If
   End With
   msngSelIndx = msngSelIndx + sngGrease * mobTblBrd.WtGrease / gobSetng.Perc100 'Calculate the index.
   If blnDefct = False And strIDCC < mstrIDCompClass Then mstrIDCompClass = strIDCC 'Remember a lower class.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Calculate the Length item of the selection index's & complex class.
' Escape the comlex class's calculation, if the sheep/goat has a defect.
' Let the complex class equal to that of Length, if the latter is lower
'   than the former.
Private Sub Leng(ByVal blnDefct As Boolean)
On Error GoTo ErrHnd
    Dim sngLeng As Single
    Dim strIDCC As String
    With mobTblStdLeng
        ' Male of female.
        If mobShG.TblShG.IDSex = gobSetng.IDSexMl Then
            sngLeng = Index(mobShG.Apprs(mintAge1Yr, True).Leng, _
               .MaleMax, .MaleMin)
            If blnDefct = False Then strIDCC = _
                Class(mobShG.Apprs(mintAge1Yr, True).Leng, .MaleElite, _
                  .MaleClass1)
        Else
            sngLeng = Index(mobShG.Apprs(mintAge1Yr, True).Leng, .FemaleMax, .FemaleMin)
            If blnDefct = False Then strIDCC = _
                Class(mobShG.Apprs(mintAge1Yr, True).Leng, .FemaleElite, .FemaleClass1)
        End If
    End With
'    With mobTblSelIdxCC
    ' Calculate the index.
    msngSelIndx = msngSelIndx + sngLeng * mobTblBrd.WtLeng / gobSetng.Perc100
    ' Remember a lower class.
    If blnDefct = False And strIDCC < mstrIDCompClass Then _
       mstrIDCompClass = strIDCC
'    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Calculate the Diameter item of the selection index's & complex class.
' Escape the comlex class's calculation, if the sheep/goat has a defect.
' Let the complex class equal to that of Diameter, if the latter is lower
'   than the former.
Private Sub Diam(ByVal blnDefct As Boolean)
On Error GoTo ErrHnd
    Dim sngDiam As Single
    Dim strIDCC As String
    With mobTblStdDiam
        ' Male of female.
        If mobShG.TblShG.IDSex = gobSetng.IDSexMl Then
            sngDiam = Index(mobShG.Apprs(mintAge1Yr, True).Diam, .MaleMax, .MaleMin)
'            sngDiam = Index(mobShG.Apprs(mintAge1Yr, True).Diam, .MaleMax, .MaleMin, True)
            If blnDefct = False Then strIDCC = Class(mobShG.Apprs(mintAge1Yr, True) _
               .Diam, .MaleElite, .MaleClass1)
'            If blnDefct = False Then strIDCC = Class(mobShG.Apprs(mintAge1Yr, True) _
               .Diam, .MaleElite, .MaleClass1, True)
        Else
            sngDiam = Index(mobShG.Apprs(mintAge1Yr, True).Diam, .FemaleMax, .FemaleMin)
'            sngDiam = Index(mobShG.Apprs(mintAge1Yr, True).Diam, .FemaleMax, .FemaleMin, True)
            If blnDefct = False Then strIDCC = Class(mobShG.Apprs(mintAge1Yr, True) _
               .Diam, .FemaleElite, .FemaleClass1)
'            If blnDefct = False Then strIDCC = Class(mobShG.Apprs(mintAge1Yr, True) _
               .Diam, .FemaleElite, .FemaleClass1, True)
        End If
    End With
'    With mobTblSelIdxCC
    ' Calculate the index.
    msngSelIndx = msngSelIndx + sngDiam * mobTblBrd.WtDiam / gobSetng.Perc100
    ' Remember a lower class.
    If blnDefct = False And strIDCC < mstrIDCompClass Then _
       mstrIDCompClass = strIDCC
'    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Calculate the Weight item of the selection index's & complex class.
' Escape the comlex class's calculation, if the sheep/goat has a defect.
' Let the complex class equal to that of Weight, if the latter is lower than the former.
Private Sub FatTail(ByVal blnDefct As Boolean)
On Error GoTo ErrHnd
   Dim sngFatTail As Single
   Dim strIDCC As String
   With mobTblStdFatTail
      If mobShG.TblShG.IDSex = gobSetng.IDSexMl Then 'Male of female.
          sngFatTail = Index(CSng(mobShG.Apprs(mintAge1Yr, True).FatTail), CSng(.MaleMax), CSng(.MaleMin))
         If blnDefct = False Then strIDCC = Class(CSng(mobShG.Apprs(mintAge1Yr, True) _
            .FatTail), CSng(.MaleElite), CSng(.MaleClass1))
      Else
         sngFatTail = Index(CSng(mobShG.Apprs(mintAge1Yr, True).FatTail), CSng(.FemaleMax), CSng( _
            .FemaleMin))
         If blnDefct = False Then strIDCC = Class(CSng(mobShG.Apprs(mintAge1Yr, True) _
            .FatTail), CSng(.FemaleElite), CSng(.FemaleClass1))
      End If
   End With
'   With mobTblSelIdxCC
   msngSelIndx = msngSelIndx + sngFatTail * mobTblBrd.WtFatTail / gobSetng.Perc100 'Calculate the index.
   If blnDefct = False And strIDCC < mstrIDCompClass Then mstrIDCompClass = _
      strIDCC 'Remember a lower class.
'   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the Weight parameters.
Private Function VldWt() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set mobTblStdWt = New TblStd
   mobTblStdWt.Std = mobTblStdWt.StdWt
   Set obDatTbl = mobTblStdWt
   obDatTbl.Sel mobShG.TblShG.IDBrdBas
   VldWt = mobTblStdWt.VldParam 'Validate each parameter in mobTblStdWt.
   If VldWt Then
      mintParms = mintParms + 1
      If mobShG.WtWools.Exists(mintAge1Yr) Then '1-yr wt exists?
         If mobShG.WtWools(mintAge1Yr, True).WtAnnl = 0 Then
            VldWt = False 'No weight.
            Call DelFull 'Delete the selection index/complx class's record.
         Else
            VldWt = True 'Validation passed.
         End If
      Else
Debug.Assert 0 = 1 'Verify If
         VldWt = False 'No 1-yr wt.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the Grease parameters.
Private Function VldGrease() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set mobTblStdGrease = New TblStd
   mobTblStdGrease.Std = mobTblStdGrease.StdGrease
   Set obDatTbl = mobTblStdGrease
   obDatTbl.Sel mobShG.TblShG.IDBrdBas
   VldGrease = mobTblStdGrease.VldParam 'Validate each parameter in mobTblStdWt.
   If VldGrease Then
      mintParms = mintParms + 1
      If mobShG.WtWools.Exists(mintAge1Yr) Then '1-yr wool exists?
         If mobShG.WtWools(mintAge1Yr, True).GreaseAnnl = 0 Then
            VldGrease = False 'No grease wool.
            Call DelFull 'Delete the selection index/complx class's record.
         Else
            VldGrease = True 'Validation passed.
         End If
      Else
Debug.Assert 0 = 1 'Verify If
         VldGrease = False 'No 1-yr wool.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the Length parameters.
Private Function VldLeng() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set mobTblStdLeng = New TblStd
   mobTblStdLeng.Std = mobTblStdLeng.StdLeng
   Set obDatTbl = mobTblStdLeng
   obDatTbl.Sel mobShG.TblShG.IDBrdBas
   If mobTblStdLeng.VldParam Then 'Validate each parameter in mobTblStdWt.
      mintParms = mintParms + 1
      If mobShG.Apprs.Exists(mintAge1Yr) Then '1-yr appr exists?
         If mobShG.Apprs(mintAge1Yr, True).Leng = 0 Then
            VldLeng = False
               Call DelFull 'Delete the selection index/complx class's record.
         Else
            VldLeng = True 'Succeeded.
         End If
      Else
         VldLeng = False 'No 1-yr appr.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the Diameter parameters.
Private Function VldDiam() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set mobTblStdDiam = New TblStd
   mobTblStdDiam.Std = mobTblStdDiam.StdDiam
   Set obDatTbl = mobTblStdDiam
   obDatTbl.Sel mobShG.TblShG.IDBrdBas
   VldDiam = mobTblStdDiam.VldParam 'Validate each parameter in mobTblStdWt.
   If VldDiam Then
      mintParms = mintParms + 1
      If mobShG.Apprs.Exists(mintAge1Yr) Then '1-yr appr exists?
         If mobShG.Apprs(mintAge1Yr, True).Diam = "" Then
            VldDiam = False
               Call DelFull 'Delete the selection index/complx class's record.
         Else
            VldDiam = True 'Validation passed.
         End If
      Else
Debug.Assert 0 = 1 'Verify If
         VldDiam = False 'No 1-yr appr.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the FatTail parameters.
Private Function VldFatTail() As Boolean
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Set mobTblStdFatTail = New TblStd
Debug.Assert 0 = 1 'Verify
   mobTblStdFatTail.Std = mobTblStdFatTail.StdFatTail
Debug.Assert 0 = 1 'Verify
   Set obDatTbl = mobTblStdFatTail
Debug.Assert 0 = 1 'Verify
   obDatTbl.Sel mobShG.TblShG.IDBrdBas
   VldFatTail = mobTblStdFatTail.VldParam 'Validate each parameter in
   If VldFatTail Then                       'mobTblStdWt.
      mintParms = mintParms + 1
Debug.Assert 0 = 1 'Verify If
      If mobShG.Apprs.Exists(mintAge1Yr) Then '1-yr appr exists?
Debug.Assert 0 = 1 'Verify If
         If mobShG.Apprs(mintAge1Yr, True).FatTail = "" Then
            VldFatTail = False 'No FatTail content.
               Call DelFull 'Delete the selection index/complx class's record.
         Else
            VldFatTail = True 'Validation passed.
         End If
      Else
Debug.Assert 0 = 1 'Verify If
         VldFatTail = False 'No 1-yr appr.
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Scan defects for complex class.
' Count the recently updated number of defects, if the frmAppr invokes the calculation.
' In stead, count only the original number of defects just in case the same animal's
'  appraisals are simultaneously shown (& presumably updated but noy yet saved in the DB)
'  in the fmrAppr.
Private Function Defct() As Boolean
On Error GoTo ErrHnd
   Select Case mintFrmCallIdx
   Case gobSetng.FrmWtWoolIdx 'frmWtWool calls.
      If mobShG.Apprs.AllDefctOrig > 0 Then Defct = True
   Case gobSetng.FrmApprIdx 'frmAppr calls.
      If mobShG.Apprs.AllDefct > 0 Then Defct = True
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise the class in a non-standard fashion.
' Execute only once to prevent confusion.
Public Sub ClassInitialize(ByRef obShGParent As ShG)
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   If Not blnPassed Then 'Execute once.
      blnPassed = True
      Set mobShG = obShGParent
      mstrIDShG = obShGParent.IDShG
      Call DatTbl_Sel(obShGParent.IDShG) 'Select the selection index & complex class.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get IDShG
Public Property Get IDShG() As String
   IDShG = mstrIDShG
End Property

' Get SelIndx
Public Property Get SelIndx() As Single
   SelIndx = msngSelIndx
End Property

' Let & get IDCompClass
Public Property Let IDCompClass(ByVal strIDCompClass As String)
   mstrIDCompClass = strIDCompClass
End Property

Public Property Get IDCompClass() As String
   IDCompClass = mstrIDCompClass
End Property

' Unload weighings/appraisals, if loaded in the VldPoplt
Private Sub UnloadWtAppr()
On Error GoTo ErrHnd
   With mobShG
      If mblnDelWtWool Then
         mblnDelWtWool = False
         .WtWools.DelAll
         .PopltWtWool = False
      ElseIf mblnDelAppr Then
         mblnDelAppr = False
         .Apprs.DelAll
         .PopltAppr = False
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the frmInven form's dbcCompClass control, if the sheep/goat is shown in the
'  form.
Private Sub RefrshInven()
On Error GoTo ErrHnd
   If mobShG.HostShG Then
      With gobDatFrms.FrmHost(mobShG.IDShG, gobSetng.FrmShGNam)
         .CompClassDbc.BoundText = mstrIDCompClass
         Call .SwchCompClass(True) 'Switch dbcCompClass.
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the selection index/complx class's record, if any.
Private Sub DelFull()
On Error GoTo ErrHnd
   If Full Then
      Call DatTbl_Del
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the selection index & complex class on deletion of weighing/appraisal, if any of
'  the traits compose the selection index & complex class.
Public Sub DelWtAppr(ByVal strFrmHostIdx As Integer)
On Error GoTo ErrHnd
   Call PopltBrd 'Populate the mobTblBrd object.
   With mobTblBrd
      Select Case strFrmHostIdx
      Case gobSetng.FrmWtWoolIdx 'frmWtWool deletion.
         If .WtWt > 0 Then 'Weight.
            Call DelFull 'Delete, if full.
         ElseIf .WtGrease > 0 Then 'Grease wool.
            Call DelFull 'Delete, if full.
         End If
      Case gobSetng.FrmApprIdx 'frmAppr deletion.
         If .WtLeng > 0 Then 'Staple length.
            Call DelFull 'Delete, if full.
         ElseIf .WtDiam > 0 Then 'Fibre diameter.
            Call DelFull 'Delete, if full.
         ElseIf .WtFatTail > 0 Then 'FatTail content.
            Call DelFull 'Delete, if full.
         End If
      End Select
   End With
   Call RefrshInven 'Refresh the frmInven.dbcCompClass control.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Populate the mobTblBrd object. Execute once.
Private Sub PopltBrd()
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   Dim obDatTbl As DatTbl
'   Dim obDatTblSel As DatTblSel
   If Not blnPassed Then
      blnPassed = True
      Set mobTblBrd = New TblBrd
      Set obDatTbl = mobTblBrd
'      Set obDatTblSel = mobTblBrd
      obDatTbl.Sel mobShG.TblShG.IDBrdBas
'      obDatTblSel.Sel mobShG.TblShG.IDBrdBas
   End If
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

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

