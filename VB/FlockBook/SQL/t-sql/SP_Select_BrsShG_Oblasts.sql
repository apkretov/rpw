USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_Oblasts" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_Oblasts
GO
CREATE PROCEDURE spSelect_BrsShG_Oblasts (@IDCountry int) AS
    SELECT IDOblast, Oblast 
	FROM Oblasts
	WHERE IDCountry = @IDCountry
	ORDER BY Oblast
GO
spSelect_BrsShG_Oblasts 1
GO