VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Setng"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintFrmInvenIdx As Integer = 1
Const mintFrmApprIdx As Integer = 6

Dim mobTblLiv As TblLiv

Dim mintFrmChldStatOrig As Integer
Dim mintFrmChldStat As Integer
Dim mintLastTabBrsShGOrig As Integer
Dim mintLastTabShG As Integer

Public ChldLft As Integer 'Child window's left position.
Public ChldTop As Integer 'Child window's top position.
Public LastTabBrsShG As Integer 'The frmBrsShG form's tabFarms control's current tab

' The form cascade indent.
Public Property Get IndtFrmCscd() As Integer
   Const intIndtFrmCscd As Integer = 330 'The form cascade indent.
   IndtFrmCscd = intIndtFrmCscd
End Property

' The form right indent within the frmMDI form.
Public Property Get IndtFrmRght() As Integer
   Const intIndtFrmRght As Integer = 120 'The form right indent within the frmMDI form.
   IndtFrmRght = intIndtFrmRght
End Property

' The form bottom indent within the frmMDI form.
Public Property Get IndtFrmBtm() As Integer
   Const intIndtFrmBtm As Integer = 1500 'The form bottom indent within the frmMDI form.
   IndtFrmBtm = intIndtFrmBtm
End Property

' The control right indent within the form.
Public Property Get IndtCtlRght() As Integer
   Const intIndtCtlRght As Integer = 240 'The control right indent within the form.
   IndtCtlRght = intIndtCtlRght
End Property

' The indent of the Ok button from the Cancel button.
Public Property Get IndtCtlOkCanc() As Integer
   Const intIndtCtlOkCanc As Integer = 120
   IndtCtlOkCanc = intIndtCtlOkCanc
End Property

' The DatFrm forms' ModeAdd mode.
Public Property Get ModeAdd() As Integer
   Const intModeAdd As Integer = 1
   ModeAdd = intModeAdd
End Property

' The DatFrm forms' ModeEdit mode.
Public Property Get ModeEdit() As Integer
   Const intModeEdit As Integer = 2
   ModeEdit = intModeEdit
End Property

' The DatFrm forms' ModeDel mode.
Public Property Get ModeDel() As Integer
   Const intModeDel As Integer = 3
   ModeDel = intModeDel
End Property

' The DatFrm forms' ModeOff mode.
Public Property Get ModeOff() As Integer
   Const intModeOff As Integer = 4
   ModeOff = intModeOff
End Property

' Child window's state.
Public Property Let FrmChldStat(ByVal intFrmChldStat As Integer)
   mintFrmChldStat = intFrmChldStat
End Property

' Child window's state.
Public Property Get FrmChldStat() As Integer
   FrmChldStat = mintFrmChldStat
End Property

' The frmShG form's name.
Public Property Get FrmShGNam() As String
   Const strFrmShGNam As String = "frmShG"
   FrmShGNam = strFrmShGNam
End Property

' The frmInven form's name.
Public Property Get FrmInvenNam() As String
   Const strFrmInvenNam As String = "frmInven"
   FrmInvenNam = strFrmInvenNam
End Property

' The frmInven form's name.
Public Property Get FrmInvenIdx() As Integer
   FrmInvenIdx = mintFrmInvenIdx
End Property

' The frmMat form's name.
Public Property Get FrmMatNam() As String
   Const strFrmMatNam As String = "frmMat"
   FrmMatNam = strFrmMatNam
End Property

' The frmMat form's name.
Public Property Get FrmMatIdx() As Integer
   Const intFrmMatIdx As Integer = 2
   FrmMatIdx = intFrmMatIdx
End Property


' The frmLmK form's name.
Public Property Get FrmLmKNam() As String
   Const strFrmLmKNam As String = "frmLmK"
   FrmLmKNam = strFrmLmKNam
End Property

' The frmLmK form's name.
Public Property Get FrmLmKIdx() As Integer
   Const intFrmLmKIdx As Integer = 3
   FrmLmKIdx = intFrmLmKIdx
End Property


' The frmWtLmK form's name.
Public Property Get FrmWtLmKNam() As String
   Const strFrmWtLmKNam As String = "frmWtLmK"
   FrmWtLmKNam = strFrmWtLmKNam
End Property
' The frmWtLmK form's name.
Public Property Get FrmWtLmKIdx() As Integer
   Const intFrmWtLmKIdx As Integer = 4
   FrmWtLmKIdx = intFrmWtLmKIdx
End Property

' The FrmWtWoolNam form's name.
Public Property Get FrmWtWoolNam() As String
   Const strFrmWtWoolNam As String = "frmWtWool"
   FrmWtWoolNam = strFrmWtWoolNam
End Property

' The FrmWtWoolIdx form's name.
Public Property Get FrmWtWoolIdx() As Integer
   Const intFrmWtWoolIdx As Integer = 5
   FrmWtWoolIdx = intFrmWtWoolIdx
End Property


' The frmAppr form's name.
Public Property Get FrmApprNam() As String
   Const strFrmApprNam As String = "frmAppr"
   FrmApprNam = strFrmApprNam
End Property

' The frmAppr form's name.
Public Property Get FrmApprIdx() As Integer
'   Const intFrmApprIdx As Integer = 6
   FrmApprIdx = mintFrmApprIdx
End Property


' The frmCert form's name.
Public Property Get FrmCertNam() As String
   Const strFrmCertNam As String = "frmCert"
   FrmCertNam = strFrmCertNam
End Property

' The frmCountr form's name.
Public Property Get FrmCountrNam() As String
   Const strFrmCountrNam As String = "frmCountr"
   FrmCountrNam = strFrmCountrNam
End Property

' The frmObl form's name.
Public Property Get FrmOblNam() As String
   Const strFrmOblNam As String = "frmObl"
   FrmOblNam = strFrmOblNam
End Property

' The frmRayn form's name.
Public Property Get FrmRaynNam() As String
   Const strFrmRaynNam As String = "frmRayn"
   FrmRaynNam = strFrmRaynNam
End Property

' The frmTwnVll form's name.
Public Property Get FrmTwnVllNam() As String
   Const strFrmTwnVllNam As String = "frmTwnVll"
   FrmTwnVllNam = strFrmTwnVllNam
End Property

' The frmPers form's name.
Public Property Get FrmPersNam() As String
   Const strFrmPersNam As String = "frmPers"
   FrmPersNam = strFrmPersNam
End Property

' The frmFarm form's name.
Public Property Get FrmFarmNam() As String
   Const strFrmFarmNam As String = "frmFarm"
   FrmFarmNam = strFrmFarmNam
End Property

' The frmBrdStd form's name.
Public Property Get FrmBrdStdNam() As String
   Const strFrmBrdStdNam As String = "frmBrdStd"
   FrmBrdStdNam = strFrmBrdStdNam
End Property

' The frmDefct form's name.
Public Property Get FrmDefctNam() As String
   Const strFrmDefctNam As String = "frmDefct"
   FrmDefctNam = strFrmDefctNam
End Property

' Get the settings saved at the last session & remember their original values:
'  - children's window state;
'  - the frmInven & frmAppr forms' expanded/shrunk state;
'  - the frmBrsShG form's tabFarms control's current tab.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   With App
      mintFrmChldStat = CInt(GetSetting(.ProductName, "WindowSate", "Child", 0))
      mintFrmChldStatOrig = mintFrmChldStat 'FrmChldStat
      LastTabBrsShG = CInt(GetSetting(.ProductName, "Controls", "tabFarms", 0))
   End With
   mintLastTabBrsShGOrig = LastTabBrsShG
   Set mobTblLiv = New TblLiv 'initialise mobTblLiv.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save MDI-child windows' state, if differs from the original.
' Save the settings if differ from the original values:
'  - children's window state;
'  - the frmInven & frmAppr forms' expanded/shrunk state.
'  - the frmBrsShG form's tabFarms control's current tab.
Private Sub Class_Terminate()
On Error GoTo ErrHnd
   With App
      If FrmChldStat <> mintFrmChldStatOrig Then SaveSetting .ProductName, _
         "WindowSate", "Child", FrmChldStat
      If LastTabBrsShG <> mintLastTabBrsShGOrig Then SaveSetting .ProductName, "Controls", _
         "tabFarms", LastTabBrsShG
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Link to the mobTblLiv object.
Public Property Get Liv() As TblLiv
   Set Liv = mobTblLiv
End Property

' Male sex ID.
Public Property Get IDSexMl() As String
   Const strIDSexMl As String = "0"
   IDSexMl = strIDSexMl
End Property

' Female sex ID.
Public Property Get IDSexFm() As String
   Const strIDSexFm As String = "1"
   IDSexFm = strIDSexFm
End Property

' Get the number of days in the year.
Public Property Get YearDays() As Single
   Const sngYearDays As Single = 365.25
   YearDays = sngYearDays
End Property

' Get 100 per cent.
Public Property Get Perc100() As Integer
   Const intPerc100 As Integer = 100
   Perc100 = intPerc100
End Property

' Get the SQL Server zero date.
Public Property Get SQLDateZero() As Date
   Const dtmSQLDateZero As Date = #1/1/1900#
   SQLDateZero = dtmSQLDateZero
End Property

' Get the SQL Server maximal number of days the smallint type contains, i.e. from
'  January 1, 1900, through June 6, 2079.
Public Property Get SQLDaysMax() As Long
   Const lngSQLDaysMax As Long = 65535
   SQLDaysMax = lngSQLDaysMax
End Property

' Let the last tab's index of the frmShG form, if falls between Inven & Appr indexes.
Public Property Let LastTabShG(ByVal intLastTabShG As Integer)
On Error GoTo ErrHnd
   If intLastTabShG >= mintFrmInvenIdx And intLastTabShG <= mintFrmApprIdx Then _
      mintLastTabShG = intLastTabShG
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Let the last tab's index of the frmShG form.
' Defualt to the Inven data form's index, if zero.
Public Property Get LastTabShG() As Integer
On Error GoTo ErrHnd
   If mintLastTabShG <> 0 Then
      LastTabShG = mintLastTabShG
   Else
      LastTabShG = mintFrmInvenIdx
   End If
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get the data form's name by the tabShG tab's index.
' Unless the index is specified equate it with the selected data form's index.
Public Function FrmNamByIdx(ByVal intIdx As Integer) As String
On Error GoTo ErrHnd
'   If intIdx = 0 Then intIdx = tabShG.SelectedItem.Index 'Equate with the seleted index.
   With gobSetng
      Select Case intIdx
      Case .FrmInvenIdx
         FrmNamByIdx = .FrmInvenNam
      Case .FrmMatIdx
         FrmNamByIdx = .FrmMatNam
      Case .FrmLmKIdx
         FrmNamByIdx = .FrmLmKNam
      Case .FrmWtLmKIdx
         FrmNamByIdx = .FrmWtLmKNam
      Case .FrmWtWoolIdx
         FrmNamByIdx = .FrmWtWoolNam
      Case .FrmApprIdx
         FrmNamByIdx = .FrmApprNam
      End Select
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' The Sheep speces ID.
Public Property Get IDSpcsSh() As String
   Const strIDSpcsSh As String = "0"
   IDSpcsSh = strIDSpcsSh
End Property

' The Goat speces ID.
Public Property Get IDSpcsG() As String
   Const strIDSpcsG As String = "1"
   IDSpcsG = strIDSpcsG
End Property

' The slash symbol to separate a numerator & denominator in the cross breed code.
Public Property Get BrdCrsSlash() As String
   Const strIDSpcsG As String = "/"
   BrdCrsSlash = strIDSpcsG
End Property

' The maximum number of cross breed shares in the cross breed code.
Public Property Get BrdCrsMaxShare() As Integer
   Const intBrdCrsMaxShare As Integer = 6
   BrdCrsMaxShare = intBrdCrsMaxShare
End Property

' The maximum cross breed denominator in the cross breed code.
Public Property Get BrdCrsMaxDen() As Integer
   Const intBrdCrsMaxDen As Integer = 64
   BrdCrsMaxDen = intBrdCrsMaxDen
End Property

' The Null string for SQL statements.
Public Property Get NullStr() As String
   Const strNullStr As String = "NULL"
   NullStr = strNullStr
End Property

' The checked value for Access (= -1) or SQL Server (= 1) - by demand.
Public Property Get Checked() As Integer
   Const intChecked As Integer = -1
   Checked = intChecked
End Property

' Get the interval for the frmMDI form's timer.
Public Property Get TimeIntrv() As Long
   Const lngTimeIntrv As Long = 125
   TimeIntrv = lngTimeIntrv
End Property
