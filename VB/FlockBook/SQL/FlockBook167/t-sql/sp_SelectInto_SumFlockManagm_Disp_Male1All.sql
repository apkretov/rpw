USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp_Male1All" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp_Male1All
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp_Male1All -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Disp_Male1All" AND 
	type = "U")
DROP TABLE SumFlockManagm_Disp_Male1All
SELECT Disposition.IDDispReas, 
    SumFlockManagmV_Disp_Male1Avail.IDFarm, 
    SumFlockManagmV_Disp_Male1Avail.CountIDSheepGoat
INTO SumFlockManagm_Disp_Male1All 
FROM Disposition LEFT OUTER JOIN
    SumFlockManagmV_Disp_Male1Avail ON 
    Disposition.IDDispReas = SumFlockManagmV_Disp_Male1Avail.IDDispReas
WHERE (Disposition.IDDispReas <> '-')
GO
spSelectInto_SumFlockManagm_Disp_Male1All 
GO
SELECT * FROM SumFlockManagm_Disp_Male1All
GO