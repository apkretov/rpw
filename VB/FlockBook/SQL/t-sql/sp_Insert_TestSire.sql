USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_TestSire" AND type = "P")
    DROP PROCEDURE spInsert_TestSire
GO
CREATE PROCEDURE spInsert_TestSire (@IDSire char(6), @DateTestSire varchar(8)) AS
    SET DATEFORMAT dmy
    INSERT INTO TestSire (IDSire, DateTestSire)
        VALUES (@IDSire, CAST(@DateTestSire AS smalldatetime))
GO
spInsert_TestSire "¿¿0001", "01.01.01"
GO
SELECT * FROM TestSire
GO