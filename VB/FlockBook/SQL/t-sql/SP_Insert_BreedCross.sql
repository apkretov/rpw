USE FlockBookRec
--USE Test
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spInsert_BreedCross" AND type = "P")
DROP PROCEDURE spInsert_BreedCross
GO
CREATE PROCEDURE spInsert_BreedCross (@IDSheepGoat char(6), @IDBreed char(2), @BreedNum tinyint,
	@BreedDen tinyint)
AS
INSERT INTO BreedCross (IDSheepGoat, IDBreed, BreedNum, BreedDen)
VALUES (@IDSheepGoat, @IDBreed, @BreedNum, @BreedDen)
GO
