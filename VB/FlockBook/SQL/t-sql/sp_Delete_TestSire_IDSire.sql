USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spDelete_TestSire_IDSire" AND type = "P")
    DROP PROCEDURE spDelete_TestSire_IDSire
GO
CREATE PROCEDURE spDelete_TestSire_IDSire @IDSire char(6) AS
    DELETE TestSire
	WHERE IDSire = @IDSire
GO
spDelete_TestSire_IDSire "¿¿0000"
GO
SELECT * FROM TestSire
G0