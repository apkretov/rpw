USE FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Crimpins" AND type = "P")
DROP PROCEDURE spSelect_Crimpins
GO

create procedure spSelect_Crimpins as
select * from Crimpins
go

spSelect_Crimpins
go