VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblWtWool"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl
 
Dim mobSQLErrHnd As SQLErrHnd

'Dim mintAgeOrig As Integer
Dim mdtmDateAnnl As Date
Dim mdtmDateShearAnnl As Date

Public IDShG As String
Public AgeOrig As Integer
Public Age As Integer
Public WtAnnl As Single
Public GreaseAnnl As Single

' Create the mobSQLErrHnd object.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Let & get DateAnnl.
Public Property Let DateAnnl(ByVal dtmDateAnnl As Date)
    mdtmDateAnnl = dtmDateAnnl
End Property

Public Property Get DateAnnl() As Date
    DateAnnl = IIf(mdtmDateAnnl = gobSetng.SQLDateZero, 0, mdtmDateAnnl)
End Property

' Let & get DateShearAnnl.
Public Property Let DateShearAnnl(ByVal dtmDateShearAnnl As Date)
   mdtmDateShearAnnl = dtmDateShearAnnl
End Property

Public Property Get DateShearAnnl() As Date
   DateShearAnnl = IIf(mdtmDateShearAnnl = gobSetng.SQLDateZero, 0, mdtmDateShearAnnl)
End Property

' Delete the current record from the WeightWoolAnnl table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "delete from WeightWoolAnnl where IDSheepGoat = '" & IDShG & "' and " & _
      "Age = " & Age
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateAnnl As String
   Dim strDateShearAnnl As String
   strDateAnnl = DateNullVsStr(mdtmDateAnnl) 'Convert DateAnnl & DateShearAnnl.
   strDateShearAnnl = DateNullVsStr(mdtmDateShearAnnl)
   strCmdTxt = "INSERT INTO WeightWoolAnnl (IDSheepGoat, Age, DateAnnl, WtAnnl, " & _
      "DateShearAnnl, GreaseAnnl) " & _
      "VALUES ('" & IDShG & "', " & Age & ", " & strDateAnnl & ", " & IIf(WtAnnl = 0, _
         gobSetng.NullStr, Util.NumStrDB(WtAnnl)) & ", " & strDateShearAnnl & ", " & _
         IIf(GreaseAnnl = 0, gobSetng.NullStr, Util.NumStrDB(GreaseAnnl)) & ")"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

' Select data from the WeightWoolAnnl table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
    Dim rstWtWool As ADODB.Recordset
    Dim strCmdTxt As String
    Dim strIDShG As String
    Dim intAge As Integer
    Set rstWtWool = New ADODB.Recordset
    strIDShG = vntKeys(0)
    intAge = vntKeys(2)
    strCmdTxt = "SELECT * FROM WeightWoolAnnl WHERE IDSheepGoat = '" & strIDShG & _
      "' AND Age = " & intAge
    With rstWtWool
        .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
        If .EOF And .BOF Then
            ' Give feedback on whether there is a weighing.
            gobMsgInst.NoWtWoolSnd frmMDI.ActiveForm
        Else
            ' Define the animal's data from the WtWool recordset.
            With .Fields
                IDShG = .Item("IDSheepGoat")
                AgeOrig = .Item("Age")
                Age = .Item("Age")
                mdtmDateAnnl = IIf(IsNull(.Item("DateAnnl")), gobSetng.SQLDateZero, _
                  .Item("DateAnnl"))
                WtAnnl = IIf(IsNull(.Item("WtAnnl")), 0, .Item("WtAnnl"))
                mdtmDateShearAnnl = IIf(IsNull(.Item("DateShearAnnl")), gobSetng _
                  .SQLDateZero, .Item("DateShearAnnl"))
                GreaseAnnl = IIf(IsNull(.Item("GreaseAnnl")), 0, .Item("GreaseAnnl"))
            End With
        End If
    End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the WeightWoolAnnl table.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateAnnl As String
   Dim strDateShearAnnl As String
   strDateAnnl = DateNullVsStr(mdtmDateAnnl) 'Convert DateAnnl & DateShearAnnl.
   strDateShearAnnl = DateNullVsStr(mdtmDateShearAnnl)
   strCmdTxt = "UPDATE WeightWoolAnnl SET Age = " & Age & ", DateAnnl = " & strDateAnnl _
      & ", WtAnnl = " & IIf(WtAnnl = 0, gobSetng.NullStr, Util.NumStrDB(WtAnnl)) & _
      ", DateShearAnnl = " & strDateShearAnnl & ", GreaseAnnl = " & IIf(GreaseAnnl = 0, _
      gobSetng.NullStr, Util.NumStrDB(GreaseAnnl)) & _
      " WHERE IDSheepGoat = '" & IDShG & "' and Age = " & Age
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Compose the collection of the WeightWoolAnnl table's primary keys.
Public Function GetKeys(ByVal strIDShG As String) As Keys
On Error GoTo ErrHnd
   Dim obKeys As Keys
   Dim rstWtWool As ADODB.Recordset
   Dim strCmdTxt As String
   Set obKeys = New Keys
   Set rstWtWool = New ADODB.Recordset 'Open the record set with the specified sheep/
   strCmdTxt = "SELECT IDSheepGoat, Age FROM WeightWoolAnnl WHERE IDSheepGoat = '" & _
      strIDShG & "'" 'goat's weighings/shearings.
   rstWtWool.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic
   With rstWtWool 'Compose the colleciton.
      If .EOF = False And .BOF = False Then
         Do Until .EOF
            obKeys.Add .Fields("IDSheepGoat"), , .Fields("Age")
            .MoveNext
         Loop
      End If
   End With
   Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

' Return a Null or date string based on the date.
Private Function DateNullVsStr(ByVal dtmDate As Date) As String
On Error GoTo ErrHnd
   If dtmDate = 0 Then
      DateNullVsStr = gobSetng.NullStr
   Else
      DateNullVsStr = "'" & Util.DateStrDB(dtmDate) & "'"
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
