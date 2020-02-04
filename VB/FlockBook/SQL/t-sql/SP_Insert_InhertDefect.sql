USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_InhertDefect" AND type = "P")
    DROP PROCEDURE spInsert_InhertDefect
GO
CREATE PROCEDURE spInsert_InhertDefect (@IDSheepGoat char(6), @Age tinyint, @IDDefect int) AS
    INSERT INTO InhertDefect (IDSheepGoat, Age, IDDefect)
	VALUES (@IDSheepGoat, @Age, @IDDefect)
GO
SELECT * FROM InhertDefect 
GO
spInsert_InhertDefect "¿¿0000", 1, 2
GO
SELECT * FROM InhertDefect 
GO