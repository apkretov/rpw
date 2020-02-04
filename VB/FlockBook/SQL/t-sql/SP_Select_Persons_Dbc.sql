USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Persons_Dbc" AND type = "P")
    DROP PROCEDURE spSelect_Persons_Dbc
GO
CREATE PROCEDURE spSelect_Persons_Dbc AS
    SELECT IDPers, Nam
	FROM Persons
	WHERE (Nam <> "-")
	ORDER BY Nam
GO
spSelect_Persons_Dbc 
GO