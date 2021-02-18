VERSION 5.00
Object = "{0ECD9B60-23AA-11D0-B351-00A0C9055D8E}#6.0#0"; "MSHFLXGD.OCX"
Begin VB.Form frmInvMat 
   Caption         =   "Inventory/mating"
   ClientHeight    =   3870
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   5430
   LinkTopic       =   "Form1"
   ScaleHeight     =   3870
   ScaleWidth      =   5430
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtIDSheepGoat 
      Height          =   285
      Index           =   1
      Left            =   1530
      TabIndex        =   4
      Top             =   495
      Width           =   990
   End
   Begin VB.TextBox txtIDBreedBase 
      Height          =   285
      Left            =   1530
      TabIndex        =   7
      Top             =   750
      Width           =   330
   End
   Begin VB.TextBox txtBreedCross 
      Height          =   285
      Left            =   1530
      TabIndex        =   18
      Top             =   1020
      Width           =   2655
   End
   Begin VB.TextBox txtSex 
      Height          =   285
      Left            =   1530
      TabIndex        =   17
      Top             =   1275
      Width           =   165
   End
   Begin VB.TextBox txtDateBirth 
      Height          =   285
      Left            =   1530
      TabIndex        =   16
      Top             =   1545
      Width           =   2640
   End
   Begin VB.TextBox txtIDFarmBirth 
      Height          =   285
      Left            =   1530
      TabIndex        =   15
      Top             =   1800
      Width           =   330
   End
   Begin VB.TextBox txtTypeBirth 
      Height          =   285
      Left            =   1530
      TabIndex        =   14
      Top             =   2070
      Width           =   165
   End
   Begin VB.TextBox txtIDSire 
      Height          =   285
      Index           =   0
      Left            =   1530
      TabIndex        =   13
      Top             =   2325
      Width           =   990
   End
   Begin VB.TextBox txtIDDam 
      Height          =   285
      Index           =   0
      Left            =   1530
      TabIndex        =   12
      Top             =   2595
      Width           =   990
   End
   Begin VB.TextBox txtDateDisp 
      Height          =   285
      Left            =   1530
      TabIndex        =   11
      Top             =   2850
      Width           =   2640
   End
   Begin VB.TextBox txtIDDispReas 
      Height          =   285
      Left            =   1530
      TabIndex        =   10
      Top             =   3120
      Width           =   330
   End
   Begin VB.TextBox txtRemark 
      Height          =   285
      Left            =   1530
      TabIndex        =   9
      Top             =   3390
      Width           =   3375
   End
   Begin VB.TextBox txtIDFarm 
      DataSource      =   "adoSheepGoat"
      Height          =   285
      Left            =   1530
      TabIndex        =   1
      Top             =   225
      Width           =   375
   End
   Begin VB.CommandButton cmdFindIDFarm 
      Caption         =   "Find"
      Height          =   285
      Left            =   2640
      TabIndex        =   2
      Top             =   225
      Width           =   1215
   End
   Begin VB.CommandButton cmdFindIDSheepGoat 
      Caption         =   "Find"
      Height          =   285
      Left            =   2640
      TabIndex        =   5
      Top             =   495
      Width           =   1215
   End
   Begin MSHierarchicalFlexGridLib.MSHFlexGrid MSHFlexGrid2 
      Bindings        =   "frmInvMat.frx":0000
      Height          =   1200
      Left            =   -315
      TabIndex        =   8
      Top             =   7010
      Width           =   5250
      _ExtentX        =   9260
      _ExtentY        =   2117
      _Version        =   393216
      FixedCols       =   0
      AllowUserResizing=   3
      DataMember      =   "InvMatMat"
      _NumberOfBands  =   1
      _Band(0).Cols   =   2
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDFarm:"
      Height          =   255
      Index           =   0
      Left            =   -315
      TabIndex        =   0
      Top             =   240
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDSheepGoat:"
      Height          =   255
      Index           =   1
      Left            =   -315
      TabIndex        =   3
      Top             =   510
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDBreedBase:"
      Height          =   255
      Index           =   2
      Left            =   -315
      TabIndex        =   6
      Top             =   765
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "BreedCross:"
      Height          =   255
      Index           =   3
      Left            =   -315
      TabIndex        =   28
      Top             =   1035
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Sex:"
      Height          =   255
      Index           =   4
      Left            =   -315
      TabIndex        =   27
      Top             =   1305
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "DateBirth:"
      Height          =   255
      Index           =   5
      Left            =   -315
      TabIndex        =   26
      Top             =   1575
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDFarmBirth:"
      Height          =   255
      Index           =   6
      Left            =   -315
      TabIndex        =   25
      Top             =   1830
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "TypeBirth:"
      Height          =   255
      Index           =   7
      Left            =   -315
      TabIndex        =   24
      Top             =   2100
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDSire:"
      Height          =   255
      Index           =   8
      Left            =   -315
      TabIndex        =   23
      Top             =   2370
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDDam:"
      Height          =   255
      Index           =   9
      Left            =   -315
      TabIndex        =   22
      Top             =   2640
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "DateDisp:"
      Height          =   255
      Index           =   10
      Left            =   -315
      TabIndex        =   21
      Top             =   2895
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "IDDispReas:"
      Height          =   255
      Index           =   11
      Left            =   -315
      TabIndex        =   20
      Top             =   3165
      Width           =   1815
   End
   Begin VB.Label lblFieldLabel 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Remark:"
      Height          =   255
      Index           =   12
      Left            =   -315
      TabIndex        =   19
      Top             =   3435
      Width           =   1815
   End
End
Attribute VB_Name = "frmInvMat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private objAnimal As New Animal
Private objFlockBookDB As New FlockBookDB

' Find the animal by the IDSheepGoat specified in the corresponding text
' box and fill the rest text boxes.
' Unless otherwise specified invoke no search and inform about the error.
Private Sub cmdFindIDSheepGoat_Click()
    ' Helps to type.
    txtIDSheepGoat.Item(1) = "¿¿0001"
    If txtIDSheepGoat.Item(1) = "" Then
        MsgBox "No ID specified. Retry again."
        txtIDSheepGoat.Item(1).SetFocus
    Else
        Set objAnimal = objFlockBookDB.ReturnAnimal(txtIDSheepGoat. _
        Item(1))
    End If
End Sub

' Initialise the global connection and command.
Private Sub Form_Load()
    GlobalConnSet
End Sub

' Destroy the global connection, objFlockBookDB, and objAnimal
Private Sub Form_Unload(Cancel As Integer)
'    Set gstrConn = Nothing
    GlobalConnDestr
End Sub
