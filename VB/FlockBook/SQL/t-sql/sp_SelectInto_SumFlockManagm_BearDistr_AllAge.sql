USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_BearDistr_AllAge" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_BearDistr_AllAge
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_BearDistr_AllAge -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_BearDistr_AllAge" AND 
	type = "U") -- Drop the previous table.
DROP TABLE SumFlockManagm_BearDistr_AllAge
SELECT IDFarm, CAST((DateLambKid - DateBirth) AS smallint) / 365.25 AS Age, TypeBirth
INTO SumFlockManagm_BearDistr_AllAge 
FROM SumFlockManagm_LambKid
WHERE Abort = "0"
GO
spSelectInto_SumFlockManagm_BearDistr_AllAge 
GO
SELECT * FROM SumFlockManagm_BearDistr_AllAge
GO