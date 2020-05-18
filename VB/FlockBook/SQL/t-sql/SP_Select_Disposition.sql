USE FlockBookRec
--use Test
go
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Disposition" AND type = "P")
DROP PROCEDURE spSelect_Disposition
GO
create procedure spSelect_Disposition as
select * from Disposition
where IDDispReas <> "- "
go
