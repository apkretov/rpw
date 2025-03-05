USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Farms_IDFarm" AND type = "P")
    DROP PROCEDURE spSelect_Farms_IDFarm
GO
CREATE PROCEDURE spSelect_Farms_IDFarm (@IDFarm char(2)) AS
    SELECT *
	FROM Farms
	WHERE IDFarm = @IDFarm
GO
spSelect_Farms_IDFarm "ZZ"
GO
