USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_PerfAge_GreaseGroup" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfAge_GreaseGroup
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfAge_GreaseGroup -- Create a new one.
AS
SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfAge_GreaseGroup" AND 
	type = "U")
DROP TABLE SumFlockManagm_PerfAge_GreaseGroup
SELECT IDFarm, Age, AVG(GreaseAnnl) AS AvgGreaseAnnl
INTO SumFlockManagm_PerfAge_GreaseGroup 
FROM SumFlockManagm_PerfAge_GreaseAge
GROUP BY IDFarm, Age
HAVING (Age < 6)
GO
spSelectInto_SumFlockManagm_PerfAge_GreaseGroup 
GO
SELECT * FROM SumFlockManagm_PerfAge_GreaseGroup
GO