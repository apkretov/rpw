USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE -- Drop the previous SP.
	name = "spSelectInto_SumFlockManagm_Reprod" AND type = "P")
DROP PROCEDURE spSelectInto_SumFlockManagm_Reprod
GO
CREATE PROCEDURE spSelectInto_SumFlockManagm_Reprod -- Create a new one.
AS
--SET DATEFORMAT dmy
IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumFlockManagm_Reprod" AND type = "U")
DROP TABLE SumFlockManagm_Reprod
SELECT SumFlockManagm_Farms.IDFarm, 
    ISNULL(SumFlockManagmV_Reprod_MateCount.CountIDDam, 0) AS Mate, 
    ISNULL(SumFlockManagm_LambKidCount.CountIDDam, 0) AS LambKid, 
    ISNULL(SumFlockManagmV_Reprod_DeadCount.CountIDDam, 0) AS Dead, 
    ISNULL(SumFlockManagm_Reprod_AbortCount.CountIDDam, 0) AS Abort, 
    ISNULL(SumFlockManagmV_Reprod_MateCount.CountIDDam, 0) 
    - ISNULL(SumFlockManagm_LambKidCount.CountIDDam, 0)
    - ISNULL(SumFlockManagm_Reprod_AbortCount.CountIDDam, 0) AS Barren,
    ISNULL( (ISNULL(SumFlockManagm_LambKidCount.CountIDDam, 0) 
    + ISNULL(SumFlockManagm_Reprod_AbortCount.CountIDDam, 0))
     / SumFlockManagmV_Reprod_MateCount.CountIDDam * 100, 0) AS Concept, 
    ISNULL(SumFlockManagm_Reprod_OffspBornCount.CountIDLambKid, 0) AS OffspBorn, 
    ISNULL(SumFlockManagm_Reprod_OffspBornCount.CountIDLambKid 
    / SumFlockManagm_LambKidCount.CountIDDam, 0) AS OffspBornDam, 
    ISNULL(SumFlockManagmV_Reprod_OffspWeanCount.CountIDLambKid
    / SumFlockManagm_LambKidCount.CountIDDam, 0) AS OffspWeanDam,
    ISNULL(SumFlockManagmV_Reprod_AgeLambKidAvg.AvgAgeLambKid, 0) AS AgeLambKid
INTO SumFlockManagm_Reprod 
FROM dbo.SumFlockManagmV_Reprod_AgeLambKidAvg RIGHT OUTER
     JOIN
    dbo.SumFlockManagm_Farms ON 
    dbo.SumFlockManagmV_Reprod_AgeLambKidAvg.IDFarm = dbo.SumFlockManagm_Farms.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Reprod_OffspWeanCount ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Reprod_OffspWeanCount.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagm_Reprod_OffspBornCount ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagm_Reprod_OffspBornCount.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagm_Reprod_AbortCount ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagm_Reprod_AbortCount.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagm_LambKidCount ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagm_LambKidCount.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Reprod_DeadCount ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Reprod_DeadCount.IDFarm
     LEFT OUTER JOIN
    dbo.SumFlockManagmV_Reprod_MateCount ON 
    dbo.SumFlockManagm_Farms.IDFarm = dbo.SumFlockManagmV_Reprod_MateCount.IDFarm
GO
spSelectInto_SumFlockManagm_Reprod 
GO
SELECT * FROM SumFlockManagm_Reprod
GO