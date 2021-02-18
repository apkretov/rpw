USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_TownVill_IDTwnVll" AND type = "P")
    DROP PROCEDURE spDelete_TownVill_IDTwnVll
GO
CREATE PROCEDURE spDelete_TownVill_IDTwnVll (@IDTownVill int) AS
    DELETE TownVill
	WHERE IDTownVill = @IDTownVill
GO
spDelete_TownVill_IDTwnVll 33
GO
