Attribute VB_Name = "Util"
Option Explicit

' Switch cmdOK & cmdCancel buttons.
' Switch the mouse pointer.
' Switching the buttons is optional.
Public Sub SwchBtnMouse(ByRef frmForm As Form, ByVal blnEnable As Boolean, Optional _
   ByVal blnEscSwchBtn As Boolean)
On Error GoTo ErrHnd
   With frmForm
      If Not blnEscSwchBtn Then 'Switch the buttons, if required.
         .cmdOK.Enabled = blnEnable 'Buttons.
         .cmdCancel.Enabled = blnEnable
      End If
      Select Case blnEnable 'Mouse pointer
      Case True
         Screen.MousePointer = vbDefault
      Case False
         Screen.MousePointer = vbHourglass
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Message about a missing parameter & focus the control.
' Add an additional explanation to the label, if necessary, or show the calling
'  procedure's own promt.
Public Sub MissParam(ByRef ctlCtl As Control, Optional ByVal strLblCapt As String, _
   Optional ByVal strExplain As String, Optional strOwnPromt As String)
On Error GoTo ErrHnd
   Dim strPromt As String
   strLblCapt = CutColonAmpers(strLblCapt) 'Cut off the colon in the label's end.
   If strExplain <> "" Then 'Promt with/wothout an explanation.
      strPromt = LoadResString(20) & strLblCapt & Space$(1) & LCase$(CutColonAmpers _
         (strExplain)) & "'."
   ElseIf strOwnPromt <> "" Then 'Own promt.
      strPromt = strOwnPromt
   Else 'Promt w/o an explanation.
      strPromt = LoadResString(20) & strLblCapt & "'."
   End If
   MsgBox strPromt, vbExclamation, LoadResString(21)
   With ctlCtl
      If .Enabled And .Visible Then ctlCtl.SetFocus 'Focus, if enabled & visible.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Cut off the colon & ampersand, if any, from the specified label.
Public Function CutColonAmpers(ByVal strCapt As String) As String
On Error GoTo ErrHnd
   CutColonAmpers = CutChar(strCapt, ":")
   CutColonAmpers = CutChar(CutColonAmpers, "&")
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Cut off a character in the specified string.
Private Function CutChar(ByVal strTxt As String, ByVal strChar As String) As String
On Error GoTo ErrHnd
   Dim intLeng As String
   Dim intPostn As Integer
   Dim strBefore As String
   Dim strAfter As String
   intPostn = InStr(strTxt, strChar)
   If intPostn = 0 Then 'No sought character.
      CutChar = strTxt
   Else
      strBefore = Left$(strTxt, intPostn - 1) 'The string before the cut character.
      intLeng = Len(strTxt)
      strAfter = Right$(strTxt, intLeng - intPostn) 'The string after the cut character.
      CutChar = strBefore & strAfter 'Compose.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Refresh the lblDiamFrom & lblDiamTo controls in frmAppr/frmBrdStd forms by finding the
'  selected diameter in the respective adoDiam recordsets.
Public Sub RefrshDiamFrm(ByRef adoDiam As Adodc, ByVal strBoundTxt As String, ByRef _
   strDiamPrev As String, Optional ByVal blnIgnorePrev As Boolean)
On Error GoTo ErrHnd
   If blnIgnorePrev Or strDiamPrev <> strBoundTxt Then 'Proceed, if changed.
      strDiamPrev = strBoundTxt 'Save the origianal.
      With adoDiam.Recordset
         .MoveFirst
         .Find ("Diam = '" & strBoundTxt & "'")
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the data sorce for the specified data bound combo.
Public Sub SrcDbc(ByRef dbcCtl As DataCombo, ByRef adoCtl As Adodc, ByVal strBoundCol _
   As String, ByVal strLstFld As String)
On Error GoTo ErrHnd
   With dbcCtl
      Set .RowSource = adoCtl
      .BoundColumn = strBoundCol
      .ListField = strLstFld
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Switch on/off the specified control collection's TabStop's.
Public Sub SwchTabStopCtl(ByRef obColCtl As Object, ByVal intFst As Integer, ByVal _
   intLst As Integer, ByVal blnTabStop As Boolean)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = intFst To intLst 'Loop through the 1st to last controls.
      obColCtl(I).TabStop = blnTabStop
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Make the positive-size test. Return the size, if positive, or zero, if negative.
Public Function PostvSize(ByVal lngSize As Long) As Long
On Error GoTo ErrHnd
   If lngSize > 0 Then
      PostvSize = lngSize
   Else
      PostvSize = 0
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
