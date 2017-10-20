USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Countries_IDCountr" AND type = "P")
    DROP PROCEDURE spDelete_Countries_IDCountr
GO
CREATE PROCEDURE spDelete_Countries_IDCountr (@IDCountry int) AS
    DELETE Countries
	WHERE IDCountry = @IDCountry
GO
spDelete_Countries_IDCountr 12
GO
