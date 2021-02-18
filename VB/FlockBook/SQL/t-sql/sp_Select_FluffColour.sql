USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_FluffColour" AND type = "P")
    DROP PROCEDURE spSelect_FluffColour
GO
CREATE PROCEDURE spSelect_FluffColour AS
    SELECT * FROM FluffColour
	WHERE IDFluffColour <> "-"
GO
spSelect_FluffColour
GO