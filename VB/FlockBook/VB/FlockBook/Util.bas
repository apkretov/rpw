Attribute VB_Name = "Util"
Option Explicit

' Display the File menu as a pop-up menu.
Public Sub FileMnu(ByVal intButton As Integer)
On Error GoTo ErrHnd
   Const intMousRghtBtn As Integer = 2
   With frmMDI
      If intButton = intMousRghtBtn Then .PopupMenu .mnuFile 'Check the right button.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Prevent a duplication that adding the specified data form might have caused in a
'  specified control's _KeyPress procedure. If a new ID duplicates that of an open form
'  unload this duplicate data form.
' Format the control, if it's a text box.
' Reset the gobMsgInst object for later use.
' Return True only for those calling forms that need it to complete switching their
'  controls.
Public Function DuplFrmtRest(ByRef frmForm As Form, ByRef ctlCtl As Control) _
   As Boolean
On Error GoTo ErrHnd
   If gobMsgInst.DuplFrm Then
       Unload frmForm  'Prevent duplication.
   Else
      DuplFrmtRest = True
      gobMsgInst.Rest frmForm  'Reset gobMsgInst.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

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

' Switch on/off the specified ListView control. Prior to disabling, set the Hide
'  Selection option on to get rid of the mixed-colour view. Reset the option, if the
'  control is enabled.
Public Sub SwchListView(ByRef lvwListView As ListView, ByVal blnEnable As Boolean)
On Error GoTo ErrHnd
   lvwListView.HideSelection = Not blnEnable
'   lvwListView.HideSelection = IIf(blnEnable, False, True)
   lvwListView.Enabled = blnEnable
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

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

' Convert the specified date to string to save in the DB as:
'  - the SQL Server zero date, if zero;
'  - the actual date.
' Format the date to substitute the Day-to-Mon & Mon-to-Yere separation dots (Russian) by
'  slashes, if any.
Public Function DateStrDB(ByVal dtmDate As Date) As String
On Error GoTo ErrHnd
   Dim strDate As String
   Dim intSepartr1 As Integer
   Dim intSepartr2 As Integer
   If dtmDate = 0 Then
      DateStrDB = CStr(gobSetng.SQLDateZero) 'Zero date.
   Else 'Convert.
      strDate = CStr(dtmDate)
      intSepartr1 = InStr(strDate, ".")
      If intSepartr1 = 0 Then 'No dots?
         DateStrDB = dtmDate
      Else 'Substitute the dots with slashes.
         Mid(strDate, intSepartr1) = "/"
         intSepartr2 = InStr(intSepartr1, strDate, ".")
         Mid(strDate, intSepartr2) = "/"
         DateStrDB = strDate
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Convert the specified date to string to save in the DB as:
'  - the SQL Server zero date, if zero;
'  - the actual date.
' Format the date to substitute the Day-to-Mon & Mon-to-Yere separation dots (Russian) by
'  slashes, if any.
Public Function DateStrRpt(ByVal dtmDate As Date) As String
On Error GoTo ErrHnd
   Const dtmTempl As Date = #12/31/1999# 'The template date.
   Const intPostnMonTempl As Integer = 1 'US Egnlish month position.
   Const intPostnDayMonTempl As Integer = 3 'The Day-to-Month separator' position.
   Const intDayMon12 As Integer = 12 'Day or month = 12.
   Const strSepartrDB As String = "/" 'DB date separator.
   Dim strSepartr As String
   Dim strDateTempl As String
   Dim strDate As String
   Dim intSepartr1 As Integer
   Dim intSepartr2 As Integer
   Dim intPostnDayMon As Integer
   Dim intPostnMonYr As Integer
   Dim strDay As String
   Dim strMon As String
   If dtmDate = 0 Then
      DateStrRpt = CStr(gobSetng.SQLDateZero) 'Zero date.
   Else 'Convert.
      strDate = CStr(dtmDate)
      If InStr(CStr(dtmTempl), CStr(Month(dtmTempl))) = intPostnMonTempl Then 'Is the month in front by the current setting?
         DateStrRpt = DateDotToSlash(strDate) 'Substiture dots with slashes.
      Else
         strDateTempl = CStr(DateValue(dtmTempl)) 'The template date's string by the reginal set
         strSepartr = Mid$(strDateTempl, intPostnDayMonTempl, 1) 'The separator character.
         intPostnDayMon = InStr(strDate, strSepartr) 'The Day-Mon & Mon-Yr separators'
         intPostnMonYr = InStr(intPostnDayMon + 1, strDate, strSepartr) 'positions.
         strDay = Mid$(strDate, intPostnDayMon + 1, intPostnMonYr - intPostnDayMon - 1) 'Day.
         strMon = Left$(strDate, intPostnDayMon - 1) 'Month.
         DateStrRpt = strDay & strSepartrDB & strMon & strSepartrDB & Mid$(strDate, _
            intPostnMonYr + 1)
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Convert the specified number to a string to save in the DB. Substitute the decimal
'  separation comma (Russian) by a dot, if any.
Public Function NumStrDB(ByVal sngNum As Single) As String
On Error GoTo ErrHnd
   Dim strNum As String
   Dim intSepartr As Integer
   strNum = CStr(sngNum)
   If sngNum <> 0 Then 'Not zero?
      strNum = CStr(sngNum)
      intSepartr = InStr(strNum, ",")
      If intSepartr <> 0 Then Mid(strNum, intSepartr) = "." 'Any comma to substitute?
   End If
   NumStrDB = strNum
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Simulate pressing Enter in the data form's ID control.
' Avoid opening another duplicate data form by ivoking the LostFocus procedure.
Public Sub IDCtlEnter(ByRef obDatFrm As DatFrm, ByVal intKeyAscii As Integer)
On Error GoTo ErrHnd
   If intKeyAscii = gobFormtCtl.AscEnter Then
      With obDatFrm
      .IDCtlPress intKeyAscii 'Press Enter.
      .IDCtlLostFoc 'Avoid duplication.
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Syncronise the settings form's browsing list to the ID control.
Public Sub SyncBrs(ByRef obDatFrm As DatFrm)
On Error GoTo ErrHnd
   Dim obSetngFrm As SetngFrm
   If obDatFrm.IsSetngFrm Then
      Set obSetngFrm = obDatFrm.FrmHost
      obSetngFrm.SyncBrs
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the data sorce for the specified data bound combo.
Public Sub DbcSetRowSrc(ByRef dbcCtl As DataCombo, ByRef adoCtl As Adodc, ByVal strBoundCol _
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

' Read the specified datacombo's Boundtext property from its data providing Ado control.
' The procedure is necessary, when the data is read from the datacombo that has been
'  unchanged. In such a case, the datacombo's Boundtext is substituted with its Text
'  property for an unknown reason.
Public Function DbcReadBoundTxt(ByVal dbcCtl As DataCombo, ByVal adoCtl As Adodc) _
   As String
On Error GoTo ErrHnd
   With adoCtl.Recordset
      .Find (dbcCtl.ListField & " = '" & dbcCtl & "'")
      If .BOF = False And .EOF = False Then DbcReadBoundTxt = .Fields(dbcCtl.BoundColumn)
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

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

'Convert a pure breed's cross breed code to a breed name.
Public Function BrdCodeToNam(ByVal strIDBrd As String) As String
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim obTblBrd As TblBrd
   Set obTblBrd = New TblBrd
      Set obDatTbl = obTblBrd
   obDatTbl.Sel strIDBrd
   BrdCodeToNam = obTblBrd.Brd
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

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

' Set/reset the data form's caption.
' If set, write the data form's host form's oririnal caption & the data form's ID
'  separated with a hyphen.
Public Sub FrmCapt(ByVal obDatFrm As DatFrm, ByVal blnSetVsRest As Boolean)
On Error GoTo ErrHnd
   With obDatFrm
      Select Case blnSetVsRest
      Case True 'Set.
         .FrmHost.Caption = .FrmHostCaptOrig & Space(1) & "-" & Space(1) & .IDFrm
      Case False 'Reset.
         .FrmHost.Caption = .FrmHostCaptOrig
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Format the date to substitute the Day-to-Mon & Mon-to-Yere separation dots (Russian) by
'  slashes, if any.
Private Function DateDotToSlash(ByVal strDate As String) As String
On Error GoTo ErrHnd
   Dim intSepartr1 As Integer
   Dim intSepartr2 As Integer
   intSepartr1 = InStr(strDate, ".")
   If intSepartr1 = 0 Then 'No dots?
      DateDotToSlash = strDate
   Else 'Substitute the dots with slashes.
      Mid(strDate, intSepartr1) = "/"
      intSepartr2 = InStr(intSepartr1, strDate, ".")
      Mid(strDate, intSepartr2) = "/"
      DateDotToSlash = strDate
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
