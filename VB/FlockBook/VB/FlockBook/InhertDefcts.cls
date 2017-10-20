VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "InhertDefcts"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolInhertDefcts As Collection
Dim mlngIDDefctAct As Long
'Dim mstrIDDefctAct As String

Public IDShG As String

Public Age As Integer

Public Edited As Boolean

' Create a new mcolInhertDefcts object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolInhertDefcts = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolInhertDefcts.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new obTblInhertDefct object to the InhertDefcts collection.
Public Sub Add(ByVal lngIDDefctOrig As Long, ByVal lngIDDefct As Long, ByVal _
   strDefct As String)
On Error GoTo ErrHnd
   Dim obTblInhertDefct As TblInhertDefct
   Dim strKey As String
   Set obTblInhertDefct = New TblInhertDefct
   With obTblInhertDefct 'Fill the object.
      .IDShG = IDShG
      .Age = Age
      .IDDefctOrig = lngIDDefctOrig
      .IDDefct = lngIDDefct
      .Defct = strDefct
   End With
   strKey = IDShG & CStr(Age) & CStr(lngIDDefct) 'Create a unique key.
   mcolInhertDefcts.Add obTblInhertDefct, strKey
   mlngIDDefctAct = lngIDDefct 'Mark the active defect.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal lngIDDefct As Long)
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = IDShG & CStr(Age) & CStr(lngIDDefct) 'Create a unique key.
   mcolInhertDefcts.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete all members from the collection.
Public Sub DelAll()
On Error GoTo ErrHnd
   Dim obTblInhertDefct As TblInhertDefct
   Dim strKey As String
   For Each obTblInhertDefct In mcolInhertDefcts
      With obTblInhertDefct
Debug.Assert 0 = 1 'Verify
         strKey = .IDShG & CStr(.Age) & CStr(.IDDefct) 'Create a unique key.
         mcolInhertDefcts.Remove strKey
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal lngIDDefct As Long, ByVal blnEscSaveDefct As Boolean) _
   As TblInhertDefct
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = IDShG & CStr(Age) & CStr(lngIDDefct) 'Create a unique key.
   Set Item = mcolInhertDefcts.Item(strKey)
   If Not blnEscSaveDefct Then mlngIDDefctAct = lngIDDefct 'Save the active defect, uless
Exit Function                                              'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' NewEnum must return the IUnknown interface of a collection's
' enumerator.
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
On Error GoTo ErrHnd
    Set NewEnum = mcolInhertDefcts.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
Public Function Last() As TblInhertDefct
On Error GoTo ErrHnd
   Dim obTblInhertDefct As TblInhertDefct
   Dim lngIDDefctLast As Long
   Dim strKey As String
   For Each obTblInhertDefct In mcolInhertDefcts 'Cycle to get the last IDDefct.
Debug.Assert 0 = 1 'Verify
      lngIDDefctLast = obTblInhertDefct.IDDefct
   Next
Debug.Assert 0 = 1 'Verify
   strKey = IDShG & CStr(Age) & CStr(lngIDDefctLast) 'Create a unique key.
   Set Last = mcolInhertDefcts.Item(strKey)
   mlngIDDefctAct = lngIDDefctLast 'Mark the active defect.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's active item.
Public Function Act() As TblInhertDefct
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = IDShG & CStr(Age) & CStr(mlngIDDefctAct) 'Create a unique key.
   Set Act = mcolInhertDefcts.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if the defect exists in the collection.
Public Function Exists(ByVal lngIDDefct As Long) As Boolean
On Error GoTo ErrHnd
   Dim obTblInhertDefct As TblInhertDefct
   For Each obTblInhertDefct In mcolInhertDefcts
      If obTblInhertDefct.IDDefct = lngIDDefct Then
         Exists = True 'Exists.
         Exit For
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

