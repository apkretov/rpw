USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_WlGrsColour" AND type = "P")
    DROP PROCEDURE spSelect_WlGrsColour
GO
CREATE PROCEDURE spSelect_WlGrsColour AS
    SELECT * FROM WlGrsColour
	WHERE IDColour <> "-"
GO
spSelect_WlGrsColour
GO