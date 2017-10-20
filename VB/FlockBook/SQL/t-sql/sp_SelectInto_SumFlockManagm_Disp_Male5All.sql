USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp_Male5All" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp_Male5All
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp_Male5All -- Create a new one.
AS
SET DATEFORMAT dmy
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'SumFlockManagm_Disp_Male5All') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1) -- Drop the previous table.
DROP TABLE SumFlockManagm_Disp_Male5All
SELECT Disposition.IDDispReas, 
    SumFlockManagmV_Disp_Male5Avail.IDFarm, 
    SumFlockManagmV_Disp_Male5Avail.CountIDSheepGoat
INTO SumFlockManagm_Disp_Male5All 
FROM Disposition LEFT OUTER JOIN
    SumFlockManagmV_Disp_Male5Avail ON 
    Disposition.IDDispReas = SumFlockManagmV_Disp_Male5Avail.IDDispReas
WHERE (Disposition.IDDispReas <> '-')
GO
spSelectInto_SumFlockManagm_Disp_Male5All 
GO
SELECT * FROM SumFlockManagm_Disp_Male5All
GO