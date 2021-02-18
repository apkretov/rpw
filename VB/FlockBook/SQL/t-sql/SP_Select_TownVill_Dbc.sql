USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_TownVill_Dbc" AND type = "P")
    DROP PROCEDURE spSelect_TownVill_Dbc
GO
CREATE PROCEDURE spSelect_TownVill_Dbc AS
    SELECT IDTownVill, TownVill
	FROM TownVill
	WHERE (TownVill <> "-")
	ORDER BY TownVill
GO
spSelect_TownVill_Dbc 
GO