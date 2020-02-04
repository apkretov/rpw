VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "WtWools"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolWtWools As Collection

Dim mstrIDShG As String
Dim mintAgeAct As Integer

' Let IDShG in this class & in its inbuilt ones.
Public Property Let IDShG(ByVal strIDShG As String)
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   mstrIDShG = strIDShG
   For Each obTblWtWool In mcolWtWools
      obTblWtWool.IDShG = strIDShG
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Initialise the module-level variables.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mcolWtWools = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolWtWools.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new obTblWtWool object to the WtWools collection.
Public Sub Add(ByVal intAgeOrig As Integer, ByVal intAge As Integer, ByVal dtmDateAnnl _
   As Date, ByVal sngWtAnnl As Single, ByVal dtmDateShearAnnl As Date, ByVal _
   sngGreaseAnnl As Single)
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim strKey As String
   Set obTblWtWool = New TblWtWool
   With obTblWtWool 'Fill the object.
      .IDShG = mstrIDShG
      .AgeOrig = intAgeOrig
      .Age = intAge
      .DateAnnl = dtmDateAnnl
      .WtAnnl = sngWtAnnl
      .DateShearAnnl = dtmDateShearAnnl
      .GreaseAnnl = sngGreaseAnnl
   End With
   strKey = mstrIDShG & CStr(intAge) 'Create a unique key.
   mcolWtWools.Add obTblWtWool, strKey
   mintAgeAct = intAge 'Mark the active date.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal intAge As Integer)
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify w/o IDShG
   Dim strKey As String
Debug.Assert 0 = 1 'Verify w/o IDShG
   strKey = mstrIDShG & CStr(intAge)
   mcolWtWools.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete all members from the collection.
' To access the memebers, create a unique key based on the original age because the age
'  can be incremented in the frmShG.VldOvlpWt procedure.
Public Sub DelAll()
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim strKey As String
   For Each obTblWtWool In mcolWtWools
      With obTblWtWool
         strKey = .IDShG & CStr(.AgeOrig) 'Create a unique key.
         mcolWtWools.Remove strKey
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
' If required cancel saving the last active age.
Public Function Item(ByVal intAge As Integer, ByVal blnEscSaveAge As Boolean) _
   As TblWtWool
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDShG & CStr(intAge) 'Create a unique key.
   Set Item = mcolWtWools.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAge 'Save the active age, unless canceled.
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
    Set NewEnum = mcolWtWools.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's first item.
' If required cancel saving the last active age.
Public Function First(ByVal blnEscSaveAge As Boolean) As TblWtWool
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim intAgeFirst As Integer
   Dim strKey As String
   For Each obTblWtWool In mcolWtWools 'Cycle through all members to & exit the cycle after the first item
      intAgeFirst = obTblWtWool.Age
      Exit For
   Next obTblWtWool
   strKey = mstrIDShG & CStr(intAgeFirst)
   Set First = mcolWtWools.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgeFirst 'Save the active age, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
' If required cancel saving the last active age.
Public Function Last(ByVal blnEscSaveAge As Boolean) As TblWtWool
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim intAgeLast As Integer
   Dim strKey As String
   For Each obTblWtWool In mcolWtWools 'Cycle through all members to get the last DateAnnl.
      intAgeLast = obTblWtWool.Age
   Next obTblWtWool
   strKey = mstrIDShG & CStr(intAgeLast)
   Set Last = mcolWtWools.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgeLast 'Save the active age, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's previous item.
' If required cancel saving the last active age.
Public Function Prev(ByVal blnEscSaveAge As Boolean) As TblWtWool
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim intAgePrev As Integer
   Dim strKey As String
   For Each obTblWtWool In mcolWtWools 'Cycle through all members to get the age previous
      With obTblWtWool                 'to the active.
         If .Age < mintAgeAct Then
            intAgePrev = .Age
         Else
            Exit For
         End If
      End With
   Next obTblWtWool
   strKey = mstrIDShG & CStr(intAgePrev)
   Set Prev = mcolWtWools.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgePrev 'Save the active age, unless canceld
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's active item.
Public Function Act() As TblWtWool
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDShG & CStr(mintAgeAct)
   Set Act = mcolWtWools.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a new age that is equal to
'  - the last age + 1, if there are weighings;
'  - 1, if there are no weighings yet.
Private Function AgeNew() As Integer
On Error GoTo ErrHnd
   If mcolWtWools.Count = 0 Then
      AgeNew = 1 'No weighings.
   Else
      AgeNew = Last(False).Age + 1 'Increase age.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Open a new blank weighing/shearing to input data in.
Public Sub AgeNewOpen()
On Error GoTo ErrHnd
   Dim intAgeNew As Integer
   intAgeNew = AgeNew 'Define a new age.
   Call Add(intAgeNew, intAgeNew, 0, 0, 0, 0) 'Open the weighing/shearing.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's next-from-active item.
' If required cancel saving the last active age.
Public Function Nxt(ByVal blnEscSaveAge As Boolean) As TblWtWool
On Error GoTo ErrHnd
   Dim obTblWtWool As TblWtWool
   Dim intAgeNxt As Integer
   Dim strKey As String
   For Each obTblWtWool In mcolWtWools 'Loop & exit the cycle after the age next from the
      With obTblWtWool                 'active.
         If .Age > mintAgeAct Then
            intAgeNxt = .Age
            Exit For
         End If
      End With
   Next
   strKey = mstrIDShG & CStr(intAgeNxt)
   Set Nxt = mcolWtWools.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgeNxt 'Save the active age, unless canceled.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if the wt exists in the collection.
Public Function Exists(ByVal intAge As Integer) As Boolean
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify
   Dim obTblWtWool As TblWtWool
   For Each obTblWtWool In mcolWtWools
      If obTblWtWool.Age = intAge Then
         Exists = True 'Exists.
         Exit For
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

