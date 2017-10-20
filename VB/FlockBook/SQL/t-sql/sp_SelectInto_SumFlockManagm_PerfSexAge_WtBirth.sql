USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_SumFlockManagm_PerfSexAge_WtBirth" AND type = "P")
    DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WtBirth
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_WtBirth (@IDFarm char(2), @DateBegin smalldatetime/*varchar(8)*/, 
    @DateEnd smalldatetime/*varchar(8)*/)
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfSexAge_WtBirth" AND 
    type = "U")
    DROP TABLE SumFlockManagm_PerfSexAge_WtBirth
SELECT Offspring.IDLambKid, Offspring.WtBirth -- Create a new one.
INTO SumFlockManagm_PerfSexAge_WtBirth 
FROM Offspring INNER JOIN LambKid ON 
    Offspring.IDDam = LambKid.IDDam AND 
    Offspring.Cycle = LambKid.Cycle 
    INNER JOIN SheepGoat ON 
    Offspring.IDLambKid = SheepGoat.IDSheepGoat
WHERE (SheepGoat.IDFarm = @IDFarm) AND 
    (LambKid.DateLambKid >= /*CAST(*/@DateBegin /*AS smalldatetime)*/) AND 
    (LambKid.DateLambKid <= /*CAST(*/@DateEnd /*AS smalldatetime)*/) AND 
    (Offspring.IDLambKid <> '-')
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfSexAge_WtBirth ON 
    SumFlockManagm_PerfSexAge_WtBirth (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfSexAge_WtBirth "¿¿", "01.26.03", "01.27.03" -- "01.01.90", "27.01.03"
GO
SELECT * FROM SumFlockManagm_PerfSexAge_WtBirth
GO