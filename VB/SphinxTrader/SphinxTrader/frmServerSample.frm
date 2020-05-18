VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "mswinsck.ocx"
Begin VB.Form frmServer 
   Caption         =   "TCP Server"
   ClientHeight    =   1020
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3855
   LinkTopic       =   "Form1"
   ScaleHeight     =   1020
   ScaleWidth      =   3855
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtOutput 
      Height          =   375
      Left            =   2280
      Locked          =   -1  'True
      TabIndex        =   1
      Text            =   "txtOutput"
      Top             =   360
      Width           =   1215
   End
   Begin VB.TextBox txtSendData 
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Text            =   "txtSendData"
      Top             =   360
      Width           =   1215
   End
   Begin MSWinsockLib.Winsock tcpServer 
      Index           =   0
      Left            =   0
      Top             =   840
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label lblOutput 
      Caption         =   "Приём:"
      Height          =   255
      Left            =   2280
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblSendData 
      Caption         =   "Передача:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   120
      Width           =   1215
   End
End
Attribute VB_Name = "frmServer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private intMax As Long

Private Sub Form_Load()
   intMax = 0
   tcpServer(0).LocalPort = 1001
   tcpServer(0).Listen
   frmClient.Show ' Show the client form.
End Sub

Private Sub tcpServer_ConnectionRequest(Index As Integer, ByVal requestID As Long)
   If Index = 0 Then
      intMax = intMax + 1
      Load tcpServer(intMax)
      tcpServer(intMax).LocalPort = 0
      tcpServer(intMax).Accept requestID
      'Load txtData(intMax)
   End If
End Sub

Private Sub tcpServer_SendComplete(Index As Integer)
    'Debug.Print "SendComplete" & vbCrLf & vbCrLf
End Sub

Private Sub tcpServer_SendProgress(Index As Integer, ByVal bytesSent As Long, ByVal bytesRemaining As Long)
    Debug.Print "SendProgress bytesSent: " & bytesSent & vbTab & "bytesRemaining: " & bytesRemaining
End Sub

' The TextBox control named txtSendData contains the data to be sent. Whenever the user types into the  textbox, the  string is sent using the SendData method.
Private Sub txtSendData_Change()
On Error GoTo ErrHnd
    tcpServer(intMax).SendData txtSendData.Text
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Declare a variable for the incoming data. Invoke the GetData method and set the Text property of a TextBox named txtOutput to the data.
Private Sub tcpServer_DataArrival(Index As Integer, ByVal bytesTotal As Long)
On Error GoTo ErrHnd
    Dim strData As String
    'Debug.Print "bytesTotal = " & bytesTotal
    tcpServer(intMax).GetData strData
    txtOutput.Text = strData
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub
'Debug.Print "tcpServer(intMax).LocalIP: " & tcpServer(intMax).LocalIP
'Debug.Print "tcpServer(intMax).LocalHostName: " & tcpServer(intMax).LocalHostName
'Debug.Print "tcpServer(intMax).RemoteHostIP: " & tcpServer(intMax).RemoteHostIP

