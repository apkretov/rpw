USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Persons_IDPers" AND type = "P")
    DROP PROCEDURE spDelete_Persons_IDPers
GO
CREATE PROCEDURE spDelete_Persons_IDPers (@IDPers int) AS
    DELETE Persons
	WHERE IDPers = @IDPers
GO
spDelete_Persons_IDPers 3
GO
