USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Reprod_AbortCount" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Reprod_AbortCount
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Reprod_AbortCount -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Reprod_AbortCount" AND 
	type = "U") -- Drop the previous table.
DROP TABLE SumFlockManagm_Reprod_AbortCount
SELECT IDFarm, CAST(COUNT(IDDam) AS real) 
    AS CountIDDam
INTO SumFlockManagm_Reprod_AbortCount 
FROM SumFlockManagmV_Reprod_Abort
GROUP BY IDFarm
GO
spSelectInto_SumFlockManagm_Reprod_AbortCount 
GO
SELECT * FROM SumFlockManagm_Reprod_AbortCount
GO