USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_BearDistr2" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_BearDistr2
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_BearDistr2 -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_BearDistr2" AND type = "U")
DROP TABLE SumFlockManagm_BearDistr2
SELECT SumFlockManagm_Farms.IDFarm, 
    SumFlockManagmV_BearDistr_Sing2YrPercent.PercentAge2YrSing,
     SumFlockManagmV_BearDistr_Sing3YrPercent.PercentAge3YrSing,
     SumFlockManagmV_BearDistr_Sing4YrPercent.PercentAge4YrSing,
     SumFlockManagmV_BearDistr_Sing5YrPercent.PercentAge5YrSing,
     SumFlockManagmV_BearDistr_Sing6YrPercent.PercentAge6YrSing,
     SumFlockManagmV_BearDistr_Twin2YrPercent.PercentAge2YrTwin,
     SumFlockManagmV_BearDistr_Twin3YrPercent.PercentAge3YrTwin,
     SumFlockManagmV_BearDistr_Twin4YrPercent.PercentAge4YrTwin,
     SumFlockManagmV_BearDistr_Twin5YrPercent.PercentAge5YrTwin,
     SumFlockManagmV_BearDistr_Twin6YrPercent.PercentAge6YrTwin,
     SumFlockManagmV_BearDistr_Trip2YrPercent.PercentAge2YrTrip,
     SumFlockManagmV_BearDistr_Trip3YrPercent.PercentAge3YrTrip,
     SumFlockManagmV_BearDistr_Trip4YrPercent.PercentAge4YrTrip,
     SumFlockManagmV_BearDistr_Trip5YrPercent.PercentAge5YrTrip,
     SumFlockManagmV_BearDistr_Trip6YrPercent.PercentAge6YrTrip
INTO SumFlockManagm_BearDistr2 
FROM dbo.SumFlockManagm_Farms LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Trip6YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Trip6YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Trip5YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Trip5YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Trip4YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Trip4YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Trip3YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Trip3YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Trip2YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Trip2YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Twin6YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Twin6YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Twin5YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Twin5YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Twin4YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Twin4YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Twin3YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Twin3YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Twin2YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Twin2YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Sing6YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Sing6YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Sing5YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Sing5YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Sing4YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Sing4YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Sing3YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Sing3YrPercent.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_BearDistr_Sing2YrPercent ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_BearDistr_Sing2YrPercent.IDFarm
GO
spSelectInto_SumFlockManagm_BearDistr2 
GO
SELECT * FROM SumFlockManagm_BearDistr2
GO