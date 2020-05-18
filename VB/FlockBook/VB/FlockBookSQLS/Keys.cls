VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Keys"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolKeys As Collection

' Create a new mcolKeys object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolKeys = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolKeys.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new Keys collection's member.
Public Sub Add(ByVal strKey0 As String, Optional ByVal strKey1 As String, Optional _
    ByVal lngKey2 As Long, Optional ByVal lngKey3 As Long, Optional ByVal dtmKey4 _
    As Date)
On Error GoTo ErrHnd
    Dim obKey As Key
    Set obKey = New Key
    With obKey
        .Key0 = strKey0
        .Key1 = strKey1
        .Key2 = lngKey2
        .Key3 = lngKey3
        .Key4 = dtmKey4
    End With
    mcolKeys.Add obKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal vntIdx As Variant) As Key
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
    Set Item = mcolKeys.Item(vntIdx)
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
    Set NewEnum = mcolKeys.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
