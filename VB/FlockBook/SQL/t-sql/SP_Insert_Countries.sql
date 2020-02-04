USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Countries" AND type = "P")
    DROP PROCEDURE spInsert_Countries
GO
CREATE PROCEDURE spInsert_Countries (@Country varchar(50), @Remark varchar(150)) AS
    INSERT INTO Countries (Country, Remark)
	VALUES (@Country, @Remark)
GO
SELECT * FROM Countries
GO
spInsert_Countries "KDFADSF", "ADSFASD"
GO
SELECT * FROM Countries
GO