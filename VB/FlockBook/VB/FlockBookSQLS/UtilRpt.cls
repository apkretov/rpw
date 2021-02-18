VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UtilRpt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mfrmFrm As Form

' Show the specified report form's report. Call the form's CmdOk1 procedure & CmdOk2
'  one by enabling the fmrMDI.tmrTimer.
Public Sub Show()
On Error GoTo ErrHnd
   If mfrmFrm.CmdOK1 Then 'The 1st procedure.
      With frmMDI
         Set .TimerObj = mfrmFrm 'Specify the arguments for the timer.
         .TimerProc = "CmdOK2"
         .tmrTimer.Enabled = True 'Inovke the 2nd procedure.
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open/requery the by-reference recordset for a report.
' Return True, if succeeds.
Public Function Requery(ByRef rstRepRst As ADODB.Recordset) As Boolean
On Error GoTo ErrHnd
   Dim intResp As Integer
   With rstRepRst
      Do
         Select Case .State 'Closed or open state.
         Case adStateClosed
            .Open
            Requery = True 'Succeeded.
            Exit Do
         Case adStateOpen
            .Requery
            Requery = True 'Succeeded.
            Exit Do
         Case adStateConnecting, adStateExecuting, adStateFetching
            Call SwchBtnMouse(mfrmFrm, True) 'Switch buttons & mouse.
            intResp = MsgBox(LoadResString(80), vbQuestion + vbRetryCancel, _
               LoadResString(81))
            Call frmMDI.StatusMsg(False) 'Remove message.
         End Select
      Loop While intResp = vbRetry
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
   Call ErrHnd 'Handle the report's error.
End Function

' Check if there are records it the specified validation recordset to show in the report.
' Return True, if succeeds.
Public Function Vld(ByRef rstValid As ADODB.Recordset, ByVal strIDFarm As String) _
   As Boolean
On Error GoTo ErrHnd
   With rstValid
      Select Case .State 'Refresh the recordset.
      Case adStateClosed
         .Open
      Case adStateOpen 'This is unnecessary (the recorset is closed below), but keep it
         .Requery      'explicit just in case.
      End Select
      If .EOF And .BOF Then
         Call SwchBtnMouse(mfrmFrm, True) 'Switch buttons & mouse.
         MsgBox LoadResString(175) & strIDFarm & LoadResString(176), vbExclamation, _
            LoadResString(172)
         Call frmMDI.StatusMsg(False) 'Remove message.
      Else
         Vld = True 'Succeeded.
      End If
      .Close 'Close the recordset.
   End With
Exit Function
ErrHnd:
   MsgBox Err.Description
   Call ErrHnd 'Handle the report's error.
End Function

' Set the module-level form to operate on.
Public Property Set Frm(ByRef frmFrm As Form)
   Set mfrmFrm = frmFrm
End Property

' Handle the report's error:
'  - switch the Ok & Cancel buttons & mouse;
'  - remove the Report Preparation message.
Public Sub ErrHnd()
On Error GoTo ErrHnd
   Dim obUtilDB As UtilDB
   Set obUtilDB = New UtilDB
   obUtilDB.BusySet False 'Reset the busy mark.
   Call SwchBtnMouse(mfrmFrm, True) 'Switch buttons & mouse.
   Call frmMDI.StatusMsg(False) 'Remove message.
Exit Sub
ErrHnd:
   MsgBox Err.Description
   Resume Next 'Complete handling the outer error.
End Sub
