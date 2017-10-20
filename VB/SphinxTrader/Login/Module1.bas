Attribute VB_Name = "Module1"
Option Explicit

Public fMainForm As frmMain


Sub Main()
    Dim fLogin As New frmLogin
    fLogin.Show vbModal
    If Not fLogin.OK Then
        'Login Failed so exit app
        End
    End If
    Unload fLogin


    Set fMainForm = New frmMain
    fMainForm.Show
End Sub

