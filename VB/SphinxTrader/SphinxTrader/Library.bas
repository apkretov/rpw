Attribute VB_Name = "Library"
'PREV_
'Private Sub/Function
'KTB_

'On Error GoTo ErrHnd
'Exit Sub
'ErrHnd:
'MsgBox Err.Number & vbTab & Err.Description

'Debug.Assert 0 = 1 'Verify

' Return True, if succeeds.
Rem Suspended
Rem Update, if necessary
Rem Validation

'LoadResString strings:
') больше                                 LoadResString(346)
'Ввод записи                              LoadResString(370)
'Возраст (                                LoadResString(542)
'Возраст животного '                      LoadResString(331)
'. Вы хотите исправить ошибку?            LoadResString(593)
'Вы хотите исправить ошибку?              LoadResString(594)
' до                                      LoadResString(26)
' дней.                                   LoadResString(234)
' дней).                                  LoadResString(231)
' дней). Вы хотите исправить ошибку?      LoadResString(341)
' дней. Вы хотите исправить ошибку?       LoadResString(590)
'Животное '                               LoadResString(322)
'Изменение записи                         LoadResString(371)
'Интервал (                               LoadResString(586)
' лет).                                   LoadResString(333)
' лет. Вы хотите исправить ошибку?        LoadResString(547)
') меньше                                 LoadResString(345)
') не должен быть больше                  LoadResString(546)
') не должен быть меньше                  LoadResString(544)
'(apostrophe in front)' не существует.    LoadResString(183)
'Овцематка/козоматка '                    LoadResString(170)
'Отсутсвуют данные                        LoadResString(172)
'Ошибка                                   LoadResString(131)
'Повторная запись                         LoadResString(50)
'Пропущен параметр                        LoadResString(21)
'Удаление записи                          LoadResString(372)
'(apostrophe in front)' уже существует.   LoadResString(747)
'Ягнёнок/козлёнок '                       LoadResString(180)

'.ID = "E" & Format$(intEmpNum, "00000")
'strIDShG = strIDFarm & Format$(I, "0000")
'Debug.Print Format(#8/22/1997 5:22:20 PM#, "Medium Date"),
'Debug.Print Format(#8/22/1997 5:22:20 PM#, "Short Date"),
'Debug.Print Format(#8/22/1997 5:22:20 PM#, "Long Date"),
'Debug.Print Format(#8/22/1997 5:22:20 PM#, "General Date"),

'Debug.Print chr(asc("А"))
'Asc("А") = 192
'Asc("Я") = 223
'KeyAscii 48 To 57 '"0" - "9"
'KeyAscii 65 To 90 '"A" - "Z"
'KeyAscii 97 To 122 '"a" - "z"
'KeyAscii 192 To 223 '"А" - "Я"
'KeyAscii 224 To 255 '"а" - "я"

'Dim Start, Finish, Time
'Beep
'Start = Timer
'Finish = Timer
'Beep
'Time = Finish - Start
'Debug.Print "Time = "; Time

'Dim x
'x = x / 0

'Dim frmForm As Form
'Beep
'Debug.Print vbCrLf; "Forms.Count = "; Forms.Count
'For Each frmForm In Forms
'   Debug.Print "frmForm.Name ="; frmForm.Name
'Next

'Debug.Assert 0 = 1 'Verify the error
'Dim obShG As ShG
'Debug.Print vbCrLf; "mcolShGs.Count = "; mcolShGs.Count
'For Each obShG In mcolShGs
'   Debug.Print "obShG.IDShG = "; obShG.IDShG
'Next

'CLng(Rnd * 1000000000#)

'Dim oExcel As Object
'Dim oBook As Object
'Dim oSheet As Object
'Set oExcel = CreateObject("Excel.Application") 'Open a new Excel book
'Set oBook = oExcel.Workbooks.Add
'Set oSheet = oBook.Worksheets(1) 'Add data into new book Sheet 1 cells
'oSheet.Range("A1").Value = "Last Name"
'oSheet.Range("B1").Value = "First Name"
'oSheet.Range("A1:B1").Font.Bold = True
'oSheet.Range("A2").Value = "Doe"
'oSheet.Range("B2").Value = "John"
'oBook.SaveAs "C:\Book1.xls" 'Save the book and exit Excel
'oExcel.Quit

'Private Sub Command1_Click()
'    Dim intX As Integer   ' Declare counter variable.
'    Dim countersA(5) As Integer ' Declare and populate an integer array.
'    For intX = 0 To 4
'        countersA(intX) = intX
'    Next intX
'    Dim countersB(5) As String ' Declare and populate a string array.
'    For intX = 0 To 4
'        countersB(intX) = "hello" & intX
'    Next intX
'    Dim arrX(2) As Variant 'Declare a new two-member array.
'    arrX(1) = countersA() 'Populate the array with other arrays.
'    arrX(2) = countersB()
'    MsgBox arrX(1)(2)   ' Display a member of each array.
'    MsgBox arrX(2)(3)
'End Sub
