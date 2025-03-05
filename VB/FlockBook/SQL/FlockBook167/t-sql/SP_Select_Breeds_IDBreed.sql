use FlockBook
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelect_Breeds_IDBreed" AND type = "P")
DROP PROCEDURE spSelect_Breeds_IDBreed
GO

CREATE PROCEDURE spSelect_Breeds_IDBreed (@IDBreed char(2))
AS
select * from Breeds
where IDBreed = @IDBreed
go 
