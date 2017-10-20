VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Apprs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolApprs As Collection

Dim mstrIDShG As String
Dim mintAgeAct As Integer

' Initialise the module-level variables.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mcolApprs = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolApprs.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add a new obTblAppr object to the Apprs collection.
Public Sub Add(ByVal intAgeOrig As Integer, ByVal intAge As Integer, ByVal dtmDateAppr _
   As Date, ByVal sngLeng As Single, ByVal strDiam As String, ByVal strMass As String, _
   ByVal strCrimpins As String, ByVal strEvens As String, ByVal intDensity As Integer, _
   ByVal strStrength As String, ByVal strIDColour As String, ByVal strColour As String, _
   ByVal strQuality As String, ByVal strIDFluffColour As String, ByVal strFluffColour _
   As String, ByVal intFluff As Integer, ByVal intFibreYield As Integer, ByVal _
   strBodyType As String, ByVal strConstitutn As String, ByVal strBodySize As String, _
   ByVal strFatTail As String)
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim strKey As String
   Set obTblAppr = New TblAppr
   With obTblAppr 'Fill the object.
      .IDShG = mstrIDShG
      .AgeOrig = intAgeOrig
      .Age = intAge
      .DateAppr = dtmDateAppr
      .Leng = sngLeng
      .Diam = strDiam
      .Mass = strMass
      .Crimpins = strCrimpins
      .Evens = strEvens
      .Density = intDensity
      .Strength = strStrength
      .IDColour = strIDColour
      .Colour = strColour
      .Quality = strQuality
      .IDFluffColour = strIDFluffColour
      .FluffColour = strFluffColour
      .Fluff = intFluff
      .FibreYield = intFibreYield
      .BodyType = strBodyType
      .Constitutn = strConstitutn
      .BodySize = strBodySize
      .FatTail = strFatTail
   End With
   strKey = mstrIDShG & CStr(intAge) 'Create a unique key.
   mcolApprs.Add obTblAppr, strKey
   mintAgeAct = intAge 'Mark the active date.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal intAge As Integer)
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDShG & CStr(intAge) 'Create a unique key.
   mcolApprs.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete all members from the collection.
' To access the memebers, create a unique key based on the original age because the age
'  can be incremented in the frmShG.VldOvlpWt procedure.
Public Sub DelAll()
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim strKey As String
   For Each obTblAppr In mcolApprs
      With obTblAppr
         strKey = .IDShG & CStr(.AgeOrig) 'Create a unique key.
         mcolApprs.Remove strKey
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
' If required cancel saving the last active age.
Public Function Item(ByVal intAge As Integer, ByVal blnEscSaveAge As Boolean) As TblAppr
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDShG & CStr(intAge) 'Create a unique key.
   Set Item = mcolApprs.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAge 'Save the active age, unless canceled.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' NewEnum must return the IUnknown interface of a collection's enumerator.
Public Function NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
On Error GoTo ErrHnd
   Set NewEnum = mcolApprs.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's first item.
' If required cancel saving the last active age.
Public Function First(ByVal blnEscSaveAge As Boolean) As TblAppr
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim intAgeFirst As Integer
   Dim strKey As String
   For Each obTblAppr In mcolApprs 'Cycle & exit the cycle after the 1st item.
      intAgeFirst = obTblAppr.Age
      Exit For
   Next obTblAppr
   strKey = mstrIDShG & CStr(intAgeFirst) 'Create a unique key.
   Set First = mcolApprs.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgeFirst 'Save the active age, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's last item.
' If required cancel saving the last active age.
Public Function Last(ByVal blnEscSaveAge As Boolean) As TblAppr
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim intAgeLast As Integer
   Dim strKey As String
   For Each obTblAppr In mcolApprs 'Cycle through all members to get the last DateAppr.
      intAgeLast = obTblAppr.Age
   Next obTblAppr
   strKey = mstrIDShG & CStr(intAgeLast) 'Create a unique key.
   Set Last = mcolApprs.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgeLast 'Save the active age, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's previous item.
' If required cancel saving the last active age.
Public Function Prev(ByVal blnEscSaveAge As Boolean) As TblAppr
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim intAgePrev As Integer
   Dim strKey As String
   For Each obTblAppr In mcolApprs 'Cycle to get the age previous to the active.
      With obTblAppr
         If .Age < mintAgeAct Then
            intAgePrev = .Age
         Else
            Exit For
         End If
      End With
   Next obTblAppr
   strKey = mstrIDShG & CStr(intAgePrev) 'Create a unique key.
   Set Prev = mcolApprs.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgePrev 'Save the active age, unless
Exit Function                                          'canceled.
ErrHnd:
MsgBox Err.Description
End Function

' Set the collectoin's active item.
Public Function Act() As TblAppr
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDShG & CStr(mintAgeAct) 'Create a unique key.
   Set Act = mcolApprs.Item(strKey)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a new age that is equal to
'  - the last age + 1, if there are weighings;
'  - 1, if there are no weighings yet.
Private Function AgeNew() As Integer
On Error GoTo ErrHnd
   If mcolApprs.Count = 0 Then
      AgeNew = 1 'No weighings.
   Else
      AgeNew = Last(False).Age + 1 'Increase age.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Count defects in all members of the collection.
Public Function AllDefct() As Integer
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   For Each obTblAppr In mcolApprs 'Cycle through appraisals.
      AllDefct = AllDefct + obTblAppr.InhertDefcts.Count
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the original count of defects in all members of the collection.
Public Function AllDefctOrig() As Integer
On Error GoTo ErrHnd
   Static intAllDefctOrig As Integer
   Static blnPassed As Boolean
   If Not blnPassed Then 'Execute only once.
      blnPassed = True
      intAllDefctOrig = AllDefct
   End If
   AllDefctOrig = intAllDefctOrig
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Open a new blank appraisal to input data in.
Public Sub AgeNewOpen()
On Error GoTo ErrHnd
   Dim intAgeNew As Integer
   intAgeNew = AgeNew 'Define a new age.
   Call Add(intAgeNew, intAgeNew, 0, 0, 0, "", "", "", 0, "", "", "", "", "", "", 0, 0, _
      "", "", "", "") 'Open a new appraisal.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Let IDShG in this class & in its inbuilt ones.
Public Property Let IDShG(ByVal strIDShG As String)
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   mstrIDShG = strIDShG
   For Each obTblAppr In mcolApprs
      obTblAppr.IDShG = strIDShG
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Set the collectoin's next-from-active item.
' If required cancel saving the last active age.
Public Function Nxt(ByVal blnEscSaveAge As Boolean) As TblAppr
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   Dim intAgeNxt As Integer
   Dim strKey As String
   For Each obTblAppr In mcolApprs 'Loop & exit the cycle after the age next from the
      With obTblAppr                 'active.
         If .Age > mintAgeAct Then
            intAgeNxt = .Age
            Exit For
         End If
      End With
   Next
   strKey = mstrIDShG & CStr(intAgeNxt)
   Set Nxt = mcolApprs.Item(strKey)
   If Not blnEscSaveAge Then mintAgeAct = intAgeNxt 'Save the active age, unless canceled.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return True, if the appraisal exists in the collection.
Public Function Exists(ByVal intAge As Integer) As Boolean
On Error GoTo ErrHnd
   Dim obTblAppr As TblAppr
   For Each obTblAppr In mcolApprs
      If obTblAppr.Age = intAge Then
         Exists = True 'Exists.
         Exit For
      End If
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

