USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelect_InhertDefect_IDShGAge" AND type = "P")
    DROP PROCEDURE spSelect_InhertDefect_IDShGAge
GO
CREATE PROCEDURE spSelect_InhertDefect_IDShGAge (@IDSheepGoat char(6), @Age tinyint) AS
    SELECT * FROM InhertDefect
	WHERE IDSheepGoat = @IDSheepGoat AND
	Age = @Age
GO
spSelect_InhertDefect_IDShGAge "¿¿0000", 1
go
SELECT * FROM InhertDefect
GO