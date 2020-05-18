VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "DatFrms"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Type IDFrmLast
   ShG As String
   Coutr As String
   Obl As String
   Rayn As String
   TwnVll As String
   Pers As String
   Farm As String
   Brd As String
   Defct As String
End Type
Dim mudtIDFrmLast As IDFrmLast

Dim mcolDatFrms As Collection

' Initialise module-level variables.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mcolDatFrms = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolDatFrms.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new data form to the DatFrms collection.
' Prevent opening the same form for the same sheep/goat.
' Remember the last non-zero-length ID.
Public Sub Add(ByVal strIDFrm As String, ByVal strFrmNam As String)
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   Dim strKey As String
   Dim blnExit As Boolean
   If Exists(strIDFrm, strFrmNam) Then 'Prevent duplication.
      gobMsgInst.DuplFrm = True 'feedback on the DuplFrm error & exit.
      Call FrmHostFoc(strIDFrm, strFrmNam) 'Focus the original form.
      blnExit = True 'Exit the sub.
   End If
   If Not blnExit Then 'Proceed, unless exited above.
      Set obDatFrm = frmMDI.ActiveForm 'Fill the obDatFrm object & add it to the
      With obDatFrm                    'collection.
         .IDFrm = strIDFrm
         .FrmHostNam = strFrmNam
      End With
      strKey = strIDFrm & strFrmNam 'Create a unique key.
      mcolDatFrms.Add obDatFrm, strKey
      If strIDFrm <> "" Then Call IDFrmLastSet(strIDFrm, strFrmNam) 'The last ID
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
' On the receint duplication on an attempt to add a new data form, merely escape the
'  Remove method. Since the duplicating form's Unload event calls this Del method no
'  removing of this unregistered data from the DatFrms collection is needed.
Public Sub Del(ByVal strIDFrm As String, ByVal strFrmNam As String)
On Error GoTo ErrHnd
   Dim strKey As String
   If Not gobMsgInst.DuplFrm Then
      If Exists(strIDFrm, strFrmNam) Then 'Proceed, if exists.
         strKey = strIDFrm & strFrmNam
         mcolDatFrms.Remove strKey
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal strIDFrm As String, ByVal strFrmNam As String) As DatFrm
Attribute Item.VB_UserMemId = 0
   On Error GoTo ErrHnd
   Dim strKey As String
   strKey = strIDFrm & strFrmNam 'Create a unique key to identify the object in the
   Set Item = mcolDatFrms.Item(strKey)                                  'collection.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' NewEnum must return the IUnknown interface of a collection's enumerator.
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
On Error GoTo ErrHnd
    Set NewEnum = mcolDatFrms.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the reference to the data form where the specified sheep/goat resides.
' The procedure is obsolete. Use Item.FrmHost instead.
Public Function FrmHost(strIDFrm As String, ByVal strFrmNam As String) As Form
On Error GoTo ErrHnd
   Dim frmForm As Form
   Dim obDatFrmTest As DatFrm
   For Each frmForm In Forms
      If frmForm.Name = strFrmNam Then
         Set obDatFrmTest = frmForm
         If obDatFrmTest.IDFrm = strIDFrm Then
            Set FrmHost = frmForm
            Exit For
         End If
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Change the data forms' ID controls.
Private Sub ChanIDCtl(ByVal strIDFrmOrig As String, ByVal strIDFrmNew As String)
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   For Each obDatFrm In mcolDatFrms 'Cycle to identify the specified ID.
      If obDatFrm.IDFrm = strIDFrmOrig Then
         obDatFrm.IDCtl = strIDFrmNew 'Change the ID control.
      End If
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the last IDFrm for ShG-relevant & settings forms.
Public Property Get IDFrmLast(ByVal strFrmNam As String) As String
On Error GoTo ErrHnd
   With gobSetng
      Select Case strFrmNam 'ShG-relevant forms.
      Case .FrmShGNam, .FrmCertNam 'ShG-relevant form.
         IDFrmLast = mudtIDFrmLast.ShG
      Case .FrmCountrNam
         IDFrmLast = mudtIDFrmLast.Coutr
      Case .FrmOblNam
         IDFrmLast = mudtIDFrmLast.Obl
      Case .FrmRaynNam
         IDFrmLast = mudtIDFrmLast.Rayn
      Case .FrmTwnVllNam
         IDFrmLast = mudtIDFrmLast.TwnVll
      Case .FrmPersNam
         IDFrmLast = mudtIDFrmLast.Pers
      Case .FrmFarmNam
         IDFrmLast = mudtIDFrmLast.Farm
      Case .FrmBrdStdNam
         IDFrmLast = mudtIDFrmLast.Brd
      Case .FrmDefctNam
         IDFrmLast = mudtIDFrmLast.Defct
      End Select
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Let the last IDFrm for ShG-relevant & settings forms.
Public Sub IDFrmLastSet(ByVal strIDFrmLast As String, ByVal strFrmNam As String)
On Error GoTo ErrHnd
   With gobSetng
      Select Case strFrmNam 'ShG-relevant forms.
      Case .FrmShGNam, .FrmCertNam 'ShG-relevant form.
         mudtIDFrmLast.ShG = strIDFrmLast
      Case .FrmCountrNam
         mudtIDFrmLast.Coutr = strIDFrmLast
      Case .FrmOblNam
         mudtIDFrmLast.Obl = strIDFrmLast
      Case .FrmRaynNam
         mudtIDFrmLast.Rayn = strIDFrmLast
      Case .FrmTwnVllNam
         mudtIDFrmLast.TwnVll = strIDFrmLast
      Case .FrmPersNam
         mudtIDFrmLast.Pers = strIDFrmLast
      Case .FrmFarmNam
         mudtIDFrmLast.Farm = strIDFrmLast
      Case .FrmBrdStdNam
         mudtIDFrmLast.Brd = strIDFrmLast
      Case .FrmDefctNam
         mudtIDFrmLast.Defct = strIDFrmLast
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return True, if the data form exists in the collection.
Public Function Exists(ByVal strIDFrm As String, ByVal strFrmNam As String) _
   As Boolean
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   For Each obDatFrm In mcolDatFrms
      With obDatFrm
         If .IDFrm = strIDFrm Then
            If .FrmHostNam = strFrmNam Then
               Exists = True 'Exists.
               Exit For 'Exit.
            End If
         End If
      End With
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the reference to any data form from the collection to focus it from the
'  frmBrsShG after another calling data form has been uloaded.
Public Function FrmHostAny() As Form
On Error GoTo ErrHnd
   Dim obDatFrm As DatFrm
   Dim frmForm As Form
   For Each obDatFrm In mcolDatFrms
      With obDatFrm 'Get the 1st encountered form.
         Set FrmHostAny = FrmHost(.IDFrm, .FrmHostNam)
      End With
      Exit For
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Focus the specified data form. Expand it, if minimised.
Public Sub FrmHostFoc(ByVal strIDFrm As String, ByVal strFrmNam As String)
On Error GoTo ErrHnd
   Dim frmForm As Form
   Set frmForm = Item(strIDFrm, strFrmNam).FrmHost
   With frmForm
      .SetFocus
      If .WindowState = vbMinimized Then .WindowState = vbNormal
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Unload another empty data form while the specified one's data are being saved to the
'  DB. Because after the data will have been saved the specified form itself will become
'  empty, so this procedure prevents duplication.
Public Sub UnldEmpt(ByVal strIDFrm As String, ByVal strFrmNam As String)
On Error GoTo ErrHnd
   With gobDatFrms
      If Exists("", strFrmNam) Then Unload FrmHost("", strFrmNam)
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
