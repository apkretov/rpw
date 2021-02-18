USE FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_BreedNum" AND type = "P")
DROP PROCEDURE spSelect_BreedNum
GO

create procedure spSelect_BreedNum as
select * from BreedNum
go