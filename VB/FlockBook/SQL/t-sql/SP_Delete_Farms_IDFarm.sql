USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Farms_IDFarm" AND type = "P")
    DROP PROCEDURE spDelete_Farms_IDFarm
GO
CREATE PROCEDURE spDelete_Farms_IDFarm (@IDFarm char(2)) AS
    DELETE Farms
	WHERE IDFarm = @IDFarm
GO
spDelete_Farms_IDFarm "ZZ"
GO
