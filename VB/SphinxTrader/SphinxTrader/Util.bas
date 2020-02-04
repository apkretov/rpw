Attribute VB_Name = "Util"
Option Explicit

Public gfrmClient As frmClient

Sub LoadResStrings(frm As Form)
    On Error Resume Next
    Dim ctl As Control
    Dim obj As Object
    Dim fnt As Object
    Dim sCtlType As String
    Dim nVal As Integer
    frm.Caption = LoadResString(CInt(frm.Tag)) 'set the form's caption
    Set fnt = frm.Font 'set the font
    fnt.Name = LoadResString(20)
    fnt.Size = CInt(LoadResString(21))
    For Each ctl In frm.Controls 'set the controls' captions using the caption property for menu items and the Tag property for all other controls
        Set ctl.Font = fnt
        sCtlType = TypeName(ctl)
        If sCtlType = "Label" Then
            ctl.Caption = LoadResString(CInt(ctl.Tag))
        ElseIf sCtlType = "Menu" Then
            ctl.Caption = LoadResString(CInt(ctl.Caption))
        ElseIf sCtlType = "TabStrip" Then
            For Each obj In ctl.Tabs
                obj.Caption = LoadResString(CInt(obj.Tag))
                obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
            Next
        ElseIf sCtlType = "Toolbar" Then
            For Each obj In ctl.Buttons
                obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
            Next
        ElseIf sCtlType = "ListView" Then
            For Each obj In ctl.ColumnHeaders
                obj.Text = LoadResString(CInt(obj.Tag))
            Next
        Else
            nVal = 0
            nVal = Val(ctl.Tag)
            If nVal > 0 Then ctl.Caption = LoadResString(nVal)
            nVal = 0
            nVal = Val(ctl.ToolTipText)
            If nVal > 0 Then ctl.ToolTipText = LoadResString(nVal)
        End If
    Next
End Sub

' Login & load the main MDI form.
Sub Main()
On Error GoTo ErrHnd
   Dim frmNewLogin As frmLogin
   Set frmNewLogin = frmLogin
   frmNewLogin.Show vbModal
   If Not frmNewLogin.Success Then
      End 'Login Failed so exit app
   Else
      Unload frmNewLogin
      Set gfrmClient = New frmClient
      gfrmClient.Show
'      Set gobjDecmSeparat = New DecmSeparat ' Get locale decimal separator.
'      gfrmClient.SetTools ' Set tick monitoring notify lables.
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Number & vbTab & Err.Description
   End 'Exit app.
End Sub

' Validate filling-out controls.
Public Function ValidTxtBox(txtCtrl As TextBox, ByVal strLabel As String) As Boolean
    If Len(Trim(txtCtrl)) <> 0 Then 'Login entered?
        ValidTxtBox = True
    Else
        MsgBox "Заполните поле '" & strLabel & "'!"
    End If
End Function

' Set adoTools.
Public Sub SetAdoTools(adoTools As Adodc)
   adoTools.ConnectionString = gcnnConnServ.ConnectionString
   adoTools.RecordSource = "Tools"
End Sub

' Link the DDE price lables.
Public Sub LinkPrices(lblPrice As Label, ByVal intLinkMode As Integer, ByVal strTool As String, ByVal strLinkTopic As String)
On Error GoTo ErrHnd
   Const intNone As Integer = 0 'No link mode
   Const strDDEApp As String = "MT4" 'The DDE-source external application name.
   Const intErrNoDDE As Integer = 285 'Error: Foreign application won't perform DDE method or operation.
   lblPrice.LinkMode = intNone 'Clear DDE Link.
   lblPrice.LinkTopic = strDDEApp & "|" & strLinkTopic 'Sets up link with VB source.
   lblPrice.LinkItem = strTool 'Set link to text box on source.
   lblPrice.LinkMode = intLinkMode 'Reestablish new LinkMode.
Exit Sub
ErrHnd:
    If Err.Number <> intErrNoDDE Then MsgBox Err.Number & vbTab & Err.Description 'An error other than Foreign application won't perform DDE method or operation?
End Sub

' Convert a number into currency.
Public Function ConvCur(ByVal strNum As String) As Currency
On Error GoTo ErrHnd
   Const intTypeMismatch As Integer = 13 'The Type Mismatch error number.
   ConvCur = CCur(strNum) 'Convert to currency.
Exit Function
ErrHnd:
   If Err.Number = intTypeMismatch Then 'A non-number entry i.e. the expected Type Mismatch error?
      ConvCur = CCur(ChanWrongDecmSymb(strNum)) 'Convert to currency.
   Else 'Another error.
      MsgBox Err.Number & vbTab & Err.Description
   End If
End Function

' Change a wrong locale decimal symbol from the dot to the comma or vice versa.
Private Function ChanWrongDecmSymb(ByVal strNum As String) As String
On Error GoTo ErrHnd
   Const strDecmSymbDot As String = "." 'Dot/comma decimal symbols.
   Const strDecmSymbCom As String = ","
   Dim strDecmSymb As String
   Dim intPostn As Integer
   Dim strBefore As String
   Dim strAfter As String
   intPostn = InStr(strNum, strDecmSymbDot)
   If intPostn > 0 Then 'Found a dot?
      strDecmSymb = strDecmSymbCom 'Remember the decimal symbol.
   Else 'No dot. Search a comma.
      strDecmSymb = strDecmSymbDot
      intPostn = InStr(strNum, strDecmSymbCom)
   End If
   If intPostn = 0 Then 'No decimal symbol?
      ChanWrongDecmSymb = strNum 'Return the number unchnaged.
   Else
      strBefore = Left$(strNum, intPostn - 1) 'The string before the cut character.
      strAfter = Right$(strNum, Len(strNum) - intPostn) 'The string after the cut character.
      ChanWrongDecmSymb = strBefore & strDecmSymb & strAfter 'Compose.
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

