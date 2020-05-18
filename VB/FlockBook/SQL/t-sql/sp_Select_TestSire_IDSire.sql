USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelect_TestSire_IDSire" AND type = "P")
    DROP PROCEDURE spSelect_TestSire_IDSire
GO
CREATE PROCEDURE spSelect_TestSire_IDSire (@IDSire char(6)) AS
    SELECT * FROM TestSire
	WHERE IDSire = @IDSire
GO
spSelect_TestSire_IDSire "¿¿0000"
GO