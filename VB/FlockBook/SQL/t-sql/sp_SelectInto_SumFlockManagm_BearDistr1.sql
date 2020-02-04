USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_BearDistr1" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_BearDistr1
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_BearDistr1 -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_BearDistr1" AND type = "U")
DROP TABLE SumFlockManagm_BearDistr1
SELECT SumFlockManagm_Farms.IDFarm, 
    SumFlockManagmV_BearDistr_All2YrCountPercent.CountAge2Yr,
     SumFlockManagmV_BearDistr_All3YrCountPercent.CountAge3Yr,
     SumFlockManagmV_BearDistr_All4YrCountPercent.CountAge4Yr,
     SumFlockManagmV_BearDistr_All5YrCountPercent.CountAge5Yr,
     SumFlockManagmV_BearDistr_All6YrCountPercent.CountAge6Yr,
     SumFlockManagmV_BearDistr_All2YrCountPercent.PercentAge2YrAll,
     SumFlockManagmV_BearDistr_All3YrCountPercent.PercentAge3YrAll,
     SumFlockManagmV_BearDistr_All4YrCountPercent.PercentAge4YrAll,
     SumFlockManagmV_BearDistr_All5YrCountPercent.PercentAge5YrAll,
     SumFlockManagmV_BearDistr_All6YrCountPercent.PercentAge6YrAll
INTO SumFlockManagm_BearDistr1 
FROM dbo.SumFlockManagm_Farms LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_All6YrCountPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_All6YrCountPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_All5YrCountPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_All5YrCountPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_All4YrCountPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_All4YrCountPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_All3YrCountPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_All3YrCountPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_All2YrCountPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_All2YrCountPercent.IDFarm
GO
spSelectInto_SumFlockManagm_BearDistr1 
GO
SELECT * FROM SumFlockManagm_BearDistr1
GO