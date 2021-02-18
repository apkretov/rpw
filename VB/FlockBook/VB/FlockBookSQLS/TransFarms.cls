VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TransFarms"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolTransFarms As Collection

Dim mstrIDShG As String

' Let IDShG.
Public Property Let IDShG(ByVal strIDShG As String)
On Error GoTo ErrHnd
   Dim obTblTransFarm As TblTransFarm
   mstrIDShG = strIDShG
   For Each obTblTransFarm In mcolTransFarms
      obTblTransFarm.IDShG = strIDShG
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Create a new mcolTransFarms object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolTransFarms = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolTransFarms.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

 ' Add a new obTblTransFarm object to the TransFarms collection.
Public Sub Add(ByVal dtmDateTrans As Date, ByVal strIDFarm As String)
On Error GoTo ErrHnd
   Dim obTblTransFarm As TblTransFarm
   Dim strKey As String
   Set obTblTransFarm = New TblTransFarm
   With obTblTransFarm 'Fill the object.
      .IDShG = mstrIDShG
      .DateTrans = dtmDateTrans
      .IDFarm = strIDFarm
   End With
   strKey = mstrIDShG & CStr(dtmDateTrans)
   mcolTransFarms.Add obTblTransFarm, strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal strIDShG As String, ByVal dtmDateTrans _
    As Date)
On Error GoTo ErrHnd
    Dim strKey As String
    ' Create a unique key to delete the object from the collection.
    strKey = strIDShG & CStr(dtmDateTrans)
    mcolTransFarms.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal dtmDateTrans As Date) As TblTransFarm
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
Debug.Assert 0 = 1 'Verify w/o IDShG
   strKey = mstrIDShG & CStr(dtmDateTrans)
   Set Item = mcolTransFarms.Item(strKey)
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
    Set NewEnum = mcolTransFarms.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's first item.
Public Function First() As TblTransFarm
On Error GoTo ErrHnd
   Dim obTblTransFarm As TblTransFarm
   Dim dtmDateTransFirst As Date
   Dim strKey As String
   For Each obTblTransFarm In mcolTransFarms 'Cycle & exit the cycle after the 1st item.
      dtmDateTransFirst = obTblTransFarm.DateTrans
      Exit For
   Next
   strKey = mstrIDShG & CStr(dtmDateTransFirst)
   Set First = mcolTransFarms.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
Public Function Last() As TblTransFarm
On Error GoTo ErrHnd
   Dim obTblTransFarm As TblTransFarm
   Dim dtmDateTransLast As Date
   Dim strKey As String
   For Each obTblTransFarm In mcolTransFarms 'Cycle through all members to get the last date.
      dtmDateTransLast = obTblTransFarm.DateTrans
   Next
   strKey = mstrIDShG & CStr(dtmDateTransLast) 'Create a unique key.
   Set Last = mcolTransFarms.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

