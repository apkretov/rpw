USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp2" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp2
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp2 -- Create a new one.
AS
SET DATEFORMAT dmy
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'SumFlockManagm_Disp2') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1) -- Drop the previous table.
DROP TABLE SumFlockManagm_Disp2
SELECT SumFlockManagm_Farms.IDFarm, 
    SumFlockManagmV_Disp_Female4All01.Female401, 
    SumFlockManagmV_Disp_Female4All02.Female402, 
    SumFlockManagmV_Disp_Female4All03.Female403, 
    SumFlockManagmV_Disp_Female4All04.Female404, 
    SumFlockManagmV_Disp_Female4TotalDisp.Female4TotalDisp,
     SumFlockManagmV_Disp_Female4Total.Female4Total, 
    SumFlockManagmV_Disp_Male5All01.Male501, 
    SumFlockManagmV_Disp_Male5All02.Male502, 
    SumFlockManagmV_Disp_Male5All03.Male503, 
    SumFlockManagmV_Disp_Male5All04.Male504, 
    SumFlockManagmV_Disp_Male5TotalDisp.Male5TotalDisp, 
    SumFlockManagmV_Disp_Male5Total.Male5Total, 
    SumFlockManagmV_Disp_Female6All01.Female601, 
    SumFlockManagmV_Disp_Female6All02.Female602, 
    SumFlockManagmV_Disp_Female6All03.Female603, 
    SumFlockManagmV_Disp_Female6All04.Female604, 
    SumFlockManagmV_Disp_Female6TotalDisp.Female6TotalDisp,
     SumFlockManagmV_Disp_Female6Total.Female6Total
INTO SumFlockManagm_Disp2 
FROM dbo.SumFlockManagm_Farms LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female6Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female6Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female6TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female6TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female6All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female6All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female6All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female6All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female6All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female6All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female6All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female6All01.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male5Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male5Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male5TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male5TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male5All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male5All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male5All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male5All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male5All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male5All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male5All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male5All01.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female4Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female4Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female4TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female4TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female4All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female4All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female4All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female4All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female4All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female4All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female4All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female4All01.IDFarm
GO
spSelectInto_SumFlockManagm_Disp2 
GO
SELECT * FROM SumFlockManagm_Disp2
GO