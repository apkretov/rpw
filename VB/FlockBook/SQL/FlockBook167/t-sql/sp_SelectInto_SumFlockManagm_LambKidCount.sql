USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_LambKidCount" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_LambKidCount
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_LambKidCount -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_LambKidCount" AND type = "U")
DROP TABLE SumFlockManagm_LambKidCount
SELECT IDFarm, CAST(COUNT(IDDam) AS real) 
    AS CountIDDam
INTO SumFlockManagm_LambKidCount 
FROM SumFlockManagmV_Reprod_LambKid
GROUP BY IDFarm
GO
spSelectInto_SumFlockManagm_LambKidCount 
GO
SELECT * FROM SumFlockManagm_LambKidCount
GO