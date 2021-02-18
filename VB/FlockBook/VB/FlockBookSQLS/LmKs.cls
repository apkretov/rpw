VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "LmKs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolLmKs As Collection
Dim mstrIDDam As String
Dim mintCycleAct As Integer

' Let IDDam in this class & in its inbuilt ones.
Public Property Let IDDam(ByVal strIDDam As String)
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   mstrIDDam = strIDDam
   For Each obTblLmK In mcolLmKs
      obTblLmK.IDDam = strIDDam
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Create a new mcolLmKs object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolLmKs = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
Attribute Count.VB_MemberFlags = "40"
On Error GoTo ErrHnd
    Count = mcolLmKs.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Public Sub Add(ByVal intCycle As Integer, ByVal intCycleLmK As Integer, ByVal _
   dtmDateLmKOrig As Date, ByVal dtmDateLmK As Date, ByVal intTypeBirth As Integer, _
   ByVal intAbort As Integer)
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   Dim strKey As String
   Set obTblLmK = New TblLmK
   With obTblLmK 'Fill the object.
      .IDDam = mstrIDDam
      .Cycle = intCycle
      .CycleLmK = intCycleLmK
      .DateLmKOrig = dtmDateLmKOrig
      .DateLmK = dtmDateLmK
      .TypeBirth = intTypeBirth
      .Abort = intAbort
   End With
   strKey = mstrIDDam & CStr(intCycle) 'Create a unique key.
   mcolLmKs.Add obTblLmK, strKey
   mintCycleAct = intCycle 'Mark the active cycle.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal intCycle As Integer)
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify w/o IDDam
   Dim strKey As String
Debug.Assert 0 = 1 'Verify w/o IDDam
   strKey = mstrIDDam & CStr(intCycle)
   mcolLmKs.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete all members from the collection.
' First make sure that there are any members in the collection to delete & set the
'  PopltLmK mark to False; otherwise escape.
Public Sub DelAll()
On Error GoTo ErrHnd
    Dim obTblLmK As TblLmK
    Dim strKey As String
    Dim strIDDam As String
    ' Check the members' quantity.
    If mcolLmKs.Count > 0 Then
        ' Delete.
        For Each obTblLmK In mcolLmKs
            With obTblLmK
                ' Remember the dam' ID.
                If strIDDam = "" Then strIDDam = .IDDam
                strKey = .IDDam & .Cycle
                mcolLmKs.Remove strKey
            End With
        Next obTblLmK
        gobShGs(strIDDam).Dam.PopltLmK = False ' Reset PopltLmK.
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal intCycle As Integer, ByVal blnEscSaveCycle As Boolean) _
   As TblLmK
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDDam & CStr(intCycle) 'Create a unique key.
   Set Item = mcolLmKs.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycle 'Save the active cycle, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' NewEnum must return the IUnknown interface of a collection's
' enumerator.
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
On Error GoTo ErrHnd
    Set NewEnum = mcolLmKs.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's first item.
Public Function First(ByVal blnEscSaveCycle As Boolean) As TblLmK
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   Dim intCycleFirst As Integer
   Dim strKey As String
   For Each obTblLmK In mcolLmKs 'Exit the cycle after the first item.
      intCycleFirst = obTblLmK.Cycle
      Exit For
   Next obTblLmK
   strKey = mstrIDDam & CStr(intCycleFirst)
   Set First = mcolLmKs.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycleFirst 'Save the active cycle,
Exit Function                                               'unless canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
Public Function Last(ByVal blnEscSaveCycle As Boolean) As TblLmK
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   Dim strKey As String
   Dim intCycleLast As Integer
   For Each obTblLmK In mcolLmKs 'Cycle through all members to get the last DateAnnl.
      intCycleLast = obTblLmK.Cycle
   Next obTblLmK
   strKey = mstrIDDam & CStr(intCycleLast)
   Set Last = mcolLmKs.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycleLast 'Save the active cycle, unless
Exit Function                                              'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's active item.
Public Function Act() As TblLmK
On Error GoTo ErrHnd
    Dim strKey As String
    strKey = mstrIDDam & CStr(mintCycleAct)
    Set Act = mcolLmKs.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a new lambing/kidding cycle number that is equal to
'  - the last lambing/kidding cycle + 1, if there are cycles;
'  - 1, if there are no lambing/kidding cycles yet.
Public Function CycleLmKNew() As Integer
On Error GoTo ErrHnd
   If mcolLmKs.Count = 0 Then
      CycleLmKNew = 1 'No lambing/kidding cycles.
   Else
      CycleLmKNew = Last(False).CycleLmK + 1 'Increase lambing/kidding cycle.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the specified cycle nubmer if it exists in in the mcolLmKs collection.
' In positive case mark the cycle active.
' Return True, if succeeds.
Public Function CycleVld(ByVal intCycle As Integer) As Boolean
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   For Each obTblLmK In mcolLmKs 'Cycle through all members to find intCycle.
      If intCycle = obTblLmK.Cycle Then
         CycleVld = True 'Found.
         mintCycleAct = intCycle 'Mark the active cycle.
         Exit For
      End If
   Next obTblLmK
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's previous item.
' If required cancel saving the last active cycle.
Public Function Prev(ByVal blnEscSaveCycle As Boolean) As TblLmK
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   Dim intCyclePrev As Integer
   Dim strKey As String
   For Each obTblLmK In mcolLmKs 'Cycle through all members to get the cycle previous
      With obTblLmK                 'to the active.
         If .Cycle < mintCycleAct Then
            intCyclePrev = .Cycle
         Else
            Exit For
         End If
      End With
   Next
   strKey = mstrIDDam & CStr(intCyclePrev)
   Set Prev = mcolLmKs.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCyclePrev 'Save the active cycle, unless
Exit Function                                              'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's next-from-active item.
' If required cancel saving the last active cycle.
Public Function Nxt(ByVal blnEscSaveCycle As Boolean) As TblLmK
On Error GoTo ErrHnd
   Dim obTblLmK As TblLmK
   Dim intCycleNxt As Integer
   Dim strKey As String
   For Each obTblLmK In mcolLmKs 'Loop & exit the cycle after the cycle next from the
      With obTblLmK              'active.
         If .Cycle > mintCycleAct Then
            intCycleNxt = .Cycle
            Exit For
         End If
      End With
   Next
   strKey = mstrIDDam & CStr(intCycleNxt)
   Set Nxt = mcolLmKs.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycleNxt 'Save the active cycle, unless canceled.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

