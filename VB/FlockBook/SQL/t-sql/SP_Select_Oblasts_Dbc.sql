USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Oblasts_Dbc" AND type = "P")
    DROP PROCEDURE spSelect_Oblasts_Dbc
GO
CREATE PROCEDURE spSelect_Oblasts_Dbc AS
    SELECT IDOblast, Oblast
	FROM Oblasts
	WHERE (Oblast <> "-")
	ORDER BY Oblast
GO
spSelect_Oblasts_Dbc 
GO