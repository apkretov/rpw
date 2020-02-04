USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Rayons_Rayn" AND type = "P")
    DROP PROCEDURE spSelect_Rayons_Rayn
GO
CREATE PROCEDURE spSelect_Rayons_Rayn (@Rayon varchar(50)) AS
    SELECT *
	FROM Rayons
	WHERE Rayon = @Rayon
GO
spSelect_Rayons_Rayn "KDFADSF"
GO
