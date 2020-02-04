USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp_Female2All" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp_Female2All
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp_Female2All -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Disp_Female2All" AND 
	type = "U")
DROP TABLE SumFlockManagm_Disp_Female2All
SELECT Disposition.IDDispReas, 
    SumFlockManagmV_Disp_Female2Avail.IDFarm, 
    SumFlockManagmV_Disp_Female2Avail.CountIDSheepGoat
INTO SumFlockManagm_Disp_Female2All 
FROM Disposition LEFT OUTER JOIN
    SumFlockManagmV_Disp_Female2Avail ON 
    Disposition.IDDispReas = SumFlockManagmV_Disp_Female2Avail.IDDispReas
WHERE (Disposition.IDDispReas <> '-')
GO
spSelectInto_SumFlockManagm_Disp_Female2All 
GO
SELECT * FROM SumFlockManagm_Disp_Female2All
GO