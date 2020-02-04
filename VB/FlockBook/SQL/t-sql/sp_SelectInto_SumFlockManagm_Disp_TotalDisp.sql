USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Disp_TotalDisp" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Disp_TotalDisp
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Disp_TotalDisp -- Create a new one.
AS
--SET DATEFORMAT dmy
IF exists (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Disp_TotalDisp" AND 
	type = "U") -- Drop the previous table.
DROP TABLE SumFlockManagm_Disp_TotalDisp
SELECT IDFarm, CAST(COUNT(IDSheepGoat) AS REAL) AS CountIDSheepGoat
INTO SumFlockManagm_Disp_TotalDisp 
FROM SumFlockManagm_SheepGoatDisp
GROUP BY IDFarm
GO
spSelectInto_SumFlockManagm_Disp_TotalDisp
GO
SELECT * FROM SumFlockManagm_Disp_TotalDisp
GO