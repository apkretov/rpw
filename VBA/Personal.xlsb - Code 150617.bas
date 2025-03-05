Attribute VB_Name = "Code"
Option Explicit

Const mlngPasteCellRow As Long = 3, mlngPasteCellCol As Long = 30 'Unlike the inital position (mlngPasteCellCol As Long = 12), the formulas have been placed away from the table L48:Q73 in the Database sheet.
Const mstrFormulasData As String = "H1:H3936", mstrFormulasRow24_42 As String = "L1059:L1118"
Const mstrA41 As String = "A41", mstrA42 As String = "A42", mstrA44 As String = "A44"

Private Sub FormatAndFillIn(rngCell As Range, ByVal strValue As String) 'Format and enter the cell.
    With rngCell
        .Font.Bold = False
        .Font.Italic = True
        .Value = strValue
    End With
End Sub

Private Function KTB_HasDependents(ByVal target As Excel.Range) As Boolean
    On Error Resume Next
    HasDependents = target.Dependents.Count
End Function

Private Function KTB_Formulas(rngSelection As Range) As Range 'Get the formulas range.
    Const lngCellLowest As Long = 10000 'Any column much lower than the formula columns.
    Dim rngCell As Range, rngDependent As Range, rngFormulas As Range
    Dim lngRowHighest As Long, lngRowLowest As Long
    Dim I As Integer, J As Integer
    Dim blnNoFormula As Boolean
    With ActiveWorkbook.Sheets("Database")
        lngRowHighest = lngCellLowest 'Initialise the highest formula cell index.
        For I = mlngPasteCellRow To mlngPasteCellRow + rngSelection.Rows.Count 'Run through each cell.
            For J = mlngPasteCellCol To mlngPasteCellCol + rngSelection.Columns.Count
                Set rngCell = .Cells(I, J)
                With rngCell
                    If Not .Locked Then
                        If Not HasDependents(rngCell) Then 'No formulas?
                            blnNoFormula = True
                            If MsgBox("No formula found in the current cell! Suspend deleting?", vbYesNoCancel + vbQuestion) = vbYes Then
                                Exit For 'Suspend deletion.
                            End If
                        Else
                            Set rngDependent = .DirectDependents
                            If lngRowHighest > rngDependent.Column Then lngRowHighest = rngDependent.Row 'Find the highest formula cell.
                            If lngRowLowest < rngDependent.Column Then lngRowLowest = rngDependent.Row 'Find the lowest formula cell.
                        End If
                    End If
                End With
            Next
            If blnNoFormula Then Exit For
        Next
        If Not blnNoFormula Then Set Formulas = .Range(.Cells(lngRowHighest, rngDependent.Column), .Cells(lngRowLowest, rngDependent.Column)) 'The formulas range.
    End With
End Function

Private Function KTB_DeleteFormulas(rngSelection As Range) As Boolean 'Delete the formulas on the Database sheet.
    Dim rngFormulas As Range
    DeleteFormulas = True
    rngSelection.Parent.Unprotect 'Unprotect the source sheet to cut its cells.
    With ActiveWorkbook.Sheets("Database")
        .Select
        .Unprotect
        rngSelection.Cut 'Cut the blank table.
        .Cells(mlngPasteCellRow, mlngPasteCellCol).Select 'Select the paste cell.
        .Paste 'Paste the blank table.
        .Cells(mlngPasteCellRow, 1).Select 'Make the first column of the sheet visible.
        .Cells(mlngPasteCellRow, mlngPasteCellCol).Select 'Seletect its upper left corner in the new parent sheet i.e. the paste cell in Database.
        Set rngFormulas = Formulas(rngSelection) 'Get the formulas range.
        If rngFormulas Is Nothing Then 'No formulas?
            DeleteFormulas = False
        Else 'Delete the formulas.
            rngFormulas.Select 'Show the entire formulas range.
            ActiveWindow.SmallScroll Down:=12 'Scroll down to show the maximal number of cell below. By default the first cell visible is placed in the window center.
            If MsgBox("Delete " & rngSelection.Rows.Count * rngSelection.Columns.Count & " formulas?", vbYesNoCancel + vbQuestion) <> vbYes Then 'Reject deleting formulas?
                DeleteFormulas = False
            Else
                rngFormulas.ClearContents 'Delete the formulas.
            End If
        End If
        .Range(.Cells(mlngPasteCellRow, mlngPasteCellCol), .Cells(mlngPasteCellRow + rngSelection.Rows.Count - 1, mlngPasteCellCol + rngSelection.Columns.Count - 1)).Select 'Seletect the cut/pasted table and return it back to the source sheet.
        Selection.Cut
    End With
    With rngSelection.Parent
        .Select
        .Paste
        If DeleteFormulas Then rngSelection.Font.Strikethrough = True 'Flag to prevent any reiterated validations in future.
    End With
    With ActiveWorkbook.Sheets("Database")
        .Protect
        If Not rngFormulas Is Nothing Then 'Show the formulas range.
            .Select
            rngFormulas.Select
        End If
    End With
    If Not DeleteFormulas Then rngSelection.Parent.Select 'Stay on the soursce sheet unless deletion succeeded.
End Function

Private Function DeleteFormulas(rngSelection As Range, ByVal strDatabaseFormulas As String) As Boolean 'Delete the formulas on the Database sheet.
    Dim rngFormulas As Range, rngDatabaseFormulas As Range
    DeleteFormulas = True
    rngSelection.Parent.Unprotect 'Unprotect the source sheet to edit its cells.
    With ActiveWorkbook.Sheets("Database")
        .Select
        .Unprotect
            Set rngDatabaseFormulas = .Range(strDatabaseFormulas)
            rngDatabaseFormulas.Select 'Show the entire formulas range.
            ActiveWindow.SmallScroll Down:=12 'Scroll down to show the maximal number of cell below. By default the first cell visible is placed in the window center.
            If MsgBox("Delete " & rngSelection.Rows.Count * rngSelection.Columns.Count & " formulas?", vbYesNoCancel + vbQuestion) <> vbYes Then 'Reject deleting formulas?
                DeleteFormulas = False
            Else
                rngDatabaseFormulas.ClearContents 'Delete the formulas.
            End If
    End With
    With rngSelection.Parent
        .Activate
        If DeleteFormulas Then rngSelection.Font.Strikethrough = True 'Flag to prevent any reiterated validations in future.
    End With
    With ActiveWorkbook.Sheets("Database")
        .Protect
        .Select
        rngDatabaseFormulas.Select
    End With
    'KTB: If Not DeleteFormulas Then rngSelection.Parent.Select 'Stay on the soursce sheet unless deletion succeeded.
End Function

Private Function EntireTableBlank(rngTable As Range, ByVal strDatabaseFormulas As String, ByVal intLowestOptionalRow As Integer) As Boolean 'Is the entire table blank?
    Dim rngCell As Range
    Dim blnFilledOrChecked As Boolean
    For Each rngCell In rngTable 'Validate all the cells.
        With rngCell
            If Not .Locked Then
                If .Value <> vbNullString Or .Font.Strikethrough Then 'Not blank or checked before?
                    blnFilledOrChecked = True
                    Exit For
                End If
            End If
        End With
    Next
    If Not blnFilledOrChecked Then 'Neither filled nor checked before?
        EntireTableBlank = True 'Flag to suspend for manual edition.
        rngTable.Parent.Select
        rngTable.Select
        If intLowestOptionalRow <> 0 Then 'Optional table table needs no formulas deletion.
            If MsgBox("The entire table is blank! Continue", vbYesNoCancel + vbQuestion) = vbYes Then
                rngTable.Parent.Unprotect
                rngTable.Font.Strikethrough = True 'Flag to prevent any reiterated validations in future.
            Else
                EntireTableBlank = False 'Flag to suspend.
            End If
        ElseIf MsgBox("The entire table is blank! Delete the formulas?", vbYesNoCancel + vbQuestion) = vbYes Then
            If DeleteFormulas(Selection, strDatabaseFormulas) Then 'Delete the formulas on the Database sheet.
                rngTable.Parent.Select
                rngTable.Select
                If MsgBox("Formulas deleted! Continue", vbYesNoCancel + vbQuestion) = vbYes Then EntireTableBlank = False 'Flag to continue w/o suspending.
            End If
        End If
    End If
End Function

Private Function ValidateLockedCells(rngTable As Range, rngLockedRange As Range) As Boolean 'Prevent unathorized cells locking such as Sweden did.
    Dim rngCell As Range, rngCellLocked As Range
    Dim blnOriginallyLocked As Boolean
    Dim blnRestoreLocked As Boolean, blnRestoreUnlocked As Boolean
    ValidateLockedCells = True
    rngTable.Parent.Unprotect
    If Not rngLockedRange Is Nothing Then 'Check if the original locks are untouched.
        For Each rngCellLocked In rngLockedRange
            With rngCellLocked
                If Not .Font.Strikethrough Then ' Not checked yet?
                    If Not .Locked Then
                        .Parent.Select 'Show this cell.
                        .Select
                        If Not blnRestoreLocked Then blnRestoreLocked = MsgBox("Unauthorised cell unlocking! Restore orinigal locking?", vbYesNoCancel + vbCritical) = vbYes
                        If blnRestoreLocked Then
                            .Locked = True
                        Else
                            ValidateLockedCells = False
                            Exit For
                        End If
                    End If
                End If
            End With
        Next
    End If
    If ValidateLockedCells Then 'Continue validation?
        For Each rngCell In rngTable 'Find locked cells.
            With rngCell
                If Not .Font.Strikethrough Then ' Not checked yet?
                    If .Locked Then 'Check if the found cell belongs to the locked range by comparing its address against that of each locked cells.
                        If Not rngLockedRange Is Nothing Then
                            For Each rngCellLocked In rngLockedRange
                                If .Address = rngCellLocked.Address Then
                                    blnOriginallyLocked = True 'Originally locked.
                                    Exit For
                                End If
                            Next
                        End If
                        If Not blnOriginallyLocked Then 'An unauthorized lock?
                            .Parent.Select 'Show this cell.
                            .Select
                            If Not blnRestoreUnlocked Then blnRestoreUnlocked = MsgBox("Unauthorised cell locking! Restore orinigal locking?", vbYesNoCancel + vbCritical) = vbYes
                            If blnRestoreUnlocked Then
                                .Locked = False
                            Else
                                ValidateLockedCells = False 'Validation failed.
                                Exit For
                            End If
                        End If
                    End If
                End If
            End With
        Next
    End If
    If blnRestoreLocked Or blnRestoreUnlocked Then ValidateLockedCells = MsgBox("Original locking restored in all cells! Continue?", vbYesNoCancel + vbQuestion) = vbYes
End Function

Private Function BlankRow(rngCell As Range, rngTable As Range, ByVal intLowestOptionalRow As Integer) As Boolean 'Define if an entire row of optional cell is blank.
    Dim rngCellInRow As Range, rngRow As Range
    If rngCell.Row <= intLowestOptionalRow Then 'Is the cell above the lowest/last optional row?
        Set rngRow = rngTable.Rows(rngCell.Row - rngTable.Cells(1).Row + 1) 'The row of the cell.
        If rngRow.Columns.Count > 1 Then 'Is there more than one cell in a table row?
            BlankRow = True
            For Each rngCellInRow In rngRow.Cells 'Is every cell in this row blank?
                If Not rngCellInRow.Locked Then
                    If rngCellInRow.Value <> vbNullString Then 'A cell found that isn't blank.
                        BlankRow = False
                        Exit For
                    End If
                End If
            Next
        End If
    End If
End Function

Private Function BlankCell(rngCell As Range, Optional intAnswerEnterNA As Integer, Optional rngTable As Range, Optional ByVal intLowestOptionalRow As Integer) As Boolean 'Find a blank cell. Optionally fill it in with n/a.
    Const strNA As String = "n/a"
    Dim blnBlankRow As Boolean
    With rngCell
        If Not .Font.Strikethrough Then ' Not checked yet?
            If .Value = vbNullString Then
                If intLowestOptionalRow <> 0 Then blnBlankRow = BlankRow(rngCell, rngTable, intLowestOptionalRow) 'Are there optional rows in the table? 'Is the entire row blank?
                If Not blnBlankRow Then 'Isn't the cell from an entire blank optional row?
                    .Parent.Unprotect 'Unprotect the sheet to enable entering locked cells.
                    .Parent.Select
                    .Select
                    If intAnswerEnterNA = vbNo Then 'Enter n/a into all blank cells w/o confirmation, if confirmed before?
                        FormatAndFillIn rngCell, strNA 'Format and enter the cell.
                    Else 'Confirm entering.
                        intAnswerEnterNA = MsgBox("A blank cell found! Enter n/a cell by cell?" & vbCrLf & "If no all blank cells of the table will be filled it at once.", vbYesNoCancel + vbQuestion)
                        If intAnswerEnterNA <> vbCancel Then 'Enter n/a?
                            FormatAndFillIn rngCell, strNA 'Format and enter the cell.
                        Else 'Suspend for manual revision.
                            BlankCell = True
                        End If
                    End If
                End If
            End If
        End If
    End With
End Function

Private Function ColorHighlighting(objParent As Object) As Boolean 'Detect and show Colorful font highlighting, if any.
    Const strValidatedRange As String = "A1:M100" 'The range to be validated
    Const lngColorIndexBlack As Long = 1, lngColorIndexWhite As Long = 2, lngColorIndexBlue As Long = 5, lngColorIndexGray15 As Long = 15, lngColorIndexGray48 As Long = 48, lngColorIndexMinus4105 As Long = -4105, lngColorIndexMinus4142 As Long = -4142
    Dim rngCell As Range
    For Each rngCell In objParent.Range(strValidatedRange)
        With rngCell
            If .Text <> vbNullString And .Font.Strikethrough = False Then 'Not blank or checked before? rngCell.Text is used here unlike rngCell.Value in the rest code because of such values as =#REF, =#ERROR, etc.
                If (.Font.ColorIndex <> lngColorIndexBlack And .Font.ColorIndex <> lngColorIndexBlue And .Font.ColorIndex <> lngColorIndexMinus4105) Or (.Interior.ColorIndex <> lngColorIndexWhite And .Interior.ColorIndex <> lngColorIndexGray15 And .Interior.ColorIndex <> lngColorIndexGray48 And .Interior.ColorIndex <> lngColorIndexMinus4142) Then 'Not a black color?
                    objParent.Select
                    .Select
                    If MsgBox("Colorful highlighting! Continue?", vbQuestion + vbYesNoCancel) <> vbYes Then
                        ColorHighlighting = True
                        Exit For
                    Else
                        .Font.Strikethrough = True 'Flag to prevent future validation.
                    End If
                End If
            End If
        End With
    Next
End Function

Private Function TableValidated(rngTable As Range, ByVal strDatabaseFormulas As String, Optional ByVal blnCheckEntireTable As Boolean = True, Optional rngLockedRange As Range, Optional ByVal intLowestOptionalRow As Integer, Optional ByVal blnColorValidation = True) As Boolean
    Dim rngCell As Range
    Dim blnContinue As Boolean
    Dim intAnswerEnterNA As Integer
    If ValidateLockedCells(rngTable, rngLockedRange) Then 'Prevent unathorized cells locking such as Sweden did.
        If blnCheckEntireTable Then 'Check if the entire table is blank?
            blnContinue = Not EntireTableBlank(rngTable, strDatabaseFormulas, intLowestOptionalRow) 'Isn't the entire table blank?
        Else
            blnContinue = True
        End If
        If blnContinue Then 'Continue?
            TableValidated = True
            For Each rngCell In rngTable 'Validate all the cells.
                If Not rngCell.Locked Then
                    If BlankCell(rngCell, intAnswerEnterNA, rngTable, intLowestOptionalRow) Then
                        TableValidated = False
                        Exit For
                    End If
                End If
            Next
            If intAnswerEnterNA = vbNo Then 'Confirm a bulk operation.
                If MsgBox("All blank cells of the table filled in! Continue?", vbYesNoCancel + vbQuestion) <> vbYes Then TableValidated = False
            End If
            If blnColorValidation And TableValidated Then TableValidated = Not ColorHighlighting(rngTable.Parent) 'Any Colorful font highlighting?
        End If
    End If
End Function

Private Function TotalValidated(rngCellsSum As Range, rngCellTotal As Range) As Boolean 'Does the Total cell equal to the summarized cells?
    TotalValidated = True
    If Not rngCellTotal.Font.Strikethrough Then ' Not checked yet?
        With Application.WorksheetFunction
        If .Sum(rngCellsSum) <> .Sum(rngCellTotal) Then
                With rngCellsSum
                    .Parent.Select
                    .Select
                End With
                Select Case MsgBox("The total is not equal to the summarized cells! Enter the sum?", vbQuestion + vbYesNoCancel)
                    Case vbYes
                        FormatAndFillIn rngCellTotal, .Sum(rngCellsSum) 'Format and enter the cell.
                        If MsgBox("The total entered. Continue validation?", vbYesNoCancel + vbQuestion) <> vbYes Then TotalValidated = False 'Suspend validation.
                    Case vbNo
                        rngCellTotal.Font.Strikethrough = True 'Flag to prevent future validation.
                    Case vbCancel
                        TotalValidated = False 'Suspend validation.
                End Select
            End If
        End With
    End If
End Function

Private Function LockMergedCells(rngMergedCells As Range, rngLockedCells As Range) As Range 'Lock the merged cells that originally remained unlocked.
    Dim rngCell As Range
    rngMergedCells.Parent.Unprotect
    rngMergedCells.MergeCells = False 'Unmerge the merged cells.
    For Each rngCell In rngLockedCells 'Lock them.
        rngCell.Locked = True
    Next
    Set LockMergedCells = rngLockedCells
End Function

Private Function ValidateTableIntegrity(rngLockedBlank As Range, ByVal blnBlank As Boolean) As Boolean 'Validate original integrity of the table. Return true, the specified range (around a table) is locked and optionally blank.
    Dim rngCell As Range
    ValidateTableIntegrity = True
    For Each rngCell In rngLockedBlank
        With rngCell
            If Not .Font.Strikethrough Then ' Not checked yet?
                If Not .Locked Or Not IIf(blnBlank, .Text = vbNullString, Not .Text = vbNullString) Then 'Unlocked or cleared/empty?
                    .Parent.Unprotect 'Unprotect the sheet to enable entering locked cells.
                    .Parent.Select
                    .Select
                    If MsgBox("Unauthorised unlocking, deleting, or filling in! Continue?", vbYesNoCancel + vbCritical) = vbYes Then
                        .Font.Strikethrough = True 'Flag to prevent any reiterated validations in future.
                    Else
                        ValidateTableIntegrity = False
                        Exit For
                    End If
                End If
            End If
        End With
    Next
End Function

Public Sub FindBlankCells()
Attribute FindBlankCells.VB_ProcData.VB_Invoke_Func = " \n14"
    Dim blnRow42Deleted As Boolean

    With ActiveWorkbook.Sheets("1.1")
    If ValidateTableIntegrity(.Range("B10:B39,C9"), False) Then
    If ValidateTableIntegrity(.Range("D10:D39,C40"), True) Then
    If ValidateTableIntegrity(.Range("B44:E44,A45:A47"), False) Then
    If ValidateTableIntegrity(.Range("B48:E48,F45:F47"), True) Then
    If ValidateTableIntegrity(.Range("A50,B51:B53"), False) Then
    If ValidateTableIntegrity(.Range("B50:F50,D54:F54,G51:G53"), True) Then
    If ValidateTableIntegrity(.Range("D56:E56"), False) Then
    If ValidateTableIntegrity(.Range("F56,D81:F81"), True) Then
    If ValidateTableIntegrity(.Range("B82,E82,A83:A86,B85"), False) Then
    If ValidateTableIntegrity(.Range("C82:D82,F82,B87:F87,G83:G86"), True) Then
    If ValidateTableIntegrity(.Range("A97:F97"), False) Then
    If ValidateTableIntegrity(.Range("A108:F108,G98:G107"), True) Then
    If TableValidated(.Range(.Cells(10, 3), .Cells(39, 3)), "H3:H32", , , , False) Then
    If TableValidated(.Range(.Cells(45, 2), .Cells(47, 5)), "H33:H44") Then

    With ActiveWorkbook.Sheets("1.2")
    If ValidateTableIntegrity(.Range("C11:E11,B12:B31"), False) Then
    If ValidateTableIntegrity(.Range("C32:E32,F12:F31"), True) Then
    If ValidateTableIntegrity(.Range("B36:E36,A37:A39"), False) Then
    If ValidateTableIntegrity(.Range("B40:E40,F37:F39"), True) Then
    If ValidateTableIntegrity(.Range("D44:G44,A57,A45:A56"), False) Then
    If ValidateTableIntegrity(.Range("B55:C57,D57:G57,H45:H56"), True) Then
    If ValidateTableIntegrity(.Range("A60,B61:B63"), False) Then
    If ValidateTableIntegrity(.Range("B60:G60,D64:G64,C61:C63,H61:H63"), True) Then
    If ValidateTableIntegrity(.Range("B67:B70"), False) Then
    If ValidateTableIntegrity(.Range("D66,D71,C67:C70,E67:E70"), True) Then
    If ValidateTableIntegrity(.Range("A72,C72,F72,A73:A78"), False) Then
    If ValidateTableIntegrity(.Range("D72:E72,G72,C79,B79:G79,B73:B78,H73:H78"), True) Then
    If ValidateTableIntegrity(.Range("A88:F88"), False) Then
    If ValidateTableIntegrity(.Range("G88,A99:G99,H89:H98"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(31, 5)), "H184:H243", , , , False) Then 'Table 1.2a
    If TableValidated(.Range(.Cells(37, 2), .Cells(39, 5)), "H244:H255") Then 'Table 1.2b

    With ActiveWorkbook.Sheets("1.2")
    If ValidateTableIntegrity(.Range("D44:G44,A45:A57"), False) Then
    If ValidateTableIntegrity(.Range("B44:C44,B55:C56,B57:G57,H45:H56"), True) Then
    If ValidateTableIntegrity(.Range("B60:G60,D64:G64,H61:H63"), True) Then
    If ValidateTableIntegrity(.Range("D66,D71,E67:E70"), True) Then
    If ValidateTableIntegrity(.Range("B72,D72:E72,G72,B73:B78,C79:G79,H73:H78"), True) Then
    If TableValidated(.Range(.Cells(45, 2), .Cells(56, 7)), "H256:H323", , .Range("B55:C56"), 54) Then 'Table 1.2c. Include the textual cells.
    If TotalValidated(.Range("D45:D55"), .Range("D56")) Then 'Does the Total cell equal to the summarized cells?
    If TotalValidated(.Range("E45:E55"), .Range("E56")) Then 'Does the Total cell equal to the summarized cells?
    If TotalValidated(.Range("F45:F55"), .Range("F56")) Then 'Does the Total cell equal to the summarized cells?
    If TotalValidated(.Range("G45:G55"), .Range("G56")) Then 'Does the Total cell equal to the summarized cells?

    With ActiveWorkbook.Sheets("1.3a")
    If ValidateTableIntegrity(.Range("C10:G10,B11:B30"), False) Then
    If ValidateTableIntegrity(.Range("C31:G31,H11:H30"), True) Then
    If ValidateTableIntegrity(.Range("C35:G35,B36:B51"), False) Then
    If ValidateTableIntegrity(.Range("C52:G52,H36:H51"), True) Then
    If ValidateTableIntegrity(.Range("A54:A55"), False) Then
    If ValidateTableIntegrity(.Range("B54:G54,B56:G56,H55"), True) Then
    If ValidateTableIntegrity(.Range("A57,B58:B61"), False) Then
    If ValidateTableIntegrity(.Range("B57:G57,D62:G62,H58:H61"), True) Then
    If ValidateTableIntegrity(.Range("A63,B63,E63,A64,A65"), False) Then
    If ValidateTableIntegrity(.Range("C63:D63,F63:G63,B66:G66,H64:H65"), True) Then
    If ValidateTableIntegrity(.Range("A77:F77"), False) Then
    If ValidateTableIntegrity(.Range("G77,A88:G88,H78:H87"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(30, 7)), "H404:H503", , , , False) Then
    If TableValidated(.Range(.Cells(36, 3), .Cells(51, 7)), "H504:H583") Then

    With ActiveWorkbook.Sheets("1.3b")
    If ValidateTableIntegrity(.Range("C11:I11,B12:B19"), False) Then
    If ValidateTableIntegrity(.Range("C20:I20,J12:J19"), True) Then
    If ValidateTableIntegrity(.Range("A22,A23"), False) Then
    If ValidateTableIntegrity(.Range("B22:I22,C24:I24,B23,J23"), True) Then
    If ValidateTableIntegrity(.Range("A25,C25,G25,A26:A29"), False) Then
    If ValidateTableIntegrity(.Range("B25,D25:F25,H25:I25,C30:I30,B26:B29,J26:J29"), True) Then
    If ValidateTableIntegrity(.Range("A41:F41"), False) Then
    If ValidateTableIntegrity(.Range("G41:I41,A52:I52,J42:J51"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(19, 9)), "H653:H708") Then

    With ActiveWorkbook.Sheets("1.4")
    If ValidateTableIntegrity(.Range("C11:G11,B12:B26"), False) Then
    If ValidateTableIntegrity(.Range("C27:G27,H12:H26"), True) Then
    If ValidateTableIntegrity(.Range("A29,B30:B32"), False) Then
    If ValidateTableIntegrity(.Range("B29:G29,E33:G33,H30:H32"), True) Then
    If ValidateTableIntegrity(.Range("A34,C34,F34,A36:A41,C40"), False) Then
    If ValidateTableIntegrity(.Range("B34,D34:E34,G34,C42:G42,B36:B41,H35:H41"), True) Then
    If ValidateTableIntegrity(.Range("A55,C55:G55"), False) Then
    If ValidateTableIntegrity(.Range("B55,A66:G66,H56:H65"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(26, 7)), "H778:H852") Then

    With ActiveWorkbook.Sheets("2.4")
    If ValidateTableIntegrity(.Range("C12:K12,B13:B24"), False) Then
    If ValidateTableIntegrity(.Range("C25:K25,L13:L24"), True) Then
    If ValidateTableIntegrity(.Range("A27:A31"), False) Then
    If ValidateTableIntegrity(.Range("B27:K27,C32:K32,L28:L30,F31:K31"), True) Then
    'If ValidateTableIntegrity(.Range("A33,C33,G33,A34:A41"), False) Then
    'If ValidateTableIntegrity(.Range("B33,D33:F33,H33:K33,A43:K43,L34:L42"), True) Then
    'If ValidateTableIntegrity(.Range("A60,C60,D60,F60,G60,I60"), False) Then
    'If ValidateTableIntegrity(.Range("B60,E60,H60,J60:K60,A71:K71,L61:L70"), True) Then
    Row42DeletedUnchanged blnRow42Deleted 'Define wheter Sheet 2.4 \ Row 42 is deleted or unchanged.
    If ValidateTableIntegrity(.Range(IIf(blnRow42Deleted, "A33:A41,C33,G33", "A33,C33,G33,A34:A41")), False) Then 'The validation ranges depend on whether Sheet 2.4 \ Row 42 is deleted or unchanged.
    If ValidateTableIntegrity(.Range(IIf(blnRow42Deleted, "B33:B41,D33:F33,H33:K33,A42:K42,L34:L41", "B33,D33:F33,H33:K33,A43:K43,L34:L42")), True) Then 'The validation ranges depend on whether Sheet 2.4 \ Row 42 is deleted or unchanged.
    If ValidateTableIntegrity(.Range(IIf(blnRow42Deleted, "A58:A59,C59:D59,F59:G59,I59", "A59:A60,C60:D60,F60:G60,I60")), False) Then 'The validation ranges depend on whether Sheet 2.4 \ Row 42 is deleted or unchanged.
    If ValidateTableIntegrity(.Range(IIf(blnRow42Deleted, "B59,E59,H59,J59:K59,A70:K70,L60:L69", "B60,E60,H60,J60:K60,A71:K71,L61:L70")), True) Then 'The validation ranges depend on whether Sheet 2.4 \ Row 42 is deleted or unchanged.
    If TableValidated(.Range(.Cells(13, 3), .Cells(24, 11)), "H931:H1038") Then 'Exclude the comment cells.

    With ActiveWorkbook.Sheets("3.1")
    If ValidateTableIntegrity(.Range("C11:G11,B12:B15"), False) Then
    If ValidateTableIntegrity(.Range("C16:G16,H12:H15"), True) Then
    If ValidateTableIntegrity(.Range("A18:A19"), False) Then
    If ValidateTableIntegrity(.Range("B18:G18,B20:G20,H19"), True) Then
    If ValidateTableIntegrity(.Range("A21,B21,E21,A22:A26"), False) Then
    If ValidateTableIntegrity(.Range("C21:D21,F21:G21,B27:G27,H22:H26"), True) Then
    If ValidateTableIntegrity(.Range("A74:F74"), False) Then
    If ValidateTableIntegrity(.Range("G74,A85:G85, H75:H84"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(15, 7)), "H1119:H1138") Then

    With ActiveWorkbook.Sheets("3.2")
    .Unprotect
    .Cells(38, 3).Locked = False 'The cell mistakenly locked that Roman pointed to.
    If ValidateTableIntegrity(.Range("C12:G12,B13:B62"), False) Then
    If ValidateTableIntegrity(.Range("C63:G63,H13:H62"), True) Then
    If ValidateTableIntegrity(.Range("A65:A68"), False) Then
    If ValidateTableIntegrity(.Range("B65:G65,D69:G69,H66:H68"), True) Then
    If ValidateTableIntegrity(.Range("A70:A75,C70,F70"), False) Then
    If ValidateTableIntegrity(.Range("D70:E70,G70,B70:B75,C76:G76,H71:H75"), True) Then
    If ValidateTableIntegrity(.Range("A88,C88:G88"), False) Then
    If ValidateTableIntegrity(.Range("B88,A99:G99,H89:H98"), True) Then
    If TableValidated(.Range(.Cells(13, 3), .Cells(62, 7)), "H1210:H1459") Then
    'KTB If TableValidated(.Range(.Cells(13, 3), .Cells(62, 7)), , .Cells(38, 3)) Then 'The cell mistakenly locked that Roman pointed to is a sort of authorised locking.
    'KTB If Not BlankCell(.Cells(38, 3)) Then 'The cell mistakenly locked that Roman pointed to.

    With ActiveWorkbook.Sheets("3.3")
    If ValidateTableIntegrity(.Range("E10:G10,A11:A24"), False) Then
    If ValidateTableIntegrity(.Range("B10:D10,H10,C21:F23,H21:H23,I11:I20"), True) Then
    If ValidateTableIntegrity(.Range("A27:A40,C27,F27"), False) Then
    If ValidateTableIntegrity(.Range("B27,D27:E27,G27:H27,B40:H40,B38:B39,I28:I39"), True) Then
    If ValidateTableIntegrity(.Range("A77,C77:G77"), False) Then
    If ValidateTableIntegrity(.Range("B77,H77,A88:H88,I78:I87"), True) Then
    If TableValidated(.Range(.Cells(11, 2), .Cells(23, 8)), "H1533:H1605", , .Range("B21:F23,H21:H23"), 20, False) Then 'Include the textual cells.
    If TotalValidated(.Range("G11:G22"), .Range("G23")) Then 'Does the Total cell equal to the summarized cells?

    With ActiveWorkbook.Sheets("3.4")
    If ValidateTableIntegrity(.Range("D10:E10,B21,A11:A20,A22,A23"), False) Then
    If ValidateTableIntegrity(.Range("A10:C10,F10,A21,C21:D22,B22,F21:F22,B23:F23,G11:G20"), True) Then
    If ValidateTableIntegrity(.Range("A25:A26"), False) Then
    If ValidateTableIntegrity(.Range("B25:G25,D27:G27,H26"), True) Then
    If ValidateTableIntegrity(.Range("A28:A29,C28,F28,A34"), False) Then
    If ValidateTableIntegrity(.Range("B28:B29,D28:E28,G28,B34:G34,H29:H33"), True) Then
    If ValidateTableIntegrity(.Range("A70,C70:G70"), False) Then
    If ValidateTableIntegrity(.Range("B70,A81:G81,H71:H80"), True) Then
    If TableValidated(.Range(.Cells(11, 2), .Cells(22, 6)), "H1700:H1751", , .Range("B21:D22,F21:F22"), 20, False) Then 'Include the textual cells.
    If TotalValidated(.Range("E11:E21"), .Range("E22")) Then 'Does the Total cell equal to the summarized cells?

    With ActiveWorkbook.Sheets("3.5")
    If ValidateTableIntegrity(.Range("D11:F11,C12:C25"), False) Then
    If ValidateTableIntegrity(.Range("D26:F26,G12:G25"), True) Then
    If ValidateTableIntegrity(.Range("C30,A31:A33"), False) Then
    If ValidateTableIntegrity(.Range("A30:B30,D30,B31:B33,E31:E33,A34:D34"), True) Then
    If ValidateTableIntegrity(.Range("B36,F36,B39"), False) Then
    If ValidateTableIntegrity(.Range("C36:E36,G36,C41:G41,C37:C40,H37:H40"), True) Then
    If ValidateTableIntegrity(.Range("A61,C61:G61"), False) Then
    If ValidateTableIntegrity(.Range("B61,A72:G72,H62:H71"), True) Then
    If TableValidated(.Range(.Cells(12, 4), .Cells(25, 6)), "H1827:H1868", , , , False) Then 'Table 3.5a
    If TableValidated(.Range(.Cells(31, 3), .Cells(33, 3)), "H1869:H1871") Then 'Table 3.5b because of merged column 4 that originally remained unlocked.

    With ActiveWorkbook.Sheets("4.1")
    If ValidateTableIntegrity(.Range("C10:F10,B11:B22"), False) Then
    If ValidateTableIntegrity(.Range("C23:F23,G11:G22"), True) Then
    If ValidateTableIntegrity(.Range("A25:A27"), False) Then
    If ValidateTableIntegrity(.Range("B25:F25,B28:F28,G26:G27"), True) Then
    If ValidateTableIntegrity(.Range("A29,B29,E29,A30:A33"), False) Then
    If ValidateTableIntegrity(.Range("C29,F29,B34:F34,G30:G33"), True) Then
    If ValidateTableIntegrity(.Range("A44:F44"), False) Then
    If ValidateTableIntegrity(.Range("A55:F55,G45:G54"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(22, 6)), "H1938:H1985") Then

    With ActiveWorkbook.Sheets("4.2")
    If ValidateTableIntegrity(.Range("C11:E11,B12:B15"), False) Then
    If ValidateTableIntegrity(.Range("C16:E16,F12:F15"), True) Then
    If ValidateTableIntegrity(.Range("C21:G21,B22:B25"), False) Then
    If ValidateTableIntegrity(.Range("C26:G26,H22:H25"), True) Then
    If ValidateTableIntegrity(.Range("A28:A35,B28,F28,B30:B32"), False) Then
    If ValidateTableIntegrity(.Range("C28:E28,G28,C30:C32,B36:G36,H29:H35"), True) Then
    If ValidateTableIntegrity(.Range("A54:F54"), False) Then
    If ValidateTableIntegrity(.Range("G54,A65:G65,H55:H64"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(15, 5)), "H2056:H2067", , , , False) Then
    If TableValidated(.Range(.Cells(22, 3), .Cells(25, 7)), "H2068:H2087") Then

    With ActiveWorkbook.Sheets("4.3")
    If ValidateTableIntegrity(.Range("C10:E10,B11:B25,A26"), False) Then
    If ValidateTableIntegrity(.Range("B26:E26,F11:F25"), True) Then
    If ValidateTableIntegrity(.Range("A29,B30:B32"), False) Then
    If ValidateTableIntegrity(.Range("B29:F29,D33:F33,G30:G32"), True) Then
    If ValidateTableIntegrity(.Range("A34:A36"), False) Then
    If ValidateTableIntegrity(.Range("B34:F34,A37:F37,G35:G36"), True) Then
    If ValidateTableIntegrity(.Range("A38:A41,B38,E38"), False) Then
    If ValidateTableIntegrity(.Range("C38:D38,F38,A42:F42,G39:G41"), True) Then
    If ValidateTableIntegrity(.Range("A51:F51"), False) Then
    If ValidateTableIntegrity(.Range("A62:F62,G52:G61"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(25, 5)), "H2162:H2206") Then

    With ActiveWorkbook.Sheets("4.4")
    If ValidateTableIntegrity(.Range("C10:D10,B11:B23"), False) Then
    If ValidateTableIntegrity(.Range("C24:D24,E11:E23"), True) Then
    If ValidateTableIntegrity(.Range("C28:D28"), False) Then
    If ValidateTableIntegrity(.Range("A28:B28,A36:D36,E29:E35"), True) Then
    If ValidateTableIntegrity(.Range("A38,C40:D40"), False) Then
    If ValidateTableIntegrity(.Range("A48:D48,E41:E47"), True) Then
    If ValidateTableIntegrity(.Range("A50,B51:B53"), False) Then
    If ValidateTableIntegrity(.Range("B50:F50,A54:F54,G51:G53"), True) Then
    If ValidateTableIntegrity(.Range("A55:A58"), False) Then
    If ValidateTableIntegrity(.Range("B55:F55,A59:F59,G56:G58"), True) Then
    If ValidateTableIntegrity(.Range("A60:A64,B60,E60"), False) Then
    If ValidateTableIntegrity(.Range("C60:D60,F60,A65:F65,G61:G64"), True) Then
    If ValidateTableIntegrity(.Range("A77:F77"), False) Then
    If ValidateTableIntegrity(.Range("A88:F88,G78:G87"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(23, 4)), "H2278:H2303", , , , False) Then 'Table 4.4a
    If TableValidated(.Range("A29:D35"), "H2304:H2327", , LockMergedCells(.Range("A29:C35"), .Range("B29:B35")), 35, False) Then 'Include the textual cells w/o the hidden merged cells in Table 4.4b.
    If TableValidated(.Range("A41:D47"), "H2328:H2348", , LockMergedCells(.Range("A41:C47"), .Range("B41:B47")), 47) Then 'Include the textual cells w/o the hidden merged cells in Table 4.4c.

    With ActiveWorkbook.Sheets("4.5")
    If ValidateTableIntegrity(.Range("C10:E10,B11:B22,B24:B25,A23"), False) Then
    If ValidateTableIntegrity(.Range("B23:E23,A26:E26,F11:F25"), True) Then
    If ValidateTableIntegrity(.Range("A28:A30,B30:B34"), False) Then
    If ValidateTableIntegrity(.Range("C28:D34,B29,B28,E28,F30:F34,A35:E35"), True) Then
    If ValidateTableIntegrity(.Range("A36:A38,B36,E36"), False) Then
    If ValidateTableIntegrity(.Range("C36:D36,F36,A39:F39,G37:G38"), True) Then
    If ValidateTableIntegrity(.Range("A50:F50"), False) Then
    If ValidateTableIntegrity(.Range("A61:F61,G51:G60"), True) Then
'    If TableValidated(.Range(.Cells(11, 3), .Cells(22, 5)), , , , False) Then
'    If TableValidated(.Range(.Cells(24, 3), .Cells(25, 5))) Then
    If TableValidated(.Range("C11:E22,C24:E25"), "H2423:H2464") Then

    With ActiveWorkbook.Sheets("4.8")
    If ValidateTableIntegrity(.Range("C11:G11,B12:B39"), False) Then
    If ValidateTableIntegrity(.Range("C40:G40,H12:H39"), True) Then
    If ValidateTableIntegrity(.Range("A42:A44"), False) Then
    If ValidateTableIntegrity(.Range("B42:G42,A45:G45,H43:H44"), True) Then
    If ValidateTableIntegrity(.Range("A46:A54,C46,F46"), False) Then
    If ValidateTableIntegrity(.Range("B46:B54,A55:G55,H47:H54"), True) Then
    If ValidateTableIntegrity(.Range("A64:F64"), False) Then
    If ValidateTableIntegrity(.Range("G64,A75:G75,H65:H74"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(39, 7)), "H2535:H2674") Then

    With ActiveWorkbook.Sheets("4.9")
    If ValidateTableIntegrity(.Range("C11:F11,B12:B26"), False) Then
    If ValidateTableIntegrity(.Range("C27:F27,G12:G26"), True) Then
    If ValidateTableIntegrity(.Range("A29:A30,B30:B32"), False) Then
    If ValidateTableIntegrity(.Range("B29:F29,A31:A32,A33:F33,G30:G32"), True) Then
    If ValidateTableIntegrity(.Range("A34:A40,B34,E34"), False) Then
    If ValidateTableIntegrity(.Range("C34:D34,F34,B36:F36,A42:F42,G35:G41"), True) Then
    If ValidateTableIntegrity(.Range("A51:F51"), False) Then
    If ValidateTableIntegrity(.Range("A62:F62,G52:G61"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(26, 6)), "H2753:H2812") Then

    With ActiveWorkbook.Sheets("5")
    If ValidateTableIntegrity(.Range("C13:E13,B14:B28"), False) Then
    If ValidateTableIntegrity(.Range("C29:E29,F14:F28"), True) Then
    If ValidateTableIntegrity(.Range("A31:A32,B32:B34"), False) Then
    If ValidateTableIntegrity(.Range("B31:F31,C32:C34,A35:F35,A33:A34,G32:G34"), True) Then
    If ValidateTableIntegrity(.Range("A36:A40,B36,E36"), False) Then
    'If ValidateTableIntegrity(.Range("B38:F38,A41:F41,G37:G40"), True) Then
    If ValidateTableIntegrity(.Range("B38:F38,A41,G37:G40"), True) Then 'B41:F41 is erroneously unlocked.
    If ValidateTableIntegrity(.Range("A51:F51"), False) Then
    If ValidateTableIntegrity(.Range("A62:F62,G52:G61"), True) Then
    If TableValidated(.Range(.Cells(14, 3), .Cells(28, 5)), "H2889:H2933") Then

    With ActiveWorkbook.Sheets("6.1")
    If ValidateTableIntegrity(.Range("C11:J11,B12:B23"), False) Then
    If ValidateTableIntegrity(.Range("C24:J24,K12:K23"), True) Then
    If ValidateTableIntegrity(.Range("A25:A26"), False) Then
    If ValidateTableIntegrity(.Range("B25:E25,A27:E27,F26"), True) Then
    If ValidateTableIntegrity(.Range("A41:C41,E41:F41,H41"), False) Then
    If ValidateTableIntegrity(.Range("D41,G41,I41:J41,A52:J52,K42:K51"), True) Then
    If TableValidated(.Range(.Cells(12, 3), .Cells(23, 10)), "H3003:H3098") Then 'Exclude the comment cells.

    With ActiveWorkbook.Sheets("6.2")
    If ValidateTableIntegrity(.Range("C10:D10,B11:B22"), False) Then
    If ValidateTableIntegrity(.Range("C23:D23,E11:E22"), True) Then
    If ValidateTableIntegrity(.Range("A25:A29,B25,D25"), False) Then
    If ValidateTableIntegrity(.Range("C25,E25,A30:E30,F26:F29"), True) Then

'    If ValidateTableIntegrity(.Range("A54:E54"), False) Then
'    If ValidateTableIntegrity(.Range("A65:E65,F55:F64"), True) Then
    If ValidateTableIntegrity(.Range(IIf(blnRow42Deleted, "A56:E56,A55", "A54:E54,A53")), False) Then 'The validation ranges depend on whether Sheet 2.4 \ Row 42 is deleted or unchanged.
    If ValidateTableIntegrity(.Range(IIf(blnRow42Deleted, "A67:E67,F57:F66", "A65:E65,F55:F64")), True) Then 'The validation ranges depend on whether Sheet 2.4 \ Row 42 is deleted or unchanged.
    If TableValidated(.Range(.Cells(11, 3), .Cells(22, 4)), "H3166:H3189") Then

    With ActiveWorkbook.Sheets("6.3")
    If ValidateTableIntegrity(.Range("C10:D10,B11:B14"), False) Then
    If ValidateTableIntegrity(.Range("C15:D15,E11:E14"), True) Then
    If ValidateTableIntegrity(.Range("A17:A20,B17,D17"), False) Then
    If ValidateTableIntegrity(.Range("A21:D21,E18:E20"), True) Then
    If ValidateTableIntegrity(.Range("A37:E37"), False) Then
    If ValidateTableIntegrity(.Range("A48:E48,F38:F47"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(14, 4)), "H3248:H3255") Then

    With ActiveWorkbook.Sheets("6.4")
    If ValidateTableIntegrity(.Range("C9,B10:B37"), False) Then
    If ValidateTableIntegrity(.Range("C38,D37,D10:D37"), True) Then
    If ValidateTableIntegrity(.Range("A40:A46,C40,E40"), False) Then
    If ValidateTableIntegrity(.Range("B40:B46,A47:E47,F41:F46"), True) Then
    If ValidateTableIntegrity(.Range("A65:E65"), False) Then
    If ValidateTableIntegrity(.Range("A76:E76,F66:F75"), True) Then
    If TableValidated(.Range(.Cells(10, 3), .Cells(37, 3)), "H3312:H3339") Then

    With ActiveWorkbook.Sheets("6.5")
    If ValidateTableIntegrity(.Range("C10:G10,B11:B22"), False) Then
    If ValidateTableIntegrity(.Range("C23:G23,H11:H22"), True) Then
    If ValidateTableIntegrity(.Range("C27:G27,B28:B39"), False) Then
    If ValidateTableIntegrity(.Range("C40:G40,H28:H39"), True) Then
    If ValidateTableIntegrity(.Range("A41:A43"), False) Then
    If ValidateTableIntegrity(.Range("B41:G41,B44:G44,B42:B43,H42:H43"), True) Then
    If ValidateTableIntegrity(.Range("A45:A51,B45,E45"), False) Then
    If ValidateTableIntegrity(.Range("C45:D45,F45:G45,A52:G52,H46:H51"), True) Then
    If ValidateTableIntegrity(.Range("A68:C68,E68:F68"), False) Then
    If ValidateTableIntegrity(.Range("D68,G68,A79:G79,H69:H78"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(22, 7)), "H3402:H3461", , , , False) Then
    If TableValidated(.Range(.Cells(28, 3), .Cells(39, 7)), "H3462:H3521") Then

    With ActiveWorkbook.Sheets("6.6")
    If ValidateTableIntegrity(.Range("C10:F10,B11:B14"), False) Then
    If ValidateTableIntegrity(.Range("C15:F15,G11:G14"), True) Then
    If ValidateTableIntegrity(.Range("A16:A17"), False) Then
    If ValidateTableIntegrity(.Range("B16:D16,B18:D18,B17:C17,E17"), True) Then
    If ValidateTableIntegrity(.Range("A19:A24,C19,E19"), False) Then
    If ValidateTableIntegrity(.Range("B19:B24,D19,F19,A25:F25,G20:G24"), True) Then
    If ValidateTableIntegrity(.Range("A40:E40"), False) Then
    If ValidateTableIntegrity(.Range("F40,A51:F51,G41:G50"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(14, 6)), "H3586:H3601") Then 'Exclude the comment cells.

    With ActiveWorkbook.Sheets("6.9")
    If ValidateTableIntegrity(.Range("C10:H10,A11:A22,B15,B17"), False) Then
    If ValidateTableIntegrity(.Range("B11:B14,B18:B22,A23:H23,I11:I22"), True) Then
    If ValidateTableIntegrity(.Range("A24:A27"), False) Then
    If ValidateTableIntegrity(.Range("B25:H25,A28:H28,B26:B27,I26:I27"), True) Then
    If ValidateTableIntegrity(.Range("A29:B29,E29,A30"), False) Then
    If ValidateTableIntegrity(.Range("C29:D29,F29:H29,A31:H31,I30"), True) Then
    If ValidateTableIntegrity(.Range("A42:C42,E42:G42,A53"), False) Then
    If ValidateTableIntegrity(.Range("D42,H42,B53:H53,I43:I52"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(22, 8)), "H3663:H3725", , .Range("D11:D12,F11:F12,H11:H12,C20,E20,G20")) Then

    With ActiveWorkbook.Sheets("6.10")
    If ValidateTableIntegrity(.Range("C10:F10,B11:B14"), False) Then
    If ValidateTableIntegrity(.Range("C15:F15,G11:G14"), True) Then
    If ValidateTableIntegrity(.Range("C18:D18,A19"), False) Then
    If ValidateTableIntegrity(.Range("B19,C20:D20,E19"), True) Then
    If ValidateTableIntegrity(.Range("A22:A24"), False) Then
    If ValidateTableIntegrity(.Range("B22:F22,A25:F25,G23:G24"), True) Then
    If ValidateTableIntegrity(.Range("A26:A29,C26,E26"), False) Then
    If ValidateTableIntegrity(.Range("B26:B29,D26,F26,A30:F30,G27:G29"), True) Then
    If ValidateTableIntegrity(.Range("A42:E42"), False) Then
    If ValidateTableIntegrity(.Range("F42,A53:F53,G43:G52"), True) Then
    If TableValidated(.Range(.Cells(11, 3), .Cells(14, 6)), "H3790:H3805", , , , False) Then
    If TableValidated(.Range(.Cells(19, 3), .Cells(19, 4)), "H3806:H3807") Then

    With ActiveWorkbook.Sheets("6.11")
    If ValidateTableIntegrity(.Range("C11:G11,A12"), False) Then
    If ValidateTableIntegrity(.Range("B11,B13:G13,H12"), True) Then
    If ValidateTableIntegrity(.Range("A15:A20,D15"), False) Then
    If ValidateTableIntegrity(.Range("B15:C20,A21:G21,H16:H20"), True) Then
    If ValidateTableIntegrity(.Range("A37:F37"), False) Then
    If ValidateTableIntegrity(.Range("G37,A48:G48,H38:H47"), True) Then
    If TableValidated(.Range(.Cells(12, 2), .Cells(12, 7)), "H3866:H3871") Then 'Exclude the comment cells.

        If ValidateSharps Then MsgBox "Blank cells validated!", vbInformation 'Make sure there are no sharp signs that show errors.

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    'End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    'End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End If
    End With

End Sub

Private Sub EnterYesNo(ByVal strSheet As String, ByVal lngRow As Long, ByVal lngCol As Long) 'Enter Yes/No.
    Const strYes As String = "Yes", strNo As String = "No"
    With ActiveWorkbook.Sheets(strSheet)
        .Select
        .Unprotect 'Unprotect the sheet to enable entering locked cells.
        .Cells(lngRow, 1).Select 'Make the first column visible.
        With .Cells(lngRow, lngCol)
            .Select 'Show the entered cell.
            Select Case MsgBox("Choose Yes or No?", vbYesNoCancel + vbQuestion) 'Fill it in.
                Case vbYes
                    .Value = strYes
                Case vbNo
                    .Value = strNo
            End Select
        End With
    End With
End Sub

Private Sub CheckUncheck(ByVal lngRow As Long) 'Check/uncheck.
    Const strChecked As String = "Checked", strUnchecked As String = "Unchecked"
    Const lngColChecked As Long = 7
    With ActiveWorkbook.Sheets("1.1")
        With .Cells(lngRow, lngColChecked)
            .Select 'Show the entered cell.
            If MsgBox("Checked cell?", vbYesNoCancel + vbQuestion) = vbYes Then .Value = strChecked 'Fill it in.
            'If MsgBox("Cell will be checked!", vbOKCancel) = vbOK Then .Value = strChecked 'Fill it in.
        End With
    End With
End Sub

Private Sub MoveToDatabaseLeftUp() 'Deselect the selection and move the pointer to the left upper corner.
    With ActiveWorkbook.Sheets("Database")
        .Select
        .Range("A3:A183").Select
    End With
End Sub

Private Sub PrepareSheet1_1() 'Prepare Sheet 1.1
    Const strChecksDatabase As String = "L48:L73", strChecks1_1 As String = "G55", strChecks1_1Col1 As String = "A55"
    With ActiveWorkbook.Sheets("1.1")
        .Unprotect 'Unprotect the sheet to enable entering locked cells.
        .Select
        .Range(strChecks1_1Col1).Select 'Make the first column visible.
        .Range(strChecks1_1).Select
    End With
    If MsgBox("Paste checkes?", vbYesNoCancel + vbQuestion) = vbYes Then 'Confirm pasting.
        With ActiveWorkbook.Sheets("Database")
            .Select 'Copy/paste the checks.
            '.Range("L48:L73").Select
            .Range(strChecksDatabase).Select
            Selection.Copy
        End With
        With ActiveWorkbook.Sheets("1.1")
            .Select
            .Range(strChecks1_1).Select
            Selection.PasteSpecial Paste:=xlPasteValues, Operation:=xlNone, SkipBlanks:=False, Transpose:=False
            MoveToDatabaseLeftUp 'Deselect the selection in Database and move the pointer to the left upper corner.
            .Select
        End With
        CheckUncheck 58 'Check/uncheck the pasted cells.
        CheckUncheck 59
        CheckUncheck 60
        CheckUncheck 61
        CheckUncheck 63
        CheckUncheck 64
        CheckUncheck 65
        CheckUncheck 66
        CheckUncheck 67
        CheckUncheck 68
        CheckUncheck 69
        CheckUncheck 71
        CheckUncheck 72
        CheckUncheck 73
        CheckUncheck 75
        CheckUncheck 76
        CheckUncheck 77
        CheckUncheck 78
        CheckUncheck 79
        CheckUncheck 80
    End If
End Sub

Private Function ShiftDataSourcesFormulas() As Boolean 'Shift the Data Sources formulas for Sheet 2.4 \ Row 42 deleted.
    With ActiveWorkbook.Sheets("Database")
        .Select
        .Unprotect 'Unprotect the sheet to enable entering locked cells.
        .Range("L1059").Select
        .Range(Selection, Selection.End(xlDown)).Select
        Selection.Copy
        If MsgBox("Replace the formulas?", vbYesNoCancel + vbQuestion) = vbYes Then
            .Range("H1059").Select
            .Paste
            ShiftDataSourcesFormulas = True
        End If
        .Protect 'Protect the sheet.
    End With
End Function

Private Sub Row42DeletedUnchanged(blnRow42Deleted As Boolean, Optional blnRow42Unchanged As Boolean = False) 'Define wheter Sheet 2.4 \ Row 42 is deleted or unchanged.
    Const strUnspecifiedMixedDamage As String = "Unspecified / Mixed damage", strReportingNotes As String = "Reporting notes:"
    Const strUnspecifiedMixedDamageRus As String = "Неустановленное / Смешанное повреждение", strReportingNotesRus As String = "Примечания к отчёту:"
    Const strA43 As String = "A43"
    With ActiveWorkbook.Sheets("2.4")
        If .Range(mstrA41).Value = strUnspecifiedMixedDamage Or .Range(mstrA41).Value = strUnspecifiedMixedDamageRus Then 'Checking the integrity of the range around the questionable row 42.
            If Not .Range(mstrA42).Locked Then 'Unlocked cell i.e. data entry cell?
                If Trim$(.Range(mstrA44).Value) = strReportingNotes Or Trim$(.Range(mstrA44).Value) = strReportingNotesRus Then blnRow42Unchanged = True 'Isn't Row 42 deleted?'Row 42 isn't deleted.
            ElseIf .Range(mstrA42).Locked Then 'Loked cell i.e. not a data entry cell?
                If Trim$(.Range(strA43).Value) = strReportingNotes Or Trim$(.Range(strA43).Value) = strReportingNotesRus Then 'Is Row 42 deleted?
                    blnRow42Deleted = True 'Row 42 is deleted.
                End If
            End If
        End If
    End With
End Sub

Private Function AdjustFor24_42() As Boolean 'Adjust the formulas for Sheet 2.4 \ Row 42.
    Dim blnRow42Deleted As Boolean, blnRow42Unchanged As Boolean
    Row42DeletedUnchanged blnRow42Deleted, blnRow42Unchanged 'Define wheter Sheet 2.4 \ Row 42 is deleted or unchanged.
    With ActiveWorkbook.Sheets("2.4")
        If blnRow42Deleted Then 'Is Row 42 deleted?
            .Select
            .Range(mstrA42).Select
            If MsgBox("Row 42 deleted! Adjusted the formulas for it?", vbYesNoCancel + vbQuestion) = vbYes Then AdjustFor24_42 = ShiftDataSourcesFormulas 'Shift the Data Sources formulas for Sheet 2.4 \ Row 42 deleted.
        Else
            AdjustFor24_42 = True 'No deletion no adjustment therefore return True.
        End If
        If Not blnRow42Deleted Xor blnRow42Unchanged Then 'An unexpected case to be checked for additional robustness.
            AdjustFor24_42 = False 'Return False.
            .Select
            .Range(.Range(mstrA41), .Range(mstrA44)).Select
            MsgBox "An unauthorised changed revealed in " & mstrA42 & ":" & mstrA44 & "!", vbCritical
        End If
    End With
End Function

Private Function Link(ByVal strFormula As String) As String 'Get the link.
    Const strGeneralB13 As String = "General'!B13", strEquationApostrophe As String = "='"
    Dim intLinkBeg As Integer, intLinkEnd As Integer
    If strFormula <> strEquationApostrophe & strGeneralB13 Then
        intLinkBeg = InStr(1, strFormula, strEquationApostrophe) + 1 'The beginning of the link i.e. after the equation sign.
        intLinkEnd = InStr(1, strFormula, strGeneralB13) 'The end of the link i.e. before the General sheet name.
        If intLinkBeg < intLinkEnd Then Link = Mid$(strFormula, intLinkBeg + 1, intLinkEnd - intLinkBeg - 1) 'Isn't it the same position?
    End If
End Function

Private Sub FindReplace(ByVal strLink As String)
    Dim rngCell As Range
    For Each rngCell In ActiveWorkbook.Sheets("Database").Range(mstrFormulasData & "," & mstrFormulasRow24_42)
        rngCell.Formula = Replace(rngCell.Formula, strLink, vbNullString)
    Next
End Sub

Private Function RemoveLinks() As Boolean 'Remove the links. Return True, if removed.
    Const strCountryCell As String = "H2" 'The cell with the country.
    Dim strLink As String
    With ActiveWorkbook.Sheets("Database")
        .Select
        .Range(strCountryCell).Select 'Start replacing from the country cell.
        strLink = Link(Selection.Formula) 'Get the link.
        If strLink = vbNullString Then 'Is anything there?
            RemoveLinks = MsgBox("No link removal required! Check the current formula?" & vbCrLf & Selection.Formula, vbYesNoCancel + vbQuestion) <> vbYes
        Else
            If MsgBox("Remove " & strLink & "?", vbYesNoCancel + vbQuestion) = vbYes Then
                .Unprotect
                FindReplace strLink
                .Protect
                 RemoveLinks = MsgBox("External links removed! Continue?", vbYesNoCancel + vbQuestion) = vbYes 'Suggest to continue or view the chages.
            End If
        End If
    End With
    If RemoveLinks Then MoveToDatabaseLeftUp 'Deselect the selection and move the pointer to the left upper corner, if succeeded.
End Function

Private Function ValidateSharps() 'Make sure there are no sharp signs that show errors.
    Const strSharp As String = "#"
    Dim rngCell As Range
    Dim strValueFormula As String
    ValidateSharps = True
    For Each rngCell In ActiveWorkbook.Sheets("Database").Range(mstrFormulasData & "," & mstrFormulasRow24_42)
        With rngCell
            strValueFormula = .Text & .Formula 'Check both values and formulas.
            If InStr(strValueFormula, strSharp) > 0 Then
                .Parent.Select
                .Select
                If MsgBox("A sharp sign found! Continue?", vbYesNoCancel + vbCritical) <> vbYes Then
                    ValidateSharps = False
                    Exit For
                End If
            End If
        End With
    Next
End Function

Public Sub PrepareDatabase()
Attribute PrepareDatabase.VB_ProcData.VB_Invoke_Func = " \n14"
    If MsgBox("Start preparing the database?", vbYesNoCancel + vbQuestion) = vbYes Then
        If RemoveLinks Then 'Removing the links succeeded?
            EnterYesNo "1.2", 66, 5 'Enter Yes/No.
            EnterYesNo "2.4", 31, 12 'Enter Yes/No.
            EnterYesNo "4.5", 29, 6 'Enter Yes/No.
            PrepareSheet1_1 'Prepare Sheet 1.1
            If AdjustFor24_42 Then 'Adjust the formulas for Sheet 2.4 \ Row 42.
                ActiveWorkbook.Sheets("Database").Select
                If MsgBox("Database preparation finished! Start its validation?", vbYesNoCancel + vbQuestion) = vbYes Then FindBlankCells
            End If
        End If
    End If
End Sub

Public Sub ProtectionSheetsOn()
    Dim objSheet
    For Each objSheet In ActiveWorkbook.Sheets
        objSheet.Protect
    Next
End Sub

Public Sub ProtectionSheetsOff()
    Dim objSheet
    For Each objSheet In ActiveWorkbook.Sheets
        objSheet.Unprotect
    Next
End Sub

Public Sub ColumnWidth()
    Const intColumnFirstDefault As Integer = 2 'The default first column.
    Const intColumnLastDefault As Integer = 350 'The default last column.
    Const dblWidthDefault As Double = 10 'The default width
    Dim objSheet
    Dim I As Integer, intColumnFirst As Integer, intColumnLast As Integer
    Dim dblWidth As Double
    intColumnFirst = Int(InputBox("Adjust columns from:", , intColumnFirstDefault))
    If intColumnFirst > 0 Then 'Value entered?
        intColumnLast = Int(InputBox("Adjust columns to:", , intColumnLastDefault))
        dblWidth = Val(InputBox("Adjust width to:", , dblWidthDefault))
        If dblWidth > 0 Then 'Value entered?
            For Each objSheet In ActiveWorkbook.Sheets
                With objSheet
                    .Unprotect
                    For I = intColumnFirst To intColumnLast
                        .Columns(I).ColumnWidth = dblWidth
                    Next
                End With
            Next
        End If
    End If
End Sub

Public Sub HeadingsHide() 'Hide the headings on all sheets.
    Dim objSheet, objSheetCurrent
    Set objSheetCurrent = ActiveWorkbook.ActiveSheet 'Remember the current sheet to return to it in the end.
    For Each objSheet In ActiveWorkbook.Sheets 'Hide the headings on all sheets.
        If objSheet.Visible = xlSheetVisible Then 'Only if visible.
            objSheet.Select
            ActiveWindow.DisplayHeadings = False
        End If
    Next
    objSheetCurrent.Select 'Return to the current sheet.
End Sub

Public Sub HeadingsUnhide() 'Unhide the headings on all sheets.
    Dim objSheet, objSheetCurrent
    Set objSheetCurrent = ActiveWorkbook.ActiveSheet 'Remember the current sheet to return to it in the end.
    For Each objSheet In ActiveWorkbook.Sheets 'Hide the headings on all sheets.
        If objSheet.Visible = xlSheetVisible Then 'Only if visible.
            objSheet.Select
            ActiveWindow.DisplayHeadings = True
        End If
    Next
    objSheetCurrent.Select 'Return to the current sheet.
End Sub

Public Sub Zoom() 'Zoom all sheets.
    Const intZoomMin As Integer = 10, intZoomMax As Integer = 400, intZoomDefault As Integer = 100
    Dim objSheet, objSheetCurrent
    Dim intZoom As Integer
    Set objSheetCurrent = ActiveWorkbook.ActiveSheet 'Remember the current sheet to return to it in the end.
    intZoom = Int(InputBox("Per cent to zoom in/out (" & intZoomMin & " - " & intZoomMax & "%):", "Zoom", intZoomDefault))
    If intZoom >= intZoomMin And intZoom <= intZoomMax Then 'Relevant per cent?
        For Each objSheet In ActiveWorkbook.Sheets 'Hide the headings on all sheets.
            If objSheet.Visible = xlSheetVisible Then 'Only if visible.
                objSheet.Select
                ActiveWindow.Zoom = intZoom
            End If
        Next
        objSheetCurrent.Select 'Return to the current sheet.
    End If
End Sub

Private Function ExctractFormulaLocal(ByVal strFormula As String, ByVal strFormulaLocal As String) 'Extract the formula w/o the equation sign.
    Dim intEquationAndSpaces As Integer
    For intEquationAndSpaces = 2 To Len(strFormula) 'Define how many spaces there are after the eqation sign.
        If Mid(strFormula, intEquationAndSpaces, 1) <> Space(1) Then Exit For
    Next
    ExctractFormulaLocal = Mid(strFormulaLocal, intEquationAndSpaces) 'Extract the formula w/o the equation sign.
End Function

Public Sub PrefixAffixFormulas() 'Prefix/affix formulas of the selected cells.
    Const strPrefixDefault As String = "= IFERROR("
    Dim strAffixDefault As String, strPrefix As String, strAffix As String
    Dim rngCell As Range
    Dim intEquationAndSpaces As Integer
    Dim lngCounter As Long
    strAffixDefault = ";" & Space(1) & """-"")" 'Compile a default affix with a space (Chr(32)).
    strPrefix = InputBox("Prefix:", "Prefix/affix selected cells' formulas", GetSetting("OutputTables", "PrefixAffixFormulas", "Prefix", strPrefixDefault))
    If strPrefix <> vbNullString Then 'Not canceled?
        strAffix = InputBox("Affix:", "Prefix/affix selected cells' formulas", GetSetting("OutputTables", "PrefixAffixFormulas", "Affix", strAffixDefault))
        If strAffix <> vbNullString Then 'Not canceled?
            For Each rngCell In ActiveWindow.Selection
                With rngCell
                    If .HasFormula Then 'Has formula?
                        lngCounter = lngCounter + 1
                        .FormulaLocal = strPrefix & ExctractFormulaLocal(.Formula, .FormulaLocal) & strAffix
                    End If
                End With
            Next
            SaveSetting "OutputTables", "PrefixAffixFormulas", "Prefix", strPrefix
            SaveSetting "OutputTables", "PrefixAffixFormulas", "Affix", strAffix
            MsgBox lngCounter & " formula(s) adjusted!", vbInformation
        End If
    End If
End Sub

Public Sub PrefixAffix2Formulas() 'Prefix/affix formulas of the selected cells.
Attribute PrefixAffix2Formulas.VB_ProcData.VB_Invoke_Func = " \n14"
    Const strPrefixDefault As String = "= IFERROR("
    Dim strAffixDefault As String, strPrefix As String, strAffix1 As String, strAffix2 As String
    Dim strFormulaLocal As String
    Dim rngCell As Range
    Dim lngCounter As Long
    Dim blnContinue As Boolean
    strAffixDefault = ";" & Space(1) & """-"")" 'Compile a default affix with a space (Chr(32)).
    strPrefix = InputBox("Prefix:", "Prefix/affix selected cells' formulas", GetSetting("OutputTables", "PrefixAffixFormulas", "Prefix", strPrefixDefault))
    If strPrefix <> vbNullString Then 'Not canceled?
        strAffix1 = InputBox("Affix 1:", "Prefix/affix selected cells' formulas", GetSetting("OutputTables", "PrefixAffixFormulas", "Affix1", strAffixDefault))
        If strAffix1 <> vbNullString Then 'Not canceled?
            strAffix2 = InputBox("Affix 2:", "Prefix/affix selected cells' formulas", GetSetting("OutputTables", "PrefixAffixFormulas", "Affix2", strAffixDefault))
            If strAffix2 <> vbNullString Then 'Not canceled?
                blnContinue = True
            ElseIf MsgBox("Continue without Affix 2?", vbYesNoCancel + vbQuestion) = vbYes Then 'Continue w/o Affix2?
                blnContinue = True
            End If
            If blnContinue Then
                For Each rngCell In ActiveWindow.Selection
                    With rngCell
                        If .HasFormula Then 'Has formula?
                            lngCounter = lngCounter + 1
                            strFormulaLocal = ExctractFormulaLocal(.Formula, .FormulaLocal) 'Extract the formula w/o the equation sign.
                            .FormulaLocal = strPrefix & strFormulaLocal & strAffix1 & strFormulaLocal & strAffix2
                        End If
                    End With
                Next
                SaveSetting "OutputTables", "PrefixAffixFormulas", "Prefix", strPrefix
                SaveSetting "OutputTables", "PrefixAffixFormulas", "Affix1", strAffix1
                SaveSetting "OutputTables", "PrefixAffixFormulas", "Affix2", strAffix2
                MsgBox lngCounter & " formula(s) adjusted!", vbInformation
            End If
        End If
    End If
End Sub

Private Function UnprotectSheet(objSheet) As Boolean 'Unprotect the sheet, if confirmed.
    If Not objSheet.ProtectContents Then
        UnprotectSheet = True
    ElseIf MsgBox("Sheet protected. Unprotect it?", vbYesNoCancel + vbQuestion) = vbYes Then
        ActiveSheet.Unprotect
        UnprotectSheet = True
    End If
End Function

Public Sub PrepareAnalysis()
Attribute PrepareAnalysis.VB_ProcData.VB_Invoke_Func = " \n14"
    Const strRussiaFormula As String = "Database!B8" 'A formula with Denmark in Database.
    Dim objSheetCurrent
    If MsgBox("Start preparing the sheet for availability analysis?", vbYesNoCancel + vbQuestion) = vbYes Then
        If Selection.Count > 1 Or InStr(1, Selection(1, 1).Formula, strRussiaFormula) = 0 Then 'Is the first country selected?
            'MsgBox "Select the cell with Russian Federation (i.e. the cell with a reference to ""Database!B8"")!", vbExclamation
            MsgBox "Select the cell with Russian Federation!", vbExclamation
        Else
            If UnprotectSheet(ActiveSheet) Then 'Unprotect the sheet, if confirmed.
                Range(Selection, Selection.End(xlToRight)).Select 'Insert 3 rows below each sub-region.
                With Selection.Interior
                    .Pattern = xlSolid
                    .PatternColorIndex = xlAutomatic
                    .ThemeColor = xlThemeColorAccent5
                    .TintAndShade = 0.799981688894314
                    .PatternTintAndShade = 0
                End With
                ActiveCell.Offset(9, 0).Range("A1").Select
                Range(Selection, Selection.End(xlToRight)).Select
                With Selection.Interior
                    .Pattern = xlSolid
                    .PatternColorIndex = xlAutomatic
                    .ThemeColor = xlThemeColorAccent5
                    .TintAndShade = 0.799981688894314
                    .PatternTintAndShade = 0
                End With
                ActiveCell.Offset(1, 0).Rows("1:3").EntireRow.Select
                Selection.Insert Shift:=xlDown, CopyOrigin:=xlFormatFromLeftOrAbove
                ActiveCell.Offset(13, 0).Range("A1").Select
                Range(Selection, Selection.End(xlToRight)).Select
                With Selection.Interior
                    .Pattern = xlSolid
                    .PatternColorIndex = xlAutomatic
                    .ThemeColor = xlThemeColorAccent5
                    .TintAndShade = 0.799981688894314
                    .PatternTintAndShade = 0
                End With
                ActiveCell.Offset(1, 0).Rows("1:3").EntireRow.Select
                Selection.Insert Shift:=xlDown, CopyOrigin:=xlFormatFromLeftOrAbove
                ActiveCell.Offset(12, 0).Range("A1").Select
                Range(Selection, Selection.End(xlToRight)).Select
                With Selection.Interior
                    .Pattern = xlSolid
                    .PatternColorIndex = xlAutomatic
                    .ThemeColor = xlThemeColorAccent5
                    .TintAndShade = 0.799981688894314
                    .PatternTintAndShade = 0
                End With
                ActiveCell.Offset(1, 0).Rows("1:3").EntireRow.Select
                Selection.Insert Shift:=xlDown, CopyOrigin:=xlFormatFromLeftOrAbove
                ActiveCell.Offset(10, 0).Range("A1").Select
                Range(Selection, Selection.End(xlToRight)).Select
                With Selection.Interior
                    .Pattern = xlSolid
                    .PatternColorIndex = xlAutomatic
                    .ThemeColor = xlThemeColorAccent5
                    .TintAndShade = 0.799981688894314
                    .PatternTintAndShade = 0
                End With
                ActiveCell.Offset(1, 0).Rows("1:3").EntireRow.Select
                Selection.Insert Shift:=xlDown, CopyOrigin:=xlFormatFromLeftOrAbove
                ActiveCell.Offset(14, 0).Range("A1").Select
                Range(Selection, Selection.End(xlToRight)).Select
                With Selection.Interior
                    .Pattern = xlSolid
                    .PatternColorIndex = xlAutomatic
                    .ThemeColor = xlThemeColorAccent5
                    .TintAndShade = 0.799981688894314
                    .PatternTintAndShade = 0
                End With
                ActiveCell.Offset(1, 0).Rows("1:3").EntireRow.Select
                Selection.Insert Shift:=xlDown, CopyOrigin:=xlFormatFromLeftOrAbove

                ActiveCell.Offset(-1, 0).Range("A1").Select 'Draw the borders of the bottom cells.
                Range(Selection, Selection.End(xlToRight)).Select
                Selection.Copy
                ActiveCell.Offset(1, 0).Range("A1:A3").Select
                ActiveSheet.Paste
                Application.CutCopyMode = False
                Selection.ClearContents

                ActiveWindow.FreezePanes = False 'Insert the sub-regional columns.
                Columns("A:A").Select 'Insert a blank column before.
                Selection.Insert Shift:=xlToRight, CopyOrigin:=xlFormatFromLeftOrAbove
                Set objSheetCurrent = ActiveWorkbook.ActiveSheet 'Remember the current sheet to return to it in the end.
                Sheets("A3.2 Trend 2010").Select
                Columns("A:C").Select
                Selection.Copy
                objSheetCurrent.Select 'Return to the current sheet.
                Columns("A:A").Select
                Selection.Insert Shift:=xlToRight 'Insert the sub-regional columns.
            End If
        End If
    End If
End Sub

Private Function AdjustTopRangeEdge(ByVal strFormulaR1C1 As String, ByVal intRowsUpRange As Integer) As String 'Adjust the top edge of a sub-regional edge.
    Const strBracketOpen As String = "R[", strBracketClose As String = "]C"
    Dim intPositionColonOrig As Integer, intPositionColon As Integer, intPositionBracketR As Integer, intPositionBracketClose As Integer
    Dim intStart As Integer
    Dim strColonEndedStringOrig As String, strColonEndedString As String
    Dim strRowsUp As String, intRowsUp As Integer
    intStart = 1 'Start searching from the 1st symbol.
    Do While intStart < Len(strFormulaR1C1) 'Reiterate for every colon-ended portion of the formula.
        intPositionColonOrig = InStr(intStart, strFormulaR1C1, ":") 'The position of a colon.
        If intPositionColonOrig = 0 Then 'Exit, unless any more colon found.
            Exit Do
        Else
            strColonEndedStringOrig = Mid(strFormulaR1C1, intStart, intPositionColonOrig - intStart + 1) 'The original colon-ended string.
            intPositionBracketR = InStrRev(strColonEndedStringOrig, strBracketOpen) 'The position of R[
            intPositionBracketClose = InStr(intPositionBracketR, strColonEndedStringOrig, strBracketClose) 'The position of ].
            strRowsUp = Mid(strColonEndedStringOrig, intPositionBracketR + Len(strBracketOpen), intPositionBracketClose - intPositionBracketR - Len(strBracketOpen)) 'The number of rows up till the top of the range.
            intRowsUp = strRowsUp
            strColonEndedString = Replace(strColonEndedStringOrig, strBracketOpen & strRowsUp & strBracketClose, strBracketOpen & Str(intRowsUp - intRowsUpRange) & strBracketClose, , 1) 'Replace the number of rows up till the top of the range.
            strFormulaR1C1 = Replace(strFormulaR1C1, strColonEndedStringOrig, strColonEndedString, , 1) 'Replace the origninal colon-ended string.
            intPositionColon = InStr(intStart, strFormulaR1C1, ":") 'The new position of a colon. The position can change if the number of digits of the new number of rows up changes, e.g. from -9 to -11.
            intStart = intStart + intPositionColon 'Increment the start for a next portion of the formula.
        End If
    Loop
    AdjustTopRangeEdge = strFormulaR1C1 'Return the result.
End Function

Private Function DenmarkRow() As Boolean 'Check if the current row is Denmark's and message.
    Const strDenmarkFormula As String = "Database!B9" 'A formula with Denmark in Database.
    Dim rngCell As Range
    For Each rngCell In Range(ActiveSheet.Cells(Selection.Cells(1, 1).Row, 1), Selection.Cells(1, 1))
        If InStr(1, rngCell.Formula, strDenmarkFormula) <> 0 Then
            DenmarkRow = True
            Exit For
        End If
    Next
End Function

Private Function HasFormulasInsideSheet(rngSelection As Range) As Boolean 'The cells in the range must have formulas and with references only inside its sheet.
    Dim rngCell As Range
    HasFormulasInsideSheet = True
    For Each rngCell In rngSelection
        If Not rngCell.HasFormula Then 'No formula?
            If MsgBox("Cell without formula! Continue?", vbExclamation + vbYesNoCancel) <> vbYes Then 'Do not continue?
                HasFormulasInsideSheet = False
                rngCell.Select 'Select the cell in focus after suspending beacause the original selection is needed in other procedures.
            End If
            Exit For
        ElseIf InStr(1, rngCell.Formula, "!") <> 0 Then 'Formula with references to other sheets?
            If MsgBox("Cell formula with references to other sheets! Continue?", vbExclamation + vbYesNoCancel) <> vbYes Then 'Do not continue?
                HasFormulasInsideSheet = False
                rngCell.Select
            End If
            Exit For
        End If
    Next
End Function

Private Sub FormatRegionalSelection() 'Format regional ranges based on the current selection.
    Dim rngSelection As Range
    Set rngSelection = Selection
'TO BE RESUMED W/O SHARING.
    ActiveCell.Offset(14, 0).Range("A1").Select
    Selection.MergeCells = False
    ActiveCell.Offset(13, 0).Range("A1").Select
    Selection.MergeCells = False
    ActiveCell.Offset(11, 0).Range("A1").Select
    Selection.MergeCells = False
    ActiveCell.Offset(15, 0).Range("A1").Select
    Selection.MergeCells = False
'TO BE RESUMED W/O SHARING.

    rngSelection.Select 'Return to the original position.
    Selection.Copy
    ActiveCell.Offset(14, 0).Range("A1").Select 'Format by the selection's pattern.
    Selection.PasteSpecial Paste:=xlPasteFormats, Operation:=xlNone, SkipBlanks:=False, Transpose:=False
    ActiveCell.Offset(13, 0).Range("A1").Select
    Selection.PasteSpecial Paste:=xlPasteFormats, Operation:=xlNone, SkipBlanks:=False, Transpose:=False
    ActiveCell.Offset(11, 0).Range("A1").Select
    Selection.PasteSpecial Paste:=xlPasteFormats, Operation:=xlNone, SkipBlanks:=False, Transpose:=False
    ActiveCell.Offset(15, 0).Range("A1").Select
    Selection.PasteSpecial Paste:=xlPasteFormats, Operation:=xlNone, SkipBlanks:=False, Transpose:=False
    Application.CutCopyMode = False
    rngSelection.Select 'Return to the original position.
End Sub

Public Sub CopyRegionalFormulas() 'Copy the top region's formulas to its below counterparts.
Attribute CopyRegionalFormulas.VB_ProcData.VB_Invoke_Func = " \n14"
    Const intRowsDownOffset As Integer = 1, intRowsUpRange As Integer = 2 'The array indexes for number of rows to offset down and to extend the formulas' range up for regions.
    Const intRegions As Integer = 4 'The number of regions to copy the formulas among.
    Dim intRowsOffsetRange(1 To 4, 1 To 2) As Integer 'The numbers of rows to offset down and to extend the formulas' ranges up for the regions.
    Dim I As Integer
    Dim rngCellSource As Range, rngCellDestination As Range
    Dim blnStop As Boolean
    If MsgBox("Start copying the top region's formulas to its below counterparts?", vbYesNoCancel + vbQuestion) = vbYes Then
        If UnprotectSheet(ActiveSheet) Then 'Unprotect the sheet, if confirmed.
            If HasFormulasInsideSheet(Selection) Then 'The cells in the range must have formulas and with references only inside its sheet.
                If DenmarkRow() Then 'Check if the current row is Denmark's and message.
                    MsgBox "Do not copy cells of Denmark!", vbExclamation
                Else
                    intRowsOffsetRange(1, intRowsDownOffset) = 14 'Region 1. 'Relatively to North Europe.
                    intRowsOffsetRange(1, intRowsUpRange) = 2
                    intRowsOffsetRange(2, intRowsDownOffset) = 27 'Region 2.
                    intRowsOffsetRange(2, intRowsUpRange) = 1
                    intRowsOffsetRange(3, intRowsDownOffset) = 38 'Region 3.
                    intRowsOffsetRange(3, intRowsUpRange) = -1
                    intRowsOffsetRange(4, intRowsDownOffset) = 53 'Region 4.
                    intRowsOffsetRange(4, intRowsUpRange) = 3
                    For Each rngCellSource In Selection
                        For I = 1 To intRegions
                            Set rngCellDestination = rngCellSource.Offset(intRowsOffsetRange(I, intRowsDownOffset))
                            rngCellDestination.FormulaR1C1 = rngCellSource.FormulaR1C1
                            If InStr(1, rngCellDestination.FormulaR1C1, ":") > 0 Then rngCellDestination.FormulaR1C1 = AdjustTopRangeEdge(rngCellDestination.FormulaR1C1, intRowsOffsetRange(I, intRowsUpRange)) 'Any range (identified by a colon) contained to be adjusted?
                        Next
                    Next
                    FormatRegionalSelection 'Format regional ranges based on the current selection.
                End If
            End If
        End If
    End If
End Sub

Public Sub CopyRegionalCells()
Attribute CopyRegionalCells.VB_ProcData.VB_Invoke_Func = " \n14"
    Dim rngCurrentCells As Range
    If MsgBox("Start copying the top region's cells to its below counterparts?", vbYesNoCancel + vbQuestion) = vbYes Then
        If UnprotectSheet(ActiveSheet) Then 'Unprotect the sheet, if confirmed.
            If HasFormulasInsideSheet(Selection) Then 'The cells in the range must have formulas and with references only inside its sheet.
                If Not DenmarkRow() Then 'Check if the current row is Denmark's and message.
                    MsgBox "Select the row with Denmark!", vbExclamation
                Else
                    Set rngCurrentCells = Selection 'Remember the current cells.
                    Selection.Copy
                    ActiveCell.Offset(12, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(1, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(1, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(12, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(1, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(23, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(1, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(1, 0).Range("A1").Select
                    ActiveSheet.Paste
                    ActiveCell.Offset(1, 0).Range("A1").Select
                    ActiveSheet.Paste
                    rngCurrentCells.Select
                End If
                Application.CutCopyMode = False
            End If
        End If
    End If
End Sub

Sub UnhideAllSheets()
    Dim objSheet
    If MsgBox("Start unhiding all hidden sheets?", vbYesNoCancel + vbQuestion) = vbYes Then
        For Each objSheet In ActiveWorkbook.Sheets
            With objSheet
                If .Visible = xlSheetHidden Then .Visible = xlSheetVisible 'Only if visible.
            End With
        Next
    End If
End Sub

Sub DeleteFormulasInAllSheets()
    Dim objSheet
    If MsgBox("Start deleting formulas in all sheets?", vbYesNoCancel + vbExclamation) = vbYes Then
        For Each objSheet In ActiveWorkbook.Sheets
            With objSheet
                If .Visible = xlSheetHidden Then .Visible = xlSheetVisible 'Only if visible.
                    .Select
                    .Unprotect
                    .Cells.Select
                    Selection.Copy
                    Application.CutCopyMode = False
                    .Columns("A:BE").Select
                    .Range(Selection, Selection.End(xlToRight)).Select
                    Selection.EntireColumn.Hidden = False
                    .Cells.Select
                    Selection.Copy
                    Selection.PasteSpecial Paste:=xlPasteValues, Operation:=xlNone, SkipBlanks:=False, Transpose:=False
                    .Range("A1").Select
                    Application.CutCopyMode = False
            End With
        Next
    End If
End Sub

Public Sub ShowLess_0() 'Show cells with values > 0 hidden.
Attribute ShowLess_0.VB_ProcData.VB_Invoke_Func = "й\n14"
    Dim rngCell As Range
    Dim dblValue As Double
    Dim lngCounter As Long
    Dim blnSuspended As Boolean
    For Each rngCell In Selection
        dblValue = Abs(Val(rngCell.Value))
        If dblValue > 0 And Val(rngCell.Text) = 0 Then
            lngCounter = lngCounter + 1
            rngCell.Select
            If MsgBox("Value > 0! Continue searching?" & vbCrLf & vbCrLf & dblValue, vbYesNoCancel + vbQuestion) <> vbYes Then
                blnSuspended = True
                Exit For
            End If
        End If
    Next
    If Not blnSuspended Then MsgBox lngCounter & " value(s) found > 0!", vbInformation
End Sub

Public Sub MergeOn()
Attribute MergeOn.VB_ProcData.VB_Invoke_Func = "m\n14"
    On Error Resume Next
    Selection.Merge
End Sub

Public Sub MergeOff()
Attribute MergeOff.VB_ProcData.VB_Invoke_Func = "j\n14"
    On Error Resume Next
    Selection.UnMerge
End Sub

Public Sub UnflagValidation() 'Unflag to enable reiterated validations.
Attribute UnflagValidation.VB_ProcData.VB_Invoke_Func = " \n14"
    Dim objSheet
    If MsgBox("Unflag all tables to enable reiterated validation?", vbYesNoCancel + vbQuestion) = vbYes Then
        For Each objSheet In ActiveWorkbook.Sheets
            With objSheet
                If .Visible = xlSheetVisible Then 'Only if visible.
                    .Unprotect
                    .Cells.Font.Strikethrough = False
                End If
            End With
        Next
    End If
End Sub

Sub PreparingDistribution()
'
' PreparingDistribution Macro
'

'
    Sheets("Database").Select
    Range("EPG67").Select
    Sheets("A6.17").Select
    Range("L57").Select
    Sheets(Array("Database", "DatabaseA34", "DatabaseA36")).Select
    Sheets("DatabaseA36").Activate
    ActiveWindow.SelectedSheets.Delete
    Columns("J:AP").Select
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("J:AN").Select
    Range("J5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D7").Select
    Selection.End(xlToRight).Select
    Columns("X:CJ").Select
    Range("X7").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("L:AG").Select
    Range("L6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("C6").Select
    ActiveWindow.LargeScroll Down:=1
    Range("C45").Select
    ActiveWindow.LargeScroll Down:=1
    Range("C6").Select
    Selection.End(xlToRight).Select
    Columns("L:AG").Select
    Range("L6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("C6").Select
    ActiveSheet.Previous.Select
    Range("D7").Select
    Selection.End(xlToRight).Select
    Columns("L:AG").Select
    Range("L7").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D7").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("L:AE").Select
    Range("L6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("J:AB").Select
    Range("J5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("T:CG").Select
    Range("T6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("S:BK").Select
    Range("S6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D7").Select
    Selection.End(xlToRight).Select
    Columns("V:CE").Select
    Range("V7").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D7").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("Y:CD").Select
    Range("Y5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("L:BB").Select
    Range("L5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    ActiveSheet.Next.Select
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("V:CG").Select
    Range("V6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("P:BB").Select
    Range("P6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("L:BB").Select
    Range("L5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("L:BB").Select
    Range("L5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("N:BB").Select
    Range("N5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("N:BA").Select
    Range("N5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("X:CQ").Select
    Range("X5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("X:CQ").Select
    Range("X5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("V:CA").Select
    Range("V5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("M:BA").Select
    Range("M5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("P:BF").Select
    Range("P5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("O:BE").Select
    Range("O6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("S:BJ").Select
    Range("S6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("P:BA").Select
    Range("P5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("T:BH").Select
    Range("T6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("N:BD").Select
    Range("N6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("P:BF").Select
    Range("P6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("L:AG").Select
    Range("L6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("V:BP").Select
    Range("V5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("T:AN").Select
    Range("T5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("Q:AK").Select
    Range("Q6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("T:AN").Select
    Range("T6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    ActiveSheet.Next.Select
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("T:CM").Select
    Range("T5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("T:CQ").Select
    Range("T5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Selection.End(xlToRight).Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("X:DH").Select
    Range("X6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("AJ:DB").Select
    Range("AJ5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("C5").Select
    Selection.End(xlToRight).Select
    Columns("V:BN").Select
    Range("V5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("C5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("S:BJ").Select
    Range("S5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("N:AY").Select
    Range("N5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("T:CE").Select
    Range("T6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("S:BG").Select
    Range("S5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("M:AH").Select
    Range("M6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("N:BD").Select
    Range("N5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("N:BD").Select
    Range("N5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("M:AG").Select
    Range("M6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D4").Select
    Selection.End(xlToRight).Select
    Columns("H:Z").Select
    Range("H4").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D4").Select
    ActiveSheet.Previous.Select
    Range("D5").Select
    Selection.End(xlToRight).Select
    Columns("N:AI").Select
    Range("N5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    ActiveSheet.Next.Select
    Range("D5").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("M:AH").Select
    Range("M6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("D6").Select
    Selection.End(xlToRight).Select
    Columns("M:AG").Select
    Range("M6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("D6").Select
    ActiveSheet.Previous.Select
    Range("B6").Select
    Selection.End(xlToRight).Select
    Columns("I:AB").Select
    Range("I6").Activate
    Selection.Delete Shift:=xlToLeft
    Range("B6").Select
    ActiveSheet.Previous.Select
    Range("B5").Select
    Selection.End(xlToRight).Select
    Columns("M:AH").Select
    Range("M5").Activate
    Selection.Delete Shift:=xlToLeft
    Range("B5").Select
End Sub

Public Sub ExtractSFM() 'Extract a SFM Assessment of the country selected in the Database sheet.
Attribute ExtractSFM.VB_ProcData.VB_Invoke_Func = "q\n14"
    Dim lngCountryRow As Long
    lngCountryRow = Selection.Row
    Sheets(Array("Base data - Template", "Proposed revision - Template")).Select
    Sheets("Proposed revision - Template").Activate
    Sheets(Array("Base data - Template", "Proposed revision - Template")).Copy _
        Before:=Sheets(58)
    Sheets("Base data - Template (2)").Select
    Sheets("Base data - Template (2)").Name = "Base data - Template (2)"
    Sheets("Base data - Template (2)").Select
    Sheets("Base data - Template (2)").Name = "Base data"
    Sheets("Proposed revision - Templat (2").Select
    Sheets("Proposed revision - Templat (2").Name = "Proposed revision"
    Range("B1").Select
    ActiveSheet.Previous.Select
    Range("C4").Select
    'ActiveCell.Replace What:="24", Replacement:="9", LookAt:=xlPart, SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, ReplaceFormat:=False
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, ReplaceFormat:=False
    Cells.Find(What:="24", After:=ActiveCell, LookIn:=xlFormulas, LookAt:= _
        xlPart, SearchOrder:=xlByRows, SearchDirection:=xlNext, MatchCase:=False _
        , SearchFormat:=False).Activate
    Columns("J:J").Select
    Range("J8").Activate
    Range(Selection, Selection.End(xlToRight)).Select
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.Find(What:="24", After:=ActiveCell, LookIn:=xlFormulas, LookAt _
        :=xlPart, SearchOrder:=xlByRows, SearchDirection:=xlNext, MatchCase:= _
        False, SearchFormat:=False).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    ActiveCell.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Selection.FindNext(After:=ActiveCell).Activate
    Selection.Replace What:="24", Replacement:=lngCountryRow, LookAt:=xlPart, _
        SearchOrder:=xlByRows, MatchCase:=False, SearchFormat:=False, _
        ReplaceFormat:=False
    Columns("J:N").Select
'MsgBox "Removing formulas begins"
    Range("M9").Activate
    Selection.Copy
    Selection.PasteSpecial Paste:=xlPasteValues, Operation:=xlNone, SkipBlanks _
        :=False, Transpose:=False
    Selection.PasteSpecial Paste:=xlPasteComments, Operation:=xlNone, _
        SkipBlanks:=False, Transpose:=False
    Range("C4").Select
    Application.CutCopyMode = False
    Selection.Copy
    Selection.PasteSpecial Paste:=xlPasteValues, Operation:=xlNone, SkipBlanks _
        :=False, Transpose:=False
    Sheets(Array("Base data", "Proposed revision")).Select
    Sheets("Proposed revision").Activate
    Application.CutCopyMode = False
    Sheets(Array("Base data", "Proposed revision")).Move
    
'MsgBox "Macro7 begins"
    ' Macro7 Macro
    Range("C4").Select
    'ActiveWorkbook.SaveAs Filename:="C:\Alex\My_Documents\Business\UN\SFM\Russian Federation.xlsx", FileFormat:=xlOpenXMLWorkbook, CreateBackup:=False
    ActiveWorkbook.SaveAs Filename:="C:\Alex\My_Documents\Business\UN\SFM\" & Selection.Text & ".xlsx", FileFormat:=xlOpenXMLWorkbook, CreateBackup:=False
End Sub
