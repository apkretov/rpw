import openpyxl as xl
wb = xl.load_workbook("transactions.xlsx")
sheet = wb["Sheet1"]
cell1 = sheet["a1"]
cell2 = sheet.cell(1, 1)
print(cell1.value)
print(cell2.value)