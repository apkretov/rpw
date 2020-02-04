USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Breeds" AND type = "P")
    DROP PROCEDURE spInsert_Breeds
GO
CREATE PROCEDURE spInsert_Breeds (@IDBreed char(2), @Breed varchar(50), @IDSpecies char(1), 
    @WtWt tinyint, @WtGrease tinyint, @WtLeng tinyint, @WtDiam tinyint, @WtFatTail tinyint) AS
    INSERT INTO Breeds (IDBreed, Breed, IDSpecies, WtWt, WtGrease, WtLeng, WtDiam, WtFatTail)
	VALUES (@IDBreed, @Breed, @IDSpecies, @WtWt, @WtGrease, @WtLeng, @WtDiam, @WtFatTail)
GO
SELECT * FROM Breeds
GO
spInsert_Breeds "JF", "ASFADSF", "0", 20, 20, 20, 20, 20
GO
SELECT * FROM Breeds
GO