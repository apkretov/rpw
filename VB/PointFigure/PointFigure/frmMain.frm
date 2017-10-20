VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.MDIForm frmMain 
   BackColor       =   &H8000000C&
   Caption         =   "PointFigure"
   ClientHeight    =   8505
   ClientLeft      =   1860
   ClientTop       =   -510
   ClientWidth     =   11865
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "MDIForm1"
   LockControls    =   -1  'True
   Begin MSComctlLib.ProgressBar prgProgrBar 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   7980
      Visible         =   0   'False
      Width           =   11865
      _ExtentX        =   20929
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   1
   End
   Begin VB.Timer tmrRefrsh 
      Interval        =   10
      Left            =   2040
      Top             =   720
   End
   Begin MSComctlLib.StatusBar staStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   8235
      Width           =   11865
      _ExtentX        =   20929
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   3
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   15293
            Text            =   "Ready"
            TextSave        =   "Ready"
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "04.12.2008"
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "12:39"
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   0
      Top             =   600
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.Toolbar tlbToolBar 
      Align           =   1  'Align Top
      Height          =   450
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   11865
      _ExtentX        =   20929
      _ExtentY        =   794
      ButtonWidth     =   820
      ButtonHeight    =   794
      Style           =   1
      ImageList       =   "imlToolbarIcons(1)"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   6
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   4
            Object.Width           =   75
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "Open"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Print"
            Object.ToolTipText     =   "Print"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Refresh"
            Object.ToolTipText     =   "Refresh"
            ImageIndex      =   1
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Index           =   0
      Left            =   600
      Top             =   600
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0442
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0554
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0666
            Key             =   "Line"
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList imlToolbarIcons 
      Index           =   1
      Left            =   1320
      Top             =   600
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   24
      ImageHeight     =   24
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   4
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0778
            Key             =   "Refresh"
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":0E8A
            Key             =   "Open"
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":13CE
            Key             =   "Print"
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmMain.frx":1A52
            Key             =   "Line"
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open..."
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "&Close"
         Shortcut        =   ^{F4}
      End
      Begin VB.Menu mnuFileBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "&Print..."
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "&View"
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "&Toolbar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar 
         Caption         =   "Status &Bar"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewOptions 
         Caption         =   "&Options..."
      End
   End
   Begin VB.Menu mnuTools 
      Caption         =   "&Tools"
      Begin VB.Menu mnuToolsTuneFineLft 
         Caption         =   "Fine Tune &Left                                    Left"
      End
      Begin VB.Menu mnuToolsTuneFineRht 
         Caption         =   "Fine Tune &Right                                  Right"
      End
      Begin VB.Menu mnuToolsTuneFastLft 
         Caption         =   "Fast Tune &Left                                    Ctrl + Left"
      End
      Begin VB.Menu mnuToolsTuneFastRht 
         Caption         =   "Fast Tune &Right                                  Ctrl + Right"
      End
      Begin VB.Menu mnuToolsBar0 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsRefrsh 
         Caption         =   "Re&fresh                                               F5"
      End
      Begin VB.Menu mnuToolsRestore 
         Caption         =   "Re&store                                               Ctrl + F5"
      End
      Begin VB.Menu mnuToolsIncrUp 
         Caption         =   "Increment &Up                                      Page Up"
      End
      Begin VB.Menu mnuToolsIncrDown 
         Caption         =   "Increment &Down                                 Page Down"
      End
      Begin VB.Menu mnuToolsBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsStep 
         Caption         =   "&Step by step"
      End
      Begin VB.Menu mnuToolsBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuToolsLine 
         Caption         =   "L&ine"
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "&Window"
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "&Cascade"
      End
      Begin VB.Menu mnuWindowTileHorizontal 
         Caption         =   "Tile &Horizontal"
      End
      Begin VB.Menu mnuWindowTileVertical 
         Caption         =   "Tile &Vertical"
      End
      Begin VB.Menu mnuWindowArrangeIcons 
         Caption         =   "&Arrange Icons"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mstrChildFrm As String = "ChildFrm" 'The child forms' setting keys.
Const mstrFrmCount As String = "FrmCount"
Const mstrWndState As String = "WndState"
Const mstrLft As String = "Lft" 'Left.
Const mstrTop As String = "Top" 'Top.
Const mstrWdth As String = "Wdth" 'Width.
Const mstrHght As String = "Hght" 'Height.
Const mstrFlPath As String = "FlPath" 'File path.
Const mstrSymbol As String = "Symbol" 'File title.
Const mstrIncr As String = "Incr"
Const mstrRevers As String = "Revers"
Const mstrTimeFst As String = "TimeFst" '1st canlestick's time.

' Apply the previuosly saved settings.
Private Sub MDIForm_Load()
On Error GoTo ErrHnd
   Me.Left = GetSetting(App.Title, "Settings", "MainLeft", 1000)
   Me.Top = GetSetting(App.Title, "Settings", "MainTop", 1000)
   Me.Width = GetSetting(App.Title, "Settings", "MainWidth", 6500)
   Me.Height = GetSetting(App.Title, "Settings", "MainHeight", 6500)
   Call ChildRestore 'Restore the previous child forms' charts.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Load a new document.
' Return True, if the new form's parameters are completely inputted.
Private Function LoadNewFrm(ByVal strFileTitle As String) As Boolean
On Error GoTo ErrHnd
   Dim frmNewChart As frmChart
   Dim lngWdth As Long
   Dim lngHght As Long
   tmrRefrsh.Enabled = False 'Disable refreshing other forms, if any, until this is loaded.
   If Not Me.ActiveForm Is Nothing Then 'Get the size for the new form.
      lngWdth = Me.ActiveForm.Width 'Copy any open form's.
      lngHght = Me.ActiveForm.Height
   Else
      lngWdth = Me.ScaleWidth 'Stretch to the full screen.
      lngHght = Me.ScaleHeight
   End If
   Set frmNewChart = New frmChart
   If frmNewChart.ParamInput(strFileTitle) Then 'Input the parameters.
      frmNewChart.Width = lngWdth 'Resize.
      frmNewChart.Height = lngHght
'      frmNewChart.Move 0, 0, Me.ScaleWidth, Me.ScaleHeight 'Place to the left top & resize.
      frmNewChart.Show
      LoadNewFrm = True 'Succeeded.
   Else
      Set frmNewChart = Nothing 'Destroy.
   End If
   tmrRefrsh.Enabled = True 'Resume.
Exit Function
ErrHnd:
   MsgBox Err.Description
Debug.Assert 0 = 1 'Verify
   tmrRefrsh.Enabled = True 'Resume.
End Function

' Save the MDI & child forms' settings to apply at a next loading.
Private Sub MDIForm_QueryUnload(Cancel As Integer, UnloadMode As Integer)
On Error GoTo ErrHnd
   Const strSettings As String = "Settings"
   If Me.WindowState <> vbMinimized Then 'MDI's settings.
      SaveSetting App.Title, strSettings, "MainLeft", Me.Left
      SaveSetting App.Title, strSettings, "MainTop", Me.Top
      SaveSetting App.Title, strSettings, "MainWidth", Me.Width
      SaveSetting App.Title, strSettings, "MainHeight", Me.Height
   End If
   If Not Me.ActiveForm Is Nothing Then 'Any child form open?
'      Select Case MsgBox("Save the charts?", vbYesNoCancel + vbQuestion)
'      Case vbYes 'Save.
         Call mnuFileSave_Click
'      Case vbCancel 'Cancel exiting.
'         Cancel = 1
'      End Select
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save all open forms' settings in the Windows registry.
Private Sub mnuFileSave_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then
      Call ChildDeleteSetting 'Delete the previous child forms' settings, if any.
      Call ChildSaveSetting 'Save the child forms' settings, if any.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Decrease the increment & redraw the chart.
Private Sub mnuToolsIncrDown_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.AdjustIncr(-1)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Increase the increment & redraw the chart.
Private Sub mnuToolsIncrUp_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.AdjustIncr(1)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Draw a 45-degree line.
Private Sub mnuToolsLine_Click()
On Error GoTo ErrHnd
Debug.Assert 0 = 1 'Verify
   If Not Me.ActiveForm Is Nothing Then 'Any open form?
      With mnuToolsLine
   Debug.Assert 0 = 1 'Verify Case
         Select Case .Checked
         Case True 'Selected.
   Debug.Assert 0 = 1 'Verify Case
            .Checked = False 'Deselect.
         Case False 'Deselected.
   Debug.Assert 0 = 1 'Verify Case
            .Checked = True 'Enable drawing.
         End Select
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restore the chart based on the 1st candlestick.
Private Sub mnuToolsRestore_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.Restore
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fast tune the chart to the left.
Private Sub mnuToolsTuneFastLft_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.TuneFastLft
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fast tune the chart to the right.
Private Sub mnuToolsTuneFastRht_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.TuneFastRht
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fine tune the chart to the left.
Private Sub mnuToolsTuneFineLft_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.TuneFineLft
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Tune the chart to the right.
Private Sub mnuToolsTuneFineRht_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.TuneFineRht
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Adjust the box side size.
Private Sub mnuViewOptions_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.AdjustBox
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the chart with the latest settings.
Private Sub mnuToolsRefrsh_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Call Me.ActiveForm.Refrsh
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the Draw Step by Step mode.
Private Sub mnuToolsStep_Click()
On Error GoTo ErrHnd
   With mnuToolsStep
      Select Case .Checked
      Case False
         .Checked = True
      Case True
         .Checked = False
      End Select
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub tlbToolBar_ButtonClick(ByVal Button As MSComctlLib.Button)
   On Error Resume Next
   Select Case Button.Key
      Case "Open"
         mnuFileOpen_Click
      Case "Print"
         mnuFilePrint_Click
      Case "Refresh"
Debug.Assert 0 = 1 'Verify
         mnuToolsRefrsh_Click
      Case "Line"
         'ToDo: Add 'Line' button code.
   End Select
End Sub

Private Sub mnuWindowArrangeIcons_Click()
   Me.Arrange vbArrangeIcons
End Sub

Private Sub mnuWindowTileVertical_Click()
   Me.Arrange vbTileVertical
End Sub

Private Sub mnuWindowTileHorizontal_Click()
   Me.Arrange vbTileHorizontal
End Sub

Private Sub mnuWindowCascade_Click()
   Me.Arrange vbCascade
End Sub

Private Sub mnuViewStatusBar_Click()
   mnuViewStatusBar.Checked = Not mnuViewStatusBar.Checked
   staStatusBar.Visible = mnuViewStatusBar.Checked
End Sub

Private Sub mnuViewToolbar_Click()
   mnuViewToolbar.Checked = Not mnuViewToolbar.Checked
   tlbToolBar.Visible = mnuViewToolbar.Checked
End Sub

Private Sub mnuFileExit_Click()
   Unload Me 'unload the form
End Sub

Private Sub mnuFilePrint_Click()
   On Error Resume Next
   If ActiveForm Is Nothing Then Exit Sub
   With dlgCommonDialog
      .DialogTitle = "Print"
      .CancelError = True
      .Flags = cdlPDReturnDC + cdlPDNoPageNums
      If ActiveForm.rtfText.SelLength = 0 Then
         .Flags = .Flags + cdlPDAllPages
      Else
         .Flags = .Flags + cdlPDSelection
      End If
      .ShowPrinter
      If Err <> MSComDlg.cdlCancel Then
         ActiveForm.rtfText.SelPrint .hDC
      End If
   End With
End Sub

' Close the active chart.
Private Sub mnuFileClose_Click()
On Error GoTo ErrHnd
   If Not Me.ActiveForm Is Nothing Then Unload Me.ActiveForm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Open a text file with the data for a chart & draw one.
Private Sub mnuFileOpen_Click()
On Error Resume Next 'Prevent from messaging the following error. For some unknown reason, the Me.ActiveForm.Draw
   With dlgCommonDialog 'procedure causes an error in case of an indefinite direction candlestick.
      .DialogTitle = "Open"
      .CancelError = False
      .Filter = "MS Excel Comma Separated Values Files (*.csv)|*.csv| All Files (*.*)|*.*"
      .ShowOpen
'      If Len(.FileName) > 0 Then If LoadNewFrm Then Call Me.ActiveForm.Draw(.FileName) 'Draw the chart.
      If Len(.FileName) > 0 Then
'         If LoadNewFrm Then Call Me.ActiveForm.Draw(.FileName, .FileTitle) 'Draw a chart.
         If LoadNewFrm(.FileTitle) Then Call Me.ActiveForm.Draw(.FileName) 'Draw a chart.
      End If
   End With
End Sub

' Return a child form's key string with a two-digit affix for the Windows registry settings.
Private Function ChildFormKey(ByVal strKey As String, ByVal intCount As Integer) As String
On Error GoTo ErrHnd
   ChildFormKey = strKey & Format$(intCount, "0#")
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Delete the previous children's settings, if any.
Private Sub ChildDeleteSetting()
On Error Resume Next 'Resume because the sections will be missing right after the application's installation or any other error.
   If Forms.Count > 1 Then DeleteSetting App.Title, mstrChildFrm 'Skip deleting because nothing will be saved instead.
End Sub

' Save the child forms' settings to apply at a next loading.
Private Sub ChildSaveSetting()
On Error GoTo ErrHnd
   Dim frmForm As Form
   Dim intCount As Integer
   tmrRefrsh.Enabled = False 'Disable refreshing.
   Call ProgrBarSet 'Prepare the progress bar.
   Call ProgrBarShow(True) 'Show the progress bar.
   For Each frmForm In Forms 'Children's settings.
      With frmForm
         If .Name <> Me.Name Then
            intCount = intCount + 1
            prgProgrBar.Value = intCount
            SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrWndState, intCount), .WindowState 'Window state.
            If .WindowState = vbNormal Then 'Save the size of normal state windows.
               SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrLft, intCount), .Left 'Left.
               SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrTop, intCount), .Top 'Top.
               SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrWdth, intCount), .Width 'Width.
               SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrHght, intCount), .Height 'Height.
            End If
            SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrFlPath, intCount), .FlPath 'File path.
            SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrSymbol, intCount), .Symbol 'File title.
            SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrIncr, intCount), .Incr 'Increment.
            SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrRevers, intCount), .Revers 'Reversal.
            SaveSetting App.Title, mstrChildFrm, ChildFormKey(mstrTimeFst, intCount), .TimeFst '1st canlestick's time.
         End If
      End With
   Next
   If intCount > 0 Then SaveSetting App.Title, mstrChildFrm, mstrFrmCount, intCount
   Call ProgrBarShow(False) 'Hide the progress one.
   tmrRefrsh.Enabled = True 'Resume.
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   MsgBox Err.Description
   Call ProgrBarShow(False) 'Hide the progress bar, if shown.
   tmrRefrsh.Enabled = True 'Resume, if disabled.
End Sub

' Restore the previously saved child forms, if any, with their charts.
Private Sub ChildRestore()
On Error GoTo ErrHnd
   Dim frmNewChart As frmChart
   Dim intWndState As Integer
   Dim intFrmCount As Integer
   Dim I As Integer
   tmrRefrsh.Enabled = False 'Disable refreshing.
   intFrmCount = CInt(GetSetting(App.Title, mstrChildFrm, mstrFrmCount, 0)) 'Prev. forms.
'   Call ShowProgrBar(True, intFrmCount) 'Show the progress bar.
   For I = 1 To intFrmCount 'All prev. forms.
      prgProgrBar.Value = I 'Show the progress.
'      strFlPath = GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrFlPath, I))
      Set frmNewChart = New frmChart
      intWndState = GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrWndState, I)) 'Window state.
      With frmNewChart
         Select Case intWndState 'Resize by window state.
         Case vbNormal 'Normal.
            .Move GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrLft, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrTop, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrWdth, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrHght, I)) 'Resize, if normal window state.
         Case vbMaximized, vbMinimized 'Maximised/minimised.
            .WindowState = intWndState
         End Select
         If ChildVldKey(I) Then
'            Call .ParamSet(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrFlPath, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrIncr, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrRevers, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrTimeFst, I)))
            Call .ParamSet(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrFlPath, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrSymbol, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrIncr, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrRevers, I)), GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrTimeFst, I)))
            Call .WriteCaption 'Write the caption.
            .Show
         Else
            Set frmNewChart = Nothing 'Destroy.
         End If
      End With
   Next
'   Call ShowProgrBar(False) 'Hide the progress bar.
   tmrRefrsh.Enabled = True 'Resume.
Exit Sub
ErrHnd: 'Handle errors that will occur because the sections might be missing after a previous saving failure.
On Error Resume Next 'Resume to handle the error hanler's internal errors.
Debug.Assert 0 = 1 'Verify
   If Not frmNewChart Is Nothing Then Set frmNewChart = Nothing 'Destroy, if created.
   DeleteSetting App.Title, mstrChildFrm 'Delete the whole child forms' section to prepare writing it from scratch.
'   Call ShowProgrBar(False) 'Hide the progress bar, if shown.
   tmrRefrsh.Enabled = True 'Resume, if disabled.
End Sub

' Automatically refreesh all charts, if the undelying data file has changed.
Private Sub tmrRefrsh_Timer()
On Error GoTo ErrHnd
'   Const lngIntrvNorm As Long = 2000 'The timer normal interval vs. to the default short beginning one.
'   Const lngIntrvNorm As Long = 5000 'The timer normal interval vs. to the default short beginning one.
   Const lngIntrvNorm As Long = 3000 'The timer normal interval vs. to the default short beginning one.
   Const intPassMin As Integer = 10 'The minimal number of passes utill setting the interval to nomral.
   Static intPassCount As Integer
   Dim frmForm As Form
   Dim intCount As Integer
   If intPassCount < intPassMin Then 'Skip?
      If intPassCount <> intPassMin Then intPassCount = intPassCount + 1 'Count.
   Else 'Execute.
      tmrRefrsh.Interval = lngIntrvNorm 'Set the normal interval.
      mnuFileSave.Enabled = False 'Disable saving, because it disables the timer in turn.
      tmrRefrsh.Enabled = False 'Disable until all forms refresh.
      If Forms.Count > 1 Then Call ProgrBarSet 'Any child forms opened to prepare the progress bar?
      For Each frmForm In Forms 'Loop through all chart forms.
         If frmForm.Name <> Me.Name Then
            intCount = intCount + 1 'Show the progress.
            prgProgrBar.Value = intCount
            Call frmForm.RefrshTimer
         End If
      Next
      Call ProgrBarShow(False) 'Hide the progress bar.
      tmrRefrsh.Enabled = True 'Resume.
      mnuFileSave.Enabled = True 'Resume.
   End If
Exit Sub
ErrHnd:
   MsgBox Err.Description
Debug.Assert 0 = 1 'Verify
   mnuFileSave.Enabled = True 'Resume, if disabled.
   Call ProgrBarShow(False) 'Hide the progress bar, if shown.
   tmrRefrsh.Enabled = True 'Resume, if disabled.
End Sub

' Restore a form by previous settins.
Private Sub Restore()
On Error GoTo ErrHnd
   Dim frmNewChart As frmChart
   Set frmNewChart = New frmChart
   frmNewChart.Show
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Validate the previously saved keys of the specified form's parameters.
' Return True, if succeeds.
Private Function ChildVldKey(ByVal intIdx As Integer) As Boolean
On Error GoTo ErrHnd
   If Len(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrFlPath, intIdx))) > 0 Then
      If Len(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrSymbol, intIdx))) > 0 Then
         If CInt(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrIncr, intIdx))) > 0 Then
            If CInt(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrRevers, intIdx))) > 0 Then
               If Len(GetSetting(App.Title, mstrChildFrm, ChildFormKey(mstrTimeFst, intIdx))) > 0 Then
                  ChildVldKey = True 'Succeeded.
               End If
            End If
         End If
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Hide the status bar & show the progress one.
Public Sub ProgrBarShow(ByVal blnVisible As Boolean)
On Error GoTo ErrHnd
   If mnuViewStatusBar.Checked Then staStatusBar.Visible = Not blnVisible
   prgProgrBar.Visible = blnVisible
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set/reset the progress bar to show processing all child forms.
Private Sub ProgrBarSet()
On Error GoTo ErrHnd
   Const intCountMain As Integer = 1 'The count of the main form beyond which child forms are numbered.
   Dim intMax As Integer
   prgProgrBar.Min = 0 'Min/max of the progress bar.
   prgProgrBar.Max = Forms.Count - intCountMain 'Equal to open child forms.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub
