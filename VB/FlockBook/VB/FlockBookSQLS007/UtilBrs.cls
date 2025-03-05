VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UtilBrs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const mintFormtDate As Integer = 1
Const mintFormtNum As Integer = 2
 
Dim mflexCtl As MSHFlexGrid
Dim mintCyclAgeCol As Integer

' Set by reference the mflexCtl module-level control to operate on.
Public Property Set Grid(ByRef flexCtl As MSHFlexGrid)
   Set mflexCtl = flexCtl
End Property

' Let the cycle/age column number.
Public Property Let CyclAgeCol(ByVal intCyclAgeCol As Integer)
   mintCyclAgeCol = intCyclAgeCol
End Property

' Set the deFlockBook DataEnvironment's specified command's parameters.
Public Sub SetDEParam(ByVal strCmdNam As String, ByVal strParamNam As String, ByVal _
   vntParamVal As Variant)
On Error GoTo ErrHnd
   With deFlockBook.Recordsets(strCmdNam) 'Close the recordset.
      If .State = adStateOpen Then .Close
   End With
   deFlockBook.Commands(strCmdNam).Parameters(strParamNam).Value = vntParamVal 'Set the
Exit Sub                                                                      'parameter.
ErrHnd:
MsgBox Err.Description
End Sub

' Format
'  - date shown in the SQL Server's year-month-day format to day-monthj-year;
'  - number to show with integer and fractional parts;
'  - abortion text from True/False to Yes/No.
Public Sub Formt(ByVal intFormtIdx As Integer, ByVal intCol As Integer, ByVal _
   strCaptCol As String)
On Error GoTo ErrHnd
   Dim intRowOrig As Integer
   Dim intColOrig As Integer
   Dim strYes As String
   Dim strNo As String
   Dim I As Integer
   With mflexCtl
      If .Cols > 0 And .Rows > 0 Then 'Are there columns & rows?
         intRowOrig = .Row 'Remember the original position.
         intColOrig = .Col
         .Col = intCol 'The specified column.
         For I = 1 To .Rows - 1
            .Row = I
            If .Text <> "" And .Text <> strCaptCol Then 'Format the column.
               Select Case intFormtIdx
               Case mintFormtDate 'Date.
                  .Text = DateValue(.Text)
               Case mintFormtNum 'Number.
                  .Text = gobFormtCtl.NumFrac(Val(.Text)) 'The Val function cuts too
               End Select                                    'many digits after the decimal.
            End If
         Next
         .Row = intRowOrig 'Move to the original position.
         .Col = intColOrig
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Focus the active cycle/age row, if defined.
Public Sub CyclAgeActFoc(ByVal intActCyclAge As Integer, ByVal intColDeflt As Integer, _
   ByVal strCaptCol As String)
On Error GoTo ErrHnd
   Dim I As Integer
   If mintCyclAgeCol > 0 Then 'Defined?
Debug.Assert 0 = 1 'Verify If
      With mflexCtl
         .Col = mintCyclAgeCol 'The cycle/age column.
         For I = .Rows - 1 To 1 Step -1 'Loop to look for the active cycle/age in the grid.
            .Row = I
            If .Text <> "" And .Text <> strCaptCol Then 'Skip blank cells.
               If CInt(.Text) = intActCyclAge Then Exit For 'Exit, if found.
            End If
         Next
         .Col = intColDeflt 'Focus the active cycle/age's first column.
      End With
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the cycle/age from the selected row in the mflexCtl control.
Public Function CyclAgeGet(ByVal strCaptCol As String) As Integer
On Error GoTo ErrHnd
   With mflexCtl
      .Col = mintCyclAgeCol 'The cycle/age column.
      If .Text = strCaptCol Then 'The caption is selected instead of the data cell.
         If .Row < .Rows - 1 Then .Row = .Row + 1 'Move down, unless it's the last row.
      End If
      While .Text = "" 'Move up, if the cell in the current row is blank.
         .Row = .Row - 1
      Wend
      CyclAgeGet = CInt(.Text)
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' The date formatting index.
Public Property Get FormtDate() As Integer
   FormtDate = mintFormtDate
End Property

' The number formatting index.
Public Property Get FormtNum() As Integer
   FormtNum = mintFormtNum
End Property

