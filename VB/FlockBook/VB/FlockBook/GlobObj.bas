Attribute VB_Name = "GlobObj"
Option Explicit

Public gcnnConn As ADODB.Connection
Public gdbDB As Database
'Public gcnnConnClnt As ADODB.Connection
Public gobDatFrms As DatFrms
Public gobShGs As ShGs
Public gobTblCtrlParam As TblCtrlParam
Public gobMsgInst As MsgInst
Public gobSetng As Setng
Public gobFormtCtl As FormtCtl

Public Type DatFrmTp
   IDFrm As String
   Mode As Integer
   FrmHostNam As String
   FrmHostCaptOrig As String
   FrmFilld As Boolean
   IsDirty As Boolean
End Type

' Start the application.
Public Sub Main()
On Error GoTo ErrHnd
   Load frmSplash
   frmSplash.Show vbModal
   frmMDI.Show
   Load frmLogon
   frmLogon.Show vbModal
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
