--USE FlockBookRec
use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_SexOffspring" AND type = "P")
DROP PROCEDURE spSelect_SexOffspring
GO

create procedure spSelect_SexOffspring as
select * from SexOffspring
where IDSex <> "-"
go

spSelect_SexOffspring
go