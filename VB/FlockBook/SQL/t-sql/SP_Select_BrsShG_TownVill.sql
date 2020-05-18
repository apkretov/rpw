USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_TownVill" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_TownVill
GO
CREATE PROCEDURE spSelect_BrsShG_TownVill (@IDRayon int) AS
    SELECT IDTownVill, TownVill FROM TownVill
	WHERE IDRayon = @IDRayon
	ORDER BY TownVill
GO
spSelect_BrsShG_TownVill 1
GO