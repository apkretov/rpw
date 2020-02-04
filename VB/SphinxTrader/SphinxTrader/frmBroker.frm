VERSION 5.00
Begin VB.MDIForm frmBroker 
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
Attribute VB_Name = "frmBroker"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub MDIForm_Load()
   Dim frmTable1 As frmTable
   Dim frmTable2 As frmTable
   Set frmTable1 = New frmTable
   frmTable1.Show
   Set frmTable2 = New frmTable
   frmTable2.Show
End Sub
