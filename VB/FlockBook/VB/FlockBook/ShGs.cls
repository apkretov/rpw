VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ShGs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolShGs As Collection

'Dim mstrIDFrmLast As String
'Public IDFrmLast As String 'The last sheep/goat's ID used in forms.

' Initialise the module-level variables.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mcolShGs = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function COUNT() As Long
On Error GoTo ErrHnd
    COUNT = mcolShGs.COUNT
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new ShG object to the SheepGoats collection.
' Prior to the addition check whether the newly added sheep/goat object is shown in
'  another form. If that is the case increase its host forms' count & mark the host
'  form.
Public Sub Add(ByVal strIDShG As String, ByVal strFrmHostNam As String)
On Error GoTo ErrHnd
   Dim obShG As ShG
   Dim blnExists As Boolean
   For Each obShG In mcolShGs 'Check among the existing objects.
      With obShG
         If .IDShG = strIDShG Then
            blnExists = True 'Exit to update only the object's Host Form mark.
            Exit For
         End If
      End With
   Next obShG
   If Not blnExists Then 'Create a new object.
      Set obShG = New ShG
      obShG.IDShG = strIDShG
   End If
   With obShG 'Update the host count & mark.
      .HostCount = .HostCount + 1
      Select Case strFrmHostNam
      Case gobSetng.FrmShGNam
         .HostShG = True
      Case gobSetng.FrmLmKNam
         .HostLmK = True
      End Select
   End With
   If Not blnExists Then mcolShGs.Add obShG, strIDShG 'Add a new object.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
' Prior to the deletion check whether the deleted sheep/goat object is shown in
'  another form.
' If that is the case do the following:
'   decrease its host forms' count & erase the mark for the host form;
'   empty the WtWools, InhertDefcts, Mats, or LmKs collection.
Public Sub Del(ByVal strIDShG As String, ByVal strFrmHostNam As String, Optional ByVal _
   blnEscDel As Boolean = False)
On Error GoTo ErrHnd
   Dim obShG As ShG
   Dim blnExists As Boolean
   Dim blnExit As Boolean
   For Each obShG In mcolShGs 'Check among the existing objects.
      With obShG
         If .IDShG = strIDShG Then
            blnExists = True 'Mark existing.
            If .HostCount > 1 Then
               .HostCount = .HostCount - 1 'Update the host count & mark.
               Select Case strFrmHostNam
               Case gobSetng.FrmShGNam
                  .HostShG = False
               Case gobSetng.FrmLmKNam
                  .HostLmK = False
Debug.Assert 0 = 1 'Verify Dam in ShG
                  If Not blnEscDel Then .Dam.LmKs.DelAll 'Empty LmKs, unless escaped.
'                  If Not blnEscDel Then gobDams(strIDShG).LmKs.DelAll 'Empty LmKs, unless escaped.
               End Select
               blnExit = True 'Mark to exit the sub.
               Exit For
            End If
         End If
      End With
   Next
   If blnExists And blnExit = False Then mcolShGs.Remove strIDShG 'Remove, if exists &
Exit Sub                                                          'not exited.
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal strIDShG As String) As ShG
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
    Set Item = mcolShGs.Item(strIDShG)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' NewEnum must return the IUnknown interface of a collection's
' enumerator.
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
On Error GoTo ErrHnd
    Set NewEnum = mcolShGs.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if the ShG exists in the collection.
Public Function Exists(ByVal strIDShG As String) As Boolean
On Error GoTo ErrHnd
   Dim obShG As ShG
   For Each obShG In mcolShGs
      With obShG
         If .IDShG = strIDShG Then
            Exists = True 'Exists.
            Exit For 'Exit.
         End If
      End With
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
