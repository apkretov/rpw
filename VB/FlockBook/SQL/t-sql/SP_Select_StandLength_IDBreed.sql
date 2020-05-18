use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_StandLength_IDBreed" AND type = "P")
DROP PROCEDURE spSelect_StandLength_IDBreed
GO

CREATE PROCEDURE spSelect_StandLength_IDBreed (@IDBreed char(2))
AS
select * from StandLength
where IDBreed = @IDBreed
go

spSelect_StandLength_IDBreed " »"
go