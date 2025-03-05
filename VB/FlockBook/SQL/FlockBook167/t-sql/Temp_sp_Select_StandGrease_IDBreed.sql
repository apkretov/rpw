use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_StandGrease_IDBreed" AND type = "P")
DROP PROCEDURE spSelect_StandGrease_IDBreed
GO

CREATE PROCEDURE spSelect_StandGrease_IDBreed (@IDBreed char(2))
AS
select * from StandGrease
where IDBreed = @IDBreed
go

spSelect_StandGrease_IDBreed " »"
go