USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_BreedCross_IDShGIDBreed" AND 
    type = "P")
    DROP PROCEDURE spSelect_BreedCross_IDShGIDBreed
GO
CREATE PROCEDURE spSelect_BreedCross_IDShGIDBreed (@IDSheepGoat char(6), @IDBreed char(2)) AS
    SELECT * FROM BreedCross
	WHERE IDSheepGoat = @IDSheepGoat AND 
	    IDBreed = @IDBreed
GO 
