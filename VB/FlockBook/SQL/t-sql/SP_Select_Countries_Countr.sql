USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Countries_Countr" AND type = "P")
    DROP PROCEDURE spSelect_Countries_Countr
GO
CREATE PROCEDURE spSelect_Countries_Countr (@Country varchar(50)) AS
    SELECT *
	FROM Countries
	WHERE Country = @Country
GO
spSelect_Countries_Countr "Кыргызстан"
GO
