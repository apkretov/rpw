USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_TypeBirth" AND type = "P")
    DROP PROCEDURE spSelect_TypeBirth
GO
CREATE PROCEDURE spSelect_TypeBirth AS
    SELECT * FROM TypeBirth
	WHERE TypeBirth > 0 AND
	    TypeBirth < 7
--	WHERE TypeBirth <> "-"
GO
spSelect_TypeBirth 
GO