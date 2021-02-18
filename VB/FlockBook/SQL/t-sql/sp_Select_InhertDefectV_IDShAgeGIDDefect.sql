USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_InhertDefectV_IDShGAgeIDDefect" AND
    type = "P")
    DROP PROCEDURE spSelect_InhertDefectV_IDShGAgeIDDefect
GO
CREATE PROCEDURE spSelect_InhertDefectV_IDShGAgeIDDefect (@IDSheepGoat char(6), @Age tinyint, 
    @IDDefect int) AS
    SELECT * FROM InhertDefectV
	WHERE IDSheepGoat = @IDSheepGoat AND 
	    Age = @Age AND
	    IDDefect = @IDDefect
GO
spSelect_InhertDefectV_IDShGAgeIDDefect "¿¿0000", 1, 2
GO
