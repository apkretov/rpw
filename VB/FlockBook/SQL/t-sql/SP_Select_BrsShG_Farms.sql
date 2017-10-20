USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_Farms" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_Farms
GO
CREATE PROCEDURE spSelect_BrsShG_Farms (@IDTownVill int) AS
    SELECT IDFarm FROM Farms
	WHERE IDTownVill = @IDTownVill
GO
spSelect_BrsShG_Farms 1
GO