use FlockBookRec
--use Test
go
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spDelete_BreedCross_IDShGIDBreed" AND type = "P")
DROP PROCEDURE spDelete_BreedCross_IDShGIDBreed
GO

CREATE PROCEDURE spDelete_BreedCross_IDShGIDBreed (@IDSheepGoat char(6), @IDBreed char(2))
AS
delete BreedCross
where (IDSheepGoat = @IDSheepGoat) and (IDBreed = @IDBreed)
go