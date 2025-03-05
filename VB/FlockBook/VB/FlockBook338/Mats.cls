VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Mats"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mstrIDDam As String
Dim mcolMats As Collection
Dim mintCycleAct As Integer

' Let IDDam in this class & in its inbuilt ones.
Public Property Let IDDam(ByVal strIDDam As String)
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   mstrIDDam = strIDDam
   For Each obTblMat In mcolMats
      obTblMat.IDDam = strIDDam
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Create a new mcolMats object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolMats = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolMats.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new obTblMat object to the Mats collection.
Public Sub Add(ByVal intCycle As Integer, ByVal intCycleLmK As Integer, ByVal _
   dtmDateMat As Date, ByVal strIDSire As String)
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim obDatTbl As DatTbl
   Dim strKey As String
   Set obTblMat = New TblMat
   With obTblMat 'Fill the object.
      .IDDam = mstrIDDam
      .Cycle = intCycle
      .CycleLmK = intCycleLmK
      .DateMat = dtmDateMat
      .IDSire = strIDSire
   End With
   strKey = mstrIDDam & CStr(intCycle) 'Create a unique key.
   mcolMats.Add obTblMat, strKey
   Set obDatTbl = mcolMats(strKey) 'Save the original data.
   obDatTbl.OrigSave
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
   mcolMats.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete all members from the collection.
' First make sure that there are any members in the collection to delete
'    & set the PopltMat mark to False; otherwise escape.
Public Sub DelAll()
On Error GoTo ErrHnd
    Dim obTblMat As TblMat
    Dim strKey As String
    Dim strIDDam As String
    ' Check the members' quantity.
    If mcolMats.Count > 0 Then
        ' Delete.
        For Each obTblMat In mcolMats
            With obTblMat
                ' Remember the dam' ID.
                If strIDDam = "" Then strIDDam = .IDDam
                strKey = .IDDam & .Cycle
                mcolMats.Remove strKey
            End With
        Next obTblMat
        gobShGs(strIDDam).Dam.PopltMat = False 'Reset PopltMat.
    End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal intCycle As Integer, ByVal blnEscSaveCycle As Boolean) _
   As TblMat
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDDam & CStr(intCycle)
   Set Item = mcolMats.Item(strKey)
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
    Set NewEnum = mcolMats.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
Public Function Last(ByVal blnEscSaveCycle As Boolean) As TblMat
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim strKey As String
   Dim intCycleLast As Integer
   For Each obTblMat In mcolMats 'Cycle through all members to get the last item.
      intCycleLast = obTblMat.Cycle
   Next
   strKey = mstrIDDam & CStr(intCycleLast) 'Create a unique key.
   Set Last = mcolMats.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycleLast 'Save as an active cycle,
Exit Function                                              'unless canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Return the collectoin's first item.
Public Function First(ByVal blnEscSaveCycle As Boolean) As TblMat
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim intCycleFirst As Integer
   Dim strKey As String
   For Each obTblMat In mcolMats 'Exit the cycle after the first item.
      intCycleFirst = obTblMat.Cycle
      Exit For
   Next
   strKey = mstrIDDam & CStr(intCycleFirst)
   Set First = mcolMats.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycleFirst 'Save the active cycle,
Exit Function                                               'unless canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's active item.
Public Function Act() As TblMat
On Error GoTo ErrHnd
    Dim strKey As String
    strKey = mstrIDDam & CStr(mintCycleAct)
    Set Act = mcolMats.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a new cycle number that is equal to
'  - the last cycle + 1, if there are cycles;
'  - 1, if there are no cycles yet.
Public Function CycleNew() As Integer
On Error GoTo ErrHnd
   If mcolMats.Count = 0 Then
      CycleNew = 1 'No cycles.
   Else
      CycleNew = Last(False).Cycle + 1 'Increase cycle.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's previous item.
' If required cancel saving the last active cycle.
Public Function Prev(ByVal blnEscSaveCycle As Boolean) As TblMat
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim intCyclePrev As Integer
   Dim strKey As String
   For Each obTblMat In mcolMats 'Cycle through all members to get the cycle previous
      With obTblMat                 'to the active.
         If .Cycle < mintCycleAct Then
            intCyclePrev = .Cycle
         Else
            Exit For
         End If
      End With
   Next
   strKey = mstrIDDam & CStr(intCyclePrev)
   Set Prev = mcolMats.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCyclePrev 'Save the active cycle, unless canceled.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's next-from-active item.
' If required cancel saving the last active cycle.
Public Function Nxt(ByVal blnEscSaveCycle As Boolean) As TblMat
On Error GoTo ErrHnd
   Dim obTblMat As TblMat
   Dim intCycleNxt As Integer
   Dim strKey As String
   For Each obTblMat In mcolMats 'Loop & exit the cycle after the cycle next from the
      With obTblMat              'active.
         If .Cycle > mintCycleAct Then
            intCycleNxt = .Cycle
            Exit For
         End If
      End With
   Next
   strKey = mstrIDDam & CStr(intCycleNxt)
   Set Nxt = mcolMats.Item(strKey)
   If Not blnEscSaveCycle Then mintCycleAct = intCycleNxt 'Save the active cycle, unless canceled.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

