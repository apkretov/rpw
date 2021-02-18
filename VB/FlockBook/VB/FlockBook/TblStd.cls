VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblStd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Const mintStdWt As String = 1 'Count from 1 to distinguish the 1st & undefined indexes.
Const mintStdGrease As String = 2
Const mintStdLeng As String = 3
Const mintStdDiam As String = 4
Const mintStdFatTail As String = 5

Private Type TblStdTp
   IDBrd As String
   MaleMax As Variant
   MaleMin As Variant
   MaleElite As Variant
   MaleClass1 As Variant
   FemaleMax As Variant
   FemaleMin As Variant
   FemaleElite As Variant
   FemaleClass1 As Variant
End Type
Dim mudtTblStd As TblStdTp
Dim mudtTblStdOrig As TblStdTp

Dim mblnEscSelFail As Boolean
Dim mblnFull As Boolean
Dim mintStd As Integer

Dim mobSQLErrHnd As SQLErrHnd

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' IDBrd.
Public Property Get IDBrd() As String
   IDBrd = mudtTblStd.IDBrd
End Property

' IDBrd.
Public Property Let IDBrd(ByVal strIDBrd As String)
   mudtTblStd.IDBrd = strIDBrd
End Property

' MaleMax.
Public Property Get MaleMax() As Variant
   MaleMax = mudtTblStd.MaleMax
End Property

' MaleMax.
Public Property Let MaleMax(ByVal vntMaleMax As Variant)
   mudtTblStd.MaleMax = ConvTyp(vntMaleMax)
End Property

' MaleMin.
Public Property Get MaleMin() As Variant
   MaleMin = mudtTblStd.MaleMin
End Property

' MaleMin.
Public Property Let MaleMin(ByVal vntMaleMin As Variant)
   mudtTblStd.MaleMin = ConvTyp(vntMaleMin)
End Property

' MaleElite.
Public Property Get MaleElite() As Variant
   MaleElite = mudtTblStd.MaleElite
End Property

' MaleElite.
Public Property Let MaleElite(ByVal vntMaleElite As Variant)
   mudtTblStd.MaleElite = ConvTyp(vntMaleElite)
End Property

' MaleClass1.
Public Property Get MaleClass1() As Variant
   MaleClass1 = mudtTblStd.MaleClass1
End Property

' MaleClass1.
Public Property Let MaleClass1(ByVal vntMaleClass1 As Variant)
   mudtTblStd.MaleClass1 = ConvTyp(vntMaleClass1)
End Property

' FemaleMax.
Public Property Get FemaleMax() As Variant
   FemaleMax = mudtTblStd.FemaleMax
End Property

' FemaleMax.
Public Property Let FemaleMax(ByVal vntFemaleMax As Variant)
   mudtTblStd.FemaleMax = ConvTyp(vntFemaleMax)
End Property

' FemaleMin.
Public Property Get FemaleMin() As Variant
   FemaleMin = mudtTblStd.FemaleMin
End Property

' FemaleMin.
Public Property Let FemaleMin(ByVal vntFemaleMin As Variant)
   mudtTblStd.FemaleMin = ConvTyp(vntFemaleMin)
End Property

' FemaleElite.
Public Property Get FemaleElite() As Variant
   FemaleElite = mudtTblStd.FemaleElite
End Property

' FemaleElite.
Public Property Let FemaleElite(ByVal vntFemaleElite As Variant)
   mudtTblStd.FemaleElite = ConvTyp(vntFemaleElite)
End Property

' FemaleClass1.
Public Property Get FemaleClass1() As Variant
   FemaleClass1 = mudtTblStd.FemaleClass1
End Property

' FemaleClass1.
Public Property Let FemaleClass1(ByVal vntFemaleClass1 As Variant)
   mudtTblStd.FemaleClass1 = ConvTyp(vntFemaleClass1)
End Property

' Validate whether all parameters are defined it the specified Stand* table for the
'  current breed.
' Return True, if succeeds.
Public Function VldParam() As Boolean
On Error GoTo ErrHnd
   With mudtTblStd
      If .MaleMax <> 0 Then
         If .MaleMin <> 0 Then
            If .MaleElite <> 0 Then
               If .MaleClass1 <> 0 Then
                  If .FemaleMax <> 0 Then
                     If .FemaleMin <> 0 Then
                        If .FemaleElite <> 0 Then
                           If .FemaleClass1 <> 0 Then VldParam = True 'Succeeded.
                        End If
                     End If
                  End If
               End If
            End If
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the SP to delete a record from the specified Stand* table.
Private Function SPDel() As String
On Error GoTo ErrHnd
   Select Case mintStd 'Choose a SP.
   Case mintStdWt
Debug.Assert 0 = 1 'Verify
      SPDel = "DELETE FROM StandWeight WHERE IDBreed = '"
   Case mintStdGrease
Debug.Assert 0 = 1 'Verify
      SPDel = "DELETE FROM StandGrease WHERE IDBreed = '"
   Case mintStdLeng
Debug.Assert 0 = 1 'Verify
      SPDel = "DELETE FROM StandLength WHERE IDBreed = '"
   Case mintStdDiam
Debug.Assert 0 = 1 'Verify
      SPDel = "DELETE FROM StandDiameter WHERE IDBreed = '"
   Case mintStdFatTail
Debug.Assert 0 = 1 'Verify
      SPDel = "DELETE StandFatTail WHERE IDBreed = '"
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the SP to insert the data into the specified Stand* table.
Private Function SPIns() As String
On Error GoTo ErrHnd
   Const strInsIn As String = "INSERT INTO "
   Const strFld As String = " (IDBreed, MaleMax, MaleMin, MaleElite, MaleClass1, " & _
      "FemaleMax, FemaleMin, FemaleElite, FemaleClass1) VALUES "
   Select Case mintStd 'Choose a SP.
   Case mintStdWt
      SPIns = strInsIn & "StandWeight" & strFld & SPParamInsNum
   Case mintStdGrease
      SPIns = strInsIn & "StandGrease" & strFld & SPParamInsNum
   Case mintStdLeng
      SPIns = strInsIn & "StandLength" & strFld & SPParamInsNum
   Case mintStdDiam
      SPIns = strInsIn & "StandDiameter" & strFld & SPParamInsStr
   Case mintStdFatTail
      SPIns = strInsIn & "StandFatTail" & strFld & SPParamInsStr
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the SP to select the data from the specified Stand* table.
Private Function SPSel() As String
On Error GoTo ErrHnd
   Select Case mintStd 'Choose a SP.
   Case mintStdWt
      SPSel = "select * from StandWeight where IDBreed = '"
   Case mintStdGrease
      SPSel = "SELECT * FROM StandGrease WHERE IDBreed = '"
   Case mintStdLeng
      SPSel = "select * from StandLength where IDBreed = '"
   Case mintStdDiam
      SPSel = "SELECT * FROM StandDiameter WHERE IDBreed = '"
   Case mintStdFatTail
      SPSel = "select * from StandFatTail where IDBreed = '"
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return the SP to insert the data into the specified Stand* table.
Private Function SPUpd() As String
On Error GoTo ErrHnd
   Select Case mintStd 'Choose a SP.
   Case mintStdWt
      SPUpd = "UPDATE StandWeight " & SPParamUpdNum
   Case mintStdGrease
      SPUpd = "UPDATE StandGrease " & SPParamUpdNum
   Case mintStdLeng
Debug.Assert 0 = 1 'Verify
      SPUpd = "UPDATE StandLength " & SPParamUpdNum
   Case mintStdDiam
      SPUpd = "UPDATE StandDiameter " & SPParamUpdStr
   Case mintStdFatTail
      SPUpd = "UPDATE StandFatTail " & SPParamUpdStr
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Stand* table's ID.
Public Property Get StdWt() As Integer
   StdWt = mintStdWt
End Property

' Stand* table's ID.
Public Property Get StdGrease() As Integer
   StdGrease = mintStdGrease
End Property

' Stand* table's ID.
Public Property Get StdLeng() As Integer
   StdLeng = mintStdLeng
End Property

' Stand* table's ID.
Public Property Get StdDiam() As Integer
   StdDiam = mintStdDiam
End Property

' Stand* table's ID.
Public Property Get StdFatTail() As Integer
   StdFatTail = mintStdFatTail
End Property

' Delete the current record from the Breeds table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
Debug.Assert 0 = 1 'Verify
   strCmdTxt = SPDel & mudtTblStd.IDBrd & "'"
'   strCmdTxt = SPDel & mudtTblStd.IDBrd & "')"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   mblnFull = False 'Mark empty.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Full record mark.
Private Property Get DatTbl_Full() As Boolean
   DatTbl_Full = mblnFull
End Property

' Add a new record to a Stand* table.
' Mark an error for later reference, if any.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   gcnnConn.Execute SPIns, , adCmdText + adExecuteNoRecords
   mblnFull = True 'Mark full.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function DatTbl_OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblStdOrig
'      If .IDBrd = mudtTblStd.IDBrd Then
         If .MaleMax = mudtTblStd.MaleMax Then
            If .MaleMin = mudtTblStd.MaleMin Then
               If .MaleElite = mudtTblStd.MaleElite Then
                  If .MaleClass1 = mudtTblStd.MaleClass1 Then
                     If .FemaleMax = mudtTblStd.FemaleMax Then
                        If .FemaleMin = mudtTblStd.FemaleMin Then
                           If .FemaleElite = mudtTblStd.FemaleElite Then
                              If .FemaleClass1 = mudtTblStd.FemaleClass1 Then _
                                 DatTbl_OrigCompr = True 'Equal.
                           End If
                        End If
                     End If
                  End If
               End If
            End If
         End If
'      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Save the original data after selecting.
Private Sub DatTbl_OrigSave()
On Error GoTo ErrHnd
   With mudtTblStdOrig
'      .IDBrd = mudtTblStd.IDBrd
      .MaleMax = mudtTblStd.MaleMax
      .MaleMin = mudtTblStd.MaleMin
      .MaleElite = mudtTblStd.MaleElite
      .MaleClass1 = mudtTblStd.MaleClass1
      .FemaleMax = mudtTblStd.FemaleMax
      .FemaleMin = mudtTblStd.FemaleMin
      .FemaleElite = mudtTblStd.FemaleElite
      .FemaleClass1 = mudtTblStd.FemaleClass1
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Define the data from the specified Stand* table for the specified breed.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstStandWt As ADODB.Recordset
   Dim strIDBrd As String
   Dim strCmdTxt As String
   Set rstStandWt = New ADODB.Recordset
   strIDBrd = CStr(vntKeys(0))
   strCmdTxt = SPSel & strIDBrd & "'"
   rstStandWt.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
   With rstStandWt.Fields 'Define the data from the recordset.
      mudtTblStd.IDBrd = .Item("IDBreed")
      mudtTblStd.MaleMax = .Item("MaleMax")
      mudtTblStd.MaleMin = .Item("MaleMin")
      mudtTblStd.MaleElite = .Item("MaleElite")
      mudtTblStd.MaleClass1 = .Item("MaleClass1")
      mudtTblStd.FemaleMax = .Item("FemaleMax")
      mudtTblStd.FemaleMin = .Item("FemaleMin")
      mudtTblStd.FemaleElite = .Item("FemaleElite")
      mudtTblStd.FemaleClass1 = .Item("FemaleClass1")
   End With
   Call DatTbl_OrigSave 'Save original data.
   mblnFull = True 'Mark full.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Cancel the Selection Failed message.
Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
   mblnEscSelFail = blnEscSelFail
End Property

' Update the form's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   If Not DatTbl_OrigCompr Then gcnnConn.Execute SPUpd, , adCmdText + _
      adExecuteNoRecords 'Update, if changed.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Return the number parameter (w/o apostrophes) line added to the Insert SP.
Private Property Get SPParamUpdNum() As String
On Error GoTo ErrHnd
   With mudtTblStd
   SPParamUpdNum = "SET MaleMax = " & Util.NumStrDB(.MaleMax) & ", MaleMin = " & Util _
      .NumStrDB(.MaleMin) & ", MaleElite = " & Util.NumStrDB(.MaleElite) & ", MaleClass1 = " & Util _
      .NumStrDB(.MaleClass1) & ", FemaleMax = " & Util.NumStrDB(.FemaleMax) & _
      ", FemaleMin = " & Util.NumStrDB(.FemaleMin) & ", FemaleElite = " & Util.NumStrDB _
      (.FemaleElite) & ", FemaleClass1 = " & Util.NumStrDB(.FemaleClass1) & _
      " WHERE IDBreed = '" & .IDBrd & "'"
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the string parameter (with apostrophes) line added to the Insert SP.
Private Property Get SPParamUpdStr() As String
On Error GoTo ErrHnd
   With mudtTblStd
      SPParamUpdStr = "SET MaleMax = '" & .MaleMax & "', MaleMin = '" & .MaleMin & _
         "', MaleElite = '" & .MaleElite & "', MaleClass1 = '" & .MaleClass1 & _
         "', FemaleMax = '" & .FemaleMax & "', FemaleMin = '" & .FemaleMin & _
         "', FemaleElite = '" & .FemaleElite & "', FemaleClass1 = '" & .FemaleClass1 & _
         "' WHERE IDBreed = '" & .IDBrd & "'"
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the number parameter (w/o apostrophes) line added to the Insert SP.
Private Property Get SPParamInsNum() As String
On Error GoTo ErrHnd
   With mudtTblStd
   SPParamInsNum = "('" & .IDBrd & "', " & Util.NumStrDB(.MaleMax) & ", " & Util _
      .NumStrDB(.MaleMin) & ", " & Util.NumStrDB(.MaleElite) & ", " & Util.NumStrDB( _
      .MaleClass1) & ", " & Util.NumStrDB(.FemaleMax) & ", " & Util.NumStrDB(.FemaleMin _
      ) & ", " & Util.NumStrDB(.FemaleElite) & ", " & Util.NumStrDB(.FemaleClass1) & ")"
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Return the string parameter (with apostrophes) line added to the Insert SP.
Private Property Get SPParamInsStr() As String
On Error GoTo ErrHnd
   With mudtTblStd
      SPParamInsStr = "('" & .IDBrd & "', '" & .MaleMax & "', '" & .MaleMin & "', '" & _
         .MaleElite & "', '" & .MaleClass1 & "', '" & .FemaleMax & "', '" & .FemaleMin _
         & "', '" & .FemaleElite & "', '" & .FemaleClass1 & "')"
   End With
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Let the breed standard table's index.
Public Property Let Std(ByVal intStd As Integer)
   mintStd = intStd
End Property

' Convert the specified value to Single/String based on the breed standards' type.
Private Function ConvTyp(ByVal vntVal As Variant)
On Error GoTo ErrHnd
   Select Case mintStd 'Select the type.
   Case mintStdWt, mintStdGrease, mintStdLeng 'Single.
      ConvTyp = CSng(vntVal)
   Case mintStdDiam, mintStdFatTail 'String.
      ConvTyp = CStr(vntVal)
   End Select
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

