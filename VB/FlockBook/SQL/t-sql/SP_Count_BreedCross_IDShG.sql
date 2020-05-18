USE FlockBookRec
--use Test
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	NAME = "spCount_BreedCross_IDShG" AND type = "P")
DROP PROCEDURE spCount_BreedCross_IDShG
GO

CREATE PROCEDURE spCount_BreedCross_IDShG (@IDSheepGoat char(6))
AS
SELECT COUNT(IDSheepGoat) FROM BreedCross
WHERE IDSheepGoat = @IDSheepGoat
GO 

spCount_BreedCross_IDShG "¿¿0010"
GO