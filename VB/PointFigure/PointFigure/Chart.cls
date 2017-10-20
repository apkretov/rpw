VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Chart"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public FlPath As String
Public Symbol As String
Public FlDateCreated As Date
Public FlDateLastModified As Date
Public Incr As Integer
Public Revers As Integer
Public BoxSideSize As Single
Public ParamInputd As Boolean
Public TimeFst As String
Public TimeStep As Integer
Public CycleErr As Boolean 'The mark of cyclical errors that occur in cycles due to overlapping of the file reading simultaneous processes in all open frmChart forms. The mark is necessary to prevent from multiple error messages after the 1st error.

