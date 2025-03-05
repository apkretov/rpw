use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_BreedCross_IDShG" AND type = "P")
DROP PROCEDURE spSelect_BreedCross_IDShG
GO

CREATE PROCEDURE spSelect_BreedCross_IDShG (@IDSheepGoat char(6))
AS
select * from BreedCross
where IDSheepGoat = @IDSheepGoat
go 
