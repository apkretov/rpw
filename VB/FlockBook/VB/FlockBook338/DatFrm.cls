VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "DatFrm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Sub DBtoFrm()

End Sub

Public Sub FrmToDB()

End Sub

Public Sub ModeSet(ByVal intMode As Integer)
    
End Sub

Public Property Get Mode() As Integer

End Property

Public Sub Cancel(ByVal blnCtlClear As Boolean)

End Sub

Public Property Let IDFrm(ByVal strIDFrm As String)

End Property

Public Property Get IDFrm() As String
   
End Property

Public Property Let FrmHostNam(ByVal strFrmHostNam As String)

End Property

Public Property Get FrmHostNam() As String
   
End Property

Public Sub RegistFrm(ByVal strNewIDFrm As String, ByVal blnDelPrev As Boolean)

End Sub

Public Sub SwchCtlFill(ByVal blnEnable As Boolean, Optional ByVal blnEnableID As Boolean)

End Sub

Public Sub SwchCtlMode()

End Sub

Public Function Vld() As Boolean

End Function

Public Property Get IDCtl() As TextBox

End Property

Public Sub CtlRead()

End Sub

Public Sub CtlClear()

End Sub

Public Sub CtlWrite()

End Sub

Public Property Get IsSetngFrm() As Boolean

End Property

Public Property Get FrmHost() As Form

End Property

Public Property Get IsDirty() As Boolean

End Property

Public Property Let IsDirty(ByVal blnIsDirty As Boolean)

End Property

Public Sub IDCtlPress(ByRef intKeyAscii As Integer)

End Sub

Public Sub IDCtlLostFoc()

End Sub

Public Property Get FrmHostCaptOrig() As String

End Property

Public Property Let FrmHostCaptOrig(ByVal strFrmHostCapt As String)

End Property

