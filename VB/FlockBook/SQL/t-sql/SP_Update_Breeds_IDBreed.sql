USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Breeds_IDBreed" AND type = "P")
    DROP PROCEDURE spUpdate_Breeds_IDBreed
GO
CREATE PROCEDURE spUpdate_Breeds_IDBreed (@IDBreedOrig char(2), @IDBreed char(2), 
    @Breed varchar(50), @IDSpecies char(1), @WtWt tinyint, @WtGrease tinyint, @WtLeng tinyint, 
    @WtDiam tinyint, @WtFatTail tinyint) AS
    UPDATE Breeds
	SET IDBreed = @IDBreed, Breed = @Breed, IDSpecies = @IDSpecies, WtWt = @WtWt, 
	    WtGrease = @WtGrease, WtLeng = @WtLeng, WtDiam = @WtDiam, WtFatTail = @WtFatTail
	WHERE IDBreed = @IDBreedOrig
GO
SELECT * FROM Breeds 
GO
spUpdate_Breeds_IDBreed "JF", "99", "99999999", "1", 99, 99, 99, 99, 99
GO
SELECT * FROM Breeds 
GO