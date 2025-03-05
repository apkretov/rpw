USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp3" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp3
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp3 -- Create a new one.
AS
SET DATEFORMAT dmy
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'SumFlockManagm_Disp3') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1) -- Drop the previous table.
DROP TABLE SumFlockManagm_Disp3
SELECT SumFlockManagm_Farms.IDFarm, 
    SumFlockManagmV_Disp_All01.Count01, 
    SumFlockManagmV_Disp_All02.Count02, 
    SumFlockManagmV_Disp_All03.Count03, 
    SumFlockManagmV_Disp_All04.Count04, 
    SumFlockManagm_Disp_TotalDisp.CountIDSheepGoat AS CountTotalDisp,
     SumFlockManagmV_Disp_Total.CountIDSheepGoat AS CountTotal,
     SumFlockManagmV_Disp_All01.Percent01, 
    SumFlockManagmV_Disp_All02.Percent02, 
    SumFlockManagmV_Disp_All03.Percent03, 
    SumFlockManagmV_Disp_All04.Percent04, 
    SumFlockManagm_Disp_TotalDisp.CountIDSheepGoat / SumFlockManagm_Disp_TotalDisp.CountIDSheepGoat
     * 100 AS PercentTotal
INTO SumFlockManagm_Disp3 
FROM dbo.SumFlockManagm_Farms LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagm_Disp_TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagm_Disp_TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_All01.IDFarm
GO
spSelectInto_SumFlockManagm_Disp3 
GO
SELECT * FROM SumFlockManagm_Disp3
GO