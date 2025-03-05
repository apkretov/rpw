VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblCtrlParam"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobSQLErrHnd As SQLErrHnd

Private Type TblCtrlParamTp
   AgeWeanMin As Integer
   AgeWeanMax As Integer
   Age7MonMin As Integer
   Age7MonMax As Integer
   Age1YrChk As Boolean
   Age1YrWtMin As Integer
   Age1YrWtMax As Integer
   Age1YrShearMin As Integer
   Age1YrShearMax As Integer
   AgeMatMinSr As Integer
   AgeMatMinDm As Integer
   LifeTimeMax As Integer
   PregnLengMin As Integer
   PregnLengNorm As Integer
   PregnLengMax As Integer
   InterAnnlMin As Integer
   InterAnnlMax As Integer
   BrdBasDam As Boolean
   ConvCrsToPure As Boolean
   BVTestLifeTime As Boolean
   BVTestYr As Integer
   SelIndxScale As Integer
End Type
Dim mudtTblCtrlParam As TblCtrlParamTp

Dim mblnAllowWrite As Boolean
Dim mblnFull As Boolean

' Allow/don't allow to let change the variables.
Public Property Let AllowWrite(ByVal blnAllowWrite As Boolean)
   mblnAllowWrite = blnAllowWrite
End Property

' Get AgeWeanMin.
Public Property Get AgeWeanMin() As Integer
    AgeWeanMin = mudtTblCtrlParam.AgeWeanMin
End Property

' Let AgeWeanMin, if allowed.
Public Property Let AgeWeanMin(ByVal intAgeWeanMin As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.AgeWeanMin = intAgeWeanMin
End Property

' Get AgeWeanMax.
Public Property Get AgeWeanMax() As Integer
    AgeWeanMax = mudtTblCtrlParam.AgeWeanMax
End Property

' Let AgeWeanMax, if allowed.
Public Property Let AgeWeanMax(ByVal intAgeWeanMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.AgeWeanMax = intAgeWeanMax
End Property

' Get Age7MonMin.
Public Property Get Age7MonMin() As Integer
    Age7MonMin = mudtTblCtrlParam.Age7MonMin
End Property

' Let Age7MonMin, if allowed.
Public Property Let Age7MonMin(ByVal intAge7MonMin As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.Age7MonMin = intAge7MonMin
End Property

' Get Age7MonMax.
Public Property Get Age7MonMax() As Integer
    Age7MonMax = mudtTblCtrlParam.Age7MonMax
End Property

' Let Age7MonMax, if allowed.
Public Property Let Age7MonMax(ByVal intAge7MonMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.Age7MonMax = intAge7MonMax
End Property

' Get Age1YrWtMin.
Public Property Get Age1YrWtMin() As Integer
    Age1YrWtMin = mudtTblCtrlParam.Age1YrWtMin
End Property

' Let Age1YrWtMin, if allowed.
Public Property Let Age1YrWtMin(ByVal intAge1YrWtMin As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.Age1YrWtMin = intAge1YrWtMin
End Property

' Get Age1YrWtMax.
Public Property Get Age1YrWtMax() As Integer
    Age1YrWtMax = mudtTblCtrlParam.Age1YrWtMax
End Property

' Let Age1YrWtMax, if allowed.
Public Property Let Age1YrWtMax(ByVal intAge1YrWtMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.Age1YrWtMax = intAge1YrWtMax
End Property

' Get Age1YrShearMin.
Public Property Get Age1YrShearMin() As Integer
    Age1YrShearMin = mudtTblCtrlParam.Age1YrShearMin
End Property

' Let Age1YrShearMin, if allowed.
Public Property Let Age1YrShearMin(ByVal intAge1YrShearMin As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.Age1YrShearMin = intAge1YrShearMin
End Property

' Get Age1YrShearMax.
Public Property Get Age1YrShearMax() As Integer
    Age1YrShearMax = mudtTblCtrlParam.Age1YrShearMax
End Property

' Let Age1YrShearMax, if allowed.
Public Property Let Age1YrShearMax(ByVal intAge1YrShearMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.Age1YrShearMax = intAge1YrShearMax
End Property

' Get Age1YrChk.
Public Property Get Age1YrChk() As Boolean
    Age1YrChk = mudtTblCtrlParam.Age1YrChk
End Property

' Let Age1YrChk, if allowed.
Public Property Let Age1YrChk(ByVal blnAge1YrChk As Boolean)
   If mblnAllowWrite Then mudtTblCtrlParam.Age1YrChk = blnAge1YrChk
End Property

' Get AgeMatMinSr.
Public Property Get AgeMatMinSr() As Integer
    AgeMatMinSr = mudtTblCtrlParam.AgeMatMinSr
End Property

' Let AgeMatMinSr, if allowed.
Public Property Let AgeMatMinSr(ByVal intAgeMatMinSr As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.AgeMatMinSr = intAgeMatMinSr
End Property

' Get AgeMatMinDm.
Public Property Get AgeMatMinDm() As Integer
    AgeMatMinDm = mudtTblCtrlParam.AgeMatMinDm
End Property

' Let AgeMatMinDm, if allowed.
Public Property Let AgeMatMinDm(ByVal intAgeMatMinDm As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.AgeMatMinDm = intAgeMatMinDm
End Property

' Get PregnLengMin.
Public Property Get PregnLengMin() As Integer
    PregnLengMin = mudtTblCtrlParam.PregnLengMin
End Property

' Let PregnLengMin, if allowed.
Public Property Let PregnLengMin(ByVal intPregnLengMin As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.PregnLengMin = intPregnLengMin
End Property

' Get PregnLengNorm.
Public Property Get PregnLengNorm() As Integer
    PregnLengNorm = mudtTblCtrlParam.PregnLengNorm
End Property

' Let PregnLengNorm, if allowed.
Public Property Let PregnLengNorm(ByVal intPregnLengNorm As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.PregnLengNorm = intPregnLengNorm
End Property

' Get PregnLengMax.
Public Property Get PregnLengMax() As Integer
    PregnLengMax = mudtTblCtrlParam.PregnLengMax
End Property

' Let PregnLengMax, if allowed.
Public Property Let PregnLengMax(ByVal intPregnLengMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.PregnLengMax = intPregnLengMax
End Property

' Get InterAnnlMin.
Public Property Get InterAnnlMin() As Integer
    InterAnnlMin = mudtTblCtrlParam.InterAnnlMin
End Property

' Let InterAnnlMin, if allowed.
Public Property Let InterAnnlMin(ByVal intInterAnnlMin As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.InterAnnlMin = intInterAnnlMin
End Property

' Get InterAnnlMax.
Public Property Get InterAnnlMax() As Integer
    InterAnnlMax = mudtTblCtrlParam.InterAnnlMax
End Property

' Let InterAnnlMax, if allowed.
Public Property Let InterAnnlMax(ByVal intInterAnnlMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.InterAnnlMax = intInterAnnlMax
End Property

' Get LifeTimeMax.
Public Property Get LifeTimeMax() As Integer
    LifeTimeMax = mudtTblCtrlParam.LifeTimeMax
End Property

' Let LifeTimeMax, if allowed.
Public Property Let LifeTimeMax(ByVal intLifeTimeMax As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.LifeTimeMax = intLifeTimeMax
End Property

' Get SelIndxScale.
Public Property Get SelIndxScale() As Integer
    SelIndxScale = mudtTblCtrlParam.SelIndxScale
End Property

' Let SelIndxScale, if allowed.
Public Property Let SelIndxScale(ByVal intSelIndxScale As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.SelIndxScale = intSelIndxScale
End Property

' Get BrdBasDam.
Public Property Get BrdBasDam() As Boolean
    BrdBasDam = mudtTblCtrlParam.BrdBasDam
End Property

' Let BrdBasDam, if allowed.
Public Property Let BrdBasDam(ByVal blnBrdBasDam As Boolean)
   If mblnAllowWrite Then mudtTblCtrlParam.BrdBasDam = blnBrdBasDam
End Property

' Get ConvCrsToPure.
Public Property Get ConvCrsToPure() As Boolean
    ConvCrsToPure = mudtTblCtrlParam.ConvCrsToPure
End Property

' Let ConvCrsToPure, if allowed.
Public Property Let ConvCrsToPure(ByVal blnConvCrsToPure As Boolean)
   If mblnAllowWrite Then mudtTblCtrlParam.ConvCrsToPure = blnConvCrsToPure
End Property

' Get BVTestLifeTime.
Public Property Get BVTestLifeTime() As Boolean
    BVTestLifeTime = mudtTblCtrlParam.BVTestLifeTime
End Property

' Let BVTestLifeTime, if allowed.
Public Property Let BVTestLifeTime(ByVal blnBVTestLifeTime As Boolean)
   If mblnAllowWrite Then mudtTblCtrlParam.BVTestLifeTime = blnBVTestLifeTime
End Property

' Get BVTestYr.
Public Property Get BVTestYr() As Integer
    BVTestYr = mudtTblCtrlParam.BVTestYr
End Property

' Let BVTestYr, if allowed.
Public Property Let BVTestYr(ByVal intBVTestYr As Integer)
   If mblnAllowWrite Then mudtTblCtrlParam.BVTestYr = intBVTestYr
End Property

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Sub DatTbl_Del()
'Empty.
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Add a new sheep/goat to the ShG table, if allowed.
' Mark an error for later reference, if occurs.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If mblnAllowWrite Then
      With mudtTblCtrlParam
         strCmdTxt = "spInsert_ContrlParam(" & .AgeWeanMin & ", " & .AgeWeanMax & ", " & _
            .Age7MonMin & ", " & .Age7MonMax & ", " & IIf(.Age1YrChk, 1, 0) & ", " & _
            .Age1YrWtMin & ", " & .Age1YrWtMax & ", " & .Age1YrShearMin & ", " & _
            .Age1YrShearMax & ", " & .AgeMatMinSr & ", " & .AgeMatMinDm & ", " & _
            .LifeTimeMax & ", " & .PregnLengMin & ", " & .PregnLengNorm & ", " & _
            .PregnLengMax & ", " & .InterAnnlMin & ", " & .InterAnnlMax & ", " & IIf( _
            BrdBasDam, 1, 0) & ", " & IIf(ConvCrsToPure, 1, 0) & ", " & IIf( _
            .BVTestLifeTime, 1, 0) & ", " & .BVTestYr & ", " & .SelIndxScale & ")"
      End With
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      mblnFull = True 'Mark full.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.GenrlModl Err.Description, frmCtrlParam
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'Empty.
End Function

Private Sub DatTbl_OrigSave()
'Empty.
End Sub

' Select data from the CtrlParam table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstTblCtrlParam As ADODB.Recordset
   Set rstTblCtrlParam = New ADODB.Recordset
   rstTblCtrlParam.Open "spSelect_ContrlParam", gcnnConnServ, adOpenDynamic, _
      adLockOptimistic, adCmdStoredProc
   With rstTblCtrlParam 'Define the animal's data from the CtrlParam recordset.
      If .EOF And .BOF Then 'Give feedback if CtrlParam is available.
         mblnFull = False 'Mark empty.
      Else
         With .Fields 'Proceed.
            mudtTblCtrlParam.AgeWeanMin = .Item("AgeWeanMin")
            mudtTblCtrlParam.AgeWeanMax = .Item("AgeWeanMax")
            mudtTblCtrlParam.Age7MonMin = .Item("Age7MonMin")
            mudtTblCtrlParam.Age7MonMax = .Item("Age7MonMax")
            mudtTblCtrlParam.Age1YrChk = .Item("Age1YrCheck")
            mudtTblCtrlParam.Age1YrWtMin = .Item("Age1YrWtMin")
            mudtTblCtrlParam.Age1YrWtMax = .Item("Age1YrWtMax")
            mudtTblCtrlParam.Age1YrShearMin = .Item("Age1YrShearMin")
            mudtTblCtrlParam.Age1YrShearMax = .Item("Age1YrShearMax")
            mudtTblCtrlParam.AgeMatMinSr = .Item("AgeMatMinSire")
            mudtTblCtrlParam.AgeMatMinDm = .Item("AgeMatMinDam")
            mudtTblCtrlParam.LifeTimeMax = .Item("LifeTimeMax")
            mudtTblCtrlParam.PregnLengMin = .Item("PregnLengMin")
            mudtTblCtrlParam.PregnLengNorm = .Item("PregnLengNorm")
            mudtTblCtrlParam.PregnLengMax = .Item("PregnLengMax")
            mudtTblCtrlParam.InterAnnlMin = .Item("InterAnnlMin")
            mudtTblCtrlParam.InterAnnlMax = .Item("InterAnnlMax")
            mudtTblCtrlParam.BrdBasDam = .Item("BreedBaseDam")
            mudtTblCtrlParam.ConvCrsToPure = .Item("ConvCrossToPure")
            mudtTblCtrlParam.BVTestLifeTime = .Item("BVTestLifeTime")
            mudtTblCtrlParam.BVTestYr = .Item("BVTestYr")
            mudtTblCtrlParam.SelIndxScale = .Item("SelIndxScale")
         End With
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'Empty.
End Property

' Update the ContrlParam table, if allowed.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   If mblnAllowWrite Then
      With mudtTblCtrlParam
         strCmdTxt = "spUpdate_ContrlParam(" & .AgeWeanMin & ", " & .AgeWeanMax & ", " & _
            .Age7MonMin & ", " & .Age7MonMax & ", " & IIf(.Age1YrChk, 1, 0) & ", " & _
            .Age1YrWtMin & ", " & .Age1YrWtMax & ", " & .Age1YrShearMin & ", " & _
            .Age1YrShearMax & ", " & .AgeMatMinSr & ", " & .AgeMatMinDm & ", " & _
            .LifeTimeMax & ", " & .PregnLengMin & ", " & .PregnLengNorm & ", " & _
            .PregnLengMax & ", " & .InterAnnlMin & ", " & .InterAnnlMax & ", " & IIf( _
            BrdBasDam, 1, 0) & ", " & IIf(ConvCrsToPure, 1, 0) & ", " & IIf( _
            .BVTestLifeTime, 1, 0) & ", " & .BVTestYr & ", " & .SelIndxScale & ")"
      End With
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.GenrlModl Err.Description, frmCtrlParam
End Sub

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

