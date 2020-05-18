VERSION 5.00
Begin VB.MDIForm frmClient 
   BackColor       =   &H8000000C&
   Caption         =   "Клиентский терминал"
   ClientHeight    =   7155
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10080
   LinkTopic       =   "MDIForm1"
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub MDIForm_Load()
   Dim frmTradeHist1 As frmTradeHist
   'Dim frmTradeHist2 As frmTradeHist
   Set frmTradeHist1 = New frmTradeHist
   frmTradeHist1.Show
'   Set frmTradeHist2 = New frmTradeHist
'   frmTradeHist2.Show
End Sub
