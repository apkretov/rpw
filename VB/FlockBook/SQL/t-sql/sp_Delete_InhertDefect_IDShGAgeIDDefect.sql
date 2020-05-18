USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_InhertDefect_IDShGAgeIDDefect" AND
    type = "P")
    DROP PROCEDURE spDelete_InhertDefect_IDShGAgeIDDefect
GO
CREATE PROCEDURE spDelete_InhertDefect_IDShGAgeIDDefect (@IDSheepGoat char(6), @Age tinyint, 
    @IDDefect int) AS
    DELETE InhertDefect
	WHERE IDSheepGoat = @IDSheepGoat AND 
	Age = @Age AND
	IDDefect = @IDDefect
GO
SELECT * FROM InhertDefect
GO
spDelete_InhertDefect_IDShGAgeIDDefect "¿¿0000", 1, 1
GO
SELECT * FROM InhertDefect
GO