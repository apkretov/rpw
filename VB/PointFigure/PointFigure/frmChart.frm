VERSION 5.00
Begin VB.Form frmChart 
   Caption         =   " "
   ClientHeight    =   11115
   ClientLeft      =   390
   ClientTop       =   -300
   ClientWidth     =   13620
   Icon            =   "frmChart.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MDIChild        =   -1  'True
   ScaleHeight     =   11115
   ScaleWidth      =   13620
   Begin VB.PictureBox picChart 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      ForeColor       =   &H80000008&
      Height          =   11895
      Left            =   0
      ScaleHeight     =   11865
      ScaleWidth      =   12945
      TabIndex        =   0
      Top             =   0
      Width           =   12975
      Begin VB.Timer tmrDrawDelay 
         Enabled         =   0   'False
         Interval        =   125
         Left            =   0
         Top             =   0
      End
   End
   Begin VB.Label lblNotify 
      Alignment       =   2  'Center
      Caption         =   "lblNotify"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   13080
      TabIndex        =   103
      Top             =   960
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblBid 
      Alignment       =   2  'Center
      Caption         =   "lblBid"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   204
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   13080
      TabIndex        =   102
      Top             =   600
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   100
      Left            =   13080
      TabIndex        =   101
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   99
      Left            =   13080
      TabIndex        =   100
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   98
      Left            =   13080
      TabIndex        =   99
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   97
      Left            =   13080
      TabIndex        =   98
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   96
      Left            =   13080
      TabIndex        =   97
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   95
      Left            =   13080
      TabIndex        =   96
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   94
      Left            =   13080
      TabIndex        =   95
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   93
      Left            =   13080
      TabIndex        =   94
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   92
      Left            =   13080
      TabIndex        =   93
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   91
      Left            =   13080
      TabIndex        =   92
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   90
      Left            =   13080
      TabIndex        =   91
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   89
      Left            =   13080
      TabIndex        =   90
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   88
      Left            =   13080
      TabIndex        =   89
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   87
      Left            =   13080
      TabIndex        =   88
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   86
      Left            =   13080
      TabIndex        =   87
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   85
      Left            =   13080
      TabIndex        =   86
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   84
      Left            =   13080
      TabIndex        =   85
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   83
      Left            =   13080
      TabIndex        =   84
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   82
      Left            =   13080
      TabIndex        =   83
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   81
      Left            =   13080
      TabIndex        =   82
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   80
      Left            =   13080
      TabIndex        =   81
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   79
      Left            =   13080
      TabIndex        =   80
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   78
      Left            =   13080
      TabIndex        =   79
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   77
      Left            =   13080
      TabIndex        =   78
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   76
      Left            =   13080
      TabIndex        =   77
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   75
      Left            =   13080
      TabIndex        =   76
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   74
      Left            =   13080
      TabIndex        =   75
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   73
      Left            =   13080
      TabIndex        =   74
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   72
      Left            =   13080
      TabIndex        =   73
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   71
      Left            =   13080
      TabIndex        =   72
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   70
      Left            =   13080
      TabIndex        =   71
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   69
      Left            =   13080
      TabIndex        =   70
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   68
      Left            =   13080
      TabIndex        =   69
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   67
      Left            =   13080
      TabIndex        =   68
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   66
      Left            =   13080
      TabIndex        =   67
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   65
      Left            =   13080
      TabIndex        =   66
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   64
      Left            =   13080
      TabIndex        =   65
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   63
      Left            =   13080
      TabIndex        =   64
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   62
      Left            =   13080
      TabIndex        =   63
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   61
      Left            =   13080
      TabIndex        =   62
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   60
      Left            =   13080
      TabIndex        =   61
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   59
      Left            =   13080
      TabIndex        =   60
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   58
      Left            =   13080
      TabIndex        =   59
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   57
      Left            =   13080
      TabIndex        =   58
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   56
      Left            =   13080
      TabIndex        =   57
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   55
      Left            =   13080
      TabIndex        =   56
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   54
      Left            =   13080
      TabIndex        =   55
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   53
      Left            =   13080
      TabIndex        =   54
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   52
      Left            =   13080
      TabIndex        =   53
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   51
      Left            =   13080
      TabIndex        =   52
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   50
      Left            =   13080
      TabIndex        =   51
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   49
      Left            =   13080
      TabIndex        =   50
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   48
      Left            =   13080
      TabIndex        =   49
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   47
      Left            =   13080
      TabIndex        =   48
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   46
      Left            =   13080
      TabIndex        =   47
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   45
      Left            =   13080
      TabIndex        =   46
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   44
      Left            =   13080
      TabIndex        =   45
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   43
      Left            =   13080
      TabIndex        =   44
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   42
      Left            =   13080
      TabIndex        =   43
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   41
      Left            =   13080
      TabIndex        =   42
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   40
      Left            =   13080
      TabIndex        =   41
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   39
      Left            =   13080
      TabIndex        =   40
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   38
      Left            =   13080
      TabIndex        =   39
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   37
      Left            =   13080
      TabIndex        =   38
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   36
      Left            =   13080
      TabIndex        =   37
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   35
      Left            =   13080
      TabIndex        =   36
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   34
      Left            =   13080
      TabIndex        =   35
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   33
      Left            =   13080
      TabIndex        =   34
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   32
      Left            =   13080
      TabIndex        =   33
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   31
      Left            =   13080
      TabIndex        =   32
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   30
      Left            =   13080
      TabIndex        =   31
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   29
      Left            =   13080
      TabIndex        =   30
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   28
      Left            =   13080
      TabIndex        =   29
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   27
      Left            =   13080
      TabIndex        =   28
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   26
      Left            =   13080
      TabIndex        =   27
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   25
      Left            =   13080
      TabIndex        =   26
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   24
      Left            =   13080
      TabIndex        =   25
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   23
      Left            =   13080
      TabIndex        =   24
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   22
      Left            =   13080
      TabIndex        =   23
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   21
      Left            =   13080
      TabIndex        =   22
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   20
      Left            =   13080
      TabIndex        =   21
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   19
      Left            =   13080
      TabIndex        =   20
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   18
      Left            =   13080
      TabIndex        =   19
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   17
      Left            =   13080
      TabIndex        =   18
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   16
      Left            =   13080
      TabIndex        =   17
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   15
      Left            =   13080
      TabIndex        =   16
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   14
      Left            =   13080
      TabIndex        =   15
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   13
      Left            =   13080
      TabIndex        =   14
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   12
      Left            =   13080
      TabIndex        =   13
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   11
      Left            =   13080
      TabIndex        =   12
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   10
      Left            =   13080
      TabIndex        =   11
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   9
      Left            =   13080
      TabIndex        =   10
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   8
      Left            =   13080
      TabIndex        =   9
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   7
      Left            =   13080
      TabIndex        =   8
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   6
      Left            =   13080
      TabIndex        =   7
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   5
      Left            =   13080
      TabIndex        =   6
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   4
      Left            =   13080
      TabIndex        =   5
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   3
      Left            =   13080
      TabIndex        =   4
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   2
      Left            =   13080
      TabIndex        =   3
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   1
      Left            =   13080
      TabIndex        =   2
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
   Begin VB.Label lblQut 
      Caption         =   "1.3000"
      Height          =   160
      Index           =   0
      Left            =   13080
      TabIndex        =   1
      Top             =   120
      Visible         =   0   'False
      Width           =   495
   End
End
Attribute VB_Name = "frmChart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mlngLevrg As Long = 10000 'The currency leverage multiplier to convert to pts.
Const mintIndtArnd As Integer = 50 'The indent arond the picture box.
Const mstrReady As String = "Ready"
Const mintStepFine As Integer = 5 '1 'The fine & fast tuning steps.
Const mintStepFast As Integer = 100 '5
Const mintMinusSng As Integer = -1 'The minus sign multiplier.

Private WithEvents mobCandleStick As CandleStick
Attribute mobCandleStick.VB_VarHelpID = -1
Private WithEvents mobBar As Bar
Attribute mobBar.VB_VarHelpID = -1

Dim mobjChart As New Chart
Dim mobBox As Box

' Show the 1st time, if any, in the status bar.
Private Sub Form_Activate()
On Error GoTo ErrHnd
   Call ShowTime(False)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Ascend/decent the time step to tune the chart to the right/left.
Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   Const strTune As String = "Tune: " 'The Tune message for the status bar.
   With mobjChart
      If KeyCode = vbKeyLeft Or KeyCode = vbKeyRight Then 'Left/right arrows?
         Select Case KeyCode
         Case vbKeyLeft
            .TimeStep = .TimeStep + StepTune(Shift)
         Case vbKeyRight
            .TimeStep = .TimeStep - StepTune(Shift)
         End Select
         Call UpdStBar(strTune & .TimeStep) 'Show the tuning step.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Act as the frmMain form's menu shortcuts for the frmMain.mnuToolsRefrsh item.
' Execute tuning, if the tuning time step has been set in the Form_KeyDown procedure.
Private Sub Form_KeyUp(KeyCode As Integer, Shift As Integer)
On Error GoTo ErrHnd
   Select Case KeyCode
   Case vbKeyF5
      Select Case Shift
      Case 0
         Call Refrsh 'Refresh.
      Case vbCtrlMask
         Call Restore 'Restore.
      End Select
   Case vbKeyPageUp
      Call AdjustIncr(1) 'Increase the increment.
   Case vbKeyPageDown
      Call AdjustIncr(-1) 'Decrease the increment.
   Case vbKeyLeft, vbKeyRight
      With mobjChart
         If .TimeStep <> 0 Then 'Tuned?
            Call RefrshTune(.TimeStep) 'Execute tuning.
            .TimeStep = 0 'Reset.
         End If
      End With
   End Select
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Input the increment & the number of boxes to reverse a bar.
Private Sub Form_Load()
On Error GoTo ErrHnd
   Set mobCandleStick = New CandleStick
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set DDE via the Bid lable.
Private Sub SetDDE()
   Const intLinkModeAutomatic As Integer = 1
   Const intLinkModeNotify As Integer = 3
   Const strLinkTopicTime As String = "TIME"
   Const strLinkTopicBid As String = "BID"
'   Static blnSet As Boolean
'   If Not blnSet Then 'Not set yet?
      Call LinkPrices(lblNotify, intLinkModeNotify, mobjChart.Symbol, strLinkTopicTime) ' Link the DDE price lables.
      Call LinkPrices(lblBid, intLinkModeAutomatic, mobjChart.Symbol, strLinkTopicBid) ' Link the DDE time lables.
'      blnSet = True 'Flag setting.
'   End If
End Sub

' Link the DDE price lables.
Private Sub LinkPrices(lblPrice As Label, ByVal intLinkMode As Integer, ByVal strTool As String, ByVal strLinkTopic As String)
On Error GoTo ErrHnd
   Const intNone As Integer = 0 'No link mode
   Const strDDEApp As String = "MT4" 'The DDE-source external application name.
   Const intErrNoApp As Integer = 282 'Error: No foreign application responded to a DDE initiate.
   Const intErrNoOper As Integer = 285 'Error: Foreign application won't perform DDE method or operation.
   Dim intErr As Integer
   lblPrice.LinkMode = intNone 'Clear DDE Link.
   lblPrice.LinkTopic = strDDEApp & "|" & strLinkTopic 'Sets up link with VB source.
   lblPrice.LinkItem = strTool 'Set link to text box on source.
   lblPrice.LinkMode = intLinkMode 'Reestablish new LinkMode.
Exit Sub
ErrHnd:
    intErr = Err.Number
'    If Err.Number <> intErrNoOper Then MsgBox Err.Number & vbTab & Err.Description 'An error other than Foreign application won't perform DDE method or operation?
    If intErr <> intErrNoOper And intErr <> intErrNoApp Then MsgBox Err.Number & vbTab & Err.Description 'An error other than Foreign application won't perform DDE method or operation?
End Sub

' Refresh the latest quote tick by tick to plot boxes in bars.
Private Sub lblNotify_LinkNotify()
On Error GoTo ErrHnd
'   If frmMain.tmrRefrsh.Enabled Then mobBar.RefreshQut ConvCur(lblBid.Caption), mobjChart.Incr, mlngLevrg 'Is the timer enables i.e. no forms refreshing is going on?
   If frmMain.tmrRefrsh.Enabled Then
      mobBar.RefreshQut ConvCur(lblBid.Caption), mobjChart.Incr, mlngLevrg 'Is the timer enabled i.e. no forms refreshing is going on?
      Call PrintScaleQutLst ' Print the latest quote.
'      Call WriteCaption ' Write the incerment-reversal & file path in the form's caption.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Convert a number into the Currency number format. Why Currency but not Sigle is due to the function copied w/o a change from the SphinxTrader project.
Private Function ConvCur(ByVal strNum As String) As Currency
On Error GoTo ErrHnd
   Const intTypeMismatch As Integer = 13 'The Type Mismatch error number.
   ConvCur = CCur(strNum) 'Convert to currency.
Exit Function
ErrHnd:
   If Err.Number = intTypeMismatch Then 'A non-number entry i.e. the expected Type Mismatch error?
      ConvCur = CCur(ChanWrongDecmSymb(strNum)) 'Convert to currency.
   Else 'Another error.
      MsgBox Err.Number & vbTab & Err.Description
   End If
End Function

' Change a wrong locale decimal symbol from the dot to the comma or vice versa.
Private Function ChanWrongDecmSymb(ByVal strNum As String) As String
   Const strDecmSymbDot As String = "." 'Dot/comma decimal symbols.
   Const strDecmSymbCom As String = ","
   Dim strDecmSymb As String
   Dim intPostn As Integer
   Dim strBefore As String
   Dim strAfter As String
   intPostn = InStr(strNum, strDecmSymbDot)
   If intPostn > 0 Then 'Found a dot?
      strDecmSymb = strDecmSymbCom 'Remember the decimal symbol.
   Else 'No dot. Search a comma.
      strDecmSymb = strDecmSymbDot
      intPostn = InStr(strNum, strDecmSymbCom)
   End If
   If intPostn = 0 Then 'No decimal symbol?
      ChanWrongDecmSymb = strNum 'Return the number unchnaged.
   Else
      strBefore = Left$(strNum, intPostn - 1) 'The string before the cut character.
      strAfter = Right$(strNum, Len(strNum) - intPostn) 'The string after the cut character.
      ChanWrongDecmSymb = strBefore & strDecmSymb & strAfter 'Compose.
   End If
End Function

' Resize the picChart control to the full form.
Private Sub Form_Resize()
On Error GoTo ErrHnd
   Dim sngPicWdth As Single
   Dim sngPicHght As Single
   With Me
      If .WindowState <> vbMinimized Then 'Not minimised?
         sngPicWdth = .ScaleWidth - lblQut(0).Width - mintIndtArnd * 2 'Picture box's width & height.
         sngPicHght = .ScaleHeight - mintIndtArnd * 2
         If sngPicWdth > 0 And sngPicHght > 0 Then 'Size positive?
            picChart.Move .ScaleLeft + mintIndtArnd, .ScaleTop + mintIndtArnd, sngPicWdth, sngPicHght
            Call Draw 'Redraw the chart.
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Invoke the DrawDelay procedure by enabling the tmrDrawDelay timer.
Public Sub Draw(Optional ByVal strFlPath As String, Optional ByVal strSymbol As String)
On Error GoTo ErrHnd
   With mobjChart
      If .ParamInputd And (Len(strFlPath) > 0 Or Len(.FlPath) > 0) Then 'Parameters inputted?
         If Len(strFlPath) > 0 Then .FlPath = strFlPath 'Read a new file.
         If Len(strSymbol) > 0 Then .Symbol = strSymbol
         picChart.Cls
         Call HideLbl 'Hide the quote lables.
         tmrDrawDelay.Enabled = True
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' If the mobjChart.Incr & mobjChart.Revers parameters are inputted in the Form_Load procedure draw a point & figure
'  chart based on the specified file's data.
Private Sub DrawDelay()
   Const sngShiftCff As Single = 0.05 'The Shift Chart ratio to shift from the right edge.
   Dim sngSkipCffOrig As Single
   Dim sngSkipCff As Single
   Dim sngSkipCffAdd As Single
   Dim lngLinCount As Long
   Dim lngLinSkip As Long
   Call WriteCaption 'Write the caption.
   Call Rest 'Reset the module objects.
   lngLinCount = ReadFile(mobjChart.FlPath, 0) '1st chart draft - get the number of lines in the file.
   sngSkipCffOrig = SkipCff 'The ratio to skip the unfitted bars.
   sngSkipCff = sngSkipCffOrig 'Below: 'Not all boxes fit?
   sngSkipCffAdd = sngShiftCff 'Iniitalise the skip coefficient to double it later, if necessary.
   Do While (sngSkipCff > 1) Or (mobBox.CentrYTop < picChart.ScaleTop + mobBox.SideSize / 2) Or (mobBox.CentrYBttm > picChart.ScaleHeight - mobBox.SideSize / 2)
      sngSkipCffAdd = sngSkipCffAdd * 2 'Double the additional accumulative ration to shift.
      lngLinSkip = lngLinCount - lngLinCount / (sngSkipCffOrig + sngSkipCffAdd)
      Call Rest 'Reset the module objects.
      Call HideLbl 'Hide the quote lables.
      Call ReadFile(mobjChart.FlPath, lngLinSkip) 'Draw again skipping the boxes unfitted.
      sngSkipCff = SkipCff 'The ratio to skip the unfitted bars.
   Loop
   Call ScaleRefrsh 'Print the scale & the latest quote & arrange refreshing the chart.
End Sub

' Draw a point & figure chart based on the specified file's data.
' Return the number of lines read in the file.
Private Function ReadFile(ByVal strFlPath As String, ByVal lngLinSkip As Long) As Long
On Error GoTo ErrHnd
   Dim fsoTxtStrm As TextStream
   Call InitBox(strFlPath, lngLinSkip) 'Initialise the mobBox object.
   Set fsoTxtStrm = Util.TxtStrm(strFlPath, lngLinSkip) 'Open the file.
   If frmMain.mnuToolsStep.Checked Then 'Step by step?
      ReadFile = ReadFileStep(fsoTxtStrm)
   Else 'All.
      ReadFile = ReadFileAll(fsoTxtStrm)
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Initialise the mobBox object:
'  - the side size;
'  - 1st box's cetre's horizontal coordinate to shift from the left edge of the picture box;
'  - 1st box's cetre's vertical coordinate based on the min/max quotes & the picture box's height.
'  - the bar's open quote.
Private Sub InitBox(ByVal strFlPath As String, ByVal lngLinSkip As Long)
On Error GoTo ErrHnd
   Const sngMinBeg As Single = 1000 'The beginning minimal value to look for smaller values.
   Const intDecmlSubt As Integer = 3 'The decimal subtrahend to deduct from the levarage's decimal count.
   Dim obCandleStick As New CandleStick
   Dim fsoTxtStrm As TextStream
   Dim sngMin As Single
   Dim sngMax As Single
   Dim sngRange As Single
   Dim sngFstAvg As Single
   Dim blnFstRead As Boolean
   sngMin = sngMinBeg 'Initialise the min.
   Set fsoTxtStrm = Util.TxtStrm(strFlPath, lngLinSkip) 'Read the file.
   Do 'Get the min/max.
      With obCandleStick
         .ReadOHLC fsoTxtStrm.ReadLine, False 'Read the OHLC quotes.
         If Not blnFstRead Then '1st read?
            sngFstAvg = Round((.H + .L) / 2, CountDecml(intDecmlSubt))  '1st average rounded.
            mobBar.H = sngFstAvg 'The bar's open.
            mobBar.L = sngFstAvg 'The bar's open.
            blnFstRead = True 'Mark read.
         End If
         If sngMin > .L Then sngMin = .L
'         If sngMin >= .L Then sngMin = .L 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
         If sngMax < .H Then sngMax = .H
'         If sngMax <= .H Then sngMax = .H 'Not sure about this change but trying to solve the 4 * 3 = 13 Reversal error.
      End With
   Loop Until fsoTxtStrm.AtEndOfStream
   sngRange = sngMax - sngMin 'The quotes' range.
   Set mobBox = New Box
   With mobBox
      .SideSize = mobjChart.BoxSideSize
      .CentrX = mobjChart.BoxSideSize / 2 'The 1st horizontal coordinate.
      .CentrY = (sngMax - sngFstAvg) / sngRange * picChart.ScaleHeight 'The 1st vertical coordinate.
   End With
   Call DrawGrid(sngFstAvg) 'Draw the grid.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the status bar.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
'Debug.Print "Form_Unload"
   Call UpdStBar(mstrReady)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the latest quote to plot boxes in bars.
Private Sub mobCandleStick_RefreshQut(ByVal sngQut As Single)
On Error GoTo ErrHnd
   mobBar.RefreshQut sngQut, mobjChart.Incr, mlngLevrg
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Plot the intCountCrs number of crosses in a cross bar.
Private Sub mobBar_AddCrosses(ByVal intCountCrs As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = 1 To intCountCrs 'Plot crosses.
      mobBox.MoveUp
      Call PlotCross
   Next
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   Call CycleErrHnd(Err.Description) 'Handle a cyclical error.
End Sub

' Plot the intCountZr number of zeros in a zero bar.
Private Sub mobBar_AddZeros(ByVal intCountZr As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   For I = 1 To intCountZr 'Plot zeros.
      mobBox.MoveDown
      Call PlotZero
   Next
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   Call CycleErrHnd(Err.Description) 'Handle a cyclical error.
End Sub

' Reverse the bar down by plotting zeros at the right-down from the box's current position.
Private Sub mobBar_ReverseDown(ByVal intCountZr As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   mobBox.MoveRight
   For I = 1 To intCountZr 'Plot zeros.
      mobBox.MoveDown
      Call PlotZero
   Next
Exit Sub
ErrHnd:
   Call CycleErrHnd(Err.Description) 'Handle a cyclical error.
End Sub

' Plot a cross.
Private Sub PlotCross()
On Error GoTo ErrHnd
   Dim sngLeft As Single
   Dim sngRight As Single
   Dim sngTop As Single
   Dim sngBottom As Single
   Dim sngHalfSide As Single
   With mobBox
      sngHalfSide = .SideSize / 2 'Halve the side.
      sngLeft = .CentrX - sngHalfSide 'The corner coordinates.
      sngRight = .CentrX + sngHalfSide
      sngTop = .CentrY - sngHalfSide
      sngBottom = .CentrY + sngHalfSide
      picChart.Line (sngLeft, sngTop)-(sngRight, sngBottom), vbBlue 'The upward line.
      picChart.PSet (sngRight, sngBottom), vbBlue 'Complete the line.
      picChart.Line (sngLeft, sngBottom)-(sngRight, sngTop), vbBlue 'The downward line.
      picChart.PSet (sngRight, sngTop), vbBlue 'Complete the line.
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Plot a zero.
Private Sub PlotZero()
On Error GoTo ErrHnd
   With mobBox
      picChart.Circle (.CentrX, .CentrY), .SideSize / 2, vbBlue
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reverse the bar up by plotting crosses at the right-up from the box's current position.
Private Sub mobBar_ReverseUp(ByVal intCountCrs As Integer)
On Error GoTo ErrHnd
   Dim I As Integer
   mobBox.MoveRight
   For I = 1 To intCountCrs 'Plot zeros.
      mobBox.MoveUp
      Call PlotCross
   Next
Exit Sub
ErrHnd:
   Call CycleErrHnd(Err.Description) 'Handle a cyclical error.
End Sub

' Adjust the box side size & redraw the chart.
Public Sub AdjustBox()
On Error GoTo ErrHnd
   Dim strInput As String
   strInput = Trim(InputBox("Input the box side size", "Box Side Size", mobBox.SideSize))
   If Len(strInput) > 0 Then 'Inputted?
      If Val(strInput) > 0 Then 'More than zero?
         mobjChart.BoxSideSize = strInput
         SaveSetting App.Title, "Settings", "BoxSideSize", strInput
         Call Draw
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Refresh the chart.
Public Sub Refrsh()
On Error GoTo ErrHnd
   If mobjChart.ParamInputd Then
      If ParamInput Then 'Parameters changed?
         frmMain.tmrRefrsh.Enabled = False 'Disable the refreshing timer.
         Call Draw 'Draw, if parameters inputted.
      End If
   End If
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   frmMain.tmrRefrsh.Enabled = True 'Resume, if disabled.
   MsgBox Err.Description
End Sub

' Draw the price grid.
Private Sub DrawGrid(ByVal sngFstAvg As Single)
   Const intBoxPerGrid As Integer = 2 'The number of boxes between two grid lines.
   Const intRed As Integer = 83, intGreen As Integer = 81, intBlue As Integer = 82 'The red, green & blue components of the grid line colour.
   Dim x As Single, y As Single, sngQutScale As Single, intIdx As Integer, lngRGB As Long
   y = mobBox.CentrY '+ mobBox.SideSize / 2
   sngQutScale = AvgScaleQut(sngFstAvg) 'The average scale quote.
   picChart.DrawStyle = vbDot 'Dashed line stile.
   lngRGB = RGB(intRed, intGreen, intBlue) 'Line colour.
   Do While y > 0 'Lines from the centre to top.
      picChart.Line (picChart.ScaleLeft, y)-(picChart.ScaleWidth, y), lngRGB
      Call PrintScaleQut(intIdx, sngQutScale, y) 'Print the scale quote.
      intIdx = intIdx + 1
      y = y - mobBox.SideSize * intBoxPerGrid 'Shift.
      sngQutScale = Util.IntQut(sngQutScale + Util.BoxesToQut(intBoxPerGrid, mobjChart.Incr, mlngLevrg), mlngLevrg) 'Next scale quote to print.
   Loop
   y = mobBox.CentrY '+ mobBox.SideSize / 2 'Centre.
   sngQutScale = AvgScaleQut(sngFstAvg) 'The average scale quote.
   Do While y < picChart.ScaleHeight 'Lines from the centre to bottom.
      picChart.Line (picChart.ScaleLeft, y)-(picChart.ScaleWidth, y), lngRGB
      Call PrintScaleQut(intIdx, sngQutScale, y) 'Print the scale quote.
      intIdx = intIdx + 1
      y = y + mobBox.SideSize * intBoxPerGrid 'Shift.
      sngQutScale = Util.IntQut(sngQutScale - Util.BoxesToQut(intBoxPerGrid, mobjChart.Incr, mlngLevrg), mlngLevrg) 'Next scale quote to print.
   Loop
   Do While x < picChart.ScaleWidth 'Lines from the left to right.
      x = x + mobBox.SideSize * intBoxPerGrid 'Shift.
      picChart.Line (x, picChart.ScaleTop)-(x, picChart.ScaleHeight), lngRGB
   Loop
   picChart.DrawStyle = vbSolid 'Reset the style.
End Sub

' Show the 1st time, if any, in the status bar.
Private Sub picChart_DblClick()
On Error GoTo ErrHnd
   Call ShowTime(True)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Start drawing after a delay.
Private Sub tmrDrawDelay_Timer()
On Error GoTo ErrHnd
   tmrDrawDelay.Enabled = False 'Disable.
   Call DrawDelay
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Hide the quote lables to reprint them again.
Private Sub HideLbl()
On Error GoTo ErrHnd
   Dim lblLable As Label
   For Each lblLable In lblQut
      lblLable.Visible = False
   Next
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Print the scale quotes.
Private Sub PrintScaleQut(ByVal intIdx As Integer, ByVal sngQut As Single, ByVal sngYGrid As Single)
On Error GoTo ErrHnd
   Const intDecmlSubt As Integer = 2 'The decimal subtrahend to deduct from the levarage's decimal count.
   Static intCountDecml As Integer
   If intCountDecml = 0 Then intCountDecml = CountDecml(intDecmlSubt) 'Define the decimals once.
   With lblQut(intIdx)
      .Caption = Format$(sngQut, "#." & String$(intCountDecml, "0")) 'Print the scale quote.
      .Top = sngYGrid - .Height / 2 + mintIndtArnd
      .Left = picChart.Width + mintIndtArnd
      .Visible = True
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return the average scale quote.
Private Function AvgScaleQut(ByVal sngFstAvg As Single) As Single
On Error GoTo ErrHnd
   AvgScaleQut = Util.IntQut(sngFstAvg, mlngLevrg)
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Print the latest quote.
Private Sub PrintScaleQutLst()
On Error GoTo ErrHnd
   Const intIdxLastLbl As Integer = 100 'The last lable's index.
   With mobBar
      Call PrintScaleQut(intIdxLastLbl, IIf(.Cross, .H, .L), mobBox.CentrY)
      lblQut(intIdxLastLbl).ForeColor = vbBlue
      lblQut(intIdxLastLbl).ZOrder
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Automatically refreesh the chart, if the undelying data file has changed.
Public Sub RefrshTimer()
On Error GoTo ErrHnd
   Dim fsoFSO As New FileSystemObject
   Dim fsoFile As File
   With mobjChart
      If fsoFSO.FileExists(.FlPath) Then
         Set fsoFile = Util.OpenFile(.FlPath) 'Open the file.
         If fsoFile.DateCreated <> .FlDateCreated Or fsoFile.DateLastModified <> .FlDateLastModified Then
            Call frmMain.ProgrBarShow(True) 'Show the progress bar.
            .FlDateCreated = 0 'Reset.
            .FlDateLastModified = 0
            If .CycleErr Then .CycleErr = False 'Reset the CandleStick.ReadQut mark, in case of a recent error.
            Call RefrshTune 'Redraw.
            Call SetDDE ' Set DDE via the Bid lable. It's reset here due to no external DDE-source appliction had been on when the link was being set.
         End If
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Save the original underlying data file's creation & modification dates to compare them later with new versions
'  that will invoke refreshing the chart.
Private Sub SaveOrigFlDates()
On Error GoTo ErrHnd
   Dim fsoFile As File
   With mobjChart
      Set fsoFile = Util.OpenFile(.FlPath)
      .FlDateCreated = fsoFile.DateCreated
      .FlDateLastModified = fsoFile.DateLastModified
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Count the decimals based on the currency's levarage.
Private Function CountDecml(ByVal intDecmlSubt As Integer) As Integer
On Error GoTo ErrHnd
   CountDecml = Len(Str$(mlngLevrg)) - intDecmlSubt
Exit Function
ErrHnd:
MsgBox Err.Description
End Function


' Input the increment & the number of boxes to reverse a bar.
' Return True, if succeeds.
Public Function ParamInput(Optional ByVal strFileTitle As String) As Boolean
On Error GoTo ErrHnd
   Const intIncrementDflt As Integer = 8 'The default.
   Const intReversDftl As Integer = 3 'The default.
   Static blnPassed As Boolean
   Dim strInput As String
   Dim blnSymbolDefined As Boolean
   If Len(strFileTitle) = 0 Then 'Need to input a symbol? Only frmMain.LoadNewFrm calls this function with non-empty strFileTitle.
      blnSymbolDefined = True
   Else
      strInput = Trim(InputBox("Input a symbol", "Symbol", DefaultSymbol(strFileTitle))) 'Input a symbol.
      If Len(strInput) > 0 Then 'Inputted?
         mobjChart.Symbol = strInput
'         Call SetDDE ' Set DDE via the Bid lable.
         blnSymbolDefined = True
      End If
   End If
   If blnSymbolDefined Then 'Symbol defined?
      strInput = Trim(InputBox("Input the increment", "Increment", IIf(mobjChart.Incr > 0, mobjChart.Incr, GetSetting(App.Title, "Settings", "Increment", intIncrementDflt)))) 'Input increment.
      If Len(strInput) > 0 Then 'Inputted?
         If Val(strInput) > 0 Then 'More than zero?
            mobjChart.Incr = strInput
            strInput = "" 'Reset.
            strInput = Trim(InputBox("Input the reversal", "Reversal", IIf(mobjChart.Revers > 0, mobjChart.Revers, GetSetting(App.Title, "Settings", "Revers", intReversDftl))))
            If Len(strInput) > 0 Then 'Inputted?
               If Val(strInput) > 0 Then 'More than zero?
                  With mobjChart
                     .Revers = strInput
                     Call GetSaveSizeIncrRevers 'Get & save box's side's size, increment & reversal.
                     blnPassed = True
                     .ParamInputd = True
                     ParamInput = True
                  End With
               End If
            End If
         End If
      End If
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Return a default symbol based on a file title specified.
Private Function DefaultSymbol(ByVal strFileTitle As String)
   Const intExtentLeng As Integer = 4 'The length of a file extention with the dot.
   Dim intAsc As Integer
   Dim intStart As Integer
   For intStart = Len(strFileTitle) - intExtentLeng To 1 Step -1 'Find a first digit that presumably begins periodicity. E.g. 6 withing GBPUSD60 begins 60.
      intAsc = Asc(Mid$(strFileTitle, intStart, 1))
      If intAsc < vbKey0 Or intAsc > vbKey9 Then Exit For 'A symbol other than 0 or 9?
   Next
   DefaultSymbol = Left$(strFileTitle, intStart) 'Return a string with all symbols before periodicity.
End Function

'Return rhe ratio to skip the unfitted bars.
Private Function SkipCff() As Single
On Error GoTo ErrHnd
   Const intShiftBoxes As Integer = 5 'The number of boxes to shift from the right edge.
   SkipCff = (mobBox.CentrX + mobBox.SideSize * intShiftBoxes) / picChart.Width
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Read the specified file textstream's lines step by step.
' Return the number of lines read in the file.
Private Function ReadFileStep(ByVal fsoTxtStrm As TextStream) As Long
On Error GoTo ErrHnd
   Dim lngLinCount As Long
   Dim strPromt As String
   Do 'Read the file line by line till the end.
      lngLinCount = lngLinCount + 1 'Count the lines.
      mobCandleStick.ReadOHLC fsoTxtStrm.ReadLine, True 'Read the OHLC quotes.
      Clipboard.Clear
      Clipboard.SetText mobCandleStick.Time 'Copy to the clipboard for external analysis.
      Call PrintScaleQutLst 'Print the quote.
      strPromt = "Candlestick " & lngLinCount & ": " & mobCandleStick.Time & String$(2, vbCrLf) & "Next candlestick?"
      If MsgBox(strPromt, vbYesNo + vbQuestion, "Step-by-step drawing") = vbNo Then
         strPromt = lngLinCount & " Candlesticks read."
         MsgBox strPromt, , "Drawing terminated."
         Exit Do
      End If
   Loop Until fsoTxtStrm.AtEndOfStream
   frmMain.mnuToolsStep.Checked = False 'Reset after the 1st round.
   ReadFileStep = lngLinCount 'Return the lines read.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Read the specified file textstream's all lines uninterruptedly.
' Return the number of lines read in the file.
Private Function ReadFileAll(ByVal fsoTxtStrm As TextStream) As Long
On Error GoTo ErrHnd
   Dim lngLinCount As Long
   Do 'Read the file line by line till the end.
      lngLinCount = lngLinCount + 1 'Count the lines.
      mobCandleStick.ReadOHLC fsoTxtStrm.ReadLine, True 'Read the OHLC quotes.
      If lngLinCount = 1 Then
         mobjChart.TimeFst = mobCandleStick.Time 'Remember the 1st candlestick's time.
         Call ShowTime(False) 'Show the 1st time in the status bar.
      End If
   Loop Until fsoTxtStrm.AtEndOfStream
   ReadFileAll = lngLinCount 'Return the lines read.
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Fine tune the chart by shifting the beginning of the candlesticks' range eligible for drawing to the left thereby
'  shifting the chart to the right.
Public Sub TuneFineRht()
On Error GoTo ErrHnd
   Call RefrshTune(mintStepFine * mintMinusSng)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fast tune the chart by shifting the beginning of the candlesticks' range eligible for drawing to the left thereby
'  shifting the chart to the right.
Public Sub TuneFastRht()
On Error GoTo ErrHnd
   Call RefrshTune(mintStepFast * mintMinusSng)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fine tune the chart by shifting the beginning of the candlesticks' range eligible for drawing to the right thereby
'  shifting the chart to the left.
Public Sub TuneFineLft()
On Error GoTo ErrHnd
   Call RefrshTune(mintStepFine)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Fast tune the chart by shifting the beginning of the candlesticks' range eligible for drawing to the right thereby
'  shifting the chart to the left.
Public Sub TuneFastLft()
On Error GoTo ErrHnd
   Call RefrshTune(mintStepFast)
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Tune/refresh the chart by shifting the beginning of the candlesticks' range eligible for drawing to the left/right
'  by the step stecified.
Public Sub RefrshTune(Optional ByVal intStep As Integer = 0)
On Error GoTo ErrHnd
   Dim lngLinSkip As Long
   Call Rest 'Reset the module objects.
   Call HideLbl 'Hide the quote lables.
   lngLinSkip = Util.LinSkip(mobjChart.FlPath, mobjChart.TimeFst) 'The lines to skip up to the 1st time.
   Call ReadFile(mobjChart.FlPath, lngLinSkip + intStep) 'Draw skipping the specified number of lines.
   Call ScaleRefrsh 'Print the scale & the latest quote & arrange refreshing the chart.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the module objects prior to drawing.
Private Sub Rest()
On Error GoTo ErrHnd
   picChart.Cls
   If Not frmMain.mnuToolsStep.Checked Then picChart.Visible = False 'Hide to redraw gracefully, unless step by step.
   If Not mobBar Is Nothing Then Set mobBar = Nothing 'Reset, if created before.
   If Not mobBox Is Nothing Then Set mobBox = Nothing
   Set mobBar = New Bar
   mobBar.Revers = mobjChart.Revers
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Print the scale & the latest quote & resume refreshing the chart.
Private Sub ScaleRefrsh()
On Error GoTo ErrHnd
   Call PrintScaleQutLst 'Print the latest quote.
   picChart.Visible = True 'Unhide after drawing is complete.
   Call SaveOrigFlDates 'Save the original file's dates.
   Beep 'Signal the finish.
   frmMain.tmrRefrsh.Enabled = True 'Enable the timer to monitor the file's changes.
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   frmMain.tmrRefrsh.Enabled = True 'Resume, if disabled.
   MsgBox Err.Description
End Sub

' Update the status bar with the time of 1st candlestick, which drawing the chart begins from.
Private Sub ShowTime(ByVal blnSetClipBoard As Boolean)
On Error GoTo ErrHnd
   Dim strIncrReversTime
   If Len(mobjChart.TimeFst) > 0 Then
      Call UpdStBar("Begins from: " & mobjChart.TimeFst & Space(4) & "(Double-click the chart to export to the clipboard)")
      strIncrReversTime = IncrReversStr & Space(1) & mobjChart.TimeFst
      If blnSetClipBoard Then 'Copy to the clipboard for external use, if required.
         Clipboard.Clear
         Clipboard.SetText strIncrReversTime
      End If
   Else
      Call UpdStBar(mstrReady)
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the status bar with the time of 1st candlestick, which drawing the chart begins from.
Private Sub UpdStBar(ByVal strTxt As String)
On Error GoTo ErrHnd
   Const intPane1 As Integer = 1 'The status bar's pane 1.
   frmMain.staStatusBar.Panels(intPane1) = strTxt
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Return a fine/accelerated tuning step based on the Ctrl key state.
Private Function StepTune(ByVal intShift As Integer)
On Error GoTo ErrHnd
   If intShift = vbCtrlMask Then
      StepTune = mintStepFast
   Else
      StepTune = mintStepFine
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Increase/decrease the increment by one up/down & refresh the chart.
Public Sub AdjustIncr(ByVal intOneUpDown As Integer)
On Error GoTo ErrHnd
   Const intIncrMin As Integer = 2 'The min increment.
   Dim intIncr As Integer
   With mobjChart
      If .ParamInputd Then
         intIncr = .Incr + intOneUpDown 'Assess the increment
         If intIncr < intIncrMin Then 'Below min?
            Beep
         Else
            .Incr = intIncr
            frmMain.tmrRefrsh.Enabled = False 'Disable the refreshing timer.
            Call Draw 'Draw, if parameters inputted.
         End If
      End If
   End With
Exit Sub
ErrHnd:
Debug.Assert 0 = 1 'Verify
   frmMain.tmrRefrsh.Enabled = True 'Resume, if disabled.
   MsgBox Err.Description
End Sub

' Return the increment-reversal string to be shown in the form's caption & copied to the clipboard.
Private Function IncrReversStr() As String
On Error GoTo ErrHnd
   Const strX As String = " x "
   IncrReversStr = mobjChart.Incr & strX & mobjChart.Revers
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the chart's data file name.
Public Property Get FlPath() As String
   FlPath = mobjChart.FlPath
End Property

' Get the chart's data file name.
Public Property Get Symbol() As String
   Symbol = mobjChart.Symbol
End Property

' Get the 1st canlestick's time the chart begins from.
Public Property Get TimeFst() As String
   TimeFst = mobjChart.TimeFst
End Property

' Get the 1st canlestick's time the chart begins from.
Public Property Get Incr() As Integer
   Incr = mobjChart.Incr
End Property

' Get the reversal.
Public Property Get Revers() As Integer
   Revers = mobjChart.Revers
End Property

' Handle cyclical errors.
Public Sub CycleErrHnd(ByVal strErrDescr As String)
On Error GoTo ErrHnd
   If Not mobjChart.CycleErr Then 'Show the error message.
      mobjChart.CycleErr = True 'Mark the error to prevent from identical multiple messages.
      MsgBox strErrDescr, vbCritical, "Cyclical error"
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Set the chart parameters from the previously saved settins.
'Public Sub ParamSet(ByVal strFlPath As String, ByVal intIncr As Integer, ByVal intRevers As Integer, ByVal strTimeFst As String)
Public Sub ParamSet(ByVal strFlPath As String, ByVal strSymbol As String, ByVal intIncr As Integer, ByVal intRevers As Integer, ByVal strTimeFst As String)
On Error GoTo ErrHnd
   With mobjChart
      .FlPath = strFlPath
      .Symbol = strSymbol
      .Incr = intIncr
      .Revers = intRevers
      .TimeFst = strTimeFst
      Call GetSaveSizeIncrRevers 'Get & save box's side's size, increment & reversal.
      .ParamInputd = True 'Mark parameters inputted.
   End With
'   Call SetDDE ' Set DDE via the Bid lable.
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get from & save in the registry the values of box's side's size, increment & reversal.
Private Sub GetSaveSizeIncrRevers()
On Error GoTo ErrHnd
   Const sngSideSizeDflt As Single = 120 'The default side size.
   With mobjChart
      .BoxSideSize = GetSetting(App.Title, "Settings", "BoxSideSize", sngSideSizeDflt)
      SaveSetting App.Title, "Settings", "Increment", .Incr 'Save the settings.
      SaveSetting App.Title, "Settings", "Revers", .Revers
      SaveSetting App.Title, "Settings", "BoxSideSize", .BoxSideSize
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Write the incerment-reversal & file path in the form's caption.
Public Sub WriteCaption()
On Error GoTo ErrHnd
   Dim fsoFSO As New FileSystemObject
   Dim fsoFile As File
   If fsoFSO.FileExists(mobjChart.FlPath) Then
      Set fsoFile = Util.OpenFile(mobjChart.FlPath) 'Open the file.
      Me.Caption = IncrReversStr & " - " & fsoFile.Name 'Increment-reversal in front to see it, if the form is minimised.
'      Me.Caption = IncrReversStr & " - " & fsoFile.Name & " - " & lblBid.Caption 'Increment-reversal in front to see it, if the form is minimised.
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Restore the chart based on the 1st candlestick specified.
Public Sub Restore()
On Error GoTo ErrHnd
   Dim strTimeFst As String
   If mobjChart.ParamInputd Then
      strTimeFst = Trim(InputBox("Input the first candlestick's time to begin the chart from", "Beginnig time", mobjChart.TimeFst))
      If Len(strTimeFst) > 0 Then 'Inputted?
         If Util.LinSkip(mobjChart.FlPath, strTimeFst) > 0 Then 'Time exists?
            mobjChart.TimeFst = strTimeFst 'Save the new time.
            Call RefrshTune 'Draw.
         Else
            MsgBox "The specified time is non-existent or erroneous", vbCritical, "Beginnig time"
         End If
      End If
   End If
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

