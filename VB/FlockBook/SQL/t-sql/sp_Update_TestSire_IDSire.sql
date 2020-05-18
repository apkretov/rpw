USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spUpdate_TestSire_IDSire" AND type = "P")
    DROP PROCEDURE spUpdate_TestSire_IDSire
GO
CREATE PROCEDURE spUpdate_TestSire_IDSire (@IDSire char(6), @DateTestSire varchar(8)) AS
    SET DATEFORMAT dmy
    UPDATE TestSire
	SET DateTestSire = CAST(@DateTestSire AS smalldatetime)
	    WHERE IDSire = @IDSire
GO
spUpdate_TestSire_IDSire "¿¿0000", "01.01.01"
GO
SELECT * FROM TestSire
GO