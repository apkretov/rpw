USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Tree" AND type = "P")
    DROP PROCEDURE spInsert_Tree
GO
CREATE PROCEDURE spInsert_Tree (@IDClnt as char(9), @Refrsh bit) AS
    INSERT INTO Tree (IDClnt, Refrsh)
	VALUES (@IDClnt, @Refrsh)
GO
SELECT * FROM Tree
GO
spInsert_Tree "123456789", 1
GO
SELECT * FROM Tree
GO