USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_Countries" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_Countries
GO
CREATE PROCEDURE spSelect_BrsShG_Countries AS
    SELECT IDCountry, Country
	FROM Countries
	WHERE IDCountry <> "-"
	ORDER BY Country
GO
spSelect_BrsShG_Countries
GO	