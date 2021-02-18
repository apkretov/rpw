VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TblAppr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements DatTbl

Dim mobInhertDefcts As InhertDefcts
Dim mobSQLErrHnd As SQLErrHnd

Dim mstrIDShG As String
Dim mintAge As Integer
Dim mstrDiam As String
Dim mstrMass As String
Dim mstrCrimpins As String
Dim mstrEvens As String
Dim mstrStrength As String
Dim mstrIDColour As String
Dim mstrColour As String
Dim mstrQuality As String
Dim mstrIDFluffColour As String
Dim mstrFluffColour As String
Dim mstrBodyType As String
Dim mstrConstitutn As String
Dim mstrBodySize As String
Dim mstrFatTail As String

Public AgeOrig As Integer
Public DateAppr As Date
Public Leng As Single
Public Density As Integer
Public Fluff As Integer
Public FibreYield As Integer

' Let & get BodySize.
Public Property Let BodySize(ByVal strBodySize As String)
    mstrBodySize = IIf(strBodySize = "", "-", strBodySize)
End Property

Public Property Get BodySize() As String
   BodySize = IIf(mstrBodySize = "-", "", mstrBodySize)
End Property

' Let & get BodyType.
Public Property Let BodyType(ByVal strBodyType As String)
    mstrBodyType = IIf(strBodyType = "", "-", strBodyType)
End Property

Public Property Get BodyType() As String
    BodyType = IIf(mstrBodyType = "-", "", mstrBodyType)
End Property

' Let & get Constitutn.
Public Property Let Constitutn(ByVal strConstitutn As String)
    mstrConstitutn = IIf(strConstitutn = "", "-", strConstitutn)
End Property

Public Property Get Constitutn() As String
    Constitutn = IIf(mstrConstitutn = "-", "", mstrConstitutn)
End Property

' Let & get FatTail.
Public Property Let FatTail(ByVal strFatTail As String)
    mstrFatTail = IIf(strFatTail = "", "-", strFatTail)
End Property

Public Property Get FatTail() As String
    FatTail = IIf(mstrFatTail = "-", "", mstrFatTail)
End Property

' Let & get Diam.
Public Property Let Diam(ByVal strDiam As String)
   mstrDiam = IIf(strDiam = "", "-", strDiam)
End Property

Public Property Get Diam() As String
   Diam = IIf(mstrDiam = "-", "", mstrDiam)
End Property

' Let & get Mass.
Public Property Let Mass(ByVal strMass As String)
   mstrMass = IIf(strMass = "", "-", strMass)
End Property

Public Property Get Mass() As String
   Mass = IIf(mstrMass = "-", "", mstrMass)
End Property

' Let & get Strength.
Public Property Let Strength(ByVal strStrength As String)
    mstrStrength = IIf(strStrength = "", "-", strStrength)
End Property

Public Property Get Strength() As String
    Strength = IIf(mstrStrength = "-", "", mstrStrength)
End Property

' Let & get Crimpins.
Public Property Let Crimpins(ByVal strCrimpins As String)
    mstrCrimpins = IIf(strCrimpins = "", "-", strCrimpins)
End Property

Public Property Get Crimpins() As String
    Crimpins = IIf(mstrCrimpins = "-", "", mstrCrimpins)
End Property

' Let & get Evens.
Public Property Let Evens(ByVal strEvens As String)
    mstrEvens = IIf(strEvens = "", "-", strEvens)
End Property

Public Property Get Evens() As String
    Evens = IIf(mstrEvens = "-", "", mstrEvens)
End Property

' Let & get Quality.
Public Property Let Quality(ByVal strQuality As String)
    mstrQuality = IIf(strQuality = "", "-", strQuality)
End Property

Public Property Get Quality() As String
    Quality = IIf(mstrQuality = "-", "", mstrQuality)
End Property

' Let & get IDColour.
Public Property Let IDColour(ByVal strIDColour As String)
   mstrIDColour = IIf(strIDColour = "", "-", strIDColour)
End Property

Public Property Get IDColour() As String
   IDColour = IIf(mstrIDColour = "-", "", mstrIDColour)
End Property

' Let & get Colour.
Public Property Let Colour(ByVal strColour As String)
   mstrColour = IIf(strColour = "", "-", strColour)
End Property

Public Property Get Colour() As String
   Colour = IIf(mstrColour = "-", "", mstrColour)
End Property

' Let & get IDFluffColour.
Public Property Let IDFluffColour(ByVal strIDFluffColour As String)
    mstrIDFluffColour = IIf(strIDFluffColour = "", "-", strIDFluffColour)
End Property

Public Property Get IDFluffColour() As String
    IDFluffColour = IIf(mstrIDFluffColour = "-", "", mstrIDFluffColour)
End Property

' Let & get FluffColour.
Public Property Let FluffColour(ByVal strFluffColour As String)
   mstrFluffColour = IIf(strFluffColour = "", "-", strFluffColour)
End Property

Public Property Get FluffColour() As String
    FluffColour = IIf(mstrFluffColour = "-", "", mstrFluffColour)
End Property

'' Set the source of the data for the class.
'Private Sub Class_GetDataMember(DataMember As String, Data As Object)
'On Error GoTo ErrHnd
'   Set Data = mrstAppr
'Exit Sub
'ErrHnd:
'MsgBox Err.Description
'End Sub

' Initialise new module level objects.
Private Sub Class_Initialize()
On Error GoTo ErrHnd
'    Set mrstAppr = New ADODB.Recordset
    Set mobInhertDefcts = New InhertDefcts
    Set mobSQLErrHnd = New SQLErrHnd
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Delete the current record from the Appraisal table.
' Prior to the deletion, delete the dependent defects from the InhertDefect tablle.
Private Sub DatTbl_Del()
On Error GoTo ErrHnd
    Dim strCmdTxt As String
    strCmdTxt = "DELETE FROM Appraisal WHERE IDSheepGoat = '" & IDShG & "' AND Age = " _
      & Age
    gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Add a new apprailsal to the Appraisal table.
' After a successful insertion, insert the dependent defects to the InhertDefect tablle.
' On an error in inserting the defect, roll back inserting the appraisal.
Private Sub DatTbl_Ins()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateAppr As String
   strDateAppr = Util.DateStrDB(DateAppr) 'Convert DateAppr to a string.
   strCmdTxt = "INSERT INTO Appraisal (IDSheepGoat, Age, DateAppr, Leng, Diam, Mass, " & _
      "Crimpins, Evens, Density, Strength, IDColour, Quality, IDFluffColour, Fluff, " & _
      "FibreYield, BodyType, Constitutn, BodySize, FatTail) " & _
      "VALUES ('" & IDShG & "', " & Age & ", '" & strDateAppr & "', " & IIf(Leng = 0, _
         gobSetng.NullStr, Util.NumStrDB(Leng)) & ", '" & mstrDiam & "', '" & mstrMass & "', '" _
         & mstrCrimpins & "', '" & mstrEvens & "', " & IIf(Density = 0, gobSetng _
         .NullStr, CStr(Density)) & ", '" & mstrStrength & "', '" & mstrIDColour & _
         "', '" & mstrQuality & "', '" & mstrIDFluffColour & "', " & IIf(Fluff = 0, _
         gobSetng.NullStr, CStr(Fluff)) & ", " & IIf(FibreYield = 0, gobSetng.NullStr, _
         CStr(FibreYield)) & ", '" & mstrBodyType & "', '" & mstrConstitutn & "', '" & _
         mstrBodySize & "', '" & mstrFatTail & "')"
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   Call InhertDefctIns 'Insert the defects.
   Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

Private Function DatTbl_OrigCompr() As Boolean
'If necessary modify the code to use this procedure.
End Function

Private Sub DatTbl_OrigSave()
'If necessary modify the code to use this procedure.
End Sub

' Select data from the Appraisal table.
Private Sub DatTbl_Sel(ParamArray vntKeys() As Variant)
On Error GoTo ErrHnd
   Dim rstAppr As ADODB.Recordset
   Dim strCmdTxt As String
   Dim strIDShG As String
   Dim intAge As Integer
   strIDShG = vntKeys(0)
   intAge = vntKeys(2)
   strCmdTxt = "SELECT Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, Appraisal.Density, Appraisal.Strength, Appraisal.IDColour, WlGrsColour.Colour, Appraisal.Quality, Appraisal.IDFluffColour, FluffColour.FluffColour, Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail FROM FluffColour INNER JOIN (WlGrsColour INNER JOIN Appraisal ON WlGrsColour.IDColour = Appraisal.IDColour) ON FluffColour.IDFluffColour = Appraisal.IDFluffColour " & _
      "WHERE IDSheepGoat = '" & strIDShG & "' AND Age = " & intAge
'   strCmdTxt = "SELECT Appraisal.IDSheepGoat, Appraisal.Age, Appraisal.DateAppr, Appraisal.Leng, Appraisal.Diam, Appraisal.Mass, Appraisal.Crimpins, Appraisal.Evens, Appraisal.Density, Appraisal.Strength, Appraisal.IDColour, WlGrsColour.Colour, Appraisal.Quality, Appraisal.IDFluffColour, FluffColour.FluffColour, Appraisal.Fluff, Appraisal.FibreYield, Appraisal.BodyType, Appraisal.Constitutn, Appraisal.BodySize, Appraisal.FatTail FROM Appraisal INNER JOIN WlGrsColour ON Appraisal.IDColour = WlGrsColour.IDColour INNER JOIN FluffColour ON Appraisal.IDFluffColour = FluffColour.IDFluffColour " & _
      "WHERE IDSheepGoat = '" & strIDShG & "' AND Age = " & intAge
   Set rstAppr = New ADODB.Recordset 'Set the recordset.
   With rstAppr
      .Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic, adCmdText
      If .EOF And .BOF Then
         gobMsgInst.NoApprSnd frmMDI.ActiveForm 'Give feedback about missing appraisal.
      Else
         With .Fields 'Define the animal's data from the Appraisal recordset.
            mstrIDShG = .Item("IDSheepGoat")
            AgeOrig = .Item("Age")
            mintAge = .Item("Age")
            DateAppr = .Item("DateAppr")
            Leng = IIf(IsNull(.Item("Leng")), 0, .Item("Leng"))
            mstrDiam = .Item("Diam")
            mstrMass = .Item("Mass")
            mstrCrimpins = .Item("Crimpins")
            mstrEvens = .Item("Evens")
            Density = IIf(IsNull(.Item("Density")), 0, .Item("Density"))
            mstrStrength = .Item("Strength")
            mstrIDColour = .Item("IDColour")
            mstrColour = .Item("Colour")
            mstrQuality = .Item("Quality")
            mstrIDFluffColour = .Item("IDFluffColour")
            mstrFluffColour = .Item("FluffColour")
            Fluff = IIf(IsNull(.Item("Fluff")), 0, .Item("Fluff"))
            FibreYield = IIf(IsNull(.Item("FibreYield")), 0, .Item("FibreYield"))
            mstrBodyType = .Item("BodyType")
            mstrConstitutn = .Item("Constitutn")
            mstrBodySize = .Item("BodySize")
            mstrFatTail = .Item("FatTail")
         End With
      End If
   End With
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Update the Appraisal table.
' After a successful updating, insert, update, or delete dependent
'   defects in the InhertDefect tablle.
Private Sub DatTbl_Upd()
On Error GoTo ErrHnd
   Dim strCmdTxt As String
   Dim strDateAppr As String
   strDateAppr = Util.DateStrDB(DateAppr) 'Convert DateAppr to a string.
   strCmdTxt = "UPDATE Appraisal SET DateAppr = '" & strDateAppr & "', Leng = " & IIf( _
      Leng = 0, gobSetng.NullStr, Util.NumStrDB(Leng)) & ", Diam = '" & mstrDiam & _
      "', Mass = '" & mstrMass & "', Crimpins = '" & mstrCrimpins & "', Evens = '" & _
      mstrEvens & "', Density = " & IIf(Density = 0, gobSetng.NullStr, Util.NumStrDB( _
      Density)) & ", Strength = '" & mstrStrength & "', IDColour = '" & mstrIDColour & _
      "', Quality = '" & mstrQuality & "', IDFluffColour = '" & mstrIDFluffColour & _
      "', Fluff = " & IIf(Fluff = 0, gobSetng.NullStr, Util.NumStrDB(Fluff)) & _
      ", FibreYield = " & IIf(FibreYield = 0, gobSetng.NullStr, Util.NumStrDB( _
      FibreYield)) & ", BodyType = '" & mstrBodyType & "', Constitutn = '" & _
      mstrConstitutn & "', BodySize = '" & mstrBodySize & "', FatTail = '" & _
      mstrFatTail & "' " & _
      "WHERE IDSheepGoat = '" & IDShG & "' AND Age = " & Age
   gcnnConn.Execute strCmdTxt, , adCmdText + adExecuteNoRecords
   Call InhertDefctUpd
Exit Sub
ErrHnd:
   mobSQLErrHnd.Genrl Err.Description
End Sub

' Build in & link to the InhertDefcts collection object into the
'   obTblAppr object.
Public Property Get InhertDefcts() As InhertDefcts
    Set InhertDefcts = mobInhertDefcts
End Property

' Insert all obTblInhertDefct objects from the mobInhertDefcts
'   collection into the InhertDefct table.
Public Sub InhertDefctIns()
On Error GoTo ErrHnd
   Dim obDatTbl As DatTbl
   Dim obTblInhertDefct As TblInhertDefct
   For Each obTblInhertDefct In mobInhertDefcts 'Insert each obTblInhertDefct.
      Set obDatTbl = obTblInhertDefct
      obDatTbl.Ins
   Next obTblInhertDefct
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Get the mobInhertDefcts collection for the frmAppr form.
Public Sub InhertDefctSel()
On Error GoTo ErrHnd
   Dim obTblInhertDefct As TblInhertDefct
   Dim obDatTbl As DatTbl
   Dim obKeys As Keys
   Dim obKey As Key
   Set obTblInhertDefct = New TblInhertDefct
   Set obKeys = obTblInhertDefct.GetKeys(IDShG, Age) 'Get the primary keys values for the
   For Each obKey In obKeys  'InhertDefect table to fill the mobInhertDefcts collection.
      Set obDatTbl = obTblInhertDefct
      With obKey
         obDatTbl.Sel .Key0, , .Key2, .Key3
      End With
      With obTblInhertDefct
         mobInhertDefcts.Add .IDDefctOrig, .IDDefct, .Defct
      End With
   Next obKey
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Insert, update, or delete the dependent defects in the InhertDefct
'   tablle.
' If a defect is deleted delete it also from the mobInhertDefcts
'   collection.
Public Sub InhertDefctUpd()
On Error GoTo ErrHnd
    Dim obDatTbl As DatTbl
    Dim obTblInhertDefct As TblInhertDefct
    ' Go through each obTblInhertDefct.
    For Each obTblInhertDefct In mobInhertDefcts
        Set obDatTbl = obTblInhertDefct
        With obTblInhertDefct
            If .Added Then
                ' Insert.
                obDatTbl.Ins
            ElseIf .Edited Then
                ' Update.
                obDatTbl.Upd
            ElseIf .Deld Then
                ' Delete from the InhertDefect tablle.
                obDatTbl.Del
                ' Delete from the mobInhertDefcts collection.
                mobInhertDefcts.Del .IDDefct
'                mobInhertDefcts.Del .IDShG, .IDDefct
            End If
        End With
    Next obTblInhertDefct
Exit Sub
ErrHnd:
MsgBox Err.Description
End Sub

' Compose the collection of the WeightWoolAnnl table's primary keys.
Public Function GetKeys() As Keys
On Error GoTo ErrHnd
   Dim obKeys As Keys
   Dim rstAppr As ADODB.Recordset
   Dim strCmdTxt As String
   Set obKeys = New Keys
   Set rstAppr = New ADODB.Recordset 'Open the record set with the specified sheep/goat's
   strCmdTxt = "SELECT IDSheepGoat, Age FROM Appraisal WHERE IDSheepGoat = '" & IDShG & _
      "'"        'appraisals.
   rstAppr.Open strCmdTxt, gcnnConn, adOpenDynamic, adLockOptimistic
   With rstAppr 'Compose the colleciton.
      If .EOF = False And .BOF = False Then
         Do Until .EOF
            obKeys.Add .Fields("IDSheepGoat"), , .Fields("Age")
            .MoveNext
         Loop
      End If
   End With
   Set GetKeys = obKeys
Exit Function
ErrHnd:
MsgBox Err.Description
End Function

' Get IDShG.
Public Property Get IDShG() As String
   IDShG = mstrIDShG
End Property

' Let IDShG in this class & in its inbuilt classes.
Public Property Let IDShG(ByVal strIDShG As String)
   mstrIDShG = strIDShG
   mobInhertDefcts.IDShG = strIDShG
End Property

' Get Age.
Public Property Get Age() As Integer
   Age = mintAge
End Property

' Let Age in this class & in its inbuilt classes.
Public Property Let Age(ByVal intAge As Integer)
   mintAge = intAge
   mobInhertDefcts.Age = intAge
End Property

Private Property Get DatTbl_Full() As Boolean
'If necessary modify the code to use this procedure.
End Property

Private Property Let DatTbl_EscSelFail(ByVal blnEscSelFail As Boolean)
'If necessary modify the code to use this procedure.
End Property


Private Sub DatTbl_Clear()
'If necessary modify the code to use this procedure.
End Sub

