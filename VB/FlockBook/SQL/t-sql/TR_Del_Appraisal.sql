USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "trDel_Appraisal" AND type = "TR")
    DROP TRIGGER trDel_Appraisal -- Drop & create the trigger.
GO
CREATE TRIGGER trDel_Appraisal ON Appraisal FOR DELETE AS 
    DELETE InhertDefect FROM InhertDefect, deleted			-- Delete InhertDefect.
	WHERE InhertDefect.IDSheepGoat = deleted.IDSheepGoat AND 
	    InhertDefect.Age = deleted.Age
    DELETE SelIndxCompClass 
	FROM SelIndxCompClass, deleted
	WHERE deleted.Age = 1 AND 
	    SelIndxCompClass.IDSheepGoat = deleted.IDSheepGoat
GO
