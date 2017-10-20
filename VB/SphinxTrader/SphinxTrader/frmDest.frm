VERSION 5.00
Begin VB.Form frmDest 
   Caption         =   "Destination"
   ClientHeight    =   2865
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3870
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   2865
   ScaleWidth      =   3870
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Request 
      Caption         =   "&Request"
      Height          =   375
      Left            =   2160
      TabIndex        =   4
      Top             =   2160
      Width           =   1215
   End
   Begin VB.CommandButton Poke 
      Caption         =   "Poke"
      Height          =   375
      Left            =   600
      TabIndex        =   3
      Top             =   2160
      Width           =   1215
   End
   Begin VB.OptionButton AutomaticLink 
      Caption         =   "Automatic Link"
      Height          =   495
      Left            =   480
      TabIndex        =   2
      Top             =   1440
      Width           =   1455
   End
   Begin VB.OptionButton ManualLink 
      Caption         =   "Manual Link"
      Height          =   495
      Left            =   480
      TabIndex        =   1
      Top             =   840
      Width           =   1335
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "frmDest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const AUTOMATIC = 1
Const MANUAL = 2
Const NOTIFY = 3
Const NONE = 0

Private Sub AutomaticLink_Click()
    Request.Visible = False   'No need for button with automatic link.
    Text1.LinkMode = NONE     'Clear DDE Link.
    Text1.LinkMode = AUTOMATIC   'Reestablish new LinkMode.
End Sub

Private Sub Form_Load()
    'Winsock1.Protocol = sckTCPProtocol
    'This procedure will start the VB source application.
    'z% = Shell("SOURCE", 1)
    'z% = DoEvents()   'Causes Windows to finish processing Shell command.
    Text1.LinkMode = NONE   'Clears DDE link if it already exists.
'    Text1.LinkTopic = "QR|BID" 'Text1.LinkTopic = "QR|BID!USDCHF" 'Text1.LinkTopic = "Source|Form1"   'Sets up link with VB source.
'    Text1.LinkItem = "USDCHF" 'Text1.LinkItem = "Text1"           'Set link to text box on source.
    Text1.LinkTopic = "MT4|BID" 'Text1.LinkTopic = "Source|Form1"   'Sets up link with VB source.
    Text1.LinkItem = "GBPUSD" 'Text1.LinkItem = "Text1"           'Set link to text box on source.
    Text1.LinkMode = MANUAL            'Establish a manual DDE link.
    ManualLink.Value = True            'Sets appropriate option button.
End Sub

Private Sub ManualLink_Click()
    Request.Visible = True    'Make request button valid.
    Text1.LinkMode = NONE     'Clear DDE Link.
    Text1.LinkMode = MANUAL   'Reestablish new LinkMode.
End Sub

Private Sub Poke_Click()
      'With any DDE link, this button will be visible, and when it's
      'selected, will poke information from the destination application
      'into the source application.
      Text1.LinkPoke
End Sub

Private Sub Request_Click()
    'With a manual DDE link, this button will be visible, and when
    'selected it will request an update of information from the source
    'application to the destination application.
    Text1.LinkRequest
End Sub

Private Sub Text1_LinkNotify()
   Debug.Print "Text1_LinkNotify"
End Sub

