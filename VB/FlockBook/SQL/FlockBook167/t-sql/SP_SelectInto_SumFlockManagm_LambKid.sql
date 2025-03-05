USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_LambKid" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_LambKid
GO

CREATE PROCEDURE spSelectInto_SumFlockManagm_LambKid
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_LambKid" AND type = "U") 
DROP TABLE SumFlockManagm_LambKid -- Drop the previous table.
SELECT SumFlockManagm_Mate.IDFarm, LambKid.IDDam, SheepGoat.DateBirth, LambKid.Cycle, 
	LambKid.DateLambKid, LambKid.TypeBirth, LambKid.Abort -- Create a new one.
	INTO SumFlockManagm_LambKid 
FROM LambKid INNER JOIN SumFlockManagm_Mate ON LambKid.IDDam = SumFlockManagm_Mate.IDDam AND 
	LambKid.Cycle = SumFlockManagm_Mate.Cycle INNER JOIN SheepGoat ON 
	SumFlockManagm_Mate.IDDam = SheepGoat.IDSheepGoat
    /*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_LambKid ON 
	SumFlockManagm_LambKid (IDDam) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_LambKid_1 ON 
	SumFlockManagm_LambKid (Abort) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_SumFlockManagm_LambKid_2 ON 
	SumFlockManagm_LambKid (Cycle) ON [PRIMARY]*/
GO

spSelectInto_SumFlockManagm_LambKid
GO
SELECT * FROM SumFlockManagm_LambKid
GO
