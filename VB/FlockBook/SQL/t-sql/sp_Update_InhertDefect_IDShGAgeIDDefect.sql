USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_InhertDefect_IDShGAgeIDDefect" AND
    type = "P")
    DROP PROCEDURE spUpdate_InhertDefect_IDShGAgeIDDefect
GO
CREATE PROCEDURE spUpdate_InhertDefect_IDShGAgeIDDefect (@IDSheepGoat char(6), @Age tinyint, 
    @IDDefectOrig int, @IDDefect int) AS
    UPDATE InhertDefect
	SET IDDefect = @IDDefect
	WHERE IDSheepGoat = @IDSheepGoat AND 
	Age = @Age AND
	IDDefect = @IDDefectOrig
GO
SELECT * FROM InhertDefect
GO
spUpdate_InhertDefect_IDShGAgeIDDefect "¿¿0000", 1, 2, 1
GO
SELECT * FROM InhertDefect
GO