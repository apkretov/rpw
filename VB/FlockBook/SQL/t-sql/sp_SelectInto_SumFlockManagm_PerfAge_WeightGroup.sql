USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_PerfAge_WeightGroup" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfAge_WeightGroup
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfAge_WeightGroup -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfAge_WeightGroup" AND 
	type = "U")
DROP TABLE SumFlockManagm_PerfAge_WeightGroup
SELECT IDFarm, Age, AVG(WtAnnl) AS AvgWtAnnl
INTO SumFlockManagm_PerfAge_WeightGroup 
FROM SumFlockManagm_PerfAge_WeightAge
GROUP BY IDFarm, Age
HAVING (Age < 6)
GO
spSelectInto_SumFlockManagm_PerfAge_WeightGroup 
GO
SELECT * FROM SumFlockManagm_PerfAge_WeightGroup
GO