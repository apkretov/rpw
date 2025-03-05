USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_PerfSexAge_FarmSexAge" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_FarmSexAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfSexAge_FarmSexAge -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfSexAge_FarmSexAge" AND 
	type = "U")
DROP TABLE SumFlockManagm_PerfSexAge_FarmSexAge
SELECT SumFlockManagm_Farms.IDFarm, AgeSex.IDAgeSex, AgeSex.AgeSex
INTO SumFlockManagm_PerfSexAge_FarmSexAge 
FROM dbo.AgeSex, dbo.SumFlockManagm_Farms
GO
spSelectInto_SumFlockManagm_PerfSexAge_FarmSexAge 
GO
SELECT * FROM SumFlockManagm_PerfSexAge_FarmSexAge
GO