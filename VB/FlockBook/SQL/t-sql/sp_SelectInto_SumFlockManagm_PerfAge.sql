USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_PerfAge" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_PerfAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_PerfAge -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_PerfAge" AND type = "U")
DROP TABLE SumFlockManagm_PerfAge
SELECT SumFlockManagm_Farms.IDFarm, 
    SumFlockManagmV_PerfAge_Weight1Yr.AvgWtAnnl1Yr, 
    SumFlockManagmV_PerfAge_Weight2Yr.AvgWtAnnl2Yr, 
    SumFlockManagmV_PerfAge_Weight3Yr.AvgWtAnnl3Yr, 
    SumFlockManagmV_PerfAge_Weight4Yr.AvgWtAnnl4Yr, 
    SumFlockManagmV_PerfAge_Weight5Yr.AvgWtAnnl5Yr, 
    SumFlockManagmV_PerfAge_Weight6Yr.AvgWtAnnl6Yr, 
    SumFlockManagmV_PerfAge_Grease1Yr.AvgGreaseAnnl1Yr, 
    SumFlockManagmV_PerfAge_Grease2Yr.AvgGreaseAnnl2Yr, 
    SumFlockManagmV_PerfAge_Grease3Yr.AvgGreaseAnnl3Yr, 
    SumFlockManagmV_PerfAge_Grease4Yr.AvgGreaseAnnl4Yr, 
    SumFlockManagmV_PerfAge_Grease5Yr.AvgGreaseAnnl5Yr, 
    SumFlockManagmV_PerfAge_Grease6Yr.AvgGreaseAnnl6Yr
INTO SumFlockManagm_PerfAge 
FROM dbo.SumFlockManagm_Farms LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Grease6Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Grease6Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Grease5Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Grease5Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Grease4Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Grease4Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Grease3Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Grease3Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Grease2Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Grease2Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Grease1Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Grease1Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Weight6Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Weight6Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Weight5Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Weight5Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Weight4Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Weight4Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Weight3Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Weight3Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Weight2Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Weight2Yr.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_PerfAge_Weight1Yr ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_PerfAge_Weight1Yr.IDFarm
GO
spSelectInto_SumFlockManagm_PerfAge 
GO
SELECT * FROM SumFlockManagm_PerfAge
GO