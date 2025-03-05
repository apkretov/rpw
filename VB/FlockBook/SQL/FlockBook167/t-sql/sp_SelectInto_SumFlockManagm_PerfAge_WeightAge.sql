USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_PerfAge_WeightAge" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfAge_WeightAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfAge_WeightAge -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfAge_WeightAge" AND 
	type = "U")
DROP TABLE SumFlockManagm_PerfAge_WeightAge
SELECT IDFarm, ROUND(CAST((DateAnnl - DateBirth) AS SMALLINT) / 365.25, 0) AS Age, WtAnnl
INTO SumFlockManagm_PerfAge_WeightAge 
FROM SumFlockManagm_WeightAnnl
/*CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfAge_WeightAge ON 
	SumFlockManagm_PerfAge_WeightAge (IDFarm) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_SumFlockManagm_PerfAge_WeightAge_1 ON 
	SumFlockManagm_PerfAge_WeightAge (Age) ON [PRIMARY]*/
GO
spSelectInto_SumFlockManagm_PerfAge_WeightAge 
GO
SELECT * FROM SumFlockManagm_PerfAge_WeightAge
GO