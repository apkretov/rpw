USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	NAME = "spSelectInto_SumFlockManagm_Disp_Female4All" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp_Female4All
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp_Female4All -- Create a new one.
AS
SET DATEFORMAT dmy
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'SumFlockManagm_Disp_Female4All') 
	AND OBJECTPROPERTY(id, N'IsUserTable') = 1) -- Drop the previous table.
DROP TABLE SumFlockManagm_Disp_Female4All
SELECT Disposition.IDDispReas, 
    SumFlockManagmV_Disp_Female4Avail.IDFarm, 
    SumFlockManagmV_Disp_Female4Avail.CountIDSheepGoat
INTO SumFlockManagm_Disp_Female4All 
FROM Disposition LEFT OUTER JOIN
    SumFlockManagmV_Disp_Female4Avail ON 
    Disposition.IDDispReas = SumFlockManagmV_Disp_Female4Avail.IDDispReas
WHERE (Disposition.IDDispReas <> '-')
GO
spSelectInto_SumFlockManagm_Disp_Female4All 
GO
SELECT * FROM SumFlockManagm_Disp_Female4All
GO