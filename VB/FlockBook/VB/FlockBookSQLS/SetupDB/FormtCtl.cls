VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "FormtCtl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintLengIDFarm As Integer = 2
Const mintLengIDShG As Integer = 6
Const mintLengIDBrd As Integer = 2
Const mintAscEngUpA As Integer = 65 'KeyAscii "A".
Const mintAscEngLowA As Integer = 97 'KeyAscii "a".
Const mintAscEngLowZ As Integer = 122 'KeyAscii "z".
Const mintAscRusUpA As Integer = 192 'KeyAscii "RusA".
Const mintAscRusLowA As Integer = 224 'KeyAscii "Rusa".
Const mintAscRusLowZ As Integer = 255 'KeyAscii "Rusz".

Private Type ErrHndTemplTp
   OrigIdx As Integer
   OrigDescr As String
   TestIdx As Integer
   TestDescr As String
   Templ As String
End Type

' Return a formatted number string with/without a fraction.
Public Function NumFrac(ByVal sngNum As Single, Optional ByVal blnNoFrac As Boolean _
   = False) As String
On Error GoTo ErrHnd
   If blnNoFrac Then 'Integer.
      NumFrac = Format$(sngNum, "0")
   Else 'Single.
      NumFrac = Format$(sngNum, "0.0")
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a formatted number string to show HDD space in MB.
Public Function NumMB(ByVal sngNum As Single) As String
On Error GoTo ErrHnd
   NumMB = Format$(sngNum, "#,##0.00")
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Type the date substituting the comma with dot to standardise the English key board to
'  Russian in terms of typing the date.
Public Sub TypeDate(ByRef intKeyAscii As Integer)
On Error GoTo ErrHnd
   Const intAscComma As Integer = 44 'KeyAscii "Comma"
   Const intAscDot As Integer = 46 'KeyAscii "Dot"
   If intKeyAscii = intAscComma Then intKeyAscii = intAscDot 'Substitute.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validte the text box by formatting the text as a positive integer/single number.
' The number must be in the min/mas range.
' Return True, if succeeds.
Public Function VldNum(ByRef ctlTxtDbc As Control, ByVal sngMin As Single, ByVal sngMax _
   As Single, Optional ByVal blnNoFrac As Boolean) As Boolean
On Error GoTo ErrHnd
   Const intErrTyp As Integer = 13 'Type mismatch.
'   Const sngTempl As Single = 15.5 'Single template.
   Dim udtErrHndTempl As ErrHndTemplTp
   Dim blnFail As Boolean
   If IsTxtDbcDropdown(ctlTxtDbc) Then
      Call SelTxt(ctlTxtDbc) 'Select.
      With ctlTxtDbc
         If Trim$(.Text) > "" Then
            If blnNoFrac Then 'Integer.
               udtErrHndTempl.Templ = CStr(Int(sngMax)) 'Template for the ErrHndTempl proc.
               .SelText = Format$(Abs(CLng(.Text)), "0")  'Validate by formatting.
            Else 'Single.
               udtErrHndTempl.Templ = CStr(sngMax) 'Template for the ErrHndTempl proc.
               .SelText = Format$(Abs(CSng(.Text)), "0.0") 'Validate by formatting.
            End If
            blnFail = Not VldNumMinMax(.Text, sngMin, sngMax) 'Validate the min/max.
         Else
            .Text = NumFrac(0, blnNoFrac) 'Insert zero.
         End If
      End With
   End If
   VldNum = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
   With udtErrHndTempl 'Handle the error.
      .OrigIdx = Err.Number
      .OrigDescr = Err.Description
      .TestIdx = intErrTyp
      .TestDescr = LoadResString(23)
   End With
   Call ErrHndTempl(udtErrHndTempl, ctlTxtDbc)
End Function

' Return True, unless the specified text box's clip text contains a number.
Public Function BlankNum(ByVal strText As String) As Boolean
On Error GoTo ErrHnd
   strText = Trim$(strText)
   If strText = "" Then
      BlankNum = True 'No figures.
   ElseIf CSng(strText) = 0 Then
      BlankNum = True 'Zero value.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the ShG-related data form's ID control that 6 characters are inputted in it.
' Restrict the focus, if failes.
Public Sub VldIDCtlShG(ByRef txtCtl As TextBox, ByVal strLblCapt As String, _
   ByRef blnCancel As Boolean)
On Error GoTo ErrHnd
   Call VldIDCtl(mintLengIDShG, txtCtl, strLblCapt, blnCancel)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the ShG/farm-related data form's ID control that the required number of
'  characters be inputted in it.
' Restrict the focus, if failes. Otherwise convert the text to the upper case.
Private Sub VldIDCtl(ByVal intLengID As Integer, ByRef txtCtl As TextBox, ByVal _
   strLblCapt As String, ByRef blnCancel As Boolean)
On Error GoTo ErrHnd
   Dim strPromt As String
   strLblCapt = Util.CutColonAmpers(strLblCapt) 'Cut off the colomn & ampersand.
   strPromt = LoadResString(222) & strLblCapt & LoadResString(225) & CStr _
      (intLengID) & LoadResString(226) 'The IDFrmCtl field must be full.
   If Not VldIDLeng(txtCtl, False, intLengID, strPromt) Then
'      txtCtl = UCase(txtCtl) 'Upper case.
'   Else
      blnCancel = True 'Restrict the focus.
      txtCtl.SetFocus 'Focus the control after the message.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate that 6 or none characters are inputted. Restrict the focus, if failes.
' Return True, if succeeds.
Public Function VldIDShG(ByRef txtCtl As TextBox, ByVal strLblCapt As String) _
   As Boolean
On Error GoTo ErrHnd
   VldIDShG = VldID(mintLengIDShG, txtCtl, strLblCapt)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that the required number of characters or none characters be inputted.
'  Focus the control, if failes.
' Convert the text to the upper case.
' Return True, if succeeds.
Private Function VldID(ByVal intLengID As Integer, ByRef txtCtl As TextBox, _
   ByVal strLblCapt As String) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   strLblCapt = Util.CutColonAmpers(strLblCapt) 'Cut off the colomn & ampersand.
   strPromt = LoadResString(222) & strLblCapt & LoadResString(223) & CStr(intLengID) _
      & LoadResString(224) 'The non-IDFrmCtl field can be full or blank.
   If VldIDLeng(Trim$(txtCtl), True, intLengID, strPromt) Then
      VldID = True 'Succeeded.
   Else
      txtCtl.SetFocus 'Focus the control after the message.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate that 2 or none characters are inputted. Restrict the focus, if failes.
' Return True, if succeeds.
Public Function VldIDFarm(ByRef txtCtl As TextBox, ByVal strLblCapt As String) _
   As Boolean
On Error GoTo ErrHnd
   VldIDFarm = VldID(mintLengIDFarm, txtCtl, strLblCapt)
'   VldIDFarm = VldID(mintLengIDFarm, txtCtl, strLblCapt, blnCancel)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the farm-related data form's ID control that 2 characters be inputted in it.
' Restrict the focus, if failes.
Public Sub VldIDCtlFarm(ByRef txtCtl As TextBox, ByVal strLblCapt As String, _
   ByRef blnCancel As Boolean)
On Error GoTo ErrHnd
   Call VldIDCtl(mintLengIDFarm, txtCtl, strLblCapt, blnCancel)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the breed-related data form's ID control that 2 characters be inputted in it.
' Restrict the focus, if failes.
Public Sub VldIDCtlBrd(ByRef txtCtl As TextBox, ByVal strLblCapt As String, ByRef _
   blnCancel As Boolean)
On Error GoTo ErrHnd
   Call VldIDCtl(mintLengIDBrd, txtCtl, strLblCapt, blnCancel)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate that 2 or none characters be inputted. Restrict the focus, if failes.
' Return True, if succeeds.
Public Function VldIDBrd(ByRef txtCtl As TextBox, ByVal strLblCapt As String) _
   As Boolean
On Error GoTo ErrHnd
   VldIDBrd = VldID(mintLengIDBrd, txtCtl, strLblCapt)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' IDFarm Length.
Public Property Get LengIDFarm() As Integer
   LengIDFarm = mintLengIDFarm
End Property

' IDShG Length.
Public Property Get LengIDShG() As Integer
   LengIDShG = mintLengIDShG
End Property

' IDBrd Length.
Public Property Get LengIDBrd() As Integer
   LengIDBrd = mintLengIDBrd
End Property

' Convert a typed letter to the upper case.
' Prior to convertion, validate if the specified intKeyAscii code evaluates to a lower case
'  letter.
Public Function UpCase(ByVal intKeyAscii As Integer) As Integer
On Error GoTo ErrHnd
   Dim intShift As Integer
   Select Case intKeyAscii 'Calculate a low-to-up shift.
   Case mintAscEngLowA To mintAscEngLowZ 'Eng a-z.
      intShift = mintAscEngUpA - mintAscEngLowA
   Case mintAscRusLowA To mintAscRusLowZ 'Rus à-ÿ.
      intShift = mintAscRusUpA - mintAscRusLowA
   End Select
   UpCase = intKeyAscii + intShift 'Shift.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' KeyAscii "Enter"
Public Property Get AscEnter() As Integer
   Const intAscEnter As Integer = 13 'KeyAscii "Enter"
   AscEnter = intAscEnter
End Property

' KeyAscii "AscEngUpA"
Public Property Get AscEngUpA() As Integer
   AscEngUpA = mintAscEngUpA
End Property

' KeyAscii "AscEngUpZ"
Public Property Get AscEngUpZ() As Integer
   Const intAscEngUpZ As Integer = 90 'KeyAscii "Z".
   AscEngUpZ = intAscEngUpZ
End Property

' KeyAscii "AscEngLowA"
Public Property Get AscEngLowA() As Integer
   AscEngLowA = mintAscEngLowA
End Property

' KeyAscii "AscEngLowZ"
Public Property Get AscEngLowZ() As Integer
   AscEngLowZ = mintAscEngLowZ
End Property

' KeyAscii "AscRusUpA"
Public Property Get AscRusUpA() As Integer
   AscRusUpA = mintAscRusUpA
End Property

' KeyAscii "AscRusUpZ"
Public Property Get AscRusUpZ() As Integer
   Const intAscRusUpZ As Integer = 223 'KeyAscii "RusZ".
   AscRusUpZ = intAscRusUpZ
End Property

' KeyAscii "AscRusLowA"
Public Property Get AscRusLowA() As Integer
   AscRusLowA = mintAscRusLowA
End Property

' KeyAscii "RusLowZ"
Public Property Get AscRusLowZ() As Integer
   AscRusLowZ = mintAscRusLowZ
End Property

' KeyCode "Esc"
Public Property Get CodeEsc() As Integer
   Const intCodeEsc As Integer = 27 'KeyCode "Esc"
   CodeEsc = intCodeEsc
End Property

' KeyCode "Del"
Public Property Get CodeDel() As Integer
   Const intCodeDel As Integer = 46 'KeyCode "Del"
   CodeDel = intCodeDel
End Property

' Return False, if fewer than specified number (6 of 2) of characters are inputted in an
'  ID control.
Private Function VldIDLeng(ByVal strText As String, ByVal blnAllowBlnk As Boolean, _
   ByVal intLengID As Integer, ByVal strPromt As String) As Boolean
On Error GoTo ErrHnd
   Dim intLeng As Integer
   Dim blnFail As Boolean
   intLeng = Len(strText)
   Select Case blnAllowBlnk 'Distinguish by if blakn field is alowed.
   Case True 'Allowed.
      If intLeng > 0 And intLeng < intLengID Then blnFail = True 'Failed.
   Case False 'Not allowed.
      If intLeng < intLengID Then blnFail = True 'Failed.
   End Select
   If blnFail Then MsgBox strPromt, vbExclamation, LoadResString(131) 'Message, if failed.
   VldIDLeng = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Resize the specified lines' width to the window's scale width.
Public Sub ResizeLin(ByRef frmForm As Form, ByRef linLine1 As Line, ByRef linLine2 _
   As Line)
On Error GoTo ErrHnd
   With frmForm
      linLine1.X1 = .ScaleLeft
      linLine1.X2 = .ScaleWidth
      linLine2.X1 = .ScaleLeft
      linLine2.X2 = .ScaleWidth
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Select the text control's text.
' Before selecting, check the controls type to be TextBox or dropdown DataCombo.
Public Sub SelTxt(ByRef ctlTxtDbc As Control)
On Error GoTo ErrHnd
   Dim intLeng As Integer
   If IsTxtDbcDropdown(ctlTxtDbc) Then
      With ctlTxtDbc
         intLeng = Len(Trim$(.Text)) 'Text box.
         If intLeng > 0 Then 'Proceed, if filled.
            .SelStart = 0 'Start highlight before first character.
            .SelLength = intLeng 'Highlight to end of text.
         End If
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Handle the specified validation error. Show the explanatiory message about a wrong data
'  inputted & give a correct template.
' Restrict the focus to the control, if failes.
Private Sub ErrHndTempl(ByRef udtErrHndTempl As ErrHndTemplTp, ByRef ctlTxtDbc _
   As Control, Optional ByRef blnCancel As Boolean)
On Error GoTo ErrHnd
   Dim strPromt As String
   With udtErrHndTempl
      If .OrigIdx = .TestIdx Then 'The specified error.
         blnCancel = True 'Restrict the focus.
         strPromt = .TestDescr & vbCrLf & vbCrLf & LoadResString(24) & Space$(1) & _
            .Templ
         MsgBox strPromt, vbExclamation, LoadResString(131) 'Promt the template.
         ctlTxtDbc.SetFocus
      Else 'Another error.
         MsgBox .OrigDescr
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate that the number be in the min/mas range.
' Return True, if succeeds.
Private Function VldNumMinMax(ByVal strText As String, ByVal sngMin As Single, ByVal _
   sngMax As Single) As Boolean
On Error GoTo ErrHnd
   Dim strPromt As String
   Dim blnFail As Boolean
   If (sngMin <> 0) And (CSng(strText) <> 0 And CSng(strText) < sngMin) Then 'Validate Min,
      blnFail = True 'Failed.                                               'if any & > 0.
   ElseIf CSng(strText) <> 0 And CSng(strText) > sngMax Then 'Validate Max, if > 0.
      blnFail = True 'Failed.
   End If
   If blnFail Then 'Proceed, if failed.
      strPromt = LoadResString(25) & sngMin & LoadResString(26) & sngMax & "."
      MsgBox strPromt, vbExclamation, LoadResString(131)
   End If
   VldNumMinMax = Not blnFail 'Succeeded/failed.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Validate the date that it must not be bigger than the current date.
' Restrict the focus to the control, if failes.
Private Sub VldDateCrnt(ByVal strText As String, ByRef blnCancel As Boolean)
On Error GoTo ErrHnd
   If DateValue(strText) > Date Then 'Proceed, if bigger.
      blnCancel = True 'Restrict the focus.
      MsgBox LoadResString(27), vbExclamation, LoadResString(131)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' MinGrease.
Public Property Get MinGrease() As Single
   Const sngMinGrease As Single = 0.3
   MinGrease = sngMinGrease
End Property

' MaxGrease.
Public Property Get MaxGrease() As Single
   Const sngMaxGrease As Single = 16
   MaxGrease = sngMaxGrease
End Property

' LengMin.
Public Property Get MinLeng() As Single
   Const sngMinLeng As Single = 5
   MinLeng = sngMinLeng
End Property

' MaxLeng.
Public Property Get MaxLeng() As Single
   Const sngMaxLeng As Single = 25
   MaxLeng = sngMaxLeng
End Property

' MinWt1Yr.
Public Property Get MinWt1Yr() As Single
   Const sngMinWt1Yr As Single = 25
   MinWt1Yr = sngMinWt1Yr
End Property

' MaxWt1Yr.
Public Property Get MaxWt1Yr() As Single
   Const sngMaxWt1Yr As Single = 130
   MaxWt1Yr = sngMaxWt1Yr
End Property

' Return True if the specified control is text box or drop-down data combo bos i.e.
'  allows to cut/copy/paste or select its text.
Public Function IsTxtDbcDropdown(ByVal ctlTxtDbc As Control) As Boolean
On Error GoTo ErrHnd
   If TypeOf ctlTxtDbc Is TextBox Then
      IsTxtDbcDropdown = True
   ElseIf TypeOf ctlTxtDbc Is DataCombo Then
      If ctlTxtDbc.Style = dbcDropdownCombo Then IsTxtDbcDropdown = True 'DropdownCombo only.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

