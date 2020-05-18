USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp_All" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp_All
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp_All -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Disp_All" AND type = "U")
DROP TABLE SumFlockManagm_Disp_All
SELECT Disposition.IDDispReas, 
    SumFlockManagmV_Disp_Avail.IDFarm, 
    SumFlockManagmV_Disp_Avail.CountIDSheepGoat, 
    SumFlockManagmV_Disp_Avail.CountIDSheepGoat / SumFlockManagm_Disp_TotalDisp.CountIDSheepGoat
     * 100 AS [Percent]
INTO SumFlockManagm_Disp_All 
FROM SumFlockManagmV_Disp_Avail INNER JOIN
    SumFlockManagm_Disp_TotalDisp ON 
    SumFlockManagmV_Disp_Avail.IDFarm = SumFlockManagm_Disp_TotalDisp.IDFarm
     RIGHT OUTER JOIN
    Disposition ON 
    SumFlockManagmV_Disp_Avail.IDDispReas = Disposition.IDDispReas
WHERE (Disposition.IDDispReas <> '-')
GO
spSelectInto_SumFlockManagm_Disp_All 
GO
SELECT * FROM SumFlockManagm_Disp_All
GO