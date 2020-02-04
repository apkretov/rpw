use FlockBookRec
--use Test
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_StandWeight_IDBreed" AND type = "P")
DROP PROCEDURE spSelect_StandWeight_IDBreed
GO

CREATE PROCEDURE spSelect_StandWeight_IDBreed (@IDBreed char(2))
AS
select * from StandWeight
where IDBreed = @IDBreed
go

spSelect_StandWeight_IDBreed " »"
go