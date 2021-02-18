VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form frmClient 
   Caption         =   "TCP Client"
   ClientHeight    =   1485
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4920
   LinkTopic       =   "Form2"
   LockControls    =   -1  'True
   ScaleHeight     =   1485
   ScaleWidth      =   4920
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtIPAddress 
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Text            =   "192.168.50.1"
      Top             =   240
      Width           =   2895
   End
   Begin VB.CommandButton cmdNewClient 
      Caption         =   "&New client"
      Height          =   375
      Left            =   3360
      TabIndex        =   5
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "&Connect"
      Height          =   375
      Left            =   3360
      TabIndex        =   4
      Top             =   240
      Width           =   1335
   End
   Begin VB.TextBox txtOutput 
      Height          =   375
      Left            =   1920
      Locked          =   -1  'True
      TabIndex        =   3
      Text            =   "txtOutput"
      Top             =   960
      Width           =   1215
   End
   Begin VB.TextBox txtSendData 
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Text            =   "txtSendData"
      Top             =   960
      Width           =   1215
   End
   Begin MSWinsockLib.Winsock tcpClient 
      Left            =   0
      Top             =   1320
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label lblIPAddress 
      Caption         =   "&IP Address:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   0
      Width           =   1215
   End
   Begin VB.Label lblOutput 
      Caption         =   "&Receive:"
      Height          =   255
      Left            =   1920
      TabIndex        =   7
      Top             =   720
      Width           =   1215
   End
   Begin VB.Label lblSendData 
      Caption         =   "&Send:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   720
      Width           =   1215
   End
End
Attribute VB_Name = "frmClient"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cmdNewClient_Click()
    Dim frmNewClient
    Set frmNewClient = New frmClient
    frmNewClient.Show
End Sub

' Invoke the Connect method to initiate a connection.
Private Sub cmdConnect_Click()
On Error GoTo ErrHnd
    tcpClient.RemoteHost = txtIPAddress
    tcpClient.RemotePort = 1001
    tcpClient.Connect
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

Private Sub tcpClient_SendComplete()
    'Debug.Print "SendComplete"
End Sub

Private Sub txtSendData_Change()
On Error GoTo ErrHnd
    tcpClient.SendData txtSendData.Text
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

Private Sub tcpClient_DataArrival(ByVal bytesTotal As Long)
On Error GoTo ErrHnd
    Dim strData As String
    tcpClient.GetData strData
    'tcpClient.PeekData strData
    txtOutput.Text = strData
    'Debug.Print "bytesTotal = " & bytesTotal
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub
'Debug.Print "tcpClient.LocalIP: " & tcpClient.LocalIP
'Debug.Print "tcpClient.LocalHostName: " & tcpClient.LocalHostName
'Debug.Print "tcpClient.RemoteHostIP: " & tcpClient.RemoteHostIP

