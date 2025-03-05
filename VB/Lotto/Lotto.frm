VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmLotto 
   Caption         =   "Лото"
   ClientHeight    =   6975
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4125
   Icon            =   "Lotto.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6975
   ScaleWidth      =   4125
   StartUpPosition =   2  'CenterScreen
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid flexRnd 
      Height          =   5895
      Left            =   0
      TabIndex        =   1
      Top             =   1080
      Width           =   4095
      _ExtentX        =   7223
      _ExtentY        =   10398
      _Version        =   393216
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.CommandButton cmdRnd 
      Caption         =   "Число"
      Height          =   495
      Left            =   1440
      TabIndex        =   0
      Top             =   360
      Width           =   1215
   End
End
Attribute VB_Name = "frmLotto"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim mlngMin As Long
Dim mlngMax As Long
Dim mlngRange As Long

Private Sub cmdRnd_Click()
On Error GoTo ErrHnd
   Static lngRnd()
   Static I As Long
   Dim J As Long
   Dim K As Long
   Dim lngNewNum As Long
   Dim lngCycle As Long
   Dim blnUsed As Boolean
   Dim lngMin As Long
   Dim lngMinRow As Long
   I = I + 1
   ReDim Preserve lngRnd(2, I) 'Create an array to accomodate all numbers.
   If I > mlngRange Then
      Call GameOverMsg 'The Game Over message.
   Else
      Do
         lngCycle = CInt(Minute(Now))
         For K = 0 To lngCycle
            lngNewNum = Int(Rnd() * mlngRange) + mlngMin
            lngRnd(1, I) = lngNewNum
         Next
         For J = I - 1 To 1 Step -1
            If lngRnd(1, I) = lngRnd(1, J) Then
               blnUsed = True
               Exit For
            End If
            blnUsed = False
         Next
      Loop While blnUsed
      MsgBox "Число: " & lngRnd(1, I), vbInformation, "Лото"
      With flexRnd
            .Clear
            .Rows = 1 + I
            .Cols = 3
      End With
      lngMin = mlngMax
      For J = 1 To I
         For K = 1 To I
            If lngMin > lngRnd(1, K) And lngRnd(2, K) = 0 Then
               lngMin = lngRnd(1, K)
               lngMinRow = K
            End If
         Next
         With flexRnd
            .TextMatrix(J, 0) = J
            .TextMatrix(J, 1) = lngMin
            lngRnd(2, lngMinRow) = 1
            lngMin = mlngMax
         End With
      Next
      For J = I To 1 Step -1
         lngRnd(2, J) = 0
         flexRnd.TextMatrix(J, 2) = lngRnd(1, J)
      Next
   End If
   If I = mlngRange Then Call GameOverMsg 'The Game Over message.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Input the minimal & maximal numbers.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Const lngDfltMin As Long = 1
   Const lngDfltMax As Long = 90
   Const strPromtMin As String = "От скольки?"
   Const strPromtMax As String = "До скольки?"
   Dim blnQuit As Boolean
   mlngMin = InpMinMax(strPromtMin, lngDfltMin, blnQuit) 'Input the minimum.
   If Not blnQuit Then 'Quit/continue?
InputMax:
      mlngMax = InpMinMax(strPromtMax, lngDfltMax, blnQuit) 'Input the maximum.
      If Not blnQuit Then 'Quit/continue?
         If (mlngMin > mlngMax) Then
            MsgBox "Второе число должно быть больше " & CStr(mlngMin) & ".", _
               vbExclamation, "Ошибка"
            GoTo InputMax 'Resume inputting the maximum.
         Else
            mlngRange = mlngMax - mlngMin + 1 'Define the min/max range.
         End If
      End If
   End If
   If blnQuit Then Unload Me 'Quit on an error in the InpMinMax procedure.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Input the min/max number.
Private Function InpMinMax(ByVal strPromt As String, ByVal lngDfltNum As Long, ByRef _
   blnQuit As Boolean) As Long
On Error GoTo ErrHnd
   InpMinMax = CLng(Trim(InputBox(strPromt, "Диапазон", lngDfltNum)))
Exit Function
ErrHnd:
   If MsgBox(Err.Description & String(2, vbCrLf) & "Продолжить игру?", vbYesNo + _
      vbCritical, "Ошибка") = vbYes Then 'Resume/quit?
      Resume
   Else
      blnQuit = True 'Mark to quit at a next function call.
   End If
End Function

' Resize the flexRnd grid.
Private Sub Form_Resize()
On Error GoTo ErrHnd
   With flexRnd
      .Width = Me.ScaleWidth
      .Height = Me.ScaleHeight - .Top
   End With
   With cmdRnd
      .Left = (Me.ScaleWidth - .Width) / 2
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' The Game Over message.
Private Sub GameOverMsg()
On Error GoTo ErrHnd
   MsgBox "Числа кончились. Игра окончена.", vbInformation, "Конец игры"
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
