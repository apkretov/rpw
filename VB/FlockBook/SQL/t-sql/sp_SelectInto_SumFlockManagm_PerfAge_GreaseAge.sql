USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_PerfAge_GreaseAge" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfAge_GreaseAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfAge_GreaseAge -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfAge_GreaseAge" AND 
	type = "U")
DROP TABLE SumFlockManagm_PerfAge_GreaseAge
SELECT IDFarm, ROUND(CAST((DateShearAnnl - DateBirth) 
    AS SMALLINT) / 365.25, 0) AS Age, GreaseAnnl
INTO SumFlockManagm_PerfAge_GreaseAge 
FROM SumFlockManagm_WoolAnnl
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfAge_GreaseAge ON 
	SumFlockManagm_PerfAge_GreaseAge (Age) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfAge_GreaseAge_1 ON 
	SumFlockManagm_PerfAge_GreaseAge (IDFarm) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfAge_GreaseAge 
GO
SELECT * FROM SumFlockManagm_PerfAge_GreaseAge
GO