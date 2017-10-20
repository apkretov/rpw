VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Bar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Type BarTp
   Qut As Single
   Cross As Boolean
   Zero As Boolean
   Incr As Integer
   Levrg As Long
End Type
Dim mudtBar As BarTp

Public Event AddCrosses(ByVal intCountCrs As Integer) 'Message to plot crosses/zeros.
Public Event AddZeros(ByVal intCountZr As Integer)
Public Event ReverseUp(ByVal intCountCrs As Integer) 'Message to reverse the bar with plotting crosses/zeros.
Public Event ReverseDown(ByVal intCountZr As Integer)
                                                     
Public H As Single
Public L As Single
Public Revers As Integer 'The number of boxes to reverse the bar from.

' Get the cross mark.
Public Property Get Cross() As Boolean
   Cross = mudtBar.Cross
End Property

' Get the zero mark.
Public Property Get Zero() As Boolean
Debug.Assert 0 = 1 'Verify
   Zero = mudtBar.Zero
End Property

' Refresh the quote to plot boxes on the cahrt.
Public Sub RefreshQut(ByVal sngQut As Single, ByVal intIncrement As Integer, ByVal lngLevrg As Long)
On Error GoTo ErrHnd
   Static blnPassed As Boolean
   With mudtBar
      .Qut = sngQut 'Refresh the module variants.
      If Not blnPassed Then 'Ininitalise the increment & leverage only once.
         .Incr = intIncrement
         .Levrg = lngLevrg
         blnPassed = True 'Mark passed.
      End If
      If .Cross Then 'Cross bar?
         Call RefreshCross
      ElseIf .Zero Then 'Zero bar?
         Call RefreshZero
      Else 'Begin the bar from scratch.
         Call BeginNew
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Begin the bar from scratch.
Private Sub BeginNew()
On Error GoTo ErrHnd
   Dim intBoxes As Integer
   With mudtBar
      If .Qut > H Then 'BeginNew up?
'      If .Qut >= H Then 'BeginNew up? 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
         intBoxes = QutToBoxes(.Qut - H) 'Count the boxes to add.
         If intBoxes > 0 Then 'Anything to add?
            .Cross = True 'Mark cross bar.
            H = H + Util.BoxesToQut(intBoxes, .Incr, .Levrg) 'Remember the new high.
            L = 0 'Reset.
            RaiseEvent AddCrosses(intBoxes) 'Plot crosses.
         End If
      ElseIf .Qut < L Then 'BeginNew down?
'      ElseIf .Qut <= L Then 'BeginNew down? 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
         intBoxes = QutToBoxes(L - .Qut) 'Count the boxes to add.
         If intBoxes > 0 Then 'Anything to add?
            .Zero = True 'Mark zero bar.
            L = L - Util.BoxesToQut(intBoxes, .Incr, .Levrg) 'Remember the new low.
            H = 0 'Reset.
            RaiseEvent AddZeros(intBoxes) 'Plot crosses.
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh a cross bar.
Private Sub RefreshCross()
On Error GoTo ErrHnd
   Dim intBoxes As Integer
   Dim sngQutAdd As Single
   With mudtBar
      If .Qut > H Then 'Grow up?
'      If .Qut >= H Then 'Grow up? 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
         intBoxes = QutToBoxes(.Qut - H) 'Count the boxes to add.
         If intBoxes > 0 Then 'Anything to add?
            H = H + Util.BoxesToQut(intBoxes, .Incr, .Levrg) 'Remember the new high.
            RaiseEvent AddCrosses(intBoxes) 'Plot crosses.
         End If
      Else 'Handle a reversal.
         sngQutAdd = Util.IntQut(H - .Qut, .Levrg) 'Count pts.
         If sngQutAdd > Util.BoxesToQut(Revers, .Incr, .Levrg) Then 'Reversed?
'         If sngQutAdd >= Util.BoxesToQut(Revers, .Incr, .Levrg) Then 'Reversed? 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
            intBoxes = QutToBoxes(sngQutAdd) 'Count the boxes to add.
            .Cross = False
            .Zero = True
            L = H - Util.BoxesToQut(intBoxes, .Incr, .Levrg) - 1 / .Levrg 'Remember the low, reset the high.
'            L = H - Util.BoxesToQut(intBoxes, .Incr, .Levrg) / .Levrg 'Remember the low, reset the high. 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
            H = 0
            RaiseEvent ReverseDown(intBoxes) 'Reverse & plot zeros.
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh a zero bar.
Private Sub RefreshZero()
On Error GoTo ErrHnd
   Dim intBoxes As Integer
   Dim sngQutDedct As Single
   With mudtBar
'      If .Qut < L Then 'Grow down?
      If .Qut <= L Then 'Grow down? 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
         intBoxes = QutToBoxes(L - .Qut) 'Count the boxes to add.
         If intBoxes > 0 Then 'Anything to add?
            L = L - Util.BoxesToQut(intBoxes, .Incr, .Levrg) 'Remember the new low.
            RaiseEvent AddZeros(intBoxes) 'Plot crosses.
         End If
      Else 'Handle a reversal.
         sngQutDedct = Util.IntQut(.Qut - L, .Levrg) 'Count pts.
         If sngQutDedct > Util.BoxesToQut(Revers, .Incr, .Levrg) Then 'Reversed?
'         If sngQutDedct >= Util.BoxesToQut(Revers, .Incr, .Levrg) Then 'Reversed? 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
            intBoxes = QutToBoxes(sngQutDedct) 'Count the boxes to add.
            .Zero = False
            .Cross = True
            H = L + Util.BoxesToQut(intBoxes, .Incr, .Levrg) + 1 / .Levrg 'Remember the high, reset the low.
'            H = L + Util.BoxesToQut(intBoxes, .Incr, .Levrg) / .Levrg 'Remember the high, reset the low. 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
            L = 0
            RaiseEvent ReverseUp(intBoxes) 'Reverse & plot crosses.
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Covert the number of pts to boxes.
Private Function QutToBoxes(ByVal sngQut As Single) As Integer
On Error GoTo ErrHnd
   With mudtBar
      QutToBoxes = sngQut * .Levrg \ .Incr
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
