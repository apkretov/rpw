--USE FlockBookRec
use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Liveability" AND type = "P")
DROP PROCEDURE spSelect_Liveability
GO

create procedure spSelect_Liveability as
select * from Liveability
where IDLiv <> "0"
go

spSelect_Liveability 
go