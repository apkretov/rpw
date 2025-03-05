VERSION 5.00
Object = "{67397AA1-7FB1-11D0-B148-00A0C922E820}#6.0#0"; "MSADODC.OCX"
Object = "{F0D2F211-CCB0-11D0-A316-00AA00688B10}#1.0#0"; "MSDATLST.OCX"
Begin VB.Form frmOrder 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Открытие позиции"
   ClientHeight    =   3975
   ClientLeft      =   600
   ClientTop       =   2250
   ClientWidth     =   5295
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3975
   ScaleWidth      =   5295
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdCls 
      BackColor       =   &H0080FFFF&
      Caption         =   "&Закрыть"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      Style           =   1  'Graphical
      TabIndex        =   21
      Top             =   4440
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton cmdDelete 
      BackColor       =   &H0080FFFF&
      Caption         =   "&Удалить"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   3960
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton cmdModify 
      Caption         =   "&Изменить"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      Style           =   1  'Graphical
      TabIndex        =   20
      Top             =   3960
      Visible         =   0   'False
      Width           =   2175
   End
   Begin VB.CommandButton cmdSell 
      BackColor       =   &H008080FF&
      Caption         =   "&Продать"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   240
      Style           =   1  'Graphical
      TabIndex        =   17
      Top             =   3480
      Width           =   2175
   End
   Begin VB.CommandButton cmdBuy 
      BackColor       =   &H00FF8080&
      Caption         =   "&Купить"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3000
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   3480
      Width           =   2055
   End
   Begin VB.Frame fraType 
      Caption         =   "Тип ордера"
      Height          =   1215
      Left            =   120
      TabIndex        =   10
      Top             =   1680
      Width           =   5055
      Begin VB.TextBox txtPriceOpn 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   204
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   3420
         TabIndex        =   13
         Text            =   "1.4000"
         Top             =   660
         Width           =   1455
      End
      Begin VB.OptionButton optPend 
         Caption         =   "&Отложенный ордер"
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   720
         Width           =   1815
      End
      Begin VB.OptionButton optInst 
         Caption         =   "&Немедленное исполнение"
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   360
         Value           =   -1  'True
         Width           =   2295
      End
      Begin VB.Label lblOrdPrice 
         Alignment       =   1  'Right Justify
         Caption         =   "Цена:"
         Height          =   255
         Left            =   2760
         TabIndex        =   14
         Top             =   720
         Width           =   495
      End
   End
   Begin VB.TextBox txtVol 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   3600
      TabIndex        =   5
      Text            =   "0,01"
      Top             =   360
      Width           =   1455
   End
   Begin VB.TextBox txtTP 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   3600
      TabIndex        =   9
      Text            =   "1.4000"
      Top             =   1080
      Width           =   1455
   End
   Begin VB.TextBox txtSL 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   405
      Left            =   240
      TabIndex        =   7
      Text            =   "1.3000"
      Top             =   1080
      Width           =   1455
   End
   Begin MSDataListLib.DataCombo dbcTools 
      Height          =   315
      Left            =   240
      TabIndex        =   1
      ToolTipText     =   "F4 - Открыть список"
      Top             =   360
      Width           =   1455
      _ExtentX        =   2566
      _ExtentY        =   556
      _Version        =   393216
      Style           =   2
      Text            =   ""
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin MSAdodcLib.Adodc adoTools 
      Height          =   330
      Left            =   240
      Top             =   480
      Visible         =   0   'False
      Width           =   1455
      _ExtentX        =   2566
      _ExtentY        =   582
      ConnectMode     =   0
      CursorLocation  =   3
      IsolationLevel  =   -1
      ConnectionTimeout=   15
      CommandTimeout  =   30
      CursorType      =   3
      LockType        =   1
      CommandType     =   2
      CursorOptions   =   0
      CacheSize       =   50
      MaxRecords      =   0
      BOFAction       =   0
      EOFAction       =   0
      ConnectStringType=   1
      Appearance      =   1
      BackColor       =   -2147483643
      ForeColor       =   -2147483640
      Orientation     =   0
      Enabled         =   -1
      Connect         =   ""
      OLEDBString     =   ""
      OLEDBFile       =   ""
      DataSourceName  =   ""
      OtherAttributes =   ""
      UserName        =   ""
      Password        =   ""
      RecordSource    =   ""
      Caption         =   "adoTools"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      _Version        =   393216
   End
   Begin VB.Label lblBid 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   600
      TabIndex        =   19
      Top             =   3120
      Width           =   1455
   End
   Begin VB.Label lblAsk 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3360
      TabIndex        =   18
      Top             =   3120
      Width           =   1455
   End
   Begin VB.Label lblNotify 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1920
      TabIndex        =   3
      Top             =   480
      Width           =   1455
   End
   Begin VB.Label lblVol 
      AutoSize        =   -1  'True
      Caption         =   "&Лот:"
      Height          =   195
      Left            =   3600
      TabIndex        =   4
      Top             =   120
      Width           =   330
   End
   Begin VB.Label lblTime 
      Alignment       =   2  'Center
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1920
      TabIndex        =   2
      Top             =   0
      Visible         =   0   'False
      Width           =   1455
   End
   Begin VB.Label lblTools 
      AutoSize        =   -1  'True
      Caption         =   "&Инструмент:"
      Height          =   195
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   960
   End
   Begin VB.Label lblTP 
      AutoSize        =   -1  'True
      Caption         =   "&Тэйк-профит:"
      Height          =   195
      Left            =   3600
      TabIndex        =   8
      Top             =   840
      Width           =   1020
   End
   Begin VB.Label lblSL 
      AutoSize        =   -1  'True
      Caption         =   "&Стоп-лосс:"
      Height          =   195
      Left            =   240
      TabIndex        =   6
      Top             =   840
      Width           =   810
   End
End
Attribute VB_Name = "frmOrder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mintIDTypBuy As Integer = 1 'The order type IDs.
Const mintIDTypSell As Integer = 2
Const mintIDTypBuyStp As Integer = 3
Const mintIDTypSellStp As Integer = 4
Const mintIDTypBuyLmt As Integer = 5
Const mintIDTypSellLmt As Integer = 6

Const mstrCaptBuy As String = "&Buy" 'The Buy/Sell caption items.
Const mstrCaptSell As String = "&Sell"
Const mstrCaptStp As String = " Stop"
Const mstrCaptLmt As String = " Limit"

Dim mintIDTypPendBuy As Integer 'The pending Buy/Sell Stop/Limit order flags.
Dim mintIDTypPendSell As Integer
Dim mobjTrade As Trade
'Dim mblnFlagNew As Boolean
Dim mblnModifPend As Boolean 'SUSPENDED: TO BE COMMENTED
Dim mblnModifOpn As Boolean 'SUSPENDED: TO BE COMMENTED

' Set a Trade object.
Public Property Let Trade(ByVal objTrade As Trade)
   Set mobjTrade = objTrade
End Property

' Set the New Order flag.
Public Property Let KTB_FlagNew(ByVal blnFlagNew As Boolean)
'   mblnFlagNew = blnFlagNew
End Property

' Set the Modify Pending Order flag.
Public Property Let ModifPend(ByVal blnModifPend As Boolean)
   mblnModifPend = blnModifPend
End Property

' Set the Modify Open Order flag.
Public Property Let ModifOpn(ByVal blnModifOpn As Boolean)
   mblnModifOpn = blnModifOpn
End Property


' Validate filling-out controls.
Private Function ValidCtrl()
    If Len(dbcTools.BoundText) = 0 Then
        MsgBox "Выберите инструмент!"
    ElseIf Util.ValidTxtBox(txtVol, "Лот") Then
        ValidCtrl = True
    End If
End Function

' Buy or place a Buy Stop/Limit order.
Private Sub cmdBuy_Click()
On Error GoTo ErrHnd
   If optInst Then 'Instant execution?
      Call BuySell(lblAsk, mintIDTypBuy)
   Else 'Pending order.
      Call BuySell(txtPriceOpn, mintIDTypPendBuy)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Sell or place a Sell Stop/Limit order.
Private Sub cmdSell_Click()
On Error GoTo ErrHnd
   If optInst Then 'Instant execution?
      Call BuySell(lblBid, mintIDTypSell)
   Else 'Pending order.
      Call BuySell(txtPriceOpn, mintIDTypPendSell)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Buy/Sell the selected tool.
Private Sub BuySell(ByVal strBidAsk As String, ByVal intIDTyp As Integer)
On Error GoTo ErrHnd
   Const datNull As Date = 0 'Null time
   Const intFractMultVol As Long = 100 'The Volume fraction multiplier.
   Dim lngFractMult As Long
   Call Util.LinkPrices(lblTime, gobjLinkConst.LinkModeAutomatic, dbcTools.Text, gobjLinkConst.LinkTopicTime) ' Link the DDE lable.
   With adoTools.Recordset
      .MoveFirst
      .Find (dbcTools.ListField & " = '" & dbcTools.Text & "'")
      If .BOF = False And .EOF = False Then lngFractMult = .Fields("FractMult")
   End With
   If mblnModifOpn = False And mblnModifPend = False Then 'A new record?
      gcnnConnServ.Execute "Ins_Trades(" & gintIDAcc & ", '" & lblTime & "', " & intIDTyp & ", " & Util.ConvCur(txtVol) * intFractMultVol & ", '" & CInt(dbcTools.BoundText) & "', " & lngFractMult & ", " & Util.ConvCur(strBidAsk) * lngFractMult & ", " & Util.ConvCur(txtSL) * lngFractMult & ", " & Util.ConvCur(txtTP) * lngFractMult & ")", , adCmdStoredProc + adExecuteNoRecords
   Else 'Modifying an available record.
      '''''''''''
   End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

'' Read the specified datacombo's Boundtext property from its data providing Ado control. The procedure is necessary when the data is read from the datacombo that has been unchanged. In such a case, the datacombo's Boundtext is substituted with its Text property for an unknown reason.
'Private Function FractMult() As Integer
'   With adoTools.Recordset
'      .Find (dbcTools.ListField & " = '" & dbcTools & "'")
'      If .BOF = False And .EOF = False Then FractMult = .Fields(dbcTools.BoundColumn)
'   End With
'End Function

' Set the Bid/Ask lables & the Sell/Buy buttons captions.
Private Sub dbcTools_Change()
On Error GoTo ErrHnd
   With gobjLinkConst
      Call Util.LinkPrices(lblBid, .LinkModeAutomatic, dbcTools.Text, .LinkTopicBid) ' Link the DDE price lables.
      Call Util.LinkPrices(lblAsk, .LinkModeAutomatic, dbcTools.Text, .LinkTopicAsk)
      Call Util.LinkPrices(lblNotify, .LinkModeNotify, dbcTools.Text, .LinkTopicTime)
   End With
   If optInst Then
      Call SetBtnInst ' Set the Instant Sell/Buy buttons captions.
   Else
      Call SetBtnPend ' Set the Pending Sell/Buy Stop/Limit buttons captions.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Set the Instant Sell/Buy buttons captions.
Private Sub SetBtnInst()
   Const strBuy As String = "&Купить"
   Const strSell As String = "&Продать"
   cmdSell.Caption = strSell
   cmdBuy.Caption = strBuy
End Sub

' Set the Instant Sell/Buy buttons captions.
Private Sub KTB_SetBtnInst()
'   Const strBuy As String = "&Купить"
'   Const strSell As String = "&Продать"
'   If Len(Trim$(lblBid.Caption)) = 0 Then
'      cmdSell.Caption = strSell
'      cmdBuy.Caption = strBuy
'   Else
'      cmdSell.Caption = strSell & Space$(1) & lblBid.Caption
'      cmdBuy.Caption = strBuy & Space$(1) & lblAsk.Caption
'   End If
End Sub

' Set the Pending Sell/Buy Stop/Limit buttons captions.
Private Sub SetBtnPend()
   mintIDTypPendBuy = 0 ' Reset the pending Buy/Sell Stop/Limit order flags.
   mintIDTypPendSell = 0
   If (Len(Trim$(lblBid.Caption)) = 0) Or (Len(Trim$(txtPriceOpn)) = 0) Then 'No price?
      Call DisablePendBtn ' Disable the pending buttons.
   Else
      Call SetStpLmt(cmdSell, mintIDTypPendSell, mintIDTypSellLmt, mintIDTypSellStp, lblBid, mstrCaptSell, mstrCaptLmt, mstrCaptStp) ' Set the Pending Sell Stop/Limit button caption.
      Call SetStpLmt(cmdBuy, mintIDTypPendBuy, mintIDTypBuyStp, mintIDTypBuyLmt, lblAsk, mstrCaptBuy, mstrCaptStp, mstrCaptLmt) ' Set the Pending Buy Stop/Limit button caption.
   End If
End Sub

' Set the Pending Sell/Buy Stop/Limit buttons captions. Subprocedure.
Private Sub SetStpLmt(cmdSellBuy As CommandButton, intIDTypPend As Integer, ByVal intIDTypPendAbv As Integer, ByVal intIDTypPendBlw As Integer, ByVal strBidAsk As String, ByVal strSellBuy As String, ByVal strStpLmtAbv As String, ByVal strStpLmtBlw As String)
   Dim curBidAsk As Currency
   curBidAsk = CDec(Util.ConvCur(strBidAsk)) ' Change the number locale decimal symbol.
   If CDec(txtPriceOpn) = curBidAsk Then 'The order price is equal to Bid/Ask?
      Call DisablePendBtn ' Disable the pending buttons.
   Else
      Call EnablePendBtn(True) ' Enable the pending buttons.
      If CDec(txtPriceOpn) > curBidAsk Then 'Above Bid/Ask?
         cmdSellBuy.Caption = strSellBuy & strStpLmtAbv 'Set the Sell/Buy Stop/Limit caption that is proper above the order price.
         intIDTypPend = intIDTypPendAbv 'Set the Buy/Sell Stop/Limit order flag that is proper above the order price.
      Else 'Below Bid.
         cmdSellBuy.Caption = strSellBuy & strStpLmtBlw 'Set the Sell/Buy Stop/Limit caption that is proper below the order price.
         intIDTypPend = intIDTypPendBlw 'Set the Buy/Sell Stop/Limit order flag that is proper below the order price.
      End If
   End If
End Sub

' Disable the pending buttons & set thier captions.
Private Sub DisablePendBtn()
   Call EnablePendBtn(False) ' Disable the pending buttons.
   cmdSell.Caption = mstrCaptSell & mstrCaptStp 'Set the captions.
   cmdBuy.Caption = mstrCaptBuy & mstrCaptLmt
End Sub


' Enable/disable the pending buttons.
Private Sub EnablePendBtn(ByVal blnEnabled As Boolean)
   cmdSell.Enabled = blnEnabled
   cmdBuy.Enabled = blnEnabled
End Sub

' Initialise the form's controls.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Call Util.SetAdoTools(adoTools)
   With dbcTools
      Set .RowSource = adoTools
      .BoundColumn = "ID"
      .ListField = "Tool"
   End With
   If mblnModifPend Then Call FillPend 'Fill controls with Trade object's data.
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Fill controls with a pendig order's Trade object.
Private Sub FillPend()
   With mobjTrade
      dbcTools.BoundText = .IDTool
      txtVol = .Vol
      txtSL = .SL
      txtTP = .TP
      optPend = True
      txtPriceOpn = .PriceOpn
   End With
End Sub

' Close the form on Esc press.
Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
    If KeyCode = vbKeyEscape Then Unload Me
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Validate the value entered.
Private Sub KTB_txtVol_Validate(Cancel As Boolean)
'On Error GoTo ErrHnd
'    Const lngMaxVol As Long = 10000000 'The maximal volume.
'    Const intIDTypeMismatch As Integer = 13 'The Type Mismatch error number.
'    Dim curVol As Currency
'    If CDbl(txtVol) > lngMaxVol Then 'Must not be > the maximum.
'        MsgBox "Лот не должен быть больше " & lngMaxVol & "!"
'        txtVol = lngMaxVol
'    End If
'    curVol = txtVol 'Convert to currency to cut a redundant fractional part, if any.
'    Debug.Print "Use the fraction multiplier"
'    curVol = CLng(curVol * 100) / 100
'    txtVol = curVol
'    If lngVol < 0 Then 'Must be > 0.
'       txtVol = lngVol * (-1)
'    End If
'Exit Sub
'ErrHnd:
'    If Err.Number = intIDTypeMismatch Then 'A non-number entry i.e. an expected Type Mismatch error?
'        txtVol = 0
'    Else
'        MsgBox Err.Number & vbTab & Err.Description
'    End If
End Sub

' Show the current price tick by tick on the Sell/Buy buttons, if the instant orders option is selected.
Private Sub lblNotify_LinkNotify()
On Error GoTo ErrHnd
   If optInst Then Call SetBtnInst
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Enable placing an instant order.
Private Sub optInst_Click()
On Error GoTo ErrHnd
   txtPriceOpn.Enabled = False
   Call SetBtnInst ' Set the Instant Sell/Buy buttons captions.
   Call EnablePendBtn(True) ' Enable the buttons.
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Enable placing a pending order.
Private Sub optPend_Click()
On Error GoTo ErrHnd
   txtPriceOpn.Enabled = True
   Call SetBtnPend ' Set the Pending Sell/Buy Stop/Limit buttons captions.
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

Private Sub txtPriceOpn_Change()
On Error GoTo ErrHnd
   Call SetBtnPend ' Set the Pending Sell/Buy Stop/Limit buttons captions.
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

'Private Sub txtPriceOpn_Validate(Cancel As Boolean)
'On Error GoTo ErrHnd
'   Call SetBtnPend ' Set the Pending Sell/Buy Stop/Limit buttons captions.
'Exit Sub
'ErrHnd:
'MsgBox Err.Number & vbTab & Err.Description
'End Sub
