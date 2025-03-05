USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_SumFlockManagm_Reprod_OffspBornCount" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Reprod_OffspBornCount
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Reprod_OffspBornCount -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Reprod_OffspBornCount" AND 
	type = "U") -- Drop the previous table.
DROP TABLE SumFlockManagm_Reprod_OffspBornCount
SELECT IDFarm, COUNT(IDLambKid) AS CountIDLambKid
INTO SumFlockManagm_Reprod_OffspBornCount 
FROM dbo.SumFlockManagm_Offspring
GROUP BY IDFarm
GO
spSelectInto_SumFlockManagm_Reprod_OffspBornCount 
GO
SELECT * FROM SumFlockManagm_Reprod_OffspBornCount
GO