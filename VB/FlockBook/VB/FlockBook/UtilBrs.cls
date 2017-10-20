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
                  .Text = FormtDateDo(.Text) 'Place properly the day & month.
'                  .Text = DateValue(.Text)
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

' Format a date string to put the day & month to the positions based on the PC's current
'  regional setting vs. US English.
' If neither day nor month is above 12 the MSHFlexGrid control places the month first
'  regardless of the reginal settings. Unless this position of the month proper, place
'  the day in front (by ther Russian setting).
Private Function FormtDateDo(ByVal strDate As String) As String
On Error GoTo ErrHnd
   Const dtmTempl As Date = #12/31/1999# 'The template date.
   Const intPostnDayTempl As Integer = 1 'US Egnlish month position.
   Const intPostnDayMonTempl As Integer = 3 'The Day-to-Month separator' position.
   Const intDayMon12 As Integer = 12 'Day or month = 12.
   Dim intPostnDayMon As Integer
   Dim intPostnMonYr As Integer
   Dim strDateTempl As String
   Dim strSepartr As String
   Dim strDay As String
   Dim strMon As String
   If InStr(CStr(dtmTempl), CStr(Day(dtmTempl))) = intPostnDayTempl Then 'Should Day be in front by the current setting?
      If Day(DateValue(strDate)) > intDayMon12 Or Month(DateValue(strDate)) > intDayMon12 Then 'Day or month > 12?
         FormtDateDo = CStr(DateValue(strDate)) 'No need to replace day & month if either is > 12.
      Else 'Place the day in front.
         strDateTempl = CStr(DateValue(dtmTempl)) 'The template date's string by the reginal set
         strSepartr = Mid$(strDateTempl, intPostnDayMonTempl, 1) 'The separator character.
         strDate = CStr(DateValue(strDate)) '1st convertion.
         intPostnDayMon = InStr(strDate, strSepartr) 'The Day-Mon & Mon-Yr separators'
         intPostnMonYr = InStr(intPostnDayMon + 1, strDate, strSepartr) 'positions.
         strDay = Mid$(strDate, intPostnDayMon + 1, intPostnMonYr - intPostnDayMon - 1) 'Day.
         strMon = Left$(strDate, intPostnDayMon - 1) 'Month.
         FormtDateDo = strDay & strSepartr & strMon & strSepartr & Mid$(strDate, _
            intPostnMonYr + 1)
      End If
   Else 'Month should be in front.
      FormtDateDo = CStr(DateValue(strDate))
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function
