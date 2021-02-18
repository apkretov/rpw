VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UtilDatFrm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mobDatFrm As DatFrm
Dim mobDatTbl As DatTbl

Dim mfrmFrmHost As Form
Dim mblnFrmFilld As Boolean

' Confirm changing DatFrm.IDFrm.
' Return True, if either confirmed or no change took place.
' If the change is denied restore the previous IDFrm in the DatFrm_IDCtl control just to
'  show it to the user.
Private Function ConfmIDFrmChan(ByVal strPromtChan1 As String, ByVal strPromtChan2 _
   As String) As Boolean
On Error GoTo ErrHnd
   Dim intResp As Integer
   With mobDatFrm
      If Trim$(.IDCtl) = .IDFrm Then
         ConfmIDFrmChan = True 'The same ID - confirmation is unnecessary.
      Else
         Beep
         intResp = MsgBox(strPromtChan1 & .IDFrm & strPromtChan2 & Trim$(.IDCtl) & "'?", _
            vbYesNo + vbQuestion, LoadResString(371)) 'Confirm the change.
         If intResp = vbYes Then
            ConfmIDFrmChan = True
         Else 'Denied - restore.
            .IDCtl = .IDFrm
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Complete the specified DatFrm's mode's operation.
' Clear contols in the Del mode.
' Return the focus to the IDCtl control.
Public Sub Ok_Click(ByRef dblBrsCtl As DataList, ByVal strPromtDel As String)
On Error GoTo ErrHnd
   Dim intResp As Integer
   Dim strPromt As String
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd, gobSetng.ModeEdit 'Validate 'data in an Add or Edit mode.
         If .Vld Then
            .FrmToDB
            .Cancel False
            dblBrsCtl.SetFocus
         End If
      Case gobSetng.ModeDel 'The Del mode.
         strPromt = strPromtDel & Trim$(.IDCtl) & "'?"
         Beep
         intResp = MsgBox(strPromt, vbYesNoCancel + vbQuestion, LoadResString(372))
         Select Case intResp 'Yes, No, or Cancel reaction.
         Case vbYes
            .FrmToDB
            .Cancel True
            .IDCtl = gobDatFrms.IDFrmLast(mfrmFrmHost.Name) 'Set the last ID.
            dblBrsCtl.SetFocus
         Case vbNo
            mfrmFrmHost.cmdOK.SetFocus
         Case vbCancel
            .Cancel True
            dblBrsCtl.SetFocus
         End Select
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cancel the current changes.
' Switch controls.
' Nullify the data form's marks.
' Re-register the data form under zero-length-string ID.
' Switch the menu & toolbar.
' Reset the gobMsgInst object.
Public Sub DatFrm_Cancel(ByVal blnCtlClear As Boolean)
On Error GoTo ErrHnd
   mobDatFrm.SwchCtlFill False, True 'Shwitch the controls.
   mobDatFrm.IsDirty = False
   mblnFrmFilld = False
   With mobDatFrm
      .RegistFrm "", True 'Re-register the data form.
      .IDFrm = "" 'THIS OPERATION LOOKS UNNECESSARY BUT KEEP IT EXPLICIT.
      If blnCtlClear Then .CtlClear 'Clear the controls, if required.
      Call frmMDI.SwchMnuMode(.Mode) ', False) 'Switch the menu/tool bar buttons.
   End With
   Call Util.FrmCapt(mobDatFrm, False) 'Reset the form's caption
   gobMsgInst.Rest mfrmFrmHost 'Reset gobMsgInst.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the references to
'  - data form;
'  - data table;
'  - host form.
Public Sub InitCls(ByRef frmForm As Form, ByRef obDatTbl As DatTbl)
On Error GoTo ErrHnd
   Set mobDatFrm = frmForm 'Data form.
   Set mobDatTbl = obDatTbl 'Data table.
   Set mfrmFrmHost = frmForm 'Host form.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Initialise the module-level variables.
Private Sub Class_Initialize()
   Set mobDatFrm = New DatFrm
End Sub

' Write the controls' content to the the mobTbl* object.
Public Sub DatFrm_FrmToDB(ByVal strPromtChan1 As String, ByVal strPromtChan2 As String)
On Error GoTo ErrHnd
   gobDatFrms.UnldEmpt mobDatFrm.IDFrm, mobDatFrm.FrmHostNam
   With mobDatFrm
      If .Mode = gobSetng.ModeDel Then
         mobDatTbl.Del 'Deletion.
      Else
         .CtlRead 'Read the data.
         Select Case .Mode 'Accomplish the mode's opertation.
         Case gobSetng.ModeAdd
            mobDatTbl.Ins
         Case gobSetng.ModeEdit
            If ConfmIDFrmChan(strPromtChan1, strPromtChan2) Then mobDatTbl.Upd               'Verify a IDFrm change.
         End Select
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Shwitch on/off the data form's controls depending on whether the IDCtl control is
'  filled.
Public Sub DatFrm_SwchCtlFill(ByVal blnEnable As Boolean, ByVal blnEnableID As Boolean, _
   ByVal strIDLblNam As String, ByVal strBrsLblNam As String, ByVal strBrsCtlNam _
   As String)
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   For Each ctlCtl In mfrmFrmHost.Controls 'Cycle through all controls to switch.
      If TypeOf ctlCtl Is Label And ctlCtl.Name = strIDLblNam Then
         GoTo NextCtl 'Skip labels except ID one.
      ElseIf TypeOf ctlCtl Is PictureBox Then
         GoTo NextCtl 'Skip the picture box.
      ElseIf TypeOf ctlCtl Is Line Then
         GoTo NextCtl 'Skip the line.
      Else
         Select Case ctlCtl.Name 'Switch on/off the ID control explicitly.
         Case mobDatFrm.IDCtl.Name
            ctlCtl.Enabled = blnEnableID 'ID control.
         Case strBrsCtlNam, strBrsLblNam
            ctlCtl.Enabled = Not blnEnable 'ID button - opposite to other controls.
         Case mfrmFrmHost.cmdCancel.Name
            GoTo NextCtl 'Skip cmdCancel.
         Case Else
            ctlCtl.Enabled = blnEnable 'Other controls.
         End Select
      End If
NextCtl:
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Register the data form in the gobDatFrms collection under a new ID. Delete it under the
'  previous ID, if any, & register under a new one.
Public Sub DatFrm_RegistFrm(ByVal strNewIDFrm As String, ByVal blnDelPrev As Boolean)
On Error GoTo ErrHnd
   If blnDelPrev Then gobDatFrms.Del mobDatFrm.IDFrm, mfrmFrmHost.Name 'Delete.
   gobDatFrms.Add Trim$(strNewIDFrm), mfrmFrmHost.Name 'Register.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select data from the DB to fill the data form.
Public Sub DatFrm_DBtoFrm()
On Error GoTo ErrHnd
   With mobDatFrm
      Select Case .Mode
      Case gobSetng.ModeAdd 'Add mode.
         mobDatTbl.EscSelFail = True 'Cancel the CountrWrong message.
         mobDatTbl.Sel .IDFrm 'Populate the data.
         mobDatTbl.EscSelFail = False 'Reset.
      Case gobSetng.ModeEdit, gobSetng.ModeDel 'Edit/Del mode
         mobDatTbl.Sel .IDFrm 'Populate the data.
         If mobDatTbl.Full Then 'Check if the specified item exists.
            .CtlWrite 'Fill the form.
         End If
      End Select
   End With
   Call Util.FrmCapt(mobDatFrm, True) 'Set the form's caption.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the relevant to data form forms menu's & tool bar's buttons.
' Format the IDCtl control.
' Fill the form & begin the mode's operation.
Public Sub IDCtl_KeyPress(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Dim obSetngFrm As SetngFrm
   Dim intLeng As Integer
   Dim blnFail As Boolean
   With mobDatFrm
      Call frmMDI.SetIsDirtyMnu(mobDatFrm) 'Set the menu & IsDirty mark.
'      Call frmMDI.SetIsDirtyMnu(mfrmFrmHost.IsDirty, .Mode)
'      mfrmFrmHost.IsDirty = True 'This duplicates SetIsDirtyMnu because its ByRef
      If intKeyAscii = gobFormtCtl.AscEnter Then 'blnIsDirty doesn't refer to IsDirty.
         intKeyAscii = 0 'Cancel Enter
         If Not mblnFrmFilld Then 'Proceed, unless filled.
            intLeng = Len(Trim$(.IDCtl))
            If intLeng = 0 Then
               .Cancel False 'Cancel the changes.
               .IDCtl.SetFocus
            Else 'Proceed corresponding to the mode.
               .RegistFrm Trim$(.IDCtl), True  'Register the form.
               If gobMsgInst.DuplFrm Then 'Avoid duplication by ivoking the LostFocus
                  mfrmFrmHost.cmdCancel.SetFocus      'procedure.
               Else
                  .DBtoFrm 'Fill the form in an Edit/Del mode.
                  Select Case .Mode 'Check the operation's feedback by mode.
                  Case gobSetng.ModeEdit, gobSetng.ModeDel 'Edit/Del modes.
                     If mobDatTbl.Full Then
                        mblnFrmFilld = True 'Mark filling the form.
                     Else
                        blnFail = True 'Mark the error.
                     End If
                  Case gobSetng.ModeAdd 'Add mode.
                     If mobDatTbl.Full Then 'Adding a duplicate.
                        blnFail = True 'Mark the error.
                        MsgBox LoadResString(73), vbExclamation, LoadResString(50)
                     End If
                  End Select
                  If Not blnFail Then
                     Call Util.SyncBrs(mobDatFrm) 'Syncronise the settings form's browsing list.
                     .SwchCtlMode 'Switch controls by mode.
                  Else
                     .Cancel False 'Cancel the current changes, if any.
                     .IDCtl.SetFocus
                  End If
               End If
            End If
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch the controls by mode & to save a new IDFrm.
Public Sub DatFrm_SwchCtlMode(ByVal strBrsLblNam As String, ByVal strBrsCtlNam _
   As String, ByVal strCtlNextNam As String)
On Error GoTo ErrHnd
   With mfrmFrmHost
         Select Case mobDatFrm.Mode 'Switch by mode.
         Case gobSetng.ModeAdd
            mobDatFrm.SwchCtlFill True, False
            .Controls(strCtlNextNam).SetFocus 'Focus the control next to IDCtl.
         Case gobSetng.ModeEdit
            mobDatFrm.SwchCtlFill True, True
            mobDatFrm.IDCtl.SetFocus
         Case gobSetng.ModeDel
            mobDatFrm.IDCtl.Enabled = False
            .Controls(strBrsCtlNam).Enabled = False
            .cmdOK.Enabled = True
            .cmdOK.SetFocus
         End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload the data form, if it's clear.
' Cancel the changes.
' Clear the controls.
' Return the focus to the IDCtl control.
Public Sub Cancel_Click(ByRef dblBrsCtl As DataList)
On Error GoTo ErrHnd
   If mobDatFrm.IsDirty Then 'Cancel.
      With mobDatFrm
         .Cancel True
         With .IDCtl
            .Text = gobDatFrms.IDFrmLast(mfrmFrmHost.Name) 'Set the last ID.
            mfrmFrmHost.cmdCancel.SetFocus 'Focus cmdCancel to invoke the IDCtl's
         End With
         dblBrsCtl.SetFocus
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Clear the data form's controls.
Public Sub DatFrm_CtlClear()
On Error GoTo ErrHnd
   Dim ctlCtl As Control
   For Each ctlCtl In mfrmFrmHost.Controls
      If TypeOf ctlCtl Is TextBox Then
         ctlCtl.Text = ""
      ElseIf TypeOf ctlCtl Is DataCombo Then
          ctlCtl.Text = ""
      End If
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Execute the IDCtl control's LostFocus event procedure.
' Prevent opening another duplicate data form.
' Reset the gobMsgInst object for later use.
' Unless the Util.DuplFrmtRest procedure unloads the data form complete switching the
'  controls in the Edit mode after filling the form to restrict the access to the this
'  control until saving or canceling.
Public Sub IDCtl_LostFocus()
On Error GoTo ErrHnd
   Call Util.DuplFrmtRest(mfrmFrmHost, mobDatFrm.IDCtl)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the window state, if changed.
' Resize the data form's data list, grid, Remark, picBrn controls & move the buttons.
Public Sub Form_Resize(ByRef dblBrsCtl As DataList, Optional ByVal strGridNam As String)
On Error GoTo ErrHnd
   Dim lngLeft As Long
   With mfrmFrmHost
      gobSetng.FrmChldStat = .WindowState 'Save the state.
      .txtRemark.Width = CtlWdth(.txtRemark, gobSetng.IndtCtlRght) 'Change the width.
      lngLeft = .ScaleWidth - .cmdOK.Width - .cmdCancel.Width - gobSetng _
         .IndtCtlOkCanc - gobSetng.IndtCtlRght
      .cmdOK.Left = IIf(lngLeft > 0, lngLeft, 0) 'Must be positive.
      lngLeft = .ScaleWidth - .cmdCancel.Width - gobSetng.IndtCtlRght
         gobFormtCtl.ResizeLin mfrmFrmHost, .linBtn(0), .linBtn(1)
      .cmdCancel.Left = IIf(lngLeft > 0, lngLeft, 0) 'Must be positive.
      .picBtn.ZOrder 0 'Keep picBtn on top.
      If strGridNam <> "" Then 'Proceed, if the grid is specified.
         .Controls(strGridNam).Width = CtlWdth(.Controls(strGridNam), gobSetng _
            .IndtCtlRght) 'Change the width.
         Call CtlHght(.Controls(strGridNam)) 'Change the height.
         Call GridColWdth(.Controls(strGridNam)) 'Change the grid columns.
      End If
   End With
   Call CtlHght(dblBrsCtl) 'Change the height.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus, if the field is left blank in the Edit mode after changing the ID.
' Differentiate MaskEditBox (frmFarm) IDCtl TextBox (other settings forms).
Public Sub IDCtl_Validate(ByRef blnCancel As Boolean, ByVal strLblCapt As String)
On Error GoTo ErrHnd
   Select Case mfrmFrmHost.Name
   Case gobSetng.FrmFarmNam 'frmFarm.
      Call VldIDFarm(blnCancel, strLblCapt)
   Case Else 'Others.
      Call VldIDMisc(blnCancel, strLblCapt)
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus to the IDCtl text box, if the field is left blank in the Edit mode
'  after changing the ID.
Private Sub VldIDMisc(ByRef blnCancel As Boolean, ByVal strLblCapt As String)
On Error GoTo ErrHnd
   If mblnFrmFilld Then 'Filled?
      If mobDatFrm.IDCtl.Text = "" Then 'Blank?
         If mobDatFrm.Mode = gobSetng.ModeEdit Then 'Edit mode?
            blnCancel = True
            Call Util.MissParam(mobDatFrm.IDCtl, strLblCapt) 'Message & focus.
         End If
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restrict the focus to the IDCtl text box, if the field is left blank in the Edit mode after changing the ID.
Private Sub VldIDFarm(ByRef blnCancel As Boolean, ByVal strLblCapt As String)
On Error GoTo ErrHnd
   If mblnFrmFilld Then
      If mobDatFrm.Mode = gobSetng.ModeEdit Then gobFormtCtl.VldIDCtlFarm mobDatFrm _
         .IDCtl, strLblCapt, blnCancel
   Else
      blnCancel = Not gobFormtCtl.VldIDFarm(mobDatFrm.IDCtl, strLblCapt)
'      gobFormtCtl.VldIDFarm mobDatFrm.IDCtl, strLblCapt, blnCancel
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Disable the grid, if any, in the Add mode since there are not dependent data yet to
' show in it.
Public Sub SwchGridMode(ByRef dgdCtl As DataGrid)
On Error GoTo ErrHnd
   If mobDatFrm.Mode = gobSetng.ModeAdd Then dgdCtl.Enabled = False
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the control's width on the host form's Resize event.
Private Function CtlWdth(ByVal ctlCtl As Control, ByVal lngIndtRght As Long) As Long
On Error GoTo ErrHnd
   Dim lngWdth As Long
   lngWdth = mfrmFrmHost.ScaleWidth - ctlCtl.Left - lngIndtRght
   CtlWdth = IIf(lngWdth > 0, lngWdth, 0) 'The width must be positive.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Change the control's height on the host form's Resize event.
Private Sub CtlHght(ByRef ctlCtl As Control)
On Error GoTo ErrHnd
   Const intDistGridPic As Integer = 90 'The distance between the grid & button picture.
   Dim lngHght As Long
   lngHght = mfrmFrmHost.ScaleHeight - ctlCtl.Top - intDistGridPic - mfrmFrmHost _
      .picBtn.Height
   ctlCtl.Height = IIf(lngHght > 0, lngHght, 0) 'The height must be positive.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Change the grid columns width.
Private Sub GridColWdth(ByRef dgdCtl As DataGrid)
On Error GoTo ErrHnd
   Const intWdthScrl As Integer = 180 'The scroll bar's width.
   Dim colColumn As Column
   Dim lngWdth As Long
   If dgdCtl.Width > intWdthScrl Then 'Proceed, if wider than the sroll bar.
      lngWdth = dgdCtl.Width / dgdCtl.Columns.Count - intWdthScrl 'The column width.
      lngWdth = IIf(lngWdth > 0, lngWdth, 0) 'Must be positive.
      For Each colColumn In dgdCtl.Columns
         colColumn.Width = lngWdth
      Next
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the grid's Ado control's record source; refresh it.
' Resize the dependent grid's columns.
Public Sub GridRecSrc(ByRef adoCtl As Adodc, ByVal strRecSrc As String, ByRef dgdCtl _
   As DataGrid)
On Error GoTo ErrHnd
   adoCtl.RecordSource = strRecSrc
   adoCtl.Refresh
   Call GridColWdth(dgdCtl) 'Change the grid columns width.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Resize the specified tab control with grids.
Public Sub TabResize(ByRef tabCtl As SSTab, ByRef dgdCtl1 As DataGrid, ByRef dgdCtl2 _
   As DataGrid, Optional ByRef dgdCtl3 As DataGrid)
On Error GoTo ErrHnd
   Const intGridTop As Integer = 360 '420 'The grids' top.
   Const intIndt As Integer = 60 '120 'The tab-to-grid indent.
   Const intCountTab3 As Integer = 3 '3 tab count.
   Dim lngGridWdth As Long
   Dim lngGridHght As Long
   tabCtl.Width = CtlWdth(tabCtl, gobSetng.IndtCtlRght) 'Resize the tab.
   Call CtlHght(tabCtl)
   lngGridWdth = tabCtl.Width - intIndt * 2 'Compute the grids' width/height.
   lngGridHght = tabCtl.Height - intGridTop - intIndt
   If lngGridWdth > 0 And lngGridHght > 0 Then 'Proceed, if the sides are positive.
      dgdCtl1.Width = lngGridWdth 'Resize the grids.
      dgdCtl2.Width = lngGridWdth
      dgdCtl1.Height = lngGridHght
      dgdCtl2.Height = lngGridHght
      Call GridColWdth(dgdCtl1) 'Resize the grids' columns.
      Call GridColWdth(dgdCtl2)
      If tabCtl.Tabs = intCountTab3 Then 'Resirze grid 3.
         dgdCtl3.Width = lngGridWdth
         dgdCtl3.Height = lngGridHght
         Call GridColWdth(dgdCtl3)
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
