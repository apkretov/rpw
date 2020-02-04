VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "LinkConst"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintAutomatic As Integer = 1 'Automatic link mode

' Automatic link mode
Public Property Get LinkModeAutomatic() As Integer
   Const intLinkModeAutomatic As Integer = 1
   LinkModeAutomatic = intLinkModeAutomatic
End Property

' Notify link mode
Public Property Get LinkModeNotify() As Integer
   Const intLinkModeNotify As Integer = 3
   LinkModeNotify = intLinkModeNotify
End Property

' DDE Bid link topic  setting.
Public Property Get LinkTopicBid() As String
   Const strLinkTopicBid As String = "BID"
   LinkTopicBid = strLinkTopicBid
End Property

' DDE Ask link topic  setting.
Public Property Get LinkTopicAsk() As String
   Const strLinkTopicAsk As String = "ASK"
   LinkTopicAsk = strLinkTopicAsk
End Property

' DDE Time link topic setting.
Public Property Get LinkTopicTime() As String
   Const strLinkTopicTime As String = "TIME"
   LinkTopicTime = strLinkTopicTime
End Property
