VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Trade"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintFractMultVol As Long = 100 'The Volume fraction multiplier.

Dim mcurVol As Currency
Dim mcurPriceOpn As Currency
Dim mcurSL As Currency
Dim mcurTP As Currency
Dim mlngFractMult As Long

Public ID As Long
Public TimeOpn As String
Public IDType As Integer
Public IDTool As Integer

Public ModifPend As Boolean
Public ModifOpn As Boolean

Public Property Let Vol(ByVal curVol As Currency)
   mcurVol = curVol
End Property

' Volume with a fractional part.
Public Property Get Vol() As Currency
   Vol = mcurVol
End Property

' Volume without a fractional part i.e. multiplied by 100.
Private Property Get VolMult() As Currency
   Const intFractMultVol As Long = 100 'The Volume fraction multiplier.
   VolMult = mcurVol * intFractMultVol
End Property

Public Property Let FractMult(ByVal lngFractMult As Long)
   mlngFractMult = lngFractMult
End Property

' Opening price with a fractional part.
Public Property Let PriceOpn(ByVal curPriceOpn As Currency)
   mcurPriceOpn = curPriceOpn
End Property

' Opening price with a fractional part.
Public Property Get PriceOpn() As Currency
   PriceOpn = mcurPriceOpn
End Property

' Opening price without a fractional part i.e. multiplied by mlngFractMult.
Private Property Get PriceOpnMult() As Currency
   PriceOpnMult = mcurPriceOpn * mlngFractMult
End Property

' Stop loss with a fractional part.
Public Property Let SL(ByVal curSL As Currency)
   mcurSL = curSL
End Property

' Stop loss with a fractional part.
Public Property Get SL() As Currency
   SL = mcurSL
End Property

' Stop loss without a fractional part i.e. multiplied by mlngFractMult.
Private Property Get SLMult() As Currency
   SLMult = mcurSL * mlngFractMult
End Property

' Take profit with a fractional part.
Public Property Let TP(ByVal curTP As Currency)
   mcurTP = curTP
End Property

' Take profit with a fractional part.
Public Property Get TP() As Currency
   TP = mcurTP
End Property

' Take profit without a fractional part i.e. multiplied by mlngFractMult.
Private Property Get TPMult() As Currency
   TPMult = mcurTP * mlngFractMult
End Property

' Update pending orders.
Public Sub Upd_TradesPend()
   gcnnConnServ.Execute "Upd_TradesPend(" & ID & ", '" & TimeOpn & "', " & IDType & ", " & VolMult & ", '" & IDTool & "', " & mlngFractMult & ", " & PriceOpnMult & ", " & SLMult & ", " & TPMult & ")", , adCmdStoredProc + adExecuteNoRecords
End Sub
