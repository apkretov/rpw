VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblShG"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Private Type TblShGTp
   IDFarm As String
   IDShG As String
   IDSex As String
   IDBrdBas As String
   Crs As Boolean
   BrdCrs As String
   DateBirth As Date
   IDFarmBirth As String
   TypeBirth As Integer
   IDSire As String
   IDDam As String
   DateDisp As Date
   IDDispReas As String
   Remark As String
End Type
Dim mudtTblShG As TblShGTp
Dim mudtTblShGOrig As TblShGTp

Dim mobSQLErrHnd As SQLErrHnd

Dim mobBrdCrses As BrdCrses
Dim mobBrdCrsesNew As BrdCrses
Dim mobTransFarms As TransFarms
Dim mobTransFarmsNew As TransFarms

Dim mintBrdCrsDen As Integer

Dim mstrIDBlankDB As String
Dim mblnEscIDShGWrng As Boolean
Dim mblnFull As Boolean

Public IDBrdBasNew As String
Public BrdCrsDenNew As Integer
Public PopltBrdCrs As Boolean
Public BrdCrsChand As Boolean
Public TransFarmChand As Boolean

' Original IDShG
Public Property Get IDShGOrig() As String
   IDShGOrig = mudtTblShGOrig.IDShG
End Property

' BreedCross
Public Property Let BrdCrs(ByVal strBrdCrs As String)
On Error GoTo ErrHnd
'Keep this conversion function, though it's wrong, if the pure breed is changed & the new
'  cross breed isn't saved.
'    mstrBrdCrs = IIf(strBrdCrs = "", mstrIDBrdBas, strBrdCrs)
    mudtTblShG.BrdCrs = strBrdCrs
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' BrdCrs
Public Property Get BrdCrs() As String
   BrdCrs = IIf(mudtTblShG.BrdCrs = mudtTblShG.IDBrdBas, "", mudtTblShG.BrdCrs)
End Property

' DateBirth
Public Property Let DateBirth(ByVal dtmDateBirth As Date)
   mudtTblShG.DateBirth = dtmDateBirth
End Property

' DateBirthOrig
Public Property Get DateBirthOrig() As Date
   DateBirthOrig = DateValue(mudtTblShGOrig.DateBirth)
End Property

' DateBirth
Public Property Get DateBirth() As Date
   DateBirth = DateValue(mudtTblShG.DateBirth)
End Property

' IDFarmBirth
Public Property Let IDFarmBirth(ByVal strIDFarmBirth As String)
   mudtTblShG.IDFarmBirth = IIf(strIDFarmBirth = "", "- ", strIDFarmBirth)
End Property

' Get IDFarmBirthOrig.
Public Property Get IDFarmBirthOrig() As String
   IDFarmBirthOrig = IIf(mudtTblShGOrig.IDFarmBirth = "- ", "", mudtTblShGOrig _
      .IDFarmBirth)
End Property

' IDFarmBirth
Public Property Get IDFarmBirth() As String
    IDFarmBirth = IIf(mudtTblShG.IDFarmBirth = "- ", "", mudtTblShG.IDFarmBirth)
End Property

' IDSire
Public Property Let IDSire(ByVal strIDSire As String)
  mudtTblShG.IDSire = IIf(strIDSire = "", mstrIDBlankDB, strIDSire)
End Property

' IDSireOrig
Public Property Get IDSireOrig() As String
   IDSireOrig = IIf(mudtTblShGOrig.IDSire = mstrIDBlankDB, "", mudtTblShGOrig.IDSire)
End Property

' IDSire
Public Property Get IDSire() As String
   IDSire = IIf(mudtTblShG.IDSire = mstrIDBlankDB, "", mudtTblShG.IDSire)
'   IDSire = IIf(mudtTblShG.IDSire = mstrIDBlankDB, gobFormtCtl.BlankIDText, mudtTblShG.IDSire)
End Property

' IDDam
Public Property Let IDDam(ByVal strIDDam As String)
   mudtTblShG.IDDam = IIf(strIDDam = "", mstrIDBlankDB, strIDDam)
End Property

' IDDam
Public Property Get IDDam() As String
   IDDam = IIf(mudtTblShG.IDDam = mstrIDBlankDB, "", mudtTblShG.IDDam)
End Property

' IDDamOrig
Public Property Get IDDamOrig() As String
   IDDamOrig = IIf(mudtTblShGOrig.IDDam = mstrIDBlankDB, "", mudtTblShGOrig.IDDam)
End Property

' DateDisp
Public Property Let DateDisp(ByVal dtmDateDisp As Date)
    mudtTblShG.DateDisp = dtmDateDisp
End Property

' DateDisp
Public Property Get DateDisp() As Date
   DateDisp = IIf(mudtTblShG.DateDisp = 0, 0, DateValue(mudtTblShG.DateDisp))
End Property

' DateDispOrig
Public Property Get DateDispOrig() As Date
   DateDispOrig = IIf(mudtTblShGOrig.DateDisp = 0, 0, DateValue(mudtTblShGOrig.DateDisp))
End Property

' IDDispReas
Public Property Let IDDispReas(ByVal strIDDispReas As String)
    mudtTblShG.IDDispReas = IIf(strIDDispReas = "", "- ", strIDDispReas)
End Property

' IDDispReas
Public Property Get IDDispReas() As String
    IDDispReas = IIf(mudtTblShG.IDDispReas = "- ", "", mudtTblShG.IDDispReas)
End Property

' Remark
Public Property Let Remark(ByVal strRemark As String)
    mudtTblShG.Remark = IIf(strRemark = "", "-", strRemark)
End Property

' Remark
Public Property Get Remark() As String
    Remark = IIf(mudtTblShG.Remark = "-", "", mudtTblShG.Remark)
End Property

' Initialise new module level objects.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
   Set mobBrdCrses = New BrdCrses
   Set mobBrdCrsesNew = New BrdCrses
   Set mobTransFarms = New TransFarms
   Set mobTransFarmsNew = New TransFarms
   Set mobSQLErrHnd = New SQLErrHnd
   mstrIDBlankDB = "-" & Space$(gobFormtCtl.LengIDShG - 1) 'Blank ID's with & w/o a
Exit Sub                                           'hyphen for the application & DB.
ErrHnd:
MsgBox Err.Description
End Sub

' Add a new sheep/goat to the ShG table.
' Mark an error for later reference, if occurs.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim intCrossed As Integer
   Dim strDateBirth As String
   Dim strDateDisp As String
   intCrossed = IIf(mudtTblShG.Crs, 1, 0)
   strDateBirth = Util.DateStrDB(mudtTblShG.DateBirth) 'Convert dates to strings.
   strDateDisp = IIf(mudtTblShG.DateDisp = 0, " ", Util.DateStrDB(mudtTblShG.DateDisp))
   strCmdTxt = "spInsert_SheepGoat_Object('" & mudtTblShG.IDFarm & "', '" & mudtTblShG _
      .IDShG & "', '" & mudtTblShG.IDSex & "', '" & mudtTblShG.IDBrdBas & "', " & _
      intCrossed & ", '" & mudtTblShG.BrdCrs & "', '" & strDateBirth & "','" & _
      mudtTblShG.IDFarmBirth & "', " & mudtTblShG.TypeBirth & ", '" & mudtTblShG.IDSire _
      & "', '" & mudtTblShG.IDDam & "', '" & strDateDisp & "', '" & mudtTblShG _
      .IDDispReas & "', '" & mudtTblShG.Remark & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = True 'Mark full.
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Delete the current record from the ShG table.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   strCmdTxt = "spDelete_SheepGoat_IDShG('" & mudtTblShGOrig.IDShG & "')"
   gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
   mblnFull = False 'Mark empty.
   Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Get the TblShG object's data from SheepGoat.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim strIDShG As String
   Dim rstShG As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstShG = New ADODB.Recordset
   strIDShG = vntKeys(0)
   strCmdTxt = "spSheepGoat_IDShG('" & strIDShG & "')" 'Set the specified animal's the ShG
   With rstShG                                 'recordset.
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .EOF And .BOF Then 'Give feedback on whether IDSeepGoat found.
         mblnFull = False 'Mark empty.
         If Not mblnEscIDShGWrng Then 'Message, unless escaped.
            MsgBox LoadResString(322) & strIDShG & LoadResString(183), vbExclamation, _
               LoadResString(172)
         Else
            mblnEscIDShGWrng = False 'Reset.
         End If
      Else
         With .Fields 'Define the animal's data from the ShG recordset.
            mudtTblShG.IDFarm = .Item("IDFarm")
            mudtTblShG.IDShG = .Item("IDSheepGoat")
            mudtTblShG.IDBrdBas = .Item("IDBreedBase")
            mudtTblShG.Crs = .Item("Crossed")
            mudtTblShG.BrdCrs = .Item("BreedCross")
            mudtTblShG.IDSex = .Item("IDSex")
            mudtTblShG.DateBirth = .Item("DateBirth")
            mudtTblShG.IDFarmBirth = .Item("IDFarmBirth")
            mudtTblShG.TypeBirth = .Item("TypeBirth")
            mudtTblShG.IDSire = .Item("IDSire")
            mudtTblShG.IDDam = .Item("IDDam")
            mudtTblShG.DateDisp = IIf(.Item("DateDisp") = gobSetng.SQLDateZero, 0, .Item( _
               "DateDisp")) 'Hide a null disposal date which is stored in the data base as
            mudtTblShG.IDDispReas = .Item("IDDispReas")                        '01.01.1900.
            mudtTblShG.Remark = .Item("Remark")
         End With
         Call OrigSave 'Save original data.
         mblnFull = True 'Mark full.
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the form's content to the DB.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim intCrossed As Integer
   Dim strDateBirth As String
   Dim strDateDisp As String
   If Not OrigCompr Then
      intCrossed = IIf(mudtTblShG.Crs, 1, 0)
      strDateBirth = Util.DateStrDB(mudtTblShG.DateBirth)
      strDateDisp = IIf(mudtTblShG.DateDisp = 0, " ", Util.DateStrDB(mudtTblShG.DateDisp))
      strCmdTxt = "spUpdate_SheepGoat_IDShG('" & mudtTblShGOrig.IDShG & "', '" & _
         mudtTblShG.IDFarm & "', '" & mudtTblShG.IDShG & "', '" & mudtTblShG.IDSex & _
         "', '" & mudtTblShG.IDBrdBas & "', " & intCrossed & ", '" & mudtTblShG.BrdCrs _
         & "','" & strDateBirth & "', '" & mudtTblShG.IDFarmBirth & "', " & mudtTblShG _
         .TypeBirth & ", '" & mudtTblShG.IDSire & "', '" & mudtTblShG.IDDam & "', '" & _
         strDateDisp & "', '" & mudtTblShG.IDDispReas & "', '" & mudtTblShG.Remark & "')"
      gcnnConnServ.Execute strCmdTxt, , adCmdStoredProc + adExecuteNoRecords
      Call Util.RefrshSetng(False) 'Refresh the settings forms but not frmBrsShG's tree.
   End If
Exit Sub
ErrHnd:
   mobSQLErrHnd.KeyPrim Err.Description
End Sub

' Count the sire's offpsrings in the SheepGoat table by counting its ID in the IDSire
'  field.
Public Function CountSrOffsp(ByVal strIDSire As String) As Long
On Error GoTo ErrHnd
   Dim rstShG As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstShG = New ADODB.Recordset
   strCmdTxt = "spCount_SheepGoat_IDSire('" & strIDSire & "')"
   With rstShG
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .BOF = False And .EOF = False Then CountSrOffsp = .Fields("CountIDSire")
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Count the dam's offpsrings in the SheepGoat table by counting its ID in the IDDam
'  field.
Public Function CountDmOffsp(ByVal strIDDam As String) As Long
On Error GoTo ErrHnd
   Dim rstShG As ADODB.Recordset
   Dim strCmdTxt As String
   Set rstShG = New ADODB.Recordset
   strCmdTxt = "spCount_SheepGoat_IDDam('" & strIDDam & "')"
   With rstShG
      .Open strCmdTxt, gcnnConnServ, adOpenDynamic, adLockOptimistic, adCmdStoredProc
      If .BOF = False And .EOF = False Then CountDmOffsp = .Fields("CountIDDam")
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Build in & link to the BrdCrses collection object into the ShG object.
Public Property Get BrdCrses() As BrdCrses
   Set BrdCrses = mobBrdCrses
End Property

' Build in & link to the  BrdCrsesNew collection object into the ShG object.
Public Property Get BrdCrsesNew() As BrdCrses
    Set BrdCrsesNew = mobBrdCrsesNew
End Property

' Save the new cross breeds' composition to insert them laster into the BreedCross table.
Public Sub BrdCrsSaveNew(ByVal strIDBrd As String, ByVal intBrdNum As Integer, ByVal _
   intBrdDen As Integer)
On Error GoTo ErrHnd
   mobBrdCrsesNew.Add strIDBrd, intBrdNum, intBrdDen
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the ShG object's cross breed denominator, if its breed is crossed.
' The denominator is set in the BrdCrsSel method.
Public Property Get BrdCrsDen() As Integer
    BrdCrsDen = mintBrdCrsDen
End Property

' Reset the mobBrdCrsesNew collection object to prepare it for adding new cross breeds.
Public Sub BrdCrsResetNew()
On Error GoTo ErrHnd
    Set mobBrdCrsesNew = Nothing
    Set mobBrdCrsesNew = New BrdCrses
    mobBrdCrsesNew.IDShG = mudtTblShG.IDShG
    BrdCrsChand = False
    IDBrdBasNew = ""
    BrdCrsDenNew = 0
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the previous cross breeds' composition from the BreedCross table.
Public Sub BrdCrsDel()
On Error GoTo ErrHnd
    Dim obTblBrdCrs As TblBrdCrs
    Dim obDatTbl As DatTbl
    ' Delete the previous cross breeds.
    For Each obTblBrdCrs In mobBrdCrses
        Set obDatTbl = obTblBrdCrs
        obDatTbl.Del
    Next obTblBrdCrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert the new cross breeds' composition into the BreedCross table.
Public Sub BrdCrsInsNew()
On Error GoTo ErrHnd
    Dim obTblBrdCrs As TblBrdCrs
    Dim obDatTbl As DatTbl
    ' Insert the new cross breeds.
    For Each obTblBrdCrs In mobBrdCrsesNew
        Set obDatTbl = obTblBrdCrs
        obDatTbl.Ins
    Next obTblBrdCrs
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Create a new breed cross code.
' Place the basic breed first.
' If there are no cross breeds in the mobBrdCrsesNew collection return a zero-length
'  string.
Public Function BrdCrsNew() As String
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   Dim strBrdCrs As String
   If mobBrdCrsesNew.Count > 0 Then
      strBrdCrs = BrdCrsBase 'Place the basic breed first.
      For Each obTblBrdCrs In mobBrdCrsesNew
         With obTblBrdCrs
            If .Occupied = False Then strBrdCrs = strBrdCrs & "-" & .IDBrd & _
               CStr(.BrdNum) & gobSetng.BrdCrsSlash & CStr(.BrdDen) 'Add the rest unoccupied shares.
         End With
      Next
      BrdCrsNew = strBrdCrs
   End If
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Place the basic breed first in the BreedCross code.
Private Function BrdCrsBase() As String
On Error GoTo ErrHnd
   Dim obTblBrdCrs As TblBrdCrs
   For Each obTblBrdCrs In mobBrdCrsesNew 'Cycle through cross breeds to find the
      With obTblBrdCrs                        'basic breed, occupy to place first.
         If .IDBrd = IDBrdBasNew Then
            .Occupied = True
            BrdCrsBase = .IDBrd & CStr(.BrdNum) & gobSetng.BrdCrsSlash & CStr(.BrdDen)
            Exit For
         End If
      End With
   Next
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get the mobBrdCrses collection's data for the frmBrdCrs form in the Edit mode.
' Set the cross breeds' denominator. Despite unacceptable if the cross breeds'
'  denominators defer set the overall denominator equal to the maximal.
Public Sub BrdCrsSel()
On Error GoTo ErrHnd
    Dim obTblBrdCrs As TblBrdCrs
    Dim obDatTbl As DatTbl
    Dim obKeys As Keys
    Dim obKey As Key
    Set obTblBrdCrs = New TblBrdCrs
    'Get the primary keys values for the BreedCross table to fill the mobBrdCrses
    ' collection.
    Set obKeys = obTblBrdCrs.GetKeys(mudtTblShG.IDShG)
    Set obDatTbl = obTblBrdCrs
    For Each obKey In obKeys
        With obKey
            obDatTbl.Sel .Key0, .Key1
        End With
        With obTblBrdCrs
            mobBrdCrses.Add .IDBrd, .BrdNum, .BrdDen
            If mintBrdCrsDen < .BrdDen Then mintBrdCrsDen = .BrdDen
        End With
    Next obKey
    ' Mark cross breeds populated.
    PopltBrdCrs = True
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Build in & link to the TransFarms collection object into the ShG object.
Public Property Get TransFarms() As TransFarms
    Set TransFarms = mobTransFarms
End Property

' Build in & link to the  TransFarmsNew collection object into the ShG object.
Public Property Get TransFarmsNew() As TransFarms
    Set TransFarmsNew = mobTransFarmsNew
End Property

' Save the new transer farms to insert them later into the TransFarm table.
' Set the mblnTransFarmChand mark to True.
Public Sub TransFarmSaveNew(ByVal dtmDateTrans As Date, ByVal strIDFarm As String)
On Error GoTo ErrHnd
    mobTransFarmsNew.Add dtmDateTrans, strIDFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mobTransFarms collection's data for the frmTransFarm form.
Public Sub TransFarmSel()
On Error GoTo ErrHnd
    Dim obTblTransFarm As TblTransFarm
    Dim obDatTbl As DatTbl
    Dim obKeys As Keys
    Dim obKey As Key
    Set obTblTransFarm = New TblTransFarm
    ' Get the primary keys values for the TransFarm table to fill the
    '   mobTransFarms collection.
    Set obKeys = obTblTransFarm.GetKeys(mudtTblShG.IDShG)
    For Each obKey In obKeys
        Set obDatTbl = obTblTransFarm
        With obKey
            obDatTbl.Sel .Key0, , , , .Key4
        End With
        With obTblTransFarm
            mobTransFarms.Add .DateTrans, .IDFarm
        End With
    Next obKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Reset the mobTransFarmsNew collection object to prepare it for adding new farm
'  transfers.
Public Sub TransFarmResetNew()
On Error GoTo ErrHnd
    Set mobTransFarmsNew = Nothing
    Set mobTransFarmsNew = New TransFarms
    mobTransFarmsNew.IDShG = mudtTblShG.IDShG
    TransFarmChand = False
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the previous farm transfers from the TransFarm table.
Public Sub TransFarmDel()
On Error GoTo ErrHnd
    Dim obTblTransFarm As TblTransFarm
    Dim obDatTbl As DatTbl
    ' Delete the previous farm transfers.
    For Each obTblTransFarm In mobTransFarms
        Set obDatTbl = obTblTransFarm
        obDatTbl.Del
    Next obTblTransFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert a new farm transfer into the TransFarm table.
Public Sub TransFarmInsNew()
On Error GoTo ErrHnd
    Dim obTblTransFarm As TblTransFarm
    Dim obDatTbl As DatTbl
    ' Insert the new farm transfer.
    For Each obTblTransFarm In mobTransFarmsNew
        Set obDatTbl = obTblTransFarm
        obDatTbl.Ins
    Next obTblTransFarm
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

Rem Likewise substitute the majority of messages from gobMsgInst.
' Cancel the IDShGWrong message.
Public Property Let EscIDShGWrng(ByVal blnEscIDShGWrng As Boolean)
   mblnEscIDShGWrng = blnEscIDShGWrng
End Property

' Compare this object's original data with the current.
' Return True, if the two are equal.
Private Function OrigCompr() As Boolean
On Error GoTo ErrHnd
   With mudtTblShGOrig
      If .IDFarm = mudtTblShG.IDFarm Then
         If .IDShG = mudtTblShG.IDShG Then
            If .IDSex = mudtTblShG.IDSex Then
               If .IDBrdBas = mudtTblShG.IDBrdBas Then
                  If .Crs = mudtTblShG.Crs Then
                     If .BrdCrs = mudtTblShG.BrdCrs Then
                        If .DateBirth = mudtTblShG.DateBirth Then
                           If .IDFarmBirth = mudtTblShG.IDFarmBirth Then
                              If .TypeBirth = mudtTblShG.TypeBirth Then
                                 If .IDSire = mudtTblShG.IDSire Then
                                    If .IDDam = IDDam Then
                                       If .DateDisp = mudtTblShG.DateDisp Then
                                          If .IDDispReas = mudtTblShG.IDDispReas Then
                                             If .Remark = mudtTblShG.Remark Then OrigCompr = _
                                                True 'Equal.
                                          End If
                                       End If
                                    End If
                                 End If
                              End If
                           End If
                        End If
                     End If
                  End If
               End If
            End If
         End If
      End If
   End With
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Save the original data after selecting.
Private Sub OrigSave()
On Error GoTo ErrHnd
   With mudtTblShGOrig
      .IDFarm = mudtTblShG.IDFarm
      .IDShG = mudtTblShG.IDShG
      .IDSex = mudtTblShG.IDSex
      .IDBrdBas = mudtTblShG.IDBrdBas
      .Crs = mudtTblShG.Crs
      .BrdCrs = mudtTblShG.BrdCrs
      .DateBirth = mudtTblShG.DateBirth
      .IDFarmBirth = mudtTblShG.IDFarmBirth
      .TypeBirth = mudtTblShG.TypeBirth
      .IDSire = mudtTblShG.IDSire
      .IDDam = IDDam
      .DateDisp = mudtTblShG.DateDisp
      .IDDispReas = mudtTblShG.IDDispReas
      .Remark = mudtTblShG.Remark
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get IDShG.
Public Property Get IDShG() As String
   IDShG = mudtTblShG.IDShG
End Property

' Let IDShG in this class & in its inbuilt ones.
Public Property Let IDShG(ByVal strIDShG As String)
On Error GoTo ErrHnd
   mudtTblShG.IDShG = strIDShG
   mobBrdCrses.IDShG = strIDShG
   mobBrdCrsesNew.IDShG = strIDShG
   mobTransFarms.IDShG = strIDShG
   mobTransFarmsNew.IDShG = strIDShG
Exit Property
ErrHnd:
MsgBox Err.Description
End Property

' Get IDFarmOrig.
Public Property Get IDFarmOrig() As String
   IDFarmOrig = mudtTblShGOrig.IDFarm
End Property

' Get IDFarm.
Public Property Get IDFarm() As String
   IDFarm = mudtTblShG.IDFarm
End Property

' Let IDFarm.
Public Property Let IDFarm(ByVal strIDFarm As String)
   mudtTblShG.IDFarm = strIDFarm
End Property

' Get IDSexOrig.
Public Property Get IDSexOrig() As String
   IDSexOrig = mudtTblShGOrig.IDSex
End Property

' Get IDSex.
Public Property Get IDSex() As String
   IDSex = mudtTblShG.IDSex
End Property

' Let IDSex.
Public Property Let IDSex(ByVal strIDSex As String)
   mudtTblShG.IDSex = strIDSex
End Property

' Get IDBrdBasOrig.
Public Property Get IDBrdBasOrig() As String
   IDBrdBasOrig = mudtTblShGOrig.IDBrdBas
End Property

' Get IDBrdBas.
Public Property Get IDBrdBas() As String
   IDBrdBas = mudtTblShG.IDBrdBas
End Property

' Let IDBrdBas.
Public Property Let IDBrdBas(ByVal strIDBrdBas As String)
   mudtTblShG.IDBrdBas = strIDBrdBas
End Property

' Get Crs.
Public Property Get Crs() As Boolean
   Crs = mudtTblShG.Crs
End Property

' Let Crs.
Public Property Let Crs(ByVal blnCrs As Boolean)
   mudtTblShG.Crs = blnCrs
End Property

' Get TypeBirth.
Public Property Get TypeBirth() As Integer
   TypeBirth = mudtTblShG.TypeBirth
End Property

' Let TypeBirth.
Public Property Let TypeBirth(ByVal intTypeBirth As Integer)
   mudtTblShG.TypeBirth = intTypeBirth
End Property

' Full record mark.
Public Property Get Full() As Boolean
   Full = mblnFull
End Property

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

