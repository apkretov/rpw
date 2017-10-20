USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_BreedCross_IDShGIDBreed" AND 
    type = "P")
    DROP PROCEDURE spUpdate_BreedCross_IDShGIDBreed
GO
CREATE PROCEDURE spUpdate_BreedCross_IDShGIDBreed (@IDSheepGoat char(6), @IDBreedOrigin char(2), 
    @IDBreed char(2), @BreedNum tinyint, @BreedDen tinyint) AS
    UPDATE BreedCross
	SET IDBreed = @IDBreed, BreedNum = @BreedNum, BreedDen = @BreedDen
	    WHERE (IDSheepGoat = @IDSheepGoat) AND 
		(IDBreed = @IDBreedOrigin)
GO