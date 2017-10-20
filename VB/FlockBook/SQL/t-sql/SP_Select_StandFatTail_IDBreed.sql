use FlockBook
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_StandFatTail_IDBreed" AND type = "P")
DROP PROCEDURE spSelect_StandFatTail_IDBreed
GO

CREATE PROCEDURE spSelect_StandFatTail_IDBreed (@IDBreed char(2))
AS
select * from StandFatTail
where IDBreed = @IDBreed
go

spSelect_StandFatTail_IDBreed "สร"
go