VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Offsps"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolOffsps As Collection
Dim mstrIDDam As String
Dim mintCycle As Integer
'Dim mintCycleAct As Integer
Dim mintNoLmKAct As Integer

Dim mobTblOffspTest As TblOffsp

Public Edited As Boolean 'Mark the Edit mode for the Offspring collection's member.

' Let IDDam in this class & in its inbuilt ones.
Public Property Let IDDam(ByVal strIDDam As String)
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   mstrIDDam = strIDDam
   For Each obTblOffsp In mcolOffsps
      obTblOffsp.IDDam = strIDDam
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Let Cycle in this class & in its inbuilt ones.
Public Property Let Cycle(ByVal intCycle As Integer)
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   mintCycle = intCycle
   For Each obTblOffsp In mcolOffsps
      obTblOffsp.Cycle = intCycle
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Create a new mcolOffsps object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolOffsps = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolOffsps.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new obTblOffsp object to the Offsps collection.
Public Sub Add(intNoLmKOrig As Integer, intNoLmK As Integer, ByVal strIDLmK As String, _
   ByVal strIDSex As String, ByVal strSex As String, ByVal sngWtBirth As Single, ByVal _
   strIDLiv As String, ByVal strLiv As String)
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim strKey As String
   Set obTblOffsp = New TblOffsp
   With obTblOffsp 'Fill the object.
      .IDDam = mstrIDDam
      .Cycle = mintCycle
      .NoLmKOrig = intNoLmKOrig
      .NoLmK = intNoLmK
      .IDLmK = strIDLmK
      .IDSex = strIDSex
      .Sex = strSex
      .WtBirth = sngWtBirth
      .IDLiv = strIDLiv
      .Liv = strLiv
   End With
   strKey = mstrIDDam & CStr(mintCycle) & CStr(intNoLmK) 'Create a unique key to add
   mcolOffsps.Add obTblOffsp, strKey             'the object to the collection.
   mintNoLmKAct = intNoLmK
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal intNoLmK As Integer)
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDDam & CStr(mintCycle) & CStr(intNoLmK)
   mcolOffsps.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal intNoLmK As Integer, ByVal blnEscSaveNoLmK As Boolean) _
   As TblOffsp
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDDam & CStr(mintCycle) & CStr(intNoLmK)
   Set Item = mcolOffsps.Item(strKey)
   If Not blnEscSaveNoLmK Then mintNoLmKAct = intNoLmK 'Save the active offspring, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' NewEnum must return the IUnknown interface of a collection's
'   enumerator.
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
On Error GoTo ErrHnd
    Set NewEnum = mcolOffsps.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
Public Function Last() As TblOffsp
On Error GoTo ErrHnd
   Dim obTblOffsp As TblOffsp
   Dim strKey As String
   Dim intNoLmKLast As Integer
   For Each obTblOffsp In mcolOffsps 'Cycle through all members to get the last item.
      intNoLmKLast = obTblOffsp.NoLmK
   Next
   strKey = mstrIDDam & CStr(mintCycle) & CStr(intNoLmKLast) 'Create a unique key.
   Set Last = mcolOffsps.Item(strKey)
   mintNoLmKAct = intNoLmKLast 'Mark the active offspring.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's active item.
Public Function Act() As TblOffsp
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDDam & CStr(mintCycle) & CStr(mintNoLmKAct)
   Set Act = mcolOffsps.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the active offspring No.
Public Property Let NoLmKAct(ByVal intNoLmKAct As Integer)
   mintNoLmKAct = intNoLmKAct
End Property

' Return a new NoLambKid number that is equal to
'  - the last NoLambKid + 1, if there are offsprings;
'  - 1, if there are no offsprings yet.
Public Function NoLmKNew() As Integer
On Error GoTo ErrHnd
   If mcolOffsps.Count = 0 Then
      NoLmKNew = 1 'No offsprings.
   Else
      NoLmKNew = Last.NoLmK + 1 'Increase NoLambKid.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
