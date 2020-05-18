VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "KTB_DecmSeparat"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim mstrDecmSeparat As String

Private Declare Function GetLocaleInfo Lib "kernel32" Alias "GetLocaleInfoA" (ByVal Locale As Long, ByVal LCType As Long, ByVal lpLCData As String, ByVal cchData As Long) As Long
Private Declare Function GetSystemDefaultLCID Lib "kernel32" () As Long

Public Property Get DecmSeparat() As String
   DecmSeparat = mstrDecmSeparat
End Property

' Call the function passing the Locale type variable to retrieve the required size of the string buffer needed
Private Function GetUserLocaleInfo(ByVal dwLocaleID As Long, ByVal dwLCType As Long) As String
   Dim sReturn As String
   Dim r As Long
   r = GetLocaleInfo(dwLocaleID, dwLCType, sReturn, Len(sReturn))
   If r Then 'If successful..
      sReturn = Space$(r) 'Pad the buffer with spaces
      r = GetLocaleInfo(dwLocaleID, dwLCType, sReturn, Len(sReturn)) 'and call again passing the buffer
      If r Then GetUserLocaleInfo = Left$(sReturn, r - 1) 'if successful (r > 0) r holds the size of the string including the terminating null
   End If
End Function

' Set the locale decimal separator.
Private Sub Class_Initialize()
   Const LOCALE_SDECIMAL As Long = &HE 'Decimal separator
   Dim LCID As Long
   LCID = GetSystemDefaultLCID()
   mstrDecmSeparat = GetUserLocaleInfo(LCID, LOCALE_SDECIMAL)
End Sub
