VERSION 5.00
Begin VB.Form frmLogin 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Логин"
   ClientHeight    =   2490
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   3750
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1471.174
   ScaleMode       =   0  'User
   ScaleWidth      =   3521.047
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox txtPwd 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1080
      PasswordChar    =   "*"
      TabIndex        =   3
      Text            =   "Pwd02"
      Top             =   600
      Width           =   2565
   End
   Begin VB.TextBox txtServer 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   1080
      TabIndex        =   5
      Text            =   "89.237.250.26"
      Top             =   1080
      Width           =   2565
   End
   Begin VB.TextBox txtLogin 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      Left            =   1080
      TabIndex        =   1
      Text            =   "Login02"
      Top             =   135
      Width           =   2565
   End
   Begin VB.CheckBox chkSaveStng 
      Caption         =   "&Хранить личную информацию"
      Height          =   255
      Left            =   1080
      TabIndex        =   6
      Top             =   1560
      Width           =   2775
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "ОК"
      Default         =   -1  'True
      Height          =   390
      Left            =   375
      TabIndex        =   7
      Top             =   1980
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Отмена"
      Height          =   390
      Left            =   1980
      TabIndex        =   8
      Top             =   1980
      Width           =   1140
   End
   Begin VB.Label lblServer 
      Caption         =   "&Сервер:"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1125
      Width           =   720
   End
   Begin VB.Label lblLogin 
      Caption         =   "&Логин:"
      Height          =   225
      Left            =   105
      TabIndex        =   0
      Top             =   195
      Width           =   720
   End
   Begin VB.Label lblPwd 
      Caption         =   "&Пароль:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   645
      Width           =   720
   End
End
Attribute VB_Name = "frmLogin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const mstrStngLogin As String = "Login" 'The Windows registry seting section & keys.
Const mstrStngSaveStng As String = "SaveStng"
Const mstrStngPasswd As String = "Passwd"
Const mstrStngServer As String = "Server"
Const mbytStngCmdGet As Byte = 1 'The Get Windows registry record command constant.
Const mbytStngCmdDel As Byte = 2 'The Delete Windows registry record command constant.

Public Success As Boolean

'' Validate filling-out controls.
'Private Function ValidTxtBox(txtCtrl As TextBox, ByVal strLabel As String) As Boolean
'    If Len(Trim(txtCtrl)) <> 0 Then 'Login entered?
'        ValidTxtBox = True
'    Else
'        MsgBox "Заполните поле '" & strLabel & "'!"
'    End If
'End Function

' Validate filling-out controls.
Private Function ValidCtrl() As Boolean
    If Util.ValidTxtBox(txtLogin, "Логин") Then
        If Util.ValidTxtBox(txtPwd, "Пароль") Then
            If Util.ValidTxtBox(txtServer, "Сервер") Then
                ValidCtrl = True
            End If
        End If
    End If
End Function

' Validate filling-out controls.
Private Function PREV_ValidCtrl() As Boolean
'    If ValidTxtBox(txtLogin, "Логин") Then
'        If ValidTxtBox(txtPwd, "Пароль") Then
'            If ValidTxtBox(txtServer, "Сервер") Then
'                ValidCtrl = True
'            End If
'        End If
'    End If
End Function

' Set connection.
Private Function SetConn() As Boolean
On Error GoTo ErrHnd
'    Const strCnnStr As String = "Driver={MySQL ODBC 3.51 Driver};Port=3306;Server=localhost;Database=Broker;Uid=root;Pwd=130997"
    Const strCnnStr1Serv As String = "Driver={MySQL ODBC 3.51 Driver};Port=3306;Server="
    Const strCnnStr2 As String = ";Database=Broker;Uid=root;Pwd=130997"
    Const lngCnnTimeout As Long = 30
    Dim strCnnStr As String
    Set gcnnConnServ = New ADODB.Connection
    With gcnnConnServ 'Server-side connection.
        If .State = adStateOpen Then .Close 'Close to open again.
        .ConnectionTimeout = lngCnnTimeout
        .CursorLocation = adUseClient ' adUseServer
        .Open strCnnStr1Serv & Trim(txtServer) & strCnnStr2
    End With
    SetConn = True
Exit Function
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Function

' Validate the login & password.
'Private Function ValidLoginPwd() As Integer
Private Function IDAcc() As Integer
    Dim rstAccs As ADODB.Recordset
    Set rstAccs = New ADODB.Recordset
    With rstAccs
        .Open "Sel_Accs_ID('" & Trim$(txtLogin) & "', '" & Trim$(txtPwd) & "')", gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
        If .BOF = False And .EOF = False Then IDAcc = .Fields("ID") 'Any records?
    End With
End Function

' Validate the login & password.
Private Sub PREV_ValidLoginPwd()
'Private Function ValidLoginPwd() As Boolean
'    gcnnConnServ.Execute "Sel_Accs_ID('" & Trim$(Login) & "', '" & Trim$(Pwd) & "', " & intID & ")", , adCmdStoredProc + adExecuteNoRecords
'    If intID <> 0 Then ValidLoginPwd = True ' Any ID with the login & password provided?
    gcnnConnServ.Execute "Sel_Accs_ID('" & Trim$(txtLogin) & "', '" & Trim$(txtPwd) & "', " & gintIDAcc & ")", , adCmdStoredProc + adExecuteNoRecords
'    If gintIDAcc <> 0 Then ValidLoginPwd = True ' Any ID with the login & password provided?
End Sub

' Check the password, connect to the server.
Private Sub cmdOK_Click()
On Error GoTo ErrHnd
    If ValidCtrl() Then 'Validate filling-out controls.
        If SetConn() Then ' Connection set?
            gintIDAcc = IDAcc ' Validate the login & password.
            If gintIDAcc = 0 Then ' No ID with the login & password provided?
                MsgBox "Неверный пароль или имя пользователя! Повторите ввод." 'MsgBox "Invalid Password, try again!", , "Login"
                txtPwd.SetFocus
                SendKeys "{Home}+{End}"
            Else
                Success = True
                Me.Hide 'Unload Me
            End If
        End If
    End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Check the password, connect to the server.
Private Sub PREV_cmdOK_Click()
On Error GoTo ErrHnd
'    Const strPasswd As String = "Pwd"
'    If ValidCtrl() Then 'Validate filling-out controls.
'        If txtPwd <> strPasswd Then 'check for correct password
'            MsgBox "Неверный пароль! Повторите ввод." 'MsgBox "Invalid Password, try again!", , "Login"
'            txtPwd.SetFocus
'            SendKeys "{Home}+{End}"
'        Else
'            If SetConn() Then ' Connection set?
'                Success = True
'                Me.Hide 'Unload Me
'            End If
'        End If
'    End If
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

Private Sub cmdCancel_Click()
On Error GoTo ErrHnd
    Success = False 'set the global var to false to denote a failed login
    Unload Me
'   Me.Hide
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Get or delete the Login & Passwd from the Windows registry
Private Sub GetDeleteStng(ByVal bytStngCmd As Byte)
   Const intDimKey As Integer = 0 ' The Key array dimention.
   Const intDimStng As Integer = 1 ' The Setting array dimention.
   Dim vrnStng As Variant ' Variant to hold 2-dimensional array returned by GetAllSettings
   Dim intStng As Integer ' Integer to hold counter.
   vrnStng = GetAllSettings(App.ProductName, mstrStngLogin) ' Retrieve the settings.
   If Not IsEmpty(vrnStng) Then
      For intStng = LBound(vrnStng, intDimStng) To UBound(vrnStng, intDimStng)
         Select Case bytStngCmd
         Case mbytStngCmdDel
            Select Case vrnStng(intStng, intDimKey)
            Case mstrStngLogin, mstrStngPasswd
               DeleteSetting App.ProductName, mstrStngLogin, vrnStng(intStng, intDimKey)
            End Select
         Case mbytStngCmdGet
            Select Case vrnStng(intStng, intDimKey)
            Case mstrStngLogin
               txtLogin = GetSetting(App.ProductName, mstrStngLogin, mstrStngLogin)
            Case mstrStngPasswd
               txtPwd = GetSetting(App.ProductName, mstrStngLogin, mstrStngPasswd)
            End Select
         End Select
      Next
   End If
End Sub

' Get the saved values of the controls, if saved in the Windows registry.
Private Sub Form_Load()
On Error GoTo ErrHnd
    With App
        chkSaveStng = GetSetting(.ProductName, mstrStngLogin, mstrStngSaveStng, vbUnchecked)
'        txtServer = GetSetting(.ProductName, mstrStngLogin, mstrStngServer, "localhost")
         txtServer = GetSetting(.ProductName, mstrStngLogin, mstrStngServer, txtServer)
        Call GetDeleteStng(mbytStngCmdGet) ' Get the Login & Passwd from the Windows registry
    End With
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub

' Save the controls' values in the Windows registry.
Private Sub Form_Unload(Cancel As Integer)
On Error GoTo ErrHnd
   With App
      SaveSetting .ProductName, mstrStngLogin, mstrStngSaveStng, chkSaveStng
      SaveSetting .ProductName, mstrStngLogin, mstrStngServer, txtServer
      If chkSaveStng = vbChecked Then ' Save the account information?
         SaveSetting .ProductName, mstrStngLogin, mstrStngLogin, txtLogin
         SaveSetting .ProductName, mstrStngLogin, mstrStngPasswd, txtPwd
      Else ' Delete the account information.
         Call GetDeleteStng(mbytStngCmdDel) ' Delete the Login & Passwd from the Windows registry
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Number & vbTab & Err.Description
End Sub
