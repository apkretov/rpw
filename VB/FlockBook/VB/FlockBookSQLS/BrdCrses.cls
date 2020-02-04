VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "BrdCrses"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mcolBrdCrses As Collection

Dim mstrIDShG As String

' Create a new mcolBrdCrses object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
    Set mcolBrdCrses = New Collection
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the collection's members.
Public Function Count() As Long
On Error GoTo ErrHnd
    Count = mcolBrdCrses.Count
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

 ' Add a new obTblBrdCrs object to the BrdCrses collection.
Public Sub Add(ByVal strIDBrd As String, ByVal intBrdNum As Integer, ByVal intBrdDen _
   As Integer)
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim strKey As String
   Set obTblBrdCrs = New TblBrdCrs
   With obTblBrdCrs 'Fill the object.
      .IDShG = mstrIDShG
      .IDBrd = strIDBrd
      .BrdNum = intBrdNum
      .BrdDen = intBrdDen
   End With
   strKey = mstrIDShG & strIDBrd 'Create a unique key.
   mcolBrdCrses.Add obTblBrdCrs, strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the collection's member.
Public Sub Del(ByVal strIDBrd As String)
On Error GoTo ErrHnd
   Dim strKey As String
Debug.Assert 0 = 1 'Verify
   strKey = mstrIDShG & strIDBrd 'Create a unique key.
'    strKey = strIDShG & strIDBrd
   mcolBrdCrses.Remove strKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the collectoin's specified item.
Public Function Item(ByVal strIDBrd As String) As TblBrdCrs
Attribute Item.VB_UserMemId = 0
On Error GoTo ErrHnd
   Dim strKey As String
   strKey = mstrIDShG & strIDBrd 'Create a unique key.
   Set Item = mcolBrdCrses.Item(strKey)
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
    Set NewEnum = mcolBrdCrses.[_NewEnum]
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Add the specified sheep/goat's cross breed's half by doubling the share's denominator.
' If the added share duplicates an existing one increase the latter.
' To increase the duplicated share, reduce all available shares & added one to the common
'   denominator; add to the share's numerator a half of that of the duplicate share.
Public Sub AddHalf(ByVal obTblBrdCrsAdd As TblBrdCrs)
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim intDenCommon As Integer
   For Each obTblBrdCrs In mcolBrdCrses 'Look for a duplicate.
      With obTblBrdCrs
         If obTblBrdCrsAdd.IDBrd = .IDBrd Then
            Call ReducToComnDenDupl(obTblBrdCrsAdd) 'Reduce the avialable & duplicate shares to the common denominator.
            .BrdNum = .BrdNum + obTblBrdCrsAdd.BrdNum / 2 'Increase the share.
            Exit Sub 'Exit.
         End If
      End With
   Next obTblBrdCrs
   With obTblBrdCrsAdd
      Call Add(.IDBrd, .BrdNum, .BrdDen * 2) 'Add.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reduce all cross breeds in the collection to the common denominator.
' Determine the common denominator by selecting the biggest denominator.
' Upgrade shares' smaller denominators upto the common & correspondingly mutliply the
'   shares' numerators.
Public Sub ReducToComnDen()
On Error GoTo ErrHnd
    Dim obTblBrdCrs As TblBrdCrs
    Dim intCommonDen As Integer
    ' Determine the common denominator.
    For Each obTblBrdCrs In mcolBrdCrses
        With obTblBrdCrs
            If intCommonDen < .BrdDen Then intCommonDen = .BrdDen
        End With
    Next
    ' Upgrade the shares' smaller denominators upto the common.
    For Each obTblBrdCrs In mcolBrdCrses
        With obTblBrdCrs
            If .BrdDen < intCommonDen Then
                Do Until .BrdDen = intCommonDen
                    .BrdDen = .BrdDen * 2
                    .BrdNum = .BrdNum * 2
                Loop
            End If
        End With
    Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reduce all cross breeds in the collection & in the obTblBrdCrsDupl object to a
'   common denominator.
' Set the common denominator euqual to the bigger one out of two: the biggest denominator
'   from among the collection's objects or that of the obTblBrdCrsDupl object's
'   doubled.
' Upgrade shares' smaller denominators upto the common & correspondingly mutliply
'   shares' numerators.
Private Sub ReducToComnDenDupl(obTblBrdCrsDupl)
On Error GoTo ErrHnd
    Dim obTblBrdCrs As TblBrdCrs
    Dim intDenCommon As Integer
    ' Define the biggest denominator among available.
    For Each obTblBrdCrs In mcolBrdCrses
        With obTblBrdCrs
            If intDenCommon < .BrdDen Then intDenCommon = .BrdDen
        End With
    Next obTblBrdCrs
    ' Determine the common denominator: the biggest or doubled duplicate's.
    With obTblBrdCrsDupl
        If intDenCommon < .BrdDen * 2 Then intDenCommon = .BrdDen * 2
    End With
    ' Upgrade the shares' smaller denominators upto the common.
    For Each obTblBrdCrs In mcolBrdCrses
        With obTblBrdCrs
            If .BrdDen < intDenCommon Then
                Do Until .BrdDen = intDenCommon
                    .BrdDen = .BrdDen * 2
                    .BrdNum = .BrdNum * 2
                Loop
            End If
        End With
    Next obTblBrdCrs
    ' Upgrade the duplicate's denominator upto the common, if smaller.
    With obTblBrdCrsDupl
        If .BrdDen < intDenCommon Then
            Do Until .BrdDen = intDenCommon
                .BrdDen = .BrdDen * 2
                .BrdNum = .BrdNum * 2
            Loop
        End If
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reduce the collection's breeds' denomimator & numerators, if the latters are even.
' Halve the denominator & numerators until a single odd numerator emerges.
Public Sub ReducDenNum()
On Error GoTo ErrHnd
   Do While EvenNumerators 'Halve while all numerators are even.
      Call HalveDenNum 'Halve the denominator & numerators.
   Loop
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Define whether all numerators are even.
' Test the evenness by comparing each breed's halved numerator with its integer part.
' Return True in the positive case, False - in negative.
Private Function EvenNumerators() As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   For Each obTblBrdCrs In mcolBrdCrses
      With obTblBrdCrs
         If .BrdNum / 2 > Int(.BrdNum / 2) Then
            EvenNumerators = False 'Odd numerator - exit.
            Exit For
         Else
            EvenNumerators = True 'Even numerator.
         End If
      End With
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Halve the denominator & numerators.
Private Sub HalveDenNum()
On Error GoTo ErrHnd
    Dim obTblBrdCrs As TblBrdCrs
    For Each obTblBrdCrs In mcolBrdCrses
        With obTblBrdCrs
            .BrdDen = .BrdDen / 2
            .BrdNum = .BrdNum / 2
        End With
    Next obTblBrdCrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Define the basic breed equal to the maximal breed cross share.
' If there are more than one equal biggest shares set the base equal to sire's or dam's
'  one according to the control parameters. In such case the sire's or dam's share must
'  not be less than the maximal share.
Public Function DefineBas(ByVal strIDBrdBasSire As String, ByVal strIDBrdBasDam _
   As String) As String
On Error GoTo ErrHnd
   Dim strDefineBas As String
   Dim strIDBrdMax As String
   Dim intBrdNumMax As Integer
   Call MaxShare(strIDBrdMax, intBrdNumMax) 'Find the maximal share.
   If Not MaxShareMore(strIDBrdMax, intBrdNumMax) Then 'Look for another maximal share
      DefineBas = strIDBrdMax 'The maximal share.      'equal to the last defined one.
   Else
      If gobTblCtrlParam.BrdBasDam Then 'Sire's or dam's basic breed.
         strDefineBas = IIf(Item(strIDBrdBasDam).BrdNum >= intBrdNumMax, _
            strIDBrdBasDam, strIDBrdBasSire) 'The dam's must not be less than the maximal
      Else
         strDefineBas = IIf(Item(strIDBrdBasDam).BrdNum >= intBrdNumMax, _
            strIDBrdBasSire, strIDBrdBasDam) 'The sire's must not be less than the max.
      End If
      DefineBas = IIf(Item(strDefineBas).BrdNum < intBrdNumMax, intBrdNumMax, _
         strDefineBas) 'The sire/dam's must not be less than the maximal (presumably no
   End If              'need to check but do just in case).
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Define whether share 15/16 is found in the collection, if two shares compose the
'   animal's cross breed.
' If that's the case, return share 15/16 or otherwise return a zero-length string.
' CURRENTLY UNUSED: UpgradedBrd.
Public Function UpgradedBrd() As String
On Error GoTo ErrHnd
 Debug.Assert 0 = 1 'VERIFY.
    Dim obTblBrdCrs As TblBrdCrs
    Dim strIDBrd15To16
    If mcolBrdCrses.Count = 2 Then
        ' Two shares - check for 1/16.
        For Each obTblBrdCrs In mcolBrdCrses
            With obTblBrdCrs
                If .BrdDen = 16 And .BrdNum = 15 Then
                    ' Share 15/16 is found.
                    UpgradedBrd = .IDBrd
                End If
            End With
        Next obTblBrdCrs
    End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the maximal breed cross share's strIDBrd & intBrdNumMax arguments supplied by
'  reference.
Private Sub MaxShare(ByRef strIDBrd As String, ByRef intBrdNumMax As Integer)
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   For Each obTblBrdCrs In mcolBrdCrses
      With obTblBrdCrs
         If intBrdNumMax < .BrdNum Then
            intBrdNumMax = .BrdNum
            strIDBrd = .IDBrd
         End If
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Look for more maximal shares equal to the specified strIDBrdMax.
' Return True, if one encounters.
Private Function MaxShareMore(ByVal strIDBrdMax As String, ByVal intBrdNumMax _
   As Integer) As Boolean
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   For Each obTblBrdCrs In mcolBrdCrses
      With obTblBrdCrs
         If .IDBrd <> strIDBrdMax Then
            If .BrdNum = intBrdNumMax Then
               MaxShareMore = True 'Another maximum encounters.
               Exit For
            End If
         End If
      End With
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get IDShG.
Public Property Get IDShG() As String
   IDShG = mstrIDShG
End Property

' Let IDShG in this class & in its inbuilt ones.
Public Property Let IDShG(ByVal strIDShG As String)
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   mstrIDShG = strIDShG
   For Each obTblBrdCrs In mcolBrdCrses
      obTblBrdCrs.IDShG = strIDShG
   Next
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Remove the 1/32 cross breed share.
' Delete all cross breed shares, if the cross breed comprises 2 shares & either is 1/32
'  or smaller (1/64, 1/128). Update the TblShG table of the sheep/goat to make it
'  purebred rather than crossbred.
' Return True, if the 1/32 is removed.
Public Function Remv32nd(ByVal blnDoMsgRemv As Boolean) As Boolean
On Error GoTo ErrHnd
   Dim strIDBrdRemain As String
   Dim strPromt As String
   If mcolBrdCrses.Count = 2 Then 'Proceed for 2 shares.
      strIDBrdRemain = RemainShare 'Find the removable & remaining shares.
      If strIDBrdRemain <> "" Then 'Proceed, if found.
         With gobShGs(mstrIDShG).TblShG 'Update to purebred.
            .IDBrdBas = strIDBrdRemain
            .Crs = False
            .BrdCrs = strIDBrdRemain
         End With
         Call DelAll 'Delete all shares.
         Remv32nd = True 'Removed.
         If blnDoMsgRemv Then  'Message, if required.
            strPromt = LoadResString(425) & Util.BrdCodeToNam(strIDBrdRemain) & "')."
            MsgBox strPromt, vbInformation, LoadResString(426)
         End If
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the remaining shares if either is 1/32 or smaller.
Private Function RemainShare() As String
On Error GoTo ErrHnd
   Const intRemvDen As Integer = 32
   Const intRemvNum As Integer = 1
   Dim obTblBrdCrs As TblBrdCrs
   Dim strIDBrdRemv As String
   Dim blnProceed As Boolean
   For Each obTblBrdCrs In mcolBrdCrses 'Find the removable.
      With obTblBrdCrs
         If .BrdDen >= intRemvDen Then 'Proceed for a denominator 32 or bigger.
            If .BrdNum = intRemvNum Then
               strIDBrdRemv = .IDBrd 'The removable share.
               blnProceed = True 'Mark to proceed.
               Exit For
            End If
         End If
      End With
   Next
   If blnProceed Then 'Find the remaining, if there is a removable.
      For Each obTblBrdCrs In mcolBrdCrses
         With obTblBrdCrs
            If .IDBrd <> strIDBrdRemv Then
               RemainShare = .IDBrd 'Succeeded.
               Exit For
            End If
         End With
      Next
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Delete all members from the collection.
Public Sub DelAll()
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim obDatTbl As DatTbl
   Dim strKey As String
   For Each obTblBrdCrs In mcolBrdCrses
      With obTblBrdCrs
         strKey = .IDShG & .IDBrd 'Create a unique key.
         mcolBrdCrses.Remove strKey
      End With
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
