USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp1" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp1
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp1 -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Disp1" AND type = "U")
DROP TABLE SumFlockManagm_Disp1
SELECT SumFlockManagm_Farms.IDFarm, 
    SumFlockManagmV_Disp_Male1All01.Male101, 
    SumFlockManagmV_Disp_Male1All02.Male102, 
    SumFlockManagmV_Disp_Male1All03.Male103, 
    SumFlockManagmV_Disp_Male1All04.Male104, 
    SumFlockManagmV_Disp_Male1TotalDisp.Male1TotalDisp, 
    SumFlockManagmV_Disp_Male1Total.Male1Total, 
    SumFlockManagmV_Disp_Female2All01.Female201, 
    SumFlockManagmV_Disp_Female2All02.Female202, 
    SumFlockManagmV_Disp_Female2All03.Female203, 
    SumFlockManagmV_Disp_Female2All04.Female204, 
    SumFlockManagmV_Disp_Female2TotalDisp.Female2TotalDisp,
     SumFlockManagmV_Disp_Female2Total.Female2Total, 
    SumFlockManagmV_Disp_Male3All01.Male301, 
    SumFlockManagmV_Disp_Male3All02.Male302, 
    SumFlockManagmV_Disp_Male3All03.Male303, 
    SumFlockManagmV_Disp_Male3All04.Male304, 
    SumFlockManagmV_Disp_Male3TotalDisp.Male3TotalDisp, 
    SumFlockManagmV_Disp_Male3Total.Male3Total
INTO SumFlockManagm_Disp1 
FROM dbo.SumFlockManagm_Farms LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male3Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male3Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male3TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male3TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male3All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male3All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male3All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male3All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male3All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male3All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male3All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male3All01.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female2Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female2Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female2TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female2TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female2All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female2All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female2All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female2All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female2All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female2All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Female2All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Female2All01.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male1Total ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male1Total.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male1TotalDisp ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male1TotalDisp.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male1All04 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male1All04.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male1All03 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male1All03.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male1All02 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male1All02.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Disp_Male1All01 ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Disp_Male1All01.IDFarm
GO
spSelectInto_SumFlockManagm_Disp1 
GO
SELECT * FROM SumFlockManagm_Disp1
GO