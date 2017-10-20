USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Rayons_Dbc" AND type = "P")
    DROP PROCEDURE spSelect_Rayons_Dbc
GO
CREATE PROCEDURE spSelect_Rayons_Dbc AS
    SELECT IDRayon, Rayon
	FROM Rayons
	WHERE (Rayon <> "-")
	ORDER BY Rayon
GO
spSelect_Rayons_Dbc 
GO